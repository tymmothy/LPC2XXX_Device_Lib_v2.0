/******************************************************************************
 * @file:    LPC2148_pinconfig.h
 * @purpose: Pin configurations specific to LPC214x Pin Select Block
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. November 2010
 * @license: Simplified BSD License
 *
 * TODO: This is same as the LPC2138 -- needs to be updated for USB settings
 *  in 2148.
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

#ifndef LPC2148_PINCONFIG_H_
#define LPC2148_PINCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx_pinsel.h"
#include "LPC2xxx_lib_assert.h"


/** @addtogroup LPC2148_PINCONFIG LPC214x Pin Select Block interface
  * This file has definitions specific to the LPC214x Chips' Pin Select
  * Block
  * @{
  */
  
/* Types --------------------------------------------------------------------*/

/** @addtogroup LPC2148_PINCONFIG_Types PINCONFIG Interface Definitions
  * @{
  */

/** @defgroup LPC2148_PINSEL_PinConfigs Simplified Pin Configuration Definitions
  * @{
  */
#define PINSEL_PinConfig_0_0_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x00)
#define PINSEL_PinConfig_0_0_TXD0      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x00)
#define PINSEL_PinConfig_0_0_PWM1      (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x00)

#define PINSEL_PinConfig_0_1_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x01)
#define PINSEL_PinConfig_0_1_RXD0      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x01)
#define PINSEL_PinConfig_0_1_PWM3      (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x01)
#define PINSEL_PinConfig_0_1_EINT0     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x01)

#define PINSEL_PinConfig_0_2_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x02)
#define PINSEL_PinConfig_0_2_SCL0      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x02)
#define PINSEL_PinConfig_0_2_CAP0_0    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x02)

#define PINSEL_PinConfig_0_3_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x03)
#define PINSEL_PinConfig_0_3_SDA0      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x03)
#define PINSEL_PinConfig_0_3_MAT0_0    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x03)
#define PINSEL_PinConfig_0_3_EINT1     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x03)

#define PINSEL_PinConfig_0_4_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x04)
#define PINSEL_PinConfig_0_4_SCK0      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x04)
#define PINSEL_PinConfig_0_4_CAP0_1    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x04)
#define PINSEL_PinConfig_0_4_AD0_6     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x04)

#define PINSEL_PinConfig_0_5_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x05)
#define PINSEL_PinConfig_0_5_MISO0     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x05)
#define PINSEL_PinConfig_0_5_MAT0_1    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x05)
#define PINSEL_PinConfig_0_5_AD0_7     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x05)

#define PINSEL_PinConfig_0_6_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x06)
#define PINSEL_PinConfig_0_6_MOSI0     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x06)
#define PINSEL_PinConfig_0_6_CAP0_2    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x06)
#define PINSEL_PinConfig_0_6_AD1_0     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x06)

#define PINSEL_PinConfig_0_7_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x07)
#define PINSEL_PinConfig_0_7_SSEL0     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x07)
#define PINSEL_PinConfig_0_7_PWM2      (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x07)
#define PINSEL_PinConfig_0_7_EINT2     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x07)

#define PINSEL_PinConfig_0_8_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x08)
#define PINSEL_PinConfig_0_8_TXD1      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x08)
#define PINSEL_PinConfig_0_8_PWM4      (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x08)
#define PINSEL_PinConfig_0_8_AD1_1     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x08)

#define PINSEL_PinConfig_0_9_PIO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x09)
#define PINSEL_PinConfig_0_9_RXD1      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x09)
#define PINSEL_PinConfig_0_9_PWM6      (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x09)
#define PINSEL_PinConfig_0_9_EINT3     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x09)

#define PINSEL_PinConfig_0_10_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x0a)
#define PINSEL_PinConfig_0_10_RTS1     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x0a)
#define PINSEL_PinConfig_0_10_CAP1_0   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x0a)
#define PINSEL_PinConfig_0_10_AD1_2    (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x0a)

#define PINSEL_PinConfig_0_11_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x0b)
#define PINSEL_PinConfig_0_11_CTS1     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x0b)
#define PINSEL_PinConfig_0_11_CAP1_1   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x0b)
#define PINSEL_PinConfig_0_11_SCL1     (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x0b)

#define PINSEL_PinConfig_0_12_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x0c)
#define PINSEL_PinConfig_0_12_DSR1     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x0c)
#define PINSEL_PinConfig_0_12_MAT1_0   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x0c)
#define PINSEL_PinConfig_0_12_AD1_3    (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x0c)

#define PINSEL_PinConfig_0_13_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x0d)
#define PINSEL_PinConfig_0_13_DTR1     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x0d)
#define PINSEL_PinConfig_0_13_MAT1_1   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x0d)
#define PINSEL_PinConfig_0_13_AD1_4    (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x0d)

