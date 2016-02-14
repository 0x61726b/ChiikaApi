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
#include "Root/Root.h"
#include "Request/RequestManager.h"
#include "Database/LocalDataManager.h"
#include "Request/MalManager.h"
//----------------------------------------------------------------------------
using namespace ChiikaApi;
std::string SearchKeywordAnime = "Oregairu";
std::string testUserName = "arkenthera";
std::string testPass = "";

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

int main()
{
	//char szFileName[MAX_PATH];

	//GetModuleFileNameA(NULL, szFileName, MAX_PATH);

	//std::string pathToExecutable = szFileName;
	//std::string dir = pathToExecutable.substr(0, pathToExecutable.find_last_of("\\"));

	//dir = dir + "\\..\\";
	//TestEventListener tel;

	//Root r;
	//r.Initialize(true, 1, "arkenthera", "123asd456", dir.c_str());


	//r.InitDatabase();
	////r.GetRequestManager()->GetMyAnimelist(&tel);
	////r.GetRequestManager()->AnimePageScrape(&tel,31414);
	////r.GetRequestManager()->DownloadSenpaiData(&tel);
	//


	//getchar();
	////r.Destroy();

	return 0;
}