/******************************************************************************
 * @file:    uart_noirq.c
 * @purpose: Example / test program for LPC2xxx UART interface
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    3. Januart 2012
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

 
/* Includes -----------------------------------------------------------------*/

#include <stdint.h>

#include "LPC2xxx.h"
#include "LPC2xxx_uart.h"       /* For UART interface           */
#include "LPC2xxx_syscon.h"     /* For peripheral power control */
#include "LPC2xxx_pinsel.h"     /* For IO pin configuration     */
#include "LPC2xxx_pinconfig.h"  /* For IO pin configuration     */
#include "system_LPC2xxx.h"     /* For SystemCoreClock          */


/* Default to using UART0 */
#ifndef UART
# define UART UART0
#endif


/* Functions ----------------------------------------------------------------*/

/** @brief  Determine whether the given UART has a character in the rcv buffer
  *
  * @param  [in]  uart     The UART to check
  *
  * @return 1 if the UART has at least 1 character available, 0 otherwise.
  */
int uart_available(UART_Type *uart)
{
    return (UART_GetLineStatus(uart) & UART_LineStatus_RxData) ? 1:0;
}


/** @brief  Send a character via UART
  *
  * @param  [in]  uart     The UART on which to send the character
  * @param  [in]  c        The character to send
  *
  * @return None.
  *
  * Blocks until the UART is ready to accept the new character, then
  *  writes it.
  */
void uart_putchar(UART_Type *uart, uint8_t c)
{
    /* Wait for tx holding register to empty */
    while ((UART_GetLineStatus(uart) & UART_LineStatus_TxEmpty) == 0);
    
    /* Send character */
    UART_Send(uart, c);
}


/** @brief  Send a string via UART
  *
  * @param  [in]  uart     The UART on which to send the string
  * @param  [in]  string   The string to send
  *
  * @return None.
  *
  * Uses uart_putchar, so this is will block until the entire string
  *  has been sent.
  */
void uart_putstr(UART_Type *uart, const char *string)
{
    while (*string != '\0') {
        uart_putchar(uart, (uint8_t)(*string++));
    }
}


/** @brief  Receive a character via UART
  *
  * @param  [in]  uart     The UART on which to receive the character
  *
  * @return The received character
  *
  * Blocks until the UART has a character available to read.
  */
uint8_t uart_getchar(UART_Type *uart)
{
    uint8_t c;
    
    
    /* Wait for a character to be ready */
    while ((UART_GetLineStatus(uart) & UART_LineStatus_RxData) == 0);
    
    /* Receive it */
    c = UART_Recv(uart);
    
    return c;
}


/** @brief  Initialize a UART for communication.
  *
  * @param  [in]  uart     The UART on which to receive the character
  *
  * @return The received character
  *
  * Blocks until the UART has a character available to read.
  */
void init_uart(UART_Type *uart, uint32_t baud)
{
    uint32_t uart_divisor;
    uint32_t apb_clock;
    
    
    /* Determine the UART divisor for the given baud rate. */
    apb_clock = SystemCoreClock / SYSCON_GetAPBClockDivider();
    uart_divisor = ((apb_clock / 16) + (baud / 2)) / baud;

#if (LPC2XXX_MODEL == 2148) || (LPC2XXX_MODEL == 2138) || (LPC2XXX_MODEL == 2106) \
    || (LPC2XXX_MODEL == 2103)

    /* Configure IO pins & power on the given UART */
    
    if (uart == UART0) {
        /* Configure pins for UART0 use */
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_0_TXD0);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_1_RXD0);

        /* Power on UART0 */
        SYSCON_EnablePeriphPowerLines(SYSCON_PeriphPowerLine_UART0);
    } else if (uart == UART1) {
        /* Configure pins for UART1 use */
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_8_TXD1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_9_RXD1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_10_RTS1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_11_CTS1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_12_DSR1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_13_DTR1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_14_DCD1);
        PINSEL_SetPinConfig(PINSEL_PinConfig_0_15_RI1);

        /* Power on UART1 */
        SYSCON_EnablePeriphPowerLines(SYSCON_PeriphPowerLine_UART1);
    }

#else
#error No current definition set up for the given microcontroller model.
#endif

    /* Configure baud rate & terminal settings (given baud @ 8n2) */
    UART_SetDivisor(uart, uart_divisor);
    UART_SetWordLength(uart, UART_WordLength_8b);
    UART_SetStopBits(uart, UART_StopBits_2);
    UART_SetParity(UART, UART_Parity_No);
    
    /* Enable FIFOs (necessary) and flush them */
    UART_EnableFifos(UART);
    UART_FlushRxFifo(UART);
    UART_FlushTxFifo(UART);
    
    /* Enable transmitting on the UART */
    UART_EnableTx(UART);

    /* Clear the receive buffer register */
    UART_Recv(uart);
}


/** @brief  Main function for UART example / test program.
  *
  * @return None.
  *
  * Sits in a loop waiting for characters on the given UART, then sends
  *  a string telling what it got.
  */
int main()
{
    /* Choose the UART to use for test */
    UART_Type *uart = UART;
    uint8_t c;


    /* Set up uart for 8n2, 38400 baud */
    init_uart(uart, 38400);

    uart_putstr(uart, "Now echoing characters: ");

    /* Loop forever, reporting what is received */
    while(1) {
        if (uart_available(uart)) {
            c = uart_getchar(uart);
            uart_putchar(uart, c);
            
        }
    }
    
    return 0;
}
