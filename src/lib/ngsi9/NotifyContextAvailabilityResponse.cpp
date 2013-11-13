/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Fermín Galán & Ken Zangelin
*/
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/tag.h"
#include "common/globals.h"
#include "ngsi/StatusCode.h"
#include "ngsi/ErrorCode.h"
#include "ngsi9/NotifyContextAvailabilityResponse.h"
#include "rest/HttpStatusCode.h"



/* ****************************************************************************
*
* NotifyContextAvailabilityResponse::NotifyContextAvailabilityResponse - 
*/
NotifyContextAvailabilityResponse::NotifyContextAvailabilityResponse()
{
   responseCode.fill(SccOk, "", "");
}



/* ****************************************************************************
*
* NotifyContextAvailabilityResponse::NotifyContextAvailabilityResponse - 
*/
NotifyContextAvailabilityResponse::NotifyContextAvailabilityResponse(StatusCode& sc)
{
   responseCode = sc;
}



/* ****************************************************************************
*
* NotifyContextAvailabilityResponse::NotifyContextAvailabilityResponse -
*/
NotifyContextAvailabilityResponse::NotifyContextAvailabilityResponse(ErrorCode& ec)
{
   responseCode.fill(&ec);
}



/* ****************************************************************************
*
* NotifyContextAvailabilityResponse::render -
*/
std::string NotifyContextAvailabilityResponse::render(RequestType requestType, Format format, std::string indent)
{
  std::string out = "";
  std::string tag = "notifyContextAvailabilityResponse";

  responseCode.tagSet("responseCode");

  out += startTag(indent, tag, format, false);
  out += responseCode.render(format, indent + "  ");
  out += endTag(indent, tag, format);

  return out;
}



/* ****************************************************************************
*
* NotifyContextAvailabilityResponse::present -
*/
void NotifyContextAvailabilityResponse::present(std::string indent)
{
  PRINTF("%sNotifyContextAvailabilityResponse:", indent.c_str());
  responseCode.present(indent + "  ");
  PRINTF("\n");
}



/* ****************************************************************************
*
* NotifyContextAvailabilityResponse::release -
*/
void NotifyContextAvailabilityResponse::release(void)
{
  responseCode.release();
}

