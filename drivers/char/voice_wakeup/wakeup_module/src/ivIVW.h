/*----------------------------------------------+
 |
 |		ivIVW.h - LowEnd API
 |
 |		Copyright (c) 1999-2018, iFLYTEK Ltd.
 |		All rights reserved.
 |
 +----------------------------------------------*/

#if !defined(IVW_TEAM__2014_03_04__IVW__H)
#define IVW_TEAM__2014_03_04__IVW__H

#include "ivIvwDefine.h"
#include "ivPlatform.h"
#include "ivIvwErrorCode.h"
#include "ivwConfig.h"

/* Definition of IVW parameters and parameter value */
/* Parameter ID for Ivw WakeUp Threshold*/
#define IVW_CM_THRESHOLD            (2011)
	#define CM_THRESH_DEFALT	    ((ivUInt32)0)

#define IVW_SNR_ON                  (2012)
    #define CM_SNR_ON_DEFALT	    ((ivUInt32)1)

/* --------------信噪比检测相关参数.Begin----------------------------- */
#define IVW_SNR_THRESH              (2013) /* 信噪比门限阀值参数 */
    #define IVW_SNR_THRESH_DEFAULT      ((ivUInt32)105) /* 信噪比默认门限 */

#define IVW_SNR_SKIPNOISE_MS        (2014) /* 噪音段跳过的毫秒数 */
    #define IVW_SNR_SKIPNOISE_MS_DEFAULT    ((ivUInt32)0)

#define IVW_SNR_NOISE_MS            (2015) /* 噪音段毫秒数 */
    #define IVW_SNR_NOISE_MS_DEFAULT        ((ivUInt32)400)
    #define IVW_SNR_NOISE_MS_MIN            ((ivUInt32)100) /* 用于检测的噪音段最小毫秒数，如果小于该值，则不进行检测 */

#define IVW_SNR_CMTHR_DIF           (2016) /*  */
    #define IVW_SNR_CMTHR_DIF_DEFAULT       ((ivUInt32)100)  /* 当唤醒后CM得分和用户设定的CM阀值差距在20分内,则进行信噪比检测 */

#define IVW_SNR_ENDSIL_MS           (2017) /*  */
    #define IVW_SNR_ENDSIL_MS_DEFAULT       ((ivUInt32)30) /* 设置唤醒词后必须接的静音段的时长.单位:毫秒 */
/* --------------信噪比检测相关参数.End----------------------------- */

#define IVW_KEYWORD_MAX_MS          (2018)  /* 设置支持的唤醒词的最大时长.单位:毫秒 */
    #define IVW_KEYWORD_MAX_MS_DEFAULT      ((ivUInt32)4000)

#define IVW_KEYWORD_MIN_MS          (2019)  /* 设置支持的唤醒词的最大时长.单位:毫秒 */
    #define IVW_KEYWORD_MIN_MS_DEFAULT      ((ivUInt32)100)

#define IVW_DOUBLE_THRESH_INTER_MS      ((ivUInt16)5000)      /* 唤醒双门限的时间间隔.单位:毫秒 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Interface */
/* Create Ivw object */
ivStatus
ivCall
IvwCreate(
		  ivPointer		pObj,			    /* IVW Object */
		  ivSize ivPtr	pnObjSize,		    /* [In/Out] Size of IVW object */
		  ivPointer		pResidentRAM,		/* Resident RAM */
		  ivPUInt16		pnResidentRAMSize,	/* [In/Out] Size of Resident RAM */
		  ivCPointer	pWakeupRes,			/* [In]  key Resource */
		  ivUInt16		nWakeupNetworkID	/* [In] resource file network ID */
		  );

ivStatus
ivCall
IvwCreateEx(
          ivPointer		pObj,			/* IVW Object */
          ivSize ivPtr	pnObjSize,		/* [In/Out] Size of IVW object */
          ivPointer		pResidentRAM,		/* Resident RAM */
          ivPUInt16		pnResidentRAMSize,	/* [In/Out] Size of Resident RAM */
          ivCPointer ivPtr	ppWakeupRes,	/* [In] wakeup Resource.support for multiple */
          ivUInt16      nWakeupResNum       /* [In] wakeup resource number */
          );

ivStatus
ivCall
IvwSetParam(
			ivPointer	pObj,           /* IVW Object */
			ivUInt32	nParamID,		/* Parameter ID */
			ivInt32		nParamValue,	/* Parameter Value */
			ivUInt32	iKeyWordID,		/* valid when nParamID=IVW_CM_THRESHOLD. Keyword ID. start with 0. */
            ivUInt32    iResID          /* valid when nParamID=IVW_CM_THRESHOLD. Res ID. start with 0. */
			);

