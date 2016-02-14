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
		// 5/7 algorithm ahead
		// There is no need to re construct this list when syncing user list right? I hope so..
		// So we should just find the delta of two lists then add what's missing

		size_t userAnimelistSize = m_vUserAnimeList.size();
		size_t currentLocalAnimelistSize = m_vAnimeList.size();

		if (currentLocalAnimelistSize == 0)
		{
			m_vAnimeList = list;
			return;
		}

		size_t diff = userAnimelistSize - currentLocalAnimelistSize;

		AnimeList deltaMap;
		if (diff > 0)
		{
			UserAnimeList::iterator BiggerIt;
			ForEachOnStd(BiggerIt, m_vUserAnimeList)
			{
				ChiString uAnimeId = BiggerIt->first;

				AnimeList::iterator SmallerIt;
				bool doesThisPresentInSmallerList = false;
				ForEachOnStd(SmallerIt, m_vAnimeList)
				{
					ChiString animeId = SmallerIt->first;

					if (uAnimeId == animeId)
					{
						//Present in both list
						doesThisPresentInSmallerList = true;
						break;
					}
					else
					{

					}
				}
				if (!doesThisPresentInSmallerList)
				{
					AnimeList::iterator newListIt = list.find(BiggerIt->first);

					if (IsValidIt(newListIt, list))
					{
						m_vAnimeList.insert(AnimeList::value_type(uAnimeId, newListIt->second));
					}
				}
			}
		}
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaList(MangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK;

		m_vMangaList.clear();
		m_vMangaList = list;
	}
	//----------------------------------------------------------------------------
	void MalManager::AddMangaList(UserMangaList& list)
	{
		CHIKA_AUTO_MUTEX_LOCK;


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

