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
#include "MalUserPageScrape.h"
#include "Database\LocalDataManager.h"
#include "Root\Root.h"
#include "Logging\ChiString.h"
#include "Logging\LogManager.h"
#include "boost\regex.hpp"
#include "Logging\FileHelper.h"
#include "Common\MyAnimelistUtility.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	MalScrapeRequest::MalScrapeRequest()
	{
		m_sName = kRequestAnimePageScrape;
	}
	//----------------------------------------------------------------------------
	MalScrapeRequest::~MalScrapeRequest()
	{
	}
	//----------------------------------------------------------------------------
	void MalScrapeRequest::OnSuccess()
	{

		ChiString data = (m_Curl->GetResponse());


		MyAnimelistUserPageParseResult result = MyAnimelistUtility::ParseUserPage(data);



		Root::Get()->GetUser().SetKeyValue(kUserImageLink,result.ProfileImageLink);






		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void MalScrapeRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void MalScrapeRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void MalScrapeRequest::SetUserInfo(const UserInfo& user)
	{

	}
	//----------------------------------------------------------------------------
	void MalScrapeRequest::SetOptions()
	{
		ChiString url;
		int method;
		ChiString userName;
		ChiString passWord;


		method = CURLOPT_HTTPGET;
		userName = Root::Get()->GetUser().GetKeyValue(kUserName);
		passWord = Root::Get()->GetUser().GetKeyValue(kPass);

		url = ("http://myanimelist.net/profile/" + userName);

		m_Curl->SetUrl(url);
		m_Curl->SetAuth(userName + ":" + passWord);
		m_Curl->SetMethod(method,"");

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void MalScrapeRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------