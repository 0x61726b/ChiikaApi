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
#include "Request/MalManager.h"
#include "curl.h"
#include "pugixml.hpp"
#include <sstream>
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	
	int UserInfo::UnknownUser = -1;
	template<> MalManager* Singleton<MalManager>::msSingleton = 0;
	MalManager& MalManager::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
	MalManager* MalManager::GetPtr(void)
	{
		return msSingleton;
	}

	MalManager::MalManager()
	{

	}
	//----------------------------------------------------------------------------
	MalManager::~MalManager()
	{

	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnimeList(const UserAnimeList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK;

		m_vUserAnimeList.clear();
		m_vUserAnimeList = list;

	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnimeList(AnimeList list)
	{
		m_vAnimeList.clear();
		m_vAnimeList = list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnimeUpdateList(const UserAnimeList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK;
		m_vAnimeUpdateList.clear();
		m_vAnimeUpdateList= list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaList(const MangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.clear();
		m_vMangaList = list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaUpdateList(const MangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaUpdateList.clear();
		m_vMangaUpdateList= list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnime(const UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vUserAnimeList.insert(UserAnimeList::value_type(anime.Anime.Id,anime));
	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnimeToUpdates(const UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vAnimeUpdateList.insert(UserAnimeList::value_type(anime.Anime.Id,anime));
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteAnime(const UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vUserAnimeList.erase(anime.Anime.Id);
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteAnimeFromUpdates(const UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vAnimeUpdateList.erase(anime.Anime.Id);
	}
	//----------------------------------------------------------------------------
	void MalManager::UpdateAnime(const UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			UserAnimeList::iterator It = m_vUserAnimeList.find(anime.Anime.Id);

		//UserAnimeEntry copy = It->second;
		//It->second = anime;
		//if(copy.Anime.Synopsis.size() > 0)
		//{
		//	It->second.Anime.Synopsis = copy.Anime.Synopsis;
		//}
		It->second = anime;

		//Implement comparison

	}
	//----------------------------------------------------------------------------
	void MalManager::AddManga(const MangaInfo& manga)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.insert(MangaList::value_type(manga.Mango.Id,manga));
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaToUpdates(const MangaInfo& manga)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaUpdateList.insert(MangaList::value_type(manga.Mango.Id,manga));
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteManga(const MangaInfo& manga)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.erase(manga.Mango.Id);
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteMangaFromUpdates(const MangaInfo& manga)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaUpdateList.erase(manga.Mango.Id);
	}
	//----------------------------------------------------------------------------
	void MalManager::UpdateManga(const MangaInfo& manga)
	{
		CHIKA_AUTO_MUTEX_LOCK
			MangaList::iterator It = m_vMangaList.find(manga.Mango.Id);
		if(It != m_vMangaList.end())
			It->second = manga;
	}
	//----------------------------------------------------------------------------
	const UserAnimeList& MalManager::GetAnimeList() const
	{
		return m_vUserAnimeList;
	}
	//----------------------------------------------------------------------------
	const UserAnimeList& MalManager::GetAnimeUpdateList() const
	{

		return m_vAnimeUpdateList;
	}
	//----------------------------------------------------------------------------
	const MangaList& MalManager::GetMangaList() const
	{

		return m_vMangaList;
	}
	//----------------------------------------------------------------------------
	const MangaList& MalManager::GetMangaUpdateList() const
	{

		return m_vMangaUpdateList;
	}
	//----------------------------------------------------------------------------
	void MalManager::RequestDownloadAnimeStats(const UserAnimeEntry& info)
	{

	}
	//----------------------------------------------------------------------------
	UserAnimeEntry MalManager::GetAnimeById(int Id)
	{
		CHIKA_AUTO_MUTEX_LOCK

			AnimeListIt it = m_vUserAnimeList.find(Id);
		if(it != m_vUserAnimeList.end())
			return it->second;
		else
			return UserAnimeEntry();
	}
	//----------------------------------------------------------------------------
	void MalManager::UpdateAnimeList(const UserAnimeList& list)
	{
		UserAnimeList copy = list;
		AnimeListIt it = copy.begin();
		for(it; it != copy.end(); it++)
		{
			AnimeListIt f = m_vUserAnimeList.find(it->first);

			if(f != m_vUserAnimeList.end())
			{
				UpdateAnime(f->second);
			}
		}
	}
	//----------------------------------------------------------------------------
}

