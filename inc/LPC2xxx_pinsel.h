/******************************************************************************
 * @file:    LPC2xxx_pinsel.h
 * @purpose: Header File for using LPC2xxx Pin Select Block
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. November 2010
 * @license: Simplified BSD License
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
 
#ifndef LPC2XXX_PINSEL_H_
#define LPC2XXX_PINSEL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_PINSEL
#error  Your CPU does not seem to have a Pin Select Block, or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup PINSEL LPC2xxx Pin Select Block interface
  * This file defines types and functions for using the LPC2xxx Pin Select
  * Block
  * @{
  */
  
/* Types --------------------------------------------------------------------*/

/** @addtogroup PINSEL_Types PINSEL Interface Typedefs
  * @{
  */

/** @addtogroup PINSEL_Pin_Type
  * @{
  */
typedef uint8_t PINSEL_Pin_Type;
#define PINSEL_IS_PIN(Pin)  (Pin <= 31)

/**
  * @}
  */


/** @defgroup PINSEL_Function_Settings  Pin Select Block Pin Function Settings
  * @{
  */
typedef enum {
    PINSEL_Function_Default = 0x00,
    PINSEL_Function_Alt1,
    PINSEL_Function_Alt2,
    PINSEL_Function_Alt3,
} PINSEL_Function_Type;
#define PINSEL_IS_FUNCTION(Function) \
                                  (((Function) == PINSEL_Function_Default) \
                                || ((Function) == PINSEL_Function_Alt1)    \
                                || ((Function) == PINSEL_Function_Alt2)    \
                                || ((Function) == PINSEL_Function_Alt3))
#define PINSEL_Function_Mask   (0x03)

/**
  * @}
  */  

/** @defgroup PINSEL_PinConfig  Simplified Pin Configuration Type
  * @{
  *
  * Values are in Separate, MCU-Specific Header Files.
  */
typedef uint8_t PINSEL_PinConfig_Type;

/**
  * @}
  */
  
/**
  * @}
  */
  
/* Inline Functions ---------------------------------------------------------*/

/** @addtogroup GPIO_Inline_Functions GPIO Interface Inline Functions
  * @{
  */
  
/** @brief  Set the Function of a Pin
  * @param  Pin      # of the Pin on Which to set the Function
  * @param  Function Function to Configure for the Pin
  * @return None.
  */
__INLINE static void PINSEL_SetPinFunction(PINSEL_Pin_Type Pin, PINSEL_Function_Type Function)
{
    uint8_t ShiftVal;
    
    
    lpc2xxx_lib_assert(PINSEL_IS_PIN(Pin));
    lpc2xxx_lib_assert(PINSEL_IS_FUNCTION(Function));
    
    /* Shift the function bits by (Pin * 2) */
    ShiftVal = (Pin & 0x0f) * 2;

    if (Pin > 0x0f) {    
        PINSEL->PINSEL1 = (PINSEL->PINSEL1 & ~(3 << ShiftVal)) | (Function << ShiftVal);
    } else {
        PINSEL->PINSEL0 = (PINSEL->PINSEL0 & ~(3 << ShiftVal)) | (Function << ShiftVal);
    }
}

/** @brief Quick Pin Configuration Function
  * @param  PinConfig The Pin / Configuration Hybrid Value
  * @return None.
  */
__INLINE static void PINSEL_SetPinConfig(PINSEL_PinConfig_Type PinConfig)
{
    uint16_t Pin = PinConfig & 0x1f;
    
    PINSEL_SetPinFunction(Pin, PinConfig >> 5);
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

#endif /* #ifndef LPC2XXX_PINSEL_H_ */
