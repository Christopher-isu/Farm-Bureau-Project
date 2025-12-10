/**
 * TMR0 Generated Driver API Header File
 * 
 * @file tmr0.h
 * 
 * @defgroup  tmr0 TMR0
 * 
 * @brief This file contains API prototypes and other data types for the Timer0 (TMR0) driver
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

#ifndef TMR0_H
#define TMR0_H

#include <stdbool.h>
#include <stdint.h>
#include "tmr0_deprecated.h"

/**
 * @misradeviation{@advisory,2.5}
 * MPLABÂ® Code Configurator (MCC) Melody drivers provide macros that can be added to an application. 
 * It depends on the application whether a macro is used or not. 
 */
/**
 * @ingroup tmr0
 * @brief Defines the TMR0 maximum count value
 */
/* cppcheck-suppress misra-c2012-2.5 */ 
#define TMR0_MAX_COUNT (0xFFU)
/**
 * @ingroup tmr0
 * @brief Defines the TMR0 prescaled frequency in hertz.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR0_CLOCK_FREQ (15625UL)
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_CLOCK_FREQ
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TIMER0_CLOCK_FREQ TMR0_CLOCK_FREQ
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_MAX_COUNT
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TIMER0_MAX_COUNT TMR0_MAX_COUNT
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Initialize API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_Initialize TMR0_Initialize
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Deinitialize API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_Deinitialize TMR0_Deinitialize
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_CounterGet API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_CounterGet TMR0_CounterGet
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_CounterSet API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_CounterSet TMR0_CounterSet
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_PeriodSet API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_PeriodSet TMR0_PeriodSet
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_PeriodGet API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_PeriodGet TMR0_PeriodGet
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Reload API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_Reload TMR0_Reload
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_MaxCountGet API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_MaxCountGet TMR0_MaxCountGet
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_OverflowStatusGet API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_OverflowStatusGet TMR0_OverflowStatusGet
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_OverflowStatusClear API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_OverflowStatusClear TMR0_OverflowStatusClear
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_Tasks API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_Tasks TMR0_Tasks
/**
 * @ingroup tmr0
 * @brief Defines the Custom Name for the \ref TMR0_OverflowCallbackRegister API
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer0_OverflowCallbackRegister TMR0_OverflowCallbackRegister

/**
 * @ingroup tmr0
 * @brief Initializes the TMR0 module. This routine must be called before any other timer routines.
 * @param None.
 * @return None.
 */
void TMR0_Initialize(void);

/**
 * @ingroup tmr0
 * @brief Deinitializes the TMR0 module.
 * @param None.
 * @return None.
 */
void TMR0_Deinitialize(void);

/**
 * @ingroup tmr0
 * @brief Reads the 8-bit value from the Timer0 register.
 * @pre Initialize Timer0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return 8-bit data from the Timer0 register
 */
uint8_t TMR0_CounterGet(void);

/**
 * @ingroup tmr0
 * @brief Writes an 8-bit value to the Timer0 register.
 * @pre Initialize Timer0 with TMR0_Initialize() before calling this API.
 * @param timerVal - 8-bit value to be written to the Timer0 register
 * @return None.
 */
void TMR0_CounterSet(uint8_t timerVal);

/**
 * @ingroup tmr0
 * @brief Loads an 8-bit value to the Timer0 register.
 * @pre Initialize Timer0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR0_Reload(void);

/**
 * @ingroup tmr0
 * @brief Loads the period value to the period count variable.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param periodVal - Period value written to the period count variable
 * @return None.
 */
void TMR0_PeriodSet(uint8_t periodVal);

/**
 * @ingroup tmr0
 * @brief Returns the TMR0 period count value.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return TMR0 period count value
 */
uint8_t TMR0_PeriodGet(void);

/**
 * @ingroup tmr0
 * @brief Returns the TMR0 maximum count value.
 * @param None.
 * @return TMR0 maximum count value
 */
uint8_t TMR0_MaxCountGet(void);

/**
 * @ingroup tmr0
 * @brief Setter function for the Timer0 overflow callback.
 * @param CallbackHandler - Pointer to custom callback
 * @return None.
 */
 void TMR0_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr0
 * @brief Returns the Timer Overflow flag status in Non-Interrupt mode.
 * @param None.
 * @retval True  - Timer overflow has occurred
 * @retval False - Timer overflow has not occurred
 */
bool TMR0_OverflowStatusGet(void);

/**
 * @ingroup tmr0
 * @brief Clears the Timer Overflow flag in Non-Interrupt mode.
 * @param None.
 * @retval None.
 */
void TMR0_OverflowStatusClear(void);

/**
 * @ingroup tmr0
 * @brief Performs tasks to be executed during the timer overflow event.
 * @param None.
 * @return None.
 */
void TMR0_Tasks(void);

#endif //TMR0_H