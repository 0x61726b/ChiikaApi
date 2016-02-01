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
#include "Logging/LogManager.h"
#include "Database/LocalDataManager.h"
#include "Recognition/MediaPlayerRecognitionManager.h"
#include "Recognition/AnimeRecognition.h"
#include "Seasons/SeasonManager.h"
#include "Request\ParsingManager.h"
#include "Logging\FileHelper.h"
#include "Logging\ChiString.h"
#include "Root\ThreadManager.h"
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
	void Root::Initialize(bool appMode,bool debugMode,const char* userName,const char* pass,const char* modulePath)
	{
		options.appMode = appMode;
		options.debugMode = debugMode;
		options.modulePath = modulePath;
		options.userName = userName;
		options.passWord = pass;

		
		m_pSettings = new AppSettings("Chiika.cfg",options.modulePath);
		////if(opts->appMode)
		////	m_pSettings = new AppSettings("Chiika.cfg",options->modulePath);
		m_pLogManager = new LogManager;

		ChiString version = std::to_string(ChiikaApi_VERSION_MAJOR) + "." + std::to_string(ChiikaApi_VERSION_MINOR) + "." + std::to_string(ChiikaApi_VERSION_PATCH);;
		m_sVersion = version;
		m_sCommitHash = (char)ChiikaApi_COMMIT_HASH;

		m_pLogManager->CreateLog(std::string(options.modulePath) + "\\Chiika.log",true,true,false)->
			SetLogDetail(LoggingLevel::LOG_LEVEL_EVERYTHING);

		LOG(INFO) << "Initialization successfull.Welcome to Chiika " << options.userName << "!";

		
	
		////m_pLogManager->CreateLog("DebuggerOutput",false,true,true)->
		////	SetLogDetail(LoggingLevel::LOG_LEVEL_EVERYTHING); //This is used to see messages on debug window,rather than printing to file. Use LOGD rather than LOG

		/*LOG(Bore) << "Chiika Api is initializing. Version: " << (m_sVersion);*/

		LOG(INFO) << "Creating MyAnimeList Manager";
		m_pMalManager = new MalManager;

		////LOG(INFO) << "Creating Season Manager";
		////m_pSeasonManager = new SeasonManager;

		//if(opts->appMode)
		//{
		//	LOG(INFO) << "Creating MediaPlayerRecognition Manager";
		//	m_pMPRecognition = new MediaPlayerRecognitionManager;
		//}

		//if(opts->appMode)
		//{
		//	//m_pThreadManager = new ThreadManager(false);
		//}

		LOG(INFO) << "Creating RequestManager Manager";
		m_pRequestManager = new RequestManager;

		//if(opts->appMode)
		//{
		//	LOG(INFO) << "Creating AnimeRecognition Manager";
		//	m_pRecognizer = new AnimeRecognition;
		//}


		//if(!opts->appMode)
		//{
		//	LOG(INFO) << "Skipping LocalData Manager";
		//}
		//else
		//{
		//	/*LOG(INFO) << "Creating LocalData Manager";
		//	m_pLocalData = new LocalDataManager;*/
		//}
				m_User.SetKeyValue(kUserName,options.userName);
		m_User.SetKeyValue(kPass,options.passWord);

		LOG(INFO) << "Creating LocalData Manager";
		m_pLocalData = new LocalDataManager;
		m_pLocalData->Initialize();

		////Very important!




		////if(opts->appMode)
		////	

		//StoreKeys();

		//LOG(INFO) << "Initialization successfull.Welcome to Chiika " << options->userName << "!";

		StoreKeys();
	}
	//----------------------------------------------------------------------------
	Root::~Root()
	{
		Destroy();
	}
	//----------------------------------------------------------------------------
	void Root::Destroy()
	{
		LOG(INFO) << "D-destroying ChiikaApi";
		TryDelete(m_pSettings);
		m_pSettings = 0;
		TryDelete(m_pMalManager);
		m_pMalManager = 0;
		TryDelete(m_pRequestManager);
		m_pRequestManager = 0;
		TryDelete(m_pLocalData);
		m_pLocalData = 0;
		//TryDelete(m_pMPRecognition);
		//TryDelete(m_pRecognizer);
		///*TryDelete(m_pSeasonManager);*/
		////TryDelete(m_pThreadManager);

		TryDelete(m_pLogManager);
		m_pLogManager = 0;
		
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
	void Root::DownloadImage(RequestListener* listener,const std::string& url)
	{
		//m_pRequestManager->DownloadImage(listener,url);
	}
	//----------------------------------------------------------------------------
	void Root::AnimeScrape(RequestListener* listener,int AnimeId)
	{
		m_pRequestManager->AnimePageScrape(listener,AnimeId);
	}
	//----------------------------------------------------------------------------
	void Root::SetUser(UserInfo user)
	{
		KeyList userKeys;
		GetUserInfoKeys(userKeys);

		FOR_(userKeys,j)
		{
			m_User.SetKeyValue(userKeys[j],user.GetKeyValue(userKeys[j]));
		}

		KeyList mangaKeys;
		GetUserInfoMangaKeys(mangaKeys);

		FOR_(mangaKeys,j)
		{
			m_User.Manga.SetKeyValue(mangaKeys[j],user.Manga.GetKeyValue(mangaKeys[j]));
		}

		KeyList animeKeys;
		GetUserInfoAnimeKeys(animeKeys);

		FOR_(animeKeys,j)
		{
			m_User.Anime.SetKeyValue(animeKeys[j],user.Anime.GetKeyValue(animeKeys[j]));
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
		std::map<RequestApiValues,char*>::iterator It = RequestApiValueMap.find(api);

		if(It != RequestApiValueMap.end())
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

