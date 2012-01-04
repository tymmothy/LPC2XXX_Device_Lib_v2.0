/*****************************************************************************
 * @file:    LPC2xxx_ssp.h
 * @purpose: LPC2xxx SSP Serial Interface Header File
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. June 2010
 * @license: Simplified BSD License
 *
 * NOTE: Pin Modes need to be configured in the IOCON block separately.
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

#ifndef LPC2XXX_SSP_H_
#define LPC2XXX_SSP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_SSP
#error  Your CPU does not seem to have an SSP Peripheral, or a CPU header file is missing/incorrect.
#endif


/** @addtogroup SSP
  * @{
  */

/* Typedefs -----------------------------------------------------------------*/

/** @addtogroup SSP_Types
  * @{
  */

/** @defgroup SSP_Word_Lengths
  * @{
  */

/*! @brief SSP Word Length Types */
typedef enum {
   SSP_WordLength_4 = 4,        /*!< Send/Receive 4 bit words   */
   SSP_WordLength_5,            /*!<  Send/Receive 5 bit words  */
   SSP_WordLength_6,            /*!< Send/Receive 6 bit words   */
   SSP_WordLength_7,            /*!<  Send/Receive 7 bit words  */
   SSP_WordLength_8,            /*!< Send/Receive 8 bit words   */
   SSP_WordLength_9,            /*!<  Send/Receive 9 bit words  */
   SSP_WordLength_10,           /*!< Send/Receive 10 bit words  */
   SSP_WordLength_11,           /*!<  Send/Receive 11 bit words */
   SSP_WordLength_12,           /*!< Send/Receive 12 bit words  */
   SSP_WordLength_13,           /*!<  Send/Receive 13 bit words */
   SSP_WordLength_14,           /*!< Send/Receive 14 bit words  */
   SSP_WordLength_15,           /*!<  Send/Receive 15 bit words */
   SSP_WordLength_16            /*!< Send/Receive 16 bit words  */
} SSP_WordLength_Type;
#define SSP_IS_WORD_LENGTH(WordLength) (((WordLength) >= SSP_WordLength_4) \
                                   && ((WordLength) <= SSP_WordLength_16))
/**
  * @}
  */

/** @defgroup SSP_Frame_Formats
  * @{
  */

/*! @brief SSP Frame Format Types */
typedef enum {
   SSP_FrameFormat_SPI = 0x00,   /*!< Data is formatted as SPI Frames       */
   SSP_FrameFormat_TI = 0x10,    /*!<  Data is formatted as TI Frames       */
   SSP_FrameFormat_MW = 0x20     /*!< Data is formatted as Microwire Frames */
} SSP_FrameFormat_Type;
#define SSP_IS_FRAME_FORMAT(FrameFormat) (((FrameFormat) == SSP_FrameFormatSPI)\
                                       || ((FrameFormat) == SSP_FrameFormatTI) \
                                       || ((FrameFormat) == SSP_FrameFormatMW))

/**
  * @}
  */

/** @defgroup SSP_Clock_Polarities
  * @{
  */

/*! @brief SSP Inter-frame Clock Polarity Types */
typedef enum {
   SSP_ClockPolarity_Low  = 0x00, /*!< Clock line is low between frames  */
   SSP_ClockPolarity_High = 0x40  /*!< Clock line is high between frames */
} SSP_ClockPolarity_Type;
#define SSP_IS_CLOCK_POLARITY(Polarity) (((Polarity) == SSP_ClockPolarityLow) \
                                      || ((Polarity) == SSP_ClockPolarityHigh))

/**
  * @}
  */

/** @defgroup SSP_Clock_Phases
  * @{
  */

/*! @brief SSP Clock Phase Types */
typedef enum {
   SSP_ClockPhase_A = 0x00, /*!< Data is latched on first clock transition  */
   SSP_ClockPhase_B = 0x80  /*!< Data is latched on second clock transition */
} SSP_ClockPhase_Type;
#define SSP_IS_CLOCK_PHASE(Phase) (((Phase) == SSP_ClockPhaseA) \
                                || ((Phase) == SSP_ClockPhaseB))

/**
  * @}
  */

/** @defgroup SSP_Modes
  * @{
  */

/*! @brief SSP Communication Modes */
typedef enum {
    SSP_Mode_Master         = 0x00, /*!< SSP is wire Master                 */
    SSP_Mode_Slave          = 0x04, /*!<  SSP is wire Slave                 */
    SSP_Mode_SlaveInputOnly = 0x0c  /*!< SSP is wire Slave, output disabled */
} SSP_Mode_Type;
#define SSP_IS_MODE(Mode) (((Mode) == SSP_ModeMaster) \
                        || ((Mode) == SSP_ModeSlave)  \
                        || ((Mode) == SSP_ModeSlaveInputOnly))

