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
//	Date:	 10.2.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "SenpaiMoe.h"
#include "Database/LocalDataManager.h"
#include "Settings/Settings.h"
#include "Root/Root.h"
#include "Logging/ChiString.h"
#include "Request/MalManager.h"
#include "Logging/FileHelper.h"
#include "Common/MyAnimeListUtility.h"
#include "json/json.h"
#include "Seasons/SeasonManager.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	SenpaiMoeDlRequest::SenpaiMoeDlRequest()
	{
		m_sName = kRequestDlSenpaiMoe;
	}
	//----------------------------------------------------------------------------
	SenpaiMoeDlRequest::~SenpaiMoeDlRequest()
	{
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::OnSuccess()
	{
		FileWriter fw(Root::Get()->GetAppSettings()->GetDataPath() / "Senpai.moe");

		//Write everything
		ChiString response = m_Curl->GetResponse();
		if (fw.Open())
		{
			fw.Write(response);
			fw.Close();
		}
		
		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::SetOptions()
	{
		int method;
		method = CURLOPT_HTTPGET;

		m_Curl->SetMethod(method, "");
		m_Curl->SetUrl("http://www.senpai.moe/export.php?type=json&src=raw");

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}