/******************************************************************************
 * @file:    LPC2xxx_uart.h
 * @purpose: Header file for LPC2xxx UART
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

#ifndef LPC2XXX_UART_H_
#define LPC2XXX_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_UART
#error  Your CPU does not seem to have an UART, or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup UART
  * @{
  */

/* UART Typedefs -------------------------------------------------------------*/

/** @defgroup UART_ITConfigType
  * @{
  * 
  * These UARTs have this annoying disconnect between enabling interrupts and
  *  interrupt identification...
  */

#define UART_IT_Mask             (0x0307)
#define UART_IT_RxData           (0x0001)
#define UART_IT_TxData           (0x0002)
#define UART_IT_RxLineStatus     (0x0004)
#define UART_IT_AutoBaudEnd      (0x0100)
#define UART_IT_AutoBaudTimeout  (0x0200)

/**
  * @}
  */

/** @defgroup UART_ITIDType
  * @{
  *
  * These UARTs have this annoying disconnect between enabling interrupts and
  *  interrupt identification...
  */
typedef enum {
    UART_ITID_None             = 0x01,
    UART_ITID_ModemStatus      = 0x00,
    UART_ITID_TxEmpty          = 0x02,
    UART_ITID_RxDataAvailable  = 0x04,
    UART_ITID_RxLineStatus     = 0x06,
    UART_ITID_CharacterTimeOut = 0x0c,
} UART_ITID_Type;


/**
  * @}
  */

/** @defgroup UART_Line_Status
  * @{
  */
#define UART_LineStatus_Mask         (0xff)
#define UART_LineStatus_RxData       (1 << 0)
#define UART_LineStatus_RxOverrun    (1 << 1)
#define UART_LineStatus_ParityError  (1 << 2)
#define UART_LineStatus_FramingError (1 << 3)
#define UART_LineStatus_Break        (1 << 4)
#define UART_LineStatus_TxReady      (1 << 5)
#define UART_LineStatus_TxEmpty      (1 << 6)
#define UART_LineStatus_RxFIFO       (1 << 8)

/**
  * @}
  */


/** @defgroup UART_Modem_Status
  * @{
  */
#define UART_ModemStatus_Mask        (0xff)
#define UART_ModemStatus_CTSChange   (1 << 0)
#define UART_ModemStatus_DSRChange   (1 << 1)
#define UART_ModemStatus_RIEdge      (1 << 2)
#define UART_ModemStatus_DCDChange   (1 << 3)
#define UART_ModemStatus_CTSVal      (1 << 4)
#define UART_ModemStatus_DSRVal      (1 << 5)
#define UART_ModemStatus_RIVal       (1 << 6)
#define UART_ModemStatus_DCDVal      (1 << 7)

/**
  * @}
  */  
  
/** @defgroup UART_Word_Length
  * @{
  */
typedef enum {
    UART_WordLength_5b = 0x00,
    UART_WordLength_6b = 0x01,
    UART_WordLength_7b = 0x02,
    UART_WordLength_8b = 0x03
} UART_WordLength_Type;
#define UART_IS_WORDSIZE(WORDSIZE) (((WORDSIZE) >= UART_WordLength_5b) \
                                    && ((WORDSIZE) <= UART_WordLength_8b))

/**
  * @}
  */ 

/** @defgroup UART_Stop_Bits
  * @{
  */
typedef enum {
    UART_StopBits_1 = 0x00,
    UART_StopBits_2 = 0x04
} UART_StopBits_Type;
#define UART_IS_STOPBITS(STOPBITS) (((STOPBITS) == UART_StopBits_1) \
                                 || ((STOPBITS) == UART_StopBits_2))

/**
  * @}
  */ 

/** @defgroup UART_Parity
  * @{
  */
typedef enum {
    UART_Parity_No   = 0x00,
    UART_Parity_Odd  = 0x08,
    UART_Parity_Even = 0x18,
    UART_Parity_One  = 0x28,
    UART_Parity_Zero = 0x38
} UART_Parity_Type;
#define UART_IS_PARITY(PARITY) (((PARITY) == UART_Parity_No) || ((PARITY) == UART_Parity_Odd) \
                             || ((PARITY) == UART_Parity_Even) || ((PARITY) == UART_Parity_One) \
                             || ((PARITY) == UART_Parity_Zero))

/**
  * @}
  */ 

/** @defgroup UART_RxFIFO_Trigger
  * @{
  */
