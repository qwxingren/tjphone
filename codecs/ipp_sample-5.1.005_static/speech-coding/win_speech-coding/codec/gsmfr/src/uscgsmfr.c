/*/////////////////////////////////////////////////////////////////////////////
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2004-2006 Intel Corporation. All Rights Reserved.
//
//     Intel(R) Integrated Performance Primitives
//     USC - Unified Speech Codec interface library
//
// By downloading and installing USC codec, you hereby agree that the
// accompanying Materials are being provided to you under the terms and
// conditions of the End User License Agreement for the Intel(R) Integrated
// Performance Primitives product previously accepted by you. Please refer
// to the file ipplic.htm located in the root directory of your Intel(R) IPP
// product installation for more information.
//
// A speech coding standards promoted by ITU, ETSI, 3GPP and other
// organizations. Implementations of these standards, or the standard enabled
// platforms may require licenses from various entities, including
// Intel Corporation.
//
//
// Purpose: GSM FR 06.10: USC functions.
//
*/

#include "owngsmfr.h"
#include "gsmfrapi.h"
#include <string.h>
#include <usc.h>

#define INIT_SEED          11111
#define GSMFR_NUM_RATES        1
#define GSMFR_EXT_FRAME_LEN  160
#define GSMFR_BITS_PER_SAMPLE 16

static USC_Status GetInfoSize(int *pSize);
static USC_Status GetInfo(USC_Handle handle, void *pInfo);
static USC_Status NumAlloc(const void *options, int *nbanks);
static USC_Status MemAlloc(const void *options, USC_MemBank *pBanks);
static USC_Status Init(const void *options, const USC_MemBank *pBanks, USC_Handle *handle);
static USC_Status Reinit(const void *modes, USC_Handle handle );
static USC_Status Control(const void *modes, USC_Handle handle );
static USC_Status Encode(USC_Handle handle, USC_PCMStream *in, USC_Bitstream *out);
static USC_Status Decode(USC_Handle handle, USC_Bitstream *in, USC_PCMStream *out);
static USC_Status GetOutStreamSize(const USC_Option *options, int bitrate, int nbytesSrc, int *nbytesDst);
static USC_Status SetFrameSize(const USC_Option *options, USC_Handle handle, int frameSize);


typedef struct {
    int direction;
    GSMFR_Params_t params;
    short seed;
    int fReset;
    int fReset_old;
    int lostFrames;
    int validFrames;
    unsigned char validFrame[GSMFR_PACKED_FRAME_LEN];
    int reserved; // for future extension
} GSMFR_Handle_Header;

/* global usc vector table */
USCFUN USC_Fxns USC_GSMFR_Fxns=
{
    {
        USC_Codec,
        GetInfoSize,
        GetInfo,
        NumAlloc,
        MemAlloc,
        Init,
        Reinit,
        Control
    },
    Encode,
    Decode,
    GetOutStreamSize,
    SetFrameSize

};

static __ALIGN32 CONST USC_Rates pTblRates_GSMFR[GSMFR_NUM_RATES]={
    {13000}
};

static USC_Status GetInfoSize(int *pSize)
{
    *pSize = sizeof(USC_CodecInfo);
    return USC_NoError;
}
static USC_Status GetInfo(USC_Handle handle, void *pInf)
{
   USC_CodecInfo *pInfo=pInf;
   GSMFR_Handle_Header *gsmfr_header;

   pInfo->name = "IPP_GSMFR";
   pInfo->params.framesize = GSMFR_EXT_FRAME_LEN*sizeof(short);
   if (handle == NULL) {
      pInfo->params.direction = 0;
      pInfo->params.modes.vad = 2;
    } else {
      gsmfr_header = (GSMFR_Handle_Header*)handle;
      pInfo->params.direction = gsmfr_header->direction;
      switch(gsmfr_header->params.vadDirection) {
        case GSMFR_VAD_OFF:  pInfo->params.modes.vad = 0; break;
        case GSMFR_DOWNLINK: pInfo->params.modes.vad = 1; break;
        case GSMFR_UPLINK:   pInfo->params.modes.vad = 2; break;
        default:             pInfo->params.modes.vad = 0; break;
      }
    }
   pInfo->params.modes.bitrate = 13000;
   pInfo->params.modes.truncate = 0;
   pInfo->pcmType.sample_frequency = 8000;
   pInfo->pcmType.bitPerSample = GSMFR_BITS_PER_SAMPLE;
   pInfo->maxbitsize = GSMFR_PACKED_FRAME_LEN;
   pInfo->params.modes.hpf = 0;
   pInfo->params.modes.pf = 0;
   pInfo->params.law = 0;
    pInfo->nRates = GSMFR_NUM_RATES;
    pInfo->pRateTbl = (const USC_Rates *)&pTblRates_GSMFR;

   return USC_NoError;
}

static USC_Status NumAlloc(const void *opt, int *nbanks)
{
    if (nbanks==NULL)
        return USC_NotInitialized;
    if (opt==NULL)
        return USC_NotInitialized;
    *nbanks = 1;
    return USC_NoError;
}

