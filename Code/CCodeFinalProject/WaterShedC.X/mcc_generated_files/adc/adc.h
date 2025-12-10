/**
 * ADC Generated Driver API Header File
 *
 * @file adc.h
 *  
 * @defgroup adc ADC
 *
 * @brief This file contains the API prototypes and data types for the ADC driver.
 *
 * @version ADC Driver Version 1.0.0
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

#ifndef ADC_H
#define ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_Initialize API
 */
#define ADC_Initialize   ADC_Initialize

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_SetPositiveChannel API
 */
#define ADC_SetPositiveChannel   ADC_SetPositiveChannel

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_SetNegativeChannel API
 */
#define ADC_SetNegativeChannel   ADC_SetNegativeChannel 

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_StartConversion API
 */
#define ADC_StartConversion  ADC_StartConversion

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_IsConversionDone API
 */
#define ADC_IsConversionDone ADC_IsConversionDone

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_GetConversionResult API
 */
#define ADC_GetConversionResult  ADC_GetConversionResult

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_GetConversion API
 */
#define ADC_GetConversion    ADC_GetConversion

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_TemperatureAcquisitionDelay API
 */
#define ADC_TemperatureAcquisitionDelay  ADC_TemperatureAcquisitionDelay

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_ISR API
 */
#define ADC_ISR ADC_ISR

/**
 * @ingroup  adc
 * @brief    Defines the Custom Name for the \ref ADC_SetInterruptHandler API
 */
#define ADC_SetInterruptHandler  ADC_SetInterruptHandler

/**
 @ingroup adc
 @typedef adc_result_t
 @brief Used for the result of the Analog-to-Digital (A/D) conversion.
 */

typedef uint16_t adc_result_t;

/**
 * @ingroup adc
 * @typedef adc_sync_double_result_t
 * @struct Used for the result for a Double ADC conversion value.
 */
typedef struct
{
    adc_result_t adcResult1;
    adc_result_t adcResult2;
} adc_sync_double_result_t;


/**
 * @ingroup adc
 * @enum adc_posChannel_t
 * @brief Contains the available positive ADC channels.
 */
typedef enum
{
    posChannel_DAC4 =  0x18,
    posChannel_DAC3 =  0x19,
    posChannel_DAC2 =  0x1c,
    posChannel_Temperature =  0x1d,
    posChannel_DAC1 =  0x1e,
    posChannel_FVR =  0x1f,
    posChannel_AN0 =  0x0,
    posChannel_AN1 =  0x1,
    posChannel_AN2 =  0x2,
    posChannel_AN3 =  0x3,
    posChannel_AN4 =  0x4
} adc_posChannel_t;

/**
 * @ingroup adc
 * @enum adc_negChannel_t
 * @brief Contains the available negative ADC channels.
 */
typedef enum
{
    negChannel_ADNREF =  0xf,
    negChannel_AN0 =  0x0,
    negChannel_AN1 =  0x1,
    negChannel_AN2 =  0x2,
    negChannel_AN3 =  0x3,
    negChannel_AN4 =  0x4
} adc_negChannel_t;

/**
 * @ingroup adc
 * @brief Initializes the ADC module. This routine is called before any other ADC routine.
 * @param None.
 * @return None.
 */
void ADC_Initialize(void);

/**
 * @ingroup adc
 * @brief Sets the positive channel for the A/D conversion.
 * @param channel - Analog channel number on which the A/D conversion will be applied.
 *                  Refer to adc_posChannel_t  for the available channels.
 * @return None.
 */
void ADC_SetPositiveChannel(adc_posChannel_t channel);

/**
 * @ingroup adc
 * @brief Sets the negative channel for the A/D conversion.
 * @param channel - Analog channel number on which the A/D conversion will be applied.
 *                  Refer to adc_negChannel_t  for the available channels.
 * @return None.
 */
void ADC_SetNegativeChannel(adc_negChannel_t channel);

/**
 * @ingroup adc
 * @brief Starts the A/D conversion.
 * @param None.
 * @return None.
 */
void ADC_StartConversion(void);
 
/**
 * @ingroup adc
 * @brief Checks if the A/D conversion is complete.
 * @param None.
 * @retval True - A/D conversion is complete
 * @retval False - A/D conversion is ongoing
 */
bool ADC_IsConversionDone(void);
 
/**
 * @ingroup adc
 * @brief Retrieves the result of the latest A/D conversion.
 * @param None.
 * @return The result of the A/D conversion. Refer to the adc_result_t.
 */
adc_result_t ADC_GetConversionResult(void);

/**
 * @ingroup adc
 * @brief Retrieves the result of a single A/D conversion on the selected channels.
 * @param posChannel - Postive analog channel number on which the A/D conversion will be applied.
 *                  Refer to adc_posChannel_t  for the available channels.
 * @param negChannel - Negative analog channel number on which the A/D conversion will be applied.
 *                  Refer to adc_negChannel_t  for the available channels.
* @return The result of the A/D conversion. Refer to the adc_result_t.
 */
adc_result_t ADC_GetConversion(adc_posChannel_t posChannel,adc_negChannel_t negChannel);
 
/**
 * @ingroup adc
 * @brief Adds the acquisition delay for the temperature sensor.
 * @pre Call this function when using the temperature sensor.
 * @param None.
 * @return None.
 */
void ADC_TemperatureAcquisitionDelay(void);

#endif	//ADC_H
