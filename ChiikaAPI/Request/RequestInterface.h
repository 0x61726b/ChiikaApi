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
#ifndef __RequestInterface_h__
#define __RequestInterface_h__
//----------------------------------------------------------------------------
#include "Common\Required.h"
#include "Request\CurlRequest.h"
#include "Request\RequestListener.h"
#include "Request\RequestList.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport RequestInterface
	{
	public:
		RequestInterface();
		virtual ~RequestInterface();
		virtual void OnSuccess();
		virtual void OnError();

		virtual void Initialize() = 0;
		virtual void SetOptions() = 0;

		virtual void Initiate() = 0;

		virtual void SetPostData();

		bool IsCompleted()
		{
			return m_bIsCompleted;
		}

		CurlRequestInterface* Get();
		//For creating mock objects
		void SetCURL(CurlRequestInterface* curl);
		

		const std::string& GetResponse();

		const std::string& GetName();

		ChiString GetAnimeXML(UserAnimeEntry& anime);

	public:
		void AddListener(RequestListener* listener);
		void RemoveListener(RequestListener* listener);

		Vector<RequestListener*>::type m_vListeners;

	protected:
		ChiString m_sName;
		CurlRequestInterface* m_Curl;
		bool m_bIsCompleted;
	};
	class MalApiExport FakeRequest : public RequestInterface
	{
	public:
		FakeRequest();
		void OnSuccess();
		void OnError() { }

		void Initialize() { }
		void Initiate() { }
		void SetOptions() { }
	};
}
#endif