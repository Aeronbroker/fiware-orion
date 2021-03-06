#ifndef REST_H
#define REST_H

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

#include "rest/RestService.h"

#define  MAX_LEN_IP   64

/* ****************************************************************************
*
*  IpVersion -
*/
typedef enum IpVersion 
{
  IPV4     = 1,
  IPV6     = 2,
  IPDUAL   = 3
} IpVersion;



/* ****************************************************************************
*
* ipVersionUsed - 
*/
extern IpVersion  ipVersionUsed;  



/* ****************************************************************************
*
* RestServeFunction - 
*/
typedef void (*RestServeFunction)(ConnectionInfo* ciP);



/* ****************************************************************************
*
* restInit - 
*/
extern void restInit
(
   RestService*      _restServiceV,
   IpVersion         _ipVersion,
   const char*       _bindAddress,
   unsigned short    _port,
   RestServeFunction _serveFunction = NULL,
   bool              _acceptTextXml = false
);

#endif
