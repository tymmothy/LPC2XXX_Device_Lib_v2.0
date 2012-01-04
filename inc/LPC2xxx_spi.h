/******************************************************************************
 * @file:    LPC2xxx_spi.h
 * @purpose: Header File for using LPC2xxx CPU SPI Peripheral
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. November 2010
 * @license: Simplified BSD License
 *
 * Notes:
 * - Remember to make sure PCON is set
 * - SCK, MISO, MOSI, SSEL need to be set up in PINSEL
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
 
#ifndef LPC2XXX_SPI_H_
#define LPC2XXX_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_SPI
#error  Your CPU does not seem to have an (Older style) SPI Interface, or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup SPI Serial Peripheral Interface Interface
  * This file defines types and functions for using the LPC21xx SPI Peripheral
  * @{
  */
  
/* Types --------------------------------------------------------------------*/

/** @addtogroup SPI_Types SPI Interface Typedefs
  * @{
  */

/** @defgroup SPI_WordLength
  * @{
  */

/*! @brief SPI Word Length Types */ 
typedef enum {
   SPI_WordLength_8 = 8,        /*!< Send/Receive 8 bit words   */
   SPI_WordLength_9,            /*!<  Send/Receive 9 bit words  */
   SPI_WordLength_10,           /*!< Send/Receive 10 bit words  */
   SPI_WordLength_11,           /*!<  Send/Receive 11 bit words */
   SPI_WordLength_12,           /*!< Send/Receive 12 bit words  */
   SPI_WordLength_13,           /*!<  Send/Receive 13 bit words */
   SPI_WordLength_14,           /*!< Send/Receive 14 bit words  */
   SPI_WordLength_15,           /*!<  Send/Receive 15 bit words */
   SPI_WordLength_16            /*!< Send/Receive 16 bit words  */
} SPI_WordLength_Type;
#define SPI_IS_WORD_LENGTH(WordLength) (((WordLength) >= SPI_WordLength_8) \
                                   && ((WordLength) <= SPI_WordLength_16))

/**
  * @}
  */

/** @defgroup SPI_ClockPhase
  * @{
  */
  
/*! @brief SPI Clock Phase Types */
typedef enum {
   SPI_ClockPhase_A = 0x00, /*!< Data is latched on first clock transition   */
   SPI_ClockPhase_B = 0x08  /*!< Data is latched on second clock transition  */
} SPI_ClockPhase_Type;
#define SPI_IS_CLOCK_PHASE(Phase) (((Phase) == SPI_ClockPhaseA) \
                                || ((Phase) == SPI_ClockPhaseB))

/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity
  * @{
  */

/*! @brief SPI Inter-frame Clock Polarity Types */
typedef enum {
   SPI_ClockPolarity_Low  = 0x00, /*!< Clock line is low between frames      */
   SPI_ClockPolarity_High = 0x10  /*!< Clock line is high between frames     */
} SPI_ClockPolarity_Type;
#define SPI_IS_CLOCK_POLARITY(Polarity) (((Polarity) == SPI_ClockPolarityLow) \
                                      || ((Polarity) == SPI_ClockPolarityHigh))

/**
  * @}
  */
 
/** @defgroup SPI_Mode
  * @{
  */
 
/*! @brief SPI Communication Modes */
typedef enum {
    SPI_Mode_Slave          = 0x00, /*!<  SPI is wire Slave                  */
    SPI_Mode_Master         = 0x20, /*!< SPI is wire Master                  */
} SPI_Mode_Type;
#define SPI_IS_MODE(Mode) (((Mode) == SPI_ModeMaster) \
                        || ((Mode) == SPI_ModeSlave))

/**
  * @}
  */
 
/** @defgroup SPI_BitOrder
  * @{
  */
 
/*! @brief SPI Bit Ordering */
typedef enum {
    SPI_BitOrder_MSBFirst     = 0x00, /*!< MSB Clocked Out First             */
    SPI_BitOrder_LSBFirst     = 0x40, /*!< LSB Clocked Out First             */
} SPI_BitOrder_Type;
#define SPI_IS_BitOrder(BitOrder) (((BitOrder) == SPI_BitOrder_MSBFirst) \
                                || ((BitOrder) == SPI_BitOrder_LSBFirst))

/**
  * @}
  */

/** @defgroup SPI_Status
  * @{
  */
  
/*! @brief SPI Status Bits */
#define SPI_Status_Abort          (1 << 3)
#define SPI_Status_ModeFault      (1 << 4)
#define SPI_Status_ReadOverrun    (1 << 5)
#define SPI_Status_WriteCollision (1 << 6)
#define SPI_Status_XferComplete   (1 << 7)

/**
  * @}
  */

/**
  * @}
  */


/* Inline Functions ---------------------------------------------------------*/

/** @defgroup SPI_Inline_Functions
  * @{
  */

