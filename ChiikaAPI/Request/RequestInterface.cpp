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
namespace ChiikaApi
{
	RequestInterface::RequestInterface(LocalDataManager* ldm)
	{
		if(!ldm)
		{
			m_pLocalData = LocalDataManager::GetPtr();
		}
		else
		{
			m_pLocalData = ldm;
		}

	}
	//----------------------------------------------------------------------------
	RequestInterface::~RequestInterface()
	{

	}
	//----------------------------------------------------------------------------
	void RequestInterface::OnSuccess()
	{
		for(size_t i = 0; i < m_vListeners.size(); i++)
		{
			m_vListeners[i]->OnSuccess(this);
		}

		LocalDataManager::Get().SaveAll();
	}
	//----------------------------------------------------------------------------
	void RequestInterface::OnError()
	{
		//
		int error = m_Curl.GetRequestResult();

		if(error & RequestCodes::UNAUTHORIZED)
		{
			LOG(ERROR) << "Authorization error.";
		}

		if(error & RequestCodes::CANT_CONNECT)
		{
			LOG(ERROR) << "Connection couldnt be made.";
		}

		if(error & RequestCodes::CANT_RESOLVE_HOST_OR_PROXY)
		{
			LOG(ERROR) << "Can't resolve host or proxy.Probably there is no internet connection.";
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
}