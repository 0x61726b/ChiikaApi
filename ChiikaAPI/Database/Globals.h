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
#ifndef __JsKeys_h__
#define __JsKeys_h__
//----------------------------------------------------------------------------
#define CONCAT_STR(str1,str2) (std::string(std::string(str1) + std::string(str2))).c_str()
//----------------------------------------------------------------------------
#include "Common\Required.h"
//----------------------------------------------------------------------------

MalApiExport enum RequestApiValues
{
	REQUEST_VERIFY_SUCCESS = 0,
	REQUEST_VERIFY_ERROR,

	REQUEST_GETMYANIMELIST_SUCCESS,
	REQUEST_GETMYANIMELIST_ERROR
};

namespace
{
	//Requests
	const char* kRequestSuccess = "Success";
	const char* kRequestError = "Error";

	const char* kRequestVerify = "UserVerify";
	const char* kRequestGetMyAnimelist = "GetMyAnimelist";

	const char* kChiika = "Chiika";
	const char* kMyAnimeList = "MyAnimeList";
	const char* kUserInfo = "UserInfo";
	const char* kMangaList = "MangaList";
	const char* kUpdateList = "UpdateList";
	const char* kAnimeDetails = "AnimeDetails";
	const char* kAnime = "anime";
	const char* kManga = "manga";
	//Anime Keys
	const char* kSeriesAnimedbId = "series_animedb_id";
	const char* kSeriesTitle = "series_title";
	const char* kSeriesSynonyms = "series_synonyms";
	const char* kSeriesType = "series_type";
	const char* kSeriesEpisodes = "series_episodes";
	const char* kSeriesStatus = "series_status";
	const char* kSeriesStart = "series_start";
	const char* kSeriesEnd = "series_end";
	const char* kSeriesImage = "series_image";
	//~
	//User Anime Entry
	const char* kMyId = "my_id";
	const char* kMyWatchedEpisodes = "my_watched_episodes";
	const char* kMyStartDate = "my_start_date";
	const char* kMyFinishDate = "my_finish_date";
	const char* kMyScore = "my_score";
	const char* kMyStatus = "my_status";
	const char* kMyRewatching = "my_rewatching";
	const char* kMyRewatchingEp = "my_rewatching_ep";
	const char* kMyLastUpdated = "my_last_updated";
	//~

	//UserInfo
	const char* kUserId = "user_id";
	const char* kUserName = "user_name";
	const char* kUserWatching = "user_watching";
	const char* kUserCompleted = "user_completed";
	const char* kUserOnhold = "user_onhold";
	const char* kUserDropped = "user_dropped";
	const char* kUserPtw = "user_plantowatch";
	const char* kUserDaysSpentWatching = "user_days_spent_watching";
	const char* kUserReading = "user_reading";
	const char* kUserPtr = "user_plantoread";
	const char* kUserDaysSpentReading = "user_days_spent_watching";

	//~
	const char* kSeriesMangadbId = "series_mangadb_id";
	const char* kSeriesChapters = "series_chapters";
	const char* kSeriesVolumes = "series_volumes";

	const char* kMyReadChapters = "my_read_chapters";
	const char* kMyRereading = "my_rereading";
	const char* kMyReadVolumes = "my_read_volumes";
	const char* kMyRereadingChap = "my_rereading_chap";

	const char* kPass = "Pass";

	const char* kOperation = "Operation";

	const char* kId = "Id";
	const char* kSynopsis = "Synopsis";
	const char* kTags = "Tags";
	const char* kPremiered = "Premiered";
	const char* kProducers = "Producers";
	const char* kDurationPerEpisode = "DurationPerEpisode";
	const char* kScore = "Score";
	const char* kRanked = "Ranked";
	const char* kPopularity = "Popularity";
	const char* kTag = "Tag";
	const char* kProducer = "Producer";

	typedef ChiikaApi::Vector<std::string>::type KeyList;

	void GetAnimeKeys(KeyList& keys)
	{
		keys.push_back(kSeriesAnimedbId);
		keys.push_back(kSeriesTitle);
		keys.push_back(kSeriesSynonyms);
		keys.push_back(kSeriesEpisodes);
		keys.push_back(kSeriesType);
		keys.push_back(kSeriesStatus);
		keys.push_back(kSeriesStart);
		keys.push_back(kSeriesEnd);
		keys.push_back(kSeriesImage);
	}
	void GetUserAnimeEntryKeys(KeyList& keys)
	{
		keys.push_back(kMyId);
		keys.push_back(kMyWatchedEpisodes);
		keys.push_back(kMyRewatchingEp);
		keys.push_back(kMyScore);
		keys.push_back(kMyRewatching);
		keys.push_back(kMyStatus);
		keys.push_back(kMyStartDate);
		keys.push_back(kMyFinishDate);
		keys.push_back(kMyLastUpdated);
	}
	void GetUserInfoKeys(KeyList& keys)
	{
		keys.push_back(kUserId);
		keys.push_back(kUserName);
		keys.push_back(kPass);
		keys.push_back(kUserWatching);
		keys.push_back(kUserCompleted);
		keys.push_back(kUserOnhold);
		keys.push_back(kUserDropped);
		keys.push_back(kUserPtw);
		keys.push_back(kUserDaysSpentWatching);
		keys.push_back(kUserReading);
		keys.push_back(kUserPtr);
		keys.push_back(kUserDaysSpentReading);
	}

}


//----------------------------------------------------------------------------
#endif