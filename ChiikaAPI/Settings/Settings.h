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
#ifndef __ChiikaSettings_h__
#define __ChiikaSettings_h__
//----------------------------------------------------------------------------
//Defines
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Common/Singleton.h"
#include "Settings/OptionList.h"
#include "Common/BoostHeaders.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport AppSettings
	{
	public:
		AppSettings(ChiString globalPath);
		~AppSettings();
		void Initialize();
		void SetDefaultValues();


		FsPath GetDataPath();
		FsPath GetImagePath();

		FsPath GetAnimelistPath();
		FsPath GetCachedAnimelistPath();
		FsPath GetMangalistPath();
		FsPath GetUserInfoPath();
		FsPath GetSenpaiMoePath();
		FsPath GetConfigPath();

		bool GetIfFirstLaunch();

	private:
		FsPath m_GlobalPath;
		FsPath m_DataPath;
		FsPath m_ImagePath;
		FsPath m_AnimeImagePath;

		FsPath m_AnimeListFile;
		FsPath m_CachedAnimeListFile;
		FsPath m_MangaListFile;
		FsPath m_UserInfo;
		FsPath m_SenpaiPath;
		FsPath m_ConfigFile;

		//Option Values

		//Application Values
		bool m_bFirstLaunch;

		//Options

	};
}
//----------------------------------------------------------------------------
#endif
