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

#	define JsToQ(x) (x.asString())
#	define SetXMLValue(x,y) x.text().set(y)
#	define SetXMLAttrType(x,y) x.append_attribute("Type").set_value(y)
#	define ForEachOnStd(x,y) \
								  x = y.begin(); \
									  for(x;x != y.end(); ++x )
#	define ForEachOnXml(x,y) for(x = y.first_child();x != y.end(); x++)
#	define StdIt(x) x::iterator
#	define IsValidIt(x,y) x != y.end()
#	define TryDelete(x) if(x) delete x
#	define InitializeNULL(x) x = NULL
#	define TryDestroy(x) if(x) x->Destroy();
#	define XmlNode pugi::xml_node
#	define XmlForeach(a,b) for(XmlNode a = b.first_child();a;a = a.next_sibling())
#	define EmptyKey(x,y) (strcmp(x.GetKeyValue(y).c_str(),y) == 0)
//----------------------------------------------------------------------------

#	define FsPath boost::filesystem::path
#	define SCOPED_LOCK boost::mutex::scoped_lock lock(m_Lock)
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport DictionaryBase
	{
	public:
		typedef std::vector<std::string> KeyList;
		virtual void SetKeyValue(const std::string& key, const std::string& value)
		{
			KeyMap::iterator It = m_KeyMap.find(key);
			if (It != m_KeyMap.end()) //Key exists
			{
				if(value.size() > 0)
					It->second = value;
			}
			else
			{
				m_KeyMap.insert(KeyMap::value_type(key, value));
			}
		};
		virtual const std::string& GetKeyValue(const std::string& key)
		{
			KeyMap::iterator It = m_KeyMap.find(key);
			if (It != m_KeyMap.end())
			{
				return m_KeyMap.find(key)->second;
			}
			return key;
		}
		virtual bool ContainsKey(const std::string& key)
		{
			KeyMap::iterator It = m_KeyMap.find(key);

			if (It != m_KeyMap.end())
				return true;
			return false;
		}
		virtual KeyMap GetKeys()
		{
			return m_KeyMap;
		}
		~DictionaryBase()
		{
			
		}
	protected:
		KeyMap m_KeyMap;
	};
}

//----------------------------------------------------------------------------
#endif // CHIIKAUTILITYDEFINES
//----------------------------------------------------------------------------

