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
#ifndef __LogManager_h__
#define __LogManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Common/Singleton.h"
#include "Log.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport LogManager : public Singleton<LogManager>
	{
	public:
		CHIKA_AUTO_MUTEX

		typedef Map<ChiString,Log*>::type LogList;

		LogList m_Logs;

		Log* m_pDefaultLog;

		Log* CreateLog(const ChiString& name,bool defaultLog = false,bool debuggerOutput = true,
			bool suppressFileOutput = false);

		LogManager();
		~LogManager();

		Log* GetLog(const ChiString& name);
		
		Log* GetDefaultLog();
		void DestroyLog(const ChiString& name);
		void DestroyLog(Log* log);

		Log* setDefaultLog(Log* newLog);

        void LogMessage(const ChiString& message, LogMessageLevel lml = LOG_LEVEL_INFO,
			bool maskDebug = false);

		void LogMessage(LogMessageLevel lml, const ChiString& message,
			bool maskDebug) {
			Log(message,true,false);
		}

        Log::Stream stream(LogMessageLevel lml = LOG_LEVEL_INFO,
			bool maskDebug = false);

		void setLogDetail(LoggingLevel ll);

		static LogManager& Get(void);

		static LogManager* GetPtr(void);
	};
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#define LOG(severity) LogStream(severity)
class LogStream : public std::ostringstream  {
public:
    LogStream(int i) { severity = i; }
private:
    int severity;
public:
    ~LogStream() {
        ChiikaApi::LogManager::Get().LogMessage(this->str(),(ChiikaApi::LogMessageLevel)severity,false);
    }
};
#define INFO 0
#define WARNING 1
#define ERROR_ 2
#define Bore 42 //Will log no matter what

#define LOGD LogDebugStream()
class LogDebugStream : public std::ostringstream  {
public:
    LogDebugStream() { }
public:
    ~LogDebugStream() {
		//ChiikaApi::LogManager::Get().GetLog("DebuggerOutput")->LogMessage((this->str()));
    }
};
#endif