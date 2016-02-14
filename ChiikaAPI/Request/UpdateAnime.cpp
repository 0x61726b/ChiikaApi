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
#include "UpdateAnime.h"
#include "Database/LocalDataManager.h"
#include "Root/Root.h"
#include "Logging/ChiString.h"
#include "Request/MalManager.h"
#include "Logging/FileHelper.h"
#include "Common/MyAnimelistUtility.h"

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	UpdateAnimeRequest::UpdateAnimeRequest() :
		m_Anime(-1),
		m_NewProgress(-1),
		m_NewScore(-1),
		m_NewStatus(-1)
	{
		m_sName = kRequestUpdateAnime;
	}
	//----------------------------------------------------------------------------
	UpdateAnimeRequest::~UpdateAnimeRequest()
	{
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::OnSuccess()
	{
		ChiString data = m_Curl->GetResponse();
		
		UserAnimeList& list = Root::Get()->GetMyAnimelistManager()->GetAnimeList();

		UserAnimeList::iterator It = list.find(std::to_string(m_Anime));

		ChiString oldScore = It->second.GetKeyValue(kMyScore);
		ChiString oldProgress = It->second.GetKeyValue(kMyWatchedEpisodes);
		ChiString oldStatus = It->second.GetKeyValue(kMyStatus);

		ChiString newScore = oldScore;
		ChiString newProgress = oldProgress;
		ChiString newStatus = oldStatus;

		if (m_NewProgress != -1)
			newProgress = std::to_string(m_NewProgress);
		if (m_NewScore != -1)
			newScore = std::to_string(m_NewScore);
		if (m_NewStatus != -1)
			newStatus = std::to_string(m_NewStatus);



		It->second.SetKeyValue(kMyWatchedEpisodes, newProgress);
		It->second.SetKeyValue(kMyStatus, newStatus);
		It->second.SetKeyValue(kMyScore, newScore);
		
		Root::Get()->GetLocalDataManager()->SaveAnimeList();

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::SetAnimeId(int Anime)
	{
		m_Anime = Anime;
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::SetOptions()
	{
		int method;
		method = CURLOPT_HTTPPOST;

		ChiString userName = Root::Get()->GetUser().GetKeyValue(kUserName);
		ChiString passWord = Root::Get()->GetUser().GetKeyValue(kPass);

		UserAnimeList list = Root::Get()->GetMyAnimelistManager()->GetAnimeList();

		UserAnimeList::iterator It = list.find(std::to_string(m_Anime));

		if (It != list.end())
		{
			m_Curl->SetAuth(userName + ":" + passWord);
			m_Curl->SetUrl("http://myanimelist.net/api/animelist/update/" + It->second.GetKeyValue(kSeriesAnimedbId) + ".xml");

			ChiString oldScore = It->second.GetKeyValue(kMyScore);
			ChiString oldProgress = It->second.GetKeyValue(kMyWatchedEpisodes);
			ChiString oldStatus = It->second.GetKeyValue(kMyStatus);

			ChiString newScore = oldScore;
			ChiString newProgress = oldProgress;
			ChiString newStatus = oldStatus;

			if (m_NewProgress != -1)
				newProgress = std::to_string(m_NewProgress);
			if (m_NewScore != -1)
				newScore = std::to_string(m_NewScore);
			if (m_NewStatus != -1)
				newStatus = std::to_string(m_NewStatus);



			It->second.SetKeyValue(kMyWatchedEpisodes, newProgress);
			It->second.SetKeyValue(kMyStatus, newStatus);
			It->second.SetKeyValue(kMyScore, newScore);

			m_Curl->SetMethod(method, this->GetAnimeXML(It->second));

			m_Curl->SetReady();

			int x = 0;
		}
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::UpdateScore(int newScore)
	{
		m_NewScore = newScore;
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::UpdateStatus(int newStatus)
	{
		m_NewStatus = newStatus;
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::UpdateProgress(int newProgress)
	{
		m_NewProgress = newProgress;
	}
	//----------------------------------------------------------------------------
	void UpdateAnimeRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}