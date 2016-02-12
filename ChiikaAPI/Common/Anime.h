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
		Unknown = 0,
		TV = 1,
		OVA = 2,
		Movie = 3,
		Special = 4,
		ONA = 5,
		Music = 6
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
	struct MalApiExport Timezone
	{
		ChiString TimezoneIdentifier;
		ChiString Name;
		ChiString Offset; //To Utc
	};
	struct MalApiExport UserTimezoneInfo
	{
		ChiString Name;
		long Bias;
	};
	class MalApiExport Airdate
	{
	public:
		Timezone TimeZone;
		ChiString RdDate;
		ChiString RdTime;
		int Weekday;
		ChiString RdWeekday;
	};
	class MalApiExport SenpaiItem
	{
	public:
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
	class MalApiExport Studio : public DictionaryBase
	{
	public:
		Studio(){}

	};
	class MalApiExport Character : public DictionaryBase
	{
	public:
		Character(){}

	};
	class MalApiExport Genre : public DictionaryBase
	{
	public:
		Genre(){}

	};
	class MalApiExport AnimeMisc : public DictionaryBase
	{
	public:
		AnimeMisc() {}

		std::vector<DictionaryBase> Studios;
		std::vector<DictionaryBase> Characters;
		std::vector<DictionaryBase> Genres;
	};

	class MalApiExport Anime : public DictionaryBase
	{
	public:
		Anime();
		~Anime()
		{


		}
	public:
		AnimeMisc Misc;
	};

	class MalApiExport UserAnimeEntry : public DictionaryBase
	{
	public:
		UserAnimeEntry();
	};
}
//----------------------------------------------------------------------------
#endif