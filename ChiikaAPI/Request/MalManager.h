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
#ifndef __MALUtility_h__
#define __MALUtility_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport MalManager
	{
	public:
		MalManager();
		virtual ~MalManager();

		static MalManager* Get();

		CHIKA_AUTO_MUTEX

		

		void AddAnimeList(const UserAnimeList& list);
		void AddAnimeUpdateList(const UserAnimeList& list);
		void AddAnimeList(AnimeList list);

		void AddMangaList(const MangaList& list);
		void AddMangaUpdateList(const MangaList& list);

		void AddAnime(const UserAnimeEntry& anime);
		void AddAnimeToUpdates(const UserAnimeEntry& anime);

		void DeleteAnimeFromUpdates(const UserAnimeEntry& anime);
		void DeleteAnime(const UserAnimeEntry& anime);
		void UpdateAnime(const UserAnimeEntry& anime);

		void UpdateAnimeList(const UserAnimeList& list);

		void AddManga(const MangaInfo& anime);
		void AddMangaToUpdates(const MangaInfo& anime);

		void DeleteMangaFromUpdates(const MangaInfo& anime);
		void DeleteManga(const MangaInfo& anime);
		void UpdateManga(const MangaInfo& anime);


		const UserAnimeList& GetAnimeList() const;
		const UserAnimeList& GetAnimeUpdateList() const;

		const MangaList& GetMangaList() const;
		const MangaList& GetMangaUpdateList() const;

		void RequestDownloadAnimeStats(const UserAnimeEntry& info);

		UserAnimeEntry GetAnimeById(int Id);



	private:
		UserAnimeList m_vUserAnimeList;
		AnimeList	  m_vAnimeList;

		UserAnimeList m_vAnimeUpdateList;

		MangaList m_vMangaList;
		MangaList m_vMangaUpdateList;
	};
}
//----------------------------------------------------------------------------
#endif // __Required_h__