static USC_Status MemAlloc(const void *opt, USC_MemBank *pBanks)
{
    const USC_Option *options=opt;
    unsigned int nbytes;
    if (pBanks==NULL)
        return USC_NotInitialized;
    if (opt==NULL)
        return USC_NotInitialized;
    pBanks->pMem = NULL;
    pBanks->align = 32;
    pBanks->memType = USC_OBJECT;
    pBanks->memSpaceType = USC_NORMAL;

   if (options->direction == 0) /* encode only */
    {
        apiGSMFREncoder_Alloc((int *)&nbytes);
    }
    else if (options->direction == 1) /* decode only */
    {
        apiGSMFRDecoder_Alloc((int *)&nbytes);
    } else {
        return USC_NoOperation;
    }
    pBanks->nbytes = nbytes + sizeof(GSMFR_Handle_Header); /* include GSMFR_Handle_Header */
    return USC_NoError;
}

static USC_Status Init(const void *opt, const USC_MemBank *pBanks, USC_Handle *handle)
{
    const USC_Option *options=opt;
    GSMFR_Handle_Header *gsmfr_header;
    *handle = (USC_Handle*)pBanks->pMem;
    gsmfr_header = (GSMFR_Handle_Header*)*handle;
    gsmfr_header->direction = options->direction;

    switch(options->modes.vad) {
      case 1: gsmfr_header->params.vadDirection = GSMFR_DOWNLINK; break;
      case 2: gsmfr_header->params.vadDirection = GSMFR_UPLINK; break;
      default: gsmfr_header->params.vadDirection = GSMFR_VAD_OFF; break;
    }
     if(gsmfr_header->params.vadDirection>0)
        gsmfr_header->params.vadMode=GSMFR_VAD_ON;
     else
        gsmfr_header->params.vadMode=GSMFR_VAD_OFF;
     gsmfr_header->params.ltp_f=LTP_OFF;//options->modes.truncate;
     gsmfr_header->params.direction=(GSMFR_DIRECTION_t)options->direction;
     gsmfr_header->fReset=0;
     gsmfr_header->fReset_old = 1;
     gsmfr_header->seed = INIT_SEED;

    if (options->direction == 0) /* encode only */
    {
        GSMFREncoder_Obj *EncObj = (GSMFREncoder_Obj *)((char*)*handle + sizeof(GSMFR_Handle_Header));
        apiGSMFREncoder_Init(EncObj, &gsmfr_header->params);
    }
    else if (options->direction == 1) /* decode only */
    {
        GSMFRDecoder_Obj *DecObj = (GSMFRDecoder_Obj *)((char*)*handle + sizeof(GSMFR_Handle_Header));
        apiGSMFRDecoder_Init(DecObj, &gsmfr_header->params);

    } else {
        return USC_NoOperation;
    }
    return USC_NoError;
}

static USC_Status Reinit(const void *mode, USC_Handle handle )
{
    const USC_Modes *modes=mode;
    GSMFR_Handle_Header *gsmfr_header=(GSMFR_Handle_Header*)handle;
    if (modes==NULL) {
        return USC_NoOperation;
    }
    if (gsmfr_header->direction == 0) /* encode only */
    {
        GSMFREncoder_Obj *EncObj = (GSMFREncoder_Obj *)((char*)handle + sizeof(GSMFR_Handle_Header));
        apiGSMFREncoder_Init(EncObj, &gsmfr_header->params);
    }
    else if (gsmfr_header->direction == 1) /* decode only */
    {
        GSMFRDecoder_Obj *DecObj = (GSMFRDecoder_Obj *)((char*)handle + sizeof(GSMFR_Handle_Header));
        gsmfr_header->fReset=0;
        gsmfr_header->fReset_old = 1;
        gsmfr_header->seed = INIT_SEED;

        apiGSMFRDecoder_Init(DecObj, &gsmfr_header->params);
    } else {
        return USC_NoOperation;
    }
    return USC_NoError;
}

static USC_Status Control(const void *mode, USC_Handle handle )
{
   const USC_Modes *modes=mode;
   GSMFR_Handle_Header *gsmfr_header;
   gsmfr_header = (GSMFR_Handle_Header*)handle;
   switch(modes->vad) {
      case 1:  gsmfr_header->params.vadDirection = GSMFR_DOWNLINK; break;
      case 2:  gsmfr_header->params.vadDirection = GSMFR_UPLINK; break;
      default: gsmfr_header->params.vadDirection = GSMFR_VAD_OFF; break;
   }
   if(gsmfr_header->params.vadDirection>0)
      gsmfr_header->params.vadMode=GSMFR_VAD_ON;
   else
      gsmfr_header->params.vadMode=GSMFR_VAD_OFF;

   if (gsmfr_header->direction == 0) /* encode only */
   {
      GSMFREncoder_Obj *EncObj = (GSMFREncoder_Obj *)((char*)handle + sizeof(GSMFR_Handle_Header));
      apiGSMFREncoder_Init(EncObj, &gsmfr_header->params);
   }
   return USC_NoError;
}

#define EHF_MASK 0x0008

static int is_pcm_frame_homing (const USC_PCMStream *in) {
    int i, k=0;
    short *pSrc = (short *)in->pBuffer;
    for(i = 0; i < (int)(in->nbytes/sizeof(short)); i++) {
        k = pSrc[i] ^ EHF_MASK;
        if(k)
            break;
    }
    return !k;
}

