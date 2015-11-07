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
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	FileReader::FileReader(const std::string& file)
	{
		mFile = file;
	}
	bool FileReader::Open()
	{
		mStream.open(mFile.c_str());
		return mStream.is_open();
	}
	void FileReader::Close()
	{
		mStream.close();
	}
	std::string FileReader::Read()
	{
		std::ostringstream output;
		std::string line;
		while(std::getline(mStream,line))
		{
			output << line;
		}
		return output.str();
	}
}
//----------------------------------------------------------------------------