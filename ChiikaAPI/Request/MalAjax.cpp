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
//	Date:	 1.2.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "MalAjax.h"
#include "Database/LocalDataManager.h"
#include "Root/Root.h"
#include "Logging/ChiString.h"
#include "Request/MalManager.h"
#include "Logging/FileHelper.h"
#include "Common/MyAnimeListUtility.h"

//----------------------------------------------------------------------------
namespace ChiikaApi
{
	MalAjaxRequest::MalAjaxRequest()
	{
		m_sName = kRequestMalAjax;
	}
	//----------------------------------------------------------------------------
	MalAjaxRequest::~MalAjaxRequest()
	{
	}
	//----------------------------------------------------------------------------
	void MalAjaxRequest::OnSuccess()
	{

		ChiString data = m_Curl->GetResponse();

		AnimeMisc result = MyAnimelistUtility::ParseAnimeAjax(data);


		AnimeList& list = Root::Get()->GetMyAnimelistManager()->GetAnimes();

		AnimeList::iterator It = list.find(std::to_string(m_AnimeId));

		if(It != list.end())
		{
			Anime& a = It->second;

			a.Misc = result;
		}

		Root::Get()->GetLocalDataManager()->SaveCachedAnimeList();

		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void MalAjaxRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void MalAjaxRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void MalAjaxRequest::SetAnimeId(int id)
	{
		m_AnimeId = id;
	}
	//----------------------------------------------------------------------------
	int MalAjaxRequest::GetAnimeId() const
	{
		return m_AnimeId;
	}
	//----------------------------------------------------------------------------
	void MalAjaxRequest::SetOptions()
	{
		int method;
		method = CURLOPT_HTTPGET;
		ChiString url = "http://myanimelist.net/includes/ajax.inc.php?id=" + std::to_string(m_AnimeId) +"&t=64";

		m_Curl->SetUrl(url);

		m_Curl->SetMethod(method,"");

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void MalAjaxRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}