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
#include "Database/LocalDataManager.h"
#include "Request/MalManager.h"
#include "Settings/Settings.h"
#include "Seasons/SeasonManager.h"
#include "json\json.h"
#include "Logging\FileHelper.h"
#include "Root\Root.h"

//----------------------------------------------------------------------------
ChiikaApi::LocalDataManager* gLdm = NULL;
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	FileLoader::FileLoader(ChiString path,FileType type)
	{
		m_sPath = path;
		m_eType = type;

		Create();
	}
	//----------------------------------------------------------------------------
	void FileLoader::Create()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);
		if(file.Open())
			return;

		FileWriter fr(dataFile);
		if(m_eType != FileType::SenpaiJSON)
		{
			if(fr.Open())
			{
				pugi::xml_document doc;
				pugi::xml_node  root = doc.append_child(kChiika);

				switch(m_eType)
				{
				case FileLoader::FileType::AnimeList:
				{
					root.append_child(kMyAnimeList);
				}
				break;
				case FileLoader::FileType::UserInfo:
				{
					root.append_child(kUserInfo);
				}
				break;
				case FileLoader::FileType::MangaList:
				{
					root.append_child(kMangaList);
				}
				break;
				case FileLoader::FileType::UpdateList:
				{
					root.append_child(kUpdateList);
				}
				break;
				case FileLoader::FileType::AnimeDetails:
				{
					root.append_child(kAnimeDetails);
				}
				break;
				}
				doc.save_file(dataFile.c_str());
				fr.Close();
			}
			else
			{

			}
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	AnimeFileLoader::AnimeFileLoader(ChiString path)
		: FileLoader(path,FileLoader::FileType::AnimeList)
	{

	}
	//----------------------------------------------------------------------------
	void AnimeFileLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if(file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());
			file.Close();

			XmlNode  root = doc.child(kChiika);
			XmlNode  myanimelist = root.child(kMyAnimeList);

			UserAnimeList list;
			ChiikaApi::AnimeList animeList;
			for (XmlNode anime = myanimelist.child(kAnime); anime; anime = anime.next_sibling())
			{
				Anime Anime;
				UserAnimeEntry info;
				for (XmlNode animeChild = anime.first_child(); animeChild; animeChild = animeChild.next_sibling())
				{
					const char* name = animeChild.name();
					const char* val = animeChild.text().get();

					Anime.SetKeyValue(name,val);
					info.SetKeyValue(name,val);
				}
				animeList.insert(ChiikaApi::AnimeList::value_type(Anime.GetKeyValue(kSeriesAnimedbId), Anime));
				info.Anime = Anime;
				list.insert(UserAnimeList::value_type(((Anime.GetKeyValue(kSeriesAnimedbId))), info));
			}
			MalManager::Get()->AddAnimeList(list);
			MalManager::Get()->AddAnimeList(animeList);
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	void AnimeFileLoader::Save()
	{
		ChiString dataFile = m_sPath;
		FileWriter file(dataFile);


		if(file.Open())
		{
			pugi::xml_document doc;

			XmlNode root = doc.append_child(kChiika);
			XmlNode  MAL = root.append_child(kMyAnimeList);

			ChiikaApi::UserAnimeList list = MalManager::Get()->GetAnimeList();
			ChiikaApi::UserAnimeList::iterator It;
			for(It = list.begin(); It != list.end(); ++It)
			{
				UserAnimeEntry Anime = It->second;


				XmlNode  anime = MAL.append_child(kAnime);
				KeyList keys;
				GetAnimeKeys(keys);


				for(size_t i = 0; i < keys.size(); i++)
				{
					XmlNode node = anime.append_child(ToStd(keys[i]));
					SetXMLValue(node,ToStd(Anime.Anime.GetKeyValue(keys[i])));
				}

				KeyList uaeList;
				GetUserAnimeEntryKeys(uaeList);

				for(size_t i = 0; i < uaeList.size(); i++)
				{
					XmlNode node = anime.append_child(ToStd(uaeList[i]));
					SetXMLValue(node,ToStd(Anime.GetKeyValue(uaeList[i])));
				}
			}
			doc.save_file(dataFile.c_str());
			file.Close();
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	MangaFileLoader::MangaFileLoader(ChiString path)
		: FileLoader(path,FileLoader::FileType::MangaList)
	{

	}
	//----------------------------------------------------------------------------
	void MangaFileLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if(file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());
			file.Close();

			XmlNode  root = doc.child(kChiika);
			XmlNode  mymangalist = root.child(kMangaList);

			ChiikaApi::MangaList mangaList;
			ChiikaApi::UserMangaList list;
			for (XmlNode manga = mymangalist.child(kManga); manga; manga = manga.next_sibling())
			{
				Manga Manga;
				UserMangaEntry info;

				for (XmlNode mangaChild = manga.first_child(); mangaChild; mangaChild = mangaChild.next_sibling())
				{
					const char* name = mangaChild.name();
					const char* val = mangaChild.text().get();

					Manga.SetKeyValue(name, val);
					info.SetKeyValue(name, val);
				}
				mangaList.insert(ChiikaApi::MangaList::value_type(Manga.GetKeyValue(kSeriesAnimedbId), Manga));
				info.Manga = Manga;
				list.insert(UserMangaList::value_type(Manga.GetKeyValue(kSeriesMangadbId), info));
			}
			MalManager::Get()->AddMangaList(list);
			MalManager::Get()->AddMangaList(mangaList);
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	void MangaFileLoader::Save()
	{
		ChiString dataFile = m_sPath;
		FileWriter file(dataFile);

		if (file.Open())
		{
			pugi::xml_document doc;

			XmlNode root = doc.append_child(kChiika);
			XmlNode  MAL = root.append_child(kMangaList);

			ChiikaApi::UserMangaList list = MalManager::Get()->GetMangaList();
			ChiikaApi::UserMangaList::iterator It;
			for (It = list.begin(); It != list.end(); ++It)
			{
				UserMangaEntry Manga = It->second;


				XmlNode  manga = MAL.append_child(kManga);
				KeyList keys;
				GetMangaKeys(keys);


				for (size_t i = 0; i < keys.size(); i++)
				{
					XmlNode node = manga.append_child(ToStd(keys[i]));
					SetXMLValue(node, ToStd(Manga.Manga.GetKeyValue(keys[i])));
				}

				KeyList uaeList;
				GetUserMangaEntryKeys(uaeList);

				for (size_t i = 0; i < uaeList.size(); i++)
				{
					XmlNode node = manga.append_child(ToStd(uaeList[i]));
					SetXMLValue(node, ToStd(Manga.GetKeyValue(uaeList[i])));
				}
			}
			doc.save_file(dataFile.c_str());
			file.Close();
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	UserInfoLoader::UserInfoLoader(ChiString path)
		: FileLoader(path,FileLoader::FileType::UserInfo)
	{
		m_UserDetailedInfo.SetKeyValue(kUserName,"");
	}
	//----------------------------------------------------------------------------
	void UserInfoLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);

		if(file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());


			XmlNode  root = doc.child(kChiika);
			XmlNode  info = root.child(kUserInfo);
			XmlNode	 anime = info.child(kAnime);
			XmlNode	 manga = info.child(kManga);

			for(XmlNode infoChild = info.first_child(); infoChild; infoChild = infoChild.next_sibling())
			{
				const char* name = infoChild.name();
				const char* val = infoChild.text().get();

				if (strcmp(name, kAnime) == 0 || strcmp(name, kManga) == 0)
					continue;

				Root::Get()->GetUser().SetKeyValue(name, val);
			}

			for (XmlNode animeChild = anime.first_child(); animeChild; animeChild = animeChild.next_sibling())
			{
				const char* name = animeChild.name();
				const char* val = animeChild.text().get();

				Root::Get()->GetUser().Anime.SetKeyValue(name, val);
			}

			for (XmlNode mangaChild = manga.first_child(); mangaChild; mangaChild = mangaChild.next_sibling())
			{
				const char* name = mangaChild.name();
				const char* val = mangaChild.text().get();

				Root::Get()->GetUser().Manga.SetKeyValue(name, val);
			}
			
			ChiikaApi::UserInfo ui = Root::Get()->GetUser();
			
			file.Close();

		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	void UserInfoLoader::Save()
	{
		ChiString dataFile = m_sPath;
		FileWriter file(dataFile);

		if(file.Open())
		{
			pugi::xml_document doc;
			XmlNode  root = doc.append_child(kChiika);
			XmlNode  UserInfo = root.append_child(kUserInfo);
			XmlNode	 AnimeInfo = UserInfo.append_child(kAnime);
			XmlNode	 MangaInfo = UserInfo.append_child(kManga);

			ChiikaApi::UserInfo ui = Root::Get()->GetUser();

			KeyList keys;
			GetUserInfoKeys(keys);

			FOR_(keys,i)
			{
				XmlNode node = UserInfo.append_child(ToStd(keys[i]));
				SetXMLValue(node,ToStd(ui.GetKeyValue(keys[i])));
			}

			KeyList animeKeys;
			GetUserInfoAnimeKeys(animeKeys);


			FOR_(animeKeys, i)
			{
				XmlNode node = AnimeInfo.append_child(ToStd(animeKeys[i]));
				SetXMLValue(node, ToStd(ui.Anime.GetKeyValue(animeKeys[i])));
			}

			KeyList mangaKeys;
			GetUserInfoMangaKeys(mangaKeys);


			FOR_(mangaKeys, i)
			{
				XmlNode node = MangaInfo.append_child(ToStd(mangaKeys[i]));
				std::string val = ui.Manga.GetKeyValue(mangaKeys[i]);
				SetXMLValue(node, ToStd(val));
			}

			doc.save_file(dataFile.c_str());
			file.Close();
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	UpdateListLoader::UpdateListLoader(ChiString path)
		: FileLoader(path,FileType::UpdateList)
	{

	}
	//----------------------------------------------------------------------------
	void UpdateListLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if(file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  updateList = root.child(kUpdateList);
#pragma region AnimeList
			ChiikaApi::UserAnimeList list;
			for(pugi::xml_node anime = updateList.child(kAnime); anime; anime = anime.next_sibling())
			{

				pugi::xml_node  animeDbId = anime.child(kSeriesAnimedbId);
				pugi::xml_node  Op = anime.child(kOperation);
				pugi::xml_node  series_title = anime.child(kSeriesTitle);
				pugi::xml_node  series_synonyms = anime.child(kSeriesSynonyms);
				pugi::xml_node  series_type = anime.child(kSeriesType);
				pugi::xml_node  series_episodes = anime.child(kSeriesEpisodes);
				pugi::xml_node  series_status = anime.child(kSeriesStatus);
				pugi::xml_node  series_start = anime.child(kSeriesStart);
				pugi::xml_node  series_end = anime.child(kSeriesEnd);
				pugi::xml_node  series_image = anime.child(kSeriesImage);
				pugi::xml_node  my_id = anime.child(kMyId); //What does this even mean?
				pugi::xml_node  my_watched_episodes = anime.child(kMyWatchedEpisodes);
				pugi::xml_node  my_start_date = anime.child(kMyStartDate);
				pugi::xml_node  my_finish_date = anime.child(kMyFinishDate);
				pugi::xml_node  my_score = anime.child(kMyScore);
				pugi::xml_node  my_status = anime.child(kMyStatus);
				pugi::xml_node  my_rewatching = anime.child(kMyRewatching);
				pugi::xml_node  my_rewatching_ep = anime.child(kMyRewatchingEp);
				pugi::xml_node  my_last_updated = anime.child(kMyLastUpdated);
				//pugi::xml_node  my_finish_date = anime.child(kMyFinishDate);

				/*Anime Anime;
				Anime.Id = FromXMLValueToInt(animeDbId);
				Anime.Title = FromXMLValueToStd(series_title);
				Anime.English = FromXMLValueToStd(series_synonyms);
				Anime.Type = (AnimeType)FromXMLValueToInt(series_type);
				Anime.EpisodeCount = FromXMLValueToInt(series_episodes);

				Anime.Status = (AnimeStatus)FromXMLValueToInt(series_status);
				Anime.StartDate = FromXMLValueToStd(series_start);
				Anime.EndDate = FromXMLValueToStd(series_end);
				Anime.Image = FromXMLValueToStd(series_image);*/

				//UserAnimeEntry info;
				//info.UpdateOperation = (CRUDOp)FromXMLValueToInt(Op);
				//info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
				//info.Anime = Anime;
				//info.MyId = FromXMLValueToInt(my_id);
				//info.StartDate = FromXMLValueToStd(my_start_date);
				//info.EndDate = FromXMLValueToStd(my_finish_date);
				//info.Score = FromXMLValueToInt(my_score);
				//info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
				//info.Rewatching = FromXMLValueToInt(my_rewatching);
				//info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
				//info.LastUpdated = FromXMLValueToStd(my_last_updated);
				//list.insert(UserAnimeList::value_type(Anime.Id,info));
			}
			MalManager::Get()->AddAnimeUpdateList(list);
#pragma endregion
#pragma region MangaList
			ChiikaApi::MangaList mangaList;
			for(pugi::xml_node manga = updateList.child(kManga); manga; manga = manga.next_sibling())
			{

				pugi::xml_node  series_mangadb_id = manga.child(kSeriesMangadbId);
				pugi::xml_node  Op = manga.child(kOperation);
				pugi::xml_node  series_title = manga.child(kSeriesTitle);
				pugi::xml_node  series_synonyms = manga.child(kSeriesSynonyms);
				pugi::xml_node  series_type = manga.child(kSeriesType);
				pugi::xml_node  series_chapters = manga.child(kSeriesChapters);
				pugi::xml_node  series_volumes = manga.child(kSeriesVolumes);
				pugi::xml_node  series_status = manga.child(kSeriesStatus);
				pugi::xml_node  series_start = manga.child(kSeriesStart);
				pugi::xml_node  series_end = manga.child(kSeriesEnd);
				pugi::xml_node  series_image = manga.child(kSeriesImage);
				pugi::xml_node  my_id = manga.child(kMyId); //What does this even mean?
				pugi::xml_node  my_read_chapters = manga.child(kMyReadChapters);
				pugi::xml_node  my_read_volumes = manga.child(kMyReadVolumes);
				pugi::xml_node  my_start_date = manga.child(kMyStartDate);
				pugi::xml_node  my_finish_date = manga.child(kMyFinishDate);
				pugi::xml_node  my_score = manga.child(kMyScore);
				pugi::xml_node  my_status = manga.child(kMyStatus);
				pugi::xml_node  my_rereading = manga.child(kMyRereading);
				pugi::xml_node  my_rereading_chap = manga.child(kMyRereadingChap);
				pugi::xml_node  my_last_updated = manga.child(kMyLastUpdated);
			}
			MalManager::Get()->AddMangaUpdateList(mangaList);
			//LOG("Update list file loaded successfully!")
			file.Close();
#pragma endregion
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	void UpdateListLoader::Save()
	{
		ChiString dataFile = m_sPath;
		FileWriter file(dataFile);


		if(file.Open())
		{
			pugi::xml_document doc;


			pugi::xml_node  root = doc.append_child(kChiika);
			pugi::xml_node  MAL = root.append_child(kUpdateList);

#pragma region Anime

			ChiikaApi::UserAnimeList list = MalManager::Get()->GetAnimeUpdateList();
			UserAnimeList::iterator It;
			for(It = list.begin(); It != list.end(); ++It)
			{
				UserAnimeEntry Anime = It->second;


				pugi::xml_node  anime = MAL.append_child(kAnime);
				pugi::xml_node  Op = anime.append_child(kOperation);
				pugi::xml_node  animeDbId = anime.append_child(kSeriesAnimedbId);
				pugi::xml_node  series_title = anime.append_child(kSeriesTitle);
				pugi::xml_node  series_synonyms = anime.append_child(kSeriesSynonyms);
				pugi::xml_node  series_type = anime.append_child(kSeriesType);
				pugi::xml_node  series_episodes = anime.append_child(kSeriesEpisodes);
				pugi::xml_node  series_status = anime.append_child(kSeriesStatus);
				pugi::xml_node  series_start = anime.append_child(kSeriesStart);
				pugi::xml_node  series_end = anime.append_child(kSeriesEnd);
				pugi::xml_node  series_image = anime.append_child(kSeriesImage);
				pugi::xml_node  my_id = anime.append_child(kMyId); //What does this even mean?
				pugi::xml_node  my_watched_episodes = anime.append_child(kMyWatchedEpisodes);
				pugi::xml_node  my_start_date = anime.append_child(kMyStartDate);
				pugi::xml_node  my_finish_date = anime.append_child(kMyFinishDate);
				pugi::xml_node  my_score = anime.append_child(kMyScore);
				pugi::xml_node  my_status = anime.append_child(kMyStatus);
				pugi::xml_node  my_rewatching = anime.append_child(kMyRewatching);
				pugi::xml_node  my_rewatching_ep = anime.append_child(kMyRewatchingEp);
				pugi::xml_node  my_last_updated = anime.append_child(kMyLastUpdated);

				//SetXMLValue(animeDbId,Anime.Anime.Id);
				//SetXMLValue(Op,Anime.UpdateOperation);
				//SetXMLValue(series_title,Anime.Anime.Title.c_str());
				//SetXMLValue(series_synonyms,Anime.Anime.English.c_str());
				//SetXMLValue(series_type,Anime.Anime.Type);
				//SetXMLValue(series_episodes,Anime.Anime.EpisodeCount);
				//SetXMLValue(series_status,Anime.Anime.Status);
				//SetXMLValue(series_start,Anime.Anime.StartDate.c_str());
				//SetXMLValue(series_end,Anime.Anime.EndDate.c_str());
				//SetXMLValue(series_image,Anime.Anime.Image.c_str());
				//SetXMLValue(my_id,Anime.MyId);
				//SetXMLValue(my_watched_episodes,Anime.WatchedEpisodes);
				//SetXMLValue(my_start_date,Anime.StartDate.c_str());
				//SetXMLValue(my_finish_date,Anime.EndDate.c_str());
				//SetXMLValue(my_score,Anime.Score);
				//SetXMLValue(my_status,Anime.Status);
				//SetXMLValue(my_rewatching,Anime.Rewatching);
				//SetXMLValue(my_rewatching_ep,Anime.RewatchingEp);
				//SetXMLValue(my_last_updated,Anime.LastUpdated.c_str());

			}
#pragma endregion
#pragma region Manga
			ChiikaApi::MangaList mangaList = MalManager::Get()->GetMangaUpdateList();

			MangaList::iterator ItManga;
			for(ItManga = mangaList.begin(); ItManga != mangaList.end(); ++ItManga)
			{
				

				//pugi::xml_node  manga = MAL.append_child(kManga);
				//pugi::xml_node  Op = manga.append_child(kOperation);
				//pugi::xml_node  series_mangadb_id = manga.append_child(kSeriesMangadbId);

				//pugi::xml_node  series_title = manga.append_child(kSeriesTitle);
				//pugi::xml_node  series_synonyms = manga.append_child(kSeriesSynonyms);
				//pugi::xml_node  series_type = manga.append_child(kSeriesType);
				//pugi::xml_node  series_chapters = manga.append_child(kSeriesChapters);
				//pugi::xml_node  series_volumes = manga.append_child(kSeriesVolumes);
				//pugi::xml_node  series_status = manga.append_child(kSeriesStatus);
				//pugi::xml_node  series_start = manga.append_child(kSeriesStart);
				//pugi::xml_node  series_end = manga.append_child(kSeriesEnd);
				//pugi::xml_node  series_image = manga.append_child(kSeriesImage);
				//pugi::xml_node  my_id = manga.append_child(kMyId); //What does this even mean?
				//pugi::xml_node  my_read_chapters = manga.append_child(kMyReadChapters);
				//pugi::xml_node  my_read_volumes = manga.append_child(kMyReadVolumes);
				//pugi::xml_node  my_start_date = manga.append_child(kMyStartDate);
				//pugi::xml_node  my_finish_date = manga.append_child(kMyFinishDate);
				//pugi::xml_node  my_score = manga.append_child(kMyScore);
				//pugi::xml_node  my_status = manga.append_child(kMyStatus);
				//pugi::xml_node  my_rereading = manga.append_child(kMyRereading);
				//pugi::xml_node  my_rereading_chap = manga.append_child(kMyRereadingChap);
				//pugi::xml_node  my_last_updated = manga.append_child(kMyLastUpdated);

				//SetXMLValue(series_mangadb_id,Mango.Mango.Id);
				//SetXMLValue(Op,Mango.UpdateOperation);
				//SetXMLValue(series_title,Mango.Mango.Title.c_str());
				//SetXMLValue(series_synonyms,Mango.Mango.English.c_str());
				//SetXMLValue(series_type,Mango.Mango.Type);
				//SetXMLValue(series_chapters,Mango.Mango.Chapters);
				//SetXMLValue(series_volumes,Mango.Mango.Volumes);
				//SetXMLValue(series_status,Mango.Mango.Status);
				//SetXMLValue(series_start,Mango.Mango.StartDate.c_str());
				//SetXMLValue(series_end,Mango.Mango.EndDate.c_str());
				//SetXMLValue(series_image,Mango.Mango.Image.c_str());
				//SetXMLValue(my_id,Mango.MyId);
				//SetXMLValue(my_read_chapters,Mango.ReadChapters);
				//SetXMLValue(my_read_volumes,Mango.ReadVolumes);
				//SetXMLValue(my_start_date,Mango.StartDate.c_str());
				//SetXMLValue(my_finish_date,Mango.EndDate.c_str());
				//SetXMLValue(my_score,Mango.Score);
				//SetXMLValue(my_status,Mango.Status);
				//SetXMLValue(my_rereading,Mango.Rereading);
				//SetXMLValue(my_rereading_chap,Mango.RereadChapters);
				//SetXMLValue(my_last_updated,Mango.LastUpdated.c_str());


			}
#pragma endregion
			doc.save_file(dataFile.c_str());
			//LOG("Update list file saved successfully!")
		}
		else
		{

		}
	}
	//----------------------------------------------------------------------------
	AnimeDetailsLoader::AnimeDetailsLoader(ChiString path)
		: FileLoader(path,FileType::AnimeDetails)
	{
	}
	//----------------------------------------------------------------------------
	void AnimeDetailsLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if(file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  animeDetails = root.child(kAnimeDetails);

			for(pugi::xml_node anime = animeDetails.child(kAnime); anime; anime = anime.next_sibling())
			{
				pugi::xml_node  Id = anime.child(kId);
				pugi::xml_node  syn = anime.child(kSynopsis);
				pugi::xml_node  tags = anime.child(kTags);
				pugi::xml_node  premiered = anime.child(kPremiered);
				pugi::xml_node  producers = anime.child(kProducers);
				pugi::xml_node  duration = anime.child(kDurationPerEpisode);

				pugi::xml_node  score = anime.child(kScore);
				pugi::xml_node  ranked = anime.child(kRanked);
				pugi::xml_node  popularity = anime.child(kPopularity);

				StringVector vTags;
				for(pugi::xml_node tag = tags.child(kTag); tag; tag = tag.next_sibling())
				{
					vTags.push_back(tag.text().get());
				}

				StringVector vProducers;
				for(pugi::xml_node producer = producers.child(kProducer); producer; producer = producer.next_sibling())
				{
					vProducers.push_back(producer.text().get());
				}

				UserAnimeEntry findAnime = MalManager::Get()->GetAnimeById(FromXMLValueToInt(Id));

				if (atoi(ToStd(findAnime.GetKeyValue(kSeriesAnimedbId))) != UnknownAnimeId)
				{
					ChiikaApi::AnimeDetails details = findAnime.Anime.ExtraDetails;
					details.Synopsis = syn.text().get();
					details.DurationPerEpisode = duration.text().get();
					details.Premiered = premiered.text().get();

					ChiikaApi::AnimeStatistics stats = findAnime.Anime.Statistics;
					stats.Popularity = atoi(popularity.text().get());
					stats.Ranked = atoi(ranked.text().get());
					stats.Score = atof(score.text().get());

					for(StringVectorSize i = 0; i < vTags.size(); i++)
					{
						ChiString tag = vTags[i];
						details.Tags.push_back(tag);
					}
					for(StringVectorSize i = 0; i < vProducers.size(); i++)
					{
						ChiString producer = vProducers[i];
						details.Producers.push_back(producer);
					}


					findAnime.Anime.ExtraDetails = details;
					findAnime.Anime.Statistics = stats;
					MalManager::Get()->UpdateAnime(findAnime);
				}

			}
		}
		file.Close();
	}
	//----------------------------------------------------------------------------
	void AnimeDetailsLoader::Save()
	{
		ChiString dataFile = m_sPath;
		FileWriter file(dataFile);

		if(file.Open())
		{
			pugi::xml_document doc;
			pugi::xml_node  root = doc.append_child(kChiika);
			pugi::xml_node  MAL = root.append_child(kAnimeDetails);

			ChiikaApi::UserAnimeList list = MalManager::Get()->GetAnimeList();
			ChiikaApi::UserAnimeList::iterator It;
			for(It = list.begin(); It != list.end(); ++It)
			{
				UserAnimeEntry Anime = It->second;
				ChiikaApi::AnimeDetails Details = It->second.Anime.ExtraDetails;
				ChiikaApi::AnimeStatistics Statistics = It->second.Anime.Statistics;

				pugi::xml_node  anime = MAL.append_child(kAnime);
				pugi::xml_node  animeDbId = anime.append_child(kId);
				pugi::xml_node  syn = anime.append_child(kSynopsis);
				pugi::xml_node  tags = anime.append_child(kTags);
				pugi::xml_node  premiered = anime.append_child(kPremiered);
				pugi::xml_node  producers = anime.append_child(kProducers);
				pugi::xml_node  duration = anime.append_child(kDurationPerEpisode);

				pugi::xml_node  score = anime.append_child(kScore);
				pugi::xml_node  ranked = anime.append_child(kRanked);
				pugi::xml_node  popularity = anime.append_child(kPopularity);


				SetXMLValue(animeDbId, atoi(ToStd(Anime.GetKeyValue(kSeriesAnimedbId))));
				SetXMLValue(syn,Details.Synopsis.c_str());
				SetXMLValue(premiered,Details.Premiered.c_str());
				SetXMLValue(duration,Details.DurationPerEpisode.c_str());

				SetXMLValue(score,Statistics.Score);
				SetXMLValue(ranked,Statistics.Ranked);
				SetXMLValue(popularity,Statistics.Popularity);

				for(StringVectorSize i = 0; i < Details.Producers.size(); i++)
				{
					ChiString p = Details.Producers[i];
					pugi::xml_node pNode = producers.append_child(kProducer);
					SetXMLValue(pNode,p.c_str());
				}


				for(StringVectorSize i = 0; i < Details.Tags.size(); i++)
				{
					ChiString tag = Details.Tags[i];
					pugi::xml_node  tagNode = tags.append_child(kTag);
					SetXMLValue(tagNode,tag.c_str());
				}
			}
			doc.save_file(dataFile.c_str());
			file.Close();
		}
	}
	//----------------------------------------------------------------------------
	SenpaiLoader::SenpaiLoader(ChiString path)
		: FileLoader(path,FileType::SenpaiJSON)
	{
	}
	//----------------------------------------------------------------------------
	void SenpaiLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if(file.Open())
		{
			Json::Value root;
			Json::Reader reader;
			ChiString fileData = file.Read();

			bool b = reader.parse(fileData,root);

			if(b)
			{
				//Root
				const Json::Value meta = root["meta"];
				ChiString season = (meta["season"].asString());
				ChiString start = (meta["start"].asString());

				const Json::Value tz = meta["tz"];
				Json::Value::const_iterator It = tz.begin();

				TimezoneMap list;
				for(It; It != tz.end(); It++)
				{
					Json::Value inner = *It;

					Timezone tz;
					tz.Name = (inner["abbr"].asString());
					tz.TimezoneIdentifier = (It.name());
					tz.Offset = (inner["offset"].asString());

					list.insert(TimezoneMap::value_type(tz.TimezoneIdentifier,tz));
				}
				SeasonManager::Get().SetTimezones(list);




				//Items
				const Json::Value items = root["items"];
				Json::Value::const_iterator itemsIt = items.begin();
				SenpaiData sd;

				for(itemsIt; itemsIt != items.end(); itemsIt++)
				{
					Json::Value v = *itemsIt;

					SenpaiItem si;
					si.Name = JsToQ(v["name"]);
					si.MalID = atoi(JsToQ(v["MALID"]).c_str());
					si.IsSequel = (v["isSequel"].asBool());
					si.Simulcast = JsToQ(v["simulcast"]);
					si.AirdateStr = JsToQ(v["airdate"]);
					si.Fansub = JsToQ(v["fansub"]);
					si.SimulcastDelay = v["simulcast_delay"].asInt();
					si.Type = JsToQ(v["type"]);
					si.MissingAirdate = v["missingAirdate"].asBool();
					si.MissingAirtime = v["missingAirtime"].asBool();
					si.AirDateOriginal = JsToQ(v["airdate_orig"]);


					const Json::Value airdates = v["airdates"];

					Json::Value::const_iterator adIt = airdates.begin();
					Map<ChiString,Airdate>::type airdateList;

					ForEachOnStd(adIt,airdates)
					{
						Json::Value t = *adIt;

						Airdate ad;

						ChiString timezoneValue = (adIt.name());

						ad.TimeZone = list.find(timezoneValue)->second;
						ad.RdDate = JsToQ(t["rd_date"]);
						ad.RdTime = JsToQ(t["rd_time"]);
						ad.Weekday = t["weekday"].asInt();
						ad.RdWeekday = JsToQ(t["rd_weekday"]);

						airdateList.insert(std::make_pair(ad.TimeZone.TimezoneIdentifier,ad));
					}
					si.Airdates = airdateList;
					sd.push_back(si);
				}
				SeasonManager::Get().SetSenpaiData(sd);
			}
			else
			{
			}


		}
	}
	//----------------------------------------------------------------------------
	void SenpaiLoader::Save()
	{
	}
	//----------------------------------------------------------------------------
	LocalDataManager::LocalDataManager()
	{
		m_AnimeLoader = NULL;
		m_MangaLoader = NULL;
		m_UserInfoLoader = NULL;
		m_UpdateListLoader = NULL;
		m_AnimeDetailsLoader = NULL;
		m_SenpaiLoader = NULL;

		gLdm = this;
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::Initialize()
	{
		m_sAnimeListFilePath = AppSettings::Get().GetChiStringOption(LIBRARY_ANIME_LIST_PATH);
		m_sMangaListFilePath = AppSettings::Get().GetChiStringOption(LIBRARY_MANGA_LIST_PATH);
		m_sUserInfoPath = AppSettings::Get().GetChiStringOption(LIBRARY_USER_INFO_PATH);
		m_sUpdateListPath = AppSettings::Get().GetChiStringOption(LIBRARY_UPDATE_LIST_PATH);
		m_sAnimeDetailsPath = AppSettings::Get().GetChiStringOption(LIBRARY_ANIME_DETAILS_PATH);
		m_sSenpaiPath = AppSettings::Get().GetChiStringOption(LIBRARY_SENPAI_PATH);;


		m_AnimeLoader = new AnimeFileLoader(m_sAnimeListFilePath);
		m_MangaLoader = new MangaFileLoader(m_sMangaListFilePath);
		m_UserInfoLoader = new UserInfoLoader(m_sUserInfoPath);
		m_UpdateListLoader = new UpdateListLoader(m_sUpdateListPath);
		m_AnimeDetailsLoader = new AnimeDetailsLoader(m_sAnimeDetailsPath);
		m_SenpaiLoader = new SenpaiLoader(m_sSenpaiPath);

		LoadUserInfo();
		LoadAnimeList();
		LoadMangaList();
		LoadUpdateList();
		LoadSenpaiData();

	}

	LocalDataManager::~LocalDataManager()
	{
		TryDelete(m_AnimeLoader);
		TryDelete(m_MangaLoader);
		TryDelete(m_UserInfoLoader);
		TryDelete(m_UpdateListLoader);
		TryDelete(m_AnimeDetailsLoader);
		TryDelete(m_SenpaiLoader);
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveAnimeList()
	{
		m_AnimeLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::LoadAnimeList()
	{
		m_AnimeLoader->Load();
		m_AnimeDetailsLoader->Load();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveMangaList()
	{
		m_MangaLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::LoadMangaList()
	{
		m_MangaLoader->Load();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveUpdateList()
	{
		m_UpdateListLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::LoadUpdateList()
	{
		m_UpdateListLoader->Load();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SetUserNamePass(ChiString u,ChiString p)
	{
		m_UserDetailedInfo.SetKeyValue(kUserName,u);
		m_UserDetailedInfo.SetKeyValue(kPass,p);

		m_UserInfoLoader->m_UserDetailedInfo = m_UserDetailedInfo;
		SaveUserInfo();

	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveUserInfo()
	{
		m_UserInfoLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::LoadUserInfo()
	{
		m_UserInfoLoader->Load();
		m_UserDetailedInfo = m_UserInfoLoader->m_UserDetailedInfo;
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveAnimeDetails()
	{
		m_AnimeDetailsLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::LoadAnimeDetails()
	{
		m_AnimeDetailsLoader->Load();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveSenpaiData()
	{
		m_SenpaiLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::LoadSenpaiData()
	{
		m_SenpaiLoader->Load();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SaveAll()
	{
		m_AnimeLoader->Save();
		m_MangaLoader->Save();
		m_UserInfoLoader->Save();
		m_UpdateListLoader->Save();
		m_AnimeDetailsLoader->Save();
		m_SenpaiLoader->Save();
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::SetUserInfo(const UserInfo& i)
	{

	}
	//----------------------------------------------------------------------------
	const UserInfo& LocalDataManager::GetUserInfo()
	{
		return m_UserDetailedInfo;
	}
	//----------------------------------------------------------------------------
	void LocalDataManager::GetUserInfo(UserInfo& ui)
	{
		ui = m_UserDetailedInfo;
	}
	//----------------------------------------------------------------------------
	LocalDataManager* LocalDataManager::Get()
	{
		return gLdm;
	}
	//----------------------------------------------------------------------------
}
