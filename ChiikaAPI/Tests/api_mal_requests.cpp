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
#include "api_mal_requests.h"

#include "Logging\FileHelper.h"

#ifdef YUME_PLATFORM_WIN32
#include <Windows.h>
std::string testDataDirFromExecutable = "\\..\\..\\..\\ChiikaApi\\ChiikaAPI\\Tests\\json";
#endif

#include "Root\Root.h"
#include "Request\MalManager.h"
#include "Request\GetAnimeList.h"
#include "Database\LocalDataManager.h"
using namespace ChiikaApi;
namespace
{
	class CurlMock : public ChiikaApi::CurlRequestInterface
	{
	public:
		MOCK_METHOD0(Perform,void());
		MOCK_METHOD0(GetResponse,const ChiString&());
		MOCK_METHOD1(SetUrl,void(const ChiString&));
		MOCK_METHOD1(SetAuth,void(const ChiString&));
		MOCK_METHOD2(SetMethod,void(int,const ChiString&));
		MOCK_METHOD1(SetWriteFunction,void(std::function<size_t(void *buffer,size_t size,size_t nmemb,void *stream)>*));
		MOCK_METHOD0(Initialize,void());

		MOCK_METHOD1(SetErrorCode,void(int));
		MOCK_METHOD1(SetTimeout,void(int));
		MOCK_METHOD1(SetVerbose,void(bool));
		MOCK_METHOD1(AddListener,void(CurlEventListener*));
		MOCK_METHOD1(RemoveListener,void(CurlEventListener*));
		MOCK_METHOD0(GetRequestResult,int());
	};
	class DatabaseMock : public ChiikaApi::LocalDataInterface
	{
	public:
		MOCK_METHOD0(GetUserInfo,const UserInfo&());
		MOCK_METHOD1(GetUserInfo,void(UserInfo&));
		MOCK_METHOD1(SetUserInfo,void(const ChiikaApi::UserInfo&));


		MOCK_METHOD0(SaveAnimeList,void());
		MOCK_METHOD0(SaveUserInfo,void());
		MOCK_METHOD0(SaveUpdateList,void());
		MOCK_METHOD0(SaveMangaList,void());
		MOCK_METHOD0(SaveAnimeDetails,void());
		MOCK_METHOD0(SaveSenpaiData,void());

		MOCK_METHOD0(LoadAnimeList,void());
		MOCK_METHOD0(LoadUserInfo,void());
		MOCK_METHOD0(LoadUpdateList,void());
		MOCK_METHOD0(LoadMangaList,void());
		MOCK_METHOD0(LoadAnimeDetails,void());
		MOCK_METHOD0(LoadSenpaiData,void());

		MOCK_METHOD0(Initialize,void());

		MOCK_METHOD0(SaveAll,void());

		MOCK_METHOD2(SetUserNamePass,void(ChiString,ChiString));
	};
}
namespace
{

	class RequestTests : public ::testing::Test
	{
	protected:
		// Per-test-case set-up.
		// Called before the first test in this test case.
		// Can be omitted if not needed.
		static void SetUpTestCase()
		{
			char szFileName[MAX_PATH];

			GetModuleFileNameA(NULL,szFileName,MAX_PATH);

			std::string pathToExecutable = szFileName;
			moduleDir = pathToExecutable.substr(0,pathToExecutable.find_last_of("\\"));

			std::string dir = moduleDir+ testDataDirFromExecutable;
			FileReader fr(dir + "\\getAnimeListResponse.xml");

			if(fr.Open())
			{
				fr.ReadRef(GetAnimelistResponse);
			}
		}

		// Per-test-case tear-down.
		// Called after the last test in this test case.
		// Can be omitted if not needed.
		static void TearDownTestCase()
		{

		}

		// You can define per-test set-up and tear-down logic as usual.
		void SetUp()
		{
			ui->SetUserName("chitanda");
			ui->SetPass("eru");

			EXPECT_CALL(mockCurl,Perform()).Times(1);
			EXPECT_CALL(mockCurl,SetWriteFunction(_)).Times(1);
			EXPECT_CALL(mockCurl,SetUrl(_)).Times(1);
			EXPECT_CALL(mockCurl,SetAuth(_)).Times(1);
			EXPECT_CALL(mockCurl,SetMethod(_,_)).Times(1);

			const std::string& r = GetAnimelistResponse;


			ON_CALL(mockCurl,GetResponse())
				.WillByDefault(::testing::ReturnRef(r));

			ON_CALL(mockDatabase,GetUserInfo())
				.WillByDefault(::testing::ReturnRef(*ui));



			EXPECT_CALL(mockCurl,GetResponse())
				.Times(::AtLeast(1));

		}

		virtual void TearDown()
		{
			delete ui;
			ui = NULL;
		}
		CurlMock mockCurl;
		DatabaseMock mockDatabase;
		ChiikaApi::UserInfo* ui = new UserInfo();
	public:
		static std::string GetAnimelistResponse;
		static std::string moduleDir;

	};
	std::string RequestTests::GetAnimelistResponse = "";
	std::string RequestTests::moduleDir = "";
}
TEST_F(RequestTests,GetAnimeListRequestErrorBehaviour)
{
	GetAnimeListRequest req;
	req.SetCURL(&mockCurl);
	req.SetDatabase(&mockDatabase);
	
	//req.Initialize(); Not calling this since we use mock


	EXPECT_CALL(mockCurl,GetRequestResult())
		.Times(::AtLeast(1));

	ON_CALL(mockCurl,GetRequestResult())
		.WillByDefault(::testing::Return(RequestCodes::REQUEST_ERROR | RequestCodes::CANT_RESOLVE_HOST_OR_PROXY));


	req.SetOptions();
	req.Initiate();
	req.OnError();

}

TEST_F(RequestTests,GetAnimeListRequestSuccessBehaviour)
{
	GetAnimeListRequest req;
	req.SetCURL(&mockCurl);
	req.SetDatabase(&mockDatabase);

	//req.Initialize(); Not calling this since we use mock


	EXPECT_CALL(mockDatabase,GetUserInfo(_)).Times(::AtLeast(1));
	EXPECT_CALL(mockDatabase,GetUserInfo()).Times(::AtLeast(1));
	EXPECT_CALL(mockDatabase,SetUserInfo(_)).Times(::AtLeast(1));
	EXPECT_CALL(mockDatabase,SaveAll()).Times(::AtLeast(1));

	req.SetOptions();
	req.Initiate();
	req.OnSuccess();
}