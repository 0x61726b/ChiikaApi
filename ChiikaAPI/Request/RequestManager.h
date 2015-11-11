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
#ifndef __RequestManager_h__
#define __RequestManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Common/Singleton.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	typedef std::map<ChiString,ChiString> ThreadOptions;
	enum RequestCodes
	{
		REQUEST_ERROR = 0,
		VERIFY_SUCCESS = 1,
		VERIFY_ERROR = 2,
		SEARCH_SUCCESS = 3,
		SEARCH_ERROR = 4,
		UNAUTHORIZED = 5,
	};
	enum RequestType
	{
		MyAnimeList,
		Anilist
	};
	struct RequestResult
	{
		RequestCodes Code;
		ChiString ErrorDesc;
		long HttpCode;


		//this could be done with inheritance but muh laziness
		AnimeList m_AnimeList;
		MangaList m_MangaList;

		UserAnimeEntry AnimeResult;
		MangaInfo MangaResult;

		ChiString AnilistAuthCode;
	};
	//----------------------------------------------------------------------------
	class MalApiExport RequestListener
	{
	public:
		virtual void Notify(ThreadedRequest* thread) = 0;
		virtual ~RequestListener() { }
	};
	//----------------------------------------------------------------------------
	class MalApiExport RequestBase
	{
	public:
		virtual ChiString GetResponse() = 0;
		virtual void Work() = 0;
		virtual void CreateThread() = 0;
		virtual ~RequestBase() { }
		virtual void Initialize() = 0;
	};
	//----------------------------------------------------------------------------
	class MalApiExport ThreadedRequest : public RequestBase
	{
	public:
		ThreadedRequest();
		virtual ~ThreadedRequest();

		void SetParameters(CurlConfigOptionMap Options,const ChiString& name,const RequestType& type = RequestType::MyAnimeList);
		void CreateThread();
		void DeleteThread();

		void Initialize();
		void Work();
		void Join();


		ChiString GetResponse();
		ThreadOptions m_ThreadOptions;


		std::thread* m_pThread;
		ChiString m_sUrl;
		ChiString m_sUsrPwd;
		int m_iMethod;
		ChiString xmlData;
		CurlConfigOptionMap Options;

		ChiString Name;

		RequestType Type;

		bool m_bWorking;

		virtual void OnWorkFinished(ChiString data);

		ChiString m_sBuffer;
		static int CallbackFunc(char* data,size_t size,size_t nmemb,ChiString* buffer);
		static int ReadCallbackFunc(void *ptr, size_t size, size_t nmemb, void *userp);

		static size_t Curlfwrite(void *buffer, size_t size, size_t nmemb, void *stream);

		//Listener
		void AddListener(RequestListener* listener);
		void RemoveListener(RequestListener* listener);
		virtual void NotifyListeners();

		std::vector<RequestListener*> m_vListeners;

		RequestResult m_Result;
	};
	
	//----------------------------------------------------------------------------
	class MalApiExport RequestManagerBase
	{
	public:
		virtual ~RequestManagerBase() { }

		virtual void ProcessRequest(ThreadedRequest*) = 0;
	};
	//----------------------------------------------------------------------------
	class MalApiExport RequestManager : public Singleton<RequestManager>, public RequestManagerBase
	{
	public:
		RequestManager();
		virtual ~RequestManager();

		void Initialize();
		void Destroy();

		void ProcessRequest(ThreadedRequest*);

		void CreateVerifyRequest(RequestListener* l);

		//Anime
		void CreateAnimeSearchRequest(RequestListener* l,ChiString keyword);
		void CreateGetAnimeListRequest(RequestListener* l);
		//~
		//Manga
		void CreateGetMangaListRequest(RequestListener* l);
		//~

		void CreateCRUDRequest(RequestListener* l,const UserAnimeEntry& anime,const MangaInfo& manga,CRUDOp operation,CRUDTarget target);

		//Anilist
		void CreateAnilistRequest();
		void CreateAnilistAuthRequest(RequestListener* l);
		void CreateAnilistSearchAnime(RequestListener* l,ChiString keyword);
		
		ChiString GetAnimeXML(const UserAnimeEntry& anime);
		ChiString GetMangaXML(const MangaInfo& manga);
		
		
		void CreateImageDownloadRequest(RequestListener* l,ChiString url,ChiString fileName,const UserAnimeEntry& anime);
		
		void CreateAnimePageScrapeRequest(RequestListener* l,const UserAnimeEntry& anime);
		void CreateUserPageScrapeRequest(RequestListener* l);



		void CreateSenpaiMoeDataRequest(RequestListener* l);

		
		static RequestManager& Get();
		static RequestManager* GetPtr();
	};
}
//----------------------------------------------------------------------------
#endif