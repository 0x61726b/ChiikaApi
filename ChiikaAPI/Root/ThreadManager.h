//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2016  Alperen Gezer
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
#ifndef __ThreadManager_h__
#define __ThreadManager_h__
//----------------------------------------------------------------------------
#include "Common\Required.h"
#include "boost\thread.hpp"


//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport ThreadManager
	{
	public:
		ThreadManager(bool isQueued,RequestInterface* request);
		~ThreadManager();
		bool IsBusy() { return mStop; }


		boost::thread* Get();

		void Run();
		void RunOnSpecialThread();

		void PostRequest(RequestInterface* r);
		
		RequestInterface* Front();
		void Pop();

		bool isQueued;
		bool mStop;
		boost::mutex m_Lock;
		boost::condition_variable cond;
		boost::thread* m_RequestThread;

		std::queue<RequestInterface*> m_RequestQueue;
		RequestInterface* m_SingleReq;
		
	};
}



#endif