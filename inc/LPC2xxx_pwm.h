*****************************************************************************
 * @file:    LPC2xxx_pwm.h
 * @purpose: LPC2xxx PWM Timer Interface Header File
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

#ifndef LPC2XXX_PWM_H_
#define LPC2XXX_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "LPC2xxx.h"
#include "LPC2xxx_lib_assert.h"

#ifndef LPC2XXX_HAS_PWM
#error  Your CPU does not seem to have a PWM Peripheral, or a CPU header file is missing/incorrect.  
#endif


/** @addtogroup PWM
  * @{
  */

/* Typedefs -----------------------------------------------------------------*/

/** @addtogroup PWM_Types
  * @{
  */
  
/** @defgroup PWM_Interrupt_Types
  * @{
  */

/*! @brief PWM Interrupt Sources (match registers, capture) */

#define PWM_IT_Mask          (0x70f)
#define PWM_IT_MR0           (1 << 0)
#define PWM_IT_MR1           (1 << 1)
#define PWM_IT_MR2           (1 << 2)
#define PWM_IT_MR3           (1 << 3)

#define PWM_IT_MR4           (1 << 8)
#define PWM_IT_MR5           (1 << 9)
#define PWM_IT_MR6           (1 << 10)

/**
  * @}
  */

/** @defgroup PWM_Match_Control_Types
  * @{
  *
  * PWM Actions to take on a match
  */
#define PWM_MatchControl_Mask             (0x07)

#define PWM_MatchControl_None             (0x00)
#define PWM_MatchControl_Interrupt        (1 << 0)
#define PWM_MatchControl_Reset            (1 << 1)
#define PWM_MatchControl_Stop             (1 << 2)

/**
  * @}
  */
  
/** @defgroup PWM_Mode_Types
  * @{
  *
  * PWM Counter / PWM Mode Configuration Controls
  */
#define PWM_Mode_Mask                     (0x08)

typedef enum {
    PWM_Mode_Timer                     = 0x00,
    PWM_Mode_PWM                       = 0x08,
} PWM_Mode_Type;
#define PWM_IS_MODE(Mode)  (((Mode) == PWM_Mode_Timer) \
                           || ((Mode) == PWM_Mode_PWM))

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
  
/** @brief  Enable a PWM device
  * @param  PWM    Pointer to the PWM device to enable
  * @return None.
  */
__INLINE static void PWM_Enable(PWM_Type *PWM)
{
    PWM->TCR |= PWM_CE;
}

/** @brief  Disable a PWM device
  * @param  PWM    Pointer to the PWM device to disable
  * @return None.
  */
__INLINE static void PWM_Disable(PWM_Type *PWM)
{
    PWM->TCR &= ~PWM_CE;
}

/** @brief  Determine Whether a PWM Is Enabled
  * @param  PWM    Pointer to the PWM device to query
  * @return 1 if the timer is enabled, 0 otherwise
  */
__INLINE static uint8_t PWM_IsEnabled(PWM_Type *PWM)
{
    return (PWM->TCR & PWM_CE) ? 1:0;
}

/** @brief  Set the Operation Mode for a PWM device
  * @param  PWM    Pointer to the PWM device to set
  * @param  Mode   The new PWM timer mode
  * @return None.
  *
  * Mode can be one of:
  * - PWM_Mode_PWM               -- Standard PWM mode
  * - PWM_Mode_CountRisingEdges  -- Counter mode, Count Rising Edges on CAP Input
  * - PWM_Mode_CountFallingEdges -- Counter mode, Count Falling Edges on CAP Input
  * - PWM_Mode_CountAllEdges     -- Counter mode, Count All Edges on CAP Input
  */
__INLINE static void PWM_SetMode(PWM_Type *PWM, PWM_Mode_Type Mode)
{
    lpc2xxx_lib_assert(PWM_IS_MODE(Mode));
    PWM->TCR = (PWM->TCR & ~PWM_Mode_Mask) | Mode;
}

/** @brief  Get the currently configured timer mode for a PWM device
  * @param  PWM    Pointer to the PWM device
  * @return The current mode for the PWM
  */
__INLINE static PWM_Mode_Type PWM_GetMode(PWM_Type *PWM)
{
    return (PWM->TCR & PWM_Mode_Mask);
}

