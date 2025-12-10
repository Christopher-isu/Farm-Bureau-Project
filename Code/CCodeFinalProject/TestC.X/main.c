// main.c - PIC16F1788 - MPLAB X v6.20
// DigitalOutputs (0x7C) = Direct mirror to PORTB (RB0?RB7)
// SCRAM forces PORTB = 0x00 and sends 25 00
#include <xc.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/adc/adc.h"
#include "mcc_generated_files/uart/eusart.h"

// Memory layout
volatile __at(0x70) uint16_t AN0_value;
volatile __at(0x72) uint16_t AN1_value;
volatile __at(0x74) uint16_t AN2_value;
volatile __at(0x76) uint16_t AN3_value;
volatile __at(0x78) uint16_t AN5_value;
volatile __at(0x7A) uint8_t DigitalInputs;
volatile __at(0x7C) uint8_t DigitalOutputs;   // This now CONTROLS PORTB

#define CH_AN0 2
#define CH_AN1 3
#define CH_AN2 4
#define CH_AN3 5
#define CH_AN5 6

const uint8_t ids[7]       = {0x24, 0x25, 0xA0, 0xA1, 0xA2, 0xA3, 0xA5};
const uint8_t base_addr[7] = {0x7A, 0x7C, 0x70, 0x72, 0x74, 0x76, 0x78};

volatile uint8_t ch = 0;
volatile uint8_t first_cycle = 1;

void __interrupt() ISR(void)
{
    if (IOCIF)
    {
        if (IOCAFbits.IOCAF6)
        {
            IOCAFbits.IOCAF6 = 0;
            __delay_ms(20);
            if (!PORTAbits.RA6)
            {
                DigitalInputs |=  (1 << 6);
                DigitalInputs &= ~(1 << 7);
            }
        }
        if (IOCAFbits.IOCAF7)
        {
            IOCAFbits.IOCAF7 = 0;
            __delay_ms(20);
            if (!PORTAbits.RA7)
            {
                DigitalInputs &= ~(1 << 6);
                DigitalInputs &= ~(1 << 7);
            }
        }
        IOCIF = 0;
    }
}

void main(void)
{
    SYSTEM_Initialize();

    // === PORTB SETUP: All pins as digital outputs ===
    ANSELB = 0x00;        // All PORTB pins digital (not analog)
    TRISB = 0x00;         // All PORTB pins as outputs
    PORTB = 0x00;         // Start with all off

    // IOC Setup
    IOCANbits.IOCAN6 = 1;
    IOCANbits.IOCAN7 = 1;
    IOCAF = 0;
    IOCIE = 1; PEIE = 1; GIE = 1;

    DigitalInputs  = 0x00;
    DigitalOutputs = 0xFF;        // Start with all outputs off

    // Flush UART
    while (!TXSTAbits.TRMT);
    TXREG = 0xFF; while (!TXSTAbits.TRMT);
    TXREG = 0xFF; while (!TXSTAbits.TRMT);

    __delay_ms(100);

    while (1)
    {
        uint8_t scram_active = (DigitalInputs & (1 << 6));

        // ============================================================
        // SCRAM MODE: Force PORTB = 0 and blast status
        // ============================================================
        if (scram_active)
        {
            PORTB = 0x00;                        // FORCE ALL OUTPUTS OFF

            if (TXSTAbits.TRMT)
            {
                EUSART_Write(0x24);
                while (!TXSTAbits.TRMT);
                EUSART_Write(DigitalInputs);     // 0x40

                EUSART_Write(0x25);
                while (!TXSTAbits.TRMT);
                EUSART_Write(0x00);              // Shows outputs are forced off
            }
            __delay_us(10);
            continue;
        }

        // ============================================================
        // NORMAL MODE: DigitalOutputs controls PORTB directly
        // ============================================================
        PORTB = DigitalOutputs;                  // LIVE mirror to hardware!

        if (first_cycle || ch == 0)
        {
            while (!TXSTAbits.TRMT);
            EUSART_Write(0x24);
            while (!TXSTAbits.TRMT);
            EUSART_Write(DigitalInputs);

            FSR0L = base_addr[0];
            INDF0 = DigitalInputs;

            first_cycle = 0;
            ch = 1;
            continue;
        }

        if (ch == 1)
        {
            while (!TXSTAbits.TRMT);
            EUSART_Write(0x25);
            while (!TXSTAbits.TRMT);
            EUSART_Write(DigitalOutputs);        // Sent value = actual PORTB state

            FSR0L = base_addr[1];
            INDF0 = DigitalOutputs;

            ch = 2;
            ADC_SetPositiveChannel(CH_AN0);
            ADC_StartConversion();
            continue;
        }

        if (ADC_IsConversionDone())
        {
            uint16_t result = ADC_GetConversionResult();
            uint8_t high_byte = result >> 8;

            FSR0L = base_addr[ch];
            INDF0 = (uint8_t)result;
            INDF0 = high_byte;

            while (!TXSTAbits.TRMT);
            EUSART_Write(ids[ch]);
            while (!TXSTAbits.TRMT);
            EUSART_Write(high_byte);

            ch++;
            if (ch >= 7) ch = 0;
            else if (ch >= 2)
            {
                switch (ch)
                {
                    case 2: ADC_SetPositiveChannel(CH_AN0); break;
                    case 3: ADC_SetPositiveChannel(CH_AN1); break;
                    case 4: ADC_SetPositiveChannel(CH_AN2); break;
                    case 5: ADC_SetPositiveChannel(CH_AN3); break;
                    case 6: ADC_SetPositiveChannel(CH_AN5); break;
                }
                ADC_StartConversion();
            }
        }

        __delay_us(10);
    }
}