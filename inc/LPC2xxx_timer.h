/*****************************************************************************
 * @file:    LPC2xxx_timer.h
 * @purpose: LPC2xxx 32 Bit Counter/Timer Interface Header File
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

#ifndef LPC2XXX_TIMER_H_
#define LPC2XXX_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_TIMER
#error  Your CPU does not seem to have an (Old-Style, 32-Bit) Timer, or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup TIMER
  * @{
  */

/* Typedefs -----------------------------------------------------------------*/

/** @addtogroup TIMER_Types
  * @{
  */
  
/** @defgroup TIMER_Interrupt_Types
  * @{
  *
  * TIMER Interrupt Sources (match registers, capture) 
  */
#define TIMER_IT_Mask                       (0xff)

#define TIMER_IT_None                       (0x00)
#define TIMER_IT_MR0                        (1 << 0)
#define TIMER_IT_MR1                        (1 << 1)
#define TIMER_IT_MR2                        (1 << 2)
#define TIMER_IT_MR3                        (1 << 3)
#define TIMER_IT_CR0                        (1 << 4)
#define TIMER_IT_CR1                        (1 << 5)
#define TIMER_IT_CR2                        (1 << 6)
#define TIMER_IT_CR3                        (1 << 7)

/**
  * @}
  */

/** @defgroup TIMER_Match_Control_Types
  * @{
  *
  * TIMER Actions to take on a match
  */
#define TIMER_MatchControl_Mask             (0x07)

#define TIMER_MatchControl_None             (0x00)
#define TIMER_MatchControl_Interrupt        (1 << 0)
#define TIMER_MatchControl_Reset            (1 << 1)
#define TIMER_MatchControl_Stop             (1 << 2)

/**
  * @}
  */
  
/** @defgroup TIMER_Capture_Control_Types
  * @{
  * 
  * TIMER External Capture Controls (for CAP Pins)
  */
#define TIMER_CaptureControl_Mask           (0x07)
#define TIMER_CaptureControl_None           (0x00)
#define TIMER_CaptureControl_RisingEdges    (1 << 0)
#define TIMER_CaptureControl_FallingEdges   (1 << 1)
#define TIMER_CaptureControl_Interrupt      (1 << 2)

#define TIMER_CaptureControl_BothEdges    (TIMER_CaptureControl_RisingEdges | \
                                           TIMER_CaptureControl_FallingEdges)

/**
  * @}
  */
  
/** @defgroup TIMER_Ext_Match_Control_Types
  * @{
  *
  * External Match Output Controls
  */
typedef enum {
    TIMER_ExtMatchControl_None                = 0x00,
    TIMER_ExtMatchControl_Clear,
    TIMER_ExtMatchControl_Set,
    TIMER_ExtMatchControl_Toggle,
} TIMER_ExtMatchControl_Type;
#define TIMER_IS_EXT_MATCH_CONTROL(Control) (((Control) == TIMER_ExtMatchControl_None)  \
                                          || ((Control) == TIMER_ExtMatchControl_Clear) \
                                          || ((Control) == TIMER_ExtMatchControl_Set)   \
                                          || ((Control) == TIMER_ExtMatchControl_Toggle))

/**
  * @}
  */
  
/** @defgroup TIMER_Mode_Types
  * @{
  *
  * TIMER Counter / Timer Mode Configuration Controls
  */
typedef enum {
    TIMER_Mode_Timer                   = 0x00,
    TIMER_Mode_CountRisingEdges,
    TIMER_Mode_CountFallingEdges,
    TIMER_Mode_CountAllEdges,
} TIMER_Mode_Type;
#define TIMER_IS_MODE(Mode)  (((Mode) == TIMER_Mode_Timer)             \
                           || ((Mode) == TIMER_Mode_CountRisingEdges)  \
                           || ((Mode) == TIMER_Mode_CountFallingEdges) \
                           || ((Mode) == TIMER_Mode_CountAllEdges))

#define TIMER_Mode_Mask                (0x03)

/**
  * @}
  */
  
/**
  * @}
  */

/* Inline Functions ---------------------------------------------------------*/

/** @defgroup CT32_INLINE_Functions
  * @{
  */
  