/** @brief  Reset a PWM (stays reset until cleared)
  * @param  PWM    Pointer to the PWM device
  * @return None.
  */
__INLINE static void PWM_AssertReset(PWM_Type *PWM)
{
    PWM->TCR |= PWM_CR;
}

/** @brief  Clear a PWM's RESET state
  * @param  PWM    Pointer to the PWM device
  * @return None.
  */
__INLINE static void PWM_DeassertReset(PWM_Type *PWM)
{
    PWM->TCR &= ~PWM_CR;
}

/** @brief Determine whether a PWM is being held in reset
  * @param         PWM    Pointer to the PWM device
  * @return 1 if the PWM device is in reset state, 0 otherwise
  */
__INLINE static uint8_t PWM_ResetIsAsserted(PWM_Type *PWM)
{
    return (PWM->TCR & PWM_CR) ? 1:0;
}

/** @brief  Get pending interrupts for a PWM device
  * @param         PWM    Pointer to the PWM device
  * @return Bit mask of Pending Interrupts
  */
__INLINE static uint8_t PWM_GetPendingIT(PWM_Type *PWM)
{
    return PWM->IR;
}

/** @brief  Clear pending interrupts for a PWM device
  * @param  PWM         Pointer to the PWM device
  * @param  Interrupts  Bitmask specifying which interrupts to clear
  * @return None.
  */
__INLINE static void PWM_ClearPendingIT(PWM_Type *PWM, uint8_t Interrupts)
{
    lpc2xxx_lib_assert((Interrupts & ~PWM_IT_Mask) == 0);
    
    PWM->IR = Interrupts;
}

/** @brief  Set the count value of a PWM device
  * @param  PWM    Pointer to the PWM device
  * @param  Count  The New Count Value
  * @return None.
  */
__INLINE static void PWM_SetCount(PWM_Type *PWM, uint32_t Count)
{
    PWM->TC = Count;
}

/** @brief  Get the current counter value of a PWM device
  * @param  PWM    Pointer to the PWM device
  * @return The PWM device's current counter value
  */
__INLINE static uint32_t PWM_GetCount(PWM_Type *PWM)
{
    return PWM->TC;
}

/** @brief  Set the prescaler of a PWM device
  * @param  PWM        Pointer to the PWM device
  * @param  Prescaler  The New prescaler value
  * @return None.
  *
  * Prescaler of a PWM is the # of input clocks or counts before
  *  the timer increments.  Changing this changes the number of
  *  counts before each increment of the timer/counter.
  */
__INLINE static void PWM_SetPrescaler(PWM_Type *PWM, uint32_t Prescaler)
{
    PWM->PR = Prescaler;
}

/** @brief  Get the prescaler of a PWM
  * @param  PWM    Pointer to the PWM device
  * @return The PWM device's current prescaler value
  *
  * Prescaler of a PWM is the # of input clocks or counts before
  *  the timer increments.  Changing this changes the number of
  *  counts before each increment of the timer/counter.
  */
__INLINE static uint32_t PWM_GetPrescaler(PWM_Type *PWM)
{
    return PWM->PR;
}

/** @brief  Set the prescaler count value of a PWM device
  * @param  PWM    Pointer to the PWM device
  * @param  Count  The new prescaler count value
  * @return None.
  *
  * This is the number of prescaler "ticks" thus far on the way to the
  *  next count increment.
  */
__INLINE static void PWM_SetPrescalerCount(PWM_Type *PWM, uint32_t Count)
{
    PWM->PC = Count;
}

/** @brief  Get the current prescaler count value of a PWM device
  * @param  PWM    Pointer to the PWM device
  * @return The PWM device's current prescaler count value
  *
  * This is the number of prescaler "ticks" thus far on the way to the
  *  next count increment.
  */
__INLINE static uint32_t PWM_GetPrescalerCount(PWM_Type *PWM)
{
    return PWM->PC;
}

/** @brief  Set the actions that will happen when a PWM channel match occurs
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  The channel on that PWM for which to configure actions
  * @param  Control  The action(s) to be taken, ORed together
  * @return None.
  *
  * Valid Actions (OR together):
  * - PWM_MatchControl_None
  * - PWM_MatchControl_Interrupt (Interrupt on match)
  * - PWM_MatchControl_Reset     (Reset counter to 0 on match)
  * - PWM_MatchControl_Stop      (Stop counter on match)
  */
