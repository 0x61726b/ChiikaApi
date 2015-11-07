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
#ifndef __MemoryAllocator_h__
#define __MemoryAllocator_h__
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	enum MemoryCategory
	{
		MEMORY_CAT_GENERAL
	};
}
//----------------------------------------------------------------------------
#include "CustomMemoryAllocatedObject.h"
#include "STLAllocator.h"
//----------------------------------------------------------------------------
#if CHIIKA_MEMORY_ALLOCATOR == CHIIKA_MEMORY_ALLOCATOR_NEEDPOOLING
//----------------------------------------------------------------------------
#include "NedPooling.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	template <MemoryCategory Cat> class CategorisedAllocPolicy : public NedPoolingPolicy{};
	template <MemoryCategory Cat,size_t align = 0> class CategorisedAlignAllocPolicy : public NedPoolingAlignedPolicy<align>{};
}
#elif CHIIKA_MEMORY_ALLOCATOR == CHIIKA_MEMORY_ALLOCATOR_STD
//----------------------------------------------------------------------------
#include "StdAlloc.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	template <MemoryCategory Cat> class CategorisedAllocPolicy : public StdAllocPolicy{};
	template <MemoryCategory Cat,size_t align = 0> class CategorisedAlignAllocPolicy : public StdAlignedAllocPolicy<align>{};
}
#endif
//----------------------------------------------------------------------------

namespace ChiikaApi
{
	typedef CategorisedAllocPolicy <MemoryCategory::MEMORY_CAT_GENERAL> GeneralAllocPolicy;


	typedef AllocatedObject<GeneralAllocPolicy> GeneralAllocatedObject;

	typedef GeneralAllocatedObject GeneralObjAlloc;
}

namespace ChiikaApi
{
	template<typename T>
	T* constructN(T* basePtr,size_t count)
	{
		for(size_t i = 0; i < count; ++i)
		{
			new ((void*)(basePtr+i)) T();
		}
		return basePtr;
	}
}

#ifdef CHIIKA_DEBUG_MODE

#define ChiikaNew new
#define ChiikaDelete delete
#elif
#define ChiikaNew new
#define ChiikaDelete delete
#endif

#endif
