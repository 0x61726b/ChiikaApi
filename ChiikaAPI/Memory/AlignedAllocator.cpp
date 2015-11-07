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
#include "Common/Required.h"
#include "Memory/AlignedAllocator.h"

namespace ChiikaApi
{
	//---------------------------------------------------------------------
	void* AlignedMemory::allocate(size_t size,size_t alignment)
	{
		//assert(0 < alignment && alignment <= 128 && Bitwise::isPO2(alignment));

		unsigned char* p = new unsigned char[size + alignment];
		size_t offset = alignment - (size_t(p) & (alignment-1));

		unsigned char* result = p + offset;
		result[-1] = (unsigned char)offset;

		return result;
	}
	//---------------------------------------------------------------------
	void* AlignedMemory::allocate(size_t size)
	{
		return allocate(size,YUME_SIMD_ALIGNMENT);
	}
	//---------------------------------------------------------------------
	void AlignedMemory::deallocate(void* p)
	{
		if(p)
		{
			unsigned char* mem = (unsigned char*)p;
			mem = mem - mem[-1];
			delete[] mem;
		}
	}
}