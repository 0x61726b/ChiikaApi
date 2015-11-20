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
#include "Common\Required.h"
#include "ThirdParty\curl\include\curl\curl.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport CurlEventListener
	{
	public:
		virtual void OnSuccess() = 0;
		virtual void OnError() = 0;
	};
	//----------------------------------------------------------------------------
	class MalApiExport CurlRequestInterface
	{
	public:
		virtual ~CurlRequestInterface()
		{
		};
		virtual void Initialize() = 0;
		virtual void SetUrl(const ChiString&) = 0;
		virtual void SetAuth(const ChiString&) = 0;
		virtual const ChiString& GetResponse() = 0;
		virtual void SetMethod(int method,const ChiString& data) = 0;
		virtual void SetWriteFunction(std::function<size_t(void *buffer,size_t size,size_t nmemb,void *stream)>*) = 0;
		virtual void Perform() = 0;

		virtual void SetErrorCode(int optional) = 0;
		virtual void SetTimeout(int) = 0;
		virtual void SetVerbose(bool) = 0;
		virtual void AddListener(CurlEventListener* listener) = 0;
		virtual void RemoveListener(CurlEventListener* listener) = 0;
		virtual int GetRequestResult() = 0;

	};
	//----------------------------------------------------------------------------
	class MalApiExport CurlRequest : public CurlRequestInterface
	{
	public:
		CurlRequest();
		virtual ~CurlRequest();
		void Initialize();
		void SetUrl(const ChiString&);
		void SetAuth(const ChiString&);
		void SetUserAgent(const ChiString& ua = "ChiikaApi");
		void SetMethod(int method,const ChiString& data);
		void SetTimeout(int);
		void SetVerbose(bool);
		void Perform();
		void SetWriteFunction(std::function<size_t(void *buffer,size_t size,size_t nmemb,void *stream)>*);
		void SetErrorCode(int optional);

	public:
		void AddListener(CurlEventListener* listener);
		void RemoveListener(CurlEventListener* listener);

		Vector<CurlEventListener*>::type m_vListeners;

		const ChiString& GetResponse();
		int GetRequestResult();
	private:
		CURL* m_pCurl;
		CURLcode m_CurlRes;
		int m_iRequestResult;
		bool m_bVerbose;
		int m_iMethod;

	private:
		ChiString m_sBuffer;
		ChiString m_sPostData;


		static int CallbackFunc(char* data,size_t size,size_t nmemb,ChiString* buffer);
		static int ReadCallbackFunc(void *ptr,size_t size,size_t nmemb,void *userp);

		static size_t Curlfwrite(void *buffer,size_t size,size_t nmemb,void *stream);
	};
}