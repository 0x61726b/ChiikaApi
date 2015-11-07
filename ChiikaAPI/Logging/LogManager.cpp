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
#include "Logging/LogManager.h"
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//-----------------------------------------------------------------------
	template<> LogManager* Singleton<LogManager>::msSingleton = 0;
	LogManager* LogManager::GetPtr(void)
	{
		return msSingleton;
	}
	LogManager& LogManager::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//-----------------------------------------------------------------------
	LogManager::LogManager()
	{
		m_pDefaultLog = NULL;
	}
	//-----------------------------------------------------------------------
	LogManager::~LogManager()
	{
		CHIKA_AUTO_MUTEX_LOCK
			// Destroy all logs
			LogList::iterator i;
		for(i = m_Logs.begin(); i != m_Logs.end(); ++i)
		{
			delete i->second;
		}
	}
	//-----------------------------------------------------------------------
	Log* LogManager::CreateLog(const String& name,bool defaultLog,bool debuggerOutput,
		bool suppressFileOutput)
	{
		CHIKA_AUTO_MUTEX_LOCK
			Log* newLog = new Log(name,debuggerOutput,suppressFileOutput);

		if(!m_pDefaultLog || defaultLog)
		{
			m_pDefaultLog = newLog;
		}

		m_Logs.insert(LogList::value_type(name,newLog));

		return newLog;
	}
	//-----------------------------------------------------------------------
	Log* LogManager::GetDefaultLog()
	{
		CHIKA_AUTO_MUTEX_LOCK
			return m_pDefaultLog;
	}
	//-----------------------------------------------------------------------
	Log* LogManager::setDefaultLog(Log* newLog)
	{
		CHIKA_AUTO_MUTEX_LOCK
			Log* oldLog = m_pDefaultLog;
		m_pDefaultLog = newLog;
		return oldLog;
	}
	//-----------------------------------------------------------------------
	Log* LogManager::GetLog(const String& name)
	{
		CHIKA_AUTO_MUTEX_LOCK
			LogList::iterator i = m_Logs.find(name);
		if(i != m_Logs.end())
			return i->second;
		/*OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Log not found. ", "LogManager::getLog");*/

		return 0;
	}
	//-----------------------------------------------------------------------
	void LogManager::DestroyLog(const String& name)
	{
		LogList::iterator i = m_Logs.find(name);
		if(i != m_Logs.end())
		{
			if(m_pDefaultLog == i->second)
			{
				m_pDefaultLog = 0;
			}
			delete i->second;
			m_Logs.erase(i);
		}

		// Set another default log if this one removed
		if(!m_pDefaultLog && !m_Logs.empty())
		{
			m_pDefaultLog = m_Logs.begin()->second;
		}
	}
	//-----------------------------------------------------------------------
	void LogManager::DestroyLog(Log* log)
	{
		DestroyLog(log->GetName());
	}
	//-----------------------------------------------------------------------
	void LogManager::LogMessage(const String& message,LogMessageLevel lml,bool maskDebug)
	{
		CHIKA_AUTO_MUTEX_LOCK
			if(m_pDefaultLog)
			{
				m_pDefaultLog->LogMessage(message,lml,maskDebug);
			}
	}
	//-----------------------------------------------------------------------
	void LogManager::setLogDetail(LoggingLevel ll)
	{
		CHIKA_AUTO_MUTEX_LOCK
			if(m_pDefaultLog)
			{
				m_pDefaultLog->SetLogDetail(ll);
			}
	}
	//---------------------------------------------------------------------
	Log::Stream LogManager::stream(LogMessageLevel lml,bool maskDebug)
	{
		CHIKA_AUTO_MUTEX_LOCK
			if(m_pDefaultLog)
				return m_pDefaultLog->stream(lml,maskDebug);
		/*OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Default log not found. ", "LogManager::stream");*/
		return m_pDefaultLog->stream(lml,maskDebug);
	}
}


