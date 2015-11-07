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
	typedef struct _CurlConfigOption
	{
		String Name;
		String Value;
		int cUrlOpt;

		_CurlConfigOption(): Name(""),Value(""),cUrlOpt(0) {}
	} CurlConfigOption;

	typedef struct _MALUserInfo
	{
		String UserName;
		String Pass;
	} MALUser;


	struct AnilistAuth
	{
		String AccessToken;
		int Hour;
		int Day;
	};

	struct AnitomyResult
	{
		String EpisodeTitle;
		String EpisodeNumber;
		String VideoRes;
		String Group;
	};



#pragma region Enums
	enum AnimeType
	{
		TV = 1,
		OVA = 2,
		Movie = 3
	};
	enum MangaType
	{
		Normal = 1,
		Novel = 2,
		Oneshot = 3,
		Doujinshi = 4,
		Manwha = 5,
		Manhua = 6
	};
	enum AnimeStatus
	{
		NotAired,
		Airing,
		AnimeFinished
	};
	enum AnimeUserStatus
	{
		Watching = 1,
		AnimeCompleted = 2,
		AnimeOnHold = 3,
		AnimeDropped = 4,
		PlanToWatch = 6
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

	typedef struct _Manga
	{
		int Id;
		String Title;
		String English;
		MangaType Type; //We left off here boys
		int Chapters;
		int Volumes;
		MangaStatus Status;
		String StartDate;
		String EndDate;
		String Image;
		String Synopsis;
		_Manga()
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
	} Manga;

	struct AnimeDetails
	{
		String Synopsis;
		std::vector<String> Tags;
		String Premiered;
		std::vector<String> Producers;
		String DurationPerEpisode;

		AnimeDetails()
		{

		}
	};
	struct AnimeStatistics
	{
		float Score;
		int Ranked;
		int Popularity;

		AnimeStatistics()
		{
			Score = 0;
			Ranked = 0;
			Popularity = 0;
		}
	};

	typedef struct _Anime
	{
		int Id;
		String Title;
		String English;
		int EpisodeCount;
		AnimeType Type;
		AnimeStatus Status;
		String StartDate;
		String EndDate;
		String Image;

		//Experimental
		AnimeDetails ExtraDetails;
		AnimeStatistics Statistics;
		_Anime()
		{
			Id = 0;
			Title = "";
			English = "";
			EpisodeCount = 0;
			Type = AnimeType::TV;
			Status = AnimeStatus::NotAired;
			StartDate = "";
			EndDate = "";
			Image = "";
		}
	} Anime;

	struct AnimeFileInfo
	{
		String FolderPath;
		std::vector<String> EpisodePaths;
	};
	typedef struct _AnimeInfo
	{
		Anime Animu;
		int MyId;
		int WatchedEpisodes;
		String StartDate;
		String EndDate;
		int Score;
		AnimeUserStatus Status;
		int Rewatching;
		int RewatchingEp;
		String LastUpdated;
		CRUDOp UpdateOperation;

		_AnimeInfo()
		{
			MyId = 0;
			Score = 0;
			WatchedEpisodes = 0;
			StartDate = "";
			EndDate = "";
			Status = AnimeUserStatus::PlanToWatch;
			Rewatching = 0;
			RewatchingEp = 0;
			LastUpdated = "";
			UpdateOperation = CRUDOp::Nothing;
		}
	} AnimeInfo;
	typedef struct _MangaInfo
	{
		Manga Mango;
		int MyId;
		int ReadChapters;
		int ReadVolumes;
		String StartDate;
		String EndDate;
		int Score;
		MangaUserStatus Status;
		int Rereading;
		int RereadChapters;
		String LastUpdated;
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
		String Directory;
		String FullPath;
		String Group;
		String Quality;
	};
	struct Timezone
	{
		String TimezoneIdentifier;
		String Name;
		String Offset; //To Utc
	};
	struct UserTimezoneInfo
	{
		String Name;
		long Bias;
	};
	struct Airdate
	{
		Timezone TimeZone;
		String RdDate;
		String RdTime;
		int Weekday;
		String RdWeekday;
	};
	struct SenpaiItem
	{
		String Name;
		int MalID;
		bool IsSequel;
		String Simulcast;
		String AirdateStr;
		String Fansub;
		int SimulcastDelay;
		String Type;
		bool MissingAirdate;
		bool MissingAirtime;
		String AirDateOriginal;
		Map<String,Airdate>::type Airdates;
	};
	




#pragma region User
	typedef struct _UserAnimeInfo
	{
		int Watching;
		int Completed;
		int OnHold;
		int Dropped;
		int PlanToWatch;
		float DaySpentAnime;
		_UserAnimeInfo()
		{
			Watching = 0;
			Completed = 0;
			Dropped = 0;
			PlanToWatch = 0;
			DaySpentAnime = 0.0f;
		}
	} UserAnimeInfo;
	typedef struct _UserMangaInfo
	{
		int Reading;
		int Completed;
		int OnHold;
		int Dropped;
		int PlanToRead;
		float DaysSpentReading;

		_UserMangaInfo()
		{
			Reading = 0;
			Completed = 0;
			OnHold = 0;
			Dropped = 0;
			PlanToRead = 0;
			DaysSpentReading = 0.0f;
		}
	} UserMangaInfo;

	typedef struct _User
	{
		String UserName;
		String Pass;
		String ImageLink;

		UserAnimeInfo AnimeInfo;
		UserMangaInfo MangaInfo;
	} UserInfo;
#pragma endregion
}

//----------------------------------------------------------------------------
#endif