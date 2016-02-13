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
#include "GetMyAnimelist.h"
#include "Database\LocalDataManager.h"
#include "Request\MalManager.h"
#include "Root\Root.h"

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	GetMyAnimeListRequest::GetMyAnimeListRequest()
	{
		m_sName = kRequestGetMyAnimelist;
	}
	//----------------------------------------------------------------------------
	GetMyAnimeListRequest::~GetMyAnimeListRequest()
	{
	}
	//----------------------------------------------------------------------------
	void GetMyAnimeListRequest::OnSuccess()
	{
		pugi::xml_document doc;

		bool parse = doc.load(m_Curl->GetResponse().c_str());

		if(!parse)
		{
			RequestInterface::OnError();
			return;
		}

		KeyList keys;
		GetUserAnimeEntryKeys(keys);

		UserInfo ui = Root::Get()->GetUser();

		pugi::xml_node  myanimelist = doc.child("myanimelist");
		pugi::xml_node  user = myanimelist.child("myinfo");

		for(pugi::xml_node userChild = user.first_child(); userChild; userChild = userChild.next_sibling())
		{
			const char* name = userChild.name();
			const char* val = userChild.text().get();

			if(strcmp(name,kUserId) == 0 || strcmp(name,kUserName) == 0)
			{
				ui.SetKeyValue(name,val);
			}
			else
			{
				ui.Anime.SetKeyValue(name,val);
			}
		}
		Root::Get()->SetUser(ui);

		UserAnimeList list;
		AnimeList animeList;

		KeyList animeKeys;
		GetAnimeKeys(animeKeys);

		for(pugi::xml_node anime = myanimelist.child(kAnime); anime; anime = anime.next_sibling())
		{
			UserAnimeEntry info;
			Anime animeEntry;
			for(pugi::xml_node animeChild = anime.first_child(); animeChild; animeChild = animeChild.next_sibling())
			{
				const char* name = animeChild.name();
				const char* val = animeChild.text().get();

				KeyList::iterator it = std::find(keys.begin(),keys.end(),name);

				if(it != keys.end())
				{
					info.SetKeyValue(name,val);
				}

				KeyList::iterator It = std::find(animeKeys.begin(),animeKeys.end(),name);

				if(It != animeKeys.end())
				{
					animeEntry.SetKeyValue(name,val);
				}
			}
			list.insert(UserAnimeList::value_type(info.GetKeyValue(kSeriesAnimedbId),info));
			animeList.insert(AnimeList::value_type(info.GetKeyValue(kSeriesAnimedbId),animeEntry));
		}

		Root::Get()->GetMyAnimelistManager()->AddAnimeList(list);
		Root::Get()->GetMyAnimelistManager()->AddAnimeList(animeList);




		if(Root::Get()->GetLocalDataManager())Root::Get()->GetLocalDataManager()->SaveAnimeList();
		if(Root::Get()->GetLocalDataManager())Root::Get()->GetLocalDataManager()->SaveCachedAnimeList();
		if(Root::Get()->GetLocalDataManager())Root::Get()->GetLocalDataManager()->SaveUserInfo();

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void GetMyAnimeListRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void GetMyAnimeListRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void GetMyAnimeListRequest::SetPostData()
	{

	}
	//----------------------------------------------------------------------------
	void GetMyAnimeListRequest::SetOptions()
	{
		ChiString url;
		int method;
		UserInfo ui = Root::Get()->GetUser();

		ChiString userName = ui.GetKeyValue(kUserName);
		ChiString passWord = ui.GetKeyValue(kPass);

		url = "http://myanimelist.net/malappinfo.php?u=" + userName + "&type=anime&status=all";
		method = CURLOPT_HTTPGET;

		m_Curl->SetUrl(url);
		m_Curl->SetAuth(userName + ":" + passWord);
		m_Curl->SetMethod(method,"");


		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void GetMyAnimeListRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------