typedef enum {
    UART_RxFifoTrigger_1  = 0x00,
    UART_RxFifoTrigger_4  = 0x40,
    UART_RxFifoTrigger_8  = 0x80,
    UART_RxFifoTrigger_14 = 0xc0,
} UART_RxFifoTrigger_Type;
#define UART_IS_RXFIFOTRIGGER(TRIGGER) (((TRIGGER) == UART_RxFifoTrigger_1) \
                                     || ((TRIGGER) == UART_RxFifoTrigger_4) \
                                     || ((TRIGGER) == UART_RxFifoTrigger_8) \
                                     || ((TRIGGER) == UART_RxFifoTrigger_14))

/**
  * @}
  */ 


/* UART Inline Functions ----------------------------------------------------*/


/** @defgroup UART_Inline_Functions
  * @{
  */

/**
  * @brief  Receive a Byte via the UART
  * @param  Uart    Pointer to the UART instance
  * @return None.
  */
__INLINE static uint8_t UART_Recv(UART_Type *Uart)
{
    return Uart->RBR;
}

/**
  * @brief  Send a Byte via the UART
  * @param  Uart    Pointer to the UART instance
  * @param  b       Byte to Send
  * @return None.
  */
__INLINE static void UART_Send(UART_Type *Uart, uint8_t b)
{
    Uart->THR = b;
}

/**
  * @brief  Enable UART Interrupts
  * @param  Uart    Pointer to the UART instance
  * @param  IT      Interrupts to enable
  * @return None.
  */
__INLINE static void UART_EnableIT(UART_Type *Uart, uint16_t IT)
{
    lpc2xxx_lib_assert((IT & ~UART_IT_Mask) == 0);
    
    Uart->IER |= IT;
}

/**
  * @brief  Disable UART Interrupts
  * @param  Uart    Pointer to the UART instance
  * @param  IT      Interrupts to disable
  * @return None.
  */
__INLINE static void UART_DisableIT(UART_Type *Uart, uint16_t IT)
{
    lpc2xxx_lib_assert((IT & ~UART_IT_Mask) == 0);
    
    Uart->IER &= ~IT;
}

/**
  * @brief  Get Enabled UART Interrupts
  * @param  Uart    Pointer to the UART instance
  * @return Enabled UART Interrupts
  */
__INLINE static uint16_t UART_GetEnabledIT(UART_Type *Uart)
{
    return Uart->IER;
}

/**
  * @brief  Get Pending Interrupt ID's on Uart
  * @param  Uart    Pointer to the UART instance
  * @return 16-bit value indicating pending interrupt ID
  *
  * Bit 0 will be 1 if no interrupts are pending.  Otherwise the following
  *  values correspond to pending interrupts:
  *  UART_ITID_None: No Interrupt Pending
  *  UART_ITID_ModemStatus: Modem Status Lines Changed
  *  UART_ITID_TxEmpty: Transmitter Empty
  *  UART_ITID_RxDataAvailable: Receiver has Data Available
  *  UART_ITID_RxLineStatus: Receiver Error / Other RX Status
  *  UART_ITID_CharacterTimeOut: Rx Character has been waiting some time
  */
__INLINE static uint16_t UART_GetPendingITID(UART_Type *Uart)
{
    return (Uart->IIR & UART_INTID_Mask);
}

/**
  * @brief  Set the word length for bytes sent/received via the UART
  * @param  Uart     Pointer to the UART instance
  * @param  WordLength Token indicating the word length (of UART_WordLength_Type type)
  * @return None.
  */
__INLINE static void UART_SetWordLength(UART_Type *Uart, UART_WordLength_Type WordLength)
{
    lpc2xxx_lib_assert(UART_IS_WORDSIZE(WordLength));
    
    Uart->LCR = (Uart->LCR & ~UART_WORDLEN_Mask) | WordLength;
}

/**
  * @brief  Get the Configured Word Length for Bytes Sent / Received via the UART
  * @param  Uart     Pointer to the UART instance
  * @return Token indicating the word length (of UART_WordLength_Type type)
  */
__INLINE static UART_WordLength_Type UART_GetWordLength(UART_Type *Uart)
{
    return (Uart->LCR & UART_WORDLEN_Mask);
}

/**
  * @brief  Set the # of Stop Bits for Bytes Sent / Received via the UART
  * @param  Uart     Pointer to the UART instance
  * @param  StopBits Token indicating the number of stop bits (of UART_StopBits_Type type)
  * @return None.
  */
__INLINE static void UART_SetStopBits(UART_Type *Uart, UART_StopBits_Type StopBits)
{
    lpc2xxx_lib_assert(UART_IS_STOPBITS(StopBits));
    
    Uart->LCR = (Uart->LCR & ~UART_2STOPBITS) | StopBits;
}

/**
  * @brief  Get the Configured # of Stop Bits for Bytes Sent / Received via the UART
  * @param  Uart     Pointer to the UART instance
  * @return Token representing the # of stop bits
  */
__INLINE static UART_StopBits_Type UART_GetStopBits(UART_Type *Uart)
{
    return (Uart->LCR & UART_2STOPBITS);
}

