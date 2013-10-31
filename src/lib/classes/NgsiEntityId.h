#ifndef NGSI_ENTITY_ID_H
#define NGSI_ENTITY_ID_H

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

#include "Format.h"
#include "NgsiBase.h"
#include "NgsiString.h"

namespace cb
{

namespace ngsi
{


/* ****************************************************************************
*
* NgsiEntityId - 
*/
class NgsiEntityId: public NgsiBase
{
   NgsiString    _id;
   NgsiString    _type;
   NgsiString    _isPattern;
   
public:
   NgsiEntityId(std::string id, std::string type, std::string isPattern);

   void         init(NgsiContainer container, bool isRequest, NgsiServiceType serviceType, bool mandatory, cb::common::Format format, std::string tag, std::string indent);
   std::string  render(void);
   std::string  check(void);
   void         present(void);
   void         release(void);
};

}
}

#endif