/**
  * @}
  */

/** @defgroup SSP_ClockRate
  * @{
  */

/*! @brief Number of prescaler-output clocks (minus 1) per bit on SSP bus */
typedef uint8_t SSP_ClockRate_Type;
#define SSP_IS_CLOCK_RATE(ClockRate)       (1)

/**
  * @}
  */

/*! @brief Prescaler factor for SPI clocking (even value between 2 & 254) */
typedef uint8_t SSP_ClockPrescaler_Type;
#define SSP_IS_CLOCK_PRESCALER(Prescaler)  (((Prescaler) & 1) == 0)

/**
  * @}
  */

/** @defgroup SSP_ITTypes
  * @{
  */

/*! @brief SSP Interrupts */
typedef enum {
    SSP_IT_RxOverrun           = 0x01, /*!< Receive Overrun Interrupt    */
    SSP_IT_RxTimer             = 0x02, /*!<  Rx FIFO read timeout        */
    SSP_IT_RxHalfFull          = 0x04, /*!< Rx FIFO at least half full   */
    SSP_IT_TxHalfEmpty         = 0x08, /*!<  Tx FIFO at least half empty */
} SSP_IT_Type;
#define SSP_IS_IT(Interrupt) (((Interrupt) == SSP_IT_RxOverrun)   \
                           || ((Interrupt) == SSP_IT_RxTimeout)   \
                           || ((Interrupt) == SSP_IT_RxHalfFull)  \
                           || ((Interrupt) == SSP_IT_TxHalfEmpty))

/**
  * @}
  */

/** @defgroup SSP_Initialization_Parameters
  * @{
  */

typedef struct {
    SSP_Mode_Type            Mode;
    SSP_WordLength_Type      WordLength;
    SSP_FrameFormat_Type     FrameFormat;
    SSP_ClockPolarity_Type   ClockPolarity;
    SSP_ClockPhase_Type      ClockPhase;
    SSP_ClockPrescaler_Type  ClockPrescaler;
    SSP_ClockRate_Type       ClockRate;
} SSP_Init_Type;

/**
  * @}
  */

/* Inline Functions ---------------------------------------------------------*/

/** @defgroup SSP_Inline_Functions
  * @{
  */

/** @brief  Send a Word via the SSP
  * @param  SSP         The SSP device to send the word on
  * @param  Word        The word to send
  * @return None.
  */
__INLINE static void SSP_Send(SSP_Type *SSP, uint16_t Word)
{
    SSP->DR = Word;
}

/** @brief  Retrieve a Word from the SSP's incoming FIFO
  * @param  SSP         The SSP device to retrieve the word from
  * @return The word read from the SSP's FIFO.
  */
__INLINE static uint16_t SSP_Recv(SSP_Type *SSP)
{
    return SSP->DR;
}

/** @brief  Enable Loopback Mode on an SSP Peripheral
  * @param  SSP         The SSP device for which to enable loopback mode
  * @return None.
  */
__INLINE static void SSP_EnableLoopback(SSP_Type *SSP)
{
    SSP->CR1 |= SSP_LBM;
}

/** @brief  Disable Loopback Mode on an SSP Peripheral
  * @param  SSP         The SSP device for which to disable loopback mode
  * @return None.
  */
__INLINE static void SSP_DisableLoopback(SSP_Type *SSP)
{
    SSP->CR1 &= ~SSP_LBM;
}

/** @brief  Determine Whether Loopback Mode is Enabled on the SSP Peripheral
  * @param  SSP         The SSP device for which to check loopback mode
  * @return None.
  */
__INLINE static uint8_t SSP_LoopbackIsEnabled(SSP_Type *SSP)
{
    return (SSP->CR1 & SSP_LBM) ? 1:0;
}

/** @brief  Enable an SSP Peripheral
  * @param  SSP         The SSP device to enable
  * @return None.
  */
__INLINE static void SSP_Enable(SSP_Type *SSP)
{
    SSP->CR1 |= SSP_SSE;
}

/** @brief  Disable an SSP Peripheral
  * @param  SSP         The SSP device to disable
  * @return None.
  */
__INLINE static void SSP_Disable(SSP_Type *SSP)
{
    SSP->CR1 &= ~SSP_SSE;
}

