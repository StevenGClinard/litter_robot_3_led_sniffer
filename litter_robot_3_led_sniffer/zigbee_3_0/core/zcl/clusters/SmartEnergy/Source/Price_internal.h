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


#ifndef  PRICE_INTERNAL_H_INCLUDED
#define  PRICE_INTERNAL_H_INCLUDED

/*!
\file       Price_internal.h
\brief      The internal API for the Price Cluster
*/     
#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "Price.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teSE_PriceStatus eSE_PublishPriceReceive(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsSE_PricePublishPriceCmdPayload   *psPublishPriceCmdPayload,
                    uint8                      *pu8TransactionSequenceNumber,
                    uint32                     *pu32CurrentTimeInMessage);

PUBLIC teSE_PriceStatus eSE_GetScheduledPricesReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint32                      *pu32StartTime,
                    uint8                       *pu8NumberOfEvents);

PUBLIC teSE_PriceStatus eSE_GetBlockPeriodsReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint32                      *pu32StartTime,
                    uint8                       *pu8NumberOfEvents);

PUBLIC teSE_PriceStatus eSE_GetCurrentPriceReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    teSE_PriceCommandOptions    *pePriceCommandOptions);

PUBLIC void vSE_HandleGetCurrentPrice(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC void vSE_HandleGetSheduledPrices(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC void vSE_HandleGetBlockPeriods(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC void vSE_HandlePublishPrice(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teSE_PriceStatus eSE_AddPriceEntryUsingPointer(
                    tsSE_PriceCustomDataStructure *psPriceCustomDataStructure,
                    bool_t                      bOverwritePrevious,
                    tsSE_PricePublishPriceCmdPayload   *psPublishPriceCmdPayload);

#ifdef BLOCK_CHARGING
PUBLIC teSE_PriceStatus eSE_AddBlockPeriodEntryUsingPointer(
            uint8                                     u8SourceEndPointId,
            bool                                    bIsServer,
            tsSE_PriceCustomDataStructure             *psPriceCustomDataStructure,
            bool_t                                  bOverwritePrevious,
            tsSE_PricePublishBlockPeriodCmdPayload  *psPublishBlockPeriodCmdPayload,
            tsSE_BlockThresholds                    *psBlockThresholds);
#endif /* BLOCK_CHARGING */

PUBLIC teSE_PriceStatus eSE_FindPriceCluster(
                    uint8                       u8SourceEndPointId,
                    bool_t                      bIsServer,
                    tsZCL_EndPointDefinition    **ppsEndPointDefinition,
                    tsZCL_ClusterInstance       **ppsClusterInstance,
                    tsSE_PriceCustomDataStructure  **ppsPriceCustomDataStructure);

PUBLIC void vSE_PriceTimerClickCallback(
                    tsZCL_CallBackEvent        *psCallBackEvent);

PUBLIC teSE_PriceStatus eSE_GetNumberOfFreePriceTableEntries(
                    tsZCL_EndPointDefinition   *psEndPointDefinition,
                    tsSE_PriceCustomDataStructure *psPriceCustomDataStructure,
                    uint8                      *pu8NumberOfEntries);

PUBLIC teSE_PriceStatus eSE_GetNumberOfFreeBlockPeriodTableEntries(
                            tsZCL_EndPointDefinition *psEndPointDefinition,
                            tsSE_PriceCustomDataStructure *psPriceCustomDataStructure,
                            uint8 *pu8NumberOfEntries);

PUBLIC teSE_PriceStatus eSE_PricePublishPriceSend(
                    uint8                               u8SourceEndPointId,
                    uint8                               u8DestinationEndPointId,
                    tsZCL_Address                       *psDestinationAddress,
                    uint8                               *pu8TransactionSequenceNumber,
                    tsSE_PricePublishPriceCmdPayload    *psPublishPriceCmdPayload);

PUBLIC teZCL_Status eSE_PriceCommandHandler(
                    ZPS_tsAfEvent               *pZPSEvent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teSE_PriceStatus eSE_PriceRegisterPriceTimeServer(void);

PUBLIC teSE_PriceStatus eSE_PriceAckCommandSend(
                    uint8                      u8SourceEndPointId,
                    uint8                      u8DestinationEndPointId,
                    tsZCL_Address              *psDestinationAddress,
                    uint8                      *pu8TransactionSequenceNumber,
                    tsSE_PriceAckCmdPayload    *psPriceAckPayload);

PUBLIC void vSE_HandlePriceAck(
                    ZPS_tsAfEvent                 *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teSE_PriceStatus eSE_PriceAckReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsSE_PriceAckCmdPayload     *psPriceAckPayload);


PUBLIC teSE_PriceStatus eSE_PricePublishBlockPeriodSend(
                    uint8                                       u8SourceEndPointId,
                    uint8                                       u8DestinationEndPointId,
                    tsZCL_Address                               *psDestinationAddress,
                    uint8                                       *pu8TransactionSequenceNumber,
                    tsSE_PricePublishBlockPeriodCmdPayload        *psPublishBlockPeriodCmdPayload);

PUBLIC teSE_PriceStatus eSE_PublishBlockPeriodPriceReceive(
                            ZPS_tsAfEvent              *pZPSevent,
                            tsSE_PricePublishBlockPeriodCmdPayload   *psPublishBlockPeriodCmdPayload,
                            uint8                      *pu8TransactionSequenceNumber,
                            uint32                     *pu32CurrentTimeInMessage);

PUBLIC void vSE_HandlePublishBlockPeriod(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);


#ifdef PRICE_CONVERSION_FACTOR

PUBLIC teSE_PriceStatus eSE_PublishConversionFactorReceive(
                            ZPS_tsAfEvent              *pZPSevent,
                            tsSE_PricePublishConversionCmdPayload   *psPublishConversionFactorCmdPayload,
                            uint8                      *pu8TransactionSequenceNumber,
                            uint32                     *pu32CurrentTimeInMessage);

PUBLIC teSE_PriceStatus eSE_PricePublishConversionFactorSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address              *psDestinationAddress,
                    uint8                      *pu8TransactionSequenceNumber,
                    tsSE_PricePublishConversionCmdPayload   *psPublishConversionFactorCmdPayload);

PUBLIC teSE_PriceStatus eSE_GetConversionFactorReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint32                        *pu32StartTime,
                    uint8                        *pu8NumberOfEvents);


PUBLIC void vSE_HandleGetConversionFactor(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC void vSE_HandlePublishConversionFactor(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teSE_PriceStatus eSE_AddConversionFactorUsingPointer(
            uint8                                   u8SourceEndPointId,
            bool                                    bIsServer,
            tsSE_PriceCustomDataStructure           *psPriceCustomDataStructure,
            bool_t                                  bOverwritePrevious,
            tsSE_PricePublishConversionCmdPayload   *psPublishConversionCmdPayload);

PUBLIC teSE_PriceStatus eSE_GetNumberOfFreeConversionFactorTableEntries(
         tsZCL_EndPointDefinition       *psEndPointDefinition,
         tsSE_PriceCustomDataStructure  *psPriceCustomDataStructure,
         uint8                          *pu8NumberOfEntries);
#endif

#ifdef PRICE_CALORIFIC_VALUE

PUBLIC teSE_PriceStatus eSE_GetCalorificValueReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint32                        *pu32StartTime,
                    uint8                        *pu8NumberOfEvents);


PUBLIC teSE_PriceStatus eSE_PricePublishCalorificValueSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address              *psDestinationAddress,
                    uint8                      *pu8TransactionSequenceNumber,
                    tsSE_PricePublishCalorificValueCmdPayload   *psPublishCalorificValueCmdPayload);



PUBLIC void vSE_HandleGetCalorificValue(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC void vSE_HandlePublishCalorificValue(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);


PUBLIC teSE_PriceStatus eSE_PublishCalorificValueReceive(
                            ZPS_tsAfEvent              *pZPSevent,
                            tsSE_PricePublishCalorificValueCmdPayload   *psPublishCalorificValueCmdPayload,
                            uint8                      *pu8TransactionSequenceNumber,
                            uint32                     *pu32CurrentTimeInMessage);

PUBLIC teSE_PriceStatus eSE_AddCalorificValueEntryUsingPointer(
         uint8                                      u8SourceEndPointId,
         bool                                       bIsServer,
         tsSE_PriceCustomDataStructure              *psPriceCustomDataStructure,
         bool_t                                     bOverwritePrevious,
         tsSE_PricePublishCalorificValueCmdPayload  *psPublishCalorificValueCmdPayload);

PUBLIC teSE_PriceStatus eSE_GetNumberOfFreeCalorificValueTableEntries(
         tsZCL_EndPointDefinition       *psEndPointDefinition,
         tsSE_PriceCustomDataStructure  *psPriceCustomDataStructure,
         uint8                          *pu8NumberOfEntries);

#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* PRICE_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