/** @brief  Send a Word Via the SPI
  * @param  SPI         The SPI Device to Send the Word on
  * @param  Word        The Word to Send
  * @return None.
  */
__INLINE static void SPI_Send(SPI_Type *SPI, uint16_t Word)
{
    SPI->DR = Word;
}

/** @brief  Retrieve a Word from the SPI Peripheral
  * @param  SPI         The SPI Device to Retrieve the Word From
  * @return The Word Read from the SPI
  */
__INLINE static uint16_t SPI_Recv(SPI_Type *SPI)
{
    return SPI->DR;
}

/** @brief Test Whether an SPI Peripheral is Currently Sending / Receiving Data
  * @param  SPI         The SPI Device to Check for Busy State
  * @return 1 if the SPI is Busy, 0 Otherwise
  */
__INLINE static uint8_t SPI_IsBusy(SPI_Type *SPI)
{
    return !(SPI->SR & SPI_SPIF);
}

/** @brief Enable Alternate Word Length Use by SPI Peripheral
  * @param  SPI        The SPI Device
  * @return None.
  *
  * Alternate Word Sizes Should be Configured Using SPI_SetAltWordLength,
  *  then Enabled via this Function.
  */
__INLINE static void SPI_EnableAltWordLength(SPI_Type *SPI)
{
    SPI->CR |= SPI_BITSEN;
}

/** @brief Disable Alternate Word Length Use by SPI Peripheral
  * @param  SPI        The SPI Device
  * @return None.
  *
  * Alternate Word Sizes Should be Configured Using SPI_SetAltWordLength,
  *  then Enabled via this Function.
  */
__INLINE static void SPI_DisableAltWordLength(SPI_Type *SPI)
{
    SPI->CR &= ~SPI_BITSEN;
}

/** @brief Determine whether Alternate Word Lengths are Enabled on an SPI Peripheral
  * @param  SPI         The SPI Device
  * @return  1 if the SPI Device is Configured to use Alternate Word Lengths, else 0.
  */
__INLINE static uint8_t SPI_AltWordLengthIsEnabled(SPI_Type *SPI)
{
    return (SPI->CR & SPI_BITSEN) ? 1:0;
}

/** @brief Set Word Size for IO on SPI
  * @param  SPI         The SPI Device to set Word Size on
  * @param  WordLength  Token Indicating Size of Words to Send/Receive on SPI
  * @return None.
  *
  * WordLength can be one of SPI_WordLength_8 ... SPI_WordLength_16.
  * Use of the Alternate Word Length Must be Specifically Enabled With
  *  SPI_AltWordLengthConfig.
  */
__INLINE static void SPI_SetAltWordLength(SPI_Type *SPI, SPI_WordLength_Type WordLength)
{
    lpc2xxx_lib_assert(SPI_IS_WORD_LENGTH(WordLength));
    SPI->CR = (SPI->CR & ~SPI_BITS_Mask) 
              | ((WordLength << SPI_BITS_Shift) & SPI_BITS_Mask);
}

/** @brief Get the Currently Configured Word Length of an SPI Peripheral
  * @param  SPI  The SPI Device
  * @return The SPI Device's Word Length Setting
  */
__INLINE static SPI_WordLength_Type SPI_GetAltWordLength(SPI_Type *SPI)
{
    return ((SPI->CR & SPI_BITS_Mask) >> SPI_BITS_Shift);
}

/** @brief Set Clock Phase on Which Data is Latched on SPI Peripheral
  * @param  SPI         The SPI Device to set Clock Phase on
  * @param  Polarity    Token Indicating Clock Line Polarity on Idle (A or B)
  * @return None.
  *
  * Polarity may be:
  *  SPI_ClockPolarityA: Data is Latched on First Clock Transition (Away from Idle)
  *  SPI_ClockPolarityB: Data is Latched on Second Clock Transition (Back to Idle)
  */
__INLINE static void SPI_SetClockPhase(SPI_Type *SPI, SPI_ClockPhase_Type Phase)
{
    SPI->CR = (SPI->CR & ~(SPI_CPHA)) | Phase;
}

/** @brief Get the Currently Configured Clock Phase of an SPI Peripheral
  * @param  SPI  The SPI Device
  * @return The SPI Device's Clock Phase Setting
  */
__INLINE static SPI_ClockPhase_Type SPI_GetClockPhase(SPI_Type *SPI)
{
    return (SPI->CR & SPI_CPHA);
}

/** @brief Set the Idle State Polarity of an SPI Peripheral
  * @param  SPI         The SPI Device to Set Clock Polarity on
  * @param  Polarity    Token Indicating Clock Line Polarity on Idle (Low or High)
  * @return None.
  *
  * Polarity may be:
  *  SPI_ClockPolarityLow:   Normal Polarity (1 = high, 0 = low)
  *  SPI_ClockPolarityHigh: Inverted Polarity (1 = low, 0 = high)
  */
