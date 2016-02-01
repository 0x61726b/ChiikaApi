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
#include "MalUserPageScrape.h"
#include "DownloadImage.h"
#include "MalAnimePageScrape.h"


#include "Root\Root.h"
#include "Root\ThreadManager.h"
#include "Logging\LogManager.h"
#include "Settings\Settings.h"
#include "Request\MalManager.h"


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
		//Maybe somehow some objects still linger?
		RemoveThreadObjects();
	}
	//----------------------------------------------------------------------------
	void RequestManager::VerifyUser(RequestListener* listener)
	{
		AccountVerifyRequest* request = new AccountVerifyRequest;
		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		request->AddListener(this);
		chiikaNode = listener;

		ThreadManager* tm = new ThreadManager(false, request);
		m_RequestThreads.insert(RequestThreadMap::value_type(request, tm));

		GetMyAnimelist(listener);
		GetMyMangalist(listener);


	}

	void RequestManager::GetMyAnimelist(RequestListener* listener)
	{
		GetMyAnimeListRequest* request = new GetMyAnimeListRequest;
		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		request->AddListener(this);
		ThreadManager* tm = new ThreadManager(false, request);
		m_RequestThreads.insert(RequestThreadMap::value_type(request, tm));
	}

	void RequestManager::GetMyMangalist(RequestListener* listener)
	{
		GetMyMangaListRequest* request = new GetMyMangaListRequest;
		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		request->AddListener(this);
		ThreadManager* tm = new ThreadManager(false, request);
		m_RequestThreads.insert(RequestThreadMap::value_type(request, tm));
	}

	void RequestManager::MalScrape(RequestListener* listener)
	{
		MalScrapeRequest* request = new MalScrapeRequest;

		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		request->AddListener(this);

		ThreadManager* tm = new ThreadManager(false, request);
		m_RequestThreads.insert(RequestThreadMap::value_type(request, tm));
	}

	void RequestManager::DownloadImage(RequestListener* listener,
		const std::string& url,
		const std::string& file,
		const std::string& folder)
	{
		DownloadImageRequest* request = new DownloadImageRequest;

		request->Initialize();
		request->SetOptions();
		request->AddListener(listener);
		request->AddListener(this);
		request->SetUrl(url);
		request->SetFile(file, folder);

		ThreadManager* tm = new ThreadManager(false, request);
		m_RequestThreads.insert(RequestThreadMap::value_type(request, tm));
	}

	void RequestManager::OnSuccess(ChiikaApi::RequestInterface* request)
	{
		if (request->GetName() == kRequestVerify)
		{
			if (chiikaNode)
			{
				//Download user image
				std::string fileName = Root::Get()->GetUser().GetKeyValue(kUserId) + ".jpg";
				std::string folder = Root::Get()->GetAppSettings()->GetImagePath();
				std::string url = "http://cdn.myanimelist.net/images/userimages/" + Root::Get()->GetUser().GetKeyValue(kUserId);

				DownloadImage(chiikaNode,
					url,
					fileName,
					folder
					);
			}

		}

		RemoveThreadObjects();
	}

	void RequestManager::AnimePageScrape(RequestListener* listener, int AnimeId)
	{
		AnimePageScrapeRequest* request = new AnimePageScrapeRequest;

		request->SetAnimeId(AnimeId);
		request->Initialize();
		request->SetOptions();

		request->AddListener(listener);
		request->AddListener(this);

		

		Anime anime = Root::Get()->GetMyAnimelistManager()->GetAnimeById(AnimeId);

		if (anime.GetKeyValue(kSeriesImage) != kSeriesImage)
		{
			//Download anime image
			std::string fileName = std::to_string(AnimeId) + ".jpg";
			std::string folder = Root::Get()->GetAppSettings()->GetImagePath() + "anime/";
			std::string url = anime.GetKeyValue(kSeriesImage);


			DownloadImage(listener, url, fileName,folder);
			

			
		}
		ThreadManager* tm = new ThreadManager(false, request);
		m_RequestThreads.insert(RequestThreadMap::value_type(request, tm));
	}

	void RequestManager::RemoveThreadObjects()
	{
		//Guard me onee-san
		boost::mutex::scoped_lock onee(threadLock);


		//Let's not leak the memory
		//Make sure javascript side is called before getting here
		for (RequestThreadMap::iterator It = m_RequestThreads.begin(); It != m_RequestThreads.end();)
		{
			if (It->first->IsCompleted())
			{
				LOG(INFO) << "Removed thread " << It->first->GetName();
				delete It->second;
				It = m_RequestThreads.erase(It);
			}
			else
			{
				++It;
			}
		}
	}
	void RequestManager::OnError(ChiikaApi::RequestInterface*)
	{
		RemoveThreadObjects();
	}
	//----------------------------------------------------------------------------
}
