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
#ifndef __StdHeaders_H__
#define __StdHeaders_H__

#ifdef __BORLANDC__
    #define __STD_ALGORITHM
#endif
//


// STL containers


#include <string>
#include <queue>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <map>
#include <vector>

//C++11
#include <chrono>

#include <memory>
#include <functional>
#include <type_traits>

#ifdef __BORLANDC__
namespace ChiikaApi
{
    using namespace std;
}
#endif


#if YUME_PLATFORM == YUME_PLATFORM_WIN32 || YUME_PLATFORM == YUME_PLATFORM_WINRT
#  undef min
#  undef max
#  if defined( __MINGW32__ )
#    include <unistd.h>
#  endif
#endif

#if YUME_PLATFORM == YUME_PLATFORM_LINUX
extern "C" {

#   include <unistd.h>
#   include <dlfcn.h>

}
#endif



//#if defined ( OGRE_GCC_VISIBILITY ) && ((OGRE_PLATFORM == OGRE_PLATFORM_APPLE && !__LP64__) && OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS)
//#   pragma GCC visibility pop
//#endif
#endif
