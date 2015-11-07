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
#include "Mock_ThreadedRequest.h"
#include "gtest\gtest.h"
//----------------------------------------------------------------------------
namespace Tests
{
	std::vector<ChiikaApi::SenpaiItem>* ClosestAnimeTest::AllSenpaiData = NULL;
	void ClosestAnimeTest::SetUpTestCase()
	{
		AllSenpaiData = new std::vector<SenpaiItem>();
		Json::Value root;
		Json::Reader reader;
		String dataFile = "D:\\Arken\\Qt\\ChiMalApi\\ChiikaAPI\\Tests\\json\\ClosestAnimeFromSenpaiTest.json";
		QFile file(dataFile);
		if(file.open(QFile::ReadOnly))
		{
			String fileData = file.readAll();
			bool b = reader.parse(fileData.toStdString(),root);

			if(b)
			{
				//Root
				const Json::Value meta = root["meta"];

				const Json::Value tz = meta["tz"];
				Json::Value::const_iterator It = tz.begin();

				TimezoneMap list;
				for(It;It != tz.end(); It++)
				{
					Json::Value inner = *It;

					Timezone tz;
					tz.Name = Q_(inner["abbr"].asString());
					tz.TimezoneIdentifier = Q_(It.name());
					tz.Offset = Q_(inner["offset"].asString());

					list.insert(TimezoneMap::value_type(tz.TimezoneIdentifier,tz));
				}


				//Items
				const Json::Value items = root["items"];
				Json::Value::const_iterator itemsIt = items.begin();

				for(itemsIt;itemsIt != items.end();itemsIt++)
				{
					Json::Value v = *itemsIt;

					SenpaiItem si;
					si.Name = JsToQ(v["name"]);
					const Json::Value airdates = v["airdates"];

					Json::Value::const_iterator adIt = airdates.begin();
					Map<String,Airdate>::type airdateList;

					ForEachOnStd(adIt,airdates)
					{
						Json::Value t = *adIt;

						Airdate ad;

						String timezoneValue = String::fromStdString(adIt.name());

						ad.TimeZone = list.find(timezoneValue)->second;
						ad.RdDate = JsToQ(t["rd_date"]);
						ad.RdTime = JsToQ(t["rd_time"]);
						ad.Weekday = t["weekday"].asInt();
						ad.RdWeekday = JsToQ(t["rd_weekday"]);

						airdateList.insert(std::make_pair(ad.TimeZone.TimezoneIdentifier,ad));
					}
					si.Airdates = airdateList;
					AllSenpaiData->push_back(si);
				}
			}
		}

	}

	void ClosestAnimeTest::TearDownTestCase()
	{
		AllSenpaiData->clear();
		delete AllSenpaiData;
		AllSenpaiData = NULL;
	}
	void ClosestAnimeTest::SetUp()
	{
		
	}
	void ClosestAnimeTest::TearDown()
	{
		
	}

}