/** @brief  Enable a Timer
  * @param  Timer      The Timer to Enable
  * @return None.
  */
__INLINE static void TIMER_Enable(TIMER_Type *Timer)
{
    Timer->TCR |= TIMER_CE;
}

/** @brief  Disable a Timer
  * @param  Timer      The Timer to Disable
  * @return None.
  */
__INLINE static void TIMER_Disable(TIMER_Type *Timer)
{
    Timer->TCR &= ~TIMER_CE;
}

/** @brief  Determine Whether a Timer Is Enabled
  * @param  Timer     The Timer
  * @return 1 if the TImer is Enabled, 0 Otherwise
  */
__INLINE static uint8_t TIMER_IsEnabled(TIMER_Type *Timer)
{
    return (Timer->TCR & TIMER_CE) ? 1:0;
}

/** @brief  Set the Operation Mode for a Timer
  * @param  Timer     The Timer
  * @param  Mode      The Timer's Mode Configuration
  * @return None.
  *
  * Mode can be one of:
  * - TIMER_Mode_Timer             -- Timer mode
  * - TIMER_Mode_CountRisingEdges  -- Counter mode, Count Rising Edges on CAP Input
  * - TIMER_Mode_CountFallingEdges -- Counter mode, Count Falling Edges on CAP Input
  * - TIMER_Mode_CountAllEdges     -- Counter mode, Count All Edges on CAP Input
  */
__INLINE static void TIMER_SetMode(TIMER_Type *Timer, TIMER_Mode_Type Mode)
{
    lpc2xxx_lib_assert(TIMER_IS_MODE(Mode));
    
    Timer->CTCR = Mode;
}

/** @brief  Get the Currently Configured Mode for a Timer
  * @param  Timer     The Timer
  * @return The Currently Active Mode for the Timer
  */
__INLINE static TIMER_Mode_Type TIMER_GetMode(TIMER_Type *Timer)
{
    return Timer->CTCR;
}

/** @brief  Reset a Timer (stays reset until cleared)
  * @param  Timer      The Timer
  * @return None.
  */
__INLINE static void TIMER_AssertReset(TIMER_Type *Timer)
{
    Timer->TCR |= TIMER_CR;
}

/** @brief  Clear a Timer's RESET State
  * @param  Timer      The Timer
  * @return None.
  */
__INLINE static void TIMER_DeassertReset(TIMER_Type *Timer)
{
    Timer->TCR &= ~TIMER_CR;
}

/** @brief Determine Whether a Timer is Being Held in Reset
  * @param  None.
  * @return 1 if the Reset Line is Set, 0 Otherwise.
  */
__INLINE static uint8_t TIMER_ResetIsAsserted(TIMER_Type *Timer)
{
    return (Timer->TCR & TIMER_CR) ? 1:0;
}

/** @brief  Get the Pending Interrupts for a Timer
  * @param  Timer
  * @return Bit mask of Pending Interrupts
  */
__INLINE static uint8_t TIMER_GetPendingIT(TIMER_Type *Timer)
{
    return Timer->IR;
}

/** @brief  Clear Pending Interrupts on a Timer
  * @param  Timer      The Timer
  * @param  Interrupts Bits Specifying which Interrupts to clear
  * @return None.
  */
__INLINE static void TIMER_ClearPendingIT(TIMER_Type *Timer, uint8_t Interrupts)
{
    lpc2xxx_lib_assert((Interrupts & ~TIMER_IT_Mask) == 0);
    Timer->IR = Interrupts;
}

/** @brief  Set the Count Value of a Timer
  * @param  Timer      The Timer
  * @param  Count      The New Count Value
  * @return None.
  */
__INLINE static void TIMER_SetCount(TIMER_Type *Timer, uint32_t Count)
{
    Timer->TC = Count;
}

/** @brief  Get the Current Count Value of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Count
  */
__INLINE static uint32_t TIMER_GetCount(TIMER_Type *Timer)
{
    return Timer->TC;
}

/** @brief  Set the Prescaler of a Timer
  * @param  Timer      The Timer
  * @param  Prescaler  The New Prescaler
  * @return None.
  *
  * Prescaler of a Timer is the # of input clocks or counts before
  *  the timer increments.  Changing this changes the number of
  *  counts before each increment of the timer/counter.
  */
