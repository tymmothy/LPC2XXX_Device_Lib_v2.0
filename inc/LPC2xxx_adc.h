/******************************************************************************
 * @file:    LPC2xxx_adc.h
 * @purpose: Header File for using LPC2xxx Analog to Digital Converters
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. November 2010
 * @license: Simplified BSD License
 *
 * Notes:
 *  - Enabling ADC:
 *     * must enable/disable AD converters first in power control block
 *     * don't forget PINSEL
 *
 *  - Interrupts - an interrupt is sent to VIC when DONE set to 1.
 *
 *  - DONE is negated when ADDR read
 *
 *  - adc passed as param should be address of ADC base
 *
 *  - ADC values returned are 10-bit, 0x0000 - 0x03ff (unless lower resolution
 *     set with burst mode)
 *
 *  - VPBCLK/(CLKDIV + 1) should be as close to 4.5 Mhz as possible for best
 *     ADC throughput
 *
 *
 ******************************************************************************
 * Copyright (c) 2012, Timothy Twillman
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice,
 *        this list of conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY TIMOTHY TWILLMAN ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL <COPYRIGHT HOLDER> ORCONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, ORCONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Timothy Twilllman.
 *****************************************************************************/
 
#ifndef LPC2XXX_ADC_H_
#define LPC2XXX_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_ADC
#error  Your CPU does not seem to have an ADC, or a CPU header file is missing/incorrect.
#endif


/** @addtogroup ADC LPC2xxx ADC interface
  * This file defines types and functions for using the LPC2xxx ADC
  * @{
  */
  
/* Types --------------------------------------------------------------------*/

/** @addtogroup ADC_Types ADC Interface Typedefs
  * @{
  */

/** @addtogroup ADC_Input_Channels
  * @{
  */
#define ADC_Channel_Mask (0x00ff)
#define ADC_ChannelMask_AD0  (1 << 0)  /*!< AD0 Input (PIO0_11) */
#define ADC_ChannelMask_AD1  (1 << 1)  /*!< AD1 Input (PIO1_0)  */
#define ADC_ChannelMask_AD2  (1 << 2)  /*!< AD2 Input (PIO1_1)  */
#define ADC_ChannelMask_AD3  (1 << 3)  /*!< AD3 Input (PIO1_2)  */
#define ADC_ChannelMask_AD4  (1 << 4)  /*!< AD4 Input (PIO1_3)  */
#define ADC_ChannelMask_AD5  (1 << 5)  /*!< AD5 Input (PIO1_4)  */
#define ADC_ChannelMask_AD6  (1 << 6)  /*!< AD6 Input (PIO1_10) */
#define ADC_ChannelMask_AD7  (1 << 7)  /*!< AD7 Input (PIO1_11) */
#define ADC_IS_INPUT_MASK(Mask)  ((Mask & ~(0xffUL)) == 0)

/**
  * @}
  */

/** @addtogroup ADC_Burst_Resolutions (need to be shifted to match register settings)
  * @{
  */
typedef enum {
    ADC_BurstResolution_10Bits = 0x00, /*!< 10 Bit Resolution (11 Clock Cycles) */
    ADC_BurstResolution_9Bits,         /*!<  9 Bit Resolution (10 Clock Cycles) */
    ADC_BurstResolution_8Bits,         /*!<  8 Bit Resolution ( 9 Clock Cycles) */
    ADC_BurstResolution_7Bits,         /*!<  7 Bit Resolution ( 8 Clock Cycles) */
    ADC_BurstResolution_6Bits,         /*!<  6 Bit Resolution ( 7 Clock Cycles) */
    ADC_BurstResolution_5Bits,         /*!<  5 Bit Resolution ( 6 Clock Cycles) */
    ADC_BurstResolution_4Bits,         /*!<  4 Bit Resolution ( 5 Clock Cycles) */
    ADC_BurstResolution_3Bits          /*!<  3 Bit Resolution ( 4 Clock Cycles) */
} ADC_BurstResolution_Type;
#define ADC_IS_BURST_RESOLUTION(Resolution) (((Resolution) == ADC_BurstResolution_10Bits) \
                                          || ((Resolution) == ADC_BurstResolution_9Bits)  \
                                          || ((Resolution) == ADC_BurstResolution_8Bits)  \
                                          || ((Resolution) == ADC_BurstResolution_7Bits)  \
                                          || ((Resolution) == ADC_BurstResolution_6Bits)  \
                                          || ((Resolution) == ADC_BurstResolution_5Bits)  \
                                          || ((Resolution) == ADC_BurstResolution_4Bits)  \
                                          || ((Resolution) == ADC_BurstResolution_3Bits))
