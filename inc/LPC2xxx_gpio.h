/******************************************************************************
 * @file:    LPC2xxx_gpio.h
 * @purpose: Header File for using LPC2xxx General Purpose IO
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
 
#ifndef LPC2XXX_GPIO_H_
#define LPC2XXX_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_GPIO
#error  Your CPU does not seem to have (Legacy) GPIO, or a CPU header file is missing/incorrect.  
#endif

/** @addtogroup GPIO LPC2xxx GPIO interface
  * This file defines types and functions for using the LPC2xxx GPIO Pins
  * @{
  */
  
/* Types --------------------------------------------------------------------*/

/** @addtogroup GPIO_Types GPIO Interface Typedefs
  * @{
  */

/** @defgroup GPIO_Directions
  * @{
  */
typedef enum {
    GPIO_Direction_In  = 0,
    GPIO_Direction_Out = 1
} GPIO_DirectionType;
#define GPIO_IS_DIRECTION_TYPE(Direction)  (((Direction) == GPIO_Direction_In) \
                                         || ((Direction) == GPIO_Direction_Out))

/**
  * @}
  */
  
/** @defgroup GPIO_Pins
  * @{
  */
/*! GPIO Pins */
#define GPIO_Pin_0       (1 << 0)
#define GPIO_Pin_1       (1 << 1)
#define GPIO_Pin_2       (1 << 2)
#define GPIO_Pin_3       (1 << 3)
#define GPIO_Pin_4       (1 << 4)
#define GPIO_Pin_5       (1 << 5)
#define GPIO_Pin_6       (1 << 6)
#define GPIO_Pin_7       (1 << 7)
#define GPIO_Pin_8       (1 << 8)
#define GPIO_Pin_9       (1 << 9)
#define GPIO_Pin_10      (1 << 10)
#define GPIO_Pin_11      (1 << 11)
#define GPIO_Pin_12      (1 << 12)
#define GPIO_Pin_13      (1 << 13)
#define GPIO_Pin_14      (1 << 14)
#define GPIO_Pin_15      (1 << 15)
#define GPIO_Pin_16      (1 << 16)
#define GPIO_Pin_17      (1 << 17)
#define GPIO_Pin_18      (1 << 18)
#define GPIO_Pin_19      (1 << 19)
#define GPIO_Pin_20      (1 << 20)
#define GPIO_Pin_21      (1 << 21)
#define GPIO_Pin_22      (1 << 22)
#define GPIO_Pin_23      (1 << 23)
#define GPIO_Pin_24      (1 << 24)
#define GPIO_Pin_25      (1 << 25)
#define GPIO_Pin_26      (1 << 26)
#define GPIO_Pin_27      (1 << 27)
#define GPIO_Pin_28      (1 << 28)
#define GPIO_Pin_29      (1 << 29)
#define GPIO_Pin_30      (1 << 30)
#define GPIO_Pin_31      (1 << 31)

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
  
/** @brief Write the given bits to the given pins
  * @param  GPIO      The GPIO port to write to
  * @param  Pins      The pins on the GPIO port to affect
  * @param  Bits      The bit values to apply to those pins
  * @return None.
  *
  * Bits will be essentially ANDed with Pins in hardware, and written to those
  * pins.
  * e.g. if Pins == GPIO_Pin_3 | GPIO_Pin_4 and Bits = GPIO_Pin_4, pin 3
  * on the GPIO port will be set low, and pin 4 will be set high (dependent
  * of course on the data direction settings of the port)
  */
__INLINE static void GPIO_WritePins(GPIO_Type *GPIO, uint32_t Pins, uint32_t Bits)
{
    GPIO->SET = Pins & Bits;
    GPIO->CLR = Pins ^ Bits;
}

/** @brief Read the logic state of the given pins
  * @param  GPIO      The GPIO port to write to
  * @param  Pins      The pins on the GPIO port to affect
  * @return None.
  *
  * The return value will have the states of the pins as individual bits.
  *  e.g. if Pins == GPIO_Pin_3 and pin 3 on that port is high, it will
  *  return a binary "1" in bit position 3.
  */
__INLINE static uint16_t GPIO_ReadPins(GPIO_Type *GPIO, uint32_t Pins)
{
    return GPIO->PIN & Pins;
}

/** @brief Set the state of the given pins to High (if configured for output)
  * @param  GPIO      The GPIO port to write to
  * @param  Pins      The pins on the GPIO port to affect
  * @param  Value     The bit values to apply to those pins
  * @return None.
  */
__INLINE static void GPIO_SetPins(GPIO_Type *GPIO, uint32_t Pins)
{
    GPIO->SET = Pins;
}

/** @brief Set the state of the given pins to Low (if configured for output)
  * @param  GPIO      The GPIO port to write to
  * @param  Pins      The pins on the GPIO port to affect
  * @param  Value     The bit values to apply to those pins
  * @return None.
  */
__INLINE static void GPIO_ClearPins(GPIO_Type *GPIO, uint32_t Pins)
{
    GPIO->CLR = Pins;
}

/** @brief Set the directions of specified pins of the GPIO port
  * @param  GPIO      The GPIO port to read from
  * @param  Pins      Pins for which to configure direction
  * @param  Direction The direction to set for given pins
  * @return None.
  */
__INLINE static void GPIO_SetPinDirections(GPIO_Type *GPIO, uint32_t Pins, 
                                           GPIO_DirectionType Direction)
{
    lpc2xxx_lib_assert(GPIO_IS_DIRECTION_TYPE(Direction));
    
    if (Direction) {
        GPIO->DIR |= Pins;
    } else {
        GPIO->DIR &= ~Pins;
    }
}

/** @brief Get the direction of a single pin of the GPIO port
  * @param  GPIO   The GPIO port to read from
  * @param  Pin    The pin for which to get the direction   
  * @return None.
  */
__INLINE static uint16_t GPIO_GetPinDirection(GPIO_Type *GPIO, uint16_t Pin)
{
    lpc2xxx_lib_assert(GPIO_IS_PIN_TYPE(Pin));
    
    return (GPIO->DIR & Pin) ? GPIO_Direction_In:GPIO_Direction_Out;
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

#endif /* #ifndef LPC2XXX_GPIO_H_ */
