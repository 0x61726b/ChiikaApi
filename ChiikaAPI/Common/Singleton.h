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
#ifndef __Singleton_h__
#define __Singleton_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	template <typename T> class MalApiExport Singleton
	{
	private:
		/** \brief Explicit private copy constructor. This is a forbidden operation.*/
		Singleton(const Singleton<T> &);

		/** \brief Private operator= . This is a forbidden operation. */
		Singleton& operator=(const Singleton<T> &);

	protected:

		static T* msSingleton;

	public:
		Singleton(void)
		{

			msSingleton = static_cast<T*>(this);

		}
		~Singleton(void)
		{
			msSingleton = 0;
		}
		static T& Get(void)
		{
			return (*msSingleton);
		}
		static T* GetPtr(void)
		{
			return msSingleton;
		}
	};
}
#endif // SINGLETON_H
//----------------------------------------------------------------------------