/**
  * @}
  */

/** @addtogroup ADC_Conversion_Start_Settings
  * @{
  */
typedef enum {
    ADC_Start_None = 0x00,         /*!< Stop ADC                                   */
    ADC_Start_Now,                 /*!< Start a Conversion Now                     */
    ADC_Start_TIMER0_MAT2_Rising,  /*!< Start Conversion on Edge @ TIMER0 MAT2 Pin */
    ADC_Start_TIMER0_MAT0_Rising,  /*!< Start Conversion on Edge @ TIMER0 MAT0 Pin */
    ADC_Start_TIMER0_MAT1_Rising,  /*!< Start Conversion on Edge @ TIMER0 MAT1 Pin */
    ADC_Start_TIMER0_MAT3_Rising,  /*!< Start Conversion on Edge @ TIMER0 MAT3 Pin */
    ADC_Start_TIMER1_MAT0_Rising,  /*!< Start Conversion on Edge @ TIMER1 MAT0 Pin */
    ADC_Start_TIMER1_MAT1_Rising,  /*!< Start Conversion on Edge @ TIMER1 MAT1 Pin */
    ADC_Start_None2,               /*!< Stop ADC                                   */
    ADC_Start_Now2,                /*!< Start a Conversion Now                     */
    ADC_Start_TIMER0_MAT2_Falling, /*!< Start Conversion on Edge @ TIMER0 MAT2 Pin */
    ADC_Start_TIMER0_MAT0_Falling, /*!< Start Conversion on Edge @ TIMER0 MAT0 Pin */
    ADC_Start_TIMER0_MAT1_Falling, /*!< Start Conversion on Edge @ TIMER0 MAT1 Pin */
    ADC_Start_TIMER0_MAT3_Falling, /*!< Start Conversion on Edge @ TIMER0 MAT3 Pin */
    ADC_Start_TIMER1_MAT0_Falling, /*!< Start Conversion on Edge @ TIMER1 MAT0 Pin */
    ADC_Start_TIMER1_MAT1_Falling, /*!< Start Conversion on Edge @ TIMER1 MAT1 Pin */
} ADC_Start_Type;
#define ADC_IS_START(Start) (((Start) == ADC_Start_None)                \
                          || ((Start) == ADC_Start_None2)               \
                          || ((Start) == ADC_Start_Now)                 \
                          || ((Start) == ADC_Start_Now2)                \
                          || ((Start) == ADC_Start_TIMER0_MAT2_Rising)  \
                          || ((Start) == ADC_Start_TIMER0_MAT2_Falling) \
                          || ((Start) == ADC_Start_TIMER0_MAT0_Rising)  \
                          || ((Start) == ADC_Start_TIMER0_MAT0_Falling) \
                          || ((Start) == ADC_Start_TIMER0_MAT1_Rising)  \
                          || ((Start) == ADC_Start_TIMER0_MAT1_Falling) \
                          || ((Start) == ADC_Start_TIMER0_MAT3_Rising)  \
                          || ((Start) == ADC_Start_TIMER0_MAT3_Falling) \
                          || ((Start) == ADC_Start_TIMER1_MAT0_Rising)  \
                          || ((Start) == ADC_Start_TIMER1_MAT0_Falling) \
                          || ((Start) == ADC_Start_TIMER1_MAT1_Rising)  \
                          || ((Start) == ADC_Start_TIMER1_MAT1_Falling))


/**
  * @}
  */

/**
  * @}
  */

/* Inline Functions ---------------------------------------------------------*/


/** @addtogroup ADC_Inline_Functions ADC Interface Inline Functions
  * @{
  */
  

