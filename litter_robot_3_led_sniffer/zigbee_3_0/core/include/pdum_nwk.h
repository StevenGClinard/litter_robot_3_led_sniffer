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

#ifndef PDUM_NWK_H_
#define PDUM_NWK_H_

/*!
\file       pdum_nwk.h
\brief      PDU manager interface for network protocol stacks Manages NPDUs
*/


#ifdef __cplusplus
extern "C" {
#endif

#include <jendefs.h>
#include <pdum_common.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef PDUM_INLINE
#if defined(__IAR_SYSTEMS_ICC__)  
#define PDUM_INLINE static inline
#else  
#define PDUM_INLINE INLINE
#endif
#endif

#ifndef PDUM_ALWAYS_INLINE
#define PDUM_ALWAYS_INLINE ALWAYS_INLINE
#endif

#if (defined JENNIC_CHIP_FAMILY) && (JENNIC_CHIP_FAMILY == JN514x)
// Keep PDUM size for Z01 to avoid patching
#define PDUM_NPDU_SIZE              (127)
#else
//  RAM saving lpsw2999: NPDU size can be shrunk
#define PDUM_NPDU_SIZE              (127-9)
#endif
#define PDUM_NPDU_DESCENDING(npdu)  (((pdum_tsNPdu *)(npdu))->u8Footer < ((pdum_tsNPdu *)(npdu))->u8Header)
#define PDUM_NPDU_ASCENDING(npdu)   (((pdum_tsNPdu *)(npdu))->u8Footer >= ((pdum_tsNPdu *)(npdu))->u8Header)

#define TRACE_NPDU_MAX TRUE

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* NPDU handle */
/* internal container for an NPDU */
/* [I SP001259_sfr 3] begin */
typedef struct pdum_tsNPdu_tag {
    union {
        struct pdum_tsNPdu_tag *psNext;
        struct {
            uint8 u8Footer;
            uint8 u8ClaimedFtr;
            uint8 u8Header;
            union { /* same place for descending */
                uint8 u8Data;
                uint8 u8ClaimedHdr;
            };
        };
    };
#ifdef PDUM_PEDANTIC_CHECKS
    uint8 au8Magic1[4];
#endif
    uint8 au8PayloadStorage[PDUM_NPDU_SIZE]; /* [I SP001259_sfr 6] */
#ifdef PDUM_PEDANTIC_CHECKS
    uint8 au8Magic2[4];
#endif
} pdum_tsNPdu;
/* [I SP001259_sfr 3] end */

/* NPDU handle */
typedef pdum_tsNPdu *PDUM_thNPdu;

/* [I SP001259_sfr 159] begin */
typedef enum {
    PDUM_E_DESCENDING  = 0,
    PDUM_E_ASCENDING = 1
} PDUM_teDirection;
/* [I SP001259_sfr 159] end */

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC PDUM_teStatus PDUM_eNPduAllocate(PDUM_thNPdu *phNPdu); /* [I SP001259_sfr 102] */
PUBLIC PDUM_teStatus PDUM_eNPduAllocateFromISR (PDUM_thNPdu *phNPdu);
PUBLIC PDUM_teStatus PDUM_eNPduClone(PDUM_thNPdu *phNPdu, PDUM_thNPdu hNPdu); /* [I SP001259_sfr 102] */
PUBLIC PDUM_teStatus PDUM_eNPduInitDescending(PDUM_thNPdu phNPdu); /* [I SP001259_sfr 108] */
PUBLIC PDUM_teStatus PDUM_eNPduInitAscending(PDUM_thNPdu phNPdu, uint8 u8PayloadSize); /* [I SP001259_sfr 114] */
PUBLIC PDUM_teStatus PDUM_eNPduFree(PDUM_thNPdu hNPdu); /* [I SP001259_sfr 119] */
PUBLIC PDUM_teStatus PDUM_eNPduFreeFromISR(PDUM_thNPdu hNPdu);
PUBLIC PDUM_teStatus PDUM_eNPduClaimHeader(PDUM_thNPdu hNPdu, uint8 u8HeaderSize); /* [I SP001259_sfr 125] */
PUBLIC PDUM_teStatus PDUM_eNPduClaimFooter(PDUM_thNPdu hNPdu, uint8 u8FooterSize); /* [I SP001259_sfr 133] */
PUBLIC PDUM_teStatus PDUM_eNPduClaimData(PDUM_thNPdu hNPdu, uint8 u8Size);
PUBLIC PDUM_teStatus PDUM_eNPduAscend(PDUM_thNPdu hNPdu); /* [I SP001259_sfr 144] */
PUBLIC PDUM_teStatus PDUM_eNPduDescend(PDUM_thNPdu hNPdu); /* [I SP001259_sfr 149] */
PUBLIC PDUM_teStatus PDUM_eNPduPrependHeaderNBO(PDUM_thNPdu hNPdu, const char *szFormat, ...);
PUBLIC PDUM_teStatus PDUM_eNPduAppendFooterNBO(PDUM_thNPdu hNPdu, const char *szFormat, ...);
PUBLIC PDUM_teStatus PDUM_eNPduAppendDataNBO(PDUM_thNPdu hNPdu, const char *szFormat, ...);
PUBLIC PDUM_teStatus PDUM_eNPduReadHeaderNBO(void *pvStruct, const char *szFormat, PDUM_thNPdu hNPdu);
PUBLIC PDUM_teStatus PDUM_eNPduReadFooterNBO(void *pvStruct, const char *szFormat, PDUM_thNPdu hNPdu);
PUBLIC PDUM_teStatus PDUM_eNPduWriteToBuffer(PDUM_thNPdu hNPdu, uint8 *pu8Buffer);
PUBLIC PDUM_teStatus PDUM_eNPduWriteFromBuffer(PDUM_thNPdu hNPdu, uint8 *pu8Buffer);
PUBLIC PDUM_teStatus PDUM_eNPduWriteDataToBuffer(PDUM_thNPdu hNPdu, uint8 *pu8Buffer);
PUBLIC PDUM_teStatus PDUM_eNPduWriteDataFromBuffer(PDUM_thNPdu hNPdu, uint8 *pu8Buffer);

#ifdef DBG_ENABLE
PUBLIC void PDUM_vDBGPrintNPdu(PDUM_thNPdu hNPdu);
#else
#define PDUM_vDBGPrintNPdu(npdu)
#endif

#ifdef PDUM_PEDANTIC_CHECKS
PUBLIC void vCheckNPduPoolValid(void);
#endif

#if TRACE_NPDU_MAX
PUBLIC uint8 PDUM_u8GetMaxNpduUse(void);
PUBLIC uint8 PDUM_u8GetNpduUse(void);
#endif

/****************************************************************************/
/***        Inlined Functions                                             ***/
/****************************************************************************/

/* [I SP001259_sfr 155] begin */
PDUM_INLINE void *PDUM_pvNPduGetHeader(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE void *PDUM_pvNPduGetHeader(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return &((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8Header];
    }
    return &((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8ClaimedHdr];
}
/* [I SP001259_sfr 155] end */

/* [I SP001259_sfr 130] begin */
PDUM_INLINE uint8 PDUM_u8NPduGetHeaderSize(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE uint8 PDUM_u8NPduGetHeaderSize(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return ((pdum_tsNPdu *)hNPdu)->u8Data - ((pdum_tsNPdu *)hNPdu)->u8Header;
    }
    return ((pdum_tsNPdu *)hNPdu)->u8Header - ((pdum_tsNPdu *)hNPdu)->u8ClaimedHdr;
}
/* [I SP001259_sfr 130] end */

/* [I SP001259_sfr ???] begin */
PDUM_INLINE void *PDUM_pvNPduGetData(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE void *PDUM_pvNPduGetData(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return &((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8ClaimedHdr];
    }
    return NULL;
}
/* [I SP001259_sfr ???] end */

/* [I SP001259_sfr 156] begin */
PDUM_INLINE void *PDUM_pvNPduGetFooter(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE void *PDUM_pvNPduGetFooter(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return &((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8ClaimedFtr];
    }
    return &((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8Footer];
}
/* [I SP001259_sfr 156] end */

/* [I SP001259_sfr 138] begin */
PDUM_INLINE uint8 PDUM_u8NPduGetFooterSize(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE uint8 PDUM_u8NPduGetFooterSize(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return ((pdum_tsNPdu *)hNPdu)->u8Footer - ((pdum_tsNPdu *)hNPdu)->u8ClaimedFtr;
    }
    return ((pdum_tsNPdu *)hNPdu)->u8ClaimedFtr - ((pdum_tsNPdu *)hNPdu)->u8Footer;
}
/* [I SP001259_sfr 138] end */

#if 0
// not sure we need these?
PDUM_INLINE uint8 PDUM_u8NPduReadDataByte(PDUM_thNPdu hNPdu, uint8 u8Offset) PDUM_ALWAYS_INLINE;
PDUM_INLINE uint8 PDUM_u8NPduReadDataByte(PDUM_thNPdu hNPdu, uint8 u8Offset)
{
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return ((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8ClaimedHdr + u8Offset];
    }
    return 0;
    return ((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[
        ((pdum_tsNPdu *)hNPdu)->u8Header + u8Offset > PDUM_NPDU_SIZE ?
        ((pdum_tsNPdu *)hNPdu)->u8Header + u8Offset - PDUM_NPDU_SIZE :
        ((pdum_tsNPdu *)hNPdu)->u8Header + u8Offset];
}

PDUM_INLINE void PDUM_vNPduWriteDataByte(PDUM_thNPdu hNPdu, uint8 u8Offset, uint8 u8Value) PDUM_ALWAYS_INLINE;
PDUM_INLINE void PDUM_vNPduWriteDataByte(PDUM_thNPdu hNPdu, uint8 u8Offset, uint8 u8Value)
{
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        ((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[((pdum_tsNPdu *)hNPdu)->u8ClaimedHdr + u8Offset] = u8Value;
    }
    else
    {
        ((pdum_tsNPdu *)hNPdu)->au8PayloadStorage[
            ((pdum_tsNPdu *)hNPdu)->u8Header + u8Offset > PDUM_NPDU_SIZE ?
            ((pdum_tsNPdu *)hNPdu)->u8Header + u8Offset - PDUM_NPDU_SIZE :
            ((pdum_tsNPdu *)hNPdu)->u8Header + u8Offset] = u8Value;
    }
}
#endif

/* [I SP001259_sfr 141] begin */
PDUM_INLINE uint8 PDUM_u8NPduGetDataSize(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE uint8 PDUM_u8NPduGetDataSize(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    if (PDUM_NPDU_ASCENDING(hNPdu))
    {
        return ((pdum_tsNPdu *)hNPdu)->u8ClaimedFtr - ((pdum_tsNPdu *)hNPdu)->u8Data;
    }
    else
    {
        return ((pdum_tsNPdu *)hNPdu)->u8Footer + (PDUM_NPDU_SIZE - ((pdum_tsNPdu *)hNPdu)->u8Header);
    }
}
/* [I SP001259_sfr 141] end */

/* [I SP001259_sfr 158] begin */
PDUM_INLINE PDUM_teDirection PDUM_eNPduGetDirection(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE PDUM_teDirection PDUM_eNPduGetDirection(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    return PDUM_NPDU_ASCENDING(hNPdu) ? PDUM_E_ASCENDING : PDUM_E_DESCENDING; /* [I SP001259_sfr 159] */
}
/* [I SP001259_sfr 158] end */

/* [I SP001259_sfr ???] begin */
PDUM_INLINE bool_t PDUM_bNPduNoHdrOrFtr(PDUM_thNPdu hNPdu) PDUM_ALWAYS_INLINE;
PDUM_INLINE bool_t PDUM_bNPduNoHdrOrFtr(PDUM_thNPdu hNPdu)
{
#ifdef PDUM_PEDANTIC_CHECKS
    vCheckNPduPoolValid();
#endif
    return ((((pdum_tsNPdu *)hNPdu)->u8Footer == ((pdum_tsNPdu *)hNPdu)->u8ClaimedFtr) &&
            (((pdum_tsNPdu *)hNPdu)->u8Header == ((pdum_tsNPdu *)hNPdu)->u8ClaimedHdr));
}
/* [I SP001259_sfr ???] end */

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#ifdef __cplusplus
};
#endif

#endif /* PDUM_NWK_H_ */
