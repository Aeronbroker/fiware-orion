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
#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "rest/ConnectionInfo.h"
#include "jsonParse/jsonRequest.h"
#include "xmlParse/xmlRequest.h"
#include "xmlParse/xmlParse.h"

#include "unittest.h"



/* ****************************************************************************
*
* Tests
* - badLength_xml
* - badLength_json
* - invalidDuration_json
*
*/



/* ****************************************************************************
*
* badLength_xml - 
*/
TEST(UpdateContextSubscriptionRequest, badLength_xml)
{
  ParseData       parseData;
  ConnectionInfo  ci("", "POST", "1.1");
  const char*     infile  = "ngsi10.updateContextSubscription.subscriptionIdLength.invalid.xml";
  const char*     outfile = "ngsi10.updateContextSubscriptionResponse.subscriptionIdLengthInvalid.valid.xml";
  std::string     out;

  utInit();

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), infile)) << "Error getting test data from '" << infile << "'";
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile)) << "Error getting test data from '" << outfile << "'";

  lmTraceLevelSet(LmtDump, true);
  out = xmlTreat(testBuf, &ci, &parseData, UpdateContextSubscription, "updateContextSubscriptionRequest", NULL);
  lmTraceLevelSet(LmtDump, false);
  EXPECT_STREQ(expectedBuf, out.c_str());


  //
  // With the data obtained, render, present and release methods are exercised
  //
  UpdateContextSubscriptionRequest*  ucsrP = &parseData.ucsr.res;
  
  ucsrP->present(""); // No output

  const char*     outfile2 = "ngsi10.updateContextSubscriptionResponse.ok.valid.xml";
  const char*     outfile3 = "ngsi10.updateContextSubscriptionResponse.forcedError.valid.xml";
  const char*     outfile4 = "ngsi10.updateContextSubscriptionResponse.badDuration.valid.xml";

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  out = ucsrP->render(UpdateContextSubscription, XML, "");
  EXPECT_STREQ(expectedBuf, out.c_str());

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile3)) << "Error getting test data from '" << outfile3 << "'";
  out  = ucsrP->check(UpdateContextSubscription, XML, "", "FORCED ERROR", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile4)) << "Error getting test data from '" << outfile4 << "'";
  ucsrP->duration.set("XXXYYYZZZ");
  out  = ucsrP->check(UpdateContextSubscription, XML, "", "", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  ucsrP->present("");
  ucsrP->release();

  utExit();
}



/* ****************************************************************************
*
* badLength_json - 
*/
TEST(UpdateContextSubscriptionRequest, badLength_json)
{
  ParseData       parseData;
  ConnectionInfo  ci("", "POST", "1.1");
  std::string     out;
  const char*     infile   = "ngsi10.updateContextSubscriptionRequest.badLength.invalid.json";
  const char*     outfile1 = "ngsi10.updateContextSubscriptionRequest.badLength.expected1.valid.json";
  const char*     outfile2 = "ngsi10.updateContextSubscriptionRequest.badLength.expected2.valid.json";
  const char*     outfile3 = "ngsi10.updateContextSubscriptionRequest.badLength.expected3.valid.json";
  const char*     outfile4 = "ngsi10.updateContextSubscriptionRequest.badLength.expected4.valid.json";
  
  utInit();

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), infile)) << "Error getting test data from '" << infile << "'";

  ci.inFormat  = JSON;
  ci.outFormat = JSON;

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile1)) << "Error getting test data from '" << outfile1 << "'";
  lmTraceLevelSet(LmtDump, true);
  out = jsonTreat(testBuf, &ci, &parseData, UpdateContextSubscription, "updateContextSubscriptionRequest", NULL);
  lmTraceLevelSet(LmtDump, false);
  EXPECT_STREQ(expectedBuf, out.c_str());

  //
  // With the data obtained, render, present and release methods are exercised
  //
  UpdateContextSubscriptionRequest*  ucsrP = &parseData.ucsr.res;
  
  ucsrP->present(""); // No output

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  out = ucsrP->render(UpdateContextSubscription, JSON, "");
  EXPECT_STREQ(expectedBuf, out.c_str());

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile3)) << "Error getting test data from '" << outfile3 << "'";
  out  = ucsrP->check(UpdateContextSubscription, JSON, "", "FORCED ERROR", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  ucsrP->duration.set("XXXYYYZZZ");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile4)) << "Error getting test data from '" << outfile4 << "'";
  out  = ucsrP->check(UpdateContextSubscription, JSON, "", "", 0);
  EXPECT_STREQ(expectedBuf, out.c_str());

  ucsrP->present("");
  ucsrP->release();

  utExit();
}



/* ****************************************************************************
*
* invalidDuration_json - 
*/
TEST(UpdateContextSubscriptionRequest, invalidDuration_json)
{
  ParseData       parseData;
  ConnectionInfo  ci("", "POST", "1.1");
  const char*     infile   = "ngsi10.updateContextSubscriptionRequest.duration.invalid.json";
  const char*     outfile  = "ngsi10.updateContextSubscriptionResponse.invalidDuration.valid.json";
  
  utInit();

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), infile)) << "Error getting test data from '" << infile << "'";
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile)) << "Error getting test data from '" << outfile << "'";

  ci.inFormat  = JSON;
  ci.outFormat = JSON;

  std::string out = jsonTreat(testBuf, &ci, &parseData, UpdateContextSubscription, "updateContextSubscriptionRequest", NULL);
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}
