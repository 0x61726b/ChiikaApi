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
#include "Common/ExceptionManager.h"
#include "pugixml.hpp"
#include "Logging\Log.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	typedef Map<OptionsEnum,String>::type OptionsMap;
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
	OptionsEnum GetEnumValue(String str)
	{
		StdIt(OptionsMap) It;
		ForEachOnStd(It,AllChiikaSettings)
		{
			if(It->second == str)
			{
				return It->first;
			}
		}
	}
}
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	void AppSettings::SetDefaultValues()
	{
		String dataPath = (m_sGlobalPath) + "/Data";
		m_sSettingsPath = dataPath + "/Chiika.cfg";

		Initialize();

		m_bFirstLaunch = true;


		/*QFile file(m_sSettingsPath);
		if(file.exists())
		{
			m_bFirstLaunch = false;
			return;
		}*/


		String m_sAnimeListFile = dataPath + "/Chitanda.eru";
		String m_sMangaListFile =  dataPath + "/Oreki.houtarou";
		String m_sUpdateListFile =  dataPath + "/Satoshi.fukube";
		String m_sUserInfo = dataPath + "/User.eru";
		String m_sAnimeDetailsFile = dataPath + "/Detailskun.eru";
		String m_sAnimeFolderPath = "";
		String m_sSenpaiPath = dataPath + "/Senpai.moe";
		LoggingLevel lv = LoggingLevel::LOG_LEVEL_NORMAL;

		/**/
		AddIntegerOption(API_LOG_LEVEL,(int)lv);

		AddStringOption(LIBRARY_ANIME_LIST_PATH,m_sAnimeListFile);
		AddStringOption(LIBRARY_MANGA_LIST_PATH,m_sMangaListFile);
		AddStringOption(LIBRARY_UPDATE_LIST_PATH,m_sUpdateListFile);
		AddStringOption(LIBRARY_USER_INFO_PATH,m_sUserInfo);
		AddStringOption(LIBRARY_ANIME_DETAILS_PATH,m_sAnimeDetailsFile);
		AddStringOption(LIBRARY_ANIME_FOLDER_PATH,m_sAnimeFolderPath);
		AddStringOption(LIBRARY_SENPAI_PATH,m_sSenpaiPath);
		/**/
		AddBooleanOption(WINDOW_START_MINIMIZED,false);
		AddBooleanOption(WINDOW_START_WITH_WINDOWS,false);
		AddBooleanOption(WINDOW_REMEMBER_POS,true);
		AddBooleanOption(WINDOW_REMEMBER_SIZE,true);
		/**/
		AddIntegerOption(LIBRARY_SYNC_EVERY_X_SECOND,150);
		/**/
		AddStringOption(COLORS_ANIMELIST,"red");
		AddStringOption(COLORS_MANGALIST,"blue");
		AddStringOption(COLORS_HOME,"teal");
		AddStringOption(COLORS_SETTINGS,"blueGrey");
		/**/
		AddStringOption(GEN_APP_STARTING_PAGE,"Home");

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
	StringOption::StringOption(OptionsEnum nsp,String v)
		: SettingInterface(nsp,OptionsType::Str)
	{
		SetValue(v);
	}
	//----------------------------------------------------------------------------
	void StringOption::Execute()
	{
	}
	//----------------------------------------------------------------------------
	String StringOption::GetValue()
	{
		return Value;
	}
	//----------------------------------------------------------------------------
	void StringOption::SetValue(String str)
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
	AppSettings::AppSettings(const String& settings,String globalPath)
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
	void AppSettings::SetAnimeFolderPath(String path)
	{

	}
	//----------------------------------------------------------------------------
	void AppSettings::Initialize()
	{
		String dataPath = (m_sGlobalPath) + "/Data";
		//QDir dir(dataPath);

		////Create folders here

		//if(!dir.exists())
		//{
		//	if(!QDir().mkdir(dataPath))
		//		CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't create Data directory!","AppSettings::Initialize")
		//		m_bFirstLaunch = true;
		//}

		//QDir imageDir(dataPath + "/Images");
		//if(!imageDir.exists())
		//{
		//	if(!QDir().mkdir(dataPath + "/Images"))
		//		CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't create Images directory!","AppSettings::Initialize")
		//}
	}
	//----------------------------------------------------------------------------
	String AppSettings::GetStringOption(OptionsEnum option)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<StringOption> filePtr = std::static_pointer_cast<StringOption>(It->second);
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
	void AppSettings::SetStringOption(OptionsEnum option,String newValue)
	{
		ShrPtr<SettingInterface> ptr;
		StdIt(OptionValueMap) It = m_Settings.find(option);

		ShrPtr<StringOption> filePtr = std::static_pointer_cast<StringOption>(It->second);
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
		//QFile file((m_sSettingsPath));


		//if(file.open(QFile::WriteOnly))
		//{
		//	pugi::xml_document doc;

		//	pugi::xml_node  root = doc.append_child("Chiika");
		//	pugi::xml_node  settings = root.append_child("Settings");

		//	//pugi::xml_node  _iterator It;

		//	StdIt(OptionValueMap) It;
		//	ForEachOnStd(It,m_Settings)
		//	{
		//		//Get string value
		//		StdIt(OptionsMap) strValue = AllChiikaSettings.find(It->first);
		//		if(IsValidIt(strValue,AllChiikaSettings))
		//		{
		//			pugi::xml_node  pugi::xml_node  = settings.append_child(strValue->second.toStdString().c_str());

		//			StdIt(OptionValueMap) s = m_Settings.find(It->first);
		//			ShrPtr<SettingInterface> sptr = s->second;

		//			switch(sptr->GetType())
		//			{
		//			case OptionsType::Str:
		//			{
		//				SetXMLValue(node,QToChar(GetStringOption(It->first)));
		//				SetXMLAttrType(node,"String");
		//			}
		//			break;
		//			case OptionsType::Boolean:
		//			{
		//				SetXMLValue(node,(GetBooleanOption(It->first)));
		//				SetXMLAttrType(node,"Boolean");
		//			}
		//			break;
		//			case OptionsType::Int:
		//			{
		//				SetXMLValue(node,GetIntegerOption(It->first));
		//				SetXMLAttrType(node,"Integer");
		//			}
		//			break;
		//			}
		//		}
		//	}

		//	doc.save_file(m_sSettingsPath.toStdString().c_str());
		//}
		//else
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't save settings file!","AppSettings::Save")
		//}
	}
	//----------------------------------------------------------------------------
	void AppSettings::Load()
	{
		/*QFile file((m_sSettingsPath));
		if(file.open(QFile::ReadOnly))
		{
			pugi::xml_document doc;
			String fileData = file.readAll();
			doc.load(fileData.toStdString().c_str());

			pugi::xml_node  root = doc.child("Chiika");
			pugi::xml_node  settings = root.child("Settings");

			pugi::xml_node  _iterator It;
			ForEachOnXml(It,settings)
			{
				String nodeName = It->name();
				String nodeAttr = It->attribute("Type").value();

				if(nodeName != "")
				{
					String nodeValue = It->child_value();
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
						AddStringOption(e,nodeValue);
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
						AddIntegerOption(e,nodeValue.toInt());
					}
					break;
					}
				}
			}

		}
		else
		{
			CHIKA_EXCEPTION(Exception::ERR_CANNOT_WRITE_TO_FILE,"Can't open settings file!","AppSettings::Load")
		}*/
	}
	//----------------------------------------------------------------------------
	String AppSettings::GetDataPath()
	{
		return (m_sGlobalPath) + "/Data";
	}
	//----------------------------------------------------------------------------
	String AppSettings::GetImagePath()
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