ivStatus
ivCall
IvwSetThresh(
             ivPointer  pObj,           /* IVW Object */
             ivInt16    nLThresh,       /* Param: lower cm thresh */
             ivInt16    nHThresh,       /* Param: higher cm thresh */
             ivUInt16   nIntervalMS,    /* Param: Double thresh interval time(millisecond)*/
             ivUInt32   iKeyWordID,     /* Keyword ID */
             ivUInt32   iResID          /* Res ID. start with 0. */
             );


ivStatus
ivCall
IvwRunStep(
		   ivPointer	pObj,	    /* IVW Object */
		   ivPInt16		pnCMScore ,  /* IVW CMScore */
		   ivPInt16		pnKeywordID /* IVW multi wakeup keyword ID*/
		   );

ivStatus
ivCall
IvwRunStepEx(
           ivPointer	pObj,           /* IVW Object */
           ivPInt16		pnCMScore ,     /* [out].IVW CMScore */
           ivPInt16     pnResID,        /* [out] */
           ivPInt16		pnKeywordID,    /* []IVW multi wakeup keyword ID*/
           ivPUInt32    pnStartMS,
           ivPUInt32    pnEndMS
           );

/* Append Audio data to the Ivw object,In general, Call this function in record thread */
ivStatus
ivCall
IvwAppendAudioData(
			  ivPointer			pObj,	/* IVW Object */
			  ivCPointer		pData,		/* [In] Pointer to the address of PCM data buffer */
			  ivUInt16			nSamples	/* [In] Specifies the length, in samples, of PCM data */
			  );

/* Reset object */
ivStatus
ivCall
IvwReset(
		   ivPointer	pObj		/* IVW Object */
		   );

/* Get SDK Version */
ivStatus
ivCall
IvwGetVersion(
              ivPUInt16		piMajor,
              ivPUInt16		piMinor,
              ivPUInt16		piRevision
              );

#if IVW_SUPPORT_ENROLLVP
/* Create VP object */
ivStatus
ivCall
IvwCreateVPObj(
               ivPointer    pObj,
               ivPUInt32    pnObjSize,
               ivCPointer   pUBMMdl
               );

/* Start one process of enroll */
ivStatus
ivCall
IvwStartEnroll(
               ivPointer   pObj
               );

ivStatus
ivCall
IvwEnrollStep(
              ivPointer	    pObj,
              ivPInt16		pnCMScore,
              ivPointer*    ppWakeupRes,
              ivPUInt32     pnWakeupResSize,
              ivPUInt32     pnStartMS,
              ivPUInt32     pnEndMS,
              ivPInt16		pnVpThresh
              );

ivStatus
ivCall
IvwMergeRes(
            ivCPointer	pRes1,		    /* I: 待合并唤醒资源1 */
            ivCPointer  pRes2,			/* I: 待合并唤醒资源2 */
            ivPointer	pMergeRes,		/* O: 合并后的唤醒资源 */
            ivPUInt32   pnMergeResSize	/* I/O: 输入pMergeRes大小，输出实际使用的pMergeRes大小.(单位：字节) */
            );

#endif /* #if IVW_SUPPORT_ENROLLVP */

#if IVW_SUPPORT_VPMODEL_ADAPT
ivStatus
ivCall
IvwCreateVPMdlAdaptObj(
               ivPointer    pObj,
               ivPUInt32    pnObjSize,
               ivCPointer   pUBMMdl,
               ivCPointer   pWakeupRes,
               ivInt16      nKeywordID,
               ivBool       bEnableVAD
               );

ivStatus
ivCall
IvwVPMdlAdaptRunStep(
              ivPointer	    pObj,
              ivPInt16      pnCMScore,
              ivPUInt32     pnStartMS,
              ivPUInt32     pnEndMS,
              ivPointer *   ppAdaptRes,
              ivPUInt32     pnAdaptResSize
              );
#endif /* #if IVW_SUPPORT_VPMODEL_ADAPT */


/* 强定制唤醒词3遍自动更新策略 */
#if IVW_SUPPORT_MODEL_ADAPT
ivStatus
ivCall
IvwCreateMdlAdaptObj(
                       ivPointer    pObj,
                       ivPUInt32    pnObjSize,
                       ivCPointer   pWakeupRes,
                       ivInt16      nKeywordID, /* Begin index:0 */
                       ivUInt16     nAdaptTimes,
                       ivBool       bEnableVAD
                       );

ivStatus
ivCall
IvwStartAdapt(
               ivPointer   pObj
               );

ivStatus
ivCall
IvwMdlAdaptRunStep(
                   ivPointer                pObj,
                   PMdlAdaptResult ivPtr    ppResult		/* [Out] To Receive model adapt result */
                   );
#endif /* #if IVW_SUPPORT_MODEL_ADAPT */

#if IVW_SUPPORT_ENROLLVP || IVW_SUPPORT_MODEL_ADAPT
ivStatus
ivCall
IvwEndData(
           ivPointer	pObj		/* IVW Object */
           );
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !defined(IVW_TEAM__2014_03_04__IVW__H) */