#define PINSEL_PinConfig_0_14_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x0e)
#define PINSEL_PinConfig_0_14_DCD1     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x0e)
#define PINSEL_PinConfig_0_14_EINT2    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x0e)
#define PINSEL_PinConfig_0_14_AD1_5    (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x0e)

#define PINSEL_PinConfig_0_15_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x0f)
#define PINSEL_PinConfig_0_15_RI1      (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x0f)
#define PINSEL_PinConfig_0_15_EINT2    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x0f)
#define PINSEL_PinConfig_0_15_AD1_5    (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x0f)

#define PINSEL_PinConfig_0_16_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x10)
#define PINSEL_PinConfig_0_16_EINT0    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x10)
#define PINSEL_PinConfig_0_16_MAT0_2   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x10)
#define PINSEL_PinConfig_0_16_CAP0_2   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x10)

#define PINSEL_PinConfig_0_17_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x11)
#define PINSEL_PinConfig_0_17_CAP1_2   (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x11)
#define PINSEL_PinConfig_0_17_SCK1     (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x11)
#define PINSEL_PinConfig_0_17_MAT1_2   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x11)

#define PINSEL_PinConfig_0_18_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x12)
#define PINSEL_PinConfig_0_18_CAP1_3   (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x12)
#define PINSEL_PinConfig_0_18_MISO1    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x12)
#define PINSEL_PinConfig_0_18_MAT1_3   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x12)

#define PINSEL_PinConfig_0_19_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x13)
#define PINSEL_PinConfig_0_19_MAT1_2   (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x13)
#define PINSEL_PinConfig_0_19_MOSI1    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x13)
#define PINSEL_PinConfig_0_19_CAP1_2   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x13)

#define PINSEL_PinConfig_0_20_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x14)
#define PINSEL_PinConfig_0_20_MAT1_3   (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x14)
#define PINSEL_PinConfig_0_20_SSEL1    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x14)
#define PINSEL_PinConfig_0_20_EINT3    (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x14)

#define PINSEL_PinConfig_0_21_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x15)
#define PINSEL_PinConfig_0_21_PWM5     (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x15)
#define PINSEL_PinConfig_0_21_AD1_6    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x15)
#define PINSEL_PinConfig_0_21_CAP1_3   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x15)

#define PINSEL_PinConfig_0_22_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x16)
#define PINSEL_PinConfig_0_22_AD1_7    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x16)
#define PINSEL_PinConfig_0_22_CAP0_0   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x16)
#define PINSEL_PinConfig_0_22_MAT0_0   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x16)

#define PINSEL_PinConfig_0_23_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x17)

#define PINSEL_PinConfig_0_25_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x19)
#define PINSEL_PinConfig_0_25_AD0_4    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x19)
#define PINSEL_PinConfig_0_25_DAC      (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x19)

#define PINSEL_PinConfig_0_26_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x1a)
#define PINSEL_PinConfig_0_26_AD0_5    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x1a)

#define PINSEL_PinConfig_0_27_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x1b)
#define PINSEL_PinConfig_0_27_AD0_1    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x1b)
#define PINSEL_PinConfig_0_27_CAP0_1   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x1b)
#define PINSEL_PinConfig_0_27_MAT0_1   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x1b)

#define PINSEL_PinConfig_0_28_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x1c)
#define PINSEL_PinConfig_0_28_AD0_1    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x1c)
#define PINSEL_PinConfig_0_28_CAP0_2   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x1c)
#define PINSEL_PinConfig_0_28_MAT0_2   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x1c)

#define PINSEL_PinConfig_0_29_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x1d)
#define PINSEL_PinConfig_0_29_AD0_2    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x1d)
#define PINSEL_PinConfig_0_29_CAP0_3   (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x1d)
#define PINSEL_PinConfig_0_29_MAT0_3   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x1d)

#define PINSEL_PinConfig_0_30_PIO      (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x1e)
#define PINSEL_PinConfig_0_30_AD0_3    (((((uint16_t)PINSEL_Function_Alt1) << 5))    | 0x1e)
#define PINSEL_PinConfig_0_30_EINT3    (((((uint16_t)PINSEL_Function_Alt2) << 5))    | 0x1e)
#define PINSEL_PinConfig_0_30_CAP0_0   (((((uint16_t)PINSEL_Function_Alt3) << 5))    | 0x1e)

#define PINSEL_PinConfig_0_31_PO       (((((uint16_t)PINSEL_Function_Default) << 5)) | 0x1f)

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
};
#endif

#endif /* #ifndef LPC2148_PINCONFIG_H_ */
