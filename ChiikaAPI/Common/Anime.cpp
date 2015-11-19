//----------------------------------------------------------------------------
//Py Version Header Generator
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
#include "Anime.h"

#include "Database\JsKeys.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	Anime::Anime()
	{
		Id = UnknownAnimeId;
		Title = "";
		English = "";
		EpisodeCount = 0;
		Type = AnimeType::TV;
		Status = AnimeStatus::NotAired;
		StartDate = "";
		EndDate = "";
		Image = "";

	}
	//----------------------------------------------------------------------------
	void Anime::SetKeyValue(const std::string& key,const std::string& value)
	{
		if(key == kSeriesAnimedbId)
		{
			Id = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesTitle)
		{
			Title = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesSynonyms)
		{
			English = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesType)
		{
			Type = (AnimeType)atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesEpisodes)
		{
			EpisodeCount = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesStatus)
		{
			Status = (AnimeStatus)atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesStart)
		{
			StartDate = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesEnd)
		{
			EndDate = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesImage)
		{
			Image = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
	}
	//----------------------------------------------------------------------------
	const std::string& Anime::GetKeyValue(const std::string& key)
	{
		KeyMap::iterator It = m_KeyMap.find(key);
		if(It != m_KeyMap.end())
		{
			return m_KeyMap.find(key)->second;
		}
		return key;
	}
	//----------------------------------------------------------------------------
	bool Anime::ContainsKey(const std::string& key)
	{
		KeyMap::iterator It = m_KeyMap.find(key);

		if(It != m_KeyMap.end())
			return true;
		return false;
	}
	//----------------------------------------------------------------------------
	UserAnimeEntry::UserAnimeEntry()
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
	//----------------------------------------------------------------------------
	void UserAnimeEntry::SetKeyValue(const std::string& key,const std::string& value)
	{
		if(key == kMyId)
		{
			MyId = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyWatchedEpisodes)
		{
			WatchedEpisodes = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyRewatchingEp)
		{
			RewatchingEp = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyScore)
		{
			Score = (AnimeType)atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyRewatching)
		{
			Rewatching = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kSeriesStatus)
		{
			Status = (AnimeUserStatus)atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyStartDate)
		{
			StartDate = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyFinishDate)
		{
			EndDate = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}
		if(key == kMyLastUpdated)
		{
			LastUpdated = value;
			m_KeyMap.insert(KeyMap::value_type(key,value));
		}

	}
	//----------------------------------------------------------------------------
	const std::string& UserAnimeEntry::GetKeyValue(const std::string& key)
	{
		KeyMap::iterator It = m_KeyMap.find(key);
		if(It != m_KeyMap.end())
		{
			return m_KeyMap.find(key)->second;
		}
		return key;
	}
	//----------------------------------------------------------------------------
	bool UserAnimeEntry::ContainsKey(const std::string& key)
	{
		KeyMap::iterator It = m_KeyMap.find(key);

		if(It != m_KeyMap.end())
			return true;
		return false;
	}
}