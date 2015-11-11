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
#ifndef __ChiMalApi_h__
#define __ChiMalApi_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//#include "Settings/Settings.h"
#include "Request/RequestManager.h"
#include "Recognition/MediaPlayerRecognitionManager.h" //Unfortunately,this is necessary or main func doesnt recognize the class
//#include "Recognition/AnimeRecognition.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport Root : public RequestListener,public GeneralAllocatedObject
	{
	public:
		Root();
		~Root();

		void Initialize(const ChiString& modulePath);
		void Destroy();

		void SetAnimeFolderPath(ChiString path);
		ChiString GetAnimeFolderPath();

		ChiString GetDataPath();
		ChiString GetImageFolderPath();

		AppSettings* GetAppSettings();

		void VerifyUserLogin();

		void DoFastScan();

		const UserInfo& GetUserInfo() const;
		void SetUserInfo(const UserInfo&);


		void RequestUserAnimeList();
		void AddAnimeToList(const UserAnimeEntry& data);
		void UpdateAnime(const UserAnimeEntry& data);
		void DeleteAnime(const UserAnimeEntry& name);
		void RequestAnimeScrape(const UserAnimeEntry& anime);

		void PostRequest(RequestManager* rm,ThreadedRequest* r);
		

		void RequestUserMangaList();
		void AddMangaToList(const MangaInfo& data);
		void UpdateManga(const MangaInfo& data);
		void DeleteManga(const MangaInfo& name);

		void SearchAnime(const ChiString& name);
		void SearchManga(const ChiString& name);

		void SearchAnilistAnime(const ChiString& name);

		void DownloadAnimeImage(const UserAnimeEntry& anime);
		void RequestUserPageScrape();
		void RequestSenpaiData();

		void ScanAnimeFolder(int id);

		AnimeList GetAnimeList(const AnimeUserStatus& status);
		AnimeList GetAnimeList();
		MangaList GetMangaList(const MangaUserStatus& status);
	public:

		//Events
		void OnUserVerifyComplete(const RequestResult& r);
		void OnAnimeSearchComplete(ThreadedRequest* r,const AnimeList& res);
		void OnGetAnimeListComplete(ThreadedRequest* r,const AnimeList& res);
		void OnGetMangaListComplete(ThreadedRequest* r,const MangaList& res);
		void OnCRUDComplete(ThreadedRequest* r,CRUDOp Op,CRUDTarget Target);
		void OnAnilistAuthComplete(ThreadedRequest*r);
		void OnAnilistSearchAnimeComplete(ThreadedRequest* r);
		void OnAnimeScrapeComplete(ThreadedRequest* r);
		void OnUserPageScrapeComplete(ThreadedRequest* r);
		//~

		//Api Related things
		void InitializeApi(bool b);
		void Exit();
		ChiString GetVersion();
		ChiString GetHash(); //debugging purposes

		virtual void Notify(ThreadedRequest* req);

		AbstractNativeEventFilterHelper* GetNativeEventFilterHelper();

		MalManager* m_pMalManager;
		RequestManager* m_pRequestManager;
		LogManager* m_pLogManager;
		AppSettings* m_pSettings;
		LocalDataManager* m_pLocalData;
		MediaPlayerRecognitionManager* m_pMPRecognition;
		AnimeRecognition* m_pRecognizer;
		SeasonManager* m_pSeasonManager;
	private:



	protected:
		ChiString m_sListData;
		ChiString m_sVersion;
		ChiString m_sCommitHash;
	};
}
//----------------------------------------------------------------------------
#endif // CHIMALAPI_H
