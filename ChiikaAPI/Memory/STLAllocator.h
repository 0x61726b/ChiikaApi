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
#ifndef __STLAllocator_h__
#define __STLAllocator_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	// Base STL allocator class.
	template<typename T>
	struct STLAllocatorBase
	{	// base class for generic allocators
		typedef T value_type;
	};

	// Base STL allocator class. (const T version).
	template<typename T>
	struct STLAllocatorBase<const T>
	{	// base class for generic allocators for const T
		typedef T value_type;
	};

	template
		<
		typename T,
		typename AllocPolicy
		>
	class STLAllocator : public STLAllocatorBase<T>
	{
	public:
		/// define our types, as per ISO C++
		typedef STLAllocatorBase<T>			Base;
		typedef typename Base::value_type	value_type;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;


		/// the standard rebind mechanism
		template<typename U>
		struct rebind
		{
			typedef STLAllocator<U, AllocPolicy> other;
		};

		/// ctor
		inline explicit STLAllocator()
		{ }

		/// dtor
		virtual ~STLAllocator()
		{ }

		/// copy ctor - done component wise
		inline STLAllocator(STLAllocator const&)
		{ }

		/// cast
		template <typename U>
		inline STLAllocator(STLAllocator<U, AllocPolicy> const&)
		{ }

		/// cast
		template <typename U, typename P>
		inline STLAllocator(STLAllocator<U, P> const&)
		{ }

		/// memory allocation (elements, used by STL)
		inline pointer allocate(size_type count,
			typename std::allocator<void>::const_pointer ptr = 0)
		{
			(void)ptr;
			// convert request to bytes
			register size_type sz = count*sizeof(T);
			pointer p = static_cast<pointer>(AllocPolicy::allocateBytes(sz));
			return p;
		}

		/// memory deallocation (elements, used by STL)
		inline void deallocate(pointer ptr, size_type)
		{
			// convert request to bytes, but we can't use this?
			// register size_type sz = count*sizeof( T );
			AllocPolicy::deallocateBytes(ptr);
		}

		pointer address(reference x) const
		{
			return &x;
		}

		const_pointer address(const_reference x) const
		{
			return &x;
		}

		size_type max_size() const throw()
		{
			// maximum size this can handle, delegate
			return AllocPolicy::getMaxAllocationSize();
		}

		void construct(pointer p)
		{
			// call placement new
			new(static_cast<void*>(p)) T();
		}

		void construct(pointer p, const T& val)
		{
			// call placement new
			new(static_cast<void*>(p)) T(val);
		}

		void destroy(pointer p)
		{
			// do we have to protect against non-classes here?
			// some articles suggest yes, some no
			p->~T();
		}

	};

	/// determine equality, can memory from another allocator
	/// be released by this allocator, (ISO C++)
	template<typename T, typename T2, typename P>
	inline bool operator==(STLAllocator<T, P> const&,
		STLAllocator<T2, P> const&)
	{
		// same alloc policy (P), memory can be freed
		return true;
	}

	/// determine equality, can memory from another allocator
	/// be released by this allocator, (ISO C++)
	template<typename T, typename P, typename OtherAllocator>
	inline bool operator==(STLAllocator<T, P> const&,
		OtherAllocator const&)
	{
		return false;
	}
	/// determine equality, can memory from another allocator
	/// be released by this allocator, (ISO C++)
	template<typename T, typename T2, typename P>
	inline bool operator!=(STLAllocator<T, P> const&,
		STLAllocator<T2, P> const&)
	{
		// same alloc policy (P), memory can be freed
		return false;
	}

	/// determine equality, can memory from another allocator
	/// be released by this allocator, (ISO C++)
	template<typename T, typename P, typename OtherAllocator>
	inline bool operator!=(STLAllocator<T, P> const&,
		OtherAllocator const&)
	{
		return true;
	}

}
//----------------------------------------------------------------------------

#endif