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


#ifndef On_Off_PLUG_H
#define ON_OFF_PLUG_H

/*!
\file       on_off_plug.h
\brief      Header for ZigBee On Off Plug profile functions
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
#include "LevelControl.h"
#include "Groups.h"
#include "Scenes.h"
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
    /*
     * All ZLL devices have following mandatory clusters
     */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        tsZCL_ClusterInstance sBasicServer;
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        tsZCL_ClusterInstance sIdentifyServer;
    #endif

     /*
     * On Off plug device has 3 other mandatory clusters for the server
     */
     
    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        tsZCL_ClusterInstance sOnOffServer;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        tsZCL_ClusterInstance sGroupsServer;
    #endif

    #if (defined CLD_SCENES) && (defined SCENES_SERVER)
        tsZCL_ClusterInstance sScenesServer;
    #endif

    /* Recommended optional server clusters*/
    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_SERVER)
        tsZCL_ClusterInstance sLevelControlServer;
    #endif
    
    /* Recommended optional client clusters*/
    /* OTA Cluster Instance */
    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        tsZCL_ClusterInstance sOTAClient;
    #endif
    
} tsZLO_OnOffPlugDeviceClusterInstances;
#pragma pack(pop)
#else
typedef struct 
{
    /*
     * All ZLL devices have following mandatory clusters
     */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        tsZCL_ClusterInstance sBasicServer;
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        tsZCL_ClusterInstance sIdentifyServer;
    #endif

     /*
     * On Off plug device has 3 other mandatory clusters for the server
     */
     
    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        tsZCL_ClusterInstance sOnOffServer;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        tsZCL_ClusterInstance sGroupsServer;
    #endif

    #if (defined CLD_SCENES) && (defined SCENES_SERVER)
        tsZCL_ClusterInstance sScenesServer;
    #endif

    /* Recommended optional server clusters*/
    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_SERVER)
        tsZCL_ClusterInstance sLevelControlServer;
    #endif
    
    /* Recommended optional client clusters*/
    /* OTA Cluster Instance */
    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        tsZCL_ClusterInstance sOTAClient;
    #endif
    
} tsZLO_OnOffPlugDeviceClusterInstances __attribute__ ((aligned(4)));
#endif

/* Holds everything required to create an instance of a Colour Dimmable light */
typedef struct
{
    tsZCL_EndPointDefinition sEndPoint;

    /* Cluster instances */
    tsZLO_OnOffPlugDeviceClusterInstances sClusterInstance;

    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        /* Basic Cluster - Server */
        tsCLD_Basic sBasicServerCluster;
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        /* Identify Cluster - Server */
        tsCLD_Identify sIdentifyServerCluster;
        tsCLD_IdentifyCustomDataStructure sIdentifyServerCustomDataStructure;
    #endif

    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        /* On/Off Cluster - Server */
        tsCLD_OnOff sOnOffServerCluster;
        tsCLD_OnOffCustomDataStructure     sOnOffServerCustomDataStructure;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        /* Groups Cluster - Server */
        tsCLD_Groups sGroupsServerCluster;
        tsCLD_GroupsCustomDataStructure sGroupsServerCustomDataStructure;
    #endif

    #if (defined CLD_SCENES) && (defined SCENES_SERVER)
        /* Scenes Cluster - Server */
        tsCLD_Scenes sScenesServerCluster;
        tsCLD_ScenesCustomDataStructure sScenesServerCustomDataStructure;
    #endif

    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_SERVER)
        /* LevelControl Cluster - Server */
        tsCLD_LevelControl sLevelControlServerCluster;
        tsCLD_LevelControlCustomDataStructure sLevelControlServerCustomDataStructure;
    #endif

    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        /* OTA cluster - Client */
        tsCLD_AS_Ota sCLD_OTA;
        tsOTA_Common sCLD_OTA_CustomDataStruct;
    #endif
} tsZLO_OnOffPlugDevice;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eZLO_RegisterOnOffPlugEndPoint(uint8 u8EndPointIdentifier,
                                              tfpZCL_ZCLCallBackFunction cbCallBack,
                                              tsZLO_OnOffPlugDevice *psDeviceInfo);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* ON_OFF_PLUG_H */