__INLINE static void PWM_SetChannelMatchControl(PWM_Type *PWM, uint8_t Channel, uint8_t Control)
{
    lpc2xxx_lib_assert(Channel <= 6);
    lpc2xxx_lib_assert((Control & ~PWM_MatchControl_Mask) == 0);

    PWM->MCR = (PWM->MCR & ~(PWM_MatchControl_Mask << (Channel * 3))) | (Control << (Channel * 3));
}

/** @brief  Get the actions that are configured to occur when a PWM channel match occurs
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  The channel on the PWM 
  * @return The currently configured action control bits, ORed together
  */
__INLINE static uint8_t PWM_GetChannelMatchControl(PWM_Type *PWM, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 6);

    return (PWM->MCR >> (Channel * 3)) & PWM_MatchControl_Mask;
}

/** @brief  Set the "Match" value on one channel of a PWM device
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  Channel on the PWM on which to set the "Match" value
  * @param  Count    Count value on which the match channel should trigger
  * @return None.
  *
  * Note: Writes to the PWM match registers don't actually update the
  *  values until they are specifically latched -- see PWM_Latch 
  *  (below).
  */
__INLINE static void PWM_SetChannelMatchValue(PWM_Type *PWM, uint8_t Channel, uint32_t Count)
{
    lpc2xxx_lib_assert(Channel <= 6);

    if (Channel > 3) {
        /* Skip blank area in peripheral memory map */
        Channel += 6;
    }
    
    ((__IO uint32_t *)&PWM->MR0)[Channel] = Count;
}

/** @brief  Get the "Match" value of a PWM device's channel
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  Channel on the PWM for which to get the match value
  * @return The "Match" value configured on the given channel
  */
__INLINE static uint32_t PWM_GetChannelMatchValue(PWM_Type *PWM, uint8_t Channel)
{
    lpc2xxx_lib_assert(Channel <= 6);

    if (Channel > 3) {
        /* Skip blank area in peripheral memory map */
        Channel += 6;
    }

    return ((__IO uint32_t *)&PWM->MR0)[Channel];
}

/** @brief  Enable a PWM output channel
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  Channel on the PWM to enable
  * @return None.
  */
__INLINE static void PWM_EnableOutput(PWM_Type *PWM, uint8_t Channel)
{
    lpc2xxx_lib_assert((Channel >= 1) && (Channel <= 6));

    PWM->PCR |= (((uint32_t)PWM_PWMENA1) << (Channel - 1));
}

/** @brief  Disable a PWM output channel
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  Channel on the PWM to disable
  * @return None.
  */
__INLINE static void PWM_DisableOutput(PWM_Type *PWM, uint8_t Channel)
{
    lpc2xxx_lib_assert((Channel >= 1) && (Channel <= 6));

    PWM->PCR &= ~(((uint32_t)PWM_PWMENA1) << (Channel - 1));
}

/** @brief  Determine whether a PWM output channel is enabled or disabled
  * @param  PWM      Pointer to the PWM device
  * @param  Channel  The channel on the PWM to check
  * @return 1 if the channel is enabled, 0 otherwise
  */
__INLINE static uint8_t PWM_OutputIsEnabled(PWM_Type *PWM, uint8_t Channel)
{
    lpc2xxx_lib_assert((Channel >= 1) && (Channel <= 6));

    return (PWM->PCR &(((uint32_t)PWM_PWMENA1) << (Channel - 1))) ? 1:0;
}

/** @brief  Latch new values into PWM match registers 
  * @param  PWM      Pointer to the PWM device
  * @param  ChannelMask A bitmask of channels to latch
  * @return None.
  *
  * Note: Writes to PWM match registers don't actually update
  *   the counters until they are latched.
  */
__INLINE static void PWM_Latch(PWM_Type *PWM, uint8_t ChannelMask)
{
    lpc2xxx_lib_assert((ChannelMask & 0x80) == 0);
    
    PWM->LER |= ChannelMask;
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

#endif /* #ifndef LPC2XXX_PWM_H_ */
