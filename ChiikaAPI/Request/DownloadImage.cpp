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
//	Date:	 28.1.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "DownloadImage.h"
#include "Database/LocalDataManager.h"
#include "Root/Root.h"
#include "Settings/Settings.h"

#include "Common/MyAnimeListUtility.h"
#include "Common/BoostHeaders.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	DownloadImageRequest::DownloadImageRequest()
	{
		m_sName = kRequestImageDownload;
	}
	//----------------------------------------------------------------------------
	DownloadImageRequest::~DownloadImageRequest()
	{
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::OnSuccess()
	{
		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::SetOptions()
	{
		ChiString url;
		int method;
		ChiString userName;
		ChiString passWord;

		
		//url = "http://i.imgur.com/TQFgglc.jpg";
		method = CURLOPT_HTTPGET;
		userName = Root::Get()->GetUser().GetKeyValue(kUserName);
		passWord = Root::Get()->GetUser().GetKeyValue(kPass);

		
		m_Curl->SetMethod(method, "");
		m_Curl->SetFlag(CurlFlags::REQUEST_DOWNLOAD);
		m_Curl->SetUrl(url);

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::SetUrl(const ChiString& url)
	{
		m_Curl->SetUrl(url);
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::SetFile(const ChiString& fileName, const ChiString& folder)
	{
		boost::filesystem::path f1(fileName);
		boost::filesystem::path f2(folder);
		boost::filesystem::path f3(f2 / f1);
		m_Curl->SetFileOutput(f3.generic_string());
	}
	//----------------------------------------------------------------------------
	void DownloadImageRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------