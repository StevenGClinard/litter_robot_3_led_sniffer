/*
* The Clear BSD License
* Copyright 2015-2017 NXP
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

#ifndef BDB_TL_INCLUDED
#define BDB_TL_INCLUDED

/*!=============================================================================
\file       bdb_tl.h
\brief      BDB Touchlink API
==============================================================================*/

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define ADJUST_POWER   TRUE

#ifdef CPU_MKW41Z512VHT4
#define TX_POWER_NORMAL     (22) //0Bbm (gPhyDefaultTxPowerLevel_d)
#define TX_POWER_LOW        (3) //-16dBm
#else
#if JENNIC_CHIP==JN5169
#define TX_POWER_NORMAL     ((uint32)(8))
#define TX_POWER_LOW        ((uint32)(0))
#else
#define TX_POWER_NORMAL     ((uint32)(3))
#define TX_POWER_LOW        ((uint32)(-9))
#endif
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void BDB_vTlInit(void);
PUBLIC bool_t BDB_bTlTouchLinkInProgress( void);
PUBLIC bool_t bIsTlStarted(void);
PUBLIC void BDB_vTlStateMachine( tsBDB_ZCLEvent *psEvent);

PUBLIC uint8 BDB_u8TlEncryptKey( uint8* au8InData,
                                  uint8* au8OutData,
                                  uint32 u32TransId,
                                  uint32 u32ResponseId,
                                  uint8 u8KeyIndex);
PUBLIC uint8 BDB_eTlDecryptKey( uint8* au8InData,
                                  uint8* au8OutData,
                                  uint32 u32TransId,
                                  uint32 u32ResponseId,
                                  uint8 u8KeyIndex);
PUBLIC bool_t BDB_bTlIsKeySupported(uint8 u8KeyIndex);
PUBLIC uint8 BDB_u8TlGetRandomPrimary(void);
PUBLIC uint8 BDB_u8TlNewUpdateID(uint8 u8ID1, uint8 u8ID2 );
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
PUBLIC void vECB_Decrypt(uint8* au8Key,
                         uint8* au8InData,
                         uint8* au8OutData);
#endif
PUBLIC void BDB_vTlTimerCb(void *pvParam);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern PUBLIC uint8 u8TimerBdbTl;

#if defined __cplusplus
}
#endif

#endif  /* BDB_TL_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/






