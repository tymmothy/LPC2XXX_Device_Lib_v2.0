#include "lpc2xxx.h"
#include "lpc2xxx_ct16b.h"
#include "lpc2xxx_syscon.h"
#include "lpc2xxx_gpio.h"
#include "lpc2xxx_pinsel.h"
#include "lpc2xxx_pinconfig.h"


void uart_putchar(uint8_t x)
{
    UART_Send(UART0, x);
    while (!(UART_GetLineStatus(UART0) & UART_THRE));
}

void uart_putstr(const char *string)
{
    while (*string != '\0') {
        uart_putchar(*string++);
    }
}



void init_gpio()
{
    /* Configure pins for UART IO lines */
    PINSEL_SetPinConfig(PINSEL_PinConfig_0_0_TXD0);
    PINSEL_SetPinConfig(PINSEL_PinConfig_0_1_RXD0);
    
    /* Power on UART block */
    SYSCON_EnablePeriphPowerLines(SYSCON_PeriphPowerLine_UART0);

    /* Configure baud rate */
    UART_SetDivisor(UART0, UART_DIVISOR);
    UART_SetWordLength(UART0, UART_WordLength_8b);
    UART_SetStopBits(UART0, UART_StopBits_2);
    UART_SetParity(UART0, UART_Parity_No);
    UART_EnableFifos(UART0);
    UART_FlushRxFifo(UART0);
    UART_FlushTxFifo(UART0);
    UART_EnableTx(UART0);

}

/*
const char *get_bob();

void cpp_static_construct_test()
{
    const char *x = get_bob();

    uart_putstr("Bob = ");
    uart_putstr(x);
    uart_putstr("\r\n");
}
*/
int main()
{
    PINSEL_SetPinConfig(PINSEL_PinConfig_0_16_PIO);
    
    GPIO_SetPins(GPIO0, 

    / * Disable the timer to eliminate race conditions * /
    CT16B_EnableConfig(CT16B0, Disable);
    
    / * Reset count & prescaler count * /
    CT16B_ResetConfig(CT16B0, Enable);
    CT16B_ResetConfig(CT16B0, Disable);
    
    // CT16B0 source = PCLK / 2 (prescaler = 1)
    CT16B_SetPrescaler(CT16B0, 1);
    CT16B_SetMode(CT16B0, CT16B_Mode_Timer);
    
    CT16B_SetChannelMatchValue(CT16B0, 0, LED_SCAN_TIMER_TRIGGER1);   
    CT16B_SetChannelMatchValue(CT16B0, 1, LED_SCAN_TIMER_TRIGGER2);
    
    CT16B_SetChannelMatchControl(CT16B0, 0, CT16B_MatchControl_Interrupt);
    CT16B_SetChannelMatchControl(CT16B0, 1, CT16B_MatchControl_Interrupt | CT16B_MatchControl_Reset);

    CT16B_EnableConfig(CT16B0, Enable);
*/    

    while(1);

    return 0;
}

