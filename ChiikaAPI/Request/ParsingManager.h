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
		bool ParseVerifyRequest(const ChiString& data);
		AnimeList ParseSearchResult(const ChiString& data);
		AnimeList ParseGetUserAnimeList(const ChiString& data);
		MangaList ParseGetUserMangaList(const ChiString& data);
		const UserAnimeEntry& ParseCRUDAnime(const ChiString& data);
		ChiString ParseAnilistAuth(const ChiString& data);
		void ParseAnilistSearchAnime(const ChiString& data);
		UserAnimeEntry ParseAnimeScrape(const ChiString& data,int Id);
		void ParseUserPage(const ChiString& data);
		void Parse(ThreadedRequest* r);


		void ParseSenpai(const ChiString& data);

		std::vector<ChiString> GetItemsSeperatedBy(ChiString data,ChiString seperator);
		ChiString ParseWebPage(ChiString data,ChiString searchStart,ChiString searchEnd);
		ChiString RemoveLink(ChiString data);
		ChiString RemoveHTMLElements(ChiString data);
		bool CheckValidLink(ChiString s);
		//Singleton Interface
	public:
		static ParsingManager& Get();
		static ParsingManager* GetPtr();
		//~
	};
}
//----------------------------------------------------------------------------
#endif
