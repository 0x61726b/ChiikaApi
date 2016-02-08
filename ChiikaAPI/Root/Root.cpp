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
#include "Root/Root.h"
#include "Request/MalManager.h"
#include "Settings/Settings.h"
#include "Request/RequestManager.h"
#include "Database/LocalDataManager.h"
#include "Recognition/MediaPlayerRecognitionManager.h"
#include "Recognition/AnimeRecognition.h"
#include "Seasons/SeasonManager.h"
#include "Request\ParsingManager.h"
#include "Logging\FileHelper.h"
#include "Logging\ChiString.h"
#include "Root\ThreadManager.h"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>
//----------------------------------------------------------------------------
//Whoops..
MalApiExport ChiikaApi::Root* GlobalInstance = 0;
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	Root::Root()
	{
		InitializeNULL(m_pSettings);
		InitializeNULL(m_pLogManager);
		InitializeNULL(m_pMalManager);
		InitializeNULL(m_pSeasonManager);
		InitializeNULL(m_pMPRecognition);
		InitializeNULL(m_pRequestManager);
		InitializeNULL(m_pRecognizer);
		InitializeNULL(m_pLocalData);

		GlobalInstance = this;
	}
	//----------------------------------------------------------------------------
	void Root::Initialize(bool appMode, bool debugMode, const char* userName, const char* pass, const char* modulePath)
	{
		options.appMode = appMode;
		options.debugMode = debugMode;
		options.modulePath = modulePath;
		options.userName = userName;
		options.passWord = pass;

		log4cplus::Initializer initializer;

		const size_t cSize = strlen(modulePath);

		std::wstring wstrModulePath(cSize, L'#');

		mbstowcs(&wstrModulePath[0], modulePath, cSize);
		std::wstring log4cplusConfig;
		log4cplusConfig.append(wstrModulePath);
		log4cplusConfig.append(L"log4cplusconfig");
		log4cplus::initialize();
		log4cplus::PropertyConfigurator config(log4cplusConfig);
		config.configure();

		log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("ChiikaTrace"));
		LOG4CPLUS_INFO(logger,
			"Initializing ChiikaAPI " << std::endl << "Options : -> " << std::endl <<
			"App Mode: " << appMode <<
			std::endl << "User: " << userName << std::endl << "Module Path: " << modulePath);


		

		m_pSettings = new AppSettings("Chiika.cfg", options.modulePath);


		ChiString version = std::to_string(ChiikaApi_VERSION_MAJOR) + "." + std::to_string(ChiikaApi_VERSION_MINOR) + "." + std::to_string(ChiikaApi_VERSION_PATCH);;
		m_sVersion = version;
		m_sCommitHash = (char)ChiikaApi_COMMIT_HASH;



		m_pMalManager = new MalManager;




		m_pRequestManager = new RequestManager;


		m_pLocalData = new LocalDataManager;
		m_pLocalData->Initialize();


		if (options.userName == "" || options.passWord == "")
		{

		}
		else
		{
			m_User.SetKeyValue(kUserName, options.userName);
			m_User.SetKeyValue(kPass, options.passWord);
		}






	}
	//----------------------------------------------------------------------------
	Root::~Root()
	{
		Destroy();
	}
	//----------------------------------------------------------------------------
	void Root::Destroy()
	{
		TryDelete(m_pSettings);
		m_pSettings = 0;
		TryDelete(m_pMalManager);
		m_pMalManager = 0;
		TryDelete(m_pRequestManager);
		m_pRequestManager = 0;
		TryDelete(m_pLocalData);
		m_pLocalData = 0;
		TryDelete(m_pLogManager);
		m_pLogManager = 0;

		log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));
		logger.shutdown();
	}
	//----------------------------------------------------------------------------
	Root* Root::Get()
	{
		return GlobalInstance;
	}
	//----------------------------------------------------------------------------
	ThreadManager* Root::GetThreadManager()
	{
		return m_pThreadManager;
	}
	//----------------------------------------------------------------------------
	RequestManager* Root::GetRequestManager()
	{
		return m_pRequestManager;
	}
	//----------------------------------------------------------------------------
	LocalDataManager* Root::GetLocalDataManager()
	{
		return m_pLocalData;
	}
	//----------------------------------------------------------------------------
	MalManager* Root::GetMyAnimelistManager()
	{
		return m_pMalManager;
	}
	//----------------------------------------------------------------------------
	AppSettings* Root::GetAppSettings()
	{
		return m_pSettings;
	}
	//----------------------------------------------------------------------------
	UserInfo& Root::GetUser()
	{
		return m_User;
	}
	//----------------------------------------------------------------------------
	void Root::VerifyUser(RequestListener* listener)
	{
		m_pRequestManager->VerifyUser(listener);
	}
	//----------------------------------------------------------------------------
	void Root::GetMyAnimelist(RequestListener* listener)
	{
		m_pRequestManager->GetMyAnimelist(listener);
	}
	//----------------------------------------------------------------------------
	const AnimeList& Root::GetAnimelist()
	{
		return GetMyAnimelistManager()->GetAnimes();
	}
	//----------------------------------------------------------------------------
	void Root::GetMyMangalist(RequestListener* listener)
	{
		m_pRequestManager->GetMyMangalist(listener);
	}
	//----------------------------------------------------------------------------
	void Root::MalScrape(RequestListener* listener)
	{
		m_pRequestManager->MalScrape(listener);
	}
	//----------------------------------------------------------------------------
	void Root::DownloadImage(RequestListener* listener, const std::string& url)
	{
		//m_pRequestManager->DownloadImage(listener,url);
	}
	//----------------------------------------------------------------------------
	void Root::AnimeScrape(RequestListener* listener, int AnimeId)
	{
		m_pRequestManager->AnimePageScrape(listener, AnimeId);
	}
	//----------------------------------------------------------------------------
	void Root::MalAjax(RequestListener* listener, int AnimeId)
	{
		m_pRequestManager->MalAjax(listener, AnimeId);
	}
	//----------------------------------------------------------------------------
	void Root::SearchAnime(RequestListener* listener, int id, const char* keywords)
	{
		m_pRequestManager->SearchAnime(listener, id, keywords);
	}
	//----------------------------------------------------------------------------
	void Root::RefreshAnimeDetails(RequestListener* listener, int id)
	{
		m_pRequestManager->RefreshAnimeDetails(listener, id);
	}
	//----------------------------------------------------------------------------
	void Root::GetAnimeDetails(RequestListener* listener, int id)
	{
		m_pRequestManager->GetAnimeDetails(listener, id);
	}
	//----------------------------------------------------------------------------
	void Root::UpdateAnime(RequestListener* listener, int AnimeId, int score, int progress, int status)
	{
		m_pRequestManager->UpdateAnime(listener, AnimeId, score, progress, status);
	}
	//----------------------------------------------------------------------------
	void Root::SetUser(UserInfo user)
	{
		KeyList userKeys;
		GetUserInfoKeys(userKeys);

		FOR_(userKeys, j)
		{
			m_User.SetKeyValue(userKeys[j], user.GetKeyValue(userKeys[j]));
		}

		KeyList mangaKeys;
		GetUserInfoMangaKeys(mangaKeys);

		FOR_(mangaKeys, j)
		{
			m_User.Manga.SetKeyValue(mangaKeys[j], user.Manga.GetKeyValue(mangaKeys[j]));
		}

		KeyList animeKeys;
		GetUserInfoAnimeKeys(animeKeys);

		FOR_(animeKeys, j)
		{
			m_User.Anime.SetKeyValue(animeKeys[j], user.Anime.GetKeyValue(animeKeys[j]));
		}

	}
	//----------------------------------------------------------------------------
	const UserAnimeList& Root::GetUserAnimelist()
	{
		return GetMyAnimelistManager()->GetAnimeList();
	}
	//----------------------------------------------------------------------------
	const UserMangaList& Root::GetUserMangalist()
	{
		return GetMyAnimelistManager()->GetMangaList();
	}
	//----------------------------------------------------------------------------
	void Root::PostRequest(RequestInterface* r)
	{
		GetThreadManager()->PostRequest(r);
	}
	//----------------------------------------------------------------------------

	ChiString Root::GetVersion()
	{
		return m_sVersion;
	}
	//----------------------------------------------------------------------------
	ChiString Root::GetHash()
	{
		return m_sCommitHash;
	}
	//----------------------------------------------------------------------------
	const char* Root::GetKey(RequestApiValues api)
	{
		std::map<RequestApiValues, char*>::iterator It = RequestApiValueMap.find(api);

		if (It != RequestApiValueMap.end())
		{
			return It->second;
		}
		return "Not_Found";
	}
	//----------------------------------------------------------------------------
	void Root::StoreKeys()
	{
		/*RequestApiValueMap.insert(std::make_pair(REQUEST_VERIFY_SUCCESS,strcat(strdup(kRequestVerify),kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_VERIFY_ERROR,strcat(strdup(kRequestVerify),kRequestError)));

		RequestApiValueMap.insert(std::make_pair(REQUEST_GETMYANIMELIST_SUCCESS,strcat(strdup(kRequestGetMyAnimelist),kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_GETMYANIMELIST_ERROR,strcat(strdup(kRequestGetMyAnimelist),kRequestError)));

		RequestApiValueMap.insert(std::make_pair(REQUEST_GETMYMANGALIST_SUCCESS,strcat(strdup(kRequestGetMyMangalist),kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_GETMYMANGALIST_ERROR,strcat(strdup(kRequestGetMyMangalist),kRequestError)));

		RequestApiValueMap.insert(std::make_pair(REQUEST_IMAGEDOWNLOAD_SUCCESS,strcat(strdup(kRequestImageDownload),kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_IMAGEDOWNLOAD_ERROR,strcat(strdup(kRequestImageDownload),kRequestError)));

		RequestApiValueMap.insert(std::make_pair(REQUEST_ANIMESCRAPE_SUCCESS,strcat(strdup(kRequestAnimePageScrape),kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_ANIMESCRAPE_ERROR,strcat(strdup(kRequestAnimePageScrape),kRequestError)));
		*/

	}
}

