//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2015  Alperen Gezer
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or
//(at your option) any later version.
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along
//with this program; if not, write to the Free Software Foundation, Inc.,
//51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/
//----------------------------------------------------------------------------
#ifndef __Mock_ParsingManager_h__
#define __Mock_ParsingManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Request\RequestManager.h"
#include "Seasons\SeasonManager.h"
#include "gmock\gmock.h"
#include "ThirdParty\jsoncpp\json\json.h"
#include <Windows.h>
//----------------------------------------------------------------------------
using namespace ChiikaApi;
namespace Tests
{
	class MalApiExport BaseTest : public ::testing::Test
	{
	protected:

		
	};
	class MalApiExport ClosestAnimeTest : public ::testing::Test
	{
	protected:
		virtual void SetUp();
		virtual void TearDown();
		static void SetUpTestCase();
		static void TearDownTestCase();
		static std::vector<ChiikaApi::SenpaiItem>* AllSenpaiData;
		std::string TestTimezone;
	};

	int TestFunc(std::string s)
	{
		if(s == "UTC")
			return 0;
		if(s == "CET")
			return 1;
	}

	//Goal: Test if closest anime is correct on any timezone
	//Requirements: SenpaiData,Timezone
	TEST_F(ClosestAnimeTest,ClosestAnimeUTC)
	{
		TestTimezone = "UTC";
		
		EXPECT_EQ(0,TestFunc(TestTimezone));
	}
	TEST_F(ClosestAnimeTest,ClosestAnimeCET)
	{
		TestTimezone = "CET";
		TestFunc(TestTimezone);
		EXPECT_EQ(1,TestFunc(TestTimezone));
	}
}
//----------------------------------------------------------------------------
#endif // MOCK_PARSINGMANAGER_H
