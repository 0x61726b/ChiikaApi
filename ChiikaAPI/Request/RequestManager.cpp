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
#include "Stable.h"
#include "RequestManager.h"
#include "AccountVerify.h"
#include "GetMyAnimelist.h"
#include "GetMyMangalist.h"
#include "Root\Root.h"
#include "Root\ThreadManager.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	struct FtpFile {
		const char* filename;
		FILE *stream;
	};
	//----------------------------------------------------------------------------
	RequestManager::RequestManager()
	{




	}
	//----------------------------------------------------------------------------
	RequestManager::~RequestManager()
	{

	}
	//----------------------------------------------------------------------------
	void RequestManager::VerifyUser(RequestListener* listener)
	{
		AccountVerifyRequest* request = new AccountVerifyRequest;
		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		Root::Get()->GetThreadManager()->PostRequest(request);
	}

	void RequestManager::GetMyAnimelist(RequestListener* listener)
	{
		GetMyAnimeListRequest* request = new GetMyAnimeListRequest;
		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		Root::Get()->GetThreadManager()->PostRequest(request);
	}

	void RequestManager::GetMyMangalist(RequestListener* listener)
	{
		GetMyMangaListRequest* request = new GetMyMangaListRequest;
		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		Root::Get()->GetThreadManager()->PostRequest(request);
	}
	//----------------------------------------------------------------------------
}
