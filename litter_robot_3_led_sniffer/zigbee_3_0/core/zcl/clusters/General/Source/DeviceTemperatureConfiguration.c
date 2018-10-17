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
\file       DeviceTemperatureConfiguration.c
\brief      Device Temperature Configuration cluster definition
==============================================================================*/


/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zcl.h"
#include "DeviceTemperatureConfiguration.h"
#include "zcl_options.h"


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
const tsZCL_AttributeDefinition asCLD_DeviceTemperatureConfigurationClusterAttributeDefinitions[] = {
#ifdef DEVICE_TEMPERATURE_CONFIGURATION_SERVER
            /* Device Temperature Information attribute set attribute ID's (3.4.2.2.1) */
            {E_CLD_DEVTEMPCFG_ATTR_ID_CURRENT_TEMPERATURE,          E_ZCL_AF_RD,                E_ZCL_INT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->i16CurrentTemperature),0},

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_MIN_TEMP_EXPERIENCED
            {E_CLD_DEVTEMPCFG_ATTR_ID_MIN_TEMP_EXPERIENCED,         E_ZCL_AF_RD,                E_ZCL_INT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->i16MinTempExperienced),0},
    #endif

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_MAX_TEMP_EXPERIENCED
            {E_CLD_DEVTEMPCFG_ATTR_ID_MAX_TEMP_EXPERIENCED,         E_ZCL_AF_RD,                E_ZCL_INT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->i16MaxTempExperienced),0},
    #endif

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_OVER_TEMP_TOTAL_DWELL
            {E_CLD_DEVTEMPCFG_ATTR_ID_OVER_TEMP_TOTAL_DWELL,        E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->u16OverTempTotalDwell),0},
    #endif

            /* Device Temperature settings attribute set attribute ID's (3.4.2.2.2) */
    #ifdef CLD_DEVTEMPCFG_ATTR_ID_DEVICE_TEMP_ALARM_MASK
            {E_CLD_DEVTEMPCFG_ATTR_ID_DEVICE_TEMP_ALARM_MASK,       (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_BMAP8,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->u8DeviceTempAlarmMask),0},
    #endif

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_LOW_TEMP_THRESHOLD
            {E_CLD_DEVTEMPCFG_ATTR_ID_LOW_TEMP_THRESHOLD,           (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_INT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->i16LowTempThreshold),0},
    #endif

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_HIGH_TEMP_THRESHOLD
            {E_CLD_DEVTEMPCFG_ATTR_ID_HIGH_TEMP_THRESHOLD,          (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_INT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->i16HighTempThreshold),0},
    #endif

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_LOW_TEMP_DWELL_TRIP_POINT
            {E_CLD_DEVTEMPCFG_ATTR_ID_LOW_TEMP_DWELL_TRIP_POINT,    (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT24,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->u24LowTempDwellTripPoint),0},
    #endif

    #ifdef CLD_DEVTEMPCFG_ATTR_ID_HIGH_TEMP_DWELL_TRIP_POINT
            {E_CLD_DEVTEMPCFG_ATTR_ID_HIGH_TEMP_DWELL_TRIP_POINT,   (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT24,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->u24HighTempDwellTripPoint),0},
    #endif
#endif    
            {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                 (E_ZCL_AF_RD|E_ZCL_AF_GA),  E_ZCL_UINT16,   (uint32)(&((tsCLD_DeviceTemperatureConfiguration*)(0))->u16ClusterRevision),0},   /* Mandatory  */

     };

tsZCL_ClusterDefinition sCLD_DeviceTemperatureConfiguration = {
        GENERAL_CLUSTER_ID_DEVICE_TEMPERATURE_CONFIGURATION,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_DeviceTemperatureConfigurationClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_DeviceTemperatureConfigurationClusterAttributeDefinitions,
        NULL
};

uint8 au8DeviceTempConfigClusterAttributeControlBits[(sizeof(asCLD_DeviceTemperatureConfigurationClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_DeviceTemperatureConfigurationCreateDeviceTemperatureConfiguration
 **
 ** DESCRIPTION:
 ** Creates a device temperature configuration cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_DeviceTemperatureConfigurationCreateDeviceTemperatureConfiguration(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{

    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL)  )
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    /* Create an instance of a device temp configuration cluster */
    vZCL_InitializeClusterInstance(
                               psClusterInstance, 
                               bIsServer,
                               psClusterDefinition,
                               pvEndPointSharedStructPtr,
                               pu8AttributeControlBits,
                               NULL,
                               NULL);

    if(psClusterInstance->pvEndPointSharedStructPtr != NULL)
    {
#ifdef DEVICE_TEMPERATURE_CONFIGURATION_SERVER 
        /* Initialise attribute defaults */
        #ifdef CLD_DEVTEMPCFG_ATTR_ID_OVER_TEMP_TOTAL_DWELL
            ((tsCLD_DeviceTemperatureConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u16OverTempTotalDwell = 0x00;
        #endif

        #ifdef CLD_DEVTEMPCFG_ATTR_ID_DEVICE_TEMP_ALARM_MASK
            ((tsCLD_DeviceTemperatureConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u8DeviceTempAlarmMask = 0x00;
        #endif
#endif
        ((tsCLD_DeviceTemperatureConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_DEVTEMPCFG_CLUSTER_REVISION;
    }

    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

