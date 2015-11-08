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
#include "ParsingManager.h"
#include "Request/MalManager.h"
#include "RequestManager.h"
#include "Common/ExceptionManager.h"
#include "Database/LocalDataManager.h"
#include "Settings/Settings.h"
#include "json\json.h"
#include "Logging\ChiString.h"
#include "Logging\FileHelper.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	template<> ParsingManager* Singleton<ParsingManager>::msSingleton = 0;
	ParsingManager& ParsingManager::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
	ParsingManager* ParsingManager::GetPtr(void)
	{
		return msSingleton;
	}
	//----------------------------------------------------------------------------
	void ParsingManager::Parse(ThreadedRequest* request)
	{
		ChiString RequestName = request->Name;

		if(RequestName == "Verify")
		{
			bool result = ParseVerifyRequest(request->m_sBuffer);

			if(result)
				request->m_Result.Code = RequestCodes::VERIFY_SUCCESS;
			else
				request->m_Result.Code = RequestCodes::VERIFY_ERROR;
		}
		if(RequestName == "SearchAnime")
		{
			AnimeList result = ParseSearchResult(request->m_sBuffer);

			request->m_Result.m_AnimeList = result;
			request->m_Result.Code = RequestCodes::SEARCH_SUCCESS;
		}
		if(RequestName == "GetAnimeList")
		{
			AnimeList result = ParseGetUserAnimeList(request->m_sBuffer);

			request->m_Result.m_AnimeList = result;
			request->m_Result.Code = RequestCodes::SEARCH_SUCCESS;
		}
		if(RequestName == "GetMangaList")
		{
			MangaList result = ParseGetUserMangaList(request->m_sBuffer);

			request->m_Result.m_MangaList = result;
			request->m_Result.Code = RequestCodes::SEARCH_SUCCESS;
		}
		if(RequestName == "AnilistAuth")
		{
			ChiString accessToken = ParseAnilistAuth(request->m_sBuffer);
			request->m_Result.AnilistAuthCode = accessToken;
		}
		if(RequestName == "AnilistSearchAnime")
		{
			ParseAnilistSearchAnime(request->m_sBuffer);
		}
		if(RequestName == "AnimeScrape")
		{
			AnimeInfo result = ParseAnimeScrape(request->m_sBuffer,request->m_Result.AnimeResult.Animu.Id);
			request->m_Result.AnimeResult = result;
		}
		if(RequestName == "UserPageScrape")
		{
			ParseUserPage(request->m_sBuffer);
		}
		if(RequestName == "SenpaiMoeData")
		{
			ParseSenpai(request->m_sBuffer);
		}
	}
	//----------------------------------------------------------------------------
	void ParsingManager::ParseAnilistSearchAnime(const ChiString& data)
	{
		Json::Value root;
		Json::Reader reader;
		reader.parse(data,root);


		//qDebug() << root.toStyledChiString().c_str();
	}
	//----------------------------------------------------------------------------
	ChiString ParsingManager::ParseAnilistAuth(const ChiString& data)
	{
		Json::Value root;
		Json::Reader reader;
		reader.parse(data,root);


		return root["access_token"].asString().c_str();
	}
	//----------------------------------------------------------------------------
	bool ParsingManager::ParseVerifyRequest(const ChiString& Data)
	{
		pugi::xml_document doc;
		try
		{
			doc.load(Data.c_str());
		}
		catch(ChiikaApi::Exception&)
		{
			CHIKA_EXCEPTION(Exception::ERR_XML_PARSING,"Can't parse XML data!","ParsingManager::ParseVerifyRequest")
		}
		pugi::xml_node  user = doc.child("user");
		ChiString userName = user.child("username").text().get();
		ChiString id = user.child("id").text().get();

		UserInfo ui = LocalDataManager::Get().GetUserInfo();

		if(ui.UserName == userName)
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------
	AnimeList ParsingManager::ParseSearchResult(const ChiString& data)
	{
		pugi::xml_document doc;
		try
		{
			doc.load(data.c_str());
		}
		catch(ChiikaApi::Exception& ex)
		{
			CHIKA_EXCEPTION(Exception::ERR_XML_PARSING,"Can't parse XML data!","ParsingManager::ParseSearchResult")
		}


		pugi::xml_node  anime = doc.child("anime");
		AnimeList list;
		if(!anime.empty())
		{
			for(pugi::xml_node entry = anime.first_child();entry;entry = entry.next_sibling())
			{
				Anime animu;
				pugi::xml_node  Id = entry.child("id");
				pugi::xml_node  title = entry.child("title");
				pugi::xml_node  english = entry.child("english");
				pugi::xml_node  synonyms = entry.child("synonyms");
				pugi::xml_node  episodes = entry.child("episodes");
				pugi::xml_node  status = entry.child("status");
				pugi::xml_node  start_date = entry.child("start_date");
				pugi::xml_node  end_date = entry.child("end_date");
				pugi::xml_node  synopsis = entry.child("synopsis");
				pugi::xml_node  image = entry.child("image");
				animu.Id = FromXMLValueToInt(Id);
				animu.Title = FromXMLValueToStd(title);
				animu.English = FromXMLValueToStd(english);
				//animu.Title = FromXMLValueToStd(synonyms); Add this later
				animu.EpisodeCount = FromXMLValueToInt(episodes);
				animu.Status = (AnimeStatus)FromXMLValueToInt(status);
				animu.StartDate = FromXMLValueToStd(start_date);
				animu.EndDate = FromXMLValueToStd(end_date);
				animu.Image = FromXMLValueToStd(image);
				animu.ExtraDetails.Synopsis = synopsis.text().get();
				AnimeInfo ai;
				ai.Animu = animu;
				list.insert(AnimeList::value_type(animu.Id,ai));
			}
			return list;
		}
		return list;
	}
	//----------------------------------------------------------------------------
	AnimeList ParsingManager::ParseGetUserAnimeList(const ChiString& data)
	{
		pugi::xml_document doc;
		try
		{
			doc.load(data.c_str());
		}
		catch(ChiikaApi::Exception& ex)
		{
			CHIKA_EXCEPTION(Exception::ERR_XML_PARSING,"Can't parse XML data!","ParsingManager::ParseGetUserAnimeList")
		}

		pugi::xml_node  myanimelist = doc.child("myanimelist");
		pugi::xml_node  user = myanimelist.child("myinfo");
		pugi::xml_node  userWatching = user.child("user_watching");
		pugi::xml_node  user_completed = user.child("user_completed");
		pugi::xml_node  user_onhold = user.child("user_onhold");
		pugi::xml_node  user_dropped = user.child("user_dropped");
		pugi::xml_node  user_plantowatch = user.child("user_plantowatch");
		pugi::xml_node  user_days_spent_watching = user.child("user_days_spent_watching");

		ChiString userName = user.child("user_name").text().get();
		ChiString id = user.child("user_id").text().get();

		UserInfo ui = LocalDataManager::Get().GetUserInfo();
		ui.UserName = ToStd(userName);
		ui.AnimeInfo.Watching = FromXMLValueToInt(userWatching);
		ui.AnimeInfo.Completed = FromXMLValueToInt(user_completed);
		ui.AnimeInfo.OnHold = FromXMLValueToInt(user_onhold);
		ui.AnimeInfo.Dropped = FromXMLValueToInt(user_dropped);
		ui.AnimeInfo.PlanToWatch = FromXMLValueToInt(user_plantowatch);
		ui.AnimeInfo.DaySpentAnime = FromXMLValueToFloat(user_days_spent_watching);

		LocalDataManager::Get().SetUserInfo(ui);

		//doc.print(std::cout);

		int animeCount = 0;
		AnimeList list;
		for(pugi::xml_node anime = myanimelist.child("anime");anime;anime = anime.next_sibling())
		{
			pugi::xml_node  animeDbId = anime.child("series_animedb_id");
			pugi::xml_node  series_title = anime.child("series_title");
			pugi::xml_node  series_synonyms = anime.child("series_synonyms");
			pugi::xml_node  series_type = anime.child("series_type");
			pugi::xml_node  series_episodes = anime.child("series_episodes");
			pugi::xml_node  series_status = anime.child("series_status");
			pugi::xml_node  series_start = anime.child("series_start");
			pugi::xml_node  series_end = anime.child("series_end");
			pugi::xml_node  series_image = anime.child("series_image");
			pugi::xml_node  my_id = anime.child("my_id"); //What does this even mean?
			pugi::xml_node  my_watched_episodes = anime.child("my_watched_episodes");
			pugi::xml_node  my_start_date = anime.child("my_start_date");
			pugi::xml_node  my_finish_date = anime.child("my_finish_date");
			pugi::xml_node  my_score = anime.child("my_score");
			pugi::xml_node  my_status = anime.child("my_status");
			pugi::xml_node  my_rewatching = anime.child("my_rewatching");
			pugi::xml_node  my_rewatching_ep = anime.child("my_rewatching_ep");
			pugi::xml_node  my_last_updated = anime.child("my_last_updated");
			//pugi::xml_node  my_finish_date = anime.child("my_finish_date");

			Anime animu;
			animu.Id = FromXMLValueToInt(animeDbId);
			animu.Title = FromXMLValueToStd(series_title);
			animu.English = FromXMLValueToStd(series_synonyms);
			animu.Type = (AnimeType)FromXMLValueToInt(series_type);
			animu.EpisodeCount = FromXMLValueToInt(series_episodes);

			animu.Status = (AnimeStatus)FromXMLValueToInt(series_status);
			animu.StartDate = FromXMLValueToStd(series_start);
			animu.EndDate = FromXMLValueToStd(series_end);
			animu.Image = FromXMLValueToStd(series_image);

			AnimeInfo info;
			info.Animu = animu;
			info.MyId = FromXMLValueToInt(my_id);
			info.WatchedEpisodes = FromXMLValueToInt(my_watched_episodes);
			info.StartDate = FromXMLValueToStd(my_start_date);
			info.EndDate = FromXMLValueToStd(my_finish_date);
			info.Score = FromXMLValueToInt(my_score);
			info.Status = (AnimeUserStatus)FromXMLValueToInt(my_status);
			info.Rewatching = FromXMLValueToInt(my_rewatching);
			info.RewatchingEp = FromXMLValueToInt(my_rewatching_ep);
			info.LastUpdated = FromXMLValueToStd(my_last_updated);

			list.insert(AnimeList::value_type(animu.Id,info));
			animeCount++;
		}


		return list;
	}
	//----------------------------------------------------------------------------
	MangaList ParsingManager::ParseGetUserMangaList(const ChiString& data)
	{

		pugi::xml_document doc;

		try
		{
			doc.load(data.c_str());
		}
		catch(ChiikaApi::Exception& ex)
		{
			CHIKA_EXCEPTION(Exception::ERR_XML_PARSING,"Can't parse XML data!","ParsingManager::ParseGetUserMangaList")
		}

		pugi::xml_node  myanimelist = doc.child("myanimelist");

		pugi::xml_node  user = myanimelist.child("myinfo");
		pugi::xml_node  user_reading = user.child("user_reading");
		pugi::xml_node  user_completed = user.child("user_completed");
		pugi::xml_node  user_onhold = user.child("user_onhold");
		pugi::xml_node  user_dropped = user.child("user_dropped");
		pugi::xml_node  user_plantowatch = user.child("user_plantoread");
		pugi::xml_node  user_days_spent_watching = user.child("user_days_spent_watching");

		ChiString userName = user.child("user_name").text().get();
		ChiString id = user.child("user_id").text().get();

		UserInfo ui = LocalDataManager::Get().GetUserInfo();

		ui.MangaInfo.Reading = FromXMLValueToInt(user_reading);
		ui.MangaInfo.Completed= FromXMLValueToInt(user_completed);
		ui.MangaInfo.OnHold = FromXMLValueToInt(user_onhold);
		ui.MangaInfo.Dropped = FromXMLValueToInt(user_dropped);
		ui.MangaInfo.PlanToRead= FromXMLValueToInt(user_plantowatch);
		ui.MangaInfo.DaysSpentReading= FromXMLValueToFloat(user_days_spent_watching);

		LocalDataManager::Get().SetUserInfo(ui);

		MangaList list;

		for(pugi::xml_node manga = myanimelist.child("manga");manga;manga = manga.next_sibling())
		{
			pugi::xml_node  series_mangadb_id = manga.child("series_mangadb_id");
			pugi::xml_node  series_title = manga.child("series_title");
			pugi::xml_node  series_synonyms = manga.child("series_synonyms");
			pugi::xml_node  series_type = manga.child("series_type");
			pugi::xml_node  series_chapters = manga.child("series_chapters");
			pugi::xml_node  series_volumes = manga.child("series_volumes");
			pugi::xml_node  series_status = manga.child("series_status");
			pugi::xml_node  series_start = manga.child("series_start");
			pugi::xml_node  series_end = manga.child("series_end");
			pugi::xml_node  series_image = manga.child("series_image");
			pugi::xml_node  my_id = manga.child("my_id"); //What does this even mean?
			pugi::xml_node  my_read_chapters = manga.child("my_read_chapters");
			pugi::xml_node  my_read_volumes = manga.child("my_read_volumes");
			pugi::xml_node  my_start_date = manga.child("my_start_date");
			pugi::xml_node  my_finish_date = manga.child("my_finish_date");
			pugi::xml_node  my_score = manga.child("my_score");
			pugi::xml_node  my_status = manga.child("my_status");
			pugi::xml_node  my_rereading = manga.child("my_rereadingg");
			pugi::xml_node  my_rereading_chap = manga.child("my_rereading_chap");
			pugi::xml_node  my_last_updated = manga.child("my_last_updated");


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
			info.ReadChapters = FromXMLValueToInt(my_read_chapters);
			info.ReadVolumes = FromXMLValueToInt(my_read_volumes);
			info.Score = FromXMLValueToInt(my_score);
			info.Status = (MangaUserStatus)FromXMLValueToInt(my_status);
			info.Rereading = FromXMLValueToInt(my_rereading);
			info.RereadChapters = FromXMLValueToInt(my_rereading_chap);
			info.LastUpdated = FromXMLValueToStd(my_last_updated);

			list.insert(MangaList::value_type(mango.Id,info));

		}
		return list;
	}
	//----------------------------------------------------------------------------
	const AnimeInfo& ParsingManager::ParseCRUDAnime(const ChiString& data)
	{
		return AnimeInfo();
	}
	//----------------------------------------------------------------------------
	AnimeInfo ParsingManager::ParseAnimeScrape(const ChiString& data,int Id)
	{
		//Oh The Good Ol' html parsing
		//What a time to be alive

		ChiString qData = data;
		ChiStringUtil strUtil;
		//---------------------------------------------
		//---------------------------------------------
		//-----------------GENRE-----------------------
		//---------------------------------------------
		//---------------------------------------------

		int genresStart = qData.find_first_of("Genres:</span>");
		int genresEnd = qData.find_first_of("</div>",genresStart);


		ChiString genres = strUtil.GetMiddle(qData,genresStart + 14,genresEnd - genresStart);
		std::vector<ChiString> genreList = GetItemsSeperatedBy(genres,",");

		//---------------------------------------------
		//---------------------------------------------
		//-----------------Duration--------------------
		//---------------------------------------------
		//---------------------------------------------
		ChiString search = "Duration:</span>";
		ChiString end = "</div>";
		ChiString duration = ParseWebPage(qData,search,end);
		//---------------------------------------------
		//---------------------------------------------
		//-----------------Premiered-------------------
		//---------------------------------------------
		//---------------------------------------------
		search = "Premiered:</span>";
		end = "</div>";
		ChiString premiered = ParseWebPage(qData,search,end);
		premiered = RemoveLink(premiered);
		//---------------------------------------------
		//---------------------------------------------
		//-----------------Producers-------------------
		//---------------------------------------------
		//---------------------------------------------
		search = "Producers:</span>";
		end = "</div>";
		ChiString producers = ParseWebPage(qData,search,end);
		std::vector<ChiString> producersList = GetItemsSeperatedBy(producers,",");
		//---------------------------------------------
		//---------------------------------------------
		//-----------------Score-----------------------
		//---------------------------------------------
		//---------------------------------------------
		search = "Score:</span>";
		end = "</div>";
		ChiString score = ParseWebPage(qData,search,end);
		score = RemoveHTMLElements(score);
		//---------------------------------------------
		//---------------------------------------------
		//-----------------Ranked----------------------
		//---------------------------------------------
		//---------------------------------------------
		search = "Ranked:</span>";
		end = "</div>";
		ChiString ranked = ParseWebPage(qData,search,end);
		ranked = RemoveHTMLElements(ranked);
		ranked = strUtil.GetMiddle(ranked,1,ranked.size() -1); //Remove the # for int purposes
		//---------------------------------------------
		//---------------------------------------------
		//-----------------Popularity------------------
		//---------------------------------------------
		//---------------------------------------------
		search = "Popularity:</span>";
		end = "</div>";
		ChiString popularity = ParseWebPage(qData,search,end);
		popularity = strUtil.GetMiddle(popularity,1,popularity.size() -1); //Remove the # for int purposes

		//---------------------------------------------
		//---------------------------------------------
		//----------WILL STEAL MOAR LATER--------------
		//---------------------------------------------
		//---------------------------------------------

		//---------------------------------------------
		//---------------------------------------------
		//---------------SYNOPSIS----------------------
		//---------------------------------------------
		//---------------------------------------------
		search = "Synopsis</h2><span itemprop=\"description\">";
		end = "<br />";
		ChiString synopsis = ParseWebPage(qData,search,end);

		AnimeInfo animeFromList = MalManager::Get().GetAnimeById(Id);
		AnimeDetails details = animeFromList.Animu.ExtraDetails;
		AnimeStatistics statistics = animeFromList.Animu.Statistics;
		if(ANIME_IN_LIST(animeFromList))
		{
			details.DurationPerEpisode = duration;
			details.Premiered = premiered;
			details.Producers = producersList;
			details.Tags = genreList;
			details.Synopsis = synopsis;
			//
			statistics.Popularity = atoi(popularity.c_str());
			statistics.Ranked = atoi(ranked.c_str());
			statistics.Score = atof(score.c_str());

			animeFromList.Animu.ExtraDetails = details;
			animeFromList.Animu.Statistics = statistics;
			MalManager::Get().UpdateAnime(animeFromList);
		}



		return animeFromList;
	}
	//----------------------------------------------------------------------------
	void ParsingManager::ParseUserPage(const ChiString& data)
	{
		ChiStringUtil strUtil;
		ChiString searchStart = "profile_leftcell";
		ChiString searchEnd = "</div>";
		ChiString imageUrl = ParseWebPage(data,searchStart,searchEnd);

		imageUrl = ParseWebPage(imageUrl,"<img src=\"","\">");
		imageUrl = strUtil.Trim(imageUrl);

		UserInfo ui = LocalDataManager::Get().GetUserInfo();
		ui.ImageLink = imageUrl;
		LocalDataManager::Get().SetUserInfo(ui);
	}
	//----------------------------------------------------------------------------
	void ParsingManager::ParseSenpai(const ChiString& data)
	{
		Json::Value root;
		Json::Reader reader;


		bool b = reader.parse(data,root);

		if(b)
		{
			FileWriter f(AppSettings::Get().GetChiStringOption(LIBRARY_SENPAI_PATH));

			if(f.Open())
			{
				f.Write(ToStd(data));
				f.Close();
			}
		}
		LocalDataManager::Get().LoadSenpaiData();
	}
	//----------------------------------------------------------------------------
	ChiString ParsingManager::ParseWebPage(ChiString data,ChiString searchStart,ChiString searchEnd)
	{
		ChiStringUtil strUtil;
		int start = data.find(searchStart);
		int end = data.find(searchEnd,start);

		ChiString first = strUtil.GetMiddle(data,start,end-start);
		first = strUtil.GetMiddle(first,searchStart.size(),first.size() - searchStart.size());
		first = strUtil.Trim(first);
		return first;
	}
	//----------------------------------------------------------------------------
	ChiString ParsingManager::RemoveHTMLElements(ChiString data)
	{
		ChiStringUtil strUtil;
		if(data.find("<span") != -1)
		{
			int start = data.find("<span");
			int descEnd= data.find("\">");
			int end = data.find("</span>",start);
			data = strUtil.GetMiddle(data,descEnd,end - descEnd);
			data = strUtil.GetMiddle(data,2,data.size() -1);
			return strUtil.Trim(data);
		}
		if(data.find("<sup") != -1)
		{
			int start = data.find("<sup>");
			int end = data.find("</sup>",start);
			end = end + 6;
			ChiString sup = strUtil.GetMiddle(data,start,end-start);
			/*data = data.replace(sup,"");*/
			return strUtil.Trim(data);
		}
		return "";
	}
	//----------------------------------------------------------------------------
	bool ParsingManager::CheckValidLink(ChiString s)
	{
		/*QRegExp r("/^http?:\/\/(?:[a-z\-]+\.)+[a-z]{2,6}(?:\/[^\/#?]+)+\.(?:jpe?g|gif|png)$/");

		if(s.contains(r))
		{
		return true;
		}
		else
		{
		return false;
		}*/
		return false;
	}
	//----------------------------------------------------------------------------
	ChiString ParsingManager::RemoveLink(ChiString data)
	{
		ChiStringUtil strUtil;
		if(data.find("<a href") != -1)
		{
			int linkStart = data.find("<a href");
			int linkDescEnd = data.find("\">");
			int linkEnd = data.find("</a>",linkStart);
			data = strUtil.GetMiddle(data,linkDescEnd,linkEnd - linkDescEnd);
			data = strUtil.GetMiddle(data,2,data.size() -1);
			data = strUtil.Trim(data);
			return data;
		}
		return data;
	}
	//----------------------------------------------------------------------------
	std::vector<ChiString> ParsingManager::GetItemsSeperatedBy(ChiString data,ChiString seperator)
	{
		int commaCount = 0;

		ChiStringUtil strUtil;
		strUtil.Trim(data);
		data.insert(data.size()-1,seperator);
		int start = 0,end = 0;

		std::vector<ChiString> genreList;

		for(int i=0; i < data.size(); i++)
		{
			if(data.at(i) == (char)seperator.c_str())
			{
				commaCount++; //tag count

				end = i;

				ChiString g = strUtil.GetMiddle(data,start+1,end-start);

				ChiString seperatorLeft = ">";
				ChiString seperatorRight = "<";

				int sStart = g.find(seperatorLeft);
				int sEnd = g.find(seperatorRight,sStart);

				ChiString genre = strUtil.GetMiddle(g,sStart+1,sEnd - sStart - 1);
				genreList.push_back(genre);
				start = end;
			}
		}
		return genreList;
	}
}
//----------------------------------------------------------------------------
