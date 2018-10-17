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

/*!=============================================================================
\file       ApplianceEventsAndAlertsCommandHandler.c
\brief      Appliance Events And Alerts Command Handler
==============================================================================*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>
//#include "zps_apl_aib.h"
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"

#include "ApplianceEventsAndAlerts.h"
#include "ApplianceEventsAndAlerts_internal.h"

#include "zcl_options.h"

#include "dbg.h"



#ifdef DEBUG_CLD_APPLIANCE_EVENTS_AND_ALERTS
#define TRACE_APPLIANCE_EVENTS_AND_ALERTS    TRUE
#else
#define TRACE_APPLIANCE_EVENTS_AND_ALERTS    FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#if defined(CLD_APPLIANCE_EVENTS_AND_ALERTS) && !defined(APPLIANCE_EVENTS_AND_ALERTS_SERVER) && !defined(APPLIANCE_EVENTS_AND_ALERTS_CLIENT)
#error You Must Have either APPLIANCE_EVENTS_AND_ALERTS_SERVER and/or APPLIANCE_EVENTS_AND_ALERTS_CLIENT defined zcl_options.h
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef APPLIANCE_EVENTS_AND_ALERTS_CLIENT
PRIVATE teZCL_Status eCLD_AEAAHandleGetAlertsResponseORAlertsNotification(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance);

PRIVATE teZCL_Status eCLD_AEAAHandleEventNotification(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance);
#endif

#ifdef APPLIANCE_EVENTS_AND_ALERTS_SERVER
PRIVATE teZCL_Status eCLD_AEAAHandleGetAlerts(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_ApplianceEventsAndAlertsCommandHandler
 **
 ** DESCRIPTION:
 ** Handles Message Cluster custom commands
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ApplianceEventsAndAlertsCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
    tsCLD_ApplianceEventsAndAlertsCustomDataStructure *psCommon;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceEventsAndAlertsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Store return address details */
    eZCL_SetReceiveEventAddressStructure(pZPSevent, &psCommon->sReceiveEventAddress);

    // further error checking can only be done once we have interrogated the ZCL payload
    u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    // fill in callback event structure
    eZCL_SetCustomCallBackEvent(&psCommon->sCustomCallBackEvent, pZPSevent, sZCL_HeaderParams.u8TransactionSequenceNumber, psEndPointDefinition->u8EndPointNumber); 

    /* Fill in message */
    psCommon->sCallBackMessage.u8CommandId = sZCL_HeaderParams.u8CommandIdentifier; 

#ifdef APPLIANCE_EVENTS_AND_ALERTS_SERVER
    /* Handle messages appropriate for the cluster type (Client/Server) */
    if(psClusterInstance->bIsServer == TRUE)
    {

        // SERVER
        if(sZCL_HeaderParams.u8CommandIdentifier == E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_GET_ALERTS) 
        {
            eCLD_AEAAHandleGetAlerts(pZPSevent, psEndPointDefinition, psClusterInstance);
        }else{
                // unlock
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);
        }
    }
#endif

#ifdef APPLIANCE_EVENTS_AND_ALERTS_CLIENT

    /* Handle messages appropriate for the cluster type (Client/Server) */
    if(psClusterInstance->bIsServer == FALSE)
    {

        // CLIENT
        switch(sZCL_HeaderParams.u8CommandIdentifier) 
        {

            case (E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_GET_ALERTS):
            case (E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_ALERTS_NOTIFICATION):
            {
                eCLD_AEAAHandleGetAlertsResponseORAlertsNotification(pZPSevent, psEndPointDefinition, psClusterInstance);
                break;
            }

            case (E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_EVENT_NOTIFICATION):
            {
                eCLD_AEAAHandleEventNotification(pZPSevent, psEndPointDefinition, psClusterInstance);
                break;
            }

            default:
            {
                // unlock
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);
                break;
            }
        }
    }
#endif

    // unlock
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    // delete the i/p buffer on return
    return(E_ZCL_SUCCESS);

}

#ifdef APPLIANCE_EVENTS_AND_ALERTS_SERVER
/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_AEAAHandleGetAlerts
 **
 ** DESCRIPTION:
 ** Handles Log request
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PRIVATE  teZCL_Status eCLD_AEAAHandleGetAlerts(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload sResponse = {0};
    uint8   u8TransactionSequenceNumber;
    tsCLD_ApplianceEventsAndAlertsCustomDataStructure *psCommon;
    tsZCL_Address sZCL_Address;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceEventsAndAlertsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_AEAAGetAlertsReceive(
                                            pZPSevent,
                                            &u8TransactionSequenceNumber);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_APPLIANCE_EVENTS_AND_ALERTS, "\nErr:eCLD_AEAAGetAlertsReceive:%d", eStatus);
        return eStatus;
    }

    /* call callback */
    psCommon->sCallBackMessage.uMessage.psGetAlertsResponseORAlertsNotificationPayload =  &sResponse;
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);

    // build address structure
    eZCL_BuildClientTransmitAddressStructure(&sZCL_Address, &psCommon->sReceiveEventAddress);

    eStatus = eCLD_AEAAGetAlertsResponseORAlertsNotificationSend(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                                     pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                                                     &sZCL_Address,
                                                     &u8TransactionSequenceNumber,
                                                     E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_GET_ALERTS,
                                                     &sResponse);
    return eStatus;
}

#endif

#ifdef APPLIANCE_EVENTS_AND_ALERTS_CLIENT

/****************************************************************************
 **
 ** NAME:       eCLD_AEAAHandleGetAlertsResponseORAlertsNotification
 **
 ** DESCRIPTION:
 ** Handles Log Queue request
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 ** uint8                    u8CommandId                Command ID
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PRIVATE teZCL_Status eCLD_AEAAHandleGetAlertsResponseORAlertsNotification(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    uint8   u8TransactionSequenceNumber;
    tsCLD_ApplianceEventsAndAlertsCustomDataStructure *psCommon;
    tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload sPayload;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceEventsAndAlertsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_AEAAGetAlertsResponseORAlertsNotificationReceive(
                                            pZPSevent,
                                            &u8TransactionSequenceNumber,
                                            &sPayload);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_APPLIANCE_EVENTS_AND_ALERTS, "\nErr:eCLD_AEAAGetAlertsResponseORAlertsNotificationReceive:%d", eStatus);
        return eStatus;
    }

    psCommon->sCallBackMessage.uMessage.psGetAlertsResponseORAlertsNotificationPayload =  &sPayload;
    
    /* call callback */
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);

    return eStatus;
}

/****************************************************************************
 **
 ** NAME:       eCLD_AEAAHandleEventNotification
 **
 ** DESCRIPTION:
 ** Handles Log Queue request
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 ** uint8                     u8CommandId               Command ID
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PRIVATE teZCL_Status eCLD_AEAAHandleEventNotification(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    uint8   u8TransactionSequenceNumber;
    tsCLD_ApplianceEventsAndAlertsCustomDataStructure *psCommon;
    tsCLD_AEAA_EventNotificationPayload sPayload;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceEventsAndAlertsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_AEAAEventNotificationReceive(
                                            pZPSevent,
                                            &u8TransactionSequenceNumber,
                                            &sPayload);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_APPLIANCE_EVENTS_AND_ALERTS, "\nErr:eCLD_AEAAEventNotificationReceive:%d", eStatus);
        return eStatus;
    }

    psCommon->sCallBackMessage.uMessage.psEventNotificationPayload =  &sPayload;
    /* call callback */
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);

    return eStatus;
}

#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/