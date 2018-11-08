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
\file       app_LR3LS_zigbee.c
\brief      ZigBee functionality of LR3LS
==================================================================================================*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include "app_LR3LS_zigbee.h"
#include "app_common.h"

// Board includes
#include "app_blink_led.h"
#include "LED.h"
#include "dbg.h"
#include "app_nwk_event_handler.h"

// ZigBee includes
#include "base_device.h"
#include "FunctionLib.h"
#include "Basic.h"
#include "white_goods.h"
#include "ApplianceEventsAndAlerts.h"
#include "bdb_api.h"

#include "build_number.defs"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifdef DEBUG_LR3LS_EVENTS
    #define TRACE_LR3LS_EVENTS   TRUE
#else
    #define TRACE_LR3LS_EVENTS  FALSE
#endif

#define ALERT_CATEGORY_BIT	8
#define ALERT_PRESENCE_BIT	12
typedef enum {
	E_ALERT_CATEGORY_RESERVED_BIT = 0,
	E_ALERT_CATEGORY_WARNING_BIT = 1,
	E_ALERT_CATEGORY_DANGER_BIT = 2,
	E_ALERT_CATEGORY_FAILURE_BIT = 3
} eAlertCategory;

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

PRIVATE tsHA_WhiteGoodsDevice			sDevice;
PRIVATE const zuint24					u8AlarmDefaults[E_LR3LS_ALARM_COUNT] =
{
		1 << E_ALERT_CATEGORY_DANGER_BIT,	// E_LR3LS_ALARM_FULL
		1 << E_ALERT_CATEGORY_FAILURE_BIT,	// E_LR3LS_ALARM_STUCK,
		1 << E_ALERT_CATEGORY_DANGER_BIT,	// E_LR3LS_ALARM_OFF,
		1 << E_ALERT_CATEGORY_FAILURE_BIT,	// E_LR3LS_ALARM_TIMEOUT,
};

PRIVATE tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload sAlarmPayload;

inline static void vSetAlarmOn(teLR3LSAlarmEnum eAlarm) { sAlarmPayload.au24AlertStructure[eAlarm] &= ~(1 << ALERT_PRESENCE_BIT); }
inline static void vSetAlarmOff(teLR3LSAlarmEnum eAlarm) { sAlarmPayload.au24AlertStructure[eAlarm] |= (1 << ALERT_PRESENCE_BIT); }

static uint8 u8SequenceNumber;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

void vApp_LR3LS_Z_HandleStartup(void)
{
    DBG_vPrintf(TRACE_LR3LS_EVENTS, "APP State Event: StartUp\n");
    BDB_eNsStartNwkSteering();
    sDeviceDesc.eNodeState = E_JOINING_NETWORK;
}

void vApp_LR3LS_Z_HandleRunning(ZPS_tsAfEvent* psStackEvent)
{
    DBG_vPrintf(TRACE_LR3LS_EVENTS, "APP State Event: Running: Event %d\n", psStackEvent->eType);

    switch(psStackEvent->eType)
    {

    case ZPS_EVENT_NWK_JOINED_AS_ENDDEVICE:
        vHandleNetworkJoinEndDevice();
        #ifdef APP_NTAG_ICODE
        {
            /* Not a rejoin ? */
            if (FALSE == psStackEvent->uEvent.sNwkJoinedEvent.bRejoin)
            {
                /* Write network data to tag */
                APP_vNtagStart(OCCUPANCYSENSOR_SENSOR_ENDPOINT);
            }
        }
        #endif
        break;

    case ZPS_EVENT_NWK_LEAVE_INDICATION:
        vHandleNetworkLeave(psStackEvent);
        break;

    case ZPS_EVENT_NWK_POLL_CONFIRM:
        vHandlePollResponse(psStackEvent);
        break;

    case ZPS_EVENT_NWK_LEAVE_CONFIRM:
        vHandleNetworkLeaveConfirm(psStackEvent);
        break;

    default:
        break;

    }
}

void vAPP_LR3LS_Z_HandleNewJoinEvent(bool bJoined)
{
    DBG_vPrintf(TRACE_LR3LS_EVENTS,"APP Device Event: joined? %s\n", (bJoined) ? "yes" : "no");
}

