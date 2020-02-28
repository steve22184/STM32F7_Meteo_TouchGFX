/*
 * ws2812.h
 *
 *  Created on: 23 дек. 2019 г.
 *      Author: ALScode
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TARGET_KEY_SAMPLER_HPP_
#define TARGET_KEY_SAMPLER_HPP_


/*******************************************************************************
*  Includes
*******************************************************************************/
#pragma once
#include <platform/driver/button/ButtonController.hpp>

/*******************************************************************************
*  Defines
*******************************************************************************/

/*******************************************************************************
*  Constants and variables
*******************************************************************************/

/*******************************************************************************
*  Enum
*******************************************************************************/

/*******************************************************************************
*  Typedef
*******************************************************************************/

/*******************************************************************************
*  Local functions declarations
*******************************************************************************/

/*******************************************************************************
*  Struct / Classes
*******************************************************************************/
class KeySampler : public touchgfx::ButtonController
{
public:
    KeySampler() {
        init();
    }
    virtual ~KeySampler() {}
    virtual void init();
    virtual bool sample(uint8_t& key);
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*******************************************************************************
*  Public functions declarations
*******************************************************************************/

 // End of ws2812 namespase


#endif /* TARGET_KEY_SAMPLER_HPP_ */
