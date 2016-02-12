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
#include "Settings/Settings.h"
#include "pugixml.hpp"
#include "Logging/FileHelper.h"

namespace fs = boost::filesystem;
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	void AppSettings::SetDefaultValues()
	{
		m_DataPath = m_GlobalPath / "Data";

		Initialize();

		m_AnimeListFile = m_DataPath / "Chitanda.eru";
		m_CachedAnimeListFile = m_DataPath / "Yuu.sonoda";
		m_MangaListFile =  m_DataPath / "Oreki.houtarou";
		m_UserInfo = m_DataPath / "User.eru";
		m_SenpaiPath = m_DataPath / "Senpai.moe";

	}
	//----------------------------------------------------------------------------
	AppSettings::AppSettings(ChiString globalPath)
	{
		m_GlobalPath = globalPath;


		SetDefaultValues();
	}
	//----------------------------------------------------------------------------
	AppSettings::~AppSettings()
	{
	}
	void AppSettings::Initialize()
	{
		//Create folders here


		if(!fs::exists(m_DataPath))
		{
			if(fs::create_directory(m_DataPath))
			{
				m_bFirstLaunch = true;
			}
		}

		m_ImagePath = m_DataPath / "Images";
		if(!fs::exists(m_ImagePath))
		{
			if(fs::create_directory(m_ImagePath))
			{
				m_AnimeImagePath = m_ImagePath / "Anime";
				if(fs::create_directory(m_AnimeImagePath))
				{

				}
			}
		}

		m_ConfigFile = m_GlobalPath / "Config";
		if(!fs::exists(m_ConfigFile))
		{
			fs::create_directory(m_ConfigFile);
		}
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetDataPath()
	{
		return m_DataPath;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetImagePath()
	{
		return m_ImagePath;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetCachedAnimelistPath()
	{
		return m_CachedAnimeListFile;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetAnimelistPath()
	{
		return m_AnimeListFile;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetMangalistPath()
	{
		return m_MangaListFile;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetUserInfoPath()
	{
		return m_UserInfo;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetSenpaiMoePath()
	{
		return m_SenpaiPath;
	}
	//----------------------------------------------------------------------------
	FsPath AppSettings::GetConfigPath()
	{
		return m_ConfigFile;
	}
	//----------------------------------------------------------------------------
	bool AppSettings::GetIfFirstLaunch()
	{
		return m_bFirstLaunch;
	}
}