void vAPP_LR3LS_Z_ClearMemory(void)
{
	DBG_vPrintf(TRACE_LR3LS_EVENTS,"APP Device Event: Clear memory\n");

	/* resetting the sensor structure back to zero*/
	FLib_MemSet(&sDevice, 0, sizeof(sDevice));
}

void vAPP_LR3LS_Z_DeviceSpecific_Init(void)
{
	DBG_vPrintf(TRACE_LR3LS_EVENTS,"APP Device Event: Init\n");

    /* Initialise the strings in Basic */
    FLib_MemCpy(sDevice.sBasicServerCluster.au8ManufacturerName, ZCL_MANUFACTURER_NAME, CLD_BAS_MANUF_NAME_SIZE);
    FLib_MemCpy(sDevice.sBasicServerCluster.au8ModelIdentifier, ZCL_MODEL_NAME, CLD_BAS_MODEL_ID_SIZE);
    FLib_MemCpy(sDevice.sBasicServerCluster.au8DateCode, BUILD_DATE, CLD_BAS_DATE_SIZE);
    FLib_MemCpy(sDevice.sBasicServerCluster.au8SWBuildID, BUILD_NUMBER, CLD_BAS_SW_BUILD_SIZE);

    FLib_MemSet(&sAlarmPayload, 0, sizeof(sAlarmPayload));
    FLib_MemCpy(sAlarmPayload.au24AlertStructure, (void*)u8AlarmDefaults, sizeof(u8AlarmDefaults));
    sAlarmPayload.u8AlertsCount = E_LR3LS_ALARM_COUNT;
}

teZCL_Status eApp_LR3LS_Z_RegisterEndpoint(tfpZCL_ZCLCallBackFunction fptr)
{
	DBG_vPrintf(TRACE_LR3LS_EVENTS,"APP Device Event: Register Endpoint\n");

	return eHA_RegisterWhiteGoodsEndPoint(E_LR3LS_APPLIANCE_ENDPOINT, fptr, &sDevice);
}

void vAPP_ZCL_DeviceSpecific_UpdateIdentify(void)
{
    APP_vSetLED(LED2, sDevice.sIdentifyServerCluster.u16IdentifyTime%2);
}
void vAPP_ZCL_DeviceSpecific_SetIdentifyTime(uint16 u16Time)
{
    sDevice.sIdentifyServerCluster.u16IdentifyTime=u16Time;
}
void vAPP_ZCL_DeviceSpecific_IdentifyOff(void)
{
    vAPP_ZCL_DeviceSpecific_SetIdentifyTime(0);
    APP_vSetLED(LED2, 0);
}

PUBLIC void vHandleDeviceEvent(teLR3LSEventEnum eEvent)
{
	tsZCL_Address sAddress;
	tsCLD_AEAA_EventNotificationPayload sPayload;

	sAddress.eAddressMode = E_ZCL_AM_BROADCAST;
	sAddress.uAddress.eBroadcastMode = ZPS_E_APL_AF_BROADCAST_RX_ON;

	sPayload.u8EventHeader = 0;
	sPayload.u8EventIdentification = eEvent;

	eCLD_AEAAEventNotificationSend(
			sDevice.sEndPoint.u8EndPointNumber,
			0,
			&sAddress,
			&u8SequenceNumber,
			&sPayload
			);
}

PUBLIC void vHandleDeviceAlarm(teLR3LSAlarmEnum eAlarm, bool_t bOn)
{
	tsZCL_Address sAddress;

	sAddress.eAddressMode = E_ZCL_AM_BROADCAST;
	sAddress.uAddress.eBroadcastMode = ZPS_E_APL_AF_BROADCAST_RX_ON;

	if (bOn)
		vSetAlarmOn(eAlarm);
	else
		vSetAlarmOff(eAlarm);

	eCLD_AEAAAlertsNotificationSend(
			sDevice.sEndPoint.u8EndPointNumber,
			0,
			&sAddress,
			&u8SequenceNumber,
			&sAlarmPayload
			);
}

PUBLIC void vSendImmediateReport(void)
{
    tsZCL_Address sAddress;

	sAddress.eAddressMode = E_ZCL_AM_BROADCAST;
	sAddress.uAddress.eBroadcastMode = ZPS_E_APL_AF_BROADCAST_RX_ON;

	eCLD_AEAAAlertsNotificationSend(
			sDevice.sEndPoint.u8EndPointNumber,
			0,
			&sAddress,
			&u8SequenceNumber,
			&sAlarmPayload
			);
}

