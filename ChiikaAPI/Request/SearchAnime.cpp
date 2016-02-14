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
//	Date:	 2.2.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "SearchAnime.h"
#include "Database/LocalDataManager.h"
#include "Root/Root.h"
#include "Logging/ChiString.h"
#include "Request/MalManager.h"
#include "Logging/FileHelper.h"
#include "Common/MyAnimeListUtility.h"

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	SearchAnimeRequest::SearchAnimeRequest()
	{
		m_sName = kRequestSearchAnime;

		KeyMap ctmap =
		{
			std::make_pair("synopsis", kSynopsis),
			std::make_pair("title", kSeriesTitle),
			std::make_pair("english", kSeriesEnglish),
			std::make_pair("synonyms", kSeriesSynonyms),
			std::make_pair("start_date", kSeriesStart),
			std::make_pair("end_date", kSeriesEnd),
			std::make_pair("image", kSeriesImage)
		};

		convertToMalApiConvention = ctmap;
	}
	//----------------------------------------------------------------------------
	SearchAnimeRequest::~SearchAnimeRequest()
	{
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::OnSuccess()
	{
		ChiString data = m_Curl->GetResponse();

		pugi::xml_document doc;
		doc.load(data.c_str());

		XmlNode root = doc.child(kAnime);
		XmlNode entry = root.child("entry");

		DictionaryBase dict;

		XmlForeach(child, entry)
		{
			const char* name = child.name();
			const char* val = child.text().get();

			dict.SetKeyValue(name, val);
		}

		if (!EmptyKey(dict, "title"))
		{
			AnimeList& list = Root::Get()->GetMyAnimelistManager()->GetAnimes();

			AnimeList::iterator It = list.find(std::to_string(m_AnimeId));

			if (It != list.end())
			{
				Anime& a = It->second;

				KeyMap keys = dict.GetKeys();
				KeyMap::iterator It = keys.begin();


				ForEachOnStd(It, keys)
				{
					KeyMap::iterator keyMapIt = convertToMalApiConvention.find(It->first);

					if (keyMapIt != convertToMalApiConvention.end())
					{
						ChiString malKey = convertToMalApiConvention.find(It->first)->second;

						a.SetKeyValue(malKey, It->second);
					}
				}

				a.Misc.SetKeyValue("synopsis", keys.find("synopsis")->second);
				a.Misc.SetKeyValue(kAvgScore, keys.find("score")->second);
				
			}
		}
		RequestInterface::OnSuccess();

		Root::Get()->GetLocalDataManager()->SaveCachedAnimeList();
	}
	//----------------------------------------------------------------------------
	int SearchAnimeRequest::GetAnimeId() const
	{
		return m_AnimeId;
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::SetAnimeId(int id)
	{
		m_AnimeId = id;
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::SetOptions()
	{
		int method;
		method = CURLOPT_HTTPGET;

		ChiString userName = Root::Get()->GetUser().GetKeyValue(kUserName);
		ChiString passWord = Root::Get()->GetUser().GetKeyValue(kPass);


		m_Curl->SetAuth(userName + ":" + passWord);
		m_Curl->SetMethod(method, "");
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::SetKeywords(const std::string& keywords)
	{
		Anime anime = Root::Get()->GetMyAnimelistManager()->GetAnimeById(m_AnimeId);

		if (!(keywords.size() > 0))
		{
			if (!EmptyKey(anime, kSeriesAnimedbId))
			{
				std::string animeName = anime.GetKeyValue(kSeriesTitle);

				animeName = MyAnimelistUtility::PrepareTitleForSearching(animeName);

				ChiString url = "http://myanimelist.net/api/anime/search.xml?q=" + animeName;

				m_Curl->SetUrl(url);

				m_Curl->SetReady();
			}
		}
	}
	//----------------------------------------------------------------------------
	void SearchAnimeRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}