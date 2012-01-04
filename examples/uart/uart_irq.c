/*****************************************************************************
 * @file:    uart_irq.c
 * @purpose: Example code for using a UART w/IRQs
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

#include "system_LPC2xxx.h"
#include "LPC2xxx_pinconfig.h"
#include "LPC2xxx_uart.h"

unsigned char rxbuf[16];
unsigned char rxbuf_start;
unsigned char rxbuf_end;

unsigned char txbuf[16];
unsigned char txbuf_start;
unsigned char txbuf_end;


void UART1_IRQHandler(void) __attribute__((__IRQ__));
void UART1_IRQHandler(void)
{
    while ((itid = UART_GetPendingITID(UART0)) != UART_ITID_None) {
        if (itid == UART_ITID_RxLineStatus) {
            tmp = UART_GetLineStatus(UART);
            if (tmp & UART_BI) { /* BREAK */
            } else if (tmp & (UART_OE | UART_PE | UART_FE)) {
                /* Overflow / Parity / Framing Error */
            }
            
            UART_Recv(UART0);
            continue;
        } else if ((itid == UART_ITID_RxDataAvailable) 
                || (itid == UART_ITID_CharacterTimeout))
        {
            tmp = UART_Recv(UART);
        } else if (itid == UART_ITID_TxEmpty) {
        } else if (itid == UART_ITID_ModemStatus) {
        } else {
            /* UART_ITID_CharacterTimeOut */
        }
        
        
    }
}

int init_uart(UART_Type *uart, IRQn_Type uart_irq_num, uint32_t baud)
{
    uint32_t uart_divisor;
    uint32_t apb_clock;
    
    
    /* Determine the UART divisor for the given baud rate. */
    apb_clock = SystemCoreClock / SYSCON_GetAPBClockDivider();
    uart_divisor = ((apb_clock / 16) + (baud / 2)) / baud;

    /* Configure baud rate & other settings */
    UART_SetDivisor(uart, uart_divisor);
    UART_SetWordLength(uart, UART_WordLength_8b);
    UART_SetStopBits(uart, UART_StopBits_1);
    UART_SetParity(uart, UART_Parity_No);

    /* Enable UART FIFOs (necessary) */
    UART_EnableFifos(uart);

    /* Flush out the FIFOs */
    UART_FlushRxFifo(uart);
    UART_FlushTxFifo(uart);
    
    /* Set the UART Rx to interrupt on every incoming byte */
    UART_SetRxFifoTrigger(uart, UART_RxFifoTrigger_1);

    /* Enable Tx */
    UART_EnableTx(uart);
}

int main()
{
    /* Disable the IRQ for the UART */
    VIC_DisableIRQ(UART0_IRQn);
    
    /* Set up the pin configuration for the UART TXD/RXD pins */
#if defined(lpc2103) || defined(lpc2102) || defined(lpc2101) 
    PINSEL_SetPinConfig(PINSEL_PinConfig_0_1_RXD0);
    PINSEL_SetPinConfig(PINSEL_PinConfig_0_0_TXD0);
#endif

    /* Enable power to the UART */
    SYSCON_EnablePeriphPowerLines(SYSCON_PeriphPowerLine_UART0);

    init_uart(UART0, 115200);
    
    /* Set up VIC slot 0 to handle the UART */
    VIC_SetSlot(0, UART0_IRQn, UART0_Handler);
    VIC_EnableSlot(0);
    
    /* Enable interrupts for the UART in the VIC */
    VIC_EnableIRQ(UART0_IRQn);

    /* Start the UART interrupts going... */
    UART_GetPendingITID(UART0);
}
