/*
 * BSD 3-Clause License

Copyright (c) 2018, Steven G. Clinard
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*!=================================================================================================
\file       app_lr3ls.h
\brief      
==================================================================================================*/

#ifndef APP_LR3LS_H_
#define APP_LR3LS_H_

typedef enum
{
	E_LR3LS_EVENT_POWER_ON		= 0x80,
	E_LR3LS_EVENT_BEGIN_CYCLE,
	E_LR3LS_EVENT_END_CYCLE,
} teLR3LSEventEnum;

typedef enum
{
	E_LR3LS_ALARM_FULL 		= 0,
	E_LR3LS_ALARM_STUCK,
	E_LR3LS_ALARM_OFF,
	E_LR3LS_ALARM_TIMEOUT,
	E_LR3LS_ALARM_UNKNOWN,

	E_LR3LS_ALARM_COUNT
} teLR3LSAlarmEnum;

#endif /* APP_LR3LS_H_ */
