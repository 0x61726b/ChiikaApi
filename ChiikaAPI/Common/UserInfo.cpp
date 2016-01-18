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

	}
	//----------------------------------------------------------------------------
	void UserInfo::SetKeyValue(const std::string& key,const std::string& value)
	{
		m_KeyMap.insert(KeyMap::value_type(key, value));
	}
	//----------------------------------------------------------------------------
	void UserInfo::SetUserName(const std::string& u)
	{
		
	}
	//----------------------------------------------------------------------------
	void UserInfo::SetPass(const std::string& p)
	{
		
	}
	//----------------------------------------------------------------------------
}