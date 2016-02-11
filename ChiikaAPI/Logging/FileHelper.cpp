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
#include "FileHelper.h"

#include <Windows.h>
#include "boost\filesystem.hpp"
//----------------------------------------------------------------------------
ChiikaApi::FileUtil* gFileUtil = NULL;
namespace ChiikaApi
{
	ChiString GetMiddle(ChiString str,std::size_t pos,std::size_t count)
	{
		if(count < str.size())
			return str.substr(pos,count);
		if(count == -1)
			return str;
		if(count >= str.size())
			return str;
		return ChiString();
	}
	//----------------------------------------------------------------------------
	FileReader::FileReader(const ChiString& file)
	{
		mFile = file;
	}
	//----------------------------------------------------------------------------
	FileReader::~FileReader()
	{
		if(mStream.is_open())
			mStream.close();
	}
	//----------------------------------------------------------------------------
	bool FileReader::Open()
	{
		mStream.open(mFile.c_str(),std::ios::in);
		return mStream.is_open();
	}
	//----------------------------------------------------------------------------
	void FileReader::Close()
	{
		mStream.close();
	}
	//----------------------------------------------------------------------------
	ChiString FileReader::Read()
	{
		std::ostringstream output;
		ChiString line;
		while(std::getline(mStream,line))
		{
			output << line;
		}
		return output.str();
	}
	//----------------------------------------------------------------------------
	void FileReader::ReadRef(ChiString& outputStr)
	{
		std::ostringstream output;
		ChiString line;
		while(std::getline(mStream,line))
		{
			output << line;
		}
		outputStr = output.str();
	}
	//----------------------------------------------------------------------------
	FileWriter::FileWriter(const ChiString& file)
	{
		mFile = file;
	}
	//----------------------------------------------------------------------------
	bool FileWriter::Open()
	{
		mStream.open(mFile.c_str(),std::ios::trunc);
		return mStream.is_open();
	}
	//----------------------------------------------------------------------------
	void FileWriter::Close()
	{
		mStream.close();
	}
	//----------------------------------------------------------------------------
	void FileWriter::Write(ChiString s)
	{
		mStream << s;
		mStream.flush();
	}
	//----------------------------------------------------------------------------
	void FileWriter::Write(std::stringstream& stream)
	{
		mStream << stream.rdbuf();
		mStream.flush();
	}
	//----------------------------------------------------------------------------
	FileUtil::FileUtil()
	{
		gFileUtil = this;
	}
	//----------------------------------------------------------------------------
	bool FileUtil::CheckIfDirectoryExists(const ChiString& path)
	{

//#ifdef YUME_PLATFORM_WIN32
//		DWORD dwAttrib = GetFileAttributesA(path.c_str());
//
//		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
//			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
//#endif
		return boost::filesystem::exists(path);
	}
	//----------------------------------------------------------------------------
	bool FileUtil::CreateDir(const ChiString& path)
	{
		if(CheckIfDirectoryExists(path))
			return false;
		return boost::filesystem::create_directory(path);
	}
	//----------------------------------------------------------------------------
	FileUtil* FileUtil::Get()
	{
		return gFileUtil ;
	}
	//-----------------------------------------------------------------------
}
//----------------------------------------------------------------------------