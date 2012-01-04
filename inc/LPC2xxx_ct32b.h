/*****************************************************************************
 * @file:    LPC2xxx_ct32b.h
 * @purpose: LPC2xxx 32 Bit Counter/Timer Interface Header File
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. June 2010
 * @license: Simplified BSD License
 *
 * Notes:
 * - The CT32B's are similar to older Timers, but include PWM functionality
 *   and counter capabilities.
 * - These are on e.g. LPC2101/2/3
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

#ifndef LPC2XXX_CT32B_H_
#define LPC2XXX_CT32B_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_CT32B
#error  Your CPU does not seem to have a 32-Bit Timer/Counter (CT32B), or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup CT32B
  * @{
  */

/* Typedefs -----------------------------------------------------------------*/

/** @addtogroup CT32B_Types
  * @{
  */
  
/** @defgroup CT32B_Interrupt_Types
  * @{
  *
  * CT32B Interrupt Sources (match registers, capture) 
  */
#if 0
# define CT32B_IT_Mask                       (0xff)
#else
# define CT32B_IT_Mask                       (0x1f) /* LPC2XXx */
#endif

#define CT32B_IT_None                       (0x00)
#define CT32B_IT_MR0                        (1 << 0)
#define CT32B_IT_MR1                        (1 << 1)
#define CT32B_IT_MR2                        (1 << 2)
#define CT32B_IT_MR3                        (1 << 3)
#define CT32B_IT_CR0                        (1 << 4)

#if 0
#define CT32B_IT_CR1                        (1 << 5)
#define CT32B_IT_CR2                        (1 << 6)
#define CT32B_IT_CR3                        (1 << 7)
#endif

/**
  * @}
  */

/** @defgroup CT32B_Match_Control_Types
  * @{
  *
  * CT32B Actions to take on a match
  */
#define CT32B_MatchControl_Mask             (0x07)

#define CT32B_MatchControl_None             (0x00)
#define CT32B_MatchControl_Interrupt        (1 << 0)
#define CT32B_MatchControl_Reset            (1 << 1)
#define CT32B_MatchControl_Stop             (1 << 2)

/**
  * @}
  */
  
/** @defgroup CT32B_Capture_Control_Types
  * @{
  * 
  * CT32B External Capture Controls (for CAP Pins)
  */
#define CT32B_CaptureControl_Mask           (0x07)
#define CT32B_CaptureControl_None           (0x00)
#define CT32B_CaptureControl_RisingEdges    (1 << 0)
#define CT32B_CaptureControl_FallingEdges   (1 << 1)
#define CT32B_CaptureControl_Interrupt      (1 << 2)

#define CT32B_CaptureControl_BothEdges    (CT32B_CaptureControl_RisingEdges | \
                                           CT32B_CaptureControl_FallingEdges)

/**
  * @}
  */
  
/** @defgroup CT32B_Ext_Match_Control_Types
  * @{
  */

/*! @brief External Match Output Controls */
typedef enum {
    CT32B_ExtMatchControl_None                = 0x00,
    CT32B_ExtMatchControl_Clear,
    CT32B_ExtMatchControl_Set,
    CT32B_ExtMatchControl_Toggle,
} CT32B_ExtMatchControl_Type;
#define CT32B_IS_EXT_MATCH_CONTROL(Control) (((Control) == CT32B_ExtMatchControl_None)  \
                                          || ((Control) == CT32B_ExtMatchControl_Clear) \
                                          || ((Control) == CT32B_ExtMatchControl_Set)   \
                                          || ((Control) == CT32B_ExtMatchControl_Toggle))

/**
  * @}
  */
  
/** @defgroup CT32B_Mode_Types
  * @{
  */

/*! @brief CT32B Counter / Timer Mode Configuration Controls */
typedef enum {
    CT32B_Mode_Timer                   = 0x00,
    CT32B_Mode_CountRisingEdges,
    CT32B_Mode_CountFallingEdges,
    CT32B_Mode_CountAllEdges,
} CT32B_Mode_Type;
#define CT32B_IS_MODE(Mode)  (((Mode) == CT32B_Mode_Timer)             \
                           || ((Mode) == CT32B_Mode_CountRisingEdges)  \
                           || ((Mode) == CT32B_Mode_CountFallingEdges) \
                           || ((Mode) == CT32B_Mode_CountAllEdges))

#define CT32B_Mode_Mask                (0x03)

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
  * @return The "Match" Value of the Match Channel
  */
__INLINE static void CT32B_Enable(CT32B_Type *Timer)
{
    Timer->TCR |= CT32B_CE;
}

/** @brief  Disable a Timer
  * @param  Timer      The Timer to Disable
  * @return The "Match" Value of the Match Channel
  */
__INLINE static void CT32B_Disable(CT32B_Type *Timer)
{
    Timer->TCR &= ~CT32B_CE;
}

/** @brief  Determine Whether a Timer Is Enabled
  * @param  Timer     The Timer
  * @return 1 if the TImer is Enabled, 0 Otherwise
  */
