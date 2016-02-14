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
#include "Stable.h"
#include "GetMyMangaList.h"
#include "Database/LocalDataManager.h"
#include "Request/MalManager.h"
#include "Root/Root.h"

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	GetMyMangaListRequest::GetMyMangaListRequest()
	{
		m_sName = kRequestGetMyMangalist;
	}
	//----------------------------------------------------------------------------
	GetMyMangaListRequest::~GetMyMangaListRequest()
	{
	}
	//----------------------------------------------------------------------------
	void GetMyMangaListRequest::OnSuccess()
	{
		pugi::xml_document doc;

		bool parse = doc.load(m_Curl->GetResponse().c_str());


		KeyList keys;
		GetUserMangaEntryKeys(keys);

		UserInfo ui = Root::Get()->GetUser();

		XmlNode  myanimelist = doc.child("myanimelist");
		XmlNode  user = myanimelist.child("myinfo");



		for(XmlNode userChild = user.first_child(); userChild; userChild = userChild.next_sibling())
		{
			const char* name = userChild.name();
			const char* val = userChild.text().get();

			if(strcmp(name,kUserDaysSpentWatching) == 0)
				name = kUserDaysSpentReading;

			if(strcmp(name,kUserId) == 0 || strcmp(name,kUserName) == 0)
			{
				ui.SetKeyValue(name,val);
			}
			else
			{
				ui.Manga.SetKeyValue(name,val);
			}
		}
		Root::Get()->SetUser(ui);

		UserMangaList list;
		MangaList animeList;
		for(XmlNode manga = myanimelist.child(kManga); manga; manga = manga.next_sibling())
		{
			Manga nManga;
			UserMangaEntry info;
			for(XmlNode mangaChild = manga.first_child(); mangaChild; mangaChild = mangaChild.next_sibling())
			{
				const char* name = mangaChild.name();
				const char* val = mangaChild.text().get();

				nManga.SetKeyValue(name,val);
				info.SetKeyValue(name,val);
			}
			animeList.insert(ChiikaApi::MangaList::value_type(nManga.GetKeyValue(kSeriesMangadbId),nManga));
			list.insert(UserMangaList::value_type(nManga.GetKeyValue(kSeriesMangadbId),info));
		}

		Root::Get()->GetMyAnimelistManager()->AddMangaList(list);
		Root::Get()->GetMyAnimelistManager()->AddMangaList(animeList);


		if(Root::Get()->GetLocalDataManager())Root::Get()->GetLocalDataManager()->SaveMangaList();
		if(Root::Get()->GetLocalDataManager())Root::Get()->GetLocalDataManager()->SaveUserInfo();

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void GetMyMangaListRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void GetMyMangaListRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void GetMyMangaListRequest::SetPostData()
	{

	}
	//----------------------------------------------------------------------------
	void GetMyMangaListRequest::SetOptions()
	{
		ChiString url;
		int method;
		UserInfo ui = Root::Get()->GetUser();

		ChiString userName = ui.GetKeyValue(kUserName);
		ChiString passWord = ui.GetKeyValue(kPass);

		url = "http://myanimelist.net/malappinfo.php?u=" + userName + "&type=manga&status=all";
		method = CURLOPT_HTTPGET;

		m_Curl->SetUrl(url);
		m_Curl->SetAuth(userName + ":" + passWord);
		m_Curl->SetMethod(method,"");

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void GetMyMangaListRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------