/** @brief Enable the ADC Input Pin(s) Set in the Mask (multiple just for Burst mode)
  * @param  ChannelMask Channels (1 bit per channel) to enable
  * @return None.
  */
__INLINE static void ADC_EnableChannelMask(ADC_Type *ADC, uint16_t ChannelMask)
{
    lpc2xxx_lib_assert(ADC_IS_INPUT_MASK(ChannelMask));
    
    ADC->CR |= (ChannelMask << ADC_SEL_Shift);
}

/** @brief Disable the ADC Input Pin(s) Set in the Mask (multiple just for Burst mode)
  * @param  ChannelMask Channels (1 bit per channel) to disable
  * @return None.
  */
__INLINE static void ADC_DisableChannelMask(ADC_Type *ADC, uint16_t ChannelMask)
{
    lpc2xxx_lib_assert(ADC_IS_INPUT_MASK(ChannelMask));
    
    ADC->CR &= ~(ChannelMask << ADC_SEL_Shift);
}

/** @brief Get the Currently Configured ADC Input Pin(s)
  * @param  ADC         The A to D Converter
  * @return The Current ADC Input Pin(s)
  */
__INLINE static uint16_t ADC_GetChannelMask(ADC_Type *ADC)
{
    return ADC->CR & ADC_SEL_Mask;
}

/** @brief Enable an ADC Channel (multiple can be enabled for burst mode)
  * @param  Channel # to enable
  * @return None.
  */
__INLINE static void ADC_EnableChannel(ADC_Type *ADC, uint8_t Channel)
{
   /* Make sure only 1 channel selected */
   lpc2xxx_lib_assert(Input <= 7);

    ADC->CR |= (1 << (Channel + ADC_SEL_Shift));
}

/** @brief Disable an ADC Channel
  * @param  Channel # to disable
  * @return None.
  */
__INLINE static void ADC_DisableChannel(ADC_Type *ADC, uint8_t Channel)
{
   /* Make sure only 1 channel selected */
   lpc2xxx_lib_assert(Input <= 7);

    ADC->CR &= ~(1 << (Channel + ADC_SEL_Shift));
}

/** @brief Determine Whether an ADC Channel is Enabled
  * @param  Channel # to check
  * @return 1 if the channel is enabled, 0 otherwise.
  */
__INLINE static uint8_t ADC_ChannelIsEnabled(ADC_Type *ADC, uint8_t Channel)
{
    return (ADC->CR & (1 << (Channel + ADC_SEL_Shift))) ? 1:0;
}

/** @brief Set the ADC Clock Divisor.  End clock rate should be <= 4.5Mhz
  * @param  ADC         The A to D Converter
  * @param  Divisor  The divisor by which to divide the clock
  * @return None.
  */
__INLINE static void ADC_SetClockDivisor(ADC_Type *ADC, uint8_t Divisor)
{
    ADC->CR = (ADC->CR & ~ADC_CLKDIV_Mask) | (Divisor << ADC_CLKDIV_Shift);
}

/** @brief Get the Current ADC Clock Divisor
  * @param  ADC         The A to D Converter
  * @return The Current ADC Clock Divisor
  */
__INLINE static uint8_t ADC_GetClockDivisor(ADC_Type *ADC)
{
    return (ADC->CR & ADC_CLKDIV_Mask) >> ADC_CLKDIV_Shift;
}

/** @brief Enable the ADC Burst Mode
  * @param  None.
  * @return None.
  */
__INLINE static void ADC_EnableBurstMode(ADC_Type *ADC)
{
    ADC->CR |= ADC_BURST;
}

/** @brief Disable the ADC Burst Mode
  * @param  None.
  * @return None.
  */
__INLINE static void ADC_DisableBurstMode(ADC_Type *ADC)
{
    ADC->CR &= ~ADC_BURST;
}

/** @brief Determine Whether Burst Mode is Enabled
  * @param  None.
  * @return 1 if Burst Mode is Enabled, 0 Otherwise
  */
__INLINE static uint8_t ADC_BurstModeIsEnabled(ADC_Type *ADC)
{
    return (ADC->CR & ADC_BURST) ? 1:0;
}

