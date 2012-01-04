/******************************************************************************
 * @file:    LPC2xxx_pinconfig.h
 * @purpose: Header File for including proper headers for a LPC2xxx chip's
 *           simplified Pin Configuration Block settings
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
 
#ifndef LPC2XXX_PINCONFIG_H_
#define LPC2XXX_PINCONFIG_H_

/* Include for proper LPC2xxx definitions */
#include "LPC2xxx.h"

/* Include the CPU model group pin configuration file.
 *  Note: LPC2xxx.h will define LPC2XXX_MODEL based on the chip type being
 *  specified on compile line.  
 */

#if LPC2XXX_MODEL == 2148
# include "LPC2148_pinconfig.h"
#elif LPC2XXX_MODEL == 2138
# include "LPC2138_pinconfig.h"
#elif LPC2XXX_MODEL == 2106
# include "LPC2106_pinconfig.h"
#elif LPC2XXX_MODEL == 2103
# include "LPC2103_pinconfig.h"
#else
# warning "No Header File Found (did you -DLPC2<chip> ?)"
#endif


#endif /* #ifndef LPC2XXX_PINCONFIG_H_ */
