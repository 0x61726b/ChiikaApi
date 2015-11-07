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
#include "Common/ExceptionManager.h"
#include "Database/LocalDataManager.h"
#include "Recognition/MediaPlayerRecognitionManager.h"
#include "Recognition/AnimeRecognition.h"
#include "Seasons/SeasonManager.h"
#include "json/json.h"
#include "Logging\FileHelper.h"
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	Root::Root(const std::string& modulePath)
	{
		m_pSettings = ChiikaNew AppSettings("Chiika.cfg",modulePath);
		m_pLogManager = ChiikaNew LogManager;

		String version = std::to_string(CHIIKAAPI_VERSION_MAJOR) + "." + std::to_string(CHIIKAAPI_VERSION_MINOR) + "." + std::to_string(CHIIKAAPI_VERSION_PATCH);;
		m_sVersion = version;
		m_sCommitHash = CHIIKAAPI_COMMIT_HASH;


		m_pLogManager->CreateLog(m_pSettings->GetDataPath() + "\\Chiika.log",true,false,false)->
			SetLogDetail((LoggingLevel)m_pSettings->GetIntegerOption(API_LOG_LEVEL));

		m_pLogManager->CreateLog("DebuggerOutput",false,true,true)->
			SetLogDetail(LoggingLevel::LOG_LEVEL_EVERYTHING); //This is used to see messages on debug window,rather than printing to file. Use LOGD rather than LOG

		LOG(Bore) << "Chiika Api is initializing. Version: " << (m_sVersion);

		LOG(INFO) << "Creating MyAnimeList Manager";
		m_pMalManager = ChiikaNew MalManager;
		
		LOG(INFO) << "Creating Season Manager";
		m_pSeasonManager = ChiikaNew SeasonManager;

		LOG(INFO) << "Creating MediaPlayerRecognition Manager";
		m_pMPRecognition = ChiikaNew MediaPlayerRecognitionManager;

		LOG(INFO) << "Creating RequestManager Manager";
		m_pRequestManager = ChiikaNew RequestManager;

		LOG(INFO) << "Creating AnimeRecognition Manager";
		m_pRecognizer = ChiikaNew AnimeRecognition;

		LOG(INFO) << "Creating LocalData Manager";
		m_pLocalData = ChiikaNew LocalDataManager;

		FileReader fr(m_pSettings->GetDataPath() + "\\Chiika.log");

		if(fr.Open())
		{
			std::string r = fr.Read();
			LOGD << r.c_str();
		}
		fr.Close();
		
	}
	//----------------------------------------------------------------------------
	Root::~Root()
	{
		LOG(Bore) << "Exiting Api..";
		delete m_pSettings;
		delete m_pMalManager;
		delete m_pRequestManager;
		delete m_pLogManager;
		delete m_pLocalData;
		delete m_pRecognizer;
	}
	//----------------------------------------------------------------------------
	void Root::SetAnimeFolderPath(String path)
	{
		AppSettings::Get().SetAnimeFolderPath(path);
	}
	//----------------------------------------------------------------------------
	String Root::GetAnimeFolderPath()
	{
		return AppSettings::Get().GetStringOption(LIBRARY_ANIME_FOLDER_PATH);
	}
	//----------------------------------------------------------------------------
	String Root::GetDataPath()
	{
		return AppSettings::Get().GetDataPath();
	}
	//----------------------------------------------------------------------------
	String Root::GetImageFolderPath()
	{
		return AppSettings::Get().GetImagePath();
	}
	//----------------------------------------------------------------------------
	const UserInfo& Root::GetUserInfo() const
	{
		return m_pLocalData->GetUserInfo();
	}
	//----------------------------------------------------------------------------
	void Root::SearchAnime(const String& name)
	{
		m_pRequestManager->CreateAnimeSearchRequest(this,name);
	}
	//----------------------------------------------------------------------------
	void Root::SearchManga(const String& name)
	{

	}
	//----------------------------------------------------------------------------
	void Root::VerifyUserLogin()
	{
		m_pRequestManager->CreateVerifyRequest(this);
	}
	//----------------------------------------------------------------------------
	void Root::AddAnimeToList(const AnimeInfo& info)
	{
		AnimeInfo anime = info;
		anime.UpdateOperation = CRUDOp::Create;
		m_pMalManager->AddAnimeToUpdates(anime);
		m_pRequestManager->CreateCRUDRequest(this,anime,MangaInfo(),ChiikaApi::CRUDOp::Create,CRUDTarget::ANIME);
	}
	//----------------------------------------------------------------------------
	void Root::UpdateAnime(const AnimeInfo& info)
	{
		AnimeInfo anime = info;
		anime.UpdateOperation = CRUDOp::Update;
		m_pMalManager->AddAnimeToUpdates(anime);
		m_pRequestManager->CreateCRUDRequest(this,info,MangaInfo(),ChiikaApi::CRUDOp::Update,CRUDTarget::ANIME);
	}
	//----------------------------------------------------------------------------
	void Root::DeleteAnime(const AnimeInfo& info)
	{
		AnimeInfo anime = info;
		anime.UpdateOperation = CRUDOp::Delete;
		m_pMalManager->AddAnimeToUpdates(anime);
		m_pRequestManager->CreateCRUDRequest(this,info,MangaInfo(),ChiikaApi::CRUDOp::Delete,CRUDTarget::ANIME);
	}
	//----------------------------------------------------------------------------
	void Root::AddMangaToList(const MangaInfo& info)
	{

	}
	//----------------------------------------------------------------------------
	void Root::UpdateManga(const MangaInfo& info)
	{

	}
	//----------------------------------------------------------------------------
	void Root::DeleteManga(const MangaInfo& info)
	{

	}
	//----------------------------------------------------------------------------
	void Root::RequestUserAnimeList()
	{
		m_pRequestManager->CreateGetAnimeListRequest(this);
	}
	//----------------------------------------------------------------------------
	void Root::RequestAnimeScrape(const AnimeInfo& anime)
	{
		m_pRequestManager->CreateAnimePageScrapeRequest(this,anime);
	}
	//----------------------------------------------------------------------------
	void Root::RequestUserPageScrape()
	{
		m_pRequestManager->CreateUserPageScrapeRequest(this);
	}
	//----------------------------------------------------------------------------
	void Root::RequestUserMangaList()
	{
		m_pRequestManager->CreateGetMangaListRequest(this);
	}
	//----------------------------------------------------------------------------
	void Root::RequestSenpaiData()
	{
		m_pRequestManager->CreateSenpaiMoeDataRequest(this);
	}
	//----------------------------------------------------------------------------
	void Root::SearchAnilistAnime(const String& name)
	{
		m_pRequestManager->CreateAnilistSearchAnime(this,name);
	}
	//----------------------------------------------------------------------------
	AnimeList Root::GetAnimeList(const AnimeUserStatus& status)
	{
		AnimeList whole = m_pMalManager->GetAnimeList();
		AnimeList list;
		AnimeListIt it = whole.begin();
		for(it;it != whole.end(); it++)
		{
			if(it->second.Status == status)
				list.insert(AnimeList::value_type(it->second.Animu.Id,it->second));
		}
		return list;
	}
	//----------------------------------------------------------------------------
	AnimeList Root::GetAnimeList()
	{
		AnimeList whole = m_pMalManager->GetAnimeList();
		return whole;
	}
	//----------------------------------------------------------------------------
	MangaList Root::GetMangaList(const MangaUserStatus& status)
	{
		MangaList whole = m_pMalManager->GetMangaList();
		MangaList list;
		MangaListIt it = whole.begin();
		for(it;it != whole.end(); it++)
		{
			if(it->second.Status == status)
				list.insert(MangaList::value_type(it->second.Mango.Id,it->second));
		}
		return list;
	}
	//----------------------------------------------------------------------------
	void Root::ScanAnimeFolder(int animeId)
	{

	}
	//----------------------------------------------------------------------------
	void Root::DownloadAnimeImage(const AnimeInfo& anime)
	{
		String url = (anime.Animu.Image);
		/*String fileName = url.mid(url.lastIndexOf("/") + 1,url.size() - url.lastIndexOf("/")).toStdString();*/

		/*m_pRequestManager->CreateImageDownloadRequest(this,url.toStdString(),fileName,anime);*/
	}
	//----------------------------------------------------------------------------
	void Root::InitializeApi(bool b
		)
	{
		/*m_pMPRecognition->Init();*/

		//VerifyUserLogin();

		//m_pRecognizer->RecognizeAndCache("[Vivid] Amagi Brilliant Park - 01v2 [2F0A246D].mkv");
		//AnimeInfo test;
		//test.Animu.Id = 21;
		//test.WatchedEpisodes = 3;
		//test.Score = 6;
		//test.Status = AnimeUserStatus::Watching;
		//m_pSettings->Save();
		//m_pLocalData->LoadUserInfo();
		//m_pLocalData->LoadAnimeList();
		//m_pLocalData->LoadMangaList();

		//m_pMPRecognition->SetEnabled(false);

		//AnimeInfo test;
		//test.Animu.Id = 31318;

		////m_pRequestManager->CreateUserPageScrapeRequest(this);

		////RequestAnimeScrape(test);
		////SearchAnime("Comet Lucifer");

		//AnimeList list = m_pMalManager->GetAnimeList();
		//MangaList listManga = m_pMalManager->GetMangaList();

		////GetColorFromImage("D:\\Torrent_Downloads\\9781626921405.jpg");



		/*m_pRequestManager->CreateSenpaiMoeDataRequest(this);*/

		//if(b)
		//{
		//	RequestUserAnimeList();
		//	RequestUserMangaList();
		//}
		//UserInfo ui;
		//ui.UserName = "arkenthera";
		//ui.Pass = "123asd456";
		//SetUserInfo(ui);

		//m_pRequestManager->CreateGetAnimeListRequest(this);

		/*m_pSeasonManager->GetClosest();*/
	}
	//----------------------------------------------------------------------------
	void Root::OnAnilistAuthComplete(ThreadedRequest*r)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{

		}
		else
		{
		}
	}
	//----------------------------------------------------------------------------
	void Root::OnAnilistSearchAnimeComplete(ThreadedRequest* r)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{

		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	void Root::OnAnimeSearchComplete(ThreadedRequest* r,const AnimeList& list)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{
			/*LOG("Anime search result returned " + String::number(list.size()) + " entries")*/

			//
			//AnimeList copy = list;
			//AnimeListIt it = copy.begin();
			//for(it; it != copy.end(); it++)
			//{
			//	AnimeInfo anim = m_pMalManager->GetAnimeById(it->first);

			//	if(anim.Animu.Id != 0) //in the list
			//	{
			//		anim.Animu = it->second.Animu;
			//		m_pMalManager->UpdateAnime(anim);
			//	}
			//}
			//LocalDataManager::Get().SaveAnimeList();
			//LocalDataManager::Get().SaveAnimeDetails();
		}
		else
		{

		}

	}
	//----------------------------------------------------------------------------
	void Root::OnUserPageScrapeComplete(ThreadedRequest* r)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{
			m_pRequestManager->CreateImageDownloadRequest(this,LocalDataManager::Get().GetUserInfo().ImageLink,"UserAvatar.jpg",AnimeInfo());
		}
	}
	//----------------------------------------------------------------------------
	void Root::OnAnimeScrapeComplete(ThreadedRequest* r)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{
			LocalDataManager::Get().SaveAnimeList();
			LocalDataManager::Get().SaveAnimeDetails();
		}
	}
	//----------------------------------------------------------------------------
	void Root::OnGetAnimeListComplete(ThreadedRequest* r,const AnimeList& list)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{
			m_pLocalData->LoadUpdateList();
			AnimeList AnimeUpdates = MalManager::Get().GetAnimeUpdateList();

			if(AnimeUpdates.size() > 0)
			{
				//R-r-resolve.. ?
				AnimeListIt It = AnimeUpdates.begin();
				for(It;It != AnimeUpdates.end(); It++)
				{
					AnimeInfo anime = It->second;

					switch(anime.UpdateOperation)
					{
					case CRUDOp::Create:
					{
						m_pRequestManager->CreateCRUDRequest(this,anime,MangaInfo(),ChiikaApi::CRUDOp::Create,CRUDTarget::ANIME);
					}
					break;
					case CRUDOp::Update:
					{
						m_pRequestManager->CreateCRUDRequest(this,anime,MangaInfo(),ChiikaApi::CRUDOp::Update,CRUDTarget::ANIME);
					}
					break;
					case CRUDOp::Delete:
					{
						m_pRequestManager->CreateCRUDRequest(this,anime,MangaInfo(),ChiikaApi::CRUDOp::Delete,CRUDTarget::ANIME);
					}
					break;
					}
				}
			}
			else
			{
				//No queued update means we're in sync?
				//Lets go with this until we find a bug

				AnimeList aList = MalManager::Get().GetAnimeList();
				//if(aList.size() == 0)
				//	MalManager::Get().AddAnimeList(list);
				//else
				//	MalManager::Get().UpdateAnimeList(list);
				MalManager::Get().AddAnimeList(list);
				m_pLocalData->SaveAnimeList();
				m_pLocalData->LoadAnimeDetails();
				m_pLocalData->SaveUserInfo();

			}
		}
		else
		{
		}
	}
	//----------------------------------------------------------------------------
	void Root::OnGetMangaListComplete(ThreadedRequest* r,const MangaList& res)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{
			m_pLocalData->LoadUpdateList();
			MangaList MangaUpdates = MalManager::Get().GetMangaUpdateList();


			if(MangaUpdates.size() > 0)
			{
				MangaListIt MangaIt = MangaUpdates.begin();
				for(MangaIt;MangaIt != MangaUpdates.end(); MangaIt++)
				{
					MangaInfo manga = MangaIt->second;

					switch(manga.UpdateOperation)
					{
					case CRUDOp::Create:
					{
						m_pRequestManager->CreateCRUDRequest(this,AnimeInfo(),manga,ChiikaApi::CRUDOp::Create,CRUDTarget::MANGA);
					}
					break;
					case CRUDOp::Update:
					{
						m_pRequestManager->CreateCRUDRequest(this,AnimeInfo(),manga,ChiikaApi::CRUDOp::Update,CRUDTarget::MANGA);
					}
					break;
					case CRUDOp::Delete:
					{
						m_pRequestManager->CreateCRUDRequest(this,AnimeInfo(),manga,ChiikaApi::CRUDOp::Delete,CRUDTarget::MANGA);
					}
					break;
					}
				}
			}
			else
			{
				//No queued update means we're in sync?
				//Lets go with this until we find a bug
				MalManager::Get().AddMangaList(res);
				m_pLocalData->SaveMangaList();
				m_pLocalData->SaveUserInfo();
			}
		}
	}
	//----------------------------------------------------------------------------
	void Root::OnCRUDComplete(ThreadedRequest* r,CRUDOp Op,CRUDTarget Target)
	{
		if(REQUEST_SUCCESS(r->m_Result.HttpCode))
		{
			//Success
			if(Target == CRUDTarget::ANIME)
			{
				m_pMalManager->DeleteAnimeFromUpdates(r->m_Result.AnimeResult);

				if(Op == CRUDOp::Create)
					m_pMalManager->AddAnime(r->m_Result.AnimeResult);
				if(Op == CRUDOp::Update)
					m_pMalManager->UpdateAnime(r->m_Result.AnimeResult);
				if(Op == CRUDOp::Delete)
					m_pMalManager->DeleteAnime(r->m_Result.AnimeResult);

				//SYNC now
				RequestUserAnimeList();
			}
			if(Target == CRUDTarget::MANGA)
			{
				m_pMalManager->DeleteMangaFromUpdates(r->m_Result.MangaResult);

				if(Op == CRUDOp::Create)
					m_pMalManager->AddManga(r->m_Result.MangaResult);
				if(Op == CRUDOp::Update)
					m_pMalManager->UpdateManga(r->m_Result.MangaResult);
				if(Op == CRUDOp::Delete)
					m_pMalManager->DeleteManga(r->m_Result.MangaResult);

				//SYNC now
				RequestUserMangaList();
			}
		}
		m_pLocalData->SaveUpdateList();
		m_pLocalData->SaveAnimeList();
		m_pLocalData->SaveMangaList();
	}
	//----------------------------------------------------------------------------
	void Root::OnUserVerifyComplete(const RequestResult& r)
	{
		//
	}
	//----------------------------------------------------------------------------
	void Root::Notify(ThreadedRequest* req)
	{
		String RequestName = req->Name;
		
		if(RequestName == "AnilistAuth")
		{
			OnAnilistAuthComplete(req);
		}
		if(RequestName == "AnilistSearchAnime")
		{
			OnAnilistSearchAnimeComplete(req);
		}
		if(RequestName == "SearchAnime")
		{
			
			OnAnimeSearchComplete(req,req->m_Result.m_AnimeList);

		}
		if(RequestName == "GetAnimeList")
		{
			
			OnGetAnimeListComplete(req,req->m_Result.m_AnimeList);
		}
		if(RequestName == "GetMangaList")
		{
			
			OnGetMangaListComplete(req,req->m_Result.m_MangaList);
		}
		if(RequestName == "CreateAnime")
		{
			
			OnCRUDComplete(req,CRUDOp::Create,CRUDTarget::ANIME);
		}
		if(RequestName == "UpdateAnime")
		{
			
			OnCRUDComplete(req,CRUDOp::Update,CRUDTarget::ANIME);
		}
		if(RequestName == "DeleteAnime")
		{
			
			OnCRUDComplete(req,CRUDOp::Delete,CRUDTarget::ANIME);
		}
		if(RequestName == "CreateManga")
		{
			
			OnCRUDComplete(req,CRUDOp::Create,CRUDTarget::MANGA);
		}
		if(RequestName == "UpdateManga")
		{
			OnCRUDComplete(req,CRUDOp::Update,CRUDTarget::MANGA);
		}
		if(RequestName == "DeleteManga")
		{
			
			OnCRUDComplete(req,CRUDOp::Delete,CRUDTarget::MANGA);
		}
		if(RequestName == "Verify")
		{
			
			OnUserVerifyComplete(req->m_Result);
		}
		if(RequestName == "ImageDownload")
		{
			
		}
		if(RequestName == "AnimeScrape")
		{
			OnAnimeScrapeComplete(req);
			
		}
		if(RequestName == "UserPageScrape")
		{
			OnUserPageScrapeComplete(req);
		}
		if(RequestName == "SenpaiMoeData")
		{
			
		}
	}
	//----------------------------------------------------------------------------
	void Root::Exit()
	{
	}
	//----------------------------------------------------------------------------
	void Root::DoFastScan()
	{

	}
	//----------------------------------------------------------------------------
	AppSettings* Root::GetAppSettings()
	{
		return m_pSettings;
	}
	//----------------------------------------------------------------------------
	void Root::SetUserInfo(const UserInfo& ui)
	{
		m_pLocalData->SetUserInfo(ui);
	}
	//----------------------------------------------------------------------------
	AbstractNativeEventFilterHelper* Root::GetNativeEventFilterHelper()
	{
		return  NULL;
	}
	//----------------------------------------------------------------------------
	String Root::GetVersion()
	{
		return m_sVersion;
	}
	//----------------------------------------------------------------------------
	String Root::GetHash()
	{
		return m_sCommitHash;
	}
	//----------------------------------------------------------------------------
}

