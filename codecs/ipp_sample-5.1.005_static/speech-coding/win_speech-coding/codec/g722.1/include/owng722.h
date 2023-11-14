/*/////////////////////////////////////////////////////////////////////////////
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2005-2006 Intel Corporation. All Rights Reserved.
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
// Purpose: G.722.1 speech codec: internal definitions.
//
*/

#ifndef _OWN_G722_H_
#define _OWN_G722_H_

#if defined( _WIN32_WCE)
#pragma warning( disable : 4505 )
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ipp_w7.h>
#include <ipps.h>
#include "ippsc.h"
#include "g722.h"

#include "scratchmem.h"

#define   G722_CODECFUN(type,name,arg)                extern type name arg

typedef struct {
   Ipp16s *pBitstream;
   Ipp16s curWord;
   Ipp16s bitCount;
   Ipp16s curBitsNumber;
   Ipp16s nextBit;
}SBitObj;

#define DCT_LENGTH G722_DCT_LENGTH
#define FRAMESIZE G722_FRAMESIZE

#define NUM_CATEGORIES  8                                  /* G */
#define CAT_CONTROL_BITS 4                                 /* 7 */
#define CAT_CONTROL_NUM  16                                /* 2 */
#define REG_NUM  14                                        /* 2 */
#define REG_SIZE  20                                       /* . */
#define NUMBER_OF_VALID_COEFS   (REG_NUM * REG_SIZE)       /* 1 */
#define REG_POW_TABLE_SIZE 64                              /*   */
#define REG_POW_TABLE_NUM_NEGATIVES 24                     /* C */
#define CAT_CONTROL_MAX 32                                 /* O */
#define ESF_ADJUSTMENT_TO_RMS_INDEX (9-2)                  /* N */
#define REG_POW_STEPSIZE_DB 3.010299957                    /* S */
#define ABS_REG_POW_LEVELS  32                             /* T */
#define DIFF_REG_POW_LEVELS 24                             /* A */
#define DRP_DIFF_MIN -12                                   /* N */
#define DRP_DIFF_MAX 11                                    /* T */
#define MAX_NUM_BINS 14                                    /* S */
#define MAX_VECTOR_DIMENSION 5                             /* . */

extern CONST Ipp16s cnstDiffRegionPowerBits_G722[REG_NUM][DIFF_REG_POW_LEVELS];
extern CONST Ipp16s cnstVectorDimentions_G722[NUM_CATEGORIES];
extern CONST Ipp16s cnstNumberOfVectors_G722[NUM_CATEGORIES];
extern CONST Ipp16s cnstMaxBin_G722[NUM_CATEGORIES];
extern CONST Ipp16s cnstMaxBinInverse_G722[NUM_CATEGORIES];

typedef struct {
   int                 objSize;
   int                 key;
   int                 mode;          /* mode's */
   int                 res;           /* reserved*/
}own_G722_Obj_t;

struct _G722Encoder_Obj {
   own_G722_Obj_t    *objPrm;
   Ipp16s  history[FRAMESIZE];
};
struct _G722Decoder_Obj {
   own_G722_Obj_t* objPrm;
   Ipp16s prevScale;
   Ipp16s vecOldMlt[DCT_LENGTH];
   Ipp16s vecOldSmpls[DCT_LENGTH>>1];
   Ipp16s randVec[4];
   SBitObj bitObj;
};

Ipp16s GetFrameRegionsPowers(Ipp16s* pMlt, Ipp16s scale, Ipp16s* pDrpNumBits,
         Ipp16u *pDrpCodeBits, Ipp16s *pRegPowerIndices);

void MltQquantization(Ipp16s nBitsAvailable, Ipp16s* pMlt, Ipp16s *pRegPowerIndices,
         Ipp16s *pPowerCtgs, Ipp16s *pCtgBalances, Ipp16s *pCtgCtrl,
         int *pRegMltBitCounts, Ipp32u *pRegMltBits);

