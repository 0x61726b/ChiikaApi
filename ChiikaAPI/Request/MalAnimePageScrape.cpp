//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2015  arkenthera
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
//	authors: arkenthera
//	Date:	 24.1.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "MalAnimePageScrape.h"
#include "Database\LocalDataManager.h"
#include "Root\Root.h"
#include "Logging\ChiString.h"
#include "Logging\LogManager.h"
#include "Request\MalManager.h"
#include "Logging\FileHelper.h"
#include "Common\MyAnimelistUtility.h"

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	AnimePageScrapeRequest::AnimePageScrapeRequest()
	{
		m_sName = kRequestAnimePageScrape;
	}
	//----------------------------------------------------------------------------
	AnimePageScrapeRequest::~AnimePageScrapeRequest()
	{
	}
	//----------------------------------------------------------------------------
	void AnimePageScrapeRequest::OnSuccess()
	{

		ChiString data = m_Curl->GetResponse();

		//AnimeMisc result = MyAnimelistUtility::ParseAnimePage(data);


		AnimeList& list = Root::Get()->GetMyAnimelistManager()->GetAnimes();

		AnimeList::iterator It = list.find(std::to_string(m_AnimeId));

		if(It != list.end())
		{
			Anime& a = It->second;

			AnimeMisc miscKappa;
			
			DictionaryBase genre;
			genre.SetKeyValue(kGenre,"Test");

			DictionaryBase genre2;
			genre2.SetKeyValue(kGenre,"Test 2");

			DictionaryBase genre3;
			genre3.SetKeyValue(kGenre,"Test 3");
			
			miscKappa.Genres.push_back(genre);
			miscKappa.Genres.push_back(genre2);
			miscKappa.Genres.push_back(genre3);

			a.Misc = miscKappa;
		}

		Root::Get()->GetLocalDataManager()->SaveAnimeList();

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void AnimePageScrapeRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void AnimePageScrapeRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void AnimePageScrapeRequest::SetAnimeId(int id)
	{
		m_AnimeId = id;
	}
	//----------------------------------------------------------------------------
	void AnimePageScrapeRequest::SetOptions()
	{
		int method;
		method = CURLOPT_HTTPGET;
		ChiString url = "http://myanimelist.net/anime/" + std::to_string(m_AnimeId);

		m_Curl->SetUrl(url);

		m_Curl->SetMethod(method,"");

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void AnimePageScrapeRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}