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
#include "api_mal_search.h"
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
		MOCK_METHOD0(GetResponse, ChiString());
		MOCK_METHOD0(Work, void());
		MOCK_METHOD0(Initialize, void());
		MOCK_METHOD0(CreateThread, void());
	};
	class MockDatabase : public LocalDataManager
	{
	public:
		MOCK_METHOD0(GetUserInfo, UserInfo());
		MOCK_METHOD1(SetUserInfo, void(UserInfo i));
	};
	class MockRequestManager : public RequestManager
	{
	public:
		MOCK_METHOD1(ProcessRequest, void(ThreadedRequest*));
	};
	class Parser
	{
	public:
		Parser(ThreadedRequest* r, LocalDataManager* d)
			: _request(r),_database(d) {}
		void Parse()
		{
			if (!_request)
			{
				return;
			}
			if (_request->Name == "Verify")
			{
				ParseUserVerify();
			}
		}
		bool ParseUserVerify()
		{
			std::string response = _request->GetResponse();
			_database->GetUserInfo();

			//ToDo(arkenthear): Parse now.

			UserInfo ui;
			ui.UserName = testUserName;
			ui.UserId = testUserId;
			_database->SetUserInfo(ui);

			ResultUser = ui;

			return true;
		}
		UserInfo ResultUser;
		ThreadedRequest* _request;
		LocalDataManager* _database;

	};

}

//Fetch login
//Write expected result
TEST(MalTest, UserVerify)
{
	UserInfo inputUser;
	inputUser.UserName = testUserName;

	UserInfo defaultUser;
	defaultUser.UserName = "default";

	std::string response = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<user>"
		"<id>4987289</id>"
		"<username>chiikatestacc1</username>"
		"</user>";

	UserInfo expectedUserInfo;
	expectedUserInfo.UserName = testUserName;
	expectedUserInfo.UserId = 4987289;

	RequestMock mockRequest;
	
	mockRequest.Name = "Verify";

	MockDatabase mockDb;
	mockDb.m_UserDetailedInfo = (inputUser);

	MockRequestManager mockReqManager;


	
	EXPECT_CALL(mockReqManager, ProcessRequest(_))
		.Times(1);

	EXPECT_CALL(mockRequest, Initialize())
		.Times(1);

	//Procedure starts at Root
	Root root;
	root.PostRequest(&mockReqManager,&mockRequest);

	//Initialize the process
	RequestManager rm;
	rm.ProcessRequest(&mockRequest);


	

	ON_CALL(mockDb, GetUserInfo())
		.WillByDefault(Return(defaultUser));

	EXPECT_CALL(mockRequest, GetResponse()).Times(1)
		.WillOnce(::Return(response));

	ON_CALL(mockDb, GetUserInfo())
		.WillByDefault(Return(defaultUser));

	EXPECT_CALL(mockDb, GetUserInfo()).Times(AtLeast(1));

	EXPECT_CALL(mockDb, SetUserInfo(_)).Times(1);

	
	

	Parser pr(&mockRequest,&mockDb);
	pr.Parse();

	ON_CALL(mockDb, GetUserInfo())
		.WillByDefault(Return(expectedUserInfo));

	EXPECT_CALL(mockDb, GetUserInfo()).Times(AtLeast(1));


	EXPECT_EQ(expectedUserInfo.UserName, mockDb.GetUserInfo().UserName);
	EXPECT_EQ(expectedUserInfo.UserId, mockDb.GetUserInfo().UserId);

}