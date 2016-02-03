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
#include "Log.h"
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//-----------------------------------------------------------------------
	Log::Log(const ChiString& name, bool debuggerOuput, bool suppressFile) :
		mLogLevel(LOG_LEVEL_NORMAL), mDebugOut(debuggerOuput),
		mSuppressFile(suppressFile), mTimeStamp(true), mLogName(name)
	{
		if (!mSuppressFile)
		{
			mLog.open(name.c_str());
		}
	}
	//-----------------------------------------------------------------------
	Log::~Log()
	{
		CHIKA_AUTO_MUTEX_LOCK;

		if (!mSuppressFile)
		{
			mLog.close();
		}
	}
	//-----------------------------------------------------------------------
	void Log::LogMessage(const ChiString& message, LogMessageLevel lml, bool maskDebug)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		if ((mLogLevel + lml) >= LOG_THRESHOLD)
		{
			bool skipThisMessage = false;
			for (mtLogListener::iterator i = mListeners.begin(); i != mListeners.end(); ++i)
				(*i)->MessageLogged(message, lml, maskDebug, mLogName, skipThisMessage);

			if (!skipThisMessage)
			{

				if (mDebugOut && !maskDebug)
					std::cerr << message << std::endl;

				// Write time into log
				if (!mSuppressFile)
				{
					if (mTimeStamp)
					{
						struct tm *pTime;
						time_t ctTime; time(&ctTime);
						pTime = localtime(&ctTime);
						mLog << std::setw(2) << std::setfill('0') << pTime->tm_mday << "/"
							<< std::setw(2) << std::setfill('0') << (pTime->tm_mon + 1) << "/"
							<< (pTime->tm_year - 100) << "  "
							<< std::setw(2) << std::setfill('0') << pTime->tm_hour
							<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
							<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
							<< ": ";
					}
					ChiString prefix = "";
					if (lml == LogMessageLevel::LOG_LEVEL_INFO)
					{
						prefix = "INFO ->";
					}
					if (lml == LogMessageLevel::LOG_LEVEL_ERROR)
					{
						prefix = "ERROR ->";
					}
					if (lml == LogMessageLevel::LOG_LEVEL_WARNING)
					{
						prefix = "WARNING ->";
					}
					if (lml == LogMessageLevel::LOG_LEVEL_BORE)
					{
						prefix = "API ->";
					}
					mLog << prefix << message << std::endl;
					mLog.flush();
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void Log::SetTimeStampEnabled(bool timeStamp)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		mTimeStamp = timeStamp;
	}

	//-----------------------------------------------------------------------
	void Log::SetDebugOutputEnabled(bool debugOutput)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		mDebugOut = debugOutput;
	}

	//-----------------------------------------------------------------------
	void Log::SetLogDetail(LoggingLevel ll)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		mLogLevel = ll;
	}

	//-----------------------------------------------------------------------
	void Log::AddListener(LogListener* listener)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		mListeners.push_back(listener);
	}

	//-----------------------------------------------------------------------
	void Log::RemoveListener(LogListener* listener)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		mListeners.erase(std::find(mListeners.begin(), mListeners.end(), listener));
	}
	//---------------------------------------------------------------------
	Log::Stream Log::stream(LogMessageLevel lml, bool maskDebug)
	{
		return Stream(this, lml, maskDebug);
	}
}


