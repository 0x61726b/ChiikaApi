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
//	Date:	 10.2.2016
//----------------------------------------------------------------------------
#include "Stable.h"
#include "SenpaiMoe.h"
#include "Database\LocalDataManager.h"
#include "Settings\Settings.h"
#include "Root\Root.h"
#include "Logging\ChiString.h"
#include "Request\MalManager.h"
#include "Logging\FileHelper.h"
#include "Common\MyAnimelistUtility.h"
#include "json\json.h"
#include "Seasons/SeasonManager.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	SenpaiMoeDlRequest::SenpaiMoeDlRequest()
	{
		m_sName = kRequestDlSenpaiMoe;
	}
	//----------------------------------------------------------------------------
	SenpaiMoeDlRequest::~SenpaiMoeDlRequest()
	{
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::OnSuccess()
	{
		FileWriter fw(Root::Get()->GetAppSettings()->GetDataPath() + "Senpai.moe");

		//Write everything
		ChiString response = m_Curl->GetResponse();
		if (fw.Open())
		{
			fw.Write(response);
			fw.Close();
		}
		Json::Value root;
		Json::Reader reader;

		UserTimezoneInfo uTz = Root::Get()->GetSeasonManager()->GetUserTimezone();
		Timezone senpaiTimezone;
		bool b = reader.parse(response, root);

		//Only write the user data
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

				if (atoi(tz.TimezoneIdentifier.c_str()) == uTz.Bias)
				{
					senpaiTimezone = tz;
				}
			}

			//Items
			const Json::Value items = root["items"];
			Json::Value::const_iterator itemsIt = items.begin();
			SenpaiData sd;

			Json::Value root_;
			Json::Value userSenpai;
			Json::Value itemSenpai(Json::arrayValue);
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
				v.removeMember("airdates");
				v.removeMember("simulcast_airdates");
				v.removeMember("commentary");
				v.removeMember("fansub");
				v.removeMember("fansubClass");
				v.removeMember("fansub_link");
				v.removeMember("hasTranslation");
				v.removeMember("isAired");
				v.removeMember("isSequel");
				v.removeMember("isShort");
				v.removeMember("isSimulcastAired");
				v.removeMember("missingAirdate");
				v.removeMember("missingAirtime");
				v.removeMember("notes");
				v.removeMember("isSimulcastAired");
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

					if (ad.TimeZone.Offset == senpaiTimezone.Offset)
					{
						v["airdates"][timezoneValue] = t;
					}
				}
				itemSenpai.append(v);

			}
			root_["meta"] = meta;
			root_["items"] = (itemSenpai);
			FileWriter fw(Root::Get()->GetAppSettings()->GetDataPath() + "SenpaiUser.moe");
			if (fw.Open())
			{
				Json::StyledWriter styledWriter;
				std::stringstream file;

				file << styledWriter.write(root_);
				fw.Write(file);

				fw.Close();
			}

		}
		RequestInterface::OnSuccess();
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::OnError()
	{
		RequestInterface::OnError();
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::Initialize()
	{
		m_Curl = new CurlRequest;
		m_Curl->Initialize();
		m_Curl->AddListener(this);
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::SetOptions()
	{
		int method;
		method = CURLOPT_HTTPGET;

		m_Curl->SetMethod(method, "");
		m_Curl->SetUrl("http://www.senpai.moe/export.php?type=json&src=raw");

		m_Curl->SetReady();
	}
	//----------------------------------------------------------------------------
	void SenpaiMoeDlRequest::Initiate()
	{

	}
	//----------------------------------------------------------------------------
}