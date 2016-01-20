//----------------------------------------------------------------------------
//Chiika Hello World
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
#include "Root\Root.h"
#include "Request\RequestManager.h"
#include "Database\LocalDataManager.h"
#include "Request\GetMyAnimelist.h"
#include "Request\AccountVerify.h"
#include "Root\ThreadManager.h"

//----------------------------------------------------------------------------
using namespace ChiikaApi;
std::string SearchKeywordAnime = "Oregairu";
std::string testUserName = "arkenthera";
std::string testPass = "123asd456";

class TestEventListener : public RequestListener
{
public:
	void OnSuccess(RequestInterface*)
	{
		int x = 0;
	}
	void OnError(RequestInterface*)
	{
		int y = 0;
	}
};
#include <thread>
#include <chrono>
#include <mutex>
int main()
{
	char szFileName[MAX_PATH];

	GetModuleFileNameA(NULL,szFileName,MAX_PATH);

	std::string pathToExecutable = szFileName;
	std::string dir = pathToExecutable.substr(0,pathToExecutable.find_last_of("\\"));

	TestEventListener tel;

	RootOptions opts;
	opts.appMode = true;
	opts.modulePath = strdup(dir.c_str());
	opts.userName = strdup(testUserName.c_str());
	opts.passWord = strdup(testPass.c_str());
	Root r;
	r.Initialize(&opts);

	r.GetRequestManager()->GetMyAnimelist(&tel);


	/*UserInfo ui;
	ui.SetKeyValue(kUserName,testUserName);
	ui.SetKeyValue(kPass,testPass);*/

	//UserInfo second = ui;

	//UserInfo third = second;

	//t x = 0;

	/*r.GetRequestManager()->VerifyUser(&tel);*/

	//std::this_thread::sleep_for(std::chrono::seconds(4));

	//AccountVerifyRequest request2;
	//request2.Initialize();
	
	//request2.SetUserInfo(ui);
	//request2.SetOptions();

	//r.m_pThreadManager->PostRequest(&request2);

	//std::this_thread::sleep_for(std::chrono::seconds(4));

	//AccountVerifyRequest request3;
	//request3.Initialize();
	
	//request3.SetUserInfo(ui);
	//request3.SetOptions();

	//r.m_pThreadManager->PostRequest(&request3);

	

	


	while(true)
	{

	}
	/*r.Destroy();*/

	return 0;
}
