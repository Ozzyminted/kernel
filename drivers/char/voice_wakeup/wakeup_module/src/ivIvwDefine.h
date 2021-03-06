/*----------------------------------------------+
|
|	ivIvwDefine.h - Basic Definitions
|
|		Copyright (c) 1999-2013, iFLYTEK Ltd.
|		All rights reserved.
|
+----------------------------------------------*/

#ifndef IFLYTEK_IVW__DEFINE__H
#define IFLYTEK_IVW__DEFINE__H

#include "ivDefine.h"

/*return istatus for WakeUp*/
#define IvwErr_WakeUp				(50)
#define IvwErr_HarfWake				(51)

/* ----强/浅定制唤醒词自适应相关---- */
typedef struct tagModelAdaptResult{
    ivInt16         nCMScore;
    ivUInt32        nStartMS;
    ivUInt32        nEndMS;
    ivPointer       pAdaptedRes;
    ivUInt32        nAdaptedResSize;
}TMdlAdaptResult, ivPtr PMdlAdaptResult;
typedef TMdlAdaptResult ivCPtr PCMdlAdaptResult;

/* ---特定人唤醒词自适应相关--- */
typedef struct tagVPModelAdaptResult{
    ivInt16         nCMScore;
    ivUInt32        nStartMS;
    ivUInt32        nEndMS;
    ivPointer       pAdaptedRes;
    ivUInt32        nAdaptedResSize;
}TVPMdlAdaptResult, ivPtr PVPMdlAdaptResult;
typedef TVPMdlAdaptResult ivCPtr PCVPMdlAdaptResult;

#endif
