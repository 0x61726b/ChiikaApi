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
#ifndef __ChiikaLocalDataManager_h__
#define __ChiikaLocalDataManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Common/Singleton.h"
#include "pugixml.hpp"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport FileLoader
	{
	public:


		enum FileType
		{
			AnimeList,
			MangaList,
			UpdateList,
			Settings,
			UserInfo,
			AnimeDetails,
			SenpaiJSON
		};

		FileLoader(ChiString filePath,FileType type);

		virtual void Save() = 0;
		virtual void Load() = 0;
		virtual void Create();



	protected:
		ChiString m_sPath;
		FileType m_eType;
	};
	class MalApiExport AnimeFileLoader : public FileLoader
	{
	public:
		AnimeFileLoader(ChiString path);

		void Save();
		void Load();
	};
	class MalApiExport MangaFileLoader : public FileLoader
	{
	public:
		MangaFileLoader(ChiString path);

		void Save();
		void Load();
	};
	class MalApiExport UserInfoLoader : public FileLoader
	{
	public:
		UserInfoLoader(ChiString path,ChiikaApi::UserInfo ui);

		void Save();
		void Load();


		ChiikaApi::UserInfo m_UserDetailedInfo;
	};
	class MalApiExport UpdateListLoader : public FileLoader
	{
	public:

		UpdateListLoader(ChiString path);

		void Save();
		void Load();
	};
	class MalApiExport AnimeDetailsLoader : public FileLoader
	{
	public:
		AnimeDetailsLoader(ChiString path);

		void Save();
		void Load();
	};
	class MalApiExport SenpaiLoader : public FileLoader
	{
	public:
		SenpaiLoader(ChiString path);

		void Save();
		void Load();
	};
	class MalApiExport LocalDataManager : public Singleton<LocalDataManager>
	{
	public:

		CHIKA_AUTO_MUTEX

		LocalDataManager();
		~LocalDataManager();

	public:
		void SaveAnimeList();
		void LoadAnimeList();

	public:
		void SaveUserInfo();
		void LoadUserInfo();

	public:
		void SaveUpdateList();
		void LoadUpdateList();

	public:
		void SaveMangaList();
		void LoadMangaList();
	public:
		void SaveAnimeDetails();
		void LoadAnimeDetails();
	public:
		void SaveSenpaiData();
		void LoadSenpaiData();
	public:

		void SetUserNamePass(ChiString userName,ChiString pass);

		const UserInfo& GetUserInfo();
		void SetUserInfo(UserInfo i);

	private:
		UserInfo m_UserDetailedInfo;
	private:
		ChiString m_sAnimeListFilePath;
		ChiString m_sMangaListFilePath;
		ChiString m_sUserInfoPath;
		ChiString m_sUpdateListPath;
		ChiString m_sAnimeDetailsPath;
		ChiString m_sSenpaiPath;

	private:
		AnimeFileLoader* m_AnimeLoader;
		MangaFileLoader* m_MangaLoader;
		UserInfoLoader* m_UserInfoLoader;
		UpdateListLoader* m_UpdateListLoader;
		AnimeDetailsLoader* m_AnimeDetailsLoader;
		SenpaiLoader* m_SenpaiLoader;

	public:
		static LocalDataManager& Get();
		static LocalDataManager* GetPtr();
	};
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------