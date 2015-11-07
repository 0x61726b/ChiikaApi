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
#include "Common/ExceptionManager.h"
#include "Seasons/SeasonManager.h"
#include "json\json.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	FileLoader::FileLoader(String path,FileType type)
	{
		m_sPath = path;
		m_eType = type;

		Create();
	}
	//----------------------------------------------------------------------------
	void FileLoader::Create()
	{
		//String dataFile = m_sPath;
		//std::ifstream t(dataFile);
		//std::string str((std::istreambuf_iterator<char>(t)),
		//	std::istreambuf_iterator<char>());
		//

		//if(m_eType != FileType::SenpaiJSON)
		//{
		//	if(file.open(QFile::WriteOnly))
		//	{
		//		pugi::xml_document doc;
		//		Node root = doc.append_child("Chiika");

		//		switch(m_eType)
		//		{
		//		case FileLoader::FileType::AnimeList:
		//		{
		//			root.append_child("MyAnimeList");
		//		}
		//		break;
		//		case FileLoader::FileType::UserInfo:
		//		{
		//			root.append_child("UserInfo");
		//		}
		//		break;
		//		case FileLoader::FileType::MangaList:
		//		{
		//			root.append_child("MangaList");
		//		}
		//		break;
		//		case FileLoader::FileType::UpdateList:
		//		{
		//			root.append_child("UpdateList");
		//		}
		//		break;
		//		case FileLoader::FileType::AnimeDetails:
		//		{
		//			root.append_child("AnimeDetails");
		//		}
		//		break;
		//		}
		//		doc.save_file(dataFile.toStdString().c_str());
		//	}
		//	else
		//	{
		//		CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't create file!","FileLoader::Create")
		//	}
		//}
		//else
		//{
		//	if(file.open(QFile::WriteOnly))
		//	{
		//		//
		//	}
		//}


	}
	//----------------------------------------------------------------------------
	AnimeFileLoader::AnimeFileLoader(String path)
		: FileLoader(path,FileLoader::FileType::AnimeList)
	{

	}
	//----------------------------------------------------------------------------
	void AnimeFileLoader::Load()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);


		//if(file.open(QFile::ReadOnly))
		//{
		//	pugi::xml_document doc;
		//	String fileData = file.readAll();
		//	doc.load(fileData.toStdString().c_str());

		//	Node root = doc.child("Chiika");
		//	Node myanimelist = root.child("MyAnimeList");

		//	ChiikaApi::AnimeList list;
		//	for(Node anime = myanimelist.child("anime");anime;anime = anime.next_sibling())
		//	{

		//		Node animeDbId = anime.child("series_animedb_id");
		//		Node series_title = anime.child("series_title");
		//		Node series_synonyms = anime.child("series_synonyms");
		//		Node series_type = anime.child("series_type");
		//		Node series_episodes = anime.child("series_episodes");
		//		Node series_status = anime.child("series_status");
		//		Node series_start = anime.child("series_start");
		//		Node series_end = anime.child("series_end");
		//		Node series_image = anime.child("series_image");
		//		Node my_id = anime.child("my_id"); //What does this even mean?
		//		Node my_watched_episodes = anime.child("my_watched_episodes");
		//		Node my_start_date = anime.child("my_start_date");
		//		Node my_finish_date = anime.child("my_finish_date");
		//		Node my_score = anime.child("my_score");
		//		Node my_status = anime.child("my_status");
		//		Node my_rewatching = anime.child("my_rewatching");
		//		Node my_rewatching_ep = anime.child("my_rewatching_ep");
		//		Node my_last_updated = anime.child("my_last_updated");
		//		//Node my_finish_date = anime.child("my_finish_date");

		//		Anime animu;
		//		animu.Id = FromXMLValueToInt(animeDbId);
		//		animu.Title = FromXMLValueToStd(series_title);
		//		animu.English = FromXMLValueToStd(series_synonyms);
		//		animu.Type = (AnimeType)FromXMLValueToInt(series_type);
		//		animu.EpisodeCount = FromXMLValueToInt(series_episodes);

		//		animu.Status = (AnimeStatus)FromXMLValueToInt(series_status);
		//		animu.StartDate = FromXMLValueToStd(series_start);
		//		animu.EndDate = FromXMLValueToStd(series_end);
		//		animu.Image = FromXMLValueToStd(series_image);

		//		AnimeInfo info;
		//		info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
		//		info.Animu = animu;
		//		info.MyId = FromXMLValueToInt(my_id);
		//		info.StartDate = FromXMLValueToStd(my_start_date);
		//		info.EndDate = FromXMLValueToStd(my_finish_date);
		//		info.Score = FromXMLValueToInt(my_score);
		//		info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
		//		info.Rewatching = FromXMLValueToInt(my_rewatching);
		//		info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
		//		info.LastUpdated = FromXMLValueToStd(my_last_updated);
		//		list.insert(AnimeList::value_type(animu.Id,info));
		//	}
		//	MalManager::Get().AddAnimeList(list);
		//	//LOG("Anime list loaded succesfully!")


		//	//LOG("Loading animelist took " + String::number(stopwatch.GetDuration()) +" micro seconds");

		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open AnimeList file!","AnimeFileLoader::Load")
		//}
	}
	//----------------------------------------------------------------------------
	void AnimeFileLoader::Save()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);

		//if(!file.exists())
		//	return;

		//if(file.open(QFile::WriteOnly))
		//{
		//	pugi::xml_document doc;

		//	Node root = doc.append_child("Chiika");
		//	Node MAL = root.append_child("MyAnimeList");

		//	ChiikaApi::AnimeList list = MalManager::Get().GetAnimeList();
		//	ChiikaApi::AnimeList::iterator It;
		//	for(It = list.begin(); It != list.end(); ++It)
		//	{
		//		AnimeInfo Animu = It->second;


		//		Node anime = MAL.append_child("anime");

		//		Node animeDbId = anime.append_child("series_animedb_id");
		//		Node series_title = anime.append_child("series_title");
		//		Node series_synonyms = anime.append_child("series_synonyms");
		//		Node series_type = anime.append_child("series_type");
		//		Node series_episodes = anime.append_child("series_episodes");
		//		Node series_status = anime.append_child("series_status");
		//		Node series_start = anime.append_child("series_start");
		//		Node series_end = anime.append_child("series_end");
		//		Node series_image = anime.append_child("series_image");
		//		Node my_id = anime.append_child("my_id"); //What does this even mean?
		//		Node my_watched_episodes = anime.append_child("my_watched_episodes");
		//		Node my_start_date = anime.append_child("my_start_date");
		//		Node my_finish_date = anime.append_child("my_finish_date");
		//		Node my_score = anime.append_child("my_score");
		//		Node my_status = anime.append_child("my_status");
		//		Node my_rewatching = anime.append_child("my_rewatching");
		//		Node my_rewatching_ep = anime.append_child("my_rewatching_ep");
		//		Node my_last_updated = anime.append_child("my_last_updated");

		//		SetXMLValue(animeDbId,Animu.Animu.Id);
		//		SetXMLValue(series_title,Animu.Animu.Title.c_str());
		//		SetXMLValue(series_synonyms,Animu.Animu.English.c_str());
		//		SetXMLValue(series_type,Animu.Animu.Type);
		//		SetXMLValue(series_episodes,Animu.Animu.EpisodeCount);
		//		SetXMLValue(series_status,Animu.Animu.Status);
		//		SetXMLValue(series_start,Animu.Animu.StartDate.c_str());
		//		SetXMLValue(series_end,Animu.Animu.EndDate.c_str());
		//		SetXMLValue(series_image,Animu.Animu.Image.c_str());
		//		SetXMLValue(my_id,Animu.MyId);
		//		SetXMLValue(my_watched_episodes,Animu.WatchedEpisodes);
		//		SetXMLValue(my_start_date,Animu.StartDate.c_str());
		//		SetXMLValue(my_finish_date,Animu.EndDate.c_str());
		//		SetXMLValue(my_score,Animu.Score);
		//		SetXMLValue(my_status,Animu.Status);
		//		SetXMLValue(my_rewatching,Animu.Rewatching);
		//		SetXMLValue(my_rewatching_ep,Animu.RewatchingEp);
		//		SetXMLValue(my_last_updated,Animu.LastUpdated.c_str());

		//	}
		//	doc.save_file(dataFile.toStdString().c_str());
		//	//LOG("Anime list saved succesfully!")

		//	//LOG("Saving animelist took " + String::number(st.GetDuration()) +" micro seconds");
		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open AnimeList file!","AnimeFileLoader::Save")
		//}
	}
	//----------------------------------------------------------------------------
	MangaFileLoader::MangaFileLoader(String path)
		: FileLoader(path,FileLoader::FileType::MangaList)
	{

	}
	//----------------------------------------------------------------------------
	void MangaFileLoader::Load()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);


		//if(file.open(QFile::ReadOnly))
		//{
		//	pugi::xml_document doc;
		//	String fileData = file.readAll();
		//	doc.load(fileData.toStdString().c_str());

		//	Node root = doc.child("Chiika");
		//	Node mymangalist = root.child("MangaList");

		//	ChiikaApi::MangaList list;
		//	for(Node manga = mymangalist.child("manga");manga;manga = manga.next_sibling())
		//	{

		//		Node series_mangadb_id = manga.child("series_mangadb_id");
		//		Node series_title = manga.child("series_title");
		//		Node series_synonyms = manga.child("series_synonyms");
		//		Node series_type = manga.child("series_type");
		//		Node series_chapters = manga.child("series_chapters");
		//		Node series_volumes = manga.child("series_volumes");
		//		Node series_status = manga.child("series_status");
		//		Node series_start = manga.child("series_start");
		//		Node series_end = manga.child("series_end");
		//		Node series_image = manga.child("series_image");
		//		Node my_id = manga.child("my_id"); //What does this even mean?
		//		Node my_read_chapters = manga.child("my_read_chapters");
		//		Node my_read_volumes = manga.child("my_read_volumes");
		//		Node my_start_date = manga.child("my_start_date");
		//		Node my_finish_date = manga.child("my_finish_date");
		//		Node my_score = manga.child("my_score");
		//		Node my_status = manga.child("my_status");
		//		Node my_rereading = manga.child("my_rereadingg");
		//		Node my_rereading_chap = manga.child("my_rereading_chap");
		//		Node my_last_updated = manga.child("my_last_updated");


		//		Manga mango;
		//		mango.Id = FromXMLValueToInt(series_mangadb_id);
		//		mango.Title = FromXMLValueToStd(series_title);
		//		mango.English = FromXMLValueToStd(series_synonyms);
		//		mango.Type = (MangaType)FromXMLValueToInt(series_type);
		//		mango.Chapters = FromXMLValueToInt(series_chapters);
		//		mango.Volumes = FromXMLValueToInt(series_volumes);

		//		mango.Status = (MangaStatus)FromXMLValueToInt(series_status);
		//		mango.StartDate = FromXMLValueToStd(series_start);
		//		mango.EndDate = FromXMLValueToStd(series_end);
		//		mango.Image = FromXMLValueToStd(series_image);

		//		MangaInfo info;
		//		info.Mango = mango;
		//		info.MyId = FromXMLValueToInt(my_id);
		//		info.StartDate = FromXMLValueToStd(my_start_date);
		//		info.EndDate = FromXMLValueToStd(my_finish_date);
		//		info.Score = FromXMLValueToInt(my_score);
		//		info.ReadChapters = FromXMLValueToInt(my_read_chapters);
		//		info.ReadVolumes = FromXMLValueToInt(my_read_volumes);
		//		info.Status = (MangaUserStatus)FromXMLValueToInt(my_status);
		//		info.Rereading = FromXMLValueToInt(my_rereading);
		//		info.RereadChapters = FromXMLValueToInt(my_rereading_chap);
		//		info.LastUpdated = FromXMLValueToStd(my_last_updated);
		//		list.insert(MangaList::value_type(mango.Id,info));
		//	}
		//	MalManager::Get().AddMangaList(list);
		//	//LOG("Manga list file loaded successfully!")
		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open manga file!","ConfigManager::LoadMyMangaList")
		//}
	}
	//----------------------------------------------------------------------------
	void MangaFileLoader::Save()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);

		//if(file.open(QFile::WriteOnly))
		//{
		//	pugi::xml_document doc;

		//	Node root = doc.append_child("Chiika");

		//	Node MAL = root.append_child("MangaList");

		//	ChiikaApi::MangaList list = MalManager::Get().GetMangaList();

		//	MangaList::iterator It;
		//	for(It = list.begin(); It != list.end(); ++It)
		//	{
		//		MangaInfo Mango = It->second;

		//		Node manga = MAL.append_child("manga");

		//		Node series_mangadb_id = manga.append_child("series_mangadb_id");
		//		Node series_title = manga.append_child("series_title");
		//		Node series_synonyms = manga.append_child("series_synonyms");
		//		Node series_type = manga.append_child("series_type");
		//		Node series_chapters = manga.append_child("series_chapters");
		//		Node series_volumes = manga.append_child("series_volumes");
		//		Node series_status = manga.append_child("series_status");
		//		Node series_start = manga.append_child("series_start");
		//		Node series_end = manga.append_child("series_end");
		//		Node series_image = manga.append_child("series_image");
		//		Node my_id = manga.append_child("my_id"); //What does this even mean?
		//		Node my_read_chapters = manga.append_child("my_read_chapters");
		//		Node my_read_volumes = manga.append_child("my_read_volumes");
		//		Node my_start_date = manga.append_child("my_start_date");
		//		Node my_finish_date = manga.append_child("my_finish_date");
		//		Node my_score = manga.append_child("my_score");
		//		Node my_status = manga.append_child("my_status");
		//		Node my_rereading = manga.append_child("my_rereadingg");
		//		Node my_rereading_chap = manga.append_child("my_rereading_chap");
		//		Node my_last_updated = manga.append_child("my_last_updated");

		//		SetXMLValue(series_mangadb_id,Mango.Mango.Id);
		//		SetXMLValue(series_title,Mango.Mango.Title.c_str());
		//		SetXMLValue(series_synonyms,Mango.Mango.English.c_str());
		//		SetXMLValue(series_type,Mango.Mango.Type);
		//		SetXMLValue(series_chapters,Mango.Mango.Chapters);
		//		SetXMLValue(series_volumes,Mango.Mango.Volumes);
		//		SetXMLValue(series_status,Mango.Mango.Status);
		//		SetXMLValue(series_start,Mango.Mango.StartDate.c_str());
		//		SetXMLValue(series_end,Mango.Mango.EndDate.c_str());
		//		SetXMLValue(series_image,Mango.Mango.Image.c_str());
		//		SetXMLValue(my_id,Mango.MyId);
		//		SetXMLValue(my_read_chapters,Mango.ReadChapters);
		//		SetXMLValue(my_read_volumes,Mango.ReadVolumes);
		//		SetXMLValue(my_start_date,Mango.StartDate.c_str());
		//		SetXMLValue(my_finish_date,Mango.EndDate.c_str());
		//		SetXMLValue(my_score,Mango.Score);
		//		SetXMLValue(my_status,Mango.Status);
		//		SetXMLValue(my_rereading,Mango.Rereading);
		//		SetXMLValue(my_rereading_chap,Mango.RereadChapters);
		//		SetXMLValue(my_last_updated,Mango.LastUpdated.c_str());


		//	}
		//	doc.save_file(dataFile.toStdString().c_str());
		//	//LOG("Manga list file saved successfully!")
		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open manga file!","ConfigManager::SaveMangaList")
		//}
	}
	//----------------------------------------------------------------------------
	UserInfoLoader::UserInfoLoader(String path,ChiikaApi::UserInfo)
		: FileLoader(path,FileLoader::FileType::UserInfo)
	{
	}
	//----------------------------------------------------------------------------
	void UserInfoLoader::Load()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);

		//if(file.open(QFile::ReadOnly))
		//{
		//	pugi::xml_document doc;
		//	String fileData = file.readAll();
		//	doc.load(fileData.toStdString().c_str());

		//	Node root = doc.child("Chiika");
		//	Node info  = root.child("UserInfo");
		//	Node userName = info.child("UserName");
		//	Node pass = info.child("Pass");
		//	Node watching = info.child("Watching");
		//	Node Completed = info.child("Completed");
		//	Node OnHold = info.child("OnHold");
		//	Node Dropped = info.child("Dropped");
		//	Node PlanToWatch = info.child("PlanToWatch");
		//	Node DaySpentAnime = info.child("DaySpentAnime");

		//	Node Reading = info.child("Reading");
		//	Node Read = info.child("Read");
		//	Node MangaOnHold = info.child("MangaOnHold");
		//	Node MangaDropped = info.child("MangaDropped");
		//	Node PlanToRead = info.child("PlanToRead");
		//	Node DaySpentReading = info.child("DaySpentReading");

		//	ChiikaApi::UserInfo ui;
		//	ui.UserName = FromXMLValueToStd(userName);
		//	ui.Pass = FromXMLValueToStd(pass);
		//	ui.AnimeInfo.Watching = FromXMLValueToInt(watching);
		//	ui.AnimeInfo.Completed = FromXMLValueToInt(Completed);
		//	ui.AnimeInfo.OnHold = FromXMLValueToInt(OnHold);
		//	ui.AnimeInfo.Dropped = FromXMLValueToInt(Dropped);
		//	ui.AnimeInfo.PlanToWatch = FromXMLValueToInt(PlanToWatch);
		//	ui.AnimeInfo.DaySpentAnime = FromXMLValueToFloat(DaySpentAnime);

		//	ui.MangaInfo.Reading = FromXMLValueToInt(Reading);
		//	ui.MangaInfo.Completed= FromXMLValueToInt(Read);
		//	ui.MangaInfo.OnHold = FromXMLValueToInt(MangaOnHold);
		//	ui.MangaInfo.Dropped = FromXMLValueToInt(MangaDropped);
		//	ui.MangaInfo.PlanToRead= FromXMLValueToInt(PlanToRead);
		//	ui.MangaInfo.DaysSpentReading= FromXMLValueToFloat(DaySpentReading);

		//	m_UserDetailedInfo = ui;
		//	//LOG("User info file loaded successfully!")

		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open user info file!","ConfigManager::SaveUserInfo")
		//}
	}
	//----------------------------------------------------------------------------
	void UserInfoLoader::Save()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);

		//if(file.open(QFile::WriteOnly))
		//{
		//	pugi::xml_document doc;

		//	Node root = doc.append_child("Chiika");
		//	Node UserInfo  = root.append_child("UserInfo");
		//	Node userName = UserInfo.append_child("UserName");
		//	Node pass = UserInfo.append_child("Pass");
		//	Node watching = UserInfo.append_child("Watching");
		//	Node Completed = UserInfo.append_child("Completed");
		//	Node OnHold = UserInfo.append_child("OnHold");
		//	Node Dropped = UserInfo.append_child("Dropped");
		//	Node PlanToWatch = UserInfo.append_child("PlanToWatch");
		//	Node DaySpentAnime = UserInfo.append_child("DaySpentAnime");

		//	Node Reading = UserInfo.append_child("Reading");
		//	Node Read = UserInfo.append_child("Read");
		//	Node MangaOnHold = UserInfo.append_child("MangaOnHold");
		//	Node MangaDropped = UserInfo.append_child("MangaDropped");
		//	Node PlanToRead = UserInfo.append_child("PlanToRead");
		//	Node DaySpentReading = UserInfo.append_child("DaySpentReading");





		//	userName.text().set(m_UserDetailedInfo.UserName.c_str());
		//	pass.text().set(m_UserDetailedInfo.Pass.c_str());
		//	watching.text().set(m_UserDetailedInfo.AnimeInfo.Watching);
		//	Completed.text().set(m_UserDetailedInfo.AnimeInfo.Completed);
		//	OnHold.text().set(m_UserDetailedInfo.AnimeInfo.OnHold);
		//	Dropped.text().set(m_UserDetailedInfo.AnimeInfo.Dropped);
		//	PlanToWatch.text().set(m_UserDetailedInfo.AnimeInfo.PlanToWatch);
		//	DaySpentAnime.text().set(m_UserDetailedInfo.AnimeInfo.DaySpentAnime);

		//	Reading.text().set(m_UserDetailedInfo.MangaInfo.Reading);
		//	Read.text().set(m_UserDetailedInfo.MangaInfo.Completed);
		//	MangaOnHold.text().set(m_UserDetailedInfo.MangaInfo.OnHold);
		//	MangaDropped.text().set(m_UserDetailedInfo.MangaInfo.Dropped);
		//	PlanToRead.text().set(m_UserDetailedInfo.MangaInfo.PlanToRead);
		//	DaySpentReading.text().set(m_UserDetailedInfo.MangaInfo.DaysSpentReading);


		//	doc.save_file(dataFile.toStdString().c_str());
		//	//LOG("User info file saved successfully!")
		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open user info file!","ConfigManager::SaveUserInfo")
		//}
	}
	//----------------------------------------------------------------------------
	UpdateListLoader::UpdateListLoader(String path)
		: FileLoader(path,FileType::UpdateList)
	{

	}
	//----------------------------------------------------------------------------
	void UpdateListLoader::Load()
	{
		//		String dataFile = m_sPath;
		//		QFile file(dataFile);
		//
		//
		//		if(file.open(QFile::ReadOnly))
		//		{
		//			pugi::xml_document doc;
		//			String fileData = file.readAll();
		//			doc.load(fileData.toStdString().c_str());
		//
		//			Node root = doc.child("Chiika");
		//			Node updateList = root.child("UpdateList");
		//#pragma region AnimeList
		//			ChiikaApi::AnimeList list;
		//			for(Node anime = updateList.child("anime");anime;anime = anime.next_sibling())
		//			{
		//
		//				Node animeDbId = anime.child("series_animedb_id");
		//				Node Op = anime.child("Operation");
		//				Node series_title = anime.child("series_title");
		//				Node series_synonyms = anime.child("series_synonyms");
		//				Node series_type = anime.child("series_type");
		//				Node series_episodes = anime.child("series_episodes");
		//				Node series_status = anime.child("series_status");
		//				Node series_start = anime.child("series_start");
		//				Node series_end = anime.child("series_end");
		//				Node series_image = anime.child("series_image");
		//				Node my_id = anime.child("my_id"); //What does this even mean?
		//				Node my_watched_episodes = anime.child("my_watched_episodes");
		//				Node my_start_date = anime.child("my_start_date");
		//				Node my_finish_date = anime.child("my_finish_date");
		//				Node my_score = anime.child("my_score");
		//				Node my_status = anime.child("my_status");
		//				Node my_rewatching = anime.child("my_rewatching");
		//				Node my_rewatching_ep = anime.child("my_rewatching_ep");
		//				Node my_last_updated = anime.child("my_last_updated");
		//				//Node my_finish_date = anime.child("my_finish_date");
		//
		//				Anime animu;
		//				animu.Id = FromXMLValueToInt(animeDbId);
		//				animu.Title = FromXMLValueToStd(series_title);
		//				animu.English = FromXMLValueToStd(series_synonyms);
		//				animu.Type = (AnimeType)FromXMLValueToInt(series_type);
		//				animu.EpisodeCount = FromXMLValueToInt(series_episodes);
		//
		//				animu.Status = (AnimeStatus)FromXMLValueToInt(series_status);
		//				animu.StartDate = FromXMLValueToStd(series_start);
		//				animu.EndDate = FromXMLValueToStd(series_end);
		//				animu.Image = FromXMLValueToStd(series_image);
		//
		//				AnimeInfo info;
		//				info.UpdateOperation = (CRUDOp)FromXMLValueToInt(Op);
		//				info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
		//				info.Animu = animu;
		//				info.MyId = FromXMLValueToInt(my_id);
		//				info.StartDate = FromXMLValueToStd(my_start_date);
		//				info.EndDate = FromXMLValueToStd(my_finish_date);
		//				info.Score = FromXMLValueToInt(my_score);
		//				info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
		//				info.Rewatching = FromXMLValueToInt(my_rewatching);
		//				info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
		//				info.LastUpdated = FromXMLValueToStd(my_last_updated);
		//				list.insert(AnimeList::value_type(animu.Id,info));
		//			}
		//			MalManager::Get().AddAnimeUpdateList(list);
		//#pragma endregion
		//#pragma region MangaList
		//			ChiikaApi::MangaList mangaList;
		//			for(Node manga = updateList.child("manga");manga;manga = manga.next_sibling())
		//			{
		//
		//				Node series_mangadb_id = manga.child("series_mangadb_id");
		//				Node Op = manga.child("Operation");
		//				Node series_title = manga.child("series_title");
		//				Node series_synonyms = manga.child("series_synonyms");
		//				Node series_type = manga.child("series_type");
		//				Node series_chapters = manga.child("series_chapters");
		//				Node series_volumes = manga.child("series_volumes");
		//				Node series_status = manga.child("series_status");
		//				Node series_start = manga.child("series_start");
		//				Node series_end = manga.child("series_end");
		//				Node series_image = manga.child("series_image");
		//				Node my_id = manga.child("my_id"); //What does this even mean?
		//				Node my_read_chapters = manga.child("my_read_chapters");
		//				Node my_read_volumes = manga.child("my_read_volumes");
		//				Node my_start_date = manga.child("my_start_date");
		//				Node my_finish_date = manga.child("my_finish_date");
		//				Node my_score = manga.child("my_score");
		//				Node my_status = manga.child("my_status");
		//				Node my_rereading = manga.child("my_rereadingg");
		//				Node my_rereading_chap = manga.child("my_rereading_chap");
		//				Node my_last_updated = manga.child("my_last_updated");
		//
		//
		//				Manga mango;
		//				mango.Id = FromXMLValueToInt(series_mangadb_id);
		//				mango.Title = FromXMLValueToStd(series_title);
		//				mango.English = FromXMLValueToStd(series_synonyms);
		//				mango.Type = (MangaType)FromXMLValueToInt(series_type);
		//				mango.Chapters = FromXMLValueToInt(series_chapters);
		//				mango.Volumes = FromXMLValueToInt(series_volumes);
		//
		//				mango.Status = (MangaStatus)FromXMLValueToInt(series_status);
		//				mango.StartDate = FromXMLValueToStd(series_start);
		//				mango.EndDate = FromXMLValueToStd(series_end);
		//				mango.Image = FromXMLValueToStd(series_image);
		//
		//				MangaInfo info;
		//				info.UpdateOperation = (CRUDOp)FromXMLValueToInt(Op);
		//				info.Mango = mango;
		//				info.MyId = FromXMLValueToInt(my_id);
		//				info.StartDate = FromXMLValueToStd(my_start_date);
		//				info.EndDate = FromXMLValueToStd(my_finish_date);
		//				info.Score = FromXMLValueToInt(my_score);
		//				info.Status = (MangaUserStatus)FromXMLValueToInt(my_status);
		//				info.Rereading = FromXMLValueToInt(my_rereading);
		//				info.RereadChapters = FromXMLValueToInt(my_rereading_chap);
		//				info.LastUpdated = FromXMLValueToStd(my_last_updated);
		//				mangaList.insert(MangaList::value_type(mango.Id,info));
		//			}
		//			MalManager::Get().AddMangaUpdateList(mangaList);
		//			//LOG("Update list file loaded successfully!")
		//#pragma endregion
		//		}
		//		else
		//		{
		//			CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open update file!","ConfigManager::LoadUpdateList")
		//		}
	}
	//----------------------------------------------------------------------------
	void UpdateListLoader::Save()
	{
		//		String dataFile = m_sPath;
		//		QFile file(dataFile);
		//
		//		if(!file.exists())
		//			return;
		//
		//		if(file.open(QFile::WriteOnly))
		//		{
		//			pugi::xml_document doc;
		//
		//
		//			String fileData = file.readAll();
		//			doc.load(fileData.toStdString().c_str());
		//
		//			Node root = doc.append_child("Chiika");
		//			Node MAL = root.append_child("UpdateList");
		//
		//#pragma region Anime
		//
		//			ChiikaApi::AnimeList list = MalManager::Get().GetAnimeUpdateList();
		//			AnimeList::iterator It;
		//			for(It = list.begin(); It != list.end(); ++It)
		//			{
		//				AnimeInfo Animu = It->second;
		//
		//
		//				Node anime = MAL.append_child("anime");
		//				Node Op = anime.append_child("Operation");
		//				Node animeDbId = anime.append_child("series_animedb_id");
		//				Node series_title = anime.append_child("series_title");
		//				Node series_synonyms = anime.append_child("series_synonyms");
		//				Node series_type = anime.append_child("series_type");
		//				Node series_episodes = anime.append_child("series_episodes");
		//				Node series_status = anime.append_child("series_status");
		//				Node series_start = anime.append_child("series_start");
		//				Node series_end = anime.append_child("series_end");
		//				Node series_image = anime.append_child("series_image");
		//				Node my_id = anime.append_child("my_id"); //What does this even mean?
		//				Node my_watched_episodes = anime.append_child("my_watched_episodes");
		//				Node my_start_date = anime.append_child("my_start_date");
		//				Node my_finish_date = anime.append_child("my_finish_date");
		//				Node my_score = anime.append_child("my_score");
		//				Node my_status = anime.append_child("my_status");
		//				Node my_rewatching = anime.append_child("my_rewatching");
		//				Node my_rewatching_ep = anime.append_child("my_rewatching_ep");
		//				Node my_last_updated = anime.append_child("my_last_updated");
		//
		//				SetXMLValue(animeDbId,Animu.Animu.Id);
		//				SetXMLValue(Op,Animu.UpdateOperation);
		//				SetXMLValue(series_title,Animu.Animu.Title.c_str());
		//				SetXMLValue(series_synonyms,Animu.Animu.English.c_str());
		//				SetXMLValue(series_type,Animu.Animu.Type);
		//				SetXMLValue(series_episodes,Animu.Animu.EpisodeCount);
		//				SetXMLValue(series_status,Animu.Animu.Status);
		//				SetXMLValue(series_start,Animu.Animu.StartDate.c_str());
		//				SetXMLValue(series_end,Animu.Animu.EndDate.c_str());
		//				SetXMLValue(series_image,Animu.Animu.Image.c_str());
		//				SetXMLValue(my_id,Animu.MyId);
		//				SetXMLValue(my_watched_episodes,Animu.WatchedEpisodes);
		//				SetXMLValue(my_start_date,Animu.StartDate.c_str());
		//				SetXMLValue(my_finish_date,Animu.EndDate.c_str());
		//				SetXMLValue(my_score,Animu.Score);
		//				SetXMLValue(my_status,Animu.Status);
		//				SetXMLValue(my_rewatching,Animu.Rewatching);
		//				SetXMLValue(my_rewatching_ep,Animu.RewatchingEp);
		//				SetXMLValue(my_last_updated,Animu.LastUpdated.c_str());
		//
		//			}
		//#pragma endregion
		//#pragma region Manga
		//			ChiikaApi::MangaList mangaList = MalManager::Get().GetMangaUpdateList();
		//
		//			MangaList::iterator ItManga;
		//			for(ItManga = mangaList.begin(); ItManga != mangaList.end(); ++ItManga)
		//			{
		//				MangaInfo Mango = ItManga->second;
		//
		//				Node manga = MAL.append_child("manga");
		//				Node Op = manga.append_child("Operation");
		//				Node series_mangadb_id = manga.append_child("series_mangadb_id");
		//
		//				Node series_title = manga.append_child("series_title");
		//				Node series_synonyms = manga.append_child("series_synonyms");
		//				Node series_type = manga.append_child("series_type");
		//				Node series_chapters = manga.append_child("series_chapters");
		//				Node series_volumes = manga.append_child("series_volumes");
		//				Node series_status = manga.append_child("series_status");
		//				Node series_start = manga.append_child("series_start");
		//				Node series_end = manga.append_child("series_end");
		//				Node series_image = manga.append_child("series_image");
		//				Node my_id = manga.append_child("my_id"); //What does this even mean?
		//				Node my_read_chapters = manga.append_child("my_read_chapters");
		//				Node my_read_volumes = manga.append_child("my_read_volumes");
		//				Node my_start_date = manga.append_child("my_start_date");
		//				Node my_finish_date = manga.append_child("my_finish_date");
		//				Node my_score = manga.append_child("my_score");
		//				Node my_status = manga.append_child("my_status");
		//				Node my_rereading = manga.append_child("my_rereadingg");
		//				Node my_rereading_chap = manga.append_child("my_rereading_chap");
		//				Node my_last_updated = manga.append_child("my_last_updated");
		//
		//				SetXMLValue(series_mangadb_id,Mango.Mango.Id);
		//				SetXMLValue(Op,Mango.UpdateOperation);
		//				SetXMLValue(series_title,Mango.Mango.Title.c_str());
		//				SetXMLValue(series_synonyms,Mango.Mango.English.c_str());
		//				SetXMLValue(series_type,Mango.Mango.Type);
		//				SetXMLValue(series_chapters,Mango.Mango.Chapters);
		//				SetXMLValue(series_volumes,Mango.Mango.Volumes);
		//				SetXMLValue(series_status,Mango.Mango.Status);
		//				SetXMLValue(series_start,Mango.Mango.StartDate.c_str());
		//				SetXMLValue(series_end,Mango.Mango.EndDate.c_str());
		//				SetXMLValue(series_image,Mango.Mango.Image.c_str());
		//				SetXMLValue(my_id,Mango.MyId);
		//				SetXMLValue(my_read_chapters,Mango.ReadChapters);
		//				SetXMLValue(my_read_volumes,Mango.ReadVolumes);
		//				SetXMLValue(my_start_date,Mango.StartDate.c_str());
		//				SetXMLValue(my_finish_date,Mango.EndDate.c_str());
		//				SetXMLValue(my_score,Mango.Score);
		//				SetXMLValue(my_status,Mango.Status);
		//				SetXMLValue(my_rereading,Mango.Rereading);
		//				SetXMLValue(my_rereading_chap,Mango.RereadChapters);
		//				SetXMLValue(my_last_updated,Mango.LastUpdated.c_str());
		//
		//
		//			}
		//#pragma endregion
		//			doc.save_file(dataFile.toStdString().c_str());
		//			//LOG("Update list file saved successfully!")
		//		}
		//		else
		//		{
		//			CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open update file!","ConfigManager::LoadUpdateList")
		//		}
	}
	//----------------------------------------------------------------------------
	AnimeDetailsLoader::AnimeDetailsLoader(String path)
		: FileLoader(path,FileType::AnimeDetails)
	{
	}
	//----------------------------------------------------------------------------
	void AnimeDetailsLoader::Load()
	{
		/*String dataFile = m_sPath;
		QFile file(dataFile);


		if(file.open(QFile::ReadOnly))
		{
		pugi::xml_document doc;
		String fileData = file.readAll();
		doc.load(fileData.toStdString().c_str());

		Node root = doc.child("Chiika");
		Node animeDetails = root.child("AnimeDetails");

		for(Node anime = animeDetails.child("anime");anime;anime = anime.next_sibling())
		{
		Node Id = anime.child("Id");
		Node syn = anime.child("Synopsis");
		Node tags = anime.child("Tags");
		Node premiered = anime.child("Premiered");
		Node producers = anime.child("Producers");
		Node duration = anime.child("DurationPerEpisode");

		Node score = anime.child("Score");
		Node ranked = anime.child("Ranked");
		Node popularity = anime.child("Popularity");

		std::vector<String> vTags;
		for(Node tag = tags.child("Tag");tag;tag= tag.next_sibling())
		{
		vTags.push_back(tag.text().get());
		}

		std::vector<String> vProducers;
		for(Node producer = producers.child("Producer");producer;producer= producer.next_sibling())
		{
		vProducers.push_back(producer.text().get());
		}

		AnimeInfo findAnime = MalManager::Get().GetAnimeById(FromXMLValueToInt(Id));

		if(findAnime.Animu.Id != 0)
		{
		ChiikaApi::AnimeDetails details = findAnime.Animu.ExtraDetails;
		details.Synopsis = syn.text().get();
		details.DurationPerEpisode = String::fromStdString(duration.text().get());
		details.Premiered = premiered.text().get();

		ChiikaApi::AnimeStatistics stats = findAnime.Animu.Statistics;
		stats.Popularity = String::fromStdString(popularity.text().get()).toInt();
		stats.Ranked = String::fromStdString(ranked.text().get()).toInt();
		stats.Score = String::fromStdString(score.text().get()).toFloat();

		for(int i=0; i < vTags.size(); i++)
		{
		String tag = vTags[i];
		details.Tags.push_back(tag);
		}
		for(int i=0; i < vProducers.size(); i++)
		{
		String producer = vProducers[i];
		details.Producers.push_back(producer);
		}


		findAnime.Animu.ExtraDetails = details;
		findAnime.Animu.Statistics = stats;
		MalManager::Get().UpdateAnime(findAnime);
		}

		}
		}
		file.close();*/
	}
	//----------------------------------------------------------------------------
	void AnimeDetailsLoader::Save()
	{
		/*String dataFile = m_sPath;
		QFile file(dataFile);

		if(file.open(QFile::WriteOnly))
		{
		pugi::xml_document doc;
		Node root = doc.append_child("Chiika");
		Node MAL = root.append_child("AnimeDetails");

		ChiikaApi::AnimeList list = MalManager::Get().GetAnimeList();
		ChiikaApi::AnimeList::iterator It;
		for(It = list.begin(); It != list.end(); ++It)
		{
		AnimeInfo Animu = It->second;
		ChiikaApi::AnimeDetails Details = It->second.Animu.ExtraDetails;
		ChiikaApi::AnimeStatistics Statistics = It->second.Animu.Statistics;

		Node anime = MAL.append_child("anime");
		Node animeDbId = anime.append_child("Id");
		Node syn = anime.append_child("Synopsis");
		Node tags = anime.append_child("Tags");
		Node premiered = anime.append_child("Premiered");
		Node producers = anime.append_child("Producers");
		Node duration = anime.append_child("DurationPerEpisode");

		Node score = anime.append_child("Score");
		Node ranked = anime.append_child("Ranked");
		Node popularity = anime.append_child("Popularity");


		SetXMLValue(animeDbId,Animu.Animu.Id);
		SetXMLValue(syn,Details.Synopsis.toStdString().c_str());
		SetXMLValue(premiered,Details.Premiered.toStdString().c_str());
		SetXMLValue(duration,Details.DurationPerEpisode.toStdString().c_str());

		SetXMLValue(score,Statistics.Score);
		SetXMLValue(ranked,Statistics.Ranked);
		SetXMLValue(popularity,Statistics.Popularity);

		for(int i=0; i < Details.Producers.size(); i++)
		{
		String p = Details.Producers[i];
		Node pNode = producers.append_child("Producer");
		SetXMLValue(pNode,p.toStdString().c_str());
		}


		for(int i=0; i < Details.Tags.size(); i++)
		{
		String tag = Details.Tags[i];
		Node tagNode = tags.append_child("Tag");
		SetXMLValue(tagNode,tag.toStdString().c_str());
		}
		}
		doc.save_file(dataFile.toStdString().c_str());
		}*/
	}
	//----------------------------------------------------------------------------
	SenpaiLoader::SenpaiLoader(String path)
		: FileLoader(path,FileType::SenpaiJSON)
	{
	}
	//----------------------------------------------------------------------------
	void SenpaiLoader::Load()
	{
		//String dataFile = m_sPath;
		//QFile file(dataFile);


		//if(file.open(QFile::ReadOnly))
		//{
		//	Json::Value root;
		//	Json::Reader reader;
		//	String fileData = file.readAll();

		//	bool b = reader.parse(fileData.toStdString(),root);

		//	if(b)
		//	{
		//		//Root
		//		const Json::Value meta = root["meta"];
		//		String season = Q_(meta["season"].asString());
		//		String start = Q_(meta["start"].asString());
		//		float startU = (meta["start_u"].asFloat());

		//		const Json::Value tz = meta["tz"];
		//		Json::Value::const_iterator It = tz.begin();

		//		TimezoneMap list;
		//		for(It;It != tz.end(); It++)
		//		{
		//			Json::Value inner = *It;

		//			Timezone tz;
		//			tz.Name = Q_(inner["abbr"].asString());
		//			tz.TimezoneIdentifier = Q_(It.name());
		//			tz.Offset = Q_(inner["offset"].asString());

		//			list.insert(TimezoneMap::value_type(tz.TimezoneIdentifier,tz));
		//		}
		//		SeasonManager::Get().SetTimezones(list);




		//		//Items
		//		const Json::Value items = root["items"];
		//		Json::Value::const_iterator itemsIt = items.begin();
		//		SenpaiData sd;

		//		for(itemsIt;itemsIt != items.end();itemsIt++)
		//		{
		//			Json::Value v = *itemsIt;

		//			SenpaiItem si;
		//			si.Name = JsToQ(v["name"]);
		//			si.MalID = JsToQ(v["MALID"]).toInt();
		//			si.IsSequel = (v["isSequel"].asBool());
		//			si.Simulcast = JsToQ(v["simulcast"]);
		//			si.AirdateStr = JsToQ(v["airdate"]);
		//			si.Fansub = JsToQ(v["fansub"]);
		//			si.SimulcastDelay = v["simulcast_delay"].asInt();
		//			si.Type = JsToQ(v["type"]);
		//			si.MissingAirdate = v["missingAirdate"].asBool();
		//			si.MissingAirtime = v["missingAirtime"].asBool();
		//			si.AirDateOriginal = JsToQ(v["airdate_orig"]);


		//			const Json::Value airdates = v["airdates"];

		//			Json::Value::const_iterator adIt = airdates.begin();
		//			Map<String,Airdate>::type airdateList;

		//			ForEachOnStd(adIt,airdates)
		//			{
		//				Json::Value t = *adIt;

		//				Airdate ad;

		//				String timezoneValue = String::fromStdString(adIt.name());

		//				ad.TimeZone = list.find(timezoneValue)->second;
		//				ad.RdDate = JsToQ(t["rd_date"]);
		//				ad.RdTime = JsToQ(t["rd_time"]);
		//				ad.Weekday = t["weekday"].asInt();
		//				ad.RdWeekday = JsToQ(t["rd_weekday"]);

		//				airdateList.insert(std::make_pair(ad.TimeZone.TimezoneIdentifier,ad));
		//			}
		//			si.Airdates = airdateList;
		//			sd.push_back(si);
		//		}
		//		SeasonManager::Get().SetSenpaiData(sd);
		//	}
		//	else
		//	{
		//	}


		//}
	}
	//----------------------------------------------------------------------------
	void SenpaiLoader::Save()
	{
	}
	//----------------------------------------------------------------------------
	LocalDataManager::LocalDataManager()
	{
		m_sAnimeListFilePath = AppSettings::Get().GetStringOption(LIBRARY_ANIME_LIST_PATH);
		m_sMangaListFilePath = AppSettings::Get().GetStringOption(LIBRARY_MANGA_LIST_PATH);
		m_sUserInfoPath = AppSettings::Get().GetStringOption(LIBRARY_USER_INFO_PATH);
		m_sUpdateListPath = AppSettings::Get().GetStringOption(LIBRARY_UPDATE_LIST_PATH);
		m_sAnimeDetailsPath = AppSettings::Get().GetStringOption(LIBRARY_ANIME_DETAILS_PATH);
		m_sSenpaiPath = AppSettings::Get().GetStringOption(LIBRARY_SENPAI_PATH);;


		m_AnimeLoader = new AnimeFileLoader(m_sAnimeListFilePath);
		m_MangaLoader = new MangaFileLoader(m_sMangaListFilePath);
		m_UserInfoLoader = new UserInfoLoader(m_sUserInfoPath,m_UserDetailedInfo);
		m_UpdateListLoader = new UpdateListLoader(m_sUpdateListPath);
		m_AnimeDetailsLoader = new AnimeDetailsLoader(m_sAnimeDetailsPath);
		m_SenpaiLoader = new SenpaiLoader(m_sSenpaiPath);

		LoadUserInfo();
		LoadAnimeList();
		LoadMangaList();
		LoadUpdateList();
		LoadSenpaiData();

	}
	//----------------------------------------------------------------------------
	LocalDataManager::~LocalDataManager()
	{
		delete m_AnimeLoader;
		delete m_MangaLoader;
		delete m_UserInfoLoader;
		delete m_UpdateListLoader;
		delete m_AnimeDetailsLoader;
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
	void LocalDataManager::SetUserNamePass(String u,String p)
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
	void LocalDataManager::SetUserInfo(UserInfo i)
	{
		/*CHIKA_AUTO_MUTEX_LOCK*/
		m_UserDetailedInfo = i;
		m_UserInfoLoader->m_UserDetailedInfo = m_UserDetailedInfo;
		SaveUserInfo();
	}
	//----------------------------------------------------------------------------
	const UserInfo& LocalDataManager::GetUserInfo()
	{
		return m_UserDetailedInfo;
	}
	//----------------------------------------------------------------------------
	template<> LocalDataManager* Singleton<LocalDataManager>::msSingleton = 0;
	LocalDataManager& LocalDataManager::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
	LocalDataManager* LocalDataManager::GetPtr(void)
	{
		return msSingleton;
	}
	//----------------------------------------------------------------------------
}
