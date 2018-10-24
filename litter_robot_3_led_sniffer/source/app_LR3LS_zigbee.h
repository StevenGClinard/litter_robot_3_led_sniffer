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
\file       app_LR3LS_zigbee.h
\brief      Zigbee functionality of LR3LS
==================================================================================================*/


#ifndef APP_LR3LS_ZIGBEE_H_
#define APP_LR3LS_ZIGBEE_H_

#include "jendefs.h"
#include "app_LR3LS.h"

#include "zcl_options.h"
#include "zcl.h"
#include "app_LR3LS_zigbee.h"

//#include "ZTimer.h"

//typedef struct ZPS_tsAfEvent ZPS_tsAfEvent;
//typedef struct tfpZCL_ZCLCallBackFunction tfpZCL_ZCLCallBackFunction;

//#include "white_goods.h"
//#include "ApplianceEventsAndAlerts.h"

#define APP_JOINING_BLINK_TIME	      (ZTIMER_TIME_MSEC(1000))
#define APP_FIND_AND_BIND_BLINK_TIME  (ZTIMER_TIME_MSEC(500))
#define APP_KEEP_AWAKE_TIME           (ZTIMER_TIME_MSEC(250))

#define FAILED_POLL_COUNT             3
#define FAILED_REJOIN_COUNT           3

typedef enum
{
	E_LR3LS_ZDO_ENDPOINT				= 0,
	E_LR3LS_APPLIANCE_ENDPOINT,

	E_LR3LS_ENDPOINT_COUNT
} teLitterRobot3Endpoints;

PUBLIC void vApp_LR3LS_Z_HandleStartup(void);
PUBLIC void vApp_LR3LS_Z_HandleRunning(ZPS_tsAfEvent* psStackEvent);

PUBLIC void vAPP_LR3LS_Z_HandleNewJoinEvent(void);
PUBLIC void vAPP_LR3LS_Z_ClearMemory(void);
PUBLIC void vAPP_LR3LS_Z_DeviceSpecific_Init(void);
PUBLIC teZCL_Status eApp_LR3LS_Z_RegisterEndpoint(tfpZCL_ZCLCallBackFunction fptr);

PUBLIC void vAPP_ZCL_DeviceSpecific_UpdateIdentify(void);
PUBLIC void vAPP_ZCL_DeviceSpecific_SetIdentifyTime(uint16 u16Time);
PUBLIC void vAPP_ZCL_DeviceSpecific_IdentifyOff(void);

PUBLIC void vHandleDeviceEvent(teLR3LSEventEnum eEvent);
PUBLIC void vHandleDeviceAlarm(teLR3LSAlarmEnum eAlarm, bool_t bOn);
PUBLIC void vSendImmediateReport(void);

typedef enum
{
	E_LR3LS_SOME_KIND_OF_TIMER	= 0,

	E_LR3LS_TIMER_COUNT
} teLitterRobot3TimerEnum;

#endif /* APP_LR3LS_ZIGBEE_H_ */
