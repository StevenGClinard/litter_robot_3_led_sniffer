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
\file       app_zcl_globals.c
\brief      Aplication ZCL Globals
==============================================================================*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include <app_pdum_cfg.h>
#include "ZQueue.h"
#include "app_zps_cfg.h"
#include "app_zcl_cfg.h"

#include "zps_apl.h"
#include "zps_apl_aib.h"
#include "zps_apl_af.h"

#include "Basic.h"
#include "Identify.h"
#include "ApplianceEventsAndAlerts.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define COMPILE_TIME_ASSERT(pred)    switch(0){case 0:case pred:;}

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/*** AF Context ***************************************************/
typedef struct _zps_tsAplAfSimpleDescCont
{
    ZPS_tsAplAfSimpleDescriptor sSimpleDesc;
    const PDUM_thAPdu *phAPduInClusters;
    bool_t bEnabled;
} zps_tsAplAfSimpleDescCont;
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
PUBLIC uint8 u8MaxZpsConfigEp = 1 ;
PUBLIC uint8 au8EpMapPresent[1] = { 1  };


/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/* Simple Descriptors */
PRIVATE const uint16 s_au16Endpoint0InputClusterList[] = { 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005, 0x8006, 0x8010, 0x8011, 0x8012, 0x8014, 0x8015, 0x8016, 0x8017, 0x8018, 0x8019, 0x801a, 0x801b, 0x801c, 0x801d, 0x801e, 0x8020, 0x8021, 0x8022, 0x8023, 0x8024, 0x8025, 0x8026, 0x8027, 0x8028, 0x8029, 0x802a, 0x8030, 0x8031, 0x8032, 0x8033, 0x8034, 0x8035, 0x8036, 0x8037, 0x8038, };
#define NUMBER_OF_INPUT_CLUSTERS_ENDPOINT0 (sizeof(s_au16Endpoint0InputClusterList)/sizeof(uint16))
#define NUMBER_OF_INPUT_CLUSTERS_DISC_FLAGS_ENDPOINT0 ((NUMBER_OF_INPUT_CLUSTERS_ENDPOINT0 + 7)/8)

PRIVATE const PDUM_thAPdu s_ahEndpoint0InputClusterAPdus[NUMBER_OF_INPUT_CLUSTERS_ENDPOINT0] = { apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, apduZDP, };

PRIVATE uint8 s_au8Endpoint0InputClusterDiscFlags[NUMBER_OF_INPUT_CLUSTERS_DISC_FLAGS_ENDPOINT0] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

PRIVATE const uint16 s_au16Endpoint0OutputClusterList[83] = { 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005, 0x8006, 0x8010, 0x8011, 0x8012, 0x8014, 0x8015, 0x8016, 0x8017, 0x8018, 0x8019, 0x801a, 0x801b, 0x801c, 0x801d, 0x801e, 0x8020, 0x8021, 0x8022, 0x8023, 0x8024, 0x8025, 0x8026, 0x8027, 0x8028, 0x8029, 0x802a, 0x8030, 0x8031, 0x8032, 0x8033, 0x8034, 0x8035, 0x8036, 0x8037, 0x8038, };
#define NUMBER_OF_OUTPUT_CLUSTERS_ENDPOINT0 (sizeof(s_au16Endpoint0InputClusterList)/sizeof(uint16))
#define NUMBER_OF_OUTPUT_CLUSTERS_DISC_FLAGS_ENDPOINT0 ((NUMBER_OF_OUTPUT_CLUSTERS_ENDPOINT0 + 7)/8)
PRIVATE uint8 s_au8Endpoint0OutputClusterDiscFlags[NUMBER_OF_OUTPUT_CLUSTERS_DISC_FLAGS_ENDPOINT0] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

PRIVATE const uint16 s_au16Endpoint1InputClusterList[] = {
		GENERAL_CLUSTER_ID_BASIC,
		GENERAL_CLUSTER_ID_IDENTIFY,
		APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_EVENTS_AND_ALERTS,
		HOME_AUTOMATION_DEFAULT_CLUSTER_ID, };
