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
#ifndef __Required_h__
#define __Required_h__
//----------------------------------------------------------------------------
#include "PlatformInformation.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//Generated by version.py
#include "ApiVersion.h"
}
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class ConfigManager;
	class MalManager;
	class RequestManager;
	class ThreadedRequest;
	class RequestListener;
	class Log;
	class LogManager;
	class AppSettings;
	class LocalDataManager;
	class AbstractNativeEventFilterHelper;
	class MediaPlayerRecognitionManager;
	class SeasonManager;

	class MPRecognitionInterface;
	class AnimeRecognition;
	class SettingInterface;
}
//----------------------------------------------------------------------------
#include "StdHeaders.h"
#include "Memory\MemoryAllocator.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	template <typename K,typename V,typename P = std::less<K>,typename A = STLAllocator<std::pair<const K,V>,GeneralAllocPolicy> >
	struct Map
	{
#ifdef CHIIKA_STD_CONTAINERS_CUSTOM_MEMORY_ALLOCATOR
		typedef typename std::map<K,V,P,A> type;
		typedef typename std::map<K,V,P,A>::iterator iterator;
		typedef typename std::map<K,V,P,A>::const_iterator const_iterator;
#else
		typedef typename std::map<K,V,P,A> type;
		typedef typename std::map<K,V,P,A>::iterator iterator;
		typedef typename std::map<K,V,P,A>::const_iterator const_iterator;
#endif
	};
	//----------------------------------------------------------------------------
	template <typename K,typename V,typename P = std::less<K>,typename A = STLAllocator<std::pair<const K,V>,GeneralAllocPolicy> >
	struct MultiMap
	{
#ifdef CHIIKA_STD_CONTAINERS_CUSTOM_MEMORY_ALLOCATOR
		typedef typename std::multimap<K,V,P,A> type;
		typedef typename std::multimap<K,V,P,A>::iterator iterator;
		typedef typename std::multimap<K,V,P,A>::const_iterator const_iterator;
#else
		typedef typename std::multimap<K,V,P,A> type;
		typedef typename std::multimap<K,V,P,A>::iterator iterator;
		typedef typename std::multimap<K,V,P,A>::const_iterator const_iterator;
#endif
	};
	//----------------------------------------------------------------------------
	template <typename T,typename A = STLAllocator<T,GeneralAllocPolicy> >
	struct Vector
	{
#ifdef CHIIKA_STD_CONTAINERS_CUSTOM_MEMORY_ALLOCATOR
		typedef typename std::vector<T,A> type;
		typedef typename std::vector<T,A>::iterator iterator;
		typedef typename std::vector<T,A>::const_iterator const_iterator;
#else
		typedef typename std::vector<T,A> type;
		typedef typename std::vector<T,A>::iterator iterator;
		typedef typename std::vector<T,A>::const_iterator const_iterator;
#endif
	};
	//----------------------------------------------------------------------------
	template <typename K,typename V> //std::pair doesnt allocate anything
	struct Pair
	{
#ifdef CHIIKA_STD_CONTAINERS_CUSTOM_MEMORY_ALLOCATOR
		typedef typename std::pair<K,V> type;
		typedef typename std::pair<K,V>::iterator iterator;
		typedef typename std::pair<K,V>::const_iterator const_iterator;
#else
		typedef typename std::pair<K,V> type;
		typedef typename std::pair<K,V>::iterator iterator;
		typedef typename std::pair<K,V>::const_iterator const_iterator;
#endif
	};
	//----------------------------------------------------------------------------
#	include "Common/UtilityDefines.h"
	//----------------------------------------------------------------------------
	class Stopwatch
	{
	public:
		Stopwatch() { }

		void Begin() { t1 = std::chrono::high_resolution_clock::now(); }
		void End() { t2 = std::chrono::high_resolution_clock::now(); }

		float GetDuration() { return  std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); }

		std::chrono::high_resolution_clock::time_point t1;
		std::chrono::high_resolution_clock::time_point t2;
	};
	//----------------------------------------------------------------------------
#	define CHIKA_AUTO_MUTEX_NAME chitanda
#	define CHIKA_AUTO_MUTEX /*mutable boost::recursive_mutex CHIKA_AUTO_MUTEX_NAME;*/
#	define CHIKA_AUTO_MUTEX_LOCK /*boost::recursive_mutex::scoped_lock AutoMutexLock(CHIKA_AUTO_MUTEX_NAME);*/
}
//----------------------------------------------------------------------------
#	include "Common/MyAnimeList.h"
#define ANIME_IN_LIST(x) (x.Animu.Id != 0)
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	typedef MultiMap<int,AnimeInfo>::type AnimeList;
	typedef Map<int,MangaInfo>::type MangaList;
	typedef AnimeList::iterator AnimeListIt;
	typedef MangaList::iterator MangaListIt;
	typedef MultiMap<String,CurlConfigOption>::type CurlConfigOptionMap;
#	define REQUEST_SUCCESS(x) (x == 200 || x == 201)
}
#ifdef YUME_PLATFORM_WIN32
#include "windows.h"
#include "winbase.h"
#endif
//----------------------------------------------------------------------------
#define ApiDebugMode
//#define ApiShowXMLOutput

#endif // __Required_h__
