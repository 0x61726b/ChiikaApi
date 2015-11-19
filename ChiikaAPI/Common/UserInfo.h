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
#ifndef __UserInfo_h__
#define __UserInfo_h__
//----------------------------------------------------------------------------
#include "Common\Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	struct UserAnimeStats
	{
		int Watching;
		int Completed;
		int OnHold;
		int Dropped;
		int PlanToWatch;
		double DaySpentAnime;
		UserAnimeStats()
		{
			Watching = 0;
			Completed = 0;
			Dropped = 0;
			PlanToWatch = 0;
			OnHold = 0;
			DaySpentAnime = 0.0;
		}
	};
	typedef struct _UserMangaInfo
	{
		int Reading;
		int Completed;
		int OnHold;
		int Dropped;
		int PlanToRead;
		double DaysSpentReading;

		_UserMangaInfo()
		{
			Reading = 0;
			Completed = 0;
			OnHold = 0;
			Dropped = 0;
			PlanToRead = 0;
			DaysSpentReading = 0.0;
		}
	} UserMangaInfo;

	class MalApiExport UserInfo : public DictionaryBase
	{
	public:
		UserInfo();

	public:
		int UserId;
		ChiString UserName;
		ChiString Pass;
		ChiString ImageLink;

		UserAnimeStats AnimeStats;
		UserMangaInfo MangaInfo;

		void SetKeyValue(const std::string&, const std::string&);
	};
}
#endif