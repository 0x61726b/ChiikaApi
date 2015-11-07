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
#ifndef __Log_h__
#define __Log_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include <String.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	enum LoggingLevel
	{
		LOG_LEVEL_LOW = 1,
		LOG_LEVEL_NORMAL = 2,
		LOG_LEVEL_EVERYTHING = 3
	};
	enum LogMessageLevel
	{
		LOG_LEVEL_ERROR = 2,
		LOG_LEVEL_INFO = 0,
		LOG_LEVEL_WARNING = 1,
		LOG_LEVEL_BORE = 42
	};
#define LOG_THRESHOLD 3
	class LogListener
	{
	public:
		virtual ~LogListener() {}

		virtual void MessageLogged(const String& message,LogMessageLevel lml,bool maskDebug,const String &logName,bool& skipThisMessage) = 0;
	};

	class MalApiExport Log
	{
	protected:
		std::ofstream	mLog;
		LoggingLevel	mLogLevel;
		bool			mDebugOut;
		bool			mSuppressFile;
		bool			mTimeStamp;
		String			mLogName;

		typedef Vector<LogListener*>::type mtLogListener;
		mtLogListener mListeners;
	public:

		CHIKA_AUTO_MUTEX

		class Stream;
		Log(const String& name,bool debugOutput = true,bool suppressFileOutput = false);

		~Log();
		const String& GetName() const { return mLogName; }

		bool IsDebugOutputEnabled() const { return mDebugOut; }

		bool IsFileOutputSuppressed() const { return mSuppressFile; }

		bool IsTimeStampEnabled() const { return mTimeStamp; }

		void LogMessage(const String& message,LogMessageLevel lml = LOG_LEVEL_INFO,bool maskDebug = false);

		Stream stream(LogMessageLevel lml = LOG_LEVEL_INFO,bool maskDebug = false);

		void SetDebugOutputEnabled(bool debugOutput);

		void SetLogDetail(LoggingLevel ll);

		void SetTimeStampEnabled(bool timeStamp);

		LoggingLevel GetLogDetail() const { return mLogLevel; }

		void AddListener(LogListener* listener);

		void RemoveListener(LogListener* listener);
		class Stream
		{
		protected:
			Log* mTarget;
			LogMessageLevel mLevel;
			bool mMaskDebug;
			typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > BaseStream;
			BaseStream mCache;

		public:

			/// Simple type to indicate a flush of the stream to the log
			struct Flush {};

			Stream(Log* target,LogMessageLevel lml,bool maskDebug)
				:mTarget(target),mLevel(lml),mMaskDebug(maskDebug)
			{

			}
			// copy constructor
			Stream(const Stream& rhs)
				: mTarget(rhs.mTarget),mLevel(rhs.mLevel),mMaskDebug(rhs.mMaskDebug)
			{
				// explicit copy of stream required, gcc doesn't like implicit
				mCache.str(rhs.mCache.str());
			}
			~Stream()
			{
				// flush on destroy
				if(mCache.tellp() > 0)
				{
					mTarget->LogMessage((mCache.str()),mLevel,mMaskDebug);
				}
			}

			template <typename T>
			Stream& operator<< (const T& v)
			{
				mCache << v;
				return *this;
			}

			Stream& operator<< (const Flush& v)
			{
				(void)v;
				mTarget->LogMessage((mCache.str()),mLevel,mMaskDebug);
				mCache.str("");
				return *this;
			}


		};
	};

}
//----------------------------------------------------------------------------
#endif