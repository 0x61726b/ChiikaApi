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
//	authors: arkenthera
//	Date:	 24.1.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "MyAnimelistUtility.h"

#include "boost\regex.hpp"
#include "boost\algorithm\string\replace.hpp"

namespace ChiikaApi
{
	MyAnimelistUserPageParseResult MyAnimelistUtility::ParseUserPage(const std::string& webPage)
	{
		MyAnimelistUserPageParseResult result;
		boost::smatch what;
		boost::match_flag_type flags = boost::match_default;
		std::string::const_iterator start,end;
		//---------------------------------------
		//			
		//				User Image
		//				NOTE: Not required url is cdn... + userID.jpg,just honing muh regex skillz
		//---------------------------------------
		std::string find = "(<div class=\"user-image mb8\">)\\s*(<img src=\"([^\"']+))";

		boost::regex expr(find);
		start = webPage.begin();
		end = webPage.end();

		while(boost::regex_search(start,end,what,expr,flags))
		{
			std::string image = std::string(what[3]);

			result.ProfileImageLink = image;

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		flags = boost::match_default;



		//---------------------------------------
		//			
		//				Friends
		//		
		//---------------------------------------
		std::string innerRegex = "(<a\\s+(?:[^>]*?\\s+)?href=\"([^\"]*)\")";
		std::string outerRegex = "(?<=<div class=\"user-friends pt4 pb12\">)(\\s*).*?(\\s*)(?=</div>)";

		expr = boost::regex(outerRegex);

		start = webPage.begin();
		end = webPage.end();


		std::string outer = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			outer= std::string(what[0]);

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		flags = boost::match_default;

		start = outer.begin();
		end = outer.end();

		expr = boost::regex(innerRegex);


		std::vector<std::string> links;
		while(boost::regex_search(start,end,what,expr,flags))
		{
			links.push_back(std::string(what[2]));


			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		result.FriendProfiles = links;

		return result;
	}

	AnimeMisc MyAnimelistUtility::ParseAnimePage(const std::string& data)
	{
		//
		//Parses MyAnimeList page of an anime such as myanimelist.net/anime/20047/Sakura_Trick
		//


		AnimeMisc result;
		//---------------------------------------
		//			
		//				Studio
		//		
		//---------------------------------------
		std::string outerRegex = "(?<=Studios:</span>)(\\s*)(?s)(.+?)(?=\\s*</div>)";

		boost::smatch what;
		boost::match_flag_type flags = boost::match_default;
		std::string::const_iterator start,end;

		boost::regex expr(outerRegex);

		start = data.begin();
		end = data.end();


		std::string outer = "";
		while(boost::regex_search(start,end,what,expr,flags))
		{
			outer = what[2];



			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		flags = boost::match_default;

		std::string innerRegexStep1 = "(<a\\s+(?:[^>]*?\\s+)?href=\"([^\"]*)\")";
		std::string innerRegexStep2 = "(?:title=\".+?\">)(.+?)(?=</a>)";

		std::string inner1 = "",inner2 = "";


		start = outer.begin();
		end = outer.end();

		expr = boost::regex(innerRegexStep1);

		std::vector<std::string> studioLinks;
		while(boost::regex_search(start,end,what,expr,flags))
		{
			std::string o3 = what[2];

			studioLinks.push_back(o3);


			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		start = outer.begin();
		end = outer.end();

		expr = boost::regex(innerRegexStep2);
		flags = boost::match_default;

		std::vector<std::string> studioNames;
		while(boost::regex_search(start,end,what,expr,flags))
		{
			std::string o2 = what[1];
			studioNames.push_back(o2);


			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		std::map<std::string,std::string> studioLinkMap;
		for(int i=0; i < studioNames.size(); ++i)
		{
			Studio s;
			s.SetKeyValue(kStudioName,studioNames[i]);
			
			std::string studiolink = studioLinks[i];

			int lastSep = studiolink.find_last_of("/")+1;
			std::string studioId = studiolink.substr(lastSep,studiolink.size() - lastSep);

			s.SetKeyValue(kStudioId,studioId);
			result.Studios.push_back(s);
			studioLinkMap.insert(std::make_pair(studioNames[i],studioLinks[i]));
		}
		
		//---------------------------------------
		//			
		//				Genres
		//		
		//---------------------------------------
		std::string genresRegexStep1 = "(?<=Genres:</span>)(\\s*)(?s)(.+?)(?=\\s*</div)";
		std::string genresRegexStep2 = "(?<=title=\")(.+?)(?=\")";

		expr = boost::regex(genresRegexStep1);
		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		std::string step1Capture = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			step1Capture = what[2];


			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		flags = boost::match_default;
		start = step1Capture.begin();
		end = step1Capture.end();

		expr = boost::regex(genresRegexStep2);
		while(boost::regex_search(start,end,what,expr,flags))
		{
			std::string genre = what[0];

			Genre g;
			g.SetKeyValue(kGenre,genre);
			result.Genres.push_back(g);

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		

		//---------------------------------------
		//			
		//				Source
		//		
		//---------------------------------------

		std::string sourceRegex = "(?<=Source:</span>)(\\s*)(?s)(.+?)(?=\\s*</div>)";
		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(sourceRegex);

		std::string source = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			source= what[2];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		result.SetKeyValue(kSource,source);

		//---------------------------------------
		//			
		//				Broadcast Time
		//		
		//---------------------------------------

		std::string broadcastRegex = "(?<=Broadcast:</span>)(\\s*)(?s)(.+?)(?=\\s*</div>)";
		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(broadcastRegex);

		std::string broadcast = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			broadcast = what[2];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		result.SetKeyValue(kBroadcastTime,broadcast);

		//---------------------------------------
		//			
		//				Duration
		//		
		//---------------------------------------

		std::string durationRegex = "(?<=Duration:</span>)(\\s*)(?s)(.+?)(?=\\s*</div>)";
		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(durationRegex);

		std::string duration = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			duration = what[2];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		result.SetKeyValue(kDuration,duration);

		//---------------------------------------
		//			
		//				Score
		//		
		//---------------------------------------
		std::string scoreRegex = "(?<=Score:</span>)(\\s*)(?s)(.+?)(?=\\s*</div>)";
		std::string scoreRegexStep2 = "(?<=\"ratingValue\">)(?s)(.+?)(?=</span>)";

		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(scoreRegex);

		std::string scoreStep1Capture = "";
		std::string score = "";

		if(boost::regex_search(start,end,what,expr,flags))
		{
			scoreStep1Capture = what[2];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		flags = boost::match_default;
		start = scoreStep1Capture.begin();
		end = scoreStep1Capture.end();

		expr = boost::regex(scoreRegexStep2);

		if(boost::regex_search(start,end,what,expr,flags))
		{
			score = what[0];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		result.SetKeyValue(kAvgScore,score);

		//---------------------------------------
		//			
		//				Ranked
		//		
		//---------------------------------------

		std::string rankedRegex = "(?<=Ranked:</span>)(\\s*)(?s)(.+?)(?=\\s*<sup>)";
		std::string ranked = "";
		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(rankedRegex);

		if(boost::regex_search(start,end,what,expr,flags))
		{
			ranked = what[2];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		result.SetKeyValue(kRanked,ranked);


		//---------------------------------------
		//			
		//				Aired
		//		
		//---------------------------------------

		std::string airedRegex = "(?<=Aired:</span>)(\\s*)(?s)(.+?)(?=\\s*</div>)";
		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(airedRegex);

		std::string airedDate = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			airedDate = what[2];

			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}
		result.SetKeyValue(kAiredDate,airedDate);

		//---------------------------------------
		//			
		//				Characters
		//			(dis gon' be gud)
		//---------------------------------------
		std::string chrStep1 = "(?<=<div class=\"picSurround\"><a href=\"/character)(?s)(.+?)(?=\"\\sstyle=\"font-weight:)";

		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(chrStep1);

		std::vector<std::string> charactersWithIds;
		while(boost::regex_search(start,end,what,expr,flags))
		{
			charactersWithIds.push_back(what[0]);
			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		//Extract ID and name
		// i.e. /94351/Yuzu_Iizuka to 94351 and Yuzu Iizuka
		for(int i=0; i < charactersWithIds.size(); ++i)
		{
			std::string ch = charactersWithIds[i];
			int idStart =  ch.find_first_of("/");
			int idEnd   =  ch.find_last_of("/");

			std::string id = ch.substr(idStart+1,idEnd-(idStart+1));

			std::string name = ch.substr(idEnd+1,ch.size() - idEnd);

			boost::replace_all(name,"_"," ");

			Character character;
			character.SetKeyValue(kCharacterId,id);
			character.SetKeyValue(kCharacterName,name);
			result.Characters.push_back(character);
		}

		//---------------------------------------
		//			
		//				Synopsis
		//				
		//---------------------------------------
		std::string synopsisOuterRegex = "(?<=<span itemprop=\"description\">)(\\s*)(?s)(.+?)(?=\\s*</span>)";

		flags = boost::match_default;
		start = data.begin();
		end = data.end();

		expr = boost::regex(synopsisOuterRegex);
		std::string synopsis = "";
		if(boost::regex_search(start,end,what,expr,flags))
		{
			std::string o = what[0];
			synopsis = o;
			start = what[0].second;
			// update flags: 
			flags |= boost::match_prev_avail;
			flags |= boost::match_not_bob;
		}

		boost::replace_all(synopsis,"<br />","");

		result.SetKeyValue(kSynopsis,synopsis);

		return result;
	}

	ChiString MyAnimelistUtility::GetFilenameFromURL(const std::string& url)
	{
		int slash = url.find_last_of("/");
		int dot = url.find_last_of(".");

		ChiString sub = url.substr(slash+1,slash-dot);



		return sub;
	}
}
