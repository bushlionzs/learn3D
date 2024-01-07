

#ifndef _CEGUIExceptions_h_
#define _CEGUIExceptions_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"



namespace CEGUI
{

class  CEGUIEXPORT Exception : public std::exception
{
public:
	
	Exception(const String& message);
	virtual ~Exception(void);

	
	const String&	getMessage(void) const		{return d_message;}

	
	virtual const char *what() const { return d_message.c_str(); }

protected:
	String	d_message;
};


class CEGUIEXPORT GenericException : public Exception
{
public:
	
	GenericException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT UnknownObjectException : public Exception
{
public:
	
	UnknownObjectException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT InvalidRequestException : public Exception
{
public:
	
	InvalidRequestException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT FileIOException : public Exception
{
public:
	
	FileIOException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT RendererException : public Exception
{
public:
	
	RendererException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT AlreadyExistsException : public Exception
{
public:
	
	AlreadyExistsException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT MemoryException : public Exception
{
public:
	
	MemoryException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT NullObjectException : public Exception
{
public:
	
	NullObjectException(const String& message) : Exception(message) {}
};


class CEGUIEXPORT ObjectInUseException : public Exception
{
public:
	
	ObjectInUseException(const String& message) : Exception(message) {}
};


} 


#endif	
