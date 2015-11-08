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
#ifndef __ExceptionManager_h__
#define __ExceptionManager_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include <exception>
//----------------------------------------------------------------------------

namespace ChiikaApi
{
	class MalApiExport Exception : std::exception
	{
	protected:
		long line;
		int number;
		ChiString typeName;
		ChiString description;
		ChiString source;
		ChiString file;
		mutable ChiString fullDesc;
	public:
		enum ExceptionCodes
		{
			ERR_CANNOT_WRITE_TO_FILE,
			ERR_INVALID_STATE,
			ERR_INVALIDPARAMS,
			ERR_DUPLICATE_ITEM,
			ERR_ITEM_NOT_FOUND,
			ERR_FILE_NOT_FOUND,
			ERR_INTERNAL_ERROR,
			ERR_RT_ASSERTION_FAILED,
			ERR_NOT_IMPLEMENTED,
			ERR_XML_PARSING,
			ERR_THREADING
		};

		Exception(int number,const ChiString& description,const ChiString& source);

		/** Advanced constructor.
		*/
		Exception(int number,const ChiString& description,const ChiString& source,const char* type,const char* file,long line);

		/** Copy constructor.
		*/
		Exception(const Exception& rhs);

		/// Needed for compatibility with std::exception
		~Exception() throw() {}

		/** Assignment operator.
		*/
		void operator = (const Exception& rhs);

		/** Returns a ChiString with the full description of this error.
			@remarks
			The description contains the error number, the description
			supplied by the thrower, what routine threw the exception,
			and will also supply extra platform-specific information
			where applicable. For example - in the case of a rendering
			library error, the description of the error will include both
			the place in which OGRE found the problem, and a text
			description from the 3D rendering library, if available.
			*/
		virtual const ChiString& getFullDescription(void) const;

		/** Gets the error code.
		*/
		virtual int getNumber(void) const throw();

		/** Gets the source function.
		*/
		virtual const ChiString &getSource() const { return source; }

		/** Gets source file name.
		*/
		virtual const ChiString &getFile() const { return file; }

		/** Gets line number.
		*/
		virtual long getLine() const { return line; }

		/** Returns a ChiString with only the 'description' field of this exception. Use
			getFullDescriptionto get a full description of the error including line number,
			error number and what function threw the exception.
			*/
		virtual const ChiString &getDescription(void) const { return description; }

		/// Override std::exception::what
		const char* what() const throw() { return getFullDescription().c_str(); }
	};

	//From 'Modern C++ Design' (Alexandrescu 2001).
	template <int num>
	struct ExceptionCodeType
	{
		enum { number = num };
	};

	class MalApiExport UnimplementedException : public Exception
	{
	public:
		UnimplementedException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"UnimplementedException",inFile,inLine) {}
	};
	class MalApiExport FileNotFoundException : public Exception
	{
	public:
		FileNotFoundException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"FileNotFoundException",inFile,inLine) {}
	};
	class MalApiExport IOException : public Exception
	{
	public:
		IOException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"IOException",inFile,inLine) {}
	};
	class MalApiExport InvalidStateException : public Exception
	{
	public:
		InvalidStateException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"InvalidStateException",inFile,inLine) {}
	};
	class MalApiExport InvalidParametersException : public Exception
	{
	public:
		InvalidParametersException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"InvalidParametersException",inFile,inLine) {}
	};
	class MalApiExport ItemIdentityException : public Exception
	{
	public:
		ItemIdentityException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"ItemIdentityException",inFile,inLine) {}
	};
	class MalApiExport InternalErrorException : public Exception
	{
	public:
		InternalErrorException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"InternalErrorException",inFile,inLine) {}
	};
	class MalApiExport RuntimeAssertionException : public Exception
	{
	public:
		RuntimeAssertionException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"RuntimeAssertionException",inFile,inLine) {}
	};
	class MalApiExport XMLParsingException : public Exception
	{
	public:
		XMLParsingException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"XMLParsingException",inFile,inLine) {}
	};
	class MalApiExport ThreadingException : public Exception
	{
	public:
		ThreadingException(int inNumber,const ChiString& inDescription,const ChiString& inSource,const char* inFile,long inLine)
			: Exception(inNumber,inDescription,inSource,"ThreadingException",inFile,inLine) {}
	};
	class ExceptionFactory
	{
	private:
		/// Private constructor, no construction
		ExceptionFactory() {}
	public:
		static UnimplementedException create(
			ExceptionCodeType<Exception::ERR_NOT_IMPLEMENTED> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return UnimplementedException(code.number,desc,src,file,line);
		}
		static FileNotFoundException create(
			ExceptionCodeType<Exception::ERR_FILE_NOT_FOUND> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return FileNotFoundException(code.number,desc,src,file,line);
		}
		static IOException create(
			ExceptionCodeType<Exception::ERR_CANNOT_WRITE_TO_FILE> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return IOException(code.number,desc,src,file,line);
		}
		static InvalidStateException create(
			ExceptionCodeType<Exception::ERR_INVALID_STATE> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return InvalidStateException(code.number,desc,src,file,line);
		}
		static InvalidParametersException create(
			ExceptionCodeType<Exception::ERR_INVALIDPARAMS> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return InvalidParametersException(code.number,desc,src,file,line);
		}
		static ItemIdentityException create(
			ExceptionCodeType<Exception::ERR_ITEM_NOT_FOUND> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return ItemIdentityException(code.number,desc,src,file,line);
		}
		static ItemIdentityException create(
			ExceptionCodeType<Exception::ERR_DUPLICATE_ITEM> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return ItemIdentityException(code.number,desc,src,file,line);
		}
		static InternalErrorException create(
			ExceptionCodeType<Exception::ERR_INTERNAL_ERROR> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return InternalErrorException(code.number,desc,src,file,line);
		}
		static RuntimeAssertionException create(
			ExceptionCodeType<Exception::ERR_RT_ASSERTION_FAILED> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return RuntimeAssertionException(code.number,desc,src,file,line);
		}
		static XMLParsingException create(ExceptionCodeType<Exception::ERR_XML_PARSING> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return XMLParsingException(code.number,desc,src,file,line);
		}
		static ThreadingException create(ExceptionCodeType<Exception::ERR_THREADING> code,
			const ChiString& desc,
			const ChiString& src,const char* file,long line)
		{
			return ThreadingException(code.number,desc,src,file,line);
		}

	};

#ifndef CHIKA_EXCEPTION
#define CHIKA_EXCEPTION(num, desc, src) throw ChiikaApi::ExceptionFactory::create( \
	ChiikaApi::ExceptionCodeType<num>(), desc, src, __FILE__, __LINE__ );
#endif
}
#endif
//----------------------------------------------------------------------------