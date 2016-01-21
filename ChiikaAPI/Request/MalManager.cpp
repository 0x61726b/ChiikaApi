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
ChiikaApi::MalManager* gMalManager = NULL;
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	MalManager* MalManager::Get()
	{
		return gMalManager;
	}
	//----------------------------------------------------------------------------
	MalManager::MalManager()
	{
		gMalManager = this;
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
	void MalManager::AddMangaList(const UserMangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.clear();
		m_vUserMangaList = list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaUpdateList(const MangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaUpdateList.clear();
		m_vMangaUpdateList= list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnime(UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vUserAnimeList.insert(UserAnimeList::value_type(anime.Anime.GetKeyValue(kSeriesAnimedbId)
			, anime));
	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnimeToUpdates(UserAnimeEntry& anime)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vAnimeUpdateList.insert(UserAnimeList::value_type(anime.Anime.GetKeyValue(kSeriesAnimedbId)
			, anime));
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteAnime(UserAnimeEntry& anime)
	{
		/*CHIKA_AUTO_MUTEX_LOCK
			m_vUserAnimeList.erase(atoi(ToStd(anime.Anime.GetKeyValue(kSeriesAnimedbId))));*/
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteAnimeFromUpdates(UserAnimeEntry& anime)
	{
		/*CHIKA_AUTO_MUTEX_LOCK
			m_vAnimeUpdateList.erase(atoi(ToStd(anime.Anime.GetKeyValue(kSeriesAnimedbId))));*/
	}
	//----------------------------------------------------------------------------
	void MalManager::UpdateAnime(UserAnimeEntry& anime)
	{
		//CHIKA_AUTO_MUTEX_LOCK
		//	UserAnimeList::iterator It = m_vUserAnimeList.find(atoi(ToStd(anime.Anime.GetKeyValue(kSeriesAnimedbId))));

		////UserAnimeEntry copy = It->second;
		////It->second = anime;
		////if(copy.Anime.Synopsis.size() > 0)
		////{
		////	It->second.Anime.Synopsis = copy.Anime.Synopsis;
		////}
		//It->second = anime;

		////Implement comparison

	}
	//----------------------------------------------------------------------------
	void MalManager::AddManga(const UserMangaEntry& manga)
	{
		/*CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.insert(MangaList::value_type(manga.GetKeyValue(kSeriesMangadbId),manga));*/
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaToUpdates(const UserMangaEntry& manga)
	{
		/*CHIKA_AUTO_MUTEX_LOCK
			m_vMangaUpdateList.insert(MangaList::value_type(manga.Mango.Id,manga));*/
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteManga(const UserMangaEntry& manga)
	{
		/*CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.erase(manga.Mango.Id);*/
	}
	//----------------------------------------------------------------------------
	void MalManager::DeleteMangaFromUpdates(const UserMangaEntry& manga)
	{
		/*CHIKA_AUTO_MUTEX_LOCK
			m_vMangaUpdateList.erase(manga.Mango.Id);*/
	}
	//----------------------------------------------------------------------------
	void MalManager::UpdateManga(const UserMangaEntry& manga)
	{
		//CHIKA_AUTO_MUTEX_LOCK
		//	MangaList::iterator It = m_vMangaList.find(manga.Mango.Id);
		//if(It != m_vMangaList.end())
		//	It->second = manga;
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
	const UserMangaList& MalManager::GetMangaList() const
	{
		return m_vUserMangaList;
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

			AnimeListIt it = m_vUserAnimeList.find(std::to_string(Id));
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

