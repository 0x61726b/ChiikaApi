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
#include "Request\GetAnimeList.h"
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

	}
	void OnError(RequestInterface*)
	{

	}
};

int main()
{
	char szFileName[MAX_PATH];

	GetModuleFileNameA(NULL, szFileName, MAX_PATH);

	std::string pathToExecutable = szFileName;
	std::string dir = pathToExecutable.substr(0, pathToExecutable.find_last_of("\\"));

	Root r;
	r.Initialize(dir);
	UserInfo ui;
	ui.UserName = testUserName;
	ui.Pass = testPass;
	r.m_pLocalData->SetUserInfo(ui);
	
	GetAnimeListRequest req;
	req.Initialize();
	req.SetOptions();
	req.Initiate();
	


	while(true)
	{

	}
	/*r.Destroy();*/

    return 0;
}
