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
	
	enum MangaType
	{
		Normal = 1,
		Novel = 2,
		Oneshot = 3,
		Doujinshi = 4,
		Manwha = 5,
		Manhua = 6
	};
	enum MangaUserStatus
	{
		Reading = 1,
		MangaCompleted = 2,
		MangaOnHold = 3,
		MangaDropped = 4,
		PlanToRead = 6
	};

	enum MangaStatus
	{
		MangaFinished = 2,
		Publishing = 1,
		NotYetPublished = 3
	};
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

	struct Manga
	{
		int Id;
		ChiString Title;
		ChiString English;
		MangaType Type;
		int Chapters;
		int Volumes;
		MangaStatus Status;
		ChiString StartDate;
		ChiString EndDate;
		ChiString Image;
		ChiString Synopsis;
		Manga()
		{
			Id = 0;
			Title = "";
			English = "";
			Type = MangaType::Normal;
			Chapters = 0;
			Volumes = 0;
			Status = MangaStatus::MangaFinished;
			StartDate = "";
			EndDate = "";
			Image = "";
			Synopsis = "";
		}
	};


	struct AnimeFileInfo
	{
		ChiString FolderPath;
		std::vector<ChiString> EpisodePaths;
	};
	
	typedef struct _MangaInfo
	{
		Manga Mango;
		int MyId;
		int ReadChapters;
		int ReadVolumes;
		ChiString StartDate;
		ChiString EndDate;
		int Score;
		MangaUserStatus Status;
		int Rereading;
		int RereadChapters;
		ChiString LastUpdated;
		CRUDOp UpdateOperation;
		_MangaInfo()
		{
			MyId = 0;
			ReadChapters = 0;
			ReadVolumes = 0;
			StartDate = "";
			EndDate = "";
			Score = 0;
			Status = MangaUserStatus::PlanToRead;
			Rereading = 0;
			RereadChapters = 0;
			LastUpdated = "";
			UpdateOperation = CRUDOp::Nothing;
		}
	} MangaInfo;
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
#include "UserInfo.h"

namespace ChiikaApi
{
	typedef Map<int, UserAnimeEntry>::type UserAnimeList;

	typedef Map<int, MangaInfo>::type MangaList;

	typedef UserAnimeList::iterator AnimeListIt;

	typedef Map<int, Anime>::type AnimeList;

	typedef MangaList::iterator MangaListIt;

	typedef MultiMap<ChiString, CurlConfigOption>::type CurlConfigOptionMap;
}
//----------------------------------------------------------------------------
#endif