/** @brief  Determine Whether an SSP Peripheral is Enabled
  * @param  SSP         The SSP device to check
  * @return None.
  */
__INLINE static uint8_t SSP_IsEnabled(SSP_Type *SSP)
{
    return (SSP->CR1 & SSP_SSE) ? 1:0;
}

/** @brief Test whether an SSP's Transmit FIFO is Empty
  * @param  SSP         The SSP device to check for an empty FIFO
  * @return 1 if the SSP's transmit FIFO is empty, 0 otherwise
  */
__INLINE static uint8_t SSP_TxFIFOIsEmpty(SSP_Type *SSP)
{
    return (SSP->SR & SSP_TFE);
}

/** @brief Test whether an SSP has Space in the Transmit FIFO
  * @param  SSP         The SSP device to check for space in the transmit FIFO
  * @return 1 if the SSP's transmit FIFO has space available, 0 otherwise
  */
__INLINE static uint8_t SSP_TxIsReady(SSP_Type *SSP)
{
    return (SSP->SR & SSP_TNF);
}

/** @brief Test whether an SSP has Data in the Receive FIFO
  * @param  SSP         The SSP device to test for data in the receive FIFO
  * @return 1 if the SSP's receive FIFO has data available, 0 otherwise
  */
__INLINE static uint8_t SSP_RxIsAvailable(SSP_Type *SSP)
{
    return (SSP->SR & SSP_RNE);
}

/** @brief Test whether an SSP's Receive FIFO is Full
  * @param  SSP         The SSP device for which to test whether the receive FIFO is full
  * @return 1 if the SSP's receive FIFO is full, 0 otherwise
  */
__INLINE static uint8_t SSP_RxFIFOIsFull(SSP_Type *SSP)
{
    return (SSP->SR & SSP_RFF);
}

/** @brief Test whether an SSP is Currently Transferring Data
  * @param  SSP         The SSP device to check for busy state
  * @return 1 if the SSP is busy, 0 otherwise
  */
__INLINE static uint8_t SSP_IsBusy(SSP_Type *SSP)
{
    return (SSP->SR & SSP_BSY);
}

/* @brief Enable Specific Interrupts on an SSP Peripheral
 * @param  SSP         The SSP device for which to enable interrupts
 * @param  IT          ORed SSP interrupts to enable
 */
__INLINE static void SSP_EnableIT(SSP_Type *SSP, SSP_IT_Type IT)
{
    lpc2xxx_lib_assert(SSP_IS_IT(IT));

    SSP->IMSC |= IT;
}

/* @brief Disable Specific Interrupts on an SSP Peripheral
 * @param  SSP         The SSP device for which to disable interrupts
 * @param  IT          ORed SSP interrupts to disable
 */
__INLINE static void SSP_DisableIT(SSP_Type *SSP, SSP_IT_Type IT)
{
    lpc2xxx_lib_assert(SSP_IS_IT(IT));

    SSP->IMSC &= ~IT;
}

/* @brief Get Enabled Interrupts for an SSP Peripheral
 * @param  SSP         The SSP device to check for enabled interrupts
 * @param  IT          ORed SSP interrupts to disable
 */
__INLINE static SSP_IT_Type SSP_GetEnabledIT(SSP_Type *SSP)
{
    return SSP->IMSC;
}

/** @brief Get the Interrupts Currently Pending on an SSP Peripheral
  * @param  SSP         The SSP device for which to get pending interrupts
  * @return ORed values of all pending interrupts
  */
__INLINE static uint8_t SSP_GetPendingIT(SSP_Type *SSP)
{
    return SSP->MIS;
}

/** @brief Clear Pending Receiver Overrun or Receiver Timer Interrupts on an SSP Peripheral
  * @param  SSP         The SSP device on which to clear the pending interrupt(s)
  * @param  IT          Interrupt types for which to clear pending status
  */
__INLINE static void SSP_ClearPendingIT(SSP_Type *SSP, SSP_IT_Type IT)
{
    lpc2xxx_lib_assert((IT == SSP_IT_RxOverrun) || (IT == SSP_IT_RxTimer));

    SSP->ICR |= IT;
}

/** @brief Set Master/Slave Modes on SSP
  * @param  SSP         The SSP device to set the mode on
  * @param  Mode        Token indicating mode to operate in (of SSP_ModeType type)
  * @return None.
  *
  * Mode may be:
  *  SSP_ModeMaster
  *  SSP_ModeSlave
  *  SSP_ModeSlaveInputOnly
  */
