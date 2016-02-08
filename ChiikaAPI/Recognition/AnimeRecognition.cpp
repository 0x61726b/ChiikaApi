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
#include "Recognition/AnimeRecognition.h"

#include <string.h>
//#include "ThirdParty/anitomy/anitomy/anitomy.h"
//----------------------------------------------------------------------------
// Here is the explanation of how recognition works on Chiika
// Chiika adds a windows message called SHELLHOOK to listen window events
// which means when you launch your favourite media player Chiika will know (See http://arkenthera.github.io/Detecting-external-applicaiton-launch-on-Windows-with-Qt/ )
// When MPRecognitionInterface recognizes a media player it will call this class ::RecognizeAndCache
// Then the method will call anitomy to try to recognize the anime.
// If recognized, it will save the path into local database so next time we wont call anitomy for saving time/resources
// To:do normal recognition,without launching media player.
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	//----------------------------------------------------------------------------											
	AnimeRecognition::AnimeRecognition()
	{
		//ChiStringstream strStream;
		//ChiString test = "test";
		//ChiString param = test.toStdChiString();
		//strStream << param;
		//const ChiString& tmp = strStream.str();
		//const char* cstr = tmp.c_str();
		//LOG(ChiString::fromStdChiString(cstr));
	}
	//----------------------------------------------------------------------------
	void AnimeRecognition::RecognizeAndCache(ChiString file)
	{
		//anitomy::Anitomy anitomy;
		//anitomy.Parse(file.toStdWChiString()); //Wide ChiString mmmhhmm

		//anitomy::Elements& elements = anitomy.elements();


		//anitomy::element_iterator_t It = elements.begin();

		//if(elements.size() > 0)
		//{
		//	if(elements.at(0).first != anitomy::kInvalid)
		//	{

		//	}
		//	else
		//	{
		//		qDebug() << elements.size();
		//	}
		//}


		//for(auto& element : elements) {
		//	std::wcout << element.second << std::endl;
		//}



	}
	//----------------------------------------------------------------------------
	template<> AnimeRecognition* Singleton<AnimeRecognition>::msSingleton = 0;
	AnimeRecognition& AnimeRecognition::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
}
