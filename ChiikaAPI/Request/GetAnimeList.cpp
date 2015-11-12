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
#include "GetAnimeList.h"
#include "Database\LocalDataManager.h"
#include "Request\MalManager.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	GetAnimeListRequest::GetAnimeListRequest()
	{
		m_sName = "GetAnimeList";
	}
	//----------------------------------------------------------------------------
	GetAnimeListRequest::~GetAnimeListRequest()
	{
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::OnSuccess()
	{
		pugi::xml_document doc;

		bool parse = doc.load(m_Curl.GetResponse().c_str());

		if(!parse)
			return;


		pugi::xml_node  myanimelist = doc.child("myanimelist");
		pugi::xml_node  user = myanimelist.child("myinfo");
		pugi::xml_node  userWatching = user.child("user_watching");
		pugi::xml_node  user_completed = user.child("user_completed");
		pugi::xml_node  user_onhold = user.child("user_onhold");
		pugi::xml_node  user_dropped = user.child("user_dropped");
		pugi::xml_node  user_plantowatch = user.child("user_plantowatch");
		pugi::xml_node  user_days_spent_watching = user.child("user_days_spent_watching");

		ChiString userName = user.child("user_name").text().get();
		ChiString id = user.child("user_id").text().get();

		UserInfo ui = LocalDataManager::Get().GetUserInfo();
		ui.UserName = ToStd(userName);
		ui.AnimeStats.Watching = FromXMLValueToInt(userWatching);
		ui.AnimeStats.Completed = FromXMLValueToInt(user_completed);
		ui.AnimeStats.OnHold = FromXMLValueToInt(user_onhold);
		ui.AnimeStats.Dropped = FromXMLValueToInt(user_dropped);
		ui.AnimeStats.PlanToWatch = FromXMLValueToInt(user_plantowatch);
		ui.AnimeStats.DaySpentAnime = FromXMLValueToFloat(user_days_spent_watching);


		LocalDataManager::Get().SetUserInfo(ui);

		int animeCount = 0;
		UserAnimeList list;
		AnimeList animeList;
		for(pugi::xml_node anime = myanimelist.child("anime");anime;anime = anime.next_sibling())
		{
			pugi::xml_node  animeDbId = anime.child("series_animedb_id");
			pugi::xml_node  series_title = anime.child("series_title");
			pugi::xml_node  series_synonyms = anime.child("series_synonyms");
			pugi::xml_node  series_type = anime.child("series_type");
			pugi::xml_node  series_episodes = anime.child("series_episodes");
			pugi::xml_node  series_status = anime.child("series_status");
			pugi::xml_node  series_start = anime.child("series_start");
			pugi::xml_node  series_end = anime.child("series_end");
			pugi::xml_node  series_image = anime.child("series_image");
			pugi::xml_node  my_id = anime.child("my_id"); //What does this even mean?
			pugi::xml_node  my_watched_episodes = anime.child("my_watched_episodes");
			pugi::xml_node  my_start_date = anime.child("my_start_date");
			pugi::xml_node  my_finish_date = anime.child("my_finish_date");
			pugi::xml_node  my_score = anime.child("my_score");
			pugi::xml_node  my_status = anime.child("my_status");
			pugi::xml_node  my_rewatching = anime.child("my_rewatching");
			pugi::xml_node  my_rewatching_ep = anime.child("my_rewatching_ep");
			pugi::xml_node  my_last_updated = anime.child("my_last_updated");
			//pugi::xml_node  my_finish_date = anime.child("my_finish_date");

			Anime Anime;
			Anime.Id = FromXMLValueToInt(animeDbId);
			Anime.Title = FromXMLValueToStd(series_title);
			Anime.English = FromXMLValueToStd(series_synonyms);
			Anime.Type = (AnimeType)FromXMLValueToInt(series_type);
			Anime.EpisodeCount = FromXMLValueToInt(series_episodes);

			Anime.Status = (AnimeStatus)FromXMLValueToInt(series_status);
			Anime.StartDate = FromXMLValueToStd(series_start);
			Anime.EndDate = FromXMLValueToStd(series_end);
			Anime.Image = FromXMLValueToStd(series_image);
			animeList.insert(AnimeList::value_type(Anime.Id,Anime));

			UserAnimeEntry info;
			info.Anime = Anime;
			info.MyId = FromXMLValueToInt(my_id);
			info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
			info.StartDate = FromXMLValueToStd(my_start_date);
			info.EndDate = FromXMLValueToStd(my_finish_date);
			info.Score = FromXMLValueToInt(my_score);
			info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
			info.Rewatching = FromXMLValueToInt(my_rewatching);
			info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
			info.LastUpdated = FromXMLValueToStd(my_last_updated);

			list.insert(UserAnimeList::value_type(Anime.Id,info));
			animeCount++;
		}
		MalManager::Get().AddAnimeList(list);
		MalManager::Get().AddAnimeList(animeList);

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::OnError()
	{

		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::Initialize()
	{
		m_Curl.Initialize();
		m_Curl.AddListener(this);
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::SetOptions()
	{
		ChiString url;
		int method;
		ChiString userName = LocalDataManager::Get().GetUserInfo().UserName;
		ChiString passWord =  LocalDataManager::Get().GetUserInfo().Pass;

		url = "http://myanimelist.net/malappinfo.php?u=" + userName + "&type=anime&status=all";
		method = CURLOPT_HTTPGET;

		m_Curl.SetUrl(url);
		m_Curl.SetAuth(userName + ":" + passWord);
		m_Curl.SetMethod(method,"");
		m_Curl.SetWriteFunction(NULL);
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::Initiate()
	{
		m_Curl.Perform();
	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------