__INLINE static void SPI_SetClockPolarity(SPI_Type *SPI, SPI_ClockPolarity_Type Polarity)
{
    SPI->CR = (SPI->CR & ~(SPI_CPOL)) | Polarity;
}

/** @brief Get the Currently Configured Idle State Clock Polarity of an SPI Peripheral
  * @param  SPI  The SPI Device
  * @return The SPI Device's Clock Polarity Setting
  */
__INLINE static SPI_ClockPolarity_Type SPI_GetClockPolarity(SPI_Type *SPI)
{
    return (SPI->CR & SPI_CPOL);
}

/** @brief Set Master or Slave Mode of an SPI Peripheral
  * @param  SPI         The SPI Device to Set the Mode on
  * @param  Mode        Token Indicating Mode to Operate in (of SPI_ModeType type)
  * @return None.
  */
__INLINE static void SPI_SetMode(SPI_Type *SPI, SPI_Mode_Type Mode)
{
    lpc2xxx_lib_assert(SPI_IS_MODE(Mode));
    SPI->CR = (SPI->CR & ~SPI_MSTR) | Mode;
}

/** @brief Get Master/Slave Mode of an SPI Peripheral
  * @param  SPI         The SPI Device
  * @return  The SPI Device's Mode Setting
  */
__INLINE static SPI_Mode_Type SPI_GetMode(SPI_Type *SPI)
{
    return (SPI->CR & SPI_MSTR);
}

/** @brief Set Bit Order that Data is Clocked Out of an SPI Peripheral
  * @param  SPI         The SPI Device to set Bit Ordering on
  * @param  BitOrder    Token Indicating Bit Order to Output Data
  * @return None.
  *
  * Polarity may be:
  *  SPI_BitOrder_MSBFirst: Data is Sent MSB First
  *  SPI_BitOrder_LSBFirst: Data is Sent LSB First
  */
__INLINE static void SPI_SetBitOrder(SPI_Type *SPI, SPI_BitOrder_Type BitOrder)
{
    SPI->CR = (SPI->CR & ~(SPI_LSBF)) | BitOrder;
}

/** @brief Get the Currently Configured Bit Order of an SPI Peripheral
  * @param  SPI  The SPI Device
  * @return The SPI Device's Current Bit Ordering Setting
  */
__INLINE static SPI_BitOrder_Type SPI_GetBitOrder(SPI_Type *SPI)
{
    return (SPI->CR & SPI_LSBF);
}

/* @brief Enable Interrupts on an SPI Peripheral
 * @param  SPI         The SPI Device for which to Enable Interrupts
 */
__INLINE static void SPI_EnableIT(SPI_Type *SPI)
{
    SPI->CR |= SPI_SPIE;
}

/* @brief Disable Interrupts on an SPI Peripheral
 * @param  SPI         The SPI Device for which to Disable Interrupts
 */
__INLINE static void SPI_DisableIT(SPI_Type *SPI)
{
    SPI->CR &= ~SPI_SPIE;
}

/* @brief Determine Whether Interrupt is Enabled on an SPI Peripheral
 * @param None.
 * @return 1 if Interrupts are Enabled on the SPI Device; 0 Otherwise
 */
__INLINE static uint8_t SPI_ITIsEnabled(SPI_Type *SPI)
{
    return (SPI->CR & SPI_SPIE) ? 1:0;
}

/** @brief Determine Whether an Interrupt is Pending on the SPI Peripheral
  * @param  SPI         The SPI Device for which to get Pending Interrupts
  * @return ORed Values of all Pending Interrupts
  */
__INLINE static uint8_t SPI_ITIsPending(SPI_Type *SPI)
{
    return (SPI->INT & SPI_IT) ? 1:0;
}

/** @brief Clear Pending Interrupts on an SPI Peripheral
  * @param  SPI         The SPI Device on which to Clear the Pending Interrupt
  * @return None.
  */
__INLINE static void SPI_ClearPendingIT(SPI_Type *SPI)
{    
    SPI->INT |= SPI_IT;
}

/** @brief  Get the Current Status Bits for an SPI Peripheral
  * @param  SPI          The SPI Device
  * @return SPI Status Bits for the Device
  */
__INLINE static uint8_t SPI_GetStatus(SPI_Type *SPI)
{
    return SPI->SR;
}

/** @brief  Send & Receive a Word via the as Single op
  * @param  SPI         The SPI Device to Send the Word on
  * @param  Word        The Word to Send
  * @return The word read from the SPI Device
  */
__INLINE static uint16_t SPI_Xfer(SPI_Type *SPI, uint16_t WordOut)
{
    while (SPI_IsBusy(SPI));
    SPI->DR = WordOut;
    while (SPI_IsBusy(SPI));
    return SPI->DR;
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

#endif /* #ifndef LPC2XXX_SPI_H_ */
