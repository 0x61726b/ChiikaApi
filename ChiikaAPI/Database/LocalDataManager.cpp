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
//----------------------------------------------------------------------------
namespace
{
	const char* kChiika = "Chiika";
	const char* kMyAnimeList = "MyAnimeList";
	const char* kUserInfo = "UserInfo";
	const char* kMangaList = "MangaList";
	const char* kUpdateList = "UpdateList";
	const char* kAnimeDetails = "AnimeDetails";
	const char* kAnime = "anime";
	const char* kManga = "manga";
	const char* kSeriesAnimedbId = "series_animedb_id";
	const char* kSeriesTitle = "series_title";
	const char* kSeriesSynonyms = "series_synonyms";
	const char* kSeriesType = "series_type";
	const char* kSeriesEpisodes = "series_episodes";
	const char* kSeriesStatus = "series_status";
	const char* kSeriesStart = "series_start";
	const char* kSeriesEnd = "series_end";
	const char* kSeriesImage = "series_image";
	const char* kMyId = "my_id";
	const char* kMyWatchedEpisodes = "my_watched_episodes";
	const char* kMyStartDate = "my_start_date";
	const char* kMyFinishDate = "my_finish_date";
	const char* kMyScore = "my_score";
	const char* kMyStatus = "my_status";
	const char* kMyRewatching = "my_rewatching";
	const char* kMyRewatchingEp = "my_rewatching_ep";
	const char* kMyLastUpdated = "my_last_updated";
	const char* kSeriesMangadbId = "series_mangadb_id";
	const char* kSeriesChapters = "series_chapters";
	const char* kSeriesVolumes = "series_volumes";

	const char* kMyReadChapters = "my_read_chapters";
	const char* kMyRereading = "my_rereading";
	const char* kMyReadVolumes = "my_read_volumes";
	const char* kMyRereadingChap = "my_rereading_chap";


	const char* kUserName = "UserName";
	const char* kPass = "Pass";
	const char* kWatching = "Watching";
	const char* kCompleted = "Completed";
	const char* kOnHold = "OnHold";
	const char* kDropped = "Dropped";
	const char* kPlanToWatch = "PlanToWatch";
	const char* kDaySpentAnime = "DaySpentAnime";
	const char* kReading = "Reading";

	const char* kRead = "Read";
	const char* kMangaOnHold = "MangaOnHold";
	const char* kMangaDropped = "MangaDropped";
	const char* kPlanToRead = "PlanToRead";
	const char* kDaySpentReading = "DaySpentReading";
	const char* kOperation = "Operation";

