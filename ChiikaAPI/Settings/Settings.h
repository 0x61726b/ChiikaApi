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
#ifndef __ChiikaSettings_h__
#define __ChiikaSettings_h__
//----------------------------------------------------------------------------
//Defines
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "Common/Singleton.h"
#include "Settings/OptionList.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------
	class MalApiExport SettingInterface
	{
	public:
		SettingInterface(OptionsEnum nsp,OptionsType);
		virtual void Execute() = 0;

		OptionsType GetType();
	protected:
		OptionsEnum Id;
		OptionsType Type;
	};
	//----------------------------------------------------------------------------
	class MalApiExport StringOption : public SettingInterface
	{
	public:
		//Setting Interface
		StringOption(OptionsEnum nsp,String v);

		void Execute();
		String GetValue();
		void SetValue(String v);
	private:
		String Value;
	};
	//----------------------------------------------------------------------------
	class MalApiExport BooleanOption : public SettingInterface
	{
	public:
		BooleanOption(OptionsEnum nsp,bool b);

		void Execute();
		bool GetValue();
		void SetValue(bool b);

	private:
		bool Value;
	};
	//----------------------------------------------------------------------------
	class MalApiExport IntegerOption : public SettingInterface
	{
	public:
		IntegerOption(OptionsEnum nsp,int i);

		void Execute();
		int GetValue();
		void SetValue(int b);

	private:
		int Value;
	};
	//----------------------------------------------------------------------------
	class MalApiExport AppSettings : Singleton<AppSettings>
	{
	public:
		typedef std::map<std::string,std::string> FileMap; //<Name,Path>
		FileMap Files;

		static AppSettings& Get();
		static AppSettings* GetPtr();

		AppSettings(const String& settingsFile,String globalPath);
		~AppSettings();
		void Initialize();
		void Load();
		void Save();
		typedef Map<MangaInfo,MangaInfo>::type hehehe;
		void SetAnimeFolderPath(String path);

		/* A new era starts here*/

		typedef Map<OptionsEnum,ShrPtr<SettingInterface>>::type OptionValueMap;
		OptionValueMap m_Settings;

		void SetDefaultValues();
		

		String GetStringOption(OptionsEnum option);
		bool    GetBooleanOption(OptionsEnum option);
		int		GetIntegerOption(OptionsEnum option);

		void SetStringOption(OptionsEnum option,String newValue);
		void SetBooleanOption(OptionsEnum option,bool newValue);
		/* New era ends here*/

		String GetDataPath();
		String GetImagePath();

		bool GetIfFirstLaunch();

	private:
		String m_sGlobalPath;
		String m_sSettingsPath;

		//Option Values

		//Application Values
		bool m_bFirstLaunch;

		//Options

	};
}
//----------------------------------------------------------------------------
#endif