#define NUMBER_OF_INPUT_CLUSTERS_ENDPOINT1 (sizeof(s_au16Endpoint1InputClusterList)/sizeof(uint16))
#define NUMBER_OF_INPUT_CLUSTERS_DISC_FLAGS_ENDPOINT1 ((NUMBER_OF_INPUT_CLUSTERS_ENDPOINT1 + 7)/8)

PRIVATE const PDUM_thAPdu s_ahEndpoint1InputClusterAPdus[NUMBER_OF_INPUT_CLUSTERS_ENDPOINT1] = {
		apduZCL,
		apduZCL,
		apduZCL,
		apduZCL,
};

PRIVATE uint8 s_au8Endpoint1InputClusterDiscFlags[NUMBER_OF_INPUT_CLUSTERS_DISC_FLAGS_ENDPOINT1] = {
		(1 << 0) | // basic
		(0 << 1) | // identify 0x0d
		(1 << 2) | // appliance events and alerts
		(0 << 3),  // default
};

PRIVATE const uint16 s_au16Endpoint1OutputClusterList[] = {
		GENERAL_CLUSTER_ID_BASIC,
		GENERAL_CLUSTER_ID_IDENTIFY,
		APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_EVENTS_AND_ALERTS,
};
#define NUMBER_OF_OUTPUT_CLUSTERS_ENDPOINT1 (sizeof(s_au16Endpoint1OutputClusterList)/sizeof(uint16))
#define NUMBER_OF_OUTPUT_CLUSTERS_DISC_FLAGS_ENDPOINT1 ((NUMBER_OF_OUTPUT_CLUSTERS_ENDPOINT1 + 7)/8)

PRIVATE uint8 s_au8Endpoint1OutputClusterDiscFlags[NUMBER_OF_OUTPUT_CLUSTERS_DISC_FLAGS_ENDPOINT1] = {
		(0 << 0) | // basic
		(1 << 1) | // identify
		(0 << 2),  // appliance events and alerts
};

PUBLIC zps_tsAplAfSimpleDescCont s_asSimpleDescConts[2] = {
    {
        {
        	ZDP_PROFILE_ID,
            0,					// Device ID
            0,					// Device Version
            0,					// Endpoint
			NUMBER_OF_INPUT_CLUSTERS_ENDPOINT0,
			NUMBER_OF_OUTPUT_CLUSTERS_ENDPOINT0,
            s_au16Endpoint0InputClusterList,
            s_au16Endpoint0OutputClusterList,
            s_au8Endpoint0InputClusterDiscFlags,
            s_au8Endpoint0OutputClusterDiscFlags,
        },
        s_ahEndpoint0InputClusterAPdus,
        1
    },
    {
        {
        	HOME_AUTOMATION_PROFILE_ID,
            0xf1d0,						// Device ID (mfg specific)
            1,							// Device Version
            1,							// Endpoint
			NUMBER_OF_INPUT_CLUSTERS_ENDPOINT1,
			NUMBER_OF_OUTPUT_CLUSTERS_ENDPOINT1,
            s_au16Endpoint1InputClusterList,
            s_au16Endpoint1OutputClusterList,
            s_au8Endpoint1InputClusterDiscFlags,
            s_au8Endpoint1OutputClusterDiscFlags,
        },
        s_ahEndpoint1InputClusterAPdus,
        1
    },
};

/* Node Descriptor */
PUBLIC ZPS_tsAplAfNodeDescriptor s_sNodeDescriptor = {
	ZPS_ZDO_DEVICE_ENDDEVICE,		// logical type
    FALSE,							// complex desc avail
    FALSE,							// user desc avail
    0,								// reserved
    1 << 3,							// frequency band [no defines for this...] bit 3 = 2400 – 2483.5 MHz
    0,								// aps flags
	ZPS_NWK_CAP_ALLOC_ADDR_MASK,	// mac flags
	ZCL_MANUFACTURER_CODE,			// mfg code
    0x7f,							// max buffers
    0x0064,							// max rx size
    0x2a00,							// server mask
    0x0064,							// max tx size
    0x00};							// descriptor caps

/* Node Power Descriptor */
PUBLIC ZPS_tsAplAfNodePowerDescriptor s_sNodePowerDescriptor = {
    0xC,   							// current power mode  C =? ?
    0x4,							// available power sources 4=disposable
    0x4,							// current power source    4 = disposable
    0x0};							// current power source level

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Configuration erros checks                                    ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
