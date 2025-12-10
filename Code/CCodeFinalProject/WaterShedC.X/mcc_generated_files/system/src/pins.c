/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.0.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

void (*IO_RA6_InterruptHandler)(void);
void (*IO_RA7_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x40;

    /**
    TRISx registers
    */
    TRISA = 0xFF;
    TRISB = 0x0;
    TRISC = 0xBF;
    TRISE = 0x8;

    /**
    ANSELx registers
    */
    ANSELA = 0x2F;
    ANSELB = 0x0;
    ANSELC = 0x3F;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0xFF;
    WPUC = 0x7F;
    WPUE = 0x8;
    OPTION_REGbits.nWPUEN = 0x0;
  
    /**
    ODx registers
    */
   
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    /**
    SLRCONx registers
    */
    SLRCONA = 0x0;
    SLRCONB = 0x0;
    SLRCONC = 0x0;
    /**
    INLVLx registers
    */
    INLVLA = 0x0;
    INLVLB = 0x0;
    INLVLC = 0xFF;
    INLVLE = 0x8;

    /**
    PPS registers
    */

    /**
    APFCON registers
    */
    APFCON1 = 0x0; //RC6->EUSART:TX;

   /**
    IOCx registers 
    */
    IOCAP = 0x80;
    IOCAN = 0x40;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;

    IO_RA6_SetInterruptHandler(IO_RA6_DefaultInterruptHandler);
    IO_RA7_SetInterruptHandler(IO_RA7_DefaultInterruptHandler);

    // Enable INTCONbits.IOCIE interrupt 
    INTCONbits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin IO_RA6}
    if(IOCAFbits.IOCAF6 == 1)
    {
        IO_RA6_ISR();  
    }
    // interrupt on change for pin IO_RA7}
    if(IOCAFbits.IOCAF7 == 1)
    {
        IO_RA7_ISR();  
    }
}
   
/**
   IO_RA6 Interrupt Service Routine
*/
void IO_RA6_ISR(void) {

    // Add custom IOCAF6 code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_RA6_InterruptHandler)
    {
        IO_RA6_InterruptHandler();
    }
    IOCAFbits.IOCAF6 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF6 at application runtime
*/
void IO_RA6_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_RA6_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF6
*/
void IO_RA6_DefaultInterruptHandler(void){
    // add your IO_RA6 interrupt custom code
    // or set custom function using IO_RA6_SetInterruptHandler()
}
   
/**
   IO_RA7 Interrupt Service Routine
*/
void IO_RA7_ISR(void) {

    // Add custom IOCAF7 code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_RA7_InterruptHandler)
    {
        IO_RA7_InterruptHandler();
    }
    IOCAFbits.IOCAF7 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF7 at application runtime
*/
void IO_RA7_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_RA7_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF7
*/
void IO_RA7_DefaultInterruptHandler(void){
    // add your IO_RA7 interrupt custom code
    // or set custom function using IO_RA7_SetInterruptHandler()
}
/**
 End of File
*/