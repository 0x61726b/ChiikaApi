//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2015  arkenthera
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
//authors:arkenthera
//Date: 2.10.2016
//----------------------------------------------------------------------------
#include "Stable.h"


#include <boost/scoped_ptr.hpp>
#include "LogManager.h"
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>
#include <log4cplus/win32consoleappender.h>
#include "log4cplus/loggingmacros.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/layout.h"
#include "log4cplus/ndc.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/nullappender.h"


static log4cplus::LogLevel translate_logLevel(ChiikaApi::Log::LogLevel ll);

void ChiikaApi::Log::InitLogging(const char* loc)
{
	log4cplus::Initializer initializer;

	log4cplus::BasicConfigurator config;
	config.configure();

	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Chiika"));
	logger.setLogLevel(translate_logLevel(ChiikaApi::Log::LogLevel_Debug));

#ifdef YUME_PLATFORM_WIN32
	log4cplus::SharedAppenderPtr debugAppender(new log4cplus::Win32ConsoleAppender());
	/*std::unique_ptr<log4cplus::Layout> layout2(new log4cplus::TTCCLayout());
	debugAppender->setLayout(std::move(layout2));*/
	logger.addAppender(debugAppender);
#else
	log4cplus::SharedAppenderPtr debugAppender(new log4cplus::ConsoleAppender());
	std::unique_ptr<log4cplus::Layout> layout2(new log4cplus::TTCCLayout());
	debugAppender->setLayout(std::move(layout2));
	logger.addAppender(debugAppender);
#endif

	const size_t cSize = strlen(loc);

	std::wstring wstrModulePath(cSize, L'#');

	mbstowcs(&wstrModulePath[0], loc, cSize);

	log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender(wstrModulePath));
	/*std::unique_ptr<log4cplus::Layout> layout(new log4cplus::TTCCLayout());
	fileAppender->setLayout(std::move(layout));*/
	logger.addAppender(fileAppender);

}

void ChiikaApi::Log::StopLogging()
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Chiika"));
	logger.shutdown();
}


void ChiikaApi::Log::trace(const std::string& src, const std::string& msg, const char *file, int line, const char *fn)
{
	LOG4CPLUS_TRACE(log4cplus::Logger::getInstance(L"Chiika"),
		file << ":" << line << " - " << fn << " - " << msg.c_str());
}
void ChiikaApi::Log::debug(const std::string& src, const std::string& msg, const char *file, int line, const char *fn)
{
	LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance(L"Chiika"),
		file << ":" << line << " - " << fn << " - " << msg.c_str());
}
void ChiikaApi::Log::info(const std::string& src, const std::string& msg, const char *file, int line, const char *fn)
{
	LOG4CPLUS_INFO(log4cplus::Logger::getInstance(L"Chiika"),
		file << ":" << line << " - " << fn << " - " << msg.c_str());
}
void ChiikaApi::Log::warn(const std::string& src, const std::string& msg, const char *file, int line, const char *fn)
{
	LOG4CPLUS_WARN(log4cplus::Logger::getInstance(L"Chiika"),
		file << ":" << line << " - " << fn << " - " << msg.c_str());
}
void ChiikaApi::Log::error(const std::string& src, const std::string& msg, const char *file, int line, const char *fn)
{
	LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(L"Chiika"),
		file << ":" << line << " - " << fn << " - " << msg.c_str());
}
void ChiikaApi::Log::fatal(const std::string& src, const std::string& msg, const char *file, int line, const char *fn)
{
	LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(L"Chiika"),
		file << ":" << line << " - " << fn << " - " << msg.c_str());
}

static log4cplus::LogLevel translate_logLevel(ChiikaApi::Log::LogLevel ll){

	switch (ll) {
	case(ChiikaApi::Log::LogLevel_Trace) :
		return log4cplus::TRACE_LOG_LEVEL;
	case(ChiikaApi::Log::LogLevel_Debug) :
		return log4cplus::DEBUG_LOG_LEVEL;
	case(ChiikaApi::Log::LogLevel_Info) :
		return log4cplus::INFO_LOG_LEVEL;
	case(ChiikaApi::Log::LogLevel_Warn) :
		return log4cplus::WARN_LOG_LEVEL;
	case(ChiikaApi::Log::LogLevel_Error) :
		return log4cplus::ERROR_LOG_LEVEL;
	default:
		return log4cplus::WARN_LOG_LEVEL;
	}
}