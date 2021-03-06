/*
* The Clear BSD License
* Copyright 2016-2017 NXP
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the
* disclaimer below) provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the copyright holder nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
* GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
* HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
* IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*!=================================================================================================
\file       app_event_handler.c
\brief      ZLO Demo: Handles all the different type of Application events
==================================================================================================*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "dbg.h"
#include "app_events.h"
#include "app_buttons.h"
#include "app_sleep_handler.h"
#include "app_event_handler.h"
#include "app_blink_led.h"
#include "app_nwk_event_handler.h"
#include "bdb_api.h"
#include "bdb_fb_api.h"
#include "app_main.h"

#include "app_common.h"

#include "app_LR3LS.h"
#include "app_LR3LS_zigbee.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifdef DEBUG_EVENT_HANDLER
    #define TRACE_EVENT_HANDLER   TRUE
#else
    #define TRACE_EVENT_HANDLER   FALSE
#endif
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void vDioEventHandler(APP_teButtons eTransitionCode);
PRIVATE void vEventStartFindAndBind(void);
PRIVATE void vStartPersistantPolling(void);
PRIVATE void vStopPersistantPolling(void);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vDioEventHandler
 *
 * DESCRIPTION:
 * Processes the Dio events like binding and sniffer state change. Any other events that
 * come through we immediately attempt to go to sleep as we have no process for
 * them.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vDioEventHandler(APP_teButtons eTransitionCode )
{
	static teLR3LSAlarmEnum eLastAlarm = E_LR3LS_ALARM_COUNT;
	static bool_t bAlarmOn = false;
    static uint8_t poll_flag = 0;

    ZPS_eAplZdoPoll();

    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: In vSensorStateMachine TransitionCode = %02x -> ",eTransitionCode);
    switch(eTransitionCode)
    {
    /* Fall through for the button presses as there will be a delayed action*/
    case APP_E_BUTTONS_BUTTON_SW5:
    	bAlarmOn = !bAlarmOn;
    	if (bAlarmOn)
    	{
    		if (++eLastAlarm >= E_LR3LS_ALARM_COUNT)
    			eLastAlarm = E_LR3LS_ALARM_FULL;
    	}

    	vHandleDeviceAlarm(eLastAlarm, bAlarmOn);
        break;

    case APP_E_BUTTONS_BUTTON_SW4:  /* Start/Stop Persistant Polling */
        poll_flag ^= 1;
        poll_flag == 1 ? vStartPersistantPolling() : vStopPersistantPolling();
        break;

    case APP_E_BUTTONS_BUTTON_SW3:  /* Steering */
        DBG_vPrintf(TRUE, "APP: Switch-1(Steering)\r\n");
        BDB_eNsStartNwkSteering();
        sBDB.sAttrib.bTLStealNotAllowed = FALSE;
        break;

    case APP_E_BUTTONS_BUTTON_SW2: /* Find and Bind */
        vEventStartFindAndBind();
        break;

    default:
        break;
    }
}

/****************************************************************************
 *
 * NAME: vAppHandleAppEvent
 *
 * DESCRIPTION:
 * interprets the button press and calls the state machine.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vAppHandleAppEvent(APP_tsEvent sButton)
{
    te_TransitionCode eTransitionCode=NUMBER_OF_TRANSITION_CODE;
    
    ZPS_eAplZdoPoll();

    switch(sButton.eType)
    {
    case APP_E_EVENT_BUTTON_DOWN:
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Button Number   = %d",sButton.uEvent.sButton.u8Button);
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: DIO State       = %08x",sButton.uEvent.sButton.u32DIOState);

        eTransitionCode = sButton.uEvent.sButton.u8Button;

        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Transition Code = %d",eTransitionCode);
        vDioEventHandler(eTransitionCode);
        break;

    case APP_E_EVENT_BUTTON_UP:
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Button Number = %d",sButton.uEvent.sButton.u8Button);
        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: DIO State     = %08x",sButton.uEvent.sButton.u32DIOState);

        eTransitionCode = BUTTON_RELEASED_OFFSET | sButton.uEvent.sButton.u8Button;

        DBG_vPrintf(TRACE_EVENT_HANDLER, "\nAPP Process Buttons: Transition Code = %d",eTransitionCode);
        vDioEventHandler(eTransitionCode);
        break;

//    case APP_E_EVENT_SEND_REPORT:
//        break;

//    case APP_E_EVENT_PERIODIC_REPORT:
//        break;

    default:
        break;
    }

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vEventStartFindAndBind
 *
 * DESCRIPTION:
 * Initiates the find and bind procedure, Starts a poll timer and the blink
 * timer.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vEventStartFindAndBind(void)
{
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: eEZ_FindAndBind");
    sBDB.sAttrib.u16bdbCommissioningGroupID = 0xFFFF;
    BDB_eFbTriggerAsInitiator(E_LR3LS_APPLIANCE_ENDPOINT);
    vStartPollTimer(POLL_TIME);
    vStartBlinkTimer(APP_FIND_AND_BIND_BLINK_TIME);
}

/****************************************************************************
 *
 * NAME: vEventStopFindAndBind
 *
 * DESCRIPTION:
 * Stops the find and bind procedure and attempts to sleep.
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vEventStopFindAndBind(void)
{
    DBG_vPrintf(TRACE_EVENT_HANDLER,"\nAPP Process Buttons: Exit Easy Mode");
    vAPP_ZCL_DeviceSpecific_IdentifyOff();
    BDB_vFbExitAsInitiator();
    vStopBlinkTimer();
    vStopPollTimerTask();
    vAPP_LR3LS_Z_HandleNewJoinEvent(FALSE);
}

/****************************************************************************
 *
 * NAME: vStartPersistantPolling
 *
 * DESCRIPTION:
 * Starts the Poll timer which will in turn keep the device awake so it can
 * receive data from it's parent.
 *
 ****************************************************************************/
PRIVATE void vStartPersistantPolling(void)
{
    APP_bPersistantPolling |= TRUE;
    vStartPollTimer(POLL_TIME_FAST);
    vStartBlinkTimer(APP_KEEP_AWAKE_TIME);
}

/****************************************************************************
 *
 * NAME: vStopPersistantPolling
 *
 * DESCRIPTION:
 * Stops the poll timer which will allow the device to go back to sleep.
 *
 ****************************************************************************/
PRIVATE void vStopPersistantPolling(void)
{
    APP_bPersistantPolling &= FALSE;
    vStopPollTimerTask();
    vStopBlinkTimer();
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
