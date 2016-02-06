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
#include "RequestInterface.h"
#include "Database\LocalDataManager.h"
#include "Logging\LogManager.h"
//----------------------------------------------------------------------------
struct xml_string_writer : pugi::xml_writer
{
	std::string result;
	virtual void write(const void* data,size_t size)
	{
		result += std::string(static_cast<const char*>(data),size);
	}
};
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	RequestInterface::RequestInterface()
		: m_bIsCompleted(false),
		m_sName(""),
		m_Curl(0)
	{
		
	}
	//----------------------------------------------------------------------------
	RequestInterface::~RequestInterface()
	{

	}
	//----------------------------------------------------------------------------
	void RequestInterface::OnSuccess()
	{
		m_bIsCompleted = true;
		for(size_t i = 0; i < m_vListeners.size(); i++)
		{
			m_vListeners[i]->OnSuccess(this);
		}
	}
	//----------------------------------------------------------------------------
	void RequestInterface::SetPostData()
	{
		
	}
	//----------------------------------------------------------------------------
	void RequestInterface::OnError()
	{
		m_bIsCompleted = true;
		std::string errorResponse = m_Curl->GetResponse();
		//
		int error = m_Curl->GetRequestResult();

		if(error == 0)
		{
			errorResponse = "Wow something went really wrong wtf.";
		}

		if(error & RequestCodes::UNAUTHORIZED)
		{
			errorResponse = "Authorization error.";
		}

		if(error & RequestCodes::CANT_CONNECT)
		{
			errorResponse = "Connection couldnt be made.";
		}

		if(error & RequestCodes::CANT_RESOLVE_HOST_OR_PROXY)
		{
			errorResponse = "Can't resolve host or proxy.Probably there is no internet connection.";
		}

		for(size_t i = 0; i < m_vListeners.size(); i++)
		{
			m_vListeners[i]->OnError(this);
		}

		//ToDo(arkenthera): Implements others sometime.
	}
	//----------------------------------------------------------------------------
	void RequestInterface::AddListener(RequestListener* listener)
	{
		if(listener)
			m_vListeners.push_back(listener);
	}
	//----------------------------------------------------------------------------
	void RequestInterface::RemoveListener(RequestListener* l)
	{
		RequestListener* listener = 0;
		int index;
		for(unsigned int i = 0; i < m_vListeners.size(); i++)
		{
			if(m_vListeners[i] == l)
			{
				listener = l;
				index = i;
			}
		}

		m_vListeners.erase(m_vListeners.begin() + index);
		TryDelete(listener);
	}
	//----------------------------------------------------------------------------
	CurlRequestInterface* RequestInterface::Get()
	{
		return m_Curl;
	}
	//----------------------------------------------------------------------------
	const std::string& RequestInterface::GetName()
	{
		return m_sName;
	}
	//----------------------------------------------------------------------------
	const std::string& RequestInterface::GetResponse()
	{
		return m_Curl->GetResponse();
	}
	//----------------------------------------------------------------------------
	void RequestInterface::SetCURL(CurlRequestInterface* curl)
	{
		m_Curl = curl;
	}
	//----------------------------------------------------------------------------
	FakeRequest::FakeRequest()
	{
		SetName("FakeRequest");
	}
	//----------------------------------------------------------------------------
	void FakeRequest::OnSuccess()
	{
		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void FakeRequest::SetName(const std::string& name)
	{
		m_sName = name;
	}
	//----------------------------------------------------------------------------
	ChiString RequestInterface::GetAnimeXML(UserAnimeEntry& anime)
	{
		pugi::xml_document doc;
		XmlNode entry = doc.append_child("entry");
		XmlNode episode = entry.append_child("episode");
		XmlNode status = entry.append_child("status");
		XmlNode score = entry.append_child("score");
		XmlNode downloaded_episodes = entry.append_child("downloaded_episodes");
		XmlNode storage_type = entry.append_child("storage_type");
		XmlNode storage_value = entry.append_child("storage_value");
		XmlNode times_rewatched = entry.append_child("times_rewatched");
		XmlNode rewatch_value = entry.append_child("rewatch_value");
		XmlNode date_start = entry.append_child("date_start");
		XmlNode date_finish = entry.append_child("date_finish");
		XmlNode priority = entry.append_child("priority");
		XmlNode enable_discussion = entry.append_child("enable_discussion");
		XmlNode enable_rewatching = entry.append_child("enable_rewatching");
		XmlNode comments = entry.append_child("comments");
		XmlNode fansub_group = entry.append_child("fansub_group");
		XmlNode tags = entry.append_child("tags");

		XmlNode decl = doc.prepend_child(pugi::node_declaration);
		decl.append_attribute("version") = "1.0";
		decl.append_attribute("encoding") = "UTF-8";


		episode.text().set(anime.GetKeyValue(kMyWatchedEpisodes).c_str());
		status.text().set(ToStd(anime.GetKeyValue(kMyStatus)));
		score.text().set(ToStd(anime.GetKeyValue(kMyScore)));
		std::stringstream str;
		xml_string_writer writer;

		doc.save(writer);
		return writer.result;
	}

}