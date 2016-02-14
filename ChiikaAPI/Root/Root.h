//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2015  arkenthera
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
#include "Recognition/MediaPlayerRecognitionManager.h" //Unfortunately,this is necessary or main func doesnt recognize the class
//#include "Recognition/AnimeRecognition.h"

class MalApiExport RootOptions
{
public:
	bool appMode;
	int log_level;
	std::string userName;
	std::string passWord;
	std::string modulePath;

	RootOptions()
		: appMode(false),
		log_level(1)
	{
	}
	~RootOptions()
	{
	}
};
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport SystemEventListener
	{
	public:
		virtual void OnEvent(SystemEvents) = 0;
	};
	class MalApiExport Root
	{
	public:
		Root();
		~Root();

		void Initialize(bool appMode,int log_Level,const char* userName,const char* pass,const char* modulePath);
		void Destroy();

		void PostRequest(RequestInterface* r);

		RootOptions GetRootOptions() { return options; }

		static Root* Get();

		UserInfo& GetUser();
		void SetUser(UserInfo);

		const UserAnimeList& GetUserAnimelist();
		const UserMangaList& GetUserMangalist();

		const std::vector<SenpaiItem>& GetSenpaiData();



		const AnimeList& GetAnimelist();

		ThreadManager* GetThreadManager();
		RequestManager* GetRequestManager();
		LocalDataManager* GetLocalDataManager();
		MalManager* GetMyAnimelistManager();
		AppSettings* GetAppSettings();
		SeasonManager* GetSeasonManager();
		//New


		//Requests
		void VerifyUser(RequestListener* listener);
		void GetMyAnimelist(RequestListener* listener);
		void GetMyMangalist(RequestListener* listener);
		void MalScrape(RequestListener* listener);
		void DownloadImage(RequestListener* listener,const std::string& url);
		void AnimeScrape(RequestListener* listener,int id);
		void MalAjax(RequestListener* listener,int id);
		void SearchAnime(RequestListener* listener,int id,const char* keywords);
		void RefreshAnimeDetails(RequestListener* listener,int id);
		void GetAnimeDetails(RequestListener* listener,int id);
		void UpdateAnime(RequestListener* listener,int AnimeId,int score,int progress,int status);


		//API Related stuff
		void RegisterSystemEventListener(SystemEventListener* sys);
		void UnRegisterSystemEventListener(SystemEventListener* sys);

		void FireSystemEvent(SystemEvents evt);

		void InitDatabase();
	private:
		void StoreKeys();
		std::vector<SystemEventListener*> m_vSysEventListeners;

	public:

		//Api Related things
		void InitializeApi(bool b);
		void Exit();
		ChiString GetVersion();
		ChiString GetHash(); //debugging purposes

		MalManager* m_pMalManager;
		RequestManager* m_pRequestManager;
		AppSettings* m_pSettings;
		LocalDataManager* m_pLocalData;
		MediaPlayerRecognitionManager* m_pMPRecognition;
		AnimeRecognition* m_pRecognizer;
		SeasonManager* m_pSeasonManager;
		ThreadManager* m_pThreadManager;
	private:
		RootOptions options;
		UserInfo m_User;
	protected:
		ChiString m_sListData;
		ChiString m_sVersion;
		ChiString m_sCommitHash;
	};
}
//----------------------------------------------------------------------------
#endif // CHIMALAPI_H

