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
#include "ThirdParty\pugixml\src\pugixml.hpp"
#include "boost\asio.hpp"
#include "Common\BoostHeaders.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport LocalDataManager
	{
	public:
		LocalDataManager();
		virtual ~LocalDataManager();

		static LocalDataManager* Get();

		void Initialize();

	public:
		void SaveAnimeList();
		void SaveCachedAnimeList();
		void LoadAnimeList();
		void LoadCachedAnimelist();

	public:
		void SaveUserInfo();
		void LoadUserInfo();

	public:
		void SaveMangaList();
		void LoadMangaList();
	public:
		void SaveSenpaiData();
		void LoadSenpaiData();
	public:

	public:
		void SaveAll();

		void SetUserNamePass(ChiString userName,ChiString pass);

		void WorkerThread(boost::shared_ptr< boost::asio::io_service > io_service );

		void CheckIfFsLoaded();
	private:
		FsPath m_sAnimeListFilePath;
		FsPath m_sMangaListFilePath;
		FsPath m_sUserInfoPath;
		FsPath m_sSenpaiPath;

		bool animeListReady;
		bool animeCachedListReady;
		bool mangaListReady;
		bool userInfoReady;
		bool senpaiReady;

		boost::mutex m_Lock;
	};
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------