void ExpandBitsToWords(Ipp32u *pRegMltBits,int *pRegMltBitCounts, Ipp16s *pDrpNumBits,
         Ipp16u *pDrpCodeBits, Ipp16s *pDst, Ipp16s ctgCtrl, Ipp16s bitFrameSize);

void NormalizeWndData(Ipp16s* pWndData, Ipp16s* pScale);

void EncodeFrame(Ipp16s bitFrameSize, Ipp16s* pMlt, Ipp16s sacle, Ipp16s* pDst);

void DecodeFrame(SBitObj* bitObj, Ipp16s* randVec, Ipp16s* pMlt, Ipp16s* pScale,
         Ipp16s* pOldScale, Ipp16s *pOldMlt, Ipp16s errFlag);

Ipp16s ExpandIndexToVector(Ipp16s index, Ipp16s* pVector, Ipp16s ctgNumber);

void CategorizeFrame(Ipp16s nBitsAvailable, Ipp16s *pRmsIndices,
         Ipp16s *pPowerCtgs, Ipp16s *pCtgBalances);

void GetPowerCategories(Ipp16s* pRmsIndices, Ipp16s nAccessibleBits,
         Ipp16s *pPowerCategs, Ipp16s* pOffset);

void GetCtgPoweresBalances(Ipp16s *pPowerCtgs, Ipp16s *pCtgBalances,
         Ipp16s *pRmsIndices, Ipp16s nBitsAvailable, Ipp16s offset);

void RecoveStdDeviations(SBitObj *bitObj, Ipp16s *pStdDeviations,
         Ipp16s *pRegPowerIndices, Ipp16s *pScale);

void DecodeBitsToMlt(SBitObj* bitObj, Ipp16s* randVec, Ipp16s* pStdDeviations,
         Ipp16s* pPowerCtgs, Ipp16s* pMlt);

void ArrangePowerCategories(Ipp16s ctgCtrl, Ipp16s* pPowerCtgs, Ipp16s* pCtgBalances);

void TestFrame(SBitObj* bitObj, Ipp16s errFlag, Ipp16s ctgCtrl,
         Ipp16s *pRegPowerIndices);

void ProcessErrors(Ipp16s* pErrFlag, Ipp16s* pMlt, Ipp16s* pOldMlt,
         Ipp16s* pScale, Ipp16s* pOldScale);


__INLINE Ipp16s Exp_16s_Pos(Ipp16s x){
   Ipp16s i;
   if (x == 0) return 0;
   for(i = 0; x < (Ipp16s)0x4000; i++) x <<= 1;
   return i;
}


__INLINE void GetNextBit(SBitObj *bitObj){
   Ipp16s temp;

   if (bitObj->bitCount == 0){
      bitObj->curWord = *bitObj->pBitstream++;
      bitObj->bitCount = 16;
   }
   bitObj->bitCount--;
   temp = (short)(bitObj->curWord >> bitObj->bitCount);
   bitObj->nextBit = (Ipp16s )(temp & 1);
}

__INLINE Ipp32u GetNextBits(SBitObj* bitObj, int n){
   int i;
   Ipp32u word=0;

   for (i=0; i<n; i++){
      GetNextBit(bitObj);
        word <<= 1;
        word |= bitObj->nextBit;
   }
   bitObj->curBitsNumber = (Ipp16s)(bitObj->curBitsNumber - n);
   return word;
}

__INLINE Ipp16s GetRand(Ipp16s *randVec){
   Ipp16s rndWord;

   rndWord = (Ipp16s) (randVec[0] + randVec[3]);
   if (rndWord < 0){
      rndWord++;
   }
   randVec[3] = randVec[2];
   randVec[2] = randVec[1];
   randVec[1] = randVec[0];
   randVec[0] = rndWord;
   return(rndWord);
}


#endif /* _OWN_G722_H_*/
