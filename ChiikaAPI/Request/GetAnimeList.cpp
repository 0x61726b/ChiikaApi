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
#include "GetAnimeList.h"
#include "Database\LocalDataManager.h"
#include "Request\MalManager.h"

#include "Database\JsKeys.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	GetAnimeListRequest::GetAnimeListRequest(LocalDataManager* ldm)
		: RequestInterface(ldm)
	{
		m_sName = "GetAnimeList";
	}
	//----------------------------------------------------------------------------
	GetAnimeListRequest::GetAnimeListRequest()
		: RequestInterface(NULL)
	{
		m_sName = GetRequest(Requests::GetAnimelistRequest);
	}
	//----------------------------------------------------------------------------
	GetAnimeListRequest::~GetAnimeListRequest()
	{
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::OnSuccess()
	{
		pugi::xml_document doc;

		bool parse = doc.load(m_Curl.GetResponse().c_str());

		if (!parse)
			return;

		UserInfo::KeyList keys = UserInfo::GetKeys();

		UserInfo ui = m_pLocalData->GetUserInfo();

		pugi::xml_node  myanimelist = doc.child("myanimelist");
		pugi::xml_node  user = myanimelist.child("myinfo");

		for (pugi::xml_node userChild = user.first_child(); userChild; userChild = userChild.next_sibling())
		{
			const char* name = userChild.name();
			const char* val = userChild.text().get();

			ui.SetKeyValue(name, val);

		}
		m_pLocalData->SetUserInfo(ui);

		UserAnimeList list;
		AnimeList animeList;
		for (pugi::xml_node anime = myanimelist.child(kAnime); anime; anime = anime.next_sibling())
		{
			Anime Anime;
			UserAnimeEntry info;
			for (pugi::xml_node animeChild = anime.first_child(); animeChild; animeChild = animeChild.next_sibling())
			{
				const char* name = animeChild.name();
				const char* val = animeChild.text().get();

				Anime.SetKeyValue(name, val);
				info.SetKeyValue(name, val);
			}
			animeList.insert(ChiikaApi::AnimeList::value_type(Anime.Id, Anime));
			info.Anime = Anime;
			list.insert(UserAnimeList::value_type(Anime.Id, info));
		}
		MalManager::Get()->AddAnimeList(list);
		MalManager::Get()->AddAnimeList(animeList);

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::Initialize()
	{
		m_Curl.Initialize();
		m_Curl.AddListener(this);
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::SetPostData()
	{

	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::SetOptions()
	{
		ChiString url;
		int method;
		ChiString userName = m_pLocalData->GetUserInfo().UserName;
		ChiString passWord = m_pLocalData->GetUserInfo().Pass;

		url = "http://myanimelist.net/malappinfo.php?u=" + userName + "&type=anime&status=all";
		method = CURLOPT_HTTPGET;

		m_Curl.SetUrl(url);
		m_Curl.SetAuth(userName + ":" + passWord);
		m_Curl.SetMethod(method, "");
		m_Curl.SetWriteFunction(NULL);
	}
	//----------------------------------------------------------------------------
	void GetAnimeListRequest::Initiate()
	{
		m_Curl.Perform();
	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------