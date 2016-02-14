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
#include "AccountVerify.h"
#include "Database/LocalDataManager.h"
#include "Root/Root.h"


//----------------------------------------------------------------------------
namespace ChiikaApi
{
	AccountVerifyRequest::AccountVerifyRequest()
	{
		m_sName = kRequestVerify;
	}
	//----------------------------------------------------------------------------
	AccountVerifyRequest::~AccountVerifyRequest()
	{
	}
	//----------------------------------------------------------------------------
	void AccountVerifyRequest::OnSuccess()
	{
		pugi::xml_document doc;

		bool parse = doc.load(m_Curl->GetResponse().c_str());

		pugi::xml_node  user = doc.child(("user"));
		ChiString userName = user.child(("username")).text().as_string();
		ChiString id = user.child(("id")).text().get();

		Root::Get()->GetUser().SetKeyValue(kUserId, id);

		if (Root::Get()->GetLocalDataManager())Root::Get()->GetLocalDataManager()->SaveUserInfo();
		RequestInterface::OnSuccess();

	}
	//----------------------------------------------------------------------------
	void AccountVerifyRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void AccountVerifyRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void AccountVerifyRequest::SetUserInfo(const UserInfo& user)
	{

	}
	//----------------------------------------------------------------------------
	void AccountVerifyRequest::SetOptions()
	{
		ChiString url;
		int method;
		ChiString userName;
		ChiString passWord;

		url = ("http://myanimelist.net/api/account/verify_credentials.xml");
		method = CURLOPT_HTTPGET;
		userName = Root::Get()->GetUser().GetKeyValue(kUserName);
		passWord = Root::Get()->GetUser().GetKeyValue(kPass);

		m_Curl->SetUrl(url);
		m_Curl->SetAuth(userName + ":" + passWord);
		m_Curl->SetMethod(method, "");
		

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void AccountVerifyRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------