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
#ifndef __Anime_h__
#define __Anime_h__
//----------------------------------------------------------------------------
#include "Common\Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	enum AnimeType
	{
		TV = 1,
		OVA = 2,
		Movie = 3
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
	struct MalApiExport AnimeDetails
	{
		ChiString Synopsis;
		StringVector Tags;
		ChiString Premiered;
		StringVector Producers;
		ChiString DurationPerEpisode;

		AnimeDetails()
		{

		}
	};
	struct MalApiExport AnimeStatistics
	{
		double Score;
		int Ranked;
		int Popularity;

		AnimeStatistics()
		{
			Score = 0;
			Ranked = 0;
			Popularity = 0;
		}
	};

	class MalApiExport Anime
	{
	public:
		Anime();
		void SetKeyValue(const std::string&, const std::string&);

		const std::string& GetKeyValue(const std::string&);
		bool ContainsKey(const std::string&);

	private:
		KeyMap m_KeyMap;
	public:
		//Experimental
		AnimeDetails ExtraDetails;
		AnimeStatistics Statistics;
	};

	class MalApiExport UserAnimeEntry
	{
	public:
		Anime Anime;

		void SetKeyValue(const std::string&, const std::string&);
		const std::string& GetKeyValue(const std::string&);
		bool ContainsKey(const std::string&);
	private:
		KeyMap m_KeyMap;
	public:

		UserAnimeEntry();
	};
}
//----------------------------------------------------------------------------
#endif