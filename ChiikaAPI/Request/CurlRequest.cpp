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
#include "CurlRequest.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	int CurlRequest::CallbackFunc(char* data,size_t size,size_t nmemb,ChiString* buffer)
	{
		// What we will return
		int result = 0;

		// Is there anything in the buffer?
		if(buffer != NULL) {
			// Append the data to the buffer
			buffer->append(data,size * nmemb);

			// How much did we write?
			result = size * nmemb; //LMao
		}

		return result;
	}
	//----------------------------------------------------------------------------
	int CurlRequest::ReadCallbackFunc(void *ptr,size_t size,size_t nmemb,void *userp)
	{
		//struct WriteThis *pooh = (struct WriteThis *)userp;

		//if(size*nmemb < 1)
		//	return 0;

		//if(pooh->sizeleft) {
		//	*(char *)ptr = pooh->readptr[0]; /* copy one single byte */
		//	pooh->readptr++;                 /* advance pointer */
		//	pooh->sizeleft--;                /* less data left */
		//	return 1;                        /* we return 1 byte at a time! */
		//}

		return 0;                          /* no more data left to deliver */
	}
	//----------------------------------------------------------------------------
	size_t CurlRequest::Curlfwrite(void *ptr,size_t size,size_t nmemb,FILE *stream)
	{
		size_t written = fwrite(ptr,size,nmemb,stream);
		return written;
	}
	//----------------------------------------------------------------------------
	CurlRequest::CurlRequest()
		: m_bVerbose(false),
		m_iRequestResult(0),
		m_pCurl(NULL),
		m_iMethod(0),
		m_sBuffer(""),
		m_sPostData(""),
		m_sFileOutput(""),
		m_Flags(0)
	{
		m_bInitialized = false;
	}
	//----------------------------------------------------------------------------
	CurlRequest::~CurlRequest()
	{

	}
	//----------------------------------------------------------------------------
	void CurlRequest::Initialize()
	{
		m_pCurl = curl_easy_init();
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetAuth(const std::string& auth) //Should be username:pass
	{
		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_HTTPAUTH,CURLAUTH_BASIC);
		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_USERPWD,ToStd(auth));
		//LOG(INFO) << "Setting authentication to " + auth.substr(0,5) + "..."; //Not posting everything
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetFlag(int f)
	{
		m_Flags |= f;
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetUrl(const ChiString& url)
	{
		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_URL,ToStd(url));
		//LOG(INFO) << "Setting URL to " + url + "..";
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetUserAgent(const ChiString& ua)
	{
		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_USERAGENT,ua);
		//LOG(INFO) << "Setting User-Agent to " + ua + "..";
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetMethod(int method,const ChiString& xmlData)
	{
		m_iMethod = method;
		if(method == CURLOPT_HTTPGET)
		{
			/*LOG(INFO) << "Setting method to GET";*/
		}
		else
		{
			/*LOG(INFO) << "Setting method to POST";*/
			m_sPostData = xmlData;
		}
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetTimeout(int time)
	{
		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_TIMEOUT,time);
		/*LOG(INFO) << "Setting timeout to " << time << " seconds";*/
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetVerbose(bool b)
	{
		m_bVerbose = b;
		if(m_bVerbose)
		{
			curl_easy_setopt(m_pCurl,CURLOPT_VERBOSE,1L);
			/*LOG(INFO) << "VERBOSE enabled.";*/
		}
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetErrorCode(int optional)
	{
		if(optional != 0)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | optional;
		}
	}
	//----------------------------------------------------------------------------
	void CurlRequest::SetFileOutput(const ChiString& output)
	{
		m_sFileOutput = output;
	}
	//----------------------------------------------------------------------------
	void CurlRequest::Perform()
	{
		if (!m_bInitialized)
			return;
		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEDATA,&m_sBuffer);
		FILE* fp;

		if(m_Flags & CurlFlags::REQUEST_DOWNLOAD)
		{
			fp = fopen(m_sFileOutput.c_str(),"wb");
			m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,Curlfwrite);
			curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, fp);
		}
		else
		{
			m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,CallbackFunc);
		}
		/*LOG(INFO) << "Initiaing request....";*/

		if(m_iMethod == CURLOPT_HTTPPOST)
		{
			const char* data = m_sPostData.c_str();
			ChiString append = "data=";
			append.append(data);

			m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_POST,1L);
			m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_POSTFIELDS,append.c_str());
			m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_POSTFIELDSIZE,append.length());
			m_CurlRes = curl_easy_perform(m_pCurl);
			if(m_bVerbose)
			{
				/*LOG(INFO) << "POST Data = " + append;*/
			}
		}
		else
		{
			m_CurlRes = curl_easy_perform(m_pCurl);
		}

		if(m_Flags & CurlFlags::REQUEST_DOWNLOAD)
		{
			fclose(fp);
		}
		long http_code = 0;
		curl_easy_getinfo(m_pCurl,CURLINFO_RESPONSE_CODE,&http_code);

		/*LOG(INFO) << "Request returned HTTP code " << http_code << "...";*/

		if(m_CurlRes == CURLE_COULDNT_CONNECT)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | RequestCodes::CANT_CONNECT;
		}
		if(m_CurlRes == CURLE_COULDNT_RESOLVE_HOST || m_CurlRes == CURLE_COULDNT_RESOLVE_PROXY)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | RequestCodes::CANT_RESOLVE_HOST_OR_PROXY;
		}

		if(http_code == 200)
		{
			m_iRequestResult = RequestCodes::REQUEST_SUCCESS | RequestCodes::RETURNED_GOOD;
		}
		else if(http_code == 204)
		{
			m_iRequestResult = RequestCodes::REQUEST_SUCCESS | RequestCodes::RETURNED_EMPTY;
		}
		else if(http_code == 201)
		{
			m_iRequestResult = RequestCodes::REQUEST_SUCCESS | RequestCodes::POST_SUCCESS;
		}
		else if(http_code == 400)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | RequestCodes::BAD_REQUEST;
		}
		else  if(http_code == 401)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | RequestCodes::UNAUTHORIZED;
		}
		else if(http_code == 500)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | RequestCodes::INTERNAL_ERROR;
		}
		else if(http_code == 501)
		{
			m_iRequestResult = RequestCodes::REQUEST_ERROR | RequestCodes::NOT_IMPLEMENTED;
		}
		if(m_iRequestResult & RequestCodes::REQUEST_SUCCESS)
		{
			/*LOG(INFO) << "Request successful.";*/
			for(size_t i = 0; i < m_vListeners.size(); i++)
			{
				m_vListeners[i]->OnSuccess();
			}
		}
		if(m_iRequestResult & RequestCodes::REQUEST_ERROR)
		{
			/*LOG(INFO) << "Request error.";*/
			for(size_t i = 0; i < m_vListeners.size(); i++)
			{
				m_vListeners[i]->OnError();
			}
		}
		curl_easy_cleanup(m_pCurl);
	}
	//----------------------------------------------------------------------------
	const ChiString& CurlRequest::GetResponse()
	{
		return m_sBuffer;
	}
	//----------------------------------------------------------------------------
	void CurlRequest::AddListener(CurlEventListener* listener)
	{
		if(listener)
			m_vListeners.push_back(listener);
	}
	//----------------------------------------------------------------------------
	void CurlRequest::RemoveListener(CurlEventListener* l)
	{
		CurlEventListener* listener = 0;
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
	int CurlRequest::GetRequestResult()
	{
		return m_iRequestResult;
	}
	//----------------------------------------------------------------------------
}