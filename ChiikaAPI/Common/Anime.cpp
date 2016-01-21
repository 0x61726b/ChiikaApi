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

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	Anime::Anime()
	{
	}
	//----------------------------------------------------------------------------
	void Anime::SetKeyValue(const std::string& key,const std::string& value)
	{
		m_KeyMap.insert(KeyMap::value_type(key, value));
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
	}
	//----------------------------------------------------------------------------
	void UserAnimeEntry::SetKeyValue(const std::string& key,const std::string& value)
	{
		m_KeyMap.insert(KeyMap::value_type(key, value));
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