/** @brief Enable ADC Power-Down Mode
  * @param  ADC         The A to D Converter
  * @return None.
  */
__INLINE static void ADC_EnablePowerDown(ADC_Type *ADC)
{
    ADC->CR |= ADC_PDN;
}

/** @brief Disable ADC Power-Down Mode
  * @param  ADC         The A to D Converter
  * @return None.
  */
__INLINE static void ADC_DisablePowerDown(ADC_Type *ADC)
{
    ADC->CR &= ~ADC_PDN;
}

/** @brief Read Whether the ADC's Power-Down Mode is Enabled
  * @param  ADC         The A to D Converter
  * @return 1 if the ADC is in Power-Down Mode, 0 Otherwise
  */
__INLINE static uint8_t ADC_PowerDownIsEnabled(ADC_Type *ADC)
{
    return (ADC->CR & ADC_PDN) ? 1:0;
}

/** @brief Set the ADC Burst Conversion Resolution
  * @param  ADC         The A to D Converter
  * @param  Resolution  Token indicating the conversion resolution setting 
  * @return None.
  */
__INLINE static void ADC_SetBurstResolution(ADC_Type *ADC, ADC_BurstResolution_Type Resolution)
{
    lpc2xxx_lib_assert(ADC_IS_BURST_RESOLUTION(Resolution));
    
    ADC->CR = (ADC->CR & ~ADC_CLKS_Mask) | (Resolution << ADC_CLKS_Shift);
}

/** @brief Get the Configured ADC Burst Resolution
  * @param  ADC         The A to D Converter
  * @return The Configured Burst Resolution
  */
__INLINE static ADC_BurstResolution_Type ADC_GetBurstResolution(ADC_Type *ADC)
{
    return ((ADC->CR & ADC_CLKS_Mask) >> ADC_CLKS_Shift);
}

/** @brief Set the ADC Start Mode Type
  * @param  ADC         The A to D Converter
  * @param  Start       Condition to trigger start (immediate if ADC_Start_Now)
  * @return None.
  */
__INLINE static void ADC_SetStartMode(ADC_Type *ADC, ADC_Start_Type Start)
{
    lpc2xxx_lib_assert(ADC_IS_START(Start));
    /* Note: EDGE is the bit above the START bits which is why this works */
    ADC->CR = (ADC->CR & ~(ADC_START_Mask | ADC_EDGE)) | (Start << ADC_START_Shift);
}

/** @brief Get the Configured ADC Start Mode
  * @param  ADC         The A to D Converter
  * @return The Current ADC Start Mode
  */
__INLINE static ADC_Start_Type ADC_GetStartMode(ADC_Type *ADC)
{
    return ((ADC->CR & (ADC_START_Mask | ADC_EDGE)) >> ADC_START_Shift);
}

/** @brief Read an ADC Channel
  * @param  ADC         The A to D Converter
  * @return Last conversion value for the given input
  */
__INLINE static uint16_t ADC_Read(ADC_Type *ADC)
{
   return (ADC->DR & ADC_V_VREF_Mask) >> ADC_V_VREF_Shift;
}


/** @brief Get the ADC's Done Flag
  * @param  ADC         The A to D Converter
  * @return 1 if ADC is done converting, 0 otherwise
  */
__INLINE static uint8_t ADC_IsDone(ADC_Type *ADC)
{
    return (ADC->DR & ADC_DONE) ? 1:0;
}

/** @brief Get the ADC's Overrun Flag
  * @param  ADC         The A to D Converter
  * @return 1 if a data overwrite occurred, 0 otherwise
  */
__INLINE static uint8_t ADC_IsOverrun(ADC_Type *ADC)
{
    return (ADC->DR & ADC_OVERRUN) ? 1:0;
}

/** @brief Check whether the ADC is currently busy.
  * @param  ADC         The A to D Converter
  * @return 1 if the ADC is busy, 0 otherwise
  */
__INLINE static uint8_t ADC_IsBusy(ADC_Type *ADC)
{
    return !(ADC->DR & ADC_DONE);
}

/**
  * @}
  */
  
/**
  * @}
  */

#ifdef __cplusplus
};
#endif

#endif /* #ifndef LPC2XXX_ADC_H_ */
