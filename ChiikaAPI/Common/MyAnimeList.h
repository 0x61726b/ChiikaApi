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

	struct AnimeDetails
	{
		ChiString Synopsis;
		std::vector<ChiString> Tags;
		ChiString Premiered;
		std::vector<ChiString> Producers;
		ChiString DurationPerEpisode;

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

	struct Anime
	{
		int Id;
		ChiString Title;
		ChiString English;
		int EpisodeCount;
		AnimeType Type;
		AnimeStatus Status;
		ChiString StartDate;
		ChiString EndDate;
		ChiString Image;

		//Experimental
		AnimeDetails ExtraDetails;
		AnimeStatistics Statistics;
		Anime()
		{
			Id = UnknownAnime;
			Title = "";
			English = "";
			EpisodeCount = 0;
			Type = AnimeType::TV;
			Status = AnimeStatus::NotAired;
			StartDate = "";
			EndDate = "";
			Image = "";
		}

		static int UnknownAnime;
	} ;

	struct AnimeFileInfo
	{
		ChiString FolderPath;
		std::vector<ChiString> EpisodePaths;
	};
	struct UserAnimeEntry
	{
		Anime Anime;
		int MyId;
		int WatchedEpisodes;
		ChiString StartDate;
		ChiString EndDate;
		int Score;
		AnimeUserStatus Status;
		int Rewatching;
		int RewatchingEp;
		ChiString LastUpdated;
		CRUDOp UpdateOperation;

		UserAnimeEntry()
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
	




#pragma region User
	typedef struct _UserUserAnimeEntry
	{
		int Watching;
		int Completed;
		int OnHold;
		int Dropped;
		int PlanToWatch;
		float DaySpentAnime;
		_UserUserAnimeEntry()
		{
			Watching = 0;
			Completed = 0;
			Dropped = 0;
			PlanToWatch = 0;
			DaySpentAnime = 0.0f;
		}
	} UserUserAnimeEntry;
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

	struct UserInfo
	{
		int UserId;
		ChiString UserName;
		ChiString Pass;
		ChiString ImageLink;

		UserUserAnimeEntry UserAnimeEntry;
		UserMangaInfo MangaInfo;

		static int UnknownUser;

		UserInfo()
		{
			UserId = 0;
			UserName = "";
			Pass = "";
			ImageLink = "";
		}
	};
#pragma endregion
}

//----------------------------------------------------------------------------
#endif