/*/*
 * TMR0 Generated Driver File
 * 
 * @file tmr0.c
 * 
 * @ingroup tmr0
 * 
 * @brief This is the generated driver implementation file for the TMR0 driver.
 *
 * @version TMR0 Driver Version 3.0.0
 *
 * @version Package Version 3.0.0 
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

#include <xc.h>
#include "../tmr0.h"
/**
 * @misradeviation{@advisory,2.5}
 * MPLABÂ® Code Configurator (MCC) Melody drivers provide macros that can be added to an application.
 * It depends on the application whether a macro is used or not. 
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_2 			0x0U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_4  			0x1U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_8  			0x2U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_16  			0x3U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_32  			0x4U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_64  			0x5U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_128  			0x6U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_256  			0x7U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_ASSIGNED  	0x0U
/* cppcheck-suppress misra-c2012-2.5 */
#define PRESCALER_NOT_ASSIGNED  0x1U
/* cppcheck-suppress misra-c2012-2.5 */
#define CLOCK_SOURCE_FOSC_4  	0x0U
/* cppcheck-suppress misra-c2012-2.5 */
#define CLOCK_SOURCE_T0CKI  	0x1U
/* cppcheck-suppress misra-c2012-2.5 */
#define INCREMENT_LOW_TO_HIGH  	0x0U
/* cppcheck-suppress misra-c2012-2.5 */
#define INCREMENT_HIGH_TO_LOW  	0x1U

static volatile uint8_t periodCount;
static void (*TMR0_OverflowCallback)(void);
static void TMR0_DefaultOverflowCallback(void);

void TMR0_Initialize(void)
{
	OPTION_REGbits.TMR0CS = CLOCK_SOURCE_FOSC_4;
	OPTION_REGbits.TMR0SE = INCREMENT_HIGH_TO_LOW;
	OPTION_REGbits.PS = PRESCALER_256;
	OPTION_REGbits.PSA = PRESCALER_ASSIGNED;

	TMR0 = 0x0U;
	periodCount = 0x0U;

	TMR0_OverflowCallback = TMR0_DefaultOverflowCallback;

	INTCONbits.TMR0IF = 0U;
}

void TMR0_Deinitialize(void)
{
	INTCONbits.TMR0IE = 0U;

	OPTION_REGbits.TMR0CS = CLOCK_SOURCE_T0CKI;
	OPTION_REGbits.TMR0SE = INCREMENT_HIGH_TO_LOW;
	OPTION_REGbits.PSA = PRESCALER_NOT_ASSIGNED;
	OPTION_REGbits.PS = PRESCALER_256;

	TMR0 = 0x0U;
	
	INTCONbits.TMR0IF = 0U;
}

uint8_t TMR0_CounterGet(void)
{
	return TMR0;
}

void TMR0_CounterSet(uint8_t timerVal)
{
	TMR0 = timerVal;
}

void TMR0_Reload(void)
{
	TMR0 = periodCount;
}

void TMR0_PeriodSet(uint8_t periodVal)
{
	periodCount = periodVal;
}

uint8_t TMR0_PeriodGet(void)
{
	return periodCount;
}

uint8_t TMR0_MaxCountGet(void)
{
	return TMR0_MAX_COUNT;
}

bool TMR0_OverflowStatusGet(void)
{
	return INTCONbits.TMR0IF;
}

void TMR0_OverflowStatusClear(void)
{
	INTCONbits.TMR0IF = 0U;
}

void TMR0_Tasks(void)
{
	if(1U == INTCONbits.TMR0IF)
	{
		TMR0_OverflowCallback();
		INTCONbits.TMR0IF = 0U;
	}
}

void TMR0_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
	TMR0_OverflowCallback = CallbackHandler;
}

static void TMR0_DefaultOverflowCallback(void)
{
	//Use TMR0_OverflowCallbackRegister function to use Custom ISR
}