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
#ifndef __FileHelper_h__
#define __FileHelper_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport FileReader
	{
	protected:
		std::ifstream mStream;
		ChiString mFile;
	public:
		FileReader(const ChiString& fileName);
		~FileReader();
		bool Open();
		void Close();
		ChiString Read();
		void ReadRef(ChiString&);
	};
	class MalApiExport FileWriter
	{
	protected:
		std::ofstream mStream;
		ChiString mFile;
	public:
		FileWriter(const ChiString& fileName);
		bool Open();
		void Close();
		void Write(ChiString);
		void Write(std::stringstream&);
	};
	class MalApiExport FileUtil
	{
	public:
		FileUtil();
		bool CheckIfDirectoryExists(const ChiString& path);
		bool CreateDir(const ChiString& path);

		static FileUtil* Get();
	};

	ChiString GetMiddle(ChiString str,::size_t pos,std::size_t count);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#endif