static USC_Status Encode(USC_Handle handle, USC_PCMStream *in, USC_Bitstream *out)
{
    GSMFR_Handle_Header *gsmfr_header;
    GSMFREncoder_Obj *EncObj;
    int vad, hangover,reset_flag;
    gsmfr_header = (GSMFR_Handle_Header*)handle;

    if(handle == NULL) return USC_InvalidHandler;

    EncObj = (GSMFREncoder_Obj *)((char*)handle + sizeof(GSMFR_Handle_Header));

    /* check for homing frame */
    reset_flag = is_pcm_frame_homing(in);

    if(apiGSMFREncode(EncObj,(const short *)in->pBuffer,(unsigned char *)out->pBuffer,&vad,&hangover ) != APIGSMFR_StsNoErr){
        return USC_NoOperation;
    }
    if(reset_flag != 0) {
        apiGSMFREncoder_Init(EncObj, &gsmfr_header->params);
    }
    in->nbytes = GSMFR_EXT_FRAME_LEN*sizeof(short);
    out->bitrate=in->bitrate;
    out->nbytes=GSMFR_PACKED_FRAME_LEN;
    if(gsmfr_header->params.vadMode == GSMFR_VAD_ON ){
        if(vad){/* voice activity detected */
            out->frametype=1;/* speech frame */
        }else{
            if(hangover) {
                out->frametype=2;/* silence frame as speech frame, SP=1 */
            }else{
                out->frametype=0;/* SID frame, SP=0   */
            }
        }
    }else{
        out->frametype=-1;
    }

    return USC_NoError;
}