__INLINE static void TIMER_SetPrescaler(TIMER_Type *Timer, uint32_t Prescaler)
{
    Timer->PR = Prescaler;
}

/** @brief  Get the Prescaler of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Prescaler
  *
  * Prescaler of a Timer is the # of input clocks or counts before
  *  the timer increments.  Changing this changes the number of
  *  counts before each increment of the timer/counter.
  */
__INLINE static uint32_t TIMER_GetPrescaler(TIMER_Type *Timer)
{
    return Timer->PR;
}

/** @brief  Set the Prescaler Count Value of a Timer
  * @param  Timer      The Timer
  * @param  Count  The New Prescaler Count
  * @return None.
  *
  * This is the number of prescaler "ticks" thus far on the way to the
  *  next count increment.
  */
__INLINE static void TIMER_SetPrescalerCount(TIMER_Type *Timer, uint32_t Count)
{
    Timer->PC = Count;
}

/** @brief  Get the Current Prescaler Count Value of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Prescaler Count Value
  *
  * This is the number of prescaler "ticks" thus far on the way to the
  *  next count increment.
  */
__INLINE static uint32_t TIMER_GetPrescalerCount(TIMER_Type *Timer)
{
    return Timer->PC;
}

/** @brief  Set the Actions that will Happen when the Count Equals a "Match" Channel
  * @param  Timer      The Timer on which to operate
  * @param  Channel    The Channel on that Timer for which to Configure Actions
  * @param  Control    The Action(s) to be Taken, ORed Together
  * @return None.
  *
  * Valid Actions (OR together):
  * - TIMER_MatchControl_None
  * - TIMER_MatchControl_Interrupt (Interrupt on match)
  * - TIMER_MatchControl_Reset     (Reset counter to 0 on match)
  * - TIMER_MatchControl_Stop      (Stop counter on match)
  */
__INLINE static void TIMER_SetChannelMatchControl(TIMER_Type *Timer, uint8_t Channel, uint8_t Control)
{
    lpc2xxx_lib_assert(Channel <= 3);
    lpc2xxx_lib_assert((Control & ~TIMER_MatchControl_Mask) == 0);
    
    Timer->MCR = (Timer->MCR & ~(0x07 << (Channel * 3))) | (Control << (Channel * 3));
}

/** @brief  Get the Actions that are Configured to Occur when a Channel Matches a Timer's Count
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer 
  * @return The Currently Configured Action Control Bits, ORed together
  */
__INLINE static uint8_t TIMER_GetChannelMatchControl(TIMER_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);

    return (Timer->MCR >> (Channel * 3)) & 0x07;
}

/** @brief  Set the "Match" Value on one Channel of a Timer
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer on which to Configure the "Match" Value
  * @param  Count      The Count Value on which the Match Channel should Trigger
  * @return None.
  */
__INLINE static void TIMER_SetChannelMatchValue(TIMER_Type *Timer, uint8_t Channel, uint32_t Count)
{
    lpc2xxx_lib_assert(Channel <= 3);

    ((__IO uint32_t *)&Timer->MR0)[Channel] = Count;
}

/** @brief  Get the "Match" Value of a Timer's Channel
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer for which to get the Match Value
  * @return The "Match" Value Configured on the given Channel
  */
__INLINE static uint32_t TIMER_GetChannelMatchValue(TIMER_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);

    return ((__IO uint32_t *)&Timer->MR0)[Channel];
}

/** @brief Set the Functionality of an External Match Pin / Bit
  * @param  Timer    The Timer
  * @param  Channel  The Channel on the Timer for which to Configure the External Match Function
  * @param  Control  The Functionality of the External Match Pin / Bit
  * @return None.
  *
  * Note that regardless of whether a pin is configured for external match duty,
  *  there is a bit that reflects the state of the External Match value.
  *
  * ExtMatch can be:
  * - TIMER_ExtMatch_None
  * - TIMER_ExtMatch_Clear  - Clear the pin / bit on match of channel
  * - TIMER_ExtMatch_Set    - Set the pin / bit on match of channel
  * - TIMER_ExtMatch_Toggle - Toggle the pin / bit on match of channel
  */