__INLINE static uint8_t CT32B_IsEnabled(CT32B_Type *Timer)
{
    return (Timer->TCR & CT32B_CE) ? 1:0;
}

/** @brief  Set the Operation Mode for a Timer
  * @param  Timer     The Timer
  * @param  Mode      The Timer's Mode Configuration
  * @return None.
  *
  * Mode can be one of:
  * - CT32B_Mode_Timer             -- Timer mode
  * - CT32B_Mode_CountRisingEdges  -- Counter mode, Count Rising Edges on CAP Input
  * - CT32B_Mode_CountFallingEdges -- Counter mode, Count Falling Edges on CAP Input
  * - CT32B_Mode_CountAllEdges     -- Counter mode, Count All Edges on CAP Input
  */
__INLINE static void CT32B_SetMode(CT32B_Type *Timer, CT32B_Mode_Type Mode)
{
    lpc2xxx_lib_assert(CT32B_IS_MODE(Mode));
    Timer->CTCR = Mode;
}

/** @brief  Get the Currently Configured Mode for a Timer
  * @param  Timer     The Timer
  * @return The Currently Active Mode for the Timer
  */
__INLINE static CT32B_Mode_Type CT32B_GetMode(CT32B_Type *Timer)
{
    return Timer->CTCR;
}

/** @brief  Reset a Timer (stays reset until cleared)
  * @param  Timer      The Timer
  * @return None.
  */
__INLINE static void CT32B_AssertReset(CT32B_Type *Timer)
{
    Timer->TCR |= CT32B_CR;
}

/** @brief  Clear a Timer's RESET State
  * @param  Timer      The Timer
  * @return None.
  */
__INLINE static void CT32B_DeassertReset(CT32B_Type *Timer)
{
    Timer->TCR &= ~CT32B_CR;
}

/** @brief Determine Whether a Timer is Being Held in Reset
  * @param  None.
  * @return 1 if the Reset Line is Set, 0 Otherwise.
  */
__INLINE static uint8_t CT32B_ResetIsAsserted(CT32B_Type *Timer)
{
    return (Timer->TCR & CT32B_CR) ? 1:0;
}

/** @brief  Get the Pending Interrupts for a Timer
  * @param  Timer
  * @return Bit mask of Pending Interrupts
  */
__INLINE static uint8_t CT32B_GetPendingIT(CT32B_Type *Timer)
{
    return Timer->IR;
}

/** @brief  Clear Pending Interrupts on a Timer
  * @param  Timer      The Timer
  * @param  Interrupts Bits Specifying which Interrupts to clear
  * @return None.
  */
__INLINE static void CT32B_ClearPendingIT(CT32B_Type *Timer, uint8_t Interrupts)
{
    lpc2xxx_lib_assert((Interrupts & ~CT32B_IT_Mask) == 0);
    Timer->IR = Interrupts;
}

/** @brief  Set the Count Value of a Timer
  * @param  Timer      The Timer
  * @param  Count      The New Count Value
  * @return None.
  */
__INLINE static void CT32B_SetCount(CT32B_Type *Timer, uint32_t Count)
{
    Timer->TC = Count;
}

/** @brief  Get the Current Count Value of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Count
  */
__INLINE static uint32_t CT32B_GetCount(CT32B_Type *Timer)
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
__INLINE static void CT32B_SetPrescaler(CT32B_Type *Timer, uint32_t Prescaler)
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
__INLINE static uint32_t CT32B_GetPrescaler(CT32B_Type *Timer)
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
__INLINE static void CT32B_SetPrescalerCount(CT32B_Type *Timer, uint32_t Count)
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
__INLINE static uint32_t CT32B_GetPrescalerCount(CT32B_Type *Timer)
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
  * - CT32B_MatchControl_None
  * - CT32B_MatchControl_Interrupt (Interrupt on match)
  * - CT32B_MatchControl_Reset     (Reset counter to 0 on match)
  * - CT32B_MatchControl_Stop      (Stop counter on match)
  */
__INLINE static void CT32B_SetChannelMatchControl(CT32B_Type *Timer, uint8_t Channel, uint8_t Control)
{
    lpc2xxx_lib_assert(Channel <= 3);
    lpc2xxx_lib_assert((Control & ~CT32B_MatchControl_Mask) == 0);

    Timer->MCR = (Timer->MCR & ~(0x07 << (Channel * 3))) | (Control << (Channel * 3));
}

/** @brief  Get the Actions that are Configured to Occur when a Channel Matches a Timer's Count
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer 
  * @return The Currently Configured Action Control Bits, ORed together
  */
__INLINE static uint8_t CT32B_GetChannelMatchControl(CT32B_Type *Timer, uint8_t Channel)
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
__INLINE static void CT32B_SetChannelMatchValue(CT32B_Type *Timer, uint8_t Channel, uint32_t Count)
{
    lpc2xxx_lib_assert(Channel <= 3);

    ((__IO uint32_t *)&Timer->MR0)[Channel] = Count;
}

