/******************************************************************************
** Copyright (c) 2013-2017 Intel Corporation All Rights Reserved
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License.
**
** You may obtain a copy of the License at
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
** WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**
** See the License for the specific language governing permissions and
** limitations under the License.
**
******************************************************************************/

#ifndef _ESIF_UF_APP_
#define _ESIF_UF_APP_

#include "esif.h"
#include "esif_sdk_iface_app.h"
#include "esif_participant.h"
#include "esif_pm.h"

#define MAX_DOMAIN_ENTRY 10
#define APP_DOMAIN_VERSION 1

/*
** Hierchary
** Application
**      Participants
**          Domain
*/

/* Map App Domain Handle To ESIF Domain Data */
typedef struct _t_AppDomainDataMap {
	UInt8  fAppDomainId;
	void   *fAppDomainHandle;
	AppDomainDataPtr  fAppDomainDataPtr;
	esif_string       fQualifier;
	UInt16  fQualifierId;
} AppDomainDataMap, *AppDomainDataMapPtr, **AppDomainDataMapPtrLocation;

/* Map App Domain Handle To ESIF Participant Data */
typedef struct _t_AppParticipantDataMap {
	EsifUpPtr  fUpPtr;
	void       *fAppParticipantHandle;

	/* Each Participant May Have Many Domains */
	AppDomainDataMap  fDomainData[MAX_DOMAIN_ENTRY];
} AppParticipantDataMap, *AppParticipantDataMapPtr, *AppParticipantDataMapPtrLocation;

/* Map App Data To ESIF Prticipants */
typedef struct _t_EsifApp {
	void  *fHandle;				/* The Application Handle Opaque To Us */
	AppInterface  fInterface;			/* The Application Interface */
	EsifString    fLibNamePtr;			/* The Name Of The Library To Load */
	esif_lib_t    fLibHandle;	/* Loadable Library Handle */

	/* Each Application May Have Many Participants */
	AppParticipantDataMap  fParticipantData[MAX_PARTICIPANT_ENTRY];

	/* State information for pausing initialization */
	Bool appCreationDone;
	Bool partRegDone;
	Bool iteratorValid;
	UfPmIterator upIter;
	EsifUpPtr upPtr;
} EsifApp, *EsifAppPtr, **EsifAppPtrLocation;

#ifdef __cplusplus
extern "C" {
#endif

eEsifError EsifAppCreateParticipant(const EsifAppPtr appPtr, const EsifUpPtr upPtr);

eEsifError EsifAppDestroyParticipant(const EsifAppPtr appPtr, const EsifUpPtr upPtr);

/* Control */
eEsifError EsifAppStart(EsifAppPtr appPtr);
eEsifError EsifAppStop(EsifAppPtr appPtr);

/* Application Event Functions */
eEsifError EsifApp_RegisterEvent(
	const void *esifHandle,
	const void *appHandle,
	const void *upHandle,
	const void *domainHandle,
	const EsifDataPtr eventGuidPtr
	);

eEsifError EsifApp_UnregisterEvent(
	const void *esifHandle,
	const void *appHandle,
	const void *upHandle,
	const void *domainHandle,
	const EsifDataPtr eventGuidPtr
	);

eEsifError EsifApp_ReceiveEvent(
	const void *esifHandle,
	const void *appHandle,
	const void *upHandle,
	const void *domainHandle,
	const EsifDataPtr eventDataPtr,
	const EsifDataPtr eventGuidPtr
	);

eEsifError EsifApp_ReceiveCommand(
	const void *esifHandle,
	const void *appHandle,
	const UInt32 argc,
	const EsifDataPtr argv,
	EsifDataPtr response
	);

AppParticipantDataMapPtr EsifApp_GetParticipantDataMapFromHandle(
	const EsifAppPtr appPtr,
	const void *participantHandle
	);

AppDomainDataMapPtr EsifApp_GetDomainDataMapFromHandle(
	const AppParticipantDataMapPtr upMapPtr,
	const void *domainHandle
	);


#ifdef __cplusplus
}
#endif

#endif	// _ESIF_UF_APP_

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