	const char* kId = "Id";
	const char* kSynopsis = "Synopsis";
	const char* kTags = "Tags";
	const char* kPremiered = "Premiered";
	const char* kProducers = "Producers";
	const char* kDurationPerEpisode = "DurationPerEpisode";
	const char* kScore = "Score";
	const char* kRanked = "Ranked";
	const char* kPopularity = "Popularity";
	const char* kTag = "Tag";
	const char* kProducer = "Producer";
}
//----------------------------------------------------------------------------
ChiikaApi::LocalDataManager* gLdm = NULL;
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	FileLoader::FileLoader(ChiString path, FileType type)
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
		if (file.Open())
			return;

		FileWriter fr(dataFile);
		if (m_eType != FileType::SenpaiJSON)
		{
			if (fr.Open())
			{
				pugi::xml_document doc;
				pugi::xml_node  root = doc.append_child(kChiika);

				switch (m_eType)
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
		: FileLoader(path, FileLoader::FileType::AnimeList)
	{

	}
	//----------------------------------------------------------------------------
	void AnimeFileLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if (file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());
			file.Close();

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  myanimelist = root.child(kMyAnimeList);

			UserAnimeList list;
			ChiikaApi::AnimeList animeList;
			for (pugi::xml_node anime = myanimelist.child(kAnime); anime; anime = anime.next_sibling())
			{

				pugi::xml_node  animeDbId = anime.child(kSeriesAnimedbId);
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

				Anime Anime;
				Anime.Id = FromXMLValueToInt(animeDbId);
				Anime.Title = FromXMLValueToStd(series_title);
				Anime.English = FromXMLValueToStd(series_synonyms);
				Anime.Type = (AnimeType)FromXMLValueToInt(series_type);
				Anime.EpisodeCount = FromXMLValueToInt(series_episodes);

				Anime.Status = (AnimeStatus)FromXMLValueToInt(series_status);
				Anime.StartDate = FromXMLValueToStd(series_start);
				Anime.EndDate = FromXMLValueToStd(series_end);
				Anime.Image = FromXMLValueToStd(series_image);
				animeList.insert(ChiikaApi::AnimeList::value_type(Anime.Id,Anime));

				UserAnimeEntry info;
				info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
				info.Anime = Anime;
				info.MyId = FromXMLValueToInt(my_id);
				info.StartDate = FromXMLValueToStd(my_start_date);
				info.EndDate = FromXMLValueToStd(my_finish_date);
				info.Score = FromXMLValueToInt(my_score);
				info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
				info.Rewatching = FromXMLValueToInt(my_rewatching);
				info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
				info.LastUpdated = FromXMLValueToStd(my_last_updated);
				list.insert(UserAnimeList::value_type(Anime.Id, info));
			}
			MalManager::Get().AddAnimeList(list);
			MalManager::Get().AddAnimeList(animeList);
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


		if (file.Open())
		{
			pugi::xml_document doc;

			pugi::xml_node  root = doc.append_child(kChiika);
			pugi::xml_node  MAL = root.append_child(kMyAnimeList);

			ChiikaApi::UserAnimeList list = MalManager::Get().GetAnimeList();
			ChiikaApi::UserAnimeList::iterator It;
			for (It = list.begin(); It != list.end(); ++It)
			{
				UserAnimeEntry Anime = It->second;


				pugi::xml_node  anime = MAL.append_child(kAnime);

				pugi::xml_node  animeDbId = anime.child(kSeriesAnimedbId);
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

				SetXMLValue(animeDbId, Anime.Anime.Id);
				SetXMLValue(series_title, Anime.Anime.Title.c_str());
				SetXMLValue(series_synonyms, Anime.Anime.English.c_str());
				SetXMLValue(series_type, Anime.Anime.Type);
				SetXMLValue(series_episodes, Anime.Anime.EpisodeCount);
				SetXMLValue(series_status, Anime.Anime.Status);
				SetXMLValue(series_start, Anime.Anime.StartDate.c_str());
				SetXMLValue(series_end, Anime.Anime.EndDate.c_str());
				SetXMLValue(series_image, Anime.Anime.Image.c_str());
				SetXMLValue(my_id, Anime.MyId);
				SetXMLValue(my_watched_episodes, Anime.WatchedEpisodes);
				SetXMLValue(my_start_date, Anime.StartDate.c_str());
				SetXMLValue(my_finish_date, Anime.EndDate.c_str());
				SetXMLValue(my_score, Anime.Score);
				SetXMLValue(my_status, Anime.Status);
				SetXMLValue(my_rewatching, Anime.Rewatching);
				SetXMLValue(my_rewatching_ep, Anime.RewatchingEp);
				SetXMLValue(my_last_updated, Anime.LastUpdated.c_str());

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
		: FileLoader(path, FileLoader::FileType::MangaList)
	{

	}
	//----------------------------------------------------------------------------
	void MangaFileLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if (file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  mymangalist = root.child(kMangaList);

			ChiikaApi::MangaList list;
			for (pugi::xml_node manga = mymangalist.child(kManga); manga; manga = manga.next_sibling())
			{

				pugi::xml_node  series_mangadb_id = manga.child(kSeriesMangadbId);
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


				Manga mango;
				mango.Id = FromXMLValueToInt(series_mangadb_id);
				mango.Title = FromXMLValueToStd(series_title);
				mango.English = FromXMLValueToStd(series_synonyms);
				mango.Type = (MangaType)FromXMLValueToInt(series_type);
				mango.Chapters = FromXMLValueToInt(series_chapters);
				mango.Volumes = FromXMLValueToInt(series_volumes);

				mango.Status = (MangaStatus)FromXMLValueToInt(series_status);
				mango.StartDate = FromXMLValueToStd(series_start);
				mango.EndDate = FromXMLValueToStd(series_end);
				mango.Image = FromXMLValueToStd(series_image);

				MangaInfo info;
				info.Mango = mango;
				info.MyId = FromXMLValueToInt(my_id);
				info.StartDate = FromXMLValueToStd(my_start_date);
				info.EndDate = FromXMLValueToStd(my_finish_date);
				info.Score = FromXMLValueToInt(my_score);
				info.ReadChapters = FromXMLValueToInt(my_read_chapters);
				info.ReadVolumes = FromXMLValueToInt(my_read_volumes);
				info.Status = (MangaUserStatus)FromXMLValueToInt(my_status);
				info.Rereading = FromXMLValueToInt(my_rereading);
				info.RereadChapters = FromXMLValueToInt(my_rereading_chap);
				info.LastUpdated = FromXMLValueToStd(my_last_updated);
				list.insert(MangaList::value_type(mango.Id, info));
			}
			MalManager::Get().AddMangaList(list);
			//LOG("Manga list file loaded successfully!")
			file.Close();
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

			pugi::xml_node  root = doc.append_child(kChiika);

			pugi::xml_node  MAL = root.append_child(kMangaList);

			ChiikaApi::MangaList list = MalManager::Get().GetMangaList();

			MangaList::iterator It;
			for (It = list.begin(); It != list.end(); ++It)
			{
				MangaInfo Mango = It->second;

				pugi::xml_node  manga = MAL.append_child(kManga);

				pugi::xml_node  series_mangadb_id = manga.append_child(kSeriesMangadbId);
				pugi::xml_node  series_title = manga.append_child(kSeriesTitle);
				pugi::xml_node  series_synonyms = manga.append_child(kSeriesSynonyms);
				pugi::xml_node  series_type = manga.append_child(kSeriesType);
				pugi::xml_node  series_chapters = manga.append_child(kSeriesChapters);
				pugi::xml_node  series_volumes = manga.append_child(kSeriesVolumes);
				pugi::xml_node  series_status = manga.append_child(kSeriesStatus);
				pugi::xml_node  series_start = manga.append_child(kSeriesStart);
				pugi::xml_node  series_end = manga.append_child(kSeriesEnd);
				pugi::xml_node  series_image = manga.append_child(kSeriesImage);
				pugi::xml_node  my_id = manga.append_child(kMyId); //What does this even mean?
				pugi::xml_node  my_read_chapters = manga.append_child(kMyReadChapters);
				pugi::xml_node  my_read_volumes = manga.append_child(kMyReadVolumes);
				pugi::xml_node  my_start_date = manga.append_child(kMyStartDate);
				pugi::xml_node  my_finish_date = manga.append_child(kMyFinishDate);
				pugi::xml_node  my_score = manga.append_child(kMyScore);
				pugi::xml_node  my_status = manga.append_child(kMyStatus);
				pugi::xml_node  my_rereading = manga.append_child(kMyRereading);
				pugi::xml_node  my_rereading_chap = manga.append_child(kMyRereadingChap);
				pugi::xml_node  my_last_updated = manga.append_child(kMyLastUpdated);

				SetXMLValue(series_mangadb_id, Mango.Mango.Id);
				SetXMLValue(series_title, Mango.Mango.Title.c_str());
				SetXMLValue(series_synonyms, Mango.Mango.English.c_str());
				SetXMLValue(series_type, Mango.Mango.Type);
				SetXMLValue(series_chapters, Mango.Mango.Chapters);
				SetXMLValue(series_volumes, Mango.Mango.Volumes);
				SetXMLValue(series_status, Mango.Mango.Status);
				SetXMLValue(series_start, Mango.Mango.StartDate.c_str());
				SetXMLValue(series_end, Mango.Mango.EndDate.c_str());
				SetXMLValue(series_image, Mango.Mango.Image.c_str());
				SetXMLValue(my_id, Mango.MyId);
				SetXMLValue(my_read_chapters, Mango.ReadChapters);
				SetXMLValue(my_read_volumes, Mango.ReadVolumes);
				SetXMLValue(my_start_date, Mango.StartDate.c_str());
				SetXMLValue(my_finish_date, Mango.EndDate.c_str());
				SetXMLValue(my_score, Mango.Score);
				SetXMLValue(my_status, Mango.Status);
				SetXMLValue(my_rereading, Mango.Rereading);
				SetXMLValue(my_rereading_chap, Mango.RereadChapters);
				SetXMLValue(my_last_updated, Mango.LastUpdated.c_str());


			}
			doc.save_file(dataFile.c_str());
			//LOG("Manga list file saved successfully!")
			file.Close();
		}
		else
		{
			
		}
	}
	//----------------------------------------------------------------------------
	UserInfoLoader::UserInfoLoader(ChiString path, ChiikaApi::UserInfo)
		: FileLoader(path, FileLoader::FileType::UserInfo)
	{
	}
	//----------------------------------------------------------------------------
	void UserInfoLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);

		if (file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  info = root.child(kUserInfo);
			pugi::xml_node  userName = info.child(kUserName);
			pugi::xml_node  pass = info.child(kPass);
			pugi::xml_node  watching = info.child(kWatching);
			pugi::xml_node  Completed = info.child(kCompleted);
			pugi::xml_node  OnHold = info.child(kOnHold);
			pugi::xml_node  Dropped = info.child(kDropped);
			pugi::xml_node  PlanToWatch = info.child(kPlanToWatch);
			pugi::xml_node  DaySpentAnime = info.child(kDaySpentAnime);

			pugi::xml_node  Reading = info.child(kReading);
			pugi::xml_node  Read = info.child(kRead);
			pugi::xml_node  MangaOnHold = info.child(kMangaOnHold);
			pugi::xml_node  MangaDropped = info.child(kMangaDropped);
			pugi::xml_node  PlanToRead = info.child(kPlanToRead);
			pugi::xml_node  DaySpentReading = info.child(kDaySpentReading);

			ChiikaApi::UserInfo ui;
			ui.UserName = FromXMLValueToStd(userName);
			ui.Pass = FromXMLValueToStd(pass);
			ui.AnimeStats.Watching = FromXMLValueToInt(watching);
			ui.AnimeStats.Completed = FromXMLValueToInt(Completed);
			ui.AnimeStats.OnHold = FromXMLValueToInt(OnHold);
			ui.AnimeStats.Dropped = FromXMLValueToInt(Dropped);
			ui.AnimeStats.PlanToWatch = FromXMLValueToInt(PlanToWatch);
			ui.AnimeStats.DaySpentAnime = FromXMLValueToFloat(DaySpentAnime);

			ui.MangaInfo.Reading = FromXMLValueToInt(Reading);
			ui.MangaInfo.Completed = FromXMLValueToInt(Read);
			ui.MangaInfo.OnHold = FromXMLValueToInt(MangaOnHold);
			ui.MangaInfo.Dropped = FromXMLValueToInt(MangaDropped);
			ui.MangaInfo.PlanToRead = FromXMLValueToInt(PlanToRead);
			ui.MangaInfo.DaysSpentReading = FromXMLValueToFloat(DaySpentReading);

			m_UserDetailedInfo = ui;
			//LOG("User info file loaded successfully!")
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

		if (file.Open())
		{
			pugi::xml_document doc;

			pugi::xml_node  root = doc.append_child(kChiika);
			pugi::xml_node  UserInfo = root.append_child(kUserInfo);
			pugi::xml_node  userName = UserInfo.append_child(kUserName);
			pugi::xml_node  pass = UserInfo.append_child(kPass);
			pugi::xml_node  watching = UserInfo.append_child(kWatching);
			pugi::xml_node  Completed = UserInfo.append_child(kCompleted);
			pugi::xml_node  OnHold = UserInfo.append_child(kOnHold);
			pugi::xml_node  Dropped = UserInfo.append_child(kDropped);
			pugi::xml_node  PlanToWatch = UserInfo.append_child(kPlanToWatch);
			pugi::xml_node  DaySpentAnime = UserInfo.append_child(kDaySpentAnime);

			pugi::xml_node  Reading = UserInfo.append_child(kReading);
			pugi::xml_node  Read = UserInfo.append_child(kRead);
			pugi::xml_node  MangaOnHold = UserInfo.append_child(kMangaOnHold);
			pugi::xml_node  MangaDropped = UserInfo.append_child(kMangaDropped);
			pugi::xml_node  PlanToRead = UserInfo.append_child(kPlanToRead);
			pugi::xml_node  DaySpentReading = UserInfo.append_child(kDaySpentReading);





			userName.text().set(m_UserDetailedInfo.UserName.c_str());
			pass.text().set(m_UserDetailedInfo.Pass.c_str());
			watching.text().set(m_UserDetailedInfo.AnimeStats.Watching);
			Completed.text().set(m_UserDetailedInfo.AnimeStats.Completed);
			OnHold.text().set(m_UserDetailedInfo.AnimeStats.OnHold);
			Dropped.text().set(m_UserDetailedInfo.AnimeStats.Dropped);
			PlanToWatch.text().set(m_UserDetailedInfo.AnimeStats.PlanToWatch);
			DaySpentAnime.text().set(m_UserDetailedInfo.AnimeStats.DaySpentAnime);

			Reading.text().set(m_UserDetailedInfo.MangaInfo.Reading);
			Read.text().set(m_UserDetailedInfo.MangaInfo.Completed);
			MangaOnHold.text().set(m_UserDetailedInfo.MangaInfo.OnHold);
			MangaDropped.text().set(m_UserDetailedInfo.MangaInfo.Dropped);
			PlanToRead.text().set(m_UserDetailedInfo.MangaInfo.PlanToRead);
			DaySpentReading.text().set(m_UserDetailedInfo.MangaInfo.DaysSpentReading);


			doc.save_file(dataFile.c_str());
			//LOG("User info file saved successfully!")
			file.Close();
		}
		else
		{
			
		}
	}
	//----------------------------------------------------------------------------
	UpdateListLoader::UpdateListLoader(ChiString path)
		: FileLoader(path, FileType::UpdateList)
	{

	}
	//----------------------------------------------------------------------------
	void UpdateListLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if (file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  updateList = root.child(kUpdateList);
#pragma region AnimeList
			ChiikaApi::UserAnimeList list;
			for (pugi::xml_node anime = updateList.child(kAnime); anime; anime = anime.next_sibling())
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

				Anime Anime;
				Anime.Id = FromXMLValueToInt(animeDbId);
				Anime.Title = FromXMLValueToStd(series_title);
				Anime.English = FromXMLValueToStd(series_synonyms);
				Anime.Type = (AnimeType)FromXMLValueToInt(series_type);
				Anime.EpisodeCount = FromXMLValueToInt(series_episodes);

				Anime.Status = (AnimeStatus)FromXMLValueToInt(series_status);
				Anime.StartDate = FromXMLValueToStd(series_start);
				Anime.EndDate = FromXMLValueToStd(series_end);
				Anime.Image = FromXMLValueToStd(series_image);

				UserAnimeEntry info;
				info.UpdateOperation = (CRUDOp)FromXMLValueToInt(Op);
				info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
				info.Anime = Anime;
				info.MyId = FromXMLValueToInt(my_id);
				info.StartDate = FromXMLValueToStd(my_start_date);
				info.EndDate = FromXMLValueToStd(my_finish_date);
				info.Score = FromXMLValueToInt(my_score);
				info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
				info.Rewatching = FromXMLValueToInt(my_rewatching);
				info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
				info.LastUpdated = FromXMLValueToStd(my_last_updated);
				list.insert(UserAnimeList::value_type(Anime.Id, info));
			}
			MalManager::Get().AddAnimeUpdateList(list);
#pragma endregion
#pragma region MangaList
			ChiikaApi::MangaList mangaList;
			for (pugi::xml_node manga = updateList.child(kManga); manga; manga = manga.next_sibling())
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


				Manga mango;
				mango.Id = FromXMLValueToInt(series_mangadb_id);
				mango.Title = FromXMLValueToStd(series_title);
				mango.English = FromXMLValueToStd(series_synonyms);
				mango.Type = (MangaType)FromXMLValueToInt(series_type);
				mango.Chapters = FromXMLValueToInt(series_chapters);
				mango.Volumes = FromXMLValueToInt(series_volumes);

				mango.Status = (MangaStatus)FromXMLValueToInt(series_status);
				mango.StartDate = FromXMLValueToStd(series_start);
				mango.EndDate = FromXMLValueToStd(series_end);
				mango.Image = FromXMLValueToStd(series_image);

				MangaInfo info;
				info.UpdateOperation = (CRUDOp)FromXMLValueToInt(Op);
				info.Mango = mango;
				info.MyId = FromXMLValueToInt(my_id);
				info.StartDate = FromXMLValueToStd(my_start_date);
				info.EndDate = FromXMLValueToStd(my_finish_date);
				info.Score = FromXMLValueToInt(my_score);
				info.Status = (MangaUserStatus)FromXMLValueToInt(my_status);
				info.Rereading = FromXMLValueToInt(my_rereading);
				info.RereadChapters = FromXMLValueToInt(my_rereading_chap);
				info.LastUpdated = FromXMLValueToStd(my_last_updated);
				mangaList.insert(MangaList::value_type(mango.Id, info));
			}
			MalManager::Get().AddMangaUpdateList(mangaList);
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


		if (file.Open())
		{
			pugi::xml_document doc;


			pugi::xml_node  root = doc.append_child(kChiika);
			pugi::xml_node  MAL = root.append_child(kUpdateList);

#pragma region Anime

			ChiikaApi::UserAnimeList list = MalManager::Get().GetAnimeUpdateList();
			UserAnimeList::iterator It;
			for (It = list.begin(); It != list.end(); ++It)
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

				SetXMLValue(animeDbId, Anime.Anime.Id);
				SetXMLValue(Op, Anime.UpdateOperation);
				SetXMLValue(series_title, Anime.Anime.Title.c_str());
				SetXMLValue(series_synonyms, Anime.Anime.English.c_str());
				SetXMLValue(series_type, Anime.Anime.Type);
				SetXMLValue(series_episodes, Anime.Anime.EpisodeCount);
				SetXMLValue(series_status, Anime.Anime.Status);
				SetXMLValue(series_start, Anime.Anime.StartDate.c_str());
				SetXMLValue(series_end, Anime.Anime.EndDate.c_str());
				SetXMLValue(series_image, Anime.Anime.Image.c_str());
				SetXMLValue(my_id, Anime.MyId);
				SetXMLValue(my_watched_episodes, Anime.WatchedEpisodes);
				SetXMLValue(my_start_date, Anime.StartDate.c_str());
				SetXMLValue(my_finish_date, Anime.EndDate.c_str());
				SetXMLValue(my_score, Anime.Score);
				SetXMLValue(my_status, Anime.Status);
				SetXMLValue(my_rewatching, Anime.Rewatching);
				SetXMLValue(my_rewatching_ep, Anime.RewatchingEp);
				SetXMLValue(my_last_updated, Anime.LastUpdated.c_str());

			}
#pragma endregion
#pragma region Manga
			ChiikaApi::MangaList mangaList = MalManager::Get().GetMangaUpdateList();

			MangaList::iterator ItManga;
			for (ItManga = mangaList.begin(); ItManga != mangaList.end(); ++ItManga)
			{
				MangaInfo Mango = ItManga->second;

				pugi::xml_node  manga = MAL.append_child(kManga);
				pugi::xml_node  Op = manga.append_child(kOperation);
				pugi::xml_node  series_mangadb_id = manga.append_child(kSeriesMangadbId);

				pugi::xml_node  series_title = manga.append_child(kSeriesTitle);
				pugi::xml_node  series_synonyms = manga.append_child(kSeriesSynonyms);
				pugi::xml_node  series_type = manga.append_child(kSeriesType);
				pugi::xml_node  series_chapters = manga.append_child(kSeriesChapters);
				pugi::xml_node  series_volumes = manga.append_child(kSeriesVolumes);
				pugi::xml_node  series_status = manga.append_child(kSeriesStatus);
				pugi::xml_node  series_start = manga.append_child(kSeriesStart);
				pugi::xml_node  series_end = manga.append_child(kSeriesEnd);
				pugi::xml_node  series_image = manga.append_child(kSeriesImage);
				pugi::xml_node  my_id = manga.append_child(kMyId); //What does this even mean?
				pugi::xml_node  my_read_chapters = manga.append_child(kMyReadChapters);
				pugi::xml_node  my_read_volumes = manga.append_child(kMyReadVolumes);
				pugi::xml_node  my_start_date = manga.append_child(kMyStartDate);
				pugi::xml_node  my_finish_date = manga.append_child(kMyFinishDate);
				pugi::xml_node  my_score = manga.append_child(kMyScore);
				pugi::xml_node  my_status = manga.append_child(kMyStatus);
				pugi::xml_node  my_rereading = manga.append_child(kMyRereading);
				pugi::xml_node  my_rereading_chap = manga.append_child(kMyRereadingChap);
				pugi::xml_node  my_last_updated = manga.append_child(kMyLastUpdated);

				SetXMLValue(series_mangadb_id, Mango.Mango.Id);
				SetXMLValue(Op, Mango.UpdateOperation);
				SetXMLValue(series_title, Mango.Mango.Title.c_str());
				SetXMLValue(series_synonyms, Mango.Mango.English.c_str());
				SetXMLValue(series_type, Mango.Mango.Type);
				SetXMLValue(series_chapters, Mango.Mango.Chapters);
				SetXMLValue(series_volumes, Mango.Mango.Volumes);
				SetXMLValue(series_status, Mango.Mango.Status);
				SetXMLValue(series_start, Mango.Mango.StartDate.c_str());
				SetXMLValue(series_end, Mango.Mango.EndDate.c_str());
				SetXMLValue(series_image, Mango.Mango.Image.c_str());
				SetXMLValue(my_id, Mango.MyId);
				SetXMLValue(my_read_chapters, Mango.ReadChapters);
				SetXMLValue(my_read_volumes, Mango.ReadVolumes);
				SetXMLValue(my_start_date, Mango.StartDate.c_str());
				SetXMLValue(my_finish_date, Mango.EndDate.c_str());
				SetXMLValue(my_score, Mango.Score);
				SetXMLValue(my_status, Mango.Status);
				SetXMLValue(my_rereading, Mango.Rereading);
				SetXMLValue(my_rereading_chap, Mango.RereadChapters);
				SetXMLValue(my_last_updated, Mango.LastUpdated.c_str());


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
		: FileLoader(path, FileType::AnimeDetails)
	{
	}
	//----------------------------------------------------------------------------
	void AnimeDetailsLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if (file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(kChiika);
			pugi::xml_node  animeDetails = root.child(kAnimeDetails);

			for (pugi::xml_node anime = animeDetails.child(kAnime); anime; anime = anime.next_sibling())
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
				for (pugi::xml_node tag = tags.child(kTag); tag; tag = tag.next_sibling())
				{
					vTags.push_back(tag.text().get());
				}

				StringVector vProducers;
				for (pugi::xml_node producer = producers.child(kProducer); producer; producer = producer.next_sibling())
				{
					vProducers.push_back(producer.text().get());
				}

				UserAnimeEntry findAnime = MalManager::Get().GetAnimeById(FromXMLValueToInt(Id));

				if (findAnime.Anime.Id != UnknownAnimeId)
				{
					ChiikaApi::AnimeDetails details = findAnime.Anime.ExtraDetails;
					details.Synopsis = syn.text().get();
					details.DurationPerEpisode = duration.text().get();
					details.Premiered = premiered.text().get();

					ChiikaApi::AnimeStatistics stats = findAnime.Anime.Statistics;
					stats.Popularity = atoi(popularity.text().get());
					stats.Ranked = atoi(ranked.text().get());
					stats.Score = atof(score.text().get());

					for (StringVectorSize i = 0; i < vTags.size(); i++)
					{
						ChiString tag = vTags[i];
						details.Tags.push_back(tag);
					}
					for (StringVectorSize i = 0; i < vProducers.size(); i++)
					{
						ChiString producer = vProducers[i];
						details.Producers.push_back(producer);
					}


					findAnime.Anime.ExtraDetails = details;
					findAnime.Anime.Statistics = stats;
					MalManager::Get().UpdateAnime(findAnime);
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

		if (file.Open())
		{
			pugi::xml_document doc;
			pugi::xml_node  root = doc.append_child(kChiika);
			pugi::xml_node  MAL = root.append_child(kAnimeDetails);

			ChiikaApi::UserAnimeList list = MalManager::Get().GetAnimeList();
			ChiikaApi::UserAnimeList::iterator It;
			for (It = list.begin(); It != list.end(); ++It)
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


				SetXMLValue(animeDbId, Anime.Anime.Id);
				SetXMLValue(syn, Details.Synopsis.c_str());
				SetXMLValue(premiered, Details.Premiered.c_str());
				SetXMLValue(duration, Details.DurationPerEpisode.c_str());

				SetXMLValue(score, Statistics.Score);
				SetXMLValue(ranked, Statistics.Ranked);
				SetXMLValue(popularity, Statistics.Popularity);

				for (StringVectorSize i = 0; i < Details.Producers.size(); i++)
				{
					ChiString p = Details.Producers[i];
					pugi::xml_node pNode = producers.append_child(kProducer);
					SetXMLValue(pNode, p.c_str());
				}


				for (StringVectorSize i = 0; i < Details.Tags.size(); i++)
				{
					ChiString tag = Details.Tags[i];
					pugi::xml_node  tagNode = tags.append_child(kTag);
					SetXMLValue(tagNode, tag.c_str());
				}
			}
			doc.save_file(dataFile.c_str());
			file.Close();
		}
	}
	//----------------------------------------------------------------------------
	SenpaiLoader::SenpaiLoader(ChiString path)
		: FileLoader(path, FileType::SenpaiJSON)
	{
	}
	//----------------------------------------------------------------------------
	void SenpaiLoader::Load()
	{
		ChiString dataFile = m_sPath;
		FileReader file(dataFile);


		if (file.Open())
		{
			Json::Value root;
			Json::Reader reader;
			ChiString fileData = file.Read();

			bool b = reader.parse(fileData, root);

			if (b)
			{
				//Root
				const Json::Value meta = root["meta"];
				ChiString season = (meta["season"].asString());
				ChiString start = (meta["start"].asString());

				const Json::Value tz = meta["tz"];
				Json::Value::const_iterator It = tz.begin();

				TimezoneMap list;
				for (It; It != tz.end(); It++)
				{
					Json::Value inner = *It;

					Timezone tz;
					tz.Name = (inner["abbr"].asString());
					tz.TimezoneIdentifier = (It.name());
					tz.Offset = (inner["offset"].asString());

					list.insert(TimezoneMap::value_type(tz.TimezoneIdentifier, tz));
				}
				SeasonManager::Get().SetTimezones(list);




				//Items
				const Json::Value items = root["items"];
				Json::Value::const_iterator itemsIt = items.begin();
				SenpaiData sd;

				for (itemsIt; itemsIt != items.end(); itemsIt++)
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
					Map<ChiString, Airdate>::type airdateList;

					ForEachOnStd(adIt, airdates)
					{
						Json::Value t = *adIt;

						Airdate ad;

						ChiString timezoneValue = (adIt.name());

						ad.TimeZone = list.find(timezoneValue)->second;
						ad.RdDate = JsToQ(t["rd_date"]);
						ad.RdTime = JsToQ(t["rd_time"]);
						ad.Weekday = t["weekday"].asInt();
						ad.RdWeekday = JsToQ(t["rd_weekday"]);

						airdateList.insert(std::make_pair(ad.TimeZone.TimezoneIdentifier, ad));
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

		m_UserDetailedInfo.UserName = "Chitanda";

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
		m_UserInfoLoader = new UserInfoLoader(m_sUserInfoPath, m_UserDetailedInfo);
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
	void LocalDataManager::SetUserNamePass(ChiString u, ChiString p)
	{
		m_UserDetailedInfo.UserName = u;
		m_UserDetailedInfo.Pass = p;

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
		m_UserDetailedInfo = i;
		m_UserInfoLoader->m_UserDetailedInfo = m_UserDetailedInfo;
		/*SaveUserInfo();*/
	}
	//----------------------------------------------------------------------------
	const UserInfo& LocalDataManager::GetUserInfo()
	{
		return m_UserDetailedInfo;
	}
	//----------------------------------------------------------------------------
	LocalDataManager* LocalDataManager::Get()
	{
		return gLdm;
	}
	//----------------------------------------------------------------------------
}
