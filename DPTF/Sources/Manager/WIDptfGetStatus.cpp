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

#include "WIDptfGetStatus.h"
#include "DptfStatusInterface.h"
#include "EsifServicesInterface.h"

WIDptfGetStatus::WIDptfGetStatus(
	DptfManagerInterface* dptfManager,
	const eAppStatusCommand command,
	const UInt32 appStatusIn,
	EsifDataPtr appStatusOut,
	eEsifError* returnCode)
	: WorkItem(dptfManager, FrameworkEvent::DptfGetStatus)
	, m_command(command)
	, m_appStatusIn(appStatusIn)
	, m_appStatusOut(appStatusOut)
	, m_returnCode(returnCode)
{
}

WIDptfGetStatus::~WIDptfGetStatus(void)
{
}

void WIDptfGetStatus::execute(void)
{
	writeWorkItemStartingInfoMessage();

	try
	{
		getDptfManager()->getDptfStatus()->getStatus(m_command, m_appStatusIn, m_appStatusOut, m_returnCode);
	}
	catch (std::exception& ex)
	{
		writeWorkItemWarningMessage(ex, "DptfStatus::getStatus");
	}
}
