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
	//----------------------------------------------------------------------------
	MalManager::MalManager()
	{
		
	}
	//----------------------------------------------------------------------------
	MalManager::~MalManager()
	{

	}
	//----------------------------------------------------------------------------
	void MalManager::AddAnimeList(UserAnimeList& list)
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
	void MalManager::AddMangaList(MangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.clear();
		m_vMangaList = list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaList(UserMangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK
			m_vMangaList.clear();
		m_vUserMangaList = list;
	}
	//----------------------------------------------------------------------------
	UserMangaList& MalManager::GetMangaList()
	{
		return m_vUserMangaList;
	}
	//----------------------------------------------------------------------------
	AnimeList& MalManager::GetAnimes()
	{
		return m_vAnimeList;
	}
	//----------------------------------------------------------------------------
	UserAnimeList& MalManager::GetAnimeList()
	{
		return m_vUserAnimeList;
	}
	//----------------------------------------------------------------------------
	Anime MalManager::GetAnimeById(int AnimeId)
	{
		AnimeList::iterator It = m_vAnimeList.find(std::to_string(AnimeId));

		if (It != m_vAnimeList.end())
			return m_vAnimeList.find(std::to_string(AnimeId))->second;
		else
			return Anime();
	}
}