static void B2R(const unsigned char *pSrc, short *out_buff_cur)
{
   frame *pf = (frame*)out_buff_cur;
   pf->LARc[0]  = (short)((pSrc[0] & 0xF) << 2);
   pf->LARc[0] |= (pSrc[1] >> 6) & 0x3;
   pf->LARc[1]  = (short)(pSrc[1] & 0x3F);
   pf->LARc[2]  =(short)( (pSrc[2] >> 3) & 0x1F);
   pf->LARc[3]  =(short)( (pSrc[2] & 0x7) << 2);
   pf->LARc[3] |=(short)( (pSrc[3] >> 6) & 0x3);
   pf->LARc[4]  =(short)( (pSrc[3] >> 2) & 0xF);
   pf->LARc[5]  =(short)( (pSrc[3] & 0x3) << 2);
   pf->LARc[5] |=(short)( (pSrc[4] >> 6) & 0x3);
   pf->LARc[6]  =(short)( (pSrc[4] >> 3) & 0x7);
   pf->LARc[7]  =(short)( pSrc[4] & 0x7);
   pf->Ncr0     =(short)( (pSrc[5] >> 1) & 0x7F);
   pf->bcr0     =(short)( (pSrc[5] & 0x1) << 1);
   pf->bcr0    |=(short)( (pSrc[6] >> 7) & 0x1);
   pf->Mcr0     =(short)( (pSrc[6] >> 5) & 0x3);
   pf->xmaxc0   =(short)( (pSrc[6] & 0x1F) << 1);
   pf->xmaxc0  |=(short)( (pSrc[7] >> 7) & 0x1);
   pf->xmcr0[0]  =(short)( (pSrc[7] >> 4) & 0x7);
   pf->xmcr0[1]  =(short)( (pSrc[7] >> 1) & 0x7);
   pf->xmcr0[2]  =(short)( (pSrc[7] & 0x1) << 2);
   pf->xmcr0[2] |=(short)( (pSrc[8] >> 6) & 0x3);
   pf->xmcr0[3]  =(short)( (pSrc[8] >> 3) & 0x7);
   pf->xmcr0[4]  =(short)( pSrc[8] & 0x7);
   pf->xmcr0[5]  =(short)( (pSrc[9] >> 5) & 0x7);
   pf->xmcr0[6]  =(short)( (pSrc[9] >> 2) & 0x7);
   pf->xmcr0[7]  =(short)( (pSrc[9] & 0x3) << 1);
   pf->xmcr0[7] |=(short)( (pSrc[10] >> 7) & 0x1);
   pf->xmcr0[8]  =(short)( (pSrc[10] >> 4) & 0x7);
   pf->xmcr0[9]  =(short)( (pSrc[10] >> 1) & 0x7);
   pf->xmcr0[10] =(short)( (pSrc[10] & 0x1) << 2);
   pf->xmcr0[10]|=(short)( (pSrc[11] >> 6) & 0x3);
   pf->xmcr0[11] =(short)( (pSrc[11] >> 3) & 0x7);
   pf->xmcr0[12] =(short)( pSrc[11] & 0x7);
   pf->Ncr1      =(short)( (pSrc[12] >> 1) & 0x7F);
   pf->bcr1      =(short)( (pSrc[12] & 0x1) << 1);
   pf->bcr1     |=(short)( (pSrc[13] >> 7) & 0x1);
   pf->Mcr1      =(short)( (pSrc[13] >> 5) & 0x3);
   pf->xmaxc1    =(short)( (pSrc[13] & 0x1F) << 1);
   pf->xmaxc1   |=(short)( (pSrc[14] >> 7) & 0x1);
   pf->xmcr1[0]  =(short)( (pSrc[14] >> 4) & 0x7);
   pf->xmcr1[1]  =(short)( (pSrc[14] >> 1) & 0x7);
   pf->xmcr1[2]  =(short)( (pSrc[14] & 0x1) << 2);
   pf->xmcr1[2] |=(short)( (pSrc[15] >> 6) & 0x3);
   pf->xmcr1[3]  =(short)( (pSrc[15] >> 3) & 0x7);
   pf->xmcr1[4]  =(short)( pSrc[15] & 0x7);
   pf->xmcr1[5]  =(short)( (pSrc[16] >> 5) & 0x7);
   pf->xmcr1[6]  =(short)( (pSrc[16] >> 2) & 0x7);
   pf->xmcr1[7]  =(short)( (pSrc[16] & 0x3) << 1);
   pf->xmcr1[7] |=(short)( (pSrc[17] >> 7) & 0x1);
   pf->xmcr1[8]  =(short)( (pSrc[17] >> 4) & 0x7);
   pf->xmcr1[9]  =(short)( (pSrc[17] >> 1) & 0x7);
   pf->xmcr1[10] =(short)( (pSrc[17] & 0x1) << 2);
   pf->xmcr1[10]|=(short)( (pSrc[18] >> 6) & 0x3);
   pf->xmcr1[11] =(short)( (pSrc[18] >> 3) & 0x7);
   pf->xmcr1[12] =(short)( pSrc[18] & 0x7);
   pf->Ncr2      =(short)( (pSrc[19] >> 1) & 0x7F);
   pf->bcr2      =(short)( (pSrc[19] & 0x1) << 1);
   pf->bcr2     |=(short)( (pSrc[20] >> 7) & 0x1);
   pf->Mcr2      =(short)( (pSrc[20] >> 5) & 0x3);
   pf->xmaxc2    =(short)( (pSrc[20] & 0x1F) << 1);
   pf->xmaxc2   |=(short)( (pSrc[21] >> 7) & 0x1);
   pf->xmcr2[0]  =(short)( (pSrc[21] >> 4) & 0x7);
   pf->xmcr2[1]  =(short)( (pSrc[21] >> 1) & 0x7);
   pf->xmcr2[2]  =(short)( (pSrc[21] & 0x1) << 2);
   pf->xmcr2[2] |=(short)( (pSrc[22] >> 6) & 0x3);
   pf->xmcr2[3]  =(short)( (pSrc[22] >> 3) & 0x7);
   pf->xmcr2[4]  =(short)( pSrc[22] & 0x7);
   pf->xmcr2[5]  =(short)( (pSrc[23] >> 5) & 0x7);
   pf->xmcr2[6]  =(short)( (pSrc[23] >> 2) & 0x7);
   pf->xmcr2[7]  =(short)( (pSrc[23] & 0x3) << 1);
   pf->xmcr2[7] |=(short)( (pSrc[24] >> 7) & 0x1);
   pf->xmcr2[8]  =(short)( (pSrc[24] >> 4) & 0x7);
   pf->xmcr2[9]  =(short)( (pSrc[24] >> 1) & 0x7);
   pf->xmcr2[10] =(short)( (pSrc[24] & 0x1) << 2);
   pf->xmcr2[10] |=(short)( (pSrc[25] >> 6) & 0x3);
   pf->xmcr2[11]  =(short)( (pSrc[25] >> 3) & 0x7);
   pf->xmcr2[12]  =(short)( pSrc[25] & 0x7);
   pf->Ncr3       =(short)( (pSrc[26] >> 1) & 0x7F);
   pf->bcr3       =(short)( (pSrc[26] & 0x1) << 1);
   pf->bcr3      |=(short)( (pSrc[27] >> 7) & 0x1);
   pf->Mcr3       =(short)( (pSrc[27] >> 5) & 0x3);
   pf->xmaxc3     =(short)( (pSrc[27] & 0x1F) << 1);
   pf->xmaxc3    |=(short)( (pSrc[28] >> 7) & 0x1);
   pf->xmcr3[0]   =(short)( (pSrc[28] >> 4) & 0x7);
   pf->xmcr3[1]   =(short)( (pSrc[28] >> 1) & 0x7);
   pf->xmcr3[2]   =(short)( (pSrc[28] & 0x1) << 2);
   pf->xmcr3[2]  |=(short)( (pSrc[29] >> 6) & 0x3);
   pf->xmcr3[3]   =(short)( (pSrc[29] >> 3) & 0x7);
   pf->xmcr3[4]   =(short)( pSrc[29] & 0x7);
   pf->xmcr3[5]   =(short)( (pSrc[30] >> 5) & 0x7);
   pf->xmcr3[6]   =(short)( (pSrc[30] >> 2) & 0x7);
   pf->xmcr3[7]   =(short)( (pSrc[30] & 0x3) << 1);
   pf->xmcr3[7]  |=(short)( (pSrc[31] >> 7) & 0x1);
   pf->xmcr3[8]   =(short)( (pSrc[31] >> 4) & 0x7);
   pf->xmcr3[9]   =(short)( (pSrc[31] >> 1) & 0x7);
   pf->xmcr3[10]  =(short)( (pSrc[31] & 0x1) << 2);
   pf->xmcr3[10] |=(short)( (pSrc[32] >> 6) & 0x3);
   pf->xmcr3[11]  =(short)( (pSrc[32] >> 3) & 0x7);
   pf->xmcr3[12]  =(short)( pSrc[32] & 0x7);

   return;
}
__INLINE short Rand_16s(short *seed) /* G.729 */
{

  *seed = (short)(*seed * 31821 + 13849);

  return(*seed);
}
static int Rand_1_6(short *pseed)/* generate random number from 1..6*/
{
  short tmp;
   tmp = Rand_16s(pseed);/*1<=x<=6*/
   tmp = (short)((((tmp&0x7fff) *6)>>14)+1);
   if(tmp>=6) {
      tmp=6;
   }
   return tmp;
}
static int Rand_0_3(short *pseed)/* generate random number from 1..6*/
{
  short tmp;
   tmp = Rand_16s(pseed);/*0<=x<=3*/
   tmp = (short)((((tmp&0x7fff) *3)>>14)&0x0003);
   return tmp;
}
static void generateNoise(short *pseed,short *source) /*  ref vector unpacked bitstream */
{
short i;
  frame *fptr = (frame*)source;/* to input SID frame */
/*  for(i=0;i<8;i++)
    LARc[i] =  LARc[i]; used as is. gsm06.12 clause 6.1 */
  for(i=0;i<13;i++)
      fptr-> xmcr0[i] = (short)Rand_1_6(pseed);/*1<=x<=6*/
   for(i=0;i<13;i++)
      fptr-> xmcr1[i] = (short)Rand_1_6(pseed);/*1<=x<=6*/
   for(i=0;i<13;i++)
      fptr-> xmcr2[i] = (short)Rand_1_6(pseed);/*1<=x<=6*/
   for(i=0;i<13;i++)
      fptr-> xmcr3[i] = (short)Rand_1_6(pseed);/*1<=x<=6*/
   fptr-> Mcr0 = (short)Rand_0_3(pseed);/*0<=x<=3*/
   fptr-> Mcr1 = (short)Rand_0_3(pseed);
   fptr-> Mcr2 = (short)Rand_0_3(pseed);
   fptr-> Mcr3 = (short)Rand_0_3(pseed);

   fptr-> bcr0 = 0;
   fptr-> bcr1 = 0;
   fptr-> bcr2 = 0;
   fptr-> bcr3 = 0;

   fptr-> Ncr0 = 40;
   fptr-> Ncr1 = 120;
   fptr-> Ncr2 = 40;
   fptr-> Ncr3 = 120;

/*   fptr-> xmaxc0 =  xmaxc0;
   fptr-> xmaxc1 =  xmaxc1;
   fptr-> xmaxc2 =  xmaxc2;
   fptr-> xmaxc3 =  xmaxc3; used as is*/
}
static void mute(short *pseed,short *pSrc){
   frame *fptr = (frame*)pSrc;
   fptr-> Mcr0 = (short)Rand_0_3(pseed);/*0<=x<=3*/
   fptr-> Mcr1 = (short)Rand_0_3(pseed);
   fptr-> Mcr2 = (short)Rand_0_3(pseed);
   fptr-> Mcr3 = (short)Rand_0_3(pseed);

   fptr-> xmaxc0 -= 4;/* down to zero*/
   if(fptr-> xmaxc0<0)
       fptr-> xmaxc0 = 0;
   fptr-> xmaxc1 -= 4;
   if(fptr-> xmaxc1<0)
       fptr-> xmaxc1 = 0;
   fptr-> xmaxc2 -= 4;
   if(fptr-> xmaxc2<0)
       fptr-> xmaxc2 = 0;
   fptr-> xmaxc3 -= 4;
   if(fptr-> xmaxc3<0)
       fptr-> xmaxc3 = 0;
}

