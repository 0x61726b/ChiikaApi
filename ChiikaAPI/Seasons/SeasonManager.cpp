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
#include "Seasons/SeasonManager.h"
#include "Request/MalManager.h"

#if YUME_PLATFORM == YUME_PLATFORM_WIN32
#include <Windows.h>
#endif
tm* GetTimeinfo()
{
	time_t rawtime;
	tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return timeinfo;
}
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//Uhh
	std::map<int,int> daymap =
	{
		std::make_pair(0,7), //Sunday
		std::make_pair(1,1), //Monday
		std::make_pair(2,2), //Tuesday
		std::make_pair(3,3), //Wed
		std::make_pair(4,4), //Thursday
		std::make_pair(5,5), //Friday
		std::make_pair(6,6), //Saturday
	};
	SeasonManager::SeasonManager()
	{

	}
	//----------------------------------------------------------------------------
	void SeasonManager::SetTimezones(TimezoneMap map)
	{
		m_Timezones = map;
	}
	//----------------------------------------------------------------------------
	void SeasonManager::SetSenpaiData(SenpaiData sd)
	{
		m_SenpaiData = sd;
	}
	//----------------------------------------------------------------------------
	SenpaiItem SeasonManager::GetSenpaiDataFromMalId(int malid)
	{
		SenpaiData::iterator It = m_SenpaiData.begin();
		SenpaiItem si;
		ForEachOnStd(It,m_SenpaiData)
		{
			if(It->MalID == malid)
			{
				si = *It;
				break;
			}
		}
		return si;
	}
	//----------------------------------------------------------------------------
	SenpaiData SeasonManager::GetSenpaiData()
	{
		UserAnimeList list = MalManager::Get()->GetAnimeList();

		SenpaiData sd;

		SenpaiData::iterator It = m_SenpaiData.begin();

		ForEachOnStd(It,m_SenpaiData)
		{
			if(list.find(std::to_string(It->MalID)) != list.end())
			{
				sd.push_back(*It);
			}
		}
		return sd;
	}
	//----------------------------------------------------------------------------
	Timezone SeasonManager::GetSenpaiAirdateFromLocalTimezone()
	{
		UserTimezoneInfo tz = GetUserTimezone();


		TimezoneMap::iterator It = m_Timezones.begin();
		Timezone senpaiAirdate;

		ForEachOnStd(It,m_Timezones)
		{
			if(atoi(It->first.c_str()) == tz.Bias)
			{
				senpaiAirdate = It->second;
			}
		}


		return senpaiAirdate;
	}
	//----------------------------------------------------------------------------
	SenpaiItem SeasonManager::GetClosest()
	{
		//SenpaiData sd = GetSenpaiData();
		//Timezone userTimezone = GetSenpaiAirdateFromLocalTimezone();
		//SenpaiItem closest;
		//if(sd.size() > 0)
		//{
		//	tm* timeinfo = GetTimeinfo();
		//	int localHours = timeinfo->tm_hour;
		//	int localMins = timeinfo->tm_min;

		//	int minimumDay = 7;
		//	int minimumHour = 24;
		//	int minimumMinutes = 59;
		//	int localDay = daymap.find(timeinfo->tm_wday)->second;

		//	for(int i=0; i < sd.size(); i++)
		//	{

		//		if(IsValidIt(sd[i].Airdates.find(userTimezone.Offset),sd[i].Airdates))
		//		{
		//			Airdate ad = sd[i].Airdates.find(userTimezone.Offset)->second;

		//			int showDay = ad.Weekday;
		//			int showHour = (ad.RdTime.left(2).toInt());
		//			int showMins = (ad.RdTime.right(2).toInt());

		//			int remainingHours = showHour - timeinfo->tm_hour;
		//			int remainingMinutes = showMins - timeinfo->tm_min;

		//			int remainingDays = (showDay - localDay);

		//			if(remainingDays < 0)
		//				remainingDays += 7;

		//			//minimumDay = min(remainingDays,minimumDay);

		//			if(remainingDays == 0 && remainingHours < 0)
		//				continue;

		//			if(remainingDays < minimumDay)
		//			{
		//				minimumDay = remainingDays;
		//			}
		//			else
		//			{

		//			}


		//		}
		//	}
		//	SenpaiData shows = GetShowsFromDayAway(minimumDay);
		//	SenpaiData::iterator it = shows.begin();
		//	ForEachOnStd(it,shows)
		//	{
		//		Airdate ad = it->Airdates.find(userTimezone.Offset)->second;

		//		int showDay = ad.Weekday;
		//		int showHour = (ad.RdTime.left(2).toInt());
		//		int showMins = (ad.RdTime.right(2).toInt());

		//		int remainingHours = showHour - timeinfo->tm_hour;
		//		int remainingMinutes = showMins - timeinfo->tm_min;
		//		if(remainingHours < 0)
		//		{
		//			remainingHours += 24;
		//		}
		//		if(remainingMinutes<0)
		//		{
		//			remainingMinutes += 60;
		//			remainingHours--;
		//		}

		//		if(remainingHours <= minimumHour)
		//		{
		//			minimumHour = remainingHours;
		//			closest = *it;
		//			if(remainingMinutes < minimumMinutes)
		//			{
		//				minimumMinutes = remainingMinutes;
		//				closest = *it;
		//			}

		//		}


		//	}
		//}
		//return closest;
		return SenpaiItem();
	}
	//----------------------------------------------------------------------------
	SenpaiData SeasonManager::GetShowsFromDayAway(int day)
	{
		//SenpaiData sd = GetSenpaiData();
		//SenpaiData out;
		//Timezone userTimezone = GetSenpaiAirdateFromLocalTimezone();
		//tm* timeinfo = GetTimeinfo();;
		//int localDay = daymap.find(timeinfo->tm_wday)->second;

		//for(int i=0; i < sd.size(); i++)
		//{
		//	if(IsValidIt(sd[i].Airdates.find(userTimezone.Offset),sd[i].Airdates))
		//	{
		//		Airdate ad = sd[i].Airdates.find(userTimezone.Offset)->second;
		//		int showDay = ad.Weekday;
		//		int showHour = (ad.RdTime.left(2).toInt());
		//		int showMins = (ad.RdTime.right(2).toInt());


		//		int remainingDays = (showDay - localDay);

		//		if(remainingDays < 0)
		//			remainingDays += 7;

		//		if(remainingDays == day)
		//		{
		//			out.push_back(sd[i]);
		//		}
		//	}
		//}
		//return out;
		return SenpaiData();
	}
	//----------------------------------------------------------------------------
	UserTimezoneInfo SeasonManager::GetUserTimezone()
	{
#if YUME_PLATFORM == YUME_PLATFORM_WIN32
		TIME_ZONE_INFORMATION tz;
		GetTimeZoneInformation(&tz);

		UserTimezoneInfo utz;
		/*utz.Name = (tz.DaylightName);*/
		utz.Bias = -tz.Bias*60; //convert to seconds UTC = local time + bias
		return utz;
#endif
	}
	//----------------------------------------------------------------------------
	template<> SeasonManager* Singleton<SeasonManager>::msSingleton = 0;
	SeasonManager& SeasonManager::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
	SeasonManager* SeasonManager::GetPtr(void)
	{
		return msSingleton;
	}
}