/** @brief  Get the "Match" Value of a Timer's Channel
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer for which to get the Match Value
  * @return The "Match" Value Configured on the given Channel
  */
__INLINE static uint32_t CT32B_GetChannelMatchValue(CT32B_Type *Timer, uint8_t Channel)
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
  * Control can be:
  * - CT32B_ExtMatchControl_None
  * - CT32B_ExtMatchControl_Clear  - Clear the pin / bit on match of channel
  * - CT32B_ExtMatchControl_Set    - Set the pin / bit on match of channel
  * - CT32B_ExtMatchControl_Toggle - Toggle the pin / bit on match of channel
  */
__INLINE static void CT32B_SetChannelExtMatchControl(CT32B_Type *Timer, uint8_t Channel, CT32B_ExtMatchControl_Type Control)
{
    lpc2xxx_lib_assert(Channel <= 3);
    lpc2xxx_lib_assert(CT32B_IS_EXT_MATCH(Control));

    Timer->EMR = (Timer->EMR & ~(0x03 << ((Channel * 2) + 4))) | (Control << ((Channel * 2) + 4));
}

/** @brief Get the Configured Functionality of an External Match Pin / Bit
  * @param  Timer    The Timer
  * @param  Channel  The Channel on the Timer for which to get the External Match Configuration
  * @return The Configuration of the External Match Pin / Bit
  */
__INLINE static CT32B_ExtMatchControl_Type CT32B_GetChannelExtMatchControl(CT32B_Type *Timer, uint8_t Channel)
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

__INLINE static void CT32B_SetChannelExtMatchBit(CT32B_Type *Timer, uint8_t Channel, uint8_t Value)
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
__INLINE static uint8_t CT32B_GetChannelExtMatchBit(CT32B_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    return (Timer->EMR & (1 << Channel)) ? 1:0;
}

/** @brief  Enable a PWM Channel on a Timer
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel on which to enable PWM
  * @return None.
  *
  * If enabled, a PWM channel controls the External Match pin / bit; if disabled, 
  *  it's under external match control.
  */
__INLINE static void CT32B_EnableChannelPWM(CT32B_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    Timer->PWMC |= (1 << Channel);
}

/** @brief  Disable a PWM Channel on a Timer
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel on which to disable PWM
  * @return None.
  *
  * If enabled, a PWM channel controls the External Match pin / bit; if disabled, 
  *  it's under external match control.
  */
__INLINE static void CT32B_DisableChannelPWM(CT32B_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    Timer->PWMC &= ~(1 << Channel);
}

/** @brief  Determine Whether a Timer's Channel is Configured for PWM Operation
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel for which to get PWM Configuration
  * @return 1 if the channel is Configured for PWM operation, 0 if not.
  *
  * If enabled, a PWM channel controls the External Match pin / bit; if disabled, 
  *  it's under external match control.
  */
__INLINE static uint8_t CT32B_ChannelPWMIsEnabled(CT32B_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);
    
    return (Timer->PWMC & (1 << Channel)) ? 1:0;
}

/** @brief  Configure the Capture Input on a Timer/Counter
  * @param  Timer      The Timer for which to Configure a Capture Input
  * @param  Channel    The Channel for which to Configure the Capture Input
  * @param  Control    The capture input configuration bits (ORed together)
  * @return None.
  *
  * Control can be:
  * - CT32B_CaptureControl_None
  * - CT32B_CaptureControl_RisingEdges  (capture on rising edges)
  * - CT32B_CaptureControl_FallingEdges (capture on falling edges)
  * - CT32B_CaptureControl_BothEdges    (capture on both edges)
  * - CT32B_CaptureControl_Interrupt    (interrupt on capture)
  *
  * MUST be CT32B_CaptureControl_None if counter mode is selected on timer.
  */
__INLINE static void CT32B_SetCaptureControl(CT32B_Type *Timer, uint8_t Control)
{
    lpc2xxx_lib_assert(Channel <= 3);
    lpc2xxx_lib_assert((Control & ~CT32B_CaptureControl_Mask) == 0);
    
    Timer->CCR = Control;
}

/** @brief  Get the Capture Input Configuration for a Timer's Channel
  * @param  Timer      The Timer
  * @return The Configured Control Bits (Capture on Rising / Falling / Both, Whether to Raise IRQ, etc)
  */
__INLINE static uint8_t CT32B_GetCaptureControl(CT32B_Type *Timer)
{
    return Timer->CCR;
}

/** @brief  Get the Captured Count Value from the Given Timer Channel
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel (0-3) to Get the Count Value From
  */
__INLINE static uint16_t CT32B_GetCaptureValue(CT32B_Type *Timer, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 3);

    return ((uint32_t *)&Timer->CR0)[Channel];
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

#endif /* #ifndef LPC2XXX_CT32B_H_ */