void R2B(const short *pSrc, /*  ref vector unpacked bitstream */
              unsigned char *pDst)/*  packed bitstream  */
{
const frame *pf = (frame*)pSrc;
   pDst[0]  =(uchar)( (pf->LARc[0] >> 2) & 0xF);
   pDst[1]  =(uchar)( ((pf->LARc[0] & 0x3) << 6) | (pf->LARc[1] & 0x3F));
   pDst[2]  =(uchar)( ((pf->LARc[2] & 0x1F) << 3)| ((pf->LARc[3] >> 2) & 0x7));
   pDst[3]  =(uchar)( ((pf->LARc[3] & 0x3) << 6) | ((pf->LARc[4] & 0xF) << 2) | ((pf->LARc[5] >> 2) & 0x3));
   pDst[4]  =(uchar)( ((pf->LARc[5] & 0x3) << 6) | ((pf->LARc[6] & 0x7) << 3) | (pf->LARc[7] & 0x7));
   pDst[5]  =(uchar)( ((pf->Ncr0 & 0x7F) << 1)  | ((pf->bcr0 >> 1) & 0x1));
   pDst[6]  =(uchar)( ((pf->bcr0 & 0x1) << 7)   | ((pf->Mcr0 & 0x3) << 5) | ((pf->xmaxc0 >> 1) & 0x1F));
   pDst[7]  =(uchar)( ((pf->xmaxc0 & 0x1) << 7)| ((pf->xmcr0[0] & 0x7) << 4)| ((pf->xmcr0[1] & 0x7) << 1)|
              ((pf->xmcr0[2] >> 2) & 0x1));
   pDst[8]  =(uchar)( ((pf->xmcr0[2] & 0x3) << 6)| ((pf->xmcr0[3] & 0x7) << 3)| (pf->xmcr0[4] & 0x7));
   pDst[9]  =(uchar)( ((pf->xmcr0[5] & 0x7) << 5)| ((pf->xmcr0[6] & 0x7) << 2)| ((pf->xmcr0[7] >> 1) & 0x3));
   pDst[10] =(uchar)( ((pf->xmcr0[7] & 0x1) << 7)| ((pf->xmcr0[8] & 0x7) << 4)| ((pf->xmcr0[9] & 0x7) << 1)|
              ((pf->xmcr0[10] >> 2) & 0x1));
   pDst[11] =(uchar)( ((pf->xmcr0[10] & 0x3) << 6)| ((pf->xmcr0[11] & 0x7) << 3)| (pf->xmcr0[12] & 0x7));
   pDst[12] =(uchar)( ((pf->Ncr1 & 0x7F) << 1)  | ((pf->bcr1 >> 1) & 0x1));
   pDst[13] =(uchar)( ((pf->bcr1 & 0x1) << 7)   | ((pf->Mcr1 & 0x3) << 5)| ((pf->xmaxc1 >> 1) & 0x1F));
   pDst[14] =(uchar)( ((pf->xmaxc1 & 0x1) << 7)| ((pf->xmcr1[0] & 0x7) << 4)| ((pf->xmcr1[1] & 0x7) << 1)|
              ((pf->xmcr1[2] >> 2) & 0x1));
   pDst[15] =(uchar)( ((pf->xmcr1[2] & 0x3) << 6)| ((pf->xmcr1[3] & 0x7) << 3)| (pf->xmcr1[4] & 0x7));
   pDst[16] =(uchar)( ((pf->xmcr1[5] & 0x7) << 5)| ((pf->xmcr1[6] & 0x7) << 2)| ((pf->xmcr1[7] >> 1) & 0x3));
   pDst[17] =(uchar)( ((pf->xmcr1[7] & 0x1) << 7)| ((pf->xmcr1[8] & 0x7) << 4)|
              ((pf->xmcr1[9] & 0x7) << 1)| ((pf->xmcr1[10] >> 2) & 0x1));
   pDst[18] =(uchar)( ((pf->xmcr1[10] & 0x3) << 6)| ((pf->xmcr1[11] & 0x7) << 3)| (pf->xmcr1[12] & 0x7));
   pDst[19] =(uchar)( ((pf->Ncr2 & 0x7F) << 1)  | ((pf->bcr2 >> 1) & 0x1));
   pDst[20] =(uchar)( ((pf->bcr2 & 0x1) << 7)   | ((pf->Mcr2 & 0x3) << 5)| ((pf->xmaxc2 >> 1) & 0x1F));
   pDst[21] =(uchar)( ((pf->xmaxc2 & 0x1) << 7)| ((pf->xmcr2[0] & 0x7) << 4)| ((pf->xmcr2[1] & 0x7) << 1)|
              ((pf->xmcr2[2] >> 2) & 0x1));
   pDst[22] =(uchar)( ((pf->xmcr2[2] & 0x3) << 6)| ((pf->xmcr2[3] & 0x7) << 3)| (pf->xmcr2[4] & 0x7));
   pDst[23] =(uchar)( ((pf->xmcr2[5] & 0x7) << 5)| ((pf->xmcr2[6] & 0x7) << 2)| ((pf->xmcr2[7] >> 1) & 0x3));
   pDst[24] =(uchar)( ((pf->xmcr2[7] & 0x1) << 7)| ((pf->xmcr2[8] & 0x7) << 4)| ((pf->xmcr2[9] & 0x7) << 1)|
              ((pf->xmcr2[10] >> 2) & 0x1));
   pDst[25] =(uchar)( ((pf->xmcr2[10] & 0x3) << 6) | ((pf->xmcr2[11] & 0x7) << 3)| (pf->xmcr2[12] & 0x7));
   pDst[26] =(uchar)( ((pf->Ncr3 & 0x7F) << 1)   | ((pf->bcr3 >> 1) & 0x1));
   pDst[27] =(uchar)( ((pf->bcr3 & 0x1) << 7)    | ((pf->Mcr3 & 0x3) << 5) | ((pf->xmaxc3 >> 1) & 0x1F));
   pDst[28] =(uchar)( ((pf->xmaxc3 & 0x1) << 7) | ((pf->xmcr3[0] & 0x7) << 4) | ((pf->xmcr3[1] & 0x7) << 1)|
              ((pf->xmcr3[2] >> 2) & 0x1));
   pDst[29] =(uchar)( ((pf->xmcr3[2] & 0x3) << 6) | ((pf->xmcr3[3] & 0x7) << 3) | (pf->xmcr3[4] & 0x7));
   pDst[30] =(uchar)( ((pf->xmcr3[5] & 0x7) << 5) | ((pf->xmcr3[6] & 0x7) << 2) | ((pf->xmcr3[7] >> 1) & 0x3));
   pDst[31] =(uchar)( ((pf->xmcr3[7] & 0x1) << 7) | ((pf->xmcr3[8] & 0x7) << 4) | ((pf->xmcr3[9] & 0x7) << 1)|
              ((pf->xmcr3[10] >> 2) & 0x1));
   pDst[32] =(uchar)( ((pf->xmcr3[10] & 0x3) << 6) | ((pf->xmcr3[11] & 0x7) << 3) | (pf->xmcr3[12] & 0x7));
}