/**
  * @brief  Get the Configured Parity for Bytes Sent / Received via the UART
  * @param  Uart     Pointer to the UART instance
  * @param  Parity   Token indicating type of parity to use (of UART_Parity_Type type)
  * @return None.
  */
__INLINE static void UART_SetParity(UART_Type *Uart, UART_Parity_Type Parity)
{
    lpc2xxx_lib_assert(UART_IS_PARITY(Parity));
    
    Uart->LCR = (Uart->LCR & ~UART_PARITY_Mask) | Parity;
}

/**
  * @brief  Get the Configured Parity for Bytes Sent / Received via the UART
  * @param  Uart     Pointer to the UART instance
  * @return Token indicating the configured parity type
  */
__INLINE static UART_Parity_Type UART_GetParity(UART_Type *Uart)
{
    return (Uart->LCR & UART_PARITY_Mask);
}

/**
  * @brief  Get UART Status Information
  * @param  Uart     Pointer to the UART instance
  * @return UART status (from LSR)
  */
__INLINE static uint8_t UART_GetLineStatus(UART_Type *Uart)
{
    return Uart->LSR;
}

/**
  * @brief  Get the UART's Modem Line Status
  * @param  Uart    Pointer to the UART instance
  * @return Bitmask of the UART modem status bits
  */
__INLINE static uint8_t UART_GetModemStatus(UART_Type *Uart)
{
    return Uart->MSR;
}

/**
  * @brief  Enable the UART's Transmitter
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_EnableTx(UART_Type *Uart)
{
    Uart->TER = UART_TXEN;
}

/**
  * @brief  Disable the UART's Transmitter
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_DisableTx(UART_Type *Uart)
{
    Uart->TER = 0;
}

/**
  * @brief  Determine Whether the UART's Transmitter is Enabled
  * @param  Uart     Pointer to the UART instance
  * @return 1 if the UART's transmitter is enabled, 0 otherwise
  */
__INLINE static uint32_t UART_TxIsEnabled(UART_Type *Uart)
{
    return (Uart->TER & UART_TXEN) ? 1:0;
}

/**
  * @brief  Start sending a BREAK condition on the UART's TX line
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_StartBreak(UART_Type *Uart)
{
    Uart->LCR |= UART_BREAK;
}

/**
  * @brief  Stop Sending a BREAK Condition on the UART's TX Line & Return to Normal Transmission
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_EndBreak(UART_Type *Uart)
{
    Uart->LCR &= ~UART_BREAK;
}

/**
  * @brief  Determine Whether the UART is in Break Transmit Mode
  * @param  Uart     Pointer to the UART instance
  * @return 1 if the UART is in break mode, 0 otherwise
  */
__INLINE static uint32_t UART_IsInBreak(UART_Type *Uart)
{
    return (Uart->LCR & UART_BREAK) ? 1:0;
}

/**
  * @brief  Enable the UART's Loopback Mode
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_EnableLoopback(UART_Type *Uart)
{
    Uart->MCR |= UART_LOOPBACK;
}

/**
  * @brief  Disable the UART's Loopback Mode
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_DisableLoopback(UART_Type *Uart)
{
    Uart->MCR &= ~UART_LOOPBACK;
}

/**
  * @brief Get State of UART Loopback Mode
  * @param  Uart     Pointer to the UART instance
  * @param  None.
  * @return 1 if in loopback mode, 0 otherwise
  */
__INLINE static uint8_t UART_LoopbackIsEnabled(UART_Type *Uart)
{
    return (Uart->MCR & UART_LOOPBACK) ? 1:0;
}

/**
  * @brief Set State of UART DTR Line
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_SetDTR(UART_Type *Uart, uint8_t Value)
{
    if (Value) {
        Uart->MCR |= UART_DTR;
    } else {
        Uart->MCR &= UART_DTR;
    }
}

/**
  * @brief Get Current State of UART DTR Line
  * @param  Uart     Pointer to the UART instance
  * @return 1 if in DTR is set, 0 otherwise
  */
__INLINE static uint8_t UART_GetDTR(UART_Type *Uart)
{
    return (Uart->MCR & UART_DTR) ? 1:0;
}

/**
  * @brief Set State of UART RTS Line
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_SetRTS(UART_Type *Uart, uint8_t Value)
{
    if (Value) {
        Uart->MCR |= UART_RTS;
    } else {
        Uart->MCR &= UART_RTS;
    }
}

/**
  * @brief Get Current State of UART RTS Line
  * @param  Uart     Pointer to the UART instance
  * @return 1 if in RTS is set, 0 Otherwise
  */
__INLINE static uint8_t UART_GetRTS(UART_Type *Uart)
{
    return (Uart->MCR & UART_RTS) ? 1:0;
}

