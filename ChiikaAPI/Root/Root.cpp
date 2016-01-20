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
	void Root::Initialize(RootOptions* opts)
	{
		options = opts;
		if(opts->appMode)
			m_pSettings = new AppSettings("Chiika.cfg",options->modulePath);
		m_pLogManager = new LogManager;

		ChiString version = std::to_string(ChiikaApi_VERSION_MAJOR) + "." + std::to_string(ChiikaApi_VERSION_MINOR) + "." + std::to_string(ChiikaApi_VERSION_PATCH);;
		m_sVersion = version;
		m_sCommitHash = (char)ChiikaApi_COMMIT_HASH;

		if(opts->appMode)
		{
			m_pLogManager->CreateLog(std::string(options->modulePath) + "\\Chiika.log",true,true,false)->
				SetLogDetail((LoggingLevel)m_pSettings->GetIntegerOption(API_LOG_LEVEL));
		}
		if(opts->debugMode && opts->appMode)
			m_pLogManager->CreateLog(std::string(options->modulePath) + "\\Chiika.log",true,true,false)->
			SetLogDetail((LoggingLevel)LoggingLevel::LOG_LEVEL_EVERYTHING);

		m_pLogManager->CreateLog("DebuggerOutput",false,true,true)->
			SetLogDetail(LoggingLevel::LOG_LEVEL_EVERYTHING); //This is used to see messages on debug window,rather than printing to file. Use LOGD rather than LOG

		LOG(Bore) << "Chiika Api is initializing. Version: " << (m_sVersion);

		LOG(INFO) << "Creating MyAnimeList Manager";
		m_pMalManager = new MalManager;

		LOG(INFO) << "Creating Season Manager";
		m_pSeasonManager = new SeasonManager;

		if(opts->appMode)
		{
			LOG(INFO) << "Creating MediaPlayerRecognition Manager";
			m_pMPRecognition = new MediaPlayerRecognitionManager;
		}

		if(opts->appMode)
		{
			m_pThreadManager = new ThreadManager;
		}

		LOG(INFO) << "Creating RequestManager Manager";
		m_pRequestManager = new RequestManager;

		if(opts->appMode)
		{
			LOG(INFO) << "Creating AnimeRecognition Manager";
			m_pRecognizer = new AnimeRecognition;
		}


		if(!opts->appMode)
		{
			LOG(INFO) << "Skipping LocalData Manager";
		}
		else
		{
			LOG(INFO) << "Creating LocalData Manager";
			m_pLocalData = new LocalDataManager;
		}



		//Very important!
		if(opts->appMode)
			m_pLocalData->Initialize();

		m_User.SetKeyValue(kUserName, options->userName);
		m_User.SetKeyValue(kPass, options->passWord);

		StoreKeys();
	}
	//----------------------------------------------------------------------------
	Root::~Root()
	{

	}
	//----------------------------------------------------------------------------
	void Root::Destroy()
	{
		TryDelete(m_pSettings);
		TryDelete(m_pMalManager);

		TryDelete(m_pRequestManager);

		TryDelete(m_pLogManager);
		TryDelete(m_pLocalData);
		TryDelete(m_pRecognizer);
		TryDelete(options);
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
	UserInfo& Root::GetUser()
	{
		return m_User;
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
	}
	//----------------------------------------------------------------------------
	const UserAnimeList& Root::GetUserAnimelist()
	{
		return GetMyAnimelistManager()->GetAnimeList();
	}
	//----------------------------------------------------------------------------
	void Root::PostRequest(RequestInterface* r)
	{
		GetThreadManager()->PostRequest(r);
	}
	//----------------------------------------------------------------------------
	void Root::AddAnimeToList(const UserAnimeEntry& info)
	{
		//UserAnimeEntry anime = info;
		//anime.UpdateOperation = CRUDOp::Create;
		//m_pMalManager->AddAnimeToUpdates(anime);
		//m_pRequestManager->CreateCRUDRequest(this,anime,MangaInfo(),ChiikaApi::CRUDOp::Create,CRUDTarget::ANIME);
	}
	//----------------------------------------------------------------------------
	void Root::UpdateAnime(const UserAnimeEntry& info)
	{
		//UserAnimeEntry anime = info;
		//anime.UpdateOperation = CRUDOp::Update;
		//m_pMalManager->AddAnimeToUpdates(anime);
		//m_pRequestManager->CreateCRUDRequest(this,info,MangaInfo(),ChiikaApi::CRUDOp::Update,CRUDTarget::ANIME);
	}
	//----------------------------------------------------------------------------
	void Root::DeleteAnime(const UserAnimeEntry& info)
	{
		//UserAnimeEntry anime = info;
		//anime.UpdateOperation = CRUDOp::Delete;
		//m_pMalManager->AddAnimeToUpdates(anime);
		//m_pRequestManager->CreateCRUDRequest(this,info,MangaInfo(),ChiikaApi::CRUDOp::Delete,CRUDTarget::ANIME);
	}
	//----------------------------------------------------------------------------
	void Root::AddMangaToList(const MangaInfo& info)
	{

	}
	//----------------------------------------------------------------------------
	void Root::UpdateManga(const MangaInfo& info)
	{

	}

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
		RequestApiValueMap.insert(std::make_pair(REQUEST_VERIFY_SUCCESS, strcat(strdup(kRequestVerify), kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_VERIFY_ERROR, strcat(strdup(kRequestVerify), kRequestError)));

		RequestApiValueMap.insert(std::make_pair(REQUEST_GETMYANIMELIST_SUCCESS, strcat(strdup(kRequestGetMyAnimelist), kRequestSuccess)));
		RequestApiValueMap.insert(std::make_pair(REQUEST_GETMYANIMELIST_ERROR, strcat(strdup(kRequestGetMyAnimelist), kRequestError)));
	}
}

