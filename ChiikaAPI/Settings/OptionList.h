//----------------------------------------------------------------------------
//Chiika
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
#ifndef __ChiikaAppOptionList_h__
#define __ChiikaAppOptionList_h__
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	/** Little Explanation on how settings work on Chiika
		We have OptionsEnum and an option map which is used to "ChiStringfy" this option enum
		that is used when writing to XML. Different types of settings(ChiString,bool,int)
		will implement Setting interface and they will be stored as pointers on the singleton class
		The reason I chose to do this is purely laziness.I didnt want to hard code every possible setting
		then write getter and setter for every one of them.Huh. This way I'll write getters for ChiString,int and boolean
		options then cast pointers.Since I know the types pointer casting 100% safe (maybe not).
		Somehow if you change a setting or add a setting here, remember to use the correct macro to add otherwise things will go bad.
	*/
	enum OptionsEnum
	{
		/* Api Settings*/
		API_LOG_LEVEL,
		/* Library Setttings*/
		LIBRARY_ANIME_LIST_PATH, //ChiString
		LIBRARY_MANGA_LIST_PATH, //ChiString
		LIBRARY_UPDATE_LIST_PATH, //ChiString
		LIBRARY_USER_INFO_PATH, //ChiString
		LIBRARY_ANIME_FOLDER_PATH, //ChiString
		LIBRARY_ANIME_DETAILS_PATH,//ChiString
		LIBRARY_SENPAI_PATH,
		LIBRARY_SYNC_EVERY_X_SECOND, //Int
		/* Window Settings*/
		WINDOW_START_MINIMIZED, //Boolean
		WINDOW_START_WITH_WINDOWS, //Boolean
		WINDOW_REMEMBER_POS, //Boolean
		WINDOW_REMEMBER_SIZE, //Boolean
		/* Colors */
		COLORS_ANIMELIST,
		COLORS_MANGALIST,
		COLORS_HOME,
		COLORS_SETTINGS,
		/* General */
		GEN_APP_STARTING_PAGE //ChiString. Can be [Home,AList,MList]
	};
	enum OptionsType
	{
		Str,
		Boolean,
		Int
	};
}
//----------------------------------------------------------------------------
#endif // CHIIKADEFINES

