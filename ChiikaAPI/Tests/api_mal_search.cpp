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
#include "Request\RequestManager.h"
//----------------------------------------------------------------------------
using namespace ChiikaApi;

namespace
{
	std::string SearchKeywordAnime = "Oregairu";
	std::string testUserName = "arkenthera";
	std::string testPass = "123asd456";

	CurlConfigOption url;
	CurlConfigOption method;
	CurlConfigOption userName;
	CurlConfigOption passWord;
	CurlConfigOptionMap options;



	class MockEventListener : public ChiikaApi::RequestListener
	{
	public:
		MOCK_METHOD1(Notify,void(ChiikaApi::ThreadedRequest*));
	};
	class MockRequest : public ChiikaApi::ThreadedRequest
	{
	public:
		MOCK_METHOD0(CreateThread,void());
		MOCK_METHOD0(DeleteThread,void());
		MOCK_METHOD0(Work,void());
	};
	void SetParams()
	{
		url.Name = "Url";
		ChiString k = (SearchKeywordAnime);
		/*k.replace(" ","+");*/
		url.Value = "http://myanimelist.net/api/anime/search.xml?q=" + k;

		method.Name = "Method";
		method.cUrlOpt = 80;

		userName.Name = "UserName";
		userName.Value = testUserName;

		passWord.Name = "PassWord";
		passWord.Value = testPass;



		options.insert(std::make_pair(url.Name,url));
		options.insert(std::make_pair(method.Name,method));
		options.insert(std::make_pair(userName.Name,userName));
		options.insert(std::make_pair(passWord.Name,passWord));
	}
}
CONDITION_VARIABLE OperationNotReady;
CRITICAL_SECTION   OperationLock;
void WaitFinished()
{
	WakeConditionVariable(&OperationNotReady);
}
TEST(DISABLED_MalApiTests,SearchAnime)
{
	MockEventListener mockListener;
	EXPECT_CALL(mockListener,Notify(_)).Times(1);

	MockRequest request;
	SetParams();


	EXPECT_CALL(request,CreateThread()).Times(AtLeast(1));
	EXPECT_CALL(request,DeleteThread()).Times(AtLeast(1));
	EXPECT_CALL(request,Work()).Times(AtLeast(1));
	request.AddListener(&mockListener);
	
	RequestManager rm;
	rm.CreateTestRequest(&request,options);

	BOOL res = SleepConditionVariableCS(&OperationNotReady,&OperationLock,10000);
	EXPECT_EQ(TRUE,res);

	//Continue this test later
}