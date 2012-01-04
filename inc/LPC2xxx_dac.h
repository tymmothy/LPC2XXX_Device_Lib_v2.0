/******************************************************************************
 * @file:    LPC2xxx_dac.h
 * @purpose: Header File for using LPC2xxx Digital to Analog Converter
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. November 2010
 * @license: Simplified BSD License
 *
 * Notes:
 *  - don't forget PINSEL
 *  - DAC bias sets power & settling time:
 *      0: settling time 1.0 us, 700uA max
 *      1: settling time 2.5 uS, 350uA max
 *  - DAC value is 10-bit value, left justified in 16-bit field
 *  - Output is ((val & 0xffc0) / 65536) * Vref
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
 
#ifndef LPC2XXX_DAC_H_
#define LPC2XXX_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_DAC
#error  Your CPU does not seem to have an DAC, or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup DAC LPC2xxx DAC interface
  * This file defines types and functions for using the LPC2xxx DAC
  * @{
  */
  
/* Types --------------------------------------------------------------------*/

/** @addtogroup DAC_Types DAC Interface Typedefs
  * @{
  */

/** @addtogroup DAC_Bias DAC Bias Types
  * @{
  */
typedef enum {
    DAC_Bias_700uA,  /* 1uS settling time   */
    DAC_Bias_350uA,  /* 2.5uS settling time */ 
} DAC_Bias_Type;
#define DAC_IS_BIAS(Bias)  (((Bias) == DAC_Bias_700uA) \
                         || ((Bias) == DAC_Bias_350uA))

/**
  * @}
  */

/**
  * @}
  */

/* Inline Functions ---------------------------------------------------------*/

/** @addtogroup DAC_Inline_Functions DAC Interface Inline Functions
  * @{
  */

/** @brief Set the Bias Mode for the DAC
  * @param Bias  The Bias Mode to Set
  * @return None.
  *
  * Higher current means faster settling...
  */
__INLINE static void DAC_SetBias(DAC_Type *DAC, DAC_Bias_Type Bias)
{
    LPC2xxx_lib_assert(DAC_IS_BIAS(Bias));
    
    if (Bias) {
        DAC->CR |= DAC_BIAS;
    } else {
        DAC->CR &= DAC_BIAS;
    }
}

/** @brief Get the Currently Configured Bias Mode for the DAC
  * @param  None.
  * @return Bias Mode of the DAC
  */
__INLINE static DAC_Bias_Type DAC_GetBias(DAC_Type *DAC)
{
    return (DAC->CR & DAC_BIAS) ? 1:0;       
}

/** @brief Set the Output Value of the DAC
  * @param Value  The Output Value to Set
  * @return None.
  *
  * 10 useable bits, left justified in 16-bit integer
  */
__INLINE static void DAC_SetValue(DAC_Type *DAC, uint16_t Value)
{
    DAC->CR = (DAC->CR & DAC_BIAS) | ((Value << DAC_VALUE_Shift) & DAC_VALUE_Mask);
}

/** @brief Get the Current Output Value of the DAC
  * @param  None.
  * @return Current DAC Output Value
  */
__INLINE static uint16_t DAC_GetValue(DAC_Type *DAC)
{
    return (DAC->CR & DAC_VALUE_Mask) >> DAC_VALUE_Shift;
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

#endif /* #ifndef LPC2XXX_DAC_H_ */