/**
  * @brief  Enable the UART's Auto RTS Flow Control
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_AutoRTSEnable(UART_Type *Uart)
{
    Uart->MCR |= UART_RTSENA;
}

/**
  * @brief  Disable the UART's Auto RTS Flow Control
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_AutoRTSDisable(UART_Type *Uart)
{
    Uart->MCR &= ~UART_RTSENA;
}

/**
  * @brief Get State of UART Auto RTS Mode
  * @param  Uart     Pointer to the UART instance
  * @return 1 if Auto RTS mode is enabled, 0 otherwise
  */
__INLINE static uint8_t UART_AutoRTSIsEnabled(UART_Type *Uart)
{
    return (Uart->MCR & UART_RTSENA) ? 1:0;
}

/**
  * @brief  Enable the UART's Auto CTS Flow Control
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_AutoCTSEnable(UART_Type *Uart)
{
    Uart->MCR |= UART_CTSENA;
}

/**
  * @brief  Disable the UART's Auto CTS Flow Control
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_AutoCTSDisable(UART_Type *Uart)
{
    Uart->MCR &= ~UART_CTSENA;
}

/**
  * @brief Get State of UART Auto CTS Mode
  * @param  Uart     Pointer to the UART instance
  * @return 1 if Auto CTS mode is enabled, 0 otherwise
  */
__INLINE static uint8_t UART_AutoCTSIsEnabled(UART_Type *Uart)
{
    return (Uart->MCR & UART_CTSENA) ? 1:0;
}

/**
  * @brief  Set the Number of Bytes in the UART's Rx FIFO that will Trigger an Interrupt
  * @param  Uart     Pointer to the UART instance
  * @param  Trigger  Token indicating number of bytes in the FIFO that will trigger an interrupt
  * @return None.
  */
__INLINE static void UART_SetRxFifoTrigger(UART_Type *Uart, UART_RxFifoTrigger_Type Trigger)
{
    lpc2xxx_lib_assert(UART_IS_RXFIFOTRIGGER(Trigger));
    
    Uart->FCR = Trigger | UART_FIFOEN;
}

/**
  * @brief  Flush the UART's Receive FIFO
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_FlushRxFifo(UART_Type *Uart)
{
    Uart->FCR = (Uart->IIR & UART_FIFO_Mask) 
                 | UART_FIFOEN | UART_FIFO_RX_RESET;
}

/**
  * @brief  Flush the UART's Transmit FIFO
  * @param  Uart     Pointer to the UART instance
  * @return None.
  */
__INLINE static void UART_FlushTxFifo(UART_Type *Uart)
{
    Uart->FCR = (Uart->IIR & UART_FIFO_Mask) 
                 | UART_FIFOEN | UART_FIFO_TX_RESET;
}

/**
  * @brief  Enable the UART's FIFOs
  * @param  Uart     Pointer to the UART instance
  * @return None.
  *
  * According to the datasheet, the FIFOs should never be disabled for proper operation.
  * This will clear the RX Trigger, setting it back to 1 character.
  */
__INLINE static void UART_EnableFifos(UART_Type *Uart)
{
    Uart->FCR = UART_FIFOEN;
}

/**
  * @brief  Disable the UART's FIFOs
  * @param  Uart     Pointer to the UART instance
  * @return None.
  *
  * According to the datasheet, the FIFOs should never be disabled for proper operation.
  * This will clear the RX Trigger, setting it back to 1 character.
  */
__INLINE static void UART_DisableFifos(UART_Type *Uart)
{
    Uart->FCR = 0;
}

/**
  * @brief  Set the UART's Divisor for Bit Timing
  * @param  Uart     Pointer to the UART instance
  * @param  Divisor  The number of prescaled UART clocks per bit (16 bits)
  * @return None.
  */
__INLINE static void UART_SetDivisor(UART_Type *Uart, uint16_t Divisor)
{
    Uart->LCR |= UART_DLAB;
    Uart->DLL = Divisor & 0xff;
    Uart->DLM = Divisor >> 8;
    Uart->LCR &= ~UART_DLAB;
}

/**
  * @brief  Get the Current UART Divisor for Bit Timing
  * @param  Uart     Pointer to the UART instance
  * @return The configured # of prescaled UART clocks per bit
  */
__INLINE static uint16_t UART_GetDivisor(UART_Type *Uart)
{
    uint16_t Divisor;
    
    
    Uart->LCR |= UART_DLAB;
    Divisor = ((Uart->DLM & 0xff) << 8) | (Uart->DLL & 0xff);
    Uart->LCR &= ~UART_DLAB;
    
    return Divisor;
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

#endif /* #ifndef LPC2XXX_UART_H_ */
