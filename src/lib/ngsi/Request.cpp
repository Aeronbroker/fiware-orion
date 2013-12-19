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
#include "Request.h"



/* ****************************************************************************
*
* requestType - 
*/
const char* requestType(RequestType rt)
{
  switch (rt)
  {
  case RegisterContext:                             return "RegisterContextRequest";
  case RegisterResponse:                            return "RegisterContextResponse";
  case DiscoverContextAvailability:                 return "DiscoverContextAvailabilityRequest";
  case SubscribeContextAvailability:                return "SubscribeContextAvailabilityRequest";
  case UpdateContextAvailabilitySubscription:       return "UpdateContextAvailabilitySubscriptionRequest";
  case UnsubscribeContextAvailability:              return "UnsubscribeContextAvailabilityRequest";
  case NotifyContextAvailability:                   return "NotifyContextAvailabilityRequest";
  case QueryContext:                                return "QueryContextRequest";
  case SubscribeContext:                            return "SubscribeContextRequest";
  case UpdateContextSubscription:                   return "UpdateContextSubscriptionRequest";
  case UnsubscribeContext:                          return "UnsubscribeContextRequest";
  case NotifyContext:                               return "NotifyContextRequest";
  case UpdateContext:                               return "UpdateContextRequest";

  case ContextEntitiesByEntityId:                   return "ContextEntitiesByEntityId";
  case ContextEntityAttributes:                     return "ContextEntityAttributes";
  case EntityByIdAttributeByName:                   return "EntityByIdAttributeByName";
  case ContextEntityTypes:                          return "ContextEntityTypes";
  case ContextEntityTypeAttributeContainer:         return "ContextEntityTypeAttributeContainer";
  case ContextEntityTypeAttribute:                  return "ContextEntityTypeAttribute";
  case Ngsi9SubscriptionsConvOp:                    return "Ngsi9SubscriptionsConvOp";

  case IndividualContextEntity:                     return "IndividualContextEntity";
  case IndividualContextEntityAttributes:           return "IndividualContextEntityAttributes";
  case AttributeValueInstance:                      return "AttributeValueInstance";
  case IndividualContextEntityAttribute:            return "IndividualContextEntityAttribute";
  case UpdateContextElement:                        return "UpdateContextElement";
  case AppendContextElement:                        return "AppendContextElement";
  case UpdateContextAttribute:                      return "UpdateContextAttribute";
  case Ngsi10ContextEntityTypes:                    return "Ngsi10ContextEntityTypes";
  case Ngsi10ContextEntityTypesAttributeContainer:  return "Ngsi10ContextEntityTypesAttributeContainer";
  case Ngsi10ContextEntityTypesAttribute:           return "Ngsi10ContextEntityTypesAttribute";
  case Ngsi10SubscriptionsConvOp:                   return "Ngsi10SubscriptionsConvOp";

  case LogRequest:                                  return "Log";
  case VersionRequest:                              return "Version";
  case StatisticsRequest:                           return "Statistics";
  case ExitRequest:                                 return "Exit";
  case LeakRequest:                                 return "Leak";
  case InvalidRequest:                              return "InvalidRequest";

  case RtSubscribeContextAvailabilityResponse:           return "SubscribeContextAvailabilityResponse";
  case RtUpdateContextAvailabilitySubscriptionResponse:  return "UpdateContextAvailabilitySubscriptionResponse";
  case RtUnsubscribeContextAvailabilityResponse:         return "UnsubscribeContextAvailabilityResponse";
  case RtUnsubscribeContextResponse:                     return "UnsubscribeContextResponse";
  case RtSubscribeResponse:                              return "SubscribeResponse";
  case RtSubscribeError:                                 return "SubscribeError";
  }

  return "";
}
