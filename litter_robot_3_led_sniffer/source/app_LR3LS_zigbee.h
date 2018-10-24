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
\file       app_litter_robot_3_led_sniffer.h
\brief      Declarations specific to LR3LS device functions
==================================================================================================*/


#ifndef APP_LITTER_ROBOT_3_LED_SNIFFER_H_
#define APP_LITTER_ROBOT_3_LED_SNIFFER_H_

#include "zcl_options.h"
#include "ZTimer.h"
#include "app_reporting.h"
#include "MultistateInputBasic.h"

#define APP_JOINING_BLINK_TIME	      (ZTIMER_TIME_MSEC(1000))
#define APP_FIND_AND_BIND_BLINK_TIME  (ZTIMER_TIME_MSEC(500))
#define APP_KEEP_AWAKE_TIME           (ZTIMER_TIME_MSEC(250))

#define FAILED_POLL_COUNT             3
#define FAILED_REJOIN_COUNT           3

typedef enum
{
	E_LR3LS_ZDO_ENDPOINT				= 0,
	E_LR3LS_MULTISTATE_INPUT_ENDPOINT,

	E_LR3LS_ENDPOINT_COUNT
} teLitterRobot3Endpoints;


#define   CLD_MULTISTATE_INPUT_BASIC_ATTR_DESCRIPTION

typedef enum
{
	E_LR3LS_ATTRIBUTE_DESCRIPTION		= 0,
	E_LR3LS_ATTRIBUTE_NUMBER_OF_STATES,
	E_LR3LS_ATTRIBUTE_OUT_OF_SERVICE,
	E_LR3LS_ATTRIBUTE_PRESENT_VALUE,
	E_LR3LS_ATTRIBUTE_STATUS_FLAGS,

	E_LR3LS_ATTRIBUTE_COUNT
} teLitterRobot3Attributes;

extern tsReports asDefaultReports[E_LR3LS_ATTRIBUTE_COUNT];

typedef enum
{
	E_LR3LS_STATE_UNKNOWN  = 0,
	E_LR3LS_STATE_OFF		= 1,
	E_LR3LS_STATE_OK		= 2,
	E_LR3LS_STATE_FULL		= 3,
	E_LR3LS_STATE_WAITING	= 4,
	E_LR3LS_STATE_CYCLING	= 5,
	E_LR3LS_STATE_STUCK	= 6,

	E_LR3LS_STATE_COUNT
} teLitterRobot3StateEnum;

PUBLIC void vHandleDeviceStateChange(teLitterRobot3StateEnum state);

PUBLIC void vHandleNewJoinEvent(void);

PUBLIC void vAPP_ZCL_DeviceSpecific_Init(void);
PUBLIC teZCL_Status eApp_ZLO_RegisterEndpoint(tfpZCL_ZCLCallBackFunction fptr);
PUBLIC void vAPP_ZCL_DeviceSpecific_UpdateIdentify(void);
PUBLIC void vAPP_ZCL_DeviceSpecific_SetIdentifyTime(uint16 u16Time);
PUBLIC void vAPP_ZCL_DeviceSpecific_IdentifyOff(void);

typedef enum
{
	E_LR3LS_SOME_KIND_OF_TIMER	= 0,

	E_LR3LS_TIMER_COUNT
} teLitterRobot3TimerEnum;

extern tsCLD_MultistateInputBasic sLR3LSState;

PUBLIC void vAppHandleStartup(void);
PUBLIC void vAppHandleRunning(ZPS_tsAfEvent* psStackEvent);

#endif /* APP_LITTER_ROBOT_3_LED_SNIFFER_H_ */
