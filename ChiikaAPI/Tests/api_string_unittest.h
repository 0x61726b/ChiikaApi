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
#ifndef __Api_String_UnitTest_h__
#define __Api_String_UnitTest_h__
//----------------------------------------------------------------------------
#include "gmock\gmock.h"
//----------------------------------------------------------------------------
std::string GetMiddleTest(std::string str,std::size_t pos,std::size_t count)
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
std::string GetLeft(std::string str,std::size_t count)
{
	if(count >= str.size())
		return str;
	if(count < 0)
		return str;
	return str.substr(0,count);
}
//----------------------------------------------------------------------------
std::string GetRight(std::string str,std::size_t count)
{
	if(count >= str.size())
		return str;
	if(count < 0)
		return str;
	return str.substr(str.size() - count,count);
}
//----------------------------------------------------------------------------
std::string Trim(std::string str)
{
	std::string out = str;
	while(out.find_first_of(' ') == 0 || out.find_last_of(' ') == out.size() -1 )
	{
		if(out.at(0) == ' ')
			out.replace(0,1,"");
		if(out.at(out.size()-1) == ' ')
			out.replace(out.size()-1,1,"");
	}
	return out;
}
//Tests if mid(pos,n) returns correct result
//Works like substring
//----------------------------------------------------------------------------
TEST(ApiStringTest,ApiStringGetMiddle)
{
	std::string str = "Out of the silent planet.";
	std::size_t pos = 0;
	int n = 5; //Out o




	EXPECT_EQ("Out o",GetMiddleTest(str,pos,n));

	n = -1; //whole string

	EXPECT_EQ(str,GetMiddleTest(str,pos,n));

	n = str.size() + 10; //whole string

	EXPECT_EQ(str,GetMiddleTest(str,pos,n));
}

#endif
//----------------------------------------------------------------------------