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
* Author: Ken Zangelin
*/
#include <stdio.h>
#include <string>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "convenience/UpdateContextAttributeRequest.h"
#include "jsonParse/jsonParse.h"
#include "jsonParse/JsonNode.h"
#include "jsonParse/jsonUpdateContextAttributeRequest.h"
#include "jsonParse/jsonNullTreat.h"



/* ****************************************************************************
*
* attributeType - 
*/
static std::string attributeType(std::string path, std::string value, ParseData* reqData)
{
  reqData->upcar.res.type = value;

  return "OK";
}



/* ****************************************************************************
*
* attributeValue - 
*/
static std::string attributeValue(std::string path, std::string value, ParseData* reqData)
{
  reqData->upcar.res.contextValue = value;

  return "OK";
}



/* ****************************************************************************
*
* contextMetadata - 
*/
static std::string contextMetadata(std::string path, std::string value, ParseData* reqData)
{
  LM_T(LmtParse, ("Creating a metadata"));
  reqData->upcar.metadataP = new Metadata();
  reqData->upcar.res.metadataVector.push_back(reqData->upcar.metadataP);
  return "OK";
}



/* ****************************************************************************
*
* contextMetadataName - 
*/
static std::string contextMetadataName(std::string path, std::string value, ParseData* reqData)
{
  LM_T(LmtParse, ("Got a metadata name: '%s'", value.c_str()));
  reqData->upcar.metadataP->name = value;
  return "OK";
}



/* ****************************************************************************
*
* contextMetadataType - 
*/
static std::string contextMetadataType(std::string path, std::string value, ParseData* reqData)
{
  LM_T(LmtParse, ("Got a metadata type: '%s'", value.c_str()));
  reqData->upcar.metadataP->type = value;
  return "OK";
}



/* ****************************************************************************
*
* contextMetadataValue - 
*/
static std::string contextMetadataValue(std::string path, std::string value, ParseData* reqData)
{
  LM_T(LmtParse, ("Got a metadata value: '%s'", value.c_str()));
  reqData->upcar.metadataP->value = value;
  return "OK";
}



/* ****************************************************************************
*
* jsonUpcarParseVector -
*/
JsonNode jsonUpcarParseVector[] =
{
  { "/type",                     attributeType        },
  { "/contextValue",             attributeValue       },
  { "/metadatas",                jsonNullTreat        },
  { "/metadatas/metadata",       contextMetadata      },
  { "/metadatas/metadata/name",  contextMetadataName  },
  { "/metadatas/metadata/type",  contextMetadataType  },
  { "/metadatas/metadata/value", contextMetadataValue },
  
  { "LAST", NULL }
};



/* ****************************************************************************
*
* jsonUpcarInit -
*/
void jsonUpcarInit(ParseData* reqData)
{
}



/* ****************************************************************************
*
* jsonUpcarRelease -
*/
void jsonUpcarRelease(ParseData* reqData)
{
  reqData->upcar.res.release();
}



/* ****************************************************************************
*
* jsonUpcarCheck -
*/
std::string jsonUpcarCheck(ParseData* reqData, ConnectionInfo* ciP)
{
  return reqData->upcar.res.check(UpdateContextAttribute, ciP->outFormat, "", reqData->errorString, 0);
}



/* ****************************************************************************
*
* jsonUpcarPresent -
*/
void jsonUpcarPresent(ParseData* reqData)
{
  if (!lmTraceIsSet(LmtDump))
    return;

  PRINTF("\n\n");
  reqData->upcar.res.present("");
}

