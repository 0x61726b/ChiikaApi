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
#ifndef __MyAnimeList_h__
#define __MyAnimeList_h__
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	struct CurlConfigOption
	{
		ChiString Name;
		ChiString Value;
		int cUrlOpt;

		CurlConfigOption(): Name(""),Value(""),cUrlOpt(0) {}
	} ;


	struct AnilistAuth
	{
		ChiString AccessToken;
		int Hour;
		int Day;
	};

	struct AnitomyResult
	{
		ChiString EpisodeTitle;
		ChiString EpisodeNumber;
		ChiString VideoRes;
		ChiString Group;
	};



#pragma region Enums

	enum CRUDOp
	{
		Nothing,
		Create,
		Update,
		Delete
	};
	enum CRUDTarget
	{
		ANIME,
		MANGA
	};
#pragma endregion




#pragma region Anime and Manga

	

	struct AnimeFileInfo
	{
		ChiString FolderPath;
		std::vector<ChiString> EpisodePaths;
	};
	

#pragma endregion

	struct AnimeFileDetails
	{
		ChiString Directory;
		ChiString FullPath;
		ChiString Group;
		ChiString Quality;
	};
	struct Timezone
	{
		ChiString TimezoneIdentifier;
		ChiString Name;
		ChiString Offset; //To Utc
	};
	struct UserTimezoneInfo
	{
		ChiString Name;
		long Bias;
	};
	struct Airdate
	{
		Timezone TimeZone;
		ChiString RdDate;
		ChiString RdTime;
		int Weekday;
		ChiString RdWeekday;
	};
	struct SenpaiItem
	{
		ChiString Name;
		int MalID;
		bool IsSequel;
		ChiString Simulcast;
		ChiString AirdateStr;
		ChiString Fansub;
		int SimulcastDelay;
		ChiString Type;
		bool MissingAirdate;
		bool MissingAirtime;
		ChiString AirDateOriginal;
		Map<ChiString,Airdate>::type Airdates;
	};
}
#include "Anime.h"
#include "Manga.h"
#include "UserInfo.h"

namespace ChiikaApi
{
	typedef Map<std::string, UserAnimeEntry>::type UserAnimeList;
	typedef Map<std::string, UserMangaEntry>::type UserMangaList;

	

	typedef UserAnimeList::iterator AnimeListIt;

	typedef Map<std::string, Anime>::type AnimeList;
	typedef Map<std::string, Manga>::type MangaList;

	typedef MangaList::iterator MangaListIt;

	typedef MultiMap<ChiString, CurlConfigOption>::type CurlConfigOptionMap;
}
//----------------------------------------------------------------------------
#endif