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
#include "ChiString.h"
#include "boost\regex.hpp"
#include "Logging\LogManager.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	ChiStringUtil::ChiStringUtil()
	{
	}
	std::string ChiStringUtil::GetMiddle(std::string str,std::size_t pos,std::size_t count)
	{
		if(count < str.size())
			return str.substr(pos,count);
		if(count == -1)
			return str;
		if(count >= str.size())
			return str;
		return std::string();
	}
	//----------------------------------------------------------------------------
	std::string ChiStringUtil::GetLeft(std::string str,std::size_t count)
	{
		if(count >= str.size())
			return str;
		if(count < 0)
			return str;
		return str.substr(0,count);
	}
	//----------------------------------------------------------------------------
	std::string ChiStringUtil::GetRight(std::string str,std::size_t count)
	{
		if(count >= str.size())
			return str;
		if(count < 0)
			return str;
		return str.substr(str.size() - count,count);
	}
	//----------------------------------------------------------------------------
	std::string ChiStringUtil::Trim(std::string str)
	{
		std::string out = str;
		while(out.find_first_of(' ') == 0 || out.find_last_of(' ') == out.size() -1)
		{
			if(out.at(0) == ' ')
				out.replace(0,1,"");
			if(out.at(out.size()-1) == ' ')
				out.replace(out.size()-1,1,"");
		}
		return out;
	}
	//----------------------------------------------------------------------------
	ChiString ChiStringUtil::ParseSubelement(ChiString data, ChiString searchStart, ChiString searchEnd)
	{
		ChiStringUtil strUtil;
		int start = data.find(searchStart);
		int end = data.find(searchEnd,start);

		ChiString first = strUtil.GetMiddle(data,start,end-start);
		first = strUtil.GetMiddle(first,searchStart.size(),first.size() - searchStart.size());
		first = strUtil.Trim(first);
		
		return first;
	}
}
//----------------------------------------------------------------------------