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
#include "UserInfo.h"

#include "Database\JsKeys.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	UserInfo::UserInfo()
	{
		UserId = 0;
		UserName = "";
		Pass = "";
		ImageLink = "";
	}
	//----------------------------------------------------------------------------
	void UserInfo::SetKeyValue(const std::string& key, const std::string& value)
	{
		if (key == kUserId)
		{
			UserId = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserName)
		{
			UserName = value;
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserWatching)
		{
			AnimeStats.Watching = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserCompleted)
		{
			AnimeStats.Completed = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserOnhold)
		{
			AnimeStats.OnHold = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserDropped)
		{
			AnimeStats.Dropped = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserPtw)
		{
			AnimeStats.PlanToWatch = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
		if (key == kUserDaysSpentWatching)
		{
			AnimeStats.DaySpentAnime = atoi(ToStd(value));
			m_KeyMap.insert(KeyMap::value_type(key, value));
		}
	}
	//----------------------------------------------------------------------------

	//----------------------------------------------------------------------------
}