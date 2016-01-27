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
#ifndef __ChiChiString_h__
#define __ChiChiString_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport ChiStringUtil
	{
	public:
		ChiStringUtil();
		std::string GetMiddle(std::string str,std::size_t pos,std::size_t count);
		virtual std::string GetLeft(std::string str,std::size_t count);
		std::string GetRight(std::string str,std::size_t count);
		std::string Trim(std::string);

		std::string ParseSubelement(std::string c,std::string start,std::string end);
	};
}
//----------------------------------------------------------------------------
#endif