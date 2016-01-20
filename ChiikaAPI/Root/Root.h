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

struct MalApiExport RootOptions
{
	bool appMode;
	bool debugMode;
	char* userName;
	char* passWord;
	char* modulePath;

	RootOptions() 
		: appMode(false),
		  debugMode(false),
		  userName(""),
		  passWord(""),
		  modulePath("")
	{
	}
};
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport Root 
	{
	public:
		Root();
		~Root();

		void Initialize(RootOptions*);
		void Destroy();

		void AddAnimeToList(const UserAnimeEntry& data);
		void UpdateAnime(const UserAnimeEntry& data);
		void DeleteAnime(const UserAnimeEntry& name);

		void AddMangaToList(const MangaInfo& data);
		void UpdateManga(const MangaInfo& data);

		void PostRequest(RequestInterface* r);

		RootOptions* GetRootOptions() { return options; }

		static Root* Get();

		UserInfo& GetUser();
		void SetUser(UserInfo);

		const UserAnimeList& GetUserAnimelist();

		ThreadManager* GetThreadManager();
		RequestManager* GetRequestManager();
		LocalDataManager* GetLocalDataManager();
		MalManager* GetMyAnimelistManager();
		//New

	private:
		void StoreKeys();
		
	public:

		//Api Related things
		void InitializeApi(bool b);
		void Exit();
		ChiString GetVersion();
		ChiString GetHash(); //debugging purposes
		const char* GetKey(RequestApiValues);


		MalManager* m_pMalManager;
		RequestManager* m_pRequestManager;
		LogManager* m_pLogManager;
		AppSettings* m_pSettings;
		LocalDataManager* m_pLocalData;
		MediaPlayerRecognitionManager* m_pMPRecognition;
		AnimeRecognition* m_pRecognizer;
		SeasonManager* m_pSeasonManager;
		ThreadManager* m_pThreadManager;
	private:
		RootOptions* options;
		UserInfo m_User;
		std::map<RequestApiValues, char*> RequestApiValueMap;
	protected:
		ChiString m_sListData;
		ChiString m_sVersion;
		ChiString m_sCommitHash;
	};
}
//----------------------------------------------------------------------------
#endif // CHIMALAPI_H