__INLINE static void TIMER_SetChannelExtMatchControl(TIMER_Type *Timer, uint8_t Channel, TIMER_ExtMatchControl_Type Control)
{
    lpc2xxx_lib_assert(Channel <= 3);
    lpc2xxx_lib_assert(TIMER_IS_EXT_MATCH(Control));

    Timer->EMR = (Timer->EMR & ~(0x03 << ((Channel * 2) + 4))) | (Control << ((Channel * 2) + 4));
}

/** @brief Get the Configured Functionality of an External Match Pin / Bit
  * @param  Timer    The Timer
  * @param  Channel  The Channel on the Timer for which to get the External Match Configuration
  * @return The Configuration of the External Match Pin / Bit
  */
__INLINE static TIMER_ExtMatchControl_Type TIMER_GetChannelExtMatchControl(TIMER_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);

    return (Timer->EMR >> ((Channel * 2) + 4)) & 0x03;
}

/** @brief Set the Value of a Timer Channel's External Match bit
  * @param  Timer    The Timer
  * @param  Channel  The Timer's Channel on which to set the External Match Bit's Value
  * @param  Value    Whether to Set or Clear the Bit (Zero means Clear, Non-Zero means Set)
  * @return None.
  */
__INLINE static void TIMER_SetChannelExtMatchBit(TIMER_Type *Timer, uint8_t Channel, uint8_t Value)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    if (Value) {
        Timer->EMR |= (1 << Channel);
    } else {
        Timer->EMR &= ~(1 << Channel);
    }
}

/** @brief Get the Value of the Given Timer Channel's External Match Bit
  * @param  Timer    The Timer
  * @param  Channel  The Timer's Channel for which to get the External Match Bit
  * @return The Value of the Timer's Channel's External Match Bit
  */
__INLINE static uint8_t TIMER_GetChannelExtMatchBit(TIMER_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    return (Timer->EMR & (1 << Channel)) ? 1:0;
}

/** @brief  Configure the Capture Input on a Timer/Counter
  * @param  Timer      The Timer for which to Configure a Capture Input
  * @param  Channel    The Channel for which to Configure the Capture Input
  * @param  Control    The capture input configuration bits (ORed together)
  * @return None.
  *
  * Control can be:
  * - TIMER_CaptureControl_None
  * - TIMER_CaptureControl_RisingEdges  (capture on rising edges)
  * - TIMER_CaptureControl_FallingEdges (capture on falling edges)
  * - TIMER_CaptureControl_BothEdges    (capture on both edges)
  * - TIMER_CaptureControl_Interrupt    (interrupt on capture)
  *
  * MUST be TIMER_CaptureControl_None if counter mode is selected on timer.
  */
__INLINE static void TIMER_SetCaptureControl(TIMER_Type *Timer, uint8_t Channel, uint8_t Control)
{
    lpc2xxx_lib_assert(Channel <= 3);
    lpc2xxx_lib_assert((Control & ~TIMER_CaptureControl_Mask) == 0);
    
    Timer->CCR = ((Timer->CCR & ~(TIMER_CaptureControl_Mask << (Channel * 3))) | (Control << (Channel * 3)));
}

/** @brief  Get the Capture Input Configuration for a Timer's Channel
  * @param  Timer      The Timer
  * @param  Channel    The Channel for which to Get the Capture Input Configuration
  * @return The Configured Control Bits (Capture on Rising / Falling / Both, Whether to Raise IRQ, etc)
  */
__INLINE static uint8_t TIMER_GetCaptureControl(TIMER_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    return (Timer->CCR >> (Channel * 3)) & TIMER_CaptureControl_Mask;
}

/** @brief  Get the Captured Count Value from the Given Timer Channel
  * @param  Timer      The Timer
  * @param  Channel    Channel of the Timer from which to get the Captured Value
  */
__INLINE static uint32_t TIMER_GetCaptureValue(TIMER_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3)
    
    return ((__IO uint32_t *)&(Timer->CR0))[Channel];
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

#endif /* #ifndef LPC2XXX_TIMER_H_ */