static int is_bitstream_frame_homing(short *src, int len)
{
  int    i,k=0;
  static __ALIGN32 CONST int maskaTable[76] = {6, 6, 5, 5, 4, 4, 3, 3,7, 2, 2, 6, 3, 3, 3, 3,3, 3, 3, 3, 3, 3, 3, 3,
                          3,7, 2, 2, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,7, 2, 2, 6, 3, 3,
                          3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,7, 2, 2, 6, 3, 3, 3,3, 3, 3, 3, 3, 3,
                          3, 3, 3, 3};
  static __ALIGN32 CONST short maska[] ={
        0x0009,  /* LARc[1]  */
        0x0017,  /* LARc[2]  */
        0x000f,  /* LARc[3]  */
        0x0008,  /* LARc[4]  */
        0x0007,  /* LARc[5]  */
        0x0003,  /* LARc[6]  */
        0x0003,  /* LARc[7]  */
        0x0002,  /* LARc[8]  */
        0x0028,  /* LTP lag  */
        0x0000,  /* LTP gain */
        0x0000,  /* RPE grid */
        0x0000,  /* block amplitude */
        0x0004,  /* RPE pulse 0 */
        0x0004,  /* RPE pulse 1 */
        0x0004,  /* RPE pulse 2 */
        0x0004,  /* RPE pulse 3 */
        0x0004,  /* RPE pulse 4 */
        0x0004,  /* RPE pulse 5 */
        0x0004,  /* RPE pulse 6 */
        0x0004,  /* RPE pulse 7 */
        0x0004,  /* RPE pulse 8 */
        0x0004,  /* RPE pulse 9 */
        0x0004,  /* RPE pulse 10 */
        0x0004,  /* RPE pulse 11 */
        0x0004,  /* RPE pulse 12 */
        0x0028,  /* LTP lag  */
        0x0000,  /* LTP gain */
        0x0000,  /* RPE grid */
        0x0000,  /* block amplitude */
        0x0004,  /* RPE pulse 0 */
        0x0004,  /* RPE pulse 1 */
        0x0004,  /* RPE pulse 2 */
        0x0004,  /* RPE pulse 3 */
        0x0004,  /* RPE pulse 4 */
        0x0004,  /* RPE pulse 5 */
        0x0004,  /* RPE pulse 6 */
        0x0004,  /* RPE pulse 7 */
        0x0004,  /* RPE pulse 8 */
        0x0004,  /* RPE pulse 9 */
        0x0004,  /* RPE pulse 10 */
        0x0004,  /* RPE pulse 11 */
        0x0004,  /* RPE pulse 12 */
        0x0028,  /* LTP lag  */
        0x0000,  /* LTP gain */
        0x0000,  /* RPE grid */
        0x0000,  /* block amplitude */
        0x0004,  /* RPE pulse 0 */
        0x0004,  /* RPE pulse 1 */
        0x0004,  /* RPE pulse 2 */
        0x0004,  /* RPE pulse 3 */
        0x0004,  /* RPE pulse 4 */
        0x0004,  /* RPE pulse 5 */
        0x0004,  /* RPE pulse 6 */
        0x0004,  /* RPE pulse 7 */
        0x0004,  /* RPE pulse 8 */
        0x0004,  /* RPE pulse 9 */
        0x0004,  /* RPE pulse 10 */
        0x0004,  /* RPE pulse 11 */
        0x0004,  /* RPE pulse 12 */
        0x0028,  /* LTP lag  */
        0x0000,  /* LTP gain */
        0x0000,  /* RPE grid */
        0x0000,  /* block amplitude */
        0x0004,  /* RPE pulse 0 */
        0x0004,  /* RPE pulse 1 */
        0x0004,  /* RPE pulse 2 */
        0x0004,  /* RPE pulse 3 */
        0x0003,  /* RPE pulse 4 */
        0x0004,  /* RPE pulse 5 */
        0x0004,  /* RPE pulse 6 */
        0x0004,  /* RPE pulse 7 */
        0x0004,  /* RPE pulse 8 */
        0x0004,  /* RPE pulse 9 */
        0x0004,  /* RPE pulse 10 */
        0x0004,  /* RPE pulse 11 */
        0x0004}; /* RPE pulse 12 */
   for(i = 0; i < len; i++) {
      k = ((src[i] & ~(~0 << maskaTable[i])) ^ maska[i]);
      if(k) break;
   }
   return !k;
}
static __ALIGN32 CONST frame silenceFrame = {
  42,39,21,10,9,4,3,2,
  0,
  40,
  1,
  0,
  3,4,3,4,4,3,3,3,3,4,4,3,3,

  0,
  40,
  1,
  0,
  3,4,3,4,4,3,3,3,3,4,4,3,3,

  0,
  40,
  1,
  0,
  3,4,3,4,4,3,3,3,3,4,4,3,3,

  0,
  40,
  1,
  0,
  3,4,3,4,4,3,3,3,3,4,4,3,3
};

