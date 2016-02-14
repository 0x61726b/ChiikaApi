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
//
//	Date: 21.1.2016
//	authors: arkenthera
//	Description:
//----------------------------------------------------------------------------
#ifndef __Manga_h__
#define __Manga_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	enum MangaType
	{
		Normal = 1,
		Novel = 2,
		Oneshot = 3,
		Doujinshi = 4,
		Manwha = 5,
		Manhua = 6
	};
	enum MangaUserStatus
	{
		Reading = 1,
		MangaCompleted = 2,
		MangaOnHold = 3,
		MangaDropped = 4,
		PlanToRead = 6
	};

	enum MangaStatus
	{
		MangaFinished = 2,
		Publishing = 1,
		NotYetPublished = 3
	};

	class MalApiExport Manga : public DictionaryBase
	{
	public:
		Manga();
	};
	class MalApiExport UserMangaEntry : public DictionaryBase
	{
	public:
		UserMangaEntry();
	};
}

#endif