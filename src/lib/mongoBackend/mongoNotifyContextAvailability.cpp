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
* Author: Fermín Galán
*/

#include "mongoNotifyContextAvailability.h"

#include "mongoBackend/MongoGlobal.h"
#include "mongoBackend/MongoCommonRegister.h"
#include "ngsi9/RegisterContextRequest.h"
#include "ngsi9/RegisterContextResponse.h"

/* ****************************************************************************
*
* mongoNofityContextAvailability -
*/
HttpStatusCode mongoNotifyContextAvailability(NotifyContextAvailabilityRequest* requestP, NotifyContextAvailabilityResponse* responseP) {

    /* We ignore "subscriptionId" and "originator" in the request, as we don't have anything interesting
     * to do with them */

    /* Process each ContextRegistrationElement to create a "fake" RegisterContextRequest */
    RegisterContextRequest rcr;
    for (unsigned int ix= 0; ix < requestP->contextRegistrationResponseVector.size(); ++ix) {
        ContextRegistration* crP = &requestP->contextRegistrationResponseVector.get(ix)->contextRegistration;
        rcr.contextRegistrationVector.push_back(crP);
    }

    /* notifyContextAvailability doesn't include duration information, so we will use the defaulf */
    rcr.duration.set(DEFAULT_DURATION);

    /* We use processRegisterContext() function. Note that in this case the response is not needed, so we will
     * only use it to conform to function signature. In addition, take into account that from a registerContext
     * point of view, notifyContextAvailability is considered as a new registration (as no registratinId is
     * received in the notification message) */
    RegisterContextResponse rcres;
    processRegisterContext(&rcr, &rcres, NULL);

    responseP->responseCode.fill(SccOk);

    return SccOk;
}

