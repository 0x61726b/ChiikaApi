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
#ifndef __ParsingManager_h__
#define __ParsingManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "pugixml.hpp"
#include "Common/Singleton.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport ParsingManager : public Singleton<ParsingManager>
	{
	public:
		bool ParseVerifyRequest(const String& data);
		AnimeList ParseSearchResult(const String& data);
		AnimeList ParseGetUserAnimeList(const String& data);
		MangaList ParseGetUserMangaList(const String& data);
		const AnimeInfo& ParseCRUDAnime(const String& data);
		String ParseAnilistAuth(const String& data);
		void ParseAnilistSearchAnime(const String& data);
		AnimeInfo ParseAnimeScrape(const String& data,int Id);
		void ParseUserPage(const String& data);
		void Parse(ThreadedRequest* r);


		void ParseSenpai(const String& data);

		std::vector<String> GetItemsSeperatedBy(String data,String seperator);
		String ParseWebPage(String data,String searchStart,String searchEnd);
		String RemoveLink(String data);
		String RemoveHTMLElements(String data);
		bool CheckValidLink(String s);
		//Singleton Interface
	public:
		static ParsingManager& Get();
		static ParsingManager* GetPtr();
		//~
	};
}
//----------------------------------------------------------------------------
#endif
