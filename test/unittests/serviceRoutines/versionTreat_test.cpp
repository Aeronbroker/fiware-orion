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
#include "gtest/gtest.h"

#include "serviceRoutines/versionTreat.h"
#include "rest/RestService.h"



/* ****************************************************************************
*
* rs - 
*/
static RestService rs[] = 
{
   { "GET",    VersionRequest,                        1, { "version"                                                }, "", versionTreat                              },
   { "",       InvalidRequest,                        0, {                                                          }, "", NULL                                      }
};



/* ****************************************************************************
*
* ok - 
*/
TEST(versionTreat, ok)
{
  ConnectionInfo  ci("/version",  "GET", "1.1");
  std::string     out       = restService(&ci, rs);

  // FIXME P2: Some day we'll do this ...
  //
  // char*    expected =
  //   "<orion>\n"
  //   "  <version>" ORION_VERSION "</version>\n"
  //   "  <uptime>*</uptime>"
  //   "  <git_hash>*</git_hash>\n"
  //   "  <compile_time>*</compile_time>\n"
  //   "  <compiled_by>*</compiled_by>\n"
  //   "  <compiled_in>*</compiled_in>\n"
  //   "</orion>\n";  
  // bool            match;
  // match = std::regex_match(expected, out.c_str());

  EXPECT_TRUE(strstr(out.c_str(), "<orion>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "<version>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "</version>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "<uptime>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "</uptime>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "<git_hash>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "</git_hash>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "<compile_time>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "</compile_time>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "<compiled_in>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "</compiled_in>") != NULL);
  EXPECT_TRUE(strstr(out.c_str(), "</orion>") != NULL);

  extern const char*  orionUnitTestVersion;
  std::string         expected = std::string("<version>") + orionUnitTestVersion + "</version>";
  EXPECT_TRUE(strstr(out.c_str(), expected.c_str()) != NULL);

  versionSet("1.2.3");
  out       = restService(&ci, rs);
  EXPECT_TRUE(strstr(out.c_str(), "<version>1.2.3</version>") != NULL);

  versionSet("1.2.3");
  std::string version = versionGet();
  EXPECT_EQ("1.2.3", version);
}
