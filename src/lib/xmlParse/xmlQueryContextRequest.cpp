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

#include "xmlParse/XmlNode.h"

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "ngsi/Request.h"
#include "ngsi/ContextAttribute.h"
#include "ngsi/EntityId.h"
#include "ngsi/Restriction.h"
#include "ngsi10/QueryContextRequest.h"
#include "xmlParse/XmlNode.h"
#include "xmlParse/xmlQueryContextRequest.h"
#include "xmlParse/xmlParse.h"



/* ****************************************************************************
*
* entityId - 
*/
static int entityId(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an entityId"));

  reqDataP->qcr.entityIdP = new EntityId();
  reqDataP->qcr.res.entityIdVector.push_back(reqDataP->qcr.entityIdP);

  std::string es = entityIdParse(QueryContext, node, reqDataP->qcr.entityIdP);
  
  if (es != "OK")
    reqDataP->errorString = es;

  return 0;
}



/* ****************************************************************************
*
* entityIdId - 
*/
static int entityIdId(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an entityId:id: '%s'", node->value()));

  reqDataP->qcr.entityIdP->id = node->value();

  return 0;
}



/* ****************************************************************************
*
* attribute - 
*/
static int attribute(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an attribute"));

  reqDataP->qcr.res.attributeList.push_back(node->value());

  return 0;
}



/* ****************************************************************************
*
* restriction - 
*/
static int restriction(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a restriction"));

  LM_T(LmtRestriction, ("Got a restriction - from value %d", reqDataP->qcr.res.restrictions));
  ++reqDataP->qcr.res.restrictions;
  LM_T(LmtRestriction, ("Got a restriction - to value %d", reqDataP->qcr.res.restrictions));

  return 0;
}



/* ****************************************************************************
*
* attributeExpression - 
*/
static int attributeExpression(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got an attributeExpression: '%s'", node->value()));

  reqDataP->qcr.res.restriction.attributeExpression.set(node->value());
  return 0;
}



/* ****************************************************************************
*
* operationScope - 
*/
static int operationScope(xml_node<>* node, ParseData* reqDataP)
{
  Scope* newScopeP = new Scope();

  LM_T(LmtParse, ("Got an operationScope"));
  reqDataP->qcr.scopeP = newScopeP;
  reqDataP->qcr.res.restriction.scopeVector.push_back(reqDataP->qcr.scopeP);

  return 0;
}



/* ****************************************************************************
*
* scopeType - 
*/
static int scopeType(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a scopeType: '%s'", node->value()));

  reqDataP->qcr.scopeP->type = node->value();
  return 0;
}



/* ****************************************************************************
*
* scopeValue - 
*/
static int scopeValue(xml_node<>* node, ParseData* reqDataP)
{
  LM_T(LmtParse, ("Got a scopeValue: '%s'", node->value()));

  reqDataP->qcr.scopeP->value = node->value();

  return 0;
}



/* ****************************************************************************
*
* qcrInit - 
*/
void qcrInit(ParseData* reqDataP)
{
  qcrRelease(reqDataP);

  reqDataP->qcr.entityIdP            = NULL;
  reqDataP->qcr.scopeP               = NULL;
  reqDataP->errorString              = "";

  reqDataP->qcr.res.restrictions     = 0;
  reqDataP->qcr.res.restriction.attributeExpression.set("");
}



/* ****************************************************************************
*
* qcrRelease - 
*/
void qcrRelease(ParseData* reqDataP)
{
  reqDataP->qcr.res.release();
}



/* ****************************************************************************
*
* qcrCheck - 
*/
std::string qcrCheck(ParseData* reqDataP, ConnectionInfo* ciP)
{
  return reqDataP->qcr.res.check(QueryContext, ciP->outFormat, "", reqDataP->errorString, 0);
}


#define PRINTF printf
/* ****************************************************************************
*
* qcrPresent - 
*/
void qcrPresent(ParseData* reqDataP)
{
  if (!lmTraceIsSet(LmtDump))
    return;

  PRINTF("\n\n");
  reqDataP->qcr.res.present("");
}



/* ****************************************************************************
*
* qcrParseVector - 
*/
XmlNode qcrParseVector[] = 
{
  { "/queryContextRequest",                                             nullTreat            },
  { "/queryContextRequest/entityIdList",                                nullTreat            },
  { "/queryContextRequest/entityIdList/entityId",                       entityId             },
  { "/queryContextRequest/entityIdList/entityId/id",                    entityIdId           },
  { "/queryContextRequest/attributeList",                               nullTreat            },
  { "/queryContextRequest/attributeList/attribute",                     attribute            },
  { "/queryContextRequest/restriction",                                 restriction          },
  { "/queryContextRequest/restriction/attributeExpression",             attributeExpression  },
  { "/queryContextRequest/restriction/scope",                           nullTreat            },
  { "/queryContextRequest/restriction/scope/operationScope",            operationScope       },
  { "/queryContextRequest/restriction/scope/operationScope/scopeType",  scopeType            },
  { "/queryContextRequest/restriction/scope/operationScope/scopeValue", scopeValue           },

  { "LAST", NULL }
};
