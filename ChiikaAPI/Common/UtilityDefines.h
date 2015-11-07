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
#ifndef __ChiikaUtilityDefines_h__
#define __ChiikaUtilityDefines_h__
//----------------------------------------------------------------------------
#	define ToStd(x) x.c_str()
#	define QToStd(x) x.toStdString()
#	define QToChar(x) /*x.toStdString().c_str()*/
#	define Q_(x) /*String::fromStdString(x)*/
#	define FromStdToInt(x) /*String::fromStdString(x).toInt()*/
#	define FromXMLValueToInt(x) atoi(x.text().get()) /*String::fromStdString(x.text().get()).toInt()*/
#	define FromXMLValueToFloat(x) atof(x.text().get()) /* String::fromStdString(x.text().get()).toFloat()*/
#	define FromXMLValueToStd(x)  x.text().get()
#	define JsToQ(x) (x.asString())
#	define SetXMLValue(x,y) x.text().set(y)
#	define SetXMLAttrType(x,y) x.append_attribute("Type").set_value(y)
#	define ForEachOnStd(x,y) \
								  x = y.begin(); \
									  for(x;x != y.end(); ++x )
#	define ForEachOnXml(x,y) for(x = y.first_child();x != y.end(); x++)
#	define For(x,y) for(x; x < y; x++)
#	define MakePair(x,y) std::make_pair(x,y)
#	define AddToMap(x,y) y.insert(x)
#	define StdIt(x) x::iterator
#	define IsValidIt(x,y) x != y.end()
#	define ShrPtr std::shared_ptr //SharedPtr is used by boost huh
#	define UniquePtr std::unique_ptr
#	define MakeShared std::make_shared
#	define AddStringOption(x,y) AddToMap(MakePair(x,MakeShared<StringOption>(x,y)),m_Settings)
#	define AddBooleanOption(x,y) AddToMap(MakePair(x,MakeShared<BooleanOption>(x,y)),m_Settings)
#	define AddIntegerOption(x,y) AddToMap(MakePair(x,MakeShared<IntegerOption>(x,y)),m_Settings)
#	define RequestThread ThreadedRequest*
#	define CreateRequest  new ThreadedRequest

//----------------------------------------------------------------------------
#endif // CHIIKAUTILITYDEFINES
//----------------------------------------------------------------------------

