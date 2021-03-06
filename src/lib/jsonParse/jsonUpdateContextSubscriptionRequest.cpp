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
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "ngsi10/UpdateContextSubscriptionRequest.h"
#include "jsonParse/jsonNullTreat.h"
#include "jsonParse/JsonNode.h"
#include "jsonParse/jsonUpdateContextSubscriptionRequest.h"



/* ****************************************************************************
*
* duration - 
*/
static std::string duration(std::string path, std::string value, ParseData* parseDataP)
{
  std::string s;

  LM_T(LmtParse, ("Got a duration: '%s'", value.c_str()));

  parseDataP->ucsr.res.duration.set(value);

  if ((s = parseDataP->ucsr.res.duration.check(UpdateContextSubscription, JSON, "", "", 0)) != "OK")
     LM_RE(s, ("error parsing duration '%s': %s", parseDataP->ucsr.res.duration.get().c_str(), s.c_str()));

  return "OK";
}



/* ****************************************************************************
*
* restriction - 
*/
static std::string restriction(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a restriction"));

  ++parseDataP->ucsr.res.restrictions;

  return "OK";
}



/* ****************************************************************************
*
* attributeExpression - 
*/
static std::string attributeExpression(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got an attributeExpression: '%s'", value.c_str()));

  parseDataP->ucsr.res.restriction.attributeExpression.set(value);

  return "OK";
}



/* ****************************************************************************
*
* scope - 
*/
static std::string scope(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a scope"));

  parseDataP->ucsr.scopeP = new Scope();
  parseDataP->ucsr.res.restriction.scopeVector.push_back(parseDataP->ucsr.scopeP);

  return "OK";
}



/* ****************************************************************************
*
* scopeType - 
*/
static std::string scopeType(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a scope type: '%s'", value.c_str()));

  parseDataP->ucsr.scopeP->type = value;

  return "OK";
}



/* ****************************************************************************
*
* scopeValue - 
*/
static std::string scopeValue(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a scope value: '%s'", value.c_str()));

  parseDataP->ucsr.scopeP->value = value;

  return "OK";
}



/* ****************************************************************************
*
* subscriptionId - 
*/
static std::string subscriptionId(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a subscriptionId: '%s'", value.c_str()));

  parseDataP->ucsr.res.subscriptionId.set(value);

  return "OK";
}



/* ****************************************************************************
*
* notifyCondition - 
*/
static std::string notifyCondition(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a notifyCondition"));
  parseDataP->ucsr.notifyConditionP = new NotifyCondition();
  parseDataP->ucsr.res.notifyConditionVector.push_back(parseDataP->ucsr.notifyConditionP);
  return "OK";
}



/* ****************************************************************************
*
* notifyConditionRestriction - 
*/
static std::string notifyConditionRestriction(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a Notify Condition restriction"));

  parseDataP->ucsr.notifyConditionP->restriction.set(value);
  return "OK";
}



/* ****************************************************************************
*
* notifyConditionType - 
*/
static std::string notifyConditionType(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a Notify Condition Type: '%s'", value.c_str()));
  parseDataP->ucsr.notifyConditionP->type = value;
  return "OK";
}



/* ****************************************************************************
*
* condValue - 
*/
static std::string notifyConditionCondValue(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a Cond Value: '%s'", value.c_str()));
  parseDataP->ucsr.notifyConditionP->condValueList.push_back(value);
  return "OK";
}



/* ****************************************************************************
*
* throttling - 
*/
static std::string throttling(std::string path, std::string value, ParseData* parseDataP)
{
  LM_T(LmtParse, ("Got a throttling: '%s'", value.c_str()));
  parseDataP->ucsr.res.throttling.set(value);
  return "OK";
}



/* ****************************************************************************
*
* jsonUcsrParseVector -
*/
JsonNode jsonUcsrParseVector[] =
{
  { "/duration",                                               duration                   },
  { "/restriction",                                            restriction                },
  { "/restriction/attributeExpression",                        attributeExpression        },
  { "/restriction/scopes/scope",                               scope,                     },
  { "/restriction/scopes/scope/type",                          scopeType                  },
  { "/restriction/scopes/scope/value",                         scopeValue                 },
  { "/subscriptionId",                                         subscriptionId             },
  { "/notifyConditions/notifyCondition",                       notifyCondition            },
  { "/notifyConditions/notifyCondition/type",                  notifyConditionType        },
  { "/notifyConditions/notifyCondition/condValues/condValue",  notifyConditionCondValue   },
  { "/notifyConditions/notifyCondition/restriction",           notifyConditionRestriction },
  { "/throttling",                                             throttling                 },

  { "LAST", NULL }
};



/* ****************************************************************************
*
* jsonUcsrInit - 
*/
void jsonUcsrInit(ParseData* parseDataP)
{
  jsonUcsrRelease(parseDataP);

  parseDataP->ucsr.notifyConditionP       = NULL;
  parseDataP->ucsr.scopeP                 = NULL;  
  parseDataP->ucsr.res.restrictions       = 0;
  parseDataP->errorString                = "";
}



/* ****************************************************************************
*
* jsonUcsrRelease - 
*/
void jsonUcsrRelease(ParseData* parseDataP)
{
  parseDataP->ucsr.res.release();
}



/* ****************************************************************************
*
* jsonUcsrCheck - 
*/
std::string jsonUcsrCheck(ParseData* parseDataP, ConnectionInfo* ciP)
{
   std::string s;
   s = parseDataP->ucsr.res.check(UpdateContextSubscription, ciP->outFormat, "", parseDataP->errorString, 0);
   return s;
}



/* ****************************************************************************
*
* jsonUcsrPresent - 
*/
void jsonUcsrPresent(ParseData* parseDataP)
{
  printf("jsonUcsrPresent\n");

  if (!lmTraceIsSet(LmtDump))
    return;

  parseDataP->ucsr.res.present("");
}
