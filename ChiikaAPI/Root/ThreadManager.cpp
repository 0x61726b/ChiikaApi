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
#include "Stable.h"
#include "ThreadManager.h"
#include "Logging\LogManager.h"
#include "Request\RequestInterface.h"

//----------------------------------------------------------------------------

namespace ChiikaApi
{
	ThreadManager::ThreadManager()
		: mStop(true)
	{
		m_RequestThread = new boost::thread(&ThreadManager::Run,this);

	}
	ThreadManager::~ThreadManager()
	{

	}

	void ThreadManager::Run()
	{
		for(;;)
		{
			
			boost::mutex::scoped_lock lock(m_Lock);

			while(m_RequestQueue.empty()) cond.wait(lock);

			LOG(Bore) << "Request Thread: Processing Queue";

			if (!m_RequestQueue.empty())
			{
				RequestInterface* process = m_RequestQueue.front();
				if (!process)
					return;
				CurlRequestInterface* curl = process->Get();
				if (!curl)
					return;

				if (curl->IsInitialized())
				{
					curl->Perform();

					m_RequestQueue.pop();
					delete process;
				}
			}
			else
			{
				LOG(Bore) << "Request Thread: Stopping";
			}
		}
	}

	void ThreadManager::PostRequest(RequestInterface* r)
	{
		boost::mutex::scoped_lock lock(m_Lock);
		m_RequestQueue.push(r);
		cond.notify_one();
		
	}

	boost::thread* ThreadManager::Get()
	{
		return m_RequestThread;
	}
}