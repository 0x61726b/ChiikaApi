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
#include "Common/Required.h"
#include "Request\RequestManager.h"

#include "Database\LocalDataManager.h"

#include "Root\Root.h"
//----------------------------------------------------------------------------
#include <chrono>
#include <thread>
using ::testing::Not;
using ::testing::FloatEq;
using ::testing::Eq;
using ::testing::_;
using ::testing::Return;
using namespace ChiikaApi;

namespace
{
	std::string SearchKeywordAnime = "Oregairu";
	std::string testUserName = "chiikatestacc1";
	std::string testPass = "chiikatest%&";
	int			testUserId = 4987289;
}
namespace
{
	class RequestMock : public ThreadedRequest
	{
	public:
		MOCK_METHOD0(GetResponse,ChiString());
	};
	class MockDatabase : public LocalDataManager
	{
	public:
		MOCK_METHOD0(GetUserInfo,UserInfo());
		MOCK_METHOD1(SetUserInfo,void(UserInfo i));
	};
	class MockRequestManager : public RequestManager
	{
	public:
		MOCK_METHOD1(ProcessRequest,void(ThreadedRequest*));
	};
	class Parser
	{
	public:
		Parser(ThreadedRequest* r,LocalDataManager* d)
			: _request(r),_database(d) {}
		bool Parse()
		{
			if(!_request)
			{
				return false;
			}
			if(_request->Name == "Verify")
			{
				return ParseUserVerify();
			}
		}
		bool ParseUserVerify()
		{
			std::string response = _request->GetResponse();
			_database->GetUserInfo();

			//ToDo(arkenthera): Parse now.

			if(response == "Invalid Credentials")
			{
				return false;
			}

			pugi::xml_document doc;

			bool b = doc.load(response.c_str());

			if(!b)
				return false;

			pugi::xml_node  user = doc.child("user");
			ChiString userName = user.child("username").text().get();
			ChiString id = user.child("id").text().get();

			UserInfo ui;
			ui.UserName = userName;
			ui.UserId = atoi(id.c_str());
			_database->SetUserInfo(ui);

			ResultUser = ui;

			return true;
		}
		UserInfo ResultUser;
		ThreadedRequest* _request;
		LocalDataManager* _database;

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
		static void SetUpTestCase() {

		}

		// Per-test-case tear-down.
		// Called after the last test in this test case.
		// Can be omitted if not needed.
		static void TearDownTestCase() {

		}

		// You can define per-test set-up and tear-down logic as usual.
		virtual void SetUp()
		{
			//Default return val
			defaultUser.UserName = "default";
			inputUser.UserName = testUserName;
		}

		virtual void TearDown()
		{
		}
	public:
		UserInfo inputUser;
		UserInfo defaultUser;
		UserInfo expectedUserInfo;
		RequestMock mockRequest;
		MockDatabase mockDb;
		MockRequestManager mockReqManager;

		std::string Response;
	};


}
TEST_F(RequestTests,VerifySuccess)
{
	Response = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<user>"
		"<id>4987289</id>"
		"<username>chiikatestacc1</username>"
		"</user>";


	expectedUserInfo.UserName = testUserName;
	expectedUserInfo.UserId = 4987289;

	mockDb.m_UserDetailedInfo = (inputUser);
	mockRequest.Name = "Verify";

	RequestManager rm;
	rm.ProcessRequest(&mockRequest);

	ON_CALL(mockDb,GetUserInfo())
		.WillByDefault(Return(defaultUser));

	EXPECT_CALL(mockRequest,GetResponse()).Times(1)
		.WillOnce(::Return(Response));

	ON_CALL(mockDb,GetUserInfo())
		.WillByDefault(Return(defaultUser));

	EXPECT_CALL(mockDb,GetUserInfo()).Times(AtLeast(1));

	EXPECT_CALL(mockDb,SetUserInfo(_)).Times(1);




	Parser pr(&mockRequest,&mockDb);
	EXPECT_EQ(true,pr.Parse());


	EXPECT_EQ(expectedUserInfo.UserName,pr.ResultUser.UserName);
	EXPECT_EQ(expectedUserInfo.UserId,pr.ResultUser.UserId);
}
//Initialize the process

//TEST(MalTest,WrongUsername)
//{
//	UserInfo inputUser;
//	inputUser.UserName = testUserName;
//
//	UserInfo defaultUser;
//	defaultUser.UserName = "default";
//
//	std::string response = "Invalid Credentials";
//
//	UserInfo expectedUserInfo;
//	expectedUserInfo.UserName = testUserName;
//	expectedUserInfo.UserId = 4987289;
//
//	RequestMock mockRequest;
//
//	mockRequest.Name = "Verify";
//
//	MockDatabase mockDb;
//	mockDb.m_UserDetailedInfo = (inputUser);
//
//	MockRequestManager mockReqManager;
//
//
//
//	EXPECT_CALL(mockReqManager,ProcessRequest(_))
//		.Times(1);
//
//	EXPECT_CALL(mockRequest,Initialize())
//		.Times(1);
//
//	//Procedure starts at Root
//	Root root;
//	root.PostRequest(&mockReqManager,&mockRequest);
//
//	//Initialize the process
//	RequestManager rm;
//	rm.ProcessRequest(&mockRequest);
//
//	ON_CALL(mockDb,GetUserInfo())
//		.WillByDefault(Return(defaultUser));
//
//	EXPECT_CALL(mockRequest,GetResponse()).Times(1)
//		.WillOnce(::Return(response));
//
//	ON_CALL(mockDb,GetUserInfo())
//		.WillByDefault(Return(defaultUser));
//
//	EXPECT_CALL(mockDb,GetUserInfo()).Times(AtLeast(1));
//
//
//
//
//	Parser pr(&mockRequest,&mockDb);
//	EXPECT_EQ(false,pr.Parse());
//
//}