__INLINE static void SSP_SetMode(SSP_Type *SSP, SSP_Mode_Type Mode)
{
    lpc2xxx_lib_assert(SSP_IS_MODE(Mode));

    SSP->CR1 = (SSP->CR1 & ~SSP_CR1_MODE_Mask) | Mode;
}

/** @brief Set Word Size for IO on SSP
  * @param  SSP         The SSP device to set word size on
  * @param  WordLength  Token indicating size of words to send/receive on SSP
  * @return None.
  *
  * WordLength can be one of SSP_WordLength_4 ... SSP_WordLength_16.
  */
__INLINE static void SSP_SetWordSize(SSP_Type *SSP, SSP_WordLength_Type WordLength)
{
    lpc2xxx_lib_assert(SSP_IS_WORD_LENGTH(WordLength));

    SSP->CR0 = (SSP->CR0 & ~(SSP_DSS_Mask)) | (WordLength - 1);
}

/** @brief Set Frame Format for IO on SSP
  * @param  FrameFormat    Token indicating frame format for SSP to use
  * @return None.
  *
  * FrameFormat may be:
  *  FrameFormat_SPI: SPI frames
  *  FrameFormat_TI:  TI frames
  *  FrameFormat_MW:  MicroWire Frames
  */
__INLINE static void SSP_SetFrameFormat(SSP_Type *SSP, SSP_FrameFormat_Type FrameFormat)
{
    SSP->CR0 = (SSP->CR0 & ~(SSP_FRF_Mask)) | FrameFormat;
}

/** @brief Set the Idle State Clock Line Polarity on SSP
  * @param  SSP         The SSP device to set clock polarity on
  * @param  Polarity    Token indicating clock line polarity on idle (low or high)
  * @return None.
  *
  * Polarity may be:
  *  SSP_ClockPolarityLow:   Normal Polarity (1 = high, 0 = low)
  *  SSP_ClockPolarityHigh: Inverted Polarity (1 = low, 0 = high)
  */
__INLINE static void SSP_SetClockPolarity(SSP_Type *SSP, SSP_ClockPolarity_Type Polarity)
{
    SSP->CR0 = (SSP->CR0 & ~(SSP_CPOL)) | Polarity;
}

/** @brief Set the Clock Phase on which Eata is Latched on SSP
  * @param  SSP         The SSP device to set clock phase on
  * @param  Polarity    Token indicating clock line polarity on idle (A or B)
  * @return None.
  *
  * Polarity may be:
  *  SSP_ClockPolarityA: Data is latched on first clock transition (away from idle)
  *  SSP_ClockPolarityB: Data is latched on second clock transition (back to idle)
  */
__INLINE static void SSP_SetClockPhase(SSP_Type *SSP, SSP_ClockPhase_Type Phase)
{
    SSP->CR0 = (SSP->CR0 & ~(SSP_CPHA)) | Phase;
}

/** @brief Set # of Prescaler Counts per Bit for an SSP, Minus 1 (0 means 1 clock)
  * @param  SSP         The SSP device to set clock rate on
  * @param  Clocks      # of clocks between 0 & 255.  Bit freq = PCLK / (CPSDVSR * (SCR + 1))
  * @return None.
  */
__INLINE static void SSP_SetClockRate(SSP_Type *SSP, uint8_t Clocks)
{
    SSP->CR0 = (SSP->CR0 & ~(SSP_SCR_Mask)) | (Clocks << SSP_SCR_Shift);
}

/** @brief Set # of PCLK Counts per SSP Prescaler Count for an SSP
  * @param  SSP         The SSP device to set clock phase on
  * @param  Prescaler   Even prescaler count between 2 & 254
  * @return None.
  */
__INLINE static void SSP_SetClockPrescaler(SSP_Type *SSP, SSP_ClockPrescaler_Type Prescaler)
{
    lpc2xxx_lib_assert(SSP_IS_CLOCK_PRESCALER(Prescaler));

    SSP->CPSR = Prescaler;
}

/** @brief  Send & Receive a Word via the SSP's Outgoing FIFO
  * @param  SSP         The SSP device to send the word on
  * @param  Word        The word to send
  * @return The word read from the SSP's FIFO.
  */
__INLINE static uint16_t SSP_Xfer(SSP_Type *SSP, uint16_t WordOut)
{
    while (SSP_IsBusy(SSP));
    while (SSP_RxIsAvailable(SSP)) {
        SSP_Recv(SSP);
    }

    SSP->DR = WordOut;

    while (!SSP_RxIsAvailable(SSP));
    return SSP->DR;
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

#endif /* #ifndef LPC2XXX_SSP_H_ */
