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
#ifndef __SeasonManager_h__
#define __SeasonManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Common/Singleton.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	typedef Map<ChiString,Timezone>::type TimezoneMap;
	typedef Vector<SenpaiItem>::type SenpaiData;

	struct MalApiExport SeasonInfo
	{
		ChiString Name;
		ChiString StartDate;
	};

	class MalApiExport SeasonManager
	{
	public:
		SeasonManager();

		void SetTimezones(TimezoneMap map);
		void SetSenpaiData(SenpaiData sd);

		SenpaiItem GetSenpaiDataFromMalId(int malid);

		SenpaiData GetSenpaiData(); //Returns SenpaiItem which are on the anime list

		UserTimezoneInfo GetUserTimezone();

		Timezone GetSenpaiAirdateFromLocalTimezone();
		virtual SenpaiItem GetClosest();

		SenpaiData GetShowsFromDayAway(int day);
		
		void SetSeasonInfo(SeasonInfo inf);
		SeasonInfo GetSeasonInfo() const;

		TimezoneMap m_Timezones;
		SenpaiData m_SenpaiData;

		SeasonInfo m_CurrentSeason;
	};
}
#endif // SEASONMANAGER_H
