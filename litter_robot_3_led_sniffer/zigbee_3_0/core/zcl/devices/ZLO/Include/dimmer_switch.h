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


#ifndef DIMMER_SWITCH_H
#define DIMMER_SWITCH_H

/*!
\file       dimmer_switch.h
\brief      Header for ZigBee Dimmer switch profile functions
*/

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/    
#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "Basic.h"
#include "Identify.h"
#include "OnOff.h"
#include "OOSC.h"
#include "Groups.h"
#include "Scenes.h"
#include "LevelControl.h"
#ifdef CLD_OTA
#include "OTA.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Holds cluster instances */
#if defined(__IAR_SYSTEMS_ICC__)
#pragma pack(push, 4)
typedef struct 
{
    /* All ZLO devices have 2 mandatory clusters - Basic(server) and Identify(server) */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        tsZCL_ClusterInstance sBasicServer;
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        tsZCL_ClusterInstance sIdentifyServer;
    #endif

    /*Recommended Optional server clusters */
   
    #if (defined CLD_OOSC) && (defined OOSC_SERVER)
        tsZCL_ClusterInstance sOOSCServer;
    #endif
    
    /* Mandatory client clusters */
    
    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
        tsZCL_ClusterInstance sIdentifyClient;
    #endif

    #if (defined CLD_BASIC) && (defined BASIC_CLIENT)
        tsZCL_ClusterInstance sBasicClient;
    #endif
    
    #if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
        tsZCL_ClusterInstance sOnOffClient;
    #endif

    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
        tsZCL_ClusterInstance sLevelControlClient;
    #endif

    /*Recommended Optional client clusters */
    #if (defined CLD_SCENES) && (defined SCENES_CLIENT)
        tsZCL_ClusterInstance sScenesClient;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
        tsZCL_ClusterInstance sGroupsClient;
    #endif

    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        /* Add  cluster instance for the OTA cluster */
        tsZCL_ClusterInstance sOTAClient;
    #endif

} tsZLO_DimmerSwitchDeviceClusterInstances;
#pragma pack(pop)
#else  
typedef struct 
{
    /* All ZLO devices have 2 mandatory clusters - Basic(server) and Identify(server) */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        tsZCL_ClusterInstance sBasicServer;
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        tsZCL_ClusterInstance sIdentifyServer;
    #endif

    /*Recommended Optional server clusters */
   
    #if (defined CLD_OOSC) && (defined OOSC_SERVER)
        tsZCL_ClusterInstance sOOSCServer;
    #endif
    
    /* Mandatory client clusters */
    
    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
        tsZCL_ClusterInstance sIdentifyClient;
    #endif

    #if (defined CLD_BASIC) && (defined BASIC_CLIENT)
        tsZCL_ClusterInstance sBasicClient;
    #endif
    
    #if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
        tsZCL_ClusterInstance sOnOffClient;
    #endif

    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
        tsZCL_ClusterInstance sLevelControlClient;
    #endif

    /*Recommended Optional client clusters */
    #if (defined CLD_SCENES) && (defined SCENES_CLIENT)
        tsZCL_ClusterInstance sScenesClient;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
        tsZCL_ClusterInstance sGroupsClient;
    #endif

    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        /* Add  cluster instance for the OTA cluster */
        tsZCL_ClusterInstance sOTAClient;
    #endif

} tsZLO_DimmerSwitchDeviceClusterInstances __attribute__ ((aligned(4)));
#endif


/* Holds everything required to create an instance of a dimmer switch */
typedef struct
{
    tsZCL_EndPointDefinition sEndPoint;

    /* Cluster instances */
    tsZLO_DimmerSwitchDeviceClusterInstances sClusterInstance;

    /* Mandatory server clusters */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        /* Basic Cluster - Server */
        tsCLD_Basic sBasicServerCluster;
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        /* Identify Cluster - Server */
        tsCLD_Identify sIdentifyServerCluster;
        tsCLD_IdentifyCustomDataStructure sIdentifyServerCustomDataStructure;
    #endif

        /* Optional server clusters */
    #if (defined CLD_OOSC) && (defined OOSC_SERVER)
        /* On/Off Switch Configuration Cluster - Server */
        tsCLD_OOSC sOOSCServerCluster;
    #endif

    /* Mandatory client clusters */
    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
        /* Identify Cluster - Client */
        tsCLD_Identify sIdentifyClientCluster;
        tsCLD_IdentifyCustomDataStructure sIdentifyClientCustomDataStructure;
    #endif

    #if (defined CLD_BASIC) && (defined BASIC_CLIENT)
        /* Basic Cluster - Client */
        tsCLD_Basic sBasicClientCluster;
    #endif
    
    #if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
        tsCLD_OnOffClient sOnOffClientCluster;
    #endif
        
    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
        /* Level Control Cluster - Client */
        tsCLD_LevelControlClient sLevelControlClientCluster;
        tsCLD_LevelControlCustomDataStructure sLevelControlClientCustomDataStructure;
    #endif
    
    /* Recommended Optional client clusters */
    #if (defined CLD_SCENES) && (defined SCENES_CLIENT)
        /* Scenes Cluster - Client */
        tsCLD_Scenes sScenesClientCluster;
        tsCLD_ScenesCustomDataStructure sScenesClientCustomDataStructure;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
        /* Groups Cluster - Client */
        tsCLD_Groups sGroupsClientCluster;
        tsCLD_GroupsCustomDataStructure sGroupsClientCustomDataStructure;
    #endif

    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        tsCLD_AS_Ota sCLD_OTA;
        tsOTA_Common sCLD_OTA_CustomDataStruct;
    #endif
} tsZLO_DimmerSwitchDevice;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eZLO_RegisterDimmerSwitchEndPoint(uint8 u8EndPointIdentifier,
                                                 tfpZCL_ZCLCallBackFunction cbCallBack,
                                                 tsZLO_DimmerSwitchDevice *psDeviceInfo);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* DIMMER_SWITCH_H */
