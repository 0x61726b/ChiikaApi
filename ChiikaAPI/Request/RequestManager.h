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

#include "Request\RequestInterface.h"
#include "boost\thread.hpp"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	class MalApiExport RequestManager : public RequestListener
	{
	public:
		RequestManager();
		virtual ~RequestManager();


		void VerifyUser(RequestListener* listener);
		void GetMyAnimelist(RequestListener* listener);
		void GetMyMangalist(RequestListener* listener);
		void MalScrape(RequestListener* listener);
		void DownloadImage(RequestListener* listener,const std::string& url);
		void AnimePageScrape(RequestListener* listener,int AnimeId);

		void OnSuccess(RequestInterface*);
		void OnError(RequestInterface*);

		//Little hacking here
		RequestListener* chiikaNode;

		//Garbage Collecting
		typedef std::map<RequestInterface*,ThreadManager*> RequestThreadMap;
		RequestThreadMap m_RequestThreads;
		boost::mutex threadLock;

		void RemoveThreadObjects();

	};
}
//----------------------------------------------------------------------------
#endif