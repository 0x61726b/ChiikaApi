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
#include "Request\RequestInterface.h"

//----------------------------------------------------------------------------

namespace ChiikaApi
{
	ThreadManager::ThreadManager(bool queue,RequestInterface* request)
		: mStop(true),
		isQueued(queue),
		m_SingleReq(request)
	{
		if(isQueued)
			m_RequestThread = new boost::thread(&ThreadManager::Run,this);
		else
			m_RequestThread = new boost::thread(&ThreadManager::RunOnSpecialThread,this);
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

			//LOG(Bore) << "Request Thread: Processing Queue";

			if(!m_RequestQueue.empty())
			{
				RequestInterface* process = Front();
				if(!process)
					return;
				CurlRequestInterface* curl = process->Get();
				if(!curl)
					return;


				if(curl->IsInitialized())
				{
					curl->Perform();
					//boost::this_thread::sleep_for(boost::chrono::seconds(3)); //for debugging

					Pop();
					//delete process;
				}
			}
		}
	}

	void ThreadManager::RunOnSpecialThread()
	{
		if(m_SingleReq->IsCompleted())
		{
			m_SingleReq->OnSuccess();
			return;
		}
		if(m_SingleReq->Get()->IsInitialized() && !m_SingleReq->IsCompleted())
		{
			m_SingleReq->Get()->Perform();
		}
	}

	RequestInterface* ThreadManager::Front()
	{
		return m_RequestQueue.front();
	}

	void ThreadManager::Pop()
	{
		m_RequestQueue.pop();
	}

	void ThreadManager::PostRequest(RequestInterface* r)
	{
		boost::mutex::scoped_lock lock(m_Lock);
		m_RequestQueue.push(r);

		if(m_RequestQueue.size() == 1)
			cond.notify_one();
	}

	boost::thread* ThreadManager::Get()
	{
		return m_RequestThread;
	}
}