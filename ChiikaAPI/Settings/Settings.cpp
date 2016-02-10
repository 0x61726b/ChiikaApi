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
#include "Settings/Settings.h"
#include "pugixml.hpp"
#include "Logging\FileHelper.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	typedef Map<OptionsEnum,ChiString>::type OptionsMap;
	//----------------------------------------------------------------------------
	OptionsMap AllChiikaSettings =
	{
		/*Api Options*/
		OptionsMap::value_type(API_LOG_LEVEL,"LogLevel"),
		/**/
		OptionsMap::value_type(LIBRARY_ANIME_LIST_PATH,"AnimeListPath"),
		OptionsMap::value_type(LIBRARY_MANGA_LIST_PATH,"MangaListPath"),
		OptionsMap::value_type(LIBRARY_UPDATE_LIST_PATH,"UpdateListPath"),
		OptionsMap::value_type(LIBRARY_USER_INFO_PATH,"UserInfoPath"),
		OptionsMap::value_type(LIBRARY_ANIME_FOLDER_PATH,"AnimeFolderPath"),
		OptionsMap::value_type(LIBRARY_ANIME_DETAILS_PATH,"AnimeDetailsPath"),
		OptionsMap::value_type(LIBRARY_SYNC_EVERY_X_SECOND,"SyncEveryXSeconds"),
		OptionsMap::value_type(LIBRARY_SENPAI_PATH,"SenpaiPath"),
		/**/
		OptionsMap::value_type(WINDOW_START_MINIMIZED,"WindowStartMinimized"),
		OptionsMap::value_type(WINDOW_START_WITH_WINDOWS,"WindowStartWithWindows"),
		OptionsMap::value_type(WINDOW_REMEMBER_POS,"WindowRememberPosition"),
		OptionsMap::value_type(WINDOW_REMEMBER_SIZE,"WindowRememberWindowSize"),
		/**/
		OptionsMap::value_type(COLORS_ANIMELIST,"ColorsAnimeList"),
		OptionsMap::value_type(COLORS_MANGALIST,"ColorsMangaList"),
		OptionsMap::value_type(COLORS_HOME,"ColorsHome"),
		OptionsMap::value_type(COLORS_SETTINGS,"ColorSettings"),
		/**/
		OptionsMap::value_type(GEN_APP_STARTING_PAGE,"AppStartingPage")
	};
	//----------------------------------------------------------------------------
	OptionsEnum GetEnumValue(ChiString str)
	{
		StdIt(OptionsMap) It;
		ForEachOnStd(It,AllChiikaSettings)
		{
			if(It->second == str)
			{
				return It->first;
			}
		}
		return OptionsEnum::UNKNOWN;
	}
}
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	void AppSettings::SetDefaultValues()
	{
		ChiString dataPath = (m_sGlobalPath)+"/Data";
		m_sSettingsPath = m_sGlobalPath + "/Chiika.cfg";

		Initialize();

		m_bFirstLaunch = true;


		FileReader file(m_sSettingsPath);
		if(file.Open())
		{
			m_bFirstLaunch = false;
			return;
		}


		ChiString m_sAnimeListFile = dataPath + "/Chitanda.eru";
		ChiString m_sMangaListFile =  dataPath + "/Oreki.houtarou";
		ChiString m_sUserInfo = dataPath + "/User.eru";
		ChiString m_sSenpaiPath = dataPath + "/Senpai.moe";






		/**/

		AddChiStringOption(LIBRARY_ANIME_LIST_PATH,m_sAnimeListFile);
		AddChiStringOption(LIBRARY_MANGA_LIST_PATH,m_sMangaListFile);
		AddChiStringOption(LIBRARY_USER_INFO_PATH,m_sUserInfo);
		AddChiStringOption(LIBRARY_SENPAI_PATH,m_sSenpaiPath);




		/**/
		

		Save();
	}
	//----------------------------------------------------------------------------
	SettingInterface::SettingInterface(OptionsEnum Nsp,OptionsType type)
	{
		Id = Nsp;
		Type = type;
	}
	//----------------------------------------------------------------------------
	OptionsType SettingInterface::GetType()
	{
		return Type;
	}
	//----------------------------------------------------------------------------
	ChiStringOption::ChiStringOption(OptionsEnum nsp,ChiString v)
		: SettingInterface(nsp,OptionsType::Str)
	{
		SetValue(v);
	}
	//----------------------------------------------------------------------------
	void ChiStringOption::Execute()
	{
	}
	//----------------------------------------------------------------------------
	ChiString ChiStringOption::GetValue()
	{
		return Value;
	}
	//----------------------------------------------------------------------------
	void ChiStringOption::SetValue(ChiString str)
	{
		Value = str;
	}
	//----------------------------------------------------------------------------
	BooleanOption::BooleanOption(OptionsEnum nsp,bool b)
		: SettingInterface(nsp,OptionsType::Boolean)
	{
		SetValue(b);
	}
	//----------------------------------------------------------------------------
	void BooleanOption::Execute()
	{
	}
	//----------------------------------------------------------------------------
	bool BooleanOption::GetValue()
	{
		return Value;
	}
	//----------------------------------------------------------------------------
	void BooleanOption::SetValue(bool b)
	{
		Value = b;
	}
	//----------------------------------------------------------------------------
	IntegerOption::IntegerOption(OptionsEnum nsp,int b)
		: SettingInterface(nsp,OptionsType::Int)
	{
		SetValue(b);
	}
	//----------------------------------------------------------------------------
	void IntegerOption::Execute()
	{
	}
	//----------------------------------------------------------------------------
	void IntegerOption::SetValue(int i)
	{
		Value = i;
	}
	//----------------------------------------------------------------------------
	int IntegerOption::GetValue()
	{
		return Value;
	}
	//----------------------------------------------------------------------------
	AppSettings::AppSettings(const ChiString& settings,ChiString globalPath)
	{
		m_sGlobalPath = globalPath;


		SetDefaultValues();

		Load();
	}
	//----------------------------------------------------------------------------
	AppSettings::~AppSettings()
	{
		m_Settings.clear();
	}
	//----------------------------------------------------------------------------
	void AppSettings::SetAnimeFolderPath(ChiString path)
	{

	}
	//----------------------------------------------------------------------------
	void AppSettings::Initialize()
	{
		ChiString dataPath = (m_sGlobalPath)+"/Data";
		//Create folders here

		if(!FileUtil::Get()->CheckIfDirectoryExists(dataPath))
		{
			if(!FileUtil::Get()->CreateDir(dataPath))
			{
				
					m_bFirstLaunch = true;
			}
		}

		ChiString imageDir = (dataPath + "/Images");
		if(!FileUtil::Get()->CheckIfDirectoryExists(imageDir))
		{
			if(FileUtil::Get()->CreateDir(imageDir))
			{
				if (!FileUtil::Get()->CreateDir(imageDir + "/Anime"))
				{

				}
			}	
		}

		if (!FileUtil::Get()->CheckIfDirectoryExists(m_sGlobalPath + "/Config"))
		{
			FileUtil::Get()->CreateDir(m_sGlobalPath + "/Config");
		}
	}
	//----------------------------------------------------------------------------
	ChiString AppSettings::GetChiStringOption(OptionsEnum option)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<ChiStringOption> filePtr = std::static_pointer_cast<ChiStringOption>(It->second);
		if(filePtr)
		{
			return filePtr->GetValue();
		}
		else
		{
			//Something is wrong..
			return "Kill me";
		}
	}
	//----------------------------------------------------------------------------
	bool AppSettings::GetBooleanOption(OptionsEnum option)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<BooleanOption> filePtr = std::static_pointer_cast<BooleanOption>(It->second);
		if(filePtr)
		{
			return filePtr->GetValue();
		}
		else
		{
			//Something is wrong..
			return false;
		}
	}
	//----------------------------------------------------------------------------
	int AppSettings::GetIntegerOption(OptionsEnum option)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<IntegerOption> intPtr = std::static_pointer_cast<IntegerOption>(It->second);
		if(intPtr)
		{
			return intPtr->GetValue();
		}
		else
		{
			//Something is wrong..
			return -1;
		}
	}
	//----------------------------------------------------------------------------
	void AppSettings::SetChiStringOption(OptionsEnum option,ChiString newValue)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<ChiStringOption> filePtr = std::static_pointer_cast<ChiStringOption>(It->second);
		if(filePtr)
		{
			filePtr->SetValue(newValue);

			Save();
		}
	}
	//----------------------------------------------------------------------------
	void AppSettings::SetBooleanOption(OptionsEnum option,bool newValue)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<BooleanOption> filePtr = std::static_pointer_cast<BooleanOption>(It->second);
		if(filePtr)
		{
			filePtr->SetValue(newValue);

			Save();
		}
	}
	//----------------------------------------------------------------------------
	void AppSettings::Save()
	{
		FileWriter file((m_sSettingsPath));


		if(file.Open())
		{
			pugi::xml_document doc;

			pugi::xml_node  root = doc.append_child(("Chiika"));
			pugi::xml_node  settings = root.append_child("Settings");

			//pugi::xml_node  _iterator It;

			StdIt(OptionValueMap) It;
			ForEachOnStd(It,m_Settings)
			{
				//Get ChiString value
				StdIt(OptionsMap) strValue = AllChiikaSettings.find(It->first);
				if(IsValidIt(strValue,AllChiikaSettings))
				{
					pugi::xml_node node = settings.append_child(strValue->second.c_str());

					StdIt(OptionValueMap) s = m_Settings.find(It->first);
					ShrPtr<SettingInterface> sptr = s->second;

					switch(sptr->GetType())
					{
					case OptionsType::Str:
					{
						SetXMLValue(node,(GetChiStringOption(It->first).c_str()));
						SetXMLAttrType(node,"String");
					}
					break;
					case OptionsType::Boolean:
					{
						SetXMLValue(node,(GetBooleanOption(It->first)));
						SetXMLAttrType(node,"Boolean");
					}
					break;
					case OptionsType::Int:
					{
						SetXMLValue(node,GetIntegerOption(It->first));
						SetXMLAttrType(node,"Integer");
					}
					break;
					}
				}
			}
			file.Close();
			doc.save_file(m_sSettingsPath.c_str());
		}
		else
		{
			
		}
	}
	//----------------------------------------------------------------------------
	void AppSettings::Load()
	{
		FileReader file((m_sSettingsPath));
		if(file.Open())
		{
			pugi::xml_document doc;
			ChiString fileData = file.Read();
			doc.load(fileData.c_str());

			pugi::xml_node  root = doc.child(("Chiika"));
			pugi::xml_node  settings = root.child("Settings");

			pugi::xml_node::iterator It;
			ForEachOnXml(It,settings)
			{
				ChiString nodeName = It->name();
				ChiString nodeAttr = It->attribute("Type").value();

				if(nodeName != "")
				{
					ChiString nodeValue = It->child_value();
					OptionsEnum e = GetEnumValue(nodeName);

					OptionsType type;

					if(nodeAttr == "String")
					{
						type = OptionsType::Str;
					}
					if(nodeAttr == "Boolean")
					{
						type = OptionsType::Boolean;
					}
					if(nodeAttr == "Integer")
					{
						type = OptionsType::Int;
					}

					switch(type)
					{
					case OptionsType::Str:
					{
						AddChiStringOption(e,nodeValue);
					}
					break;
					case OptionsType::Boolean:
					{
						if(nodeValue == "true")
							AddBooleanOption(e,true);
						else
							AddBooleanOption(e,false);
					}
					break;
					case OptionsType::Int:
					{
						AddIntegerOption(e,atoi(nodeValue.c_str()));
					}
					break;
					}
				}
			}
			file.Close();
		}
		else
		{
			
		}
	}
	//----------------------------------------------------------------------------
	ChiString AppSettings::GetDataPath()
	{
		return (m_sGlobalPath)+"/Data";
	}
	//----------------------------------------------------------------------------
	ChiString AppSettings::GetImagePath()
	{
		return GetDataPath() + "/Images/";
	}
	//----------------------------------------------------------------------------
	bool AppSettings::GetIfFirstLaunch()
	{
		return m_bFirstLaunch;
	}
	//----------------------------------------------------------------------------
	template<> AppSettings* Singleton<AppSettings>::msSingleton = 0;
	AppSettings& AppSettings::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
	AppSettings* AppSettings::GetPtr(void)
	{
		return msSingleton;
	}
}