static USC_Status Decode(USC_Handle handle, USC_Bitstream *in, USC_PCMStream *out)
{
    GSMFR_Handle_Header *gsmfr_header;
    GSMFRDecoder_Obj *DecObj;
    unsigned char *srcFrame;
    int bfi;
    IPP_ALIGNED_ARRAY(16, short, workBuff, GSMFR_INT_FRAME_LEN);
    IPP_ALIGNED_ARRAY(16, unsigned char, workBuff2, GSMFR_PACKED_FRAME_LEN);

    gsmfr_header = (GSMFR_Handle_Header*)handle;
    DecObj = (GSMFRDecoder_Obj *)((char*)handle + sizeof(GSMFR_Handle_Header));

    out->bitrate = in->bitrate;

    if(in->frametype > 2){/* it's the bad frame, BFI=1. That's my own temporary flag BFI defenition. TBD. iryzhac */
        bfi=1;
        srcFrame = workBuff2;
        in->nbytes=0;
    }else{
        bfi=0;
        srcFrame = (unsigned char *)in->pBuffer;
        in->nbytes=GSMFR_PACKED_FRAME_LEN;
    }
    if(!bfi){/* store good frame for the subsequent lost SID or speech frame case*/
        ippsCopy_8u(srcFrame,gsmfr_header->validFrame,GSMFR_PACKED_FRAME_LEN);
        gsmfr_header->lostFrames = 0;
        gsmfr_header->validFrames = 1;
    }else{/* the lost frame case */
        ++gsmfr_header->lostFrames;
        if(gsmfr_header->lostFrames==1){
           if(gsmfr_header->validFrames){/* repeat the first lost speech or SID frame */
              ippsCopy_8u(gsmfr_header->validFrame,srcFrame,GSMFR_PACKED_FRAME_LEN);
           }else{
              R2B((const short *)&silenceFrame, srcFrame );
/*              printf( "Bad first input frame\n");
              return 0;*/
           }
        }else{/* second and next lost speech or SID frame, mute procedure to be applied  */
           if(gsmfr_header->lostFrames>16){/* 320ms passed since first bad frame */
              R2B((const short *)&silenceFrame, srcFrame );
           }else{
              B2R(gsmfr_header->validFrame, workBuff );
              mute(&gsmfr_header->seed,workBuff);
              R2B(workBuff, gsmfr_header->validFrame );
              srcFrame = gsmfr_header->validFrame;
           }
        }
    }
    B2R(srcFrame, workBuff );
    if(in->frametype == 0){/* SID frame */
        generateNoise(&gsmfr_header->seed,workBuff);/* comfort noise generation on current SID*/
    }else{
        gsmfr_header->seed=INIT_SEED;
    }
    if(gsmfr_header->fReset_old == 1) {
        gsmfr_header->fReset=is_bitstream_frame_homing(workBuff, 25);
    }
    if(gsmfr_header->fReset && gsmfr_header->fReset_old) {
        ippsSet_16s( EHF_MASK, (Ipp16s*) out->pBuffer, (GSMFR_EXT_FRAME_LEN*sizeof(short))>>1 );
    } else {
        R2B( workBuff, srcFrame );
        if(apiGSMFRDecode(DecObj,srcFrame,(Ipp16s*)out->pBuffer) != APIGSMFR_StsNoErr){
            return USC_NoOperation;
        }
    }
    if(!gsmfr_header->fReset_old) {
        gsmfr_header->fReset=is_bitstream_frame_homing(workBuff, 76);
    }

    if(gsmfr_header->fReset) {
        apiGSMFRDecoder_Init(DecObj, &gsmfr_header->params);
        gsmfr_header->seed=INIT_SEED;
    }
    gsmfr_header->fReset_old = gsmfr_header->fReset;
    out->nbytes = GSMFR_EXT_FRAME_LEN*sizeof(short);

    return USC_NoError;
}

static int CheckRate_GSMFR(int rate_bps)
{
    int rate;

    switch(rate_bps) {
      case 13000:  rate = 0; break;
      default: rate = -1; break;
    }
    return rate;
}

static USC_Status CalsOutStreamSize(const USC_Option *options, int nbytesSrc, int *nbytesDst)
{
   int nBlocks, nSamples;

   if(options->modes.vad>2) return USC_UnsupportedVADType;

   if(options->direction==0) { /*Encode: src - PCMStream, dst - bitstream*/
      nSamples = nbytesSrc / (GSMFR_BITS_PER_SAMPLE >> 3);
      nBlocks = nSamples / GSMFR_EXT_FRAME_LEN;

      if (0 == nBlocks) return USC_NoOperation;

      if (0 != nSamples % GSMFR_EXT_FRAME_LEN) {
         /* Add another block to hold the last compressed fragment*/
         nBlocks++;
      }

      *nbytesDst = nBlocks * (GSMFR_PACKED_FRAME_LEN);
   } else if(options->direction==1) {/*Decode: src - bitstream, dst - PCMStream*/
      nBlocks = nbytesSrc / (GSMFR_PACKED_FRAME_LEN);

      if (0 == nBlocks) return USC_NoOperation;

      nSamples = nBlocks * GSMFR_EXT_FRAME_LEN;
      *nbytesDst = nSamples * (GSMFR_BITS_PER_SAMPLE >> 3);
   } else if(options->direction==2) {/* Both: src - PCMStream, dst - PCMStream*/
      nSamples = nbytesSrc / (GSMFR_BITS_PER_SAMPLE >> 3);
      nBlocks = nSamples / GSMFR_EXT_FRAME_LEN;

      if (0 == nBlocks) return USC_NoOperation;

      if (0 != nSamples % GSMFR_EXT_FRAME_LEN) {
         /* Add another block to hold the last compressed fragment*/
         nBlocks++;
      }
      *nbytesDst = nBlocks * GSMFR_EXT_FRAME_LEN * (GSMFR_BITS_PER_SAMPLE >> 3);
   } else return USC_NoOperation;

   return USC_NoError;
}
static USC_Status GetOutStreamSize(const USC_Option *options, int bitrate, int nbytesSrc, int *nbytesDst)
{
   int bitrate_idx;

   if(options==NULL) return USC_BadDataPointer;
   if(nbytesDst==NULL) return USC_BadDataPointer;
   if(nbytesSrc <= 0) return USC_NoOperation;

   bitrate_idx = CheckRate_GSMFR(bitrate);
    if(bitrate_idx < 0) return USC_UnsupportedBitRate;

   return CalsOutStreamSize(options, nbytesSrc, nbytesDst);
}

USC_Status SetFrameSize(const USC_Option *options, USC_Handle handle, int frameSize)
{
   if(options==NULL) return USC_BadDataPointer;
   if(handle==NULL) return USC_InvalidHandler;
   if(frameSize==0) return USC_NoOperation;

   return USC_NoError;
}
