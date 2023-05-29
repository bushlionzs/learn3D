#include "OgreHeader.h"
#include "OgreDataStream.h"

namespace Ogre {

	DataStream::DataStream(const std::string& name)
	{
		mStreamName = name;
	}

	DataStream::~DataStream()
	{

	}

	uint32_t DataStream::getStreamLength()
	{
		return mSize;
	}

	String DataStream::getLine(bool trimAfter)
	{ 
		return String(); 
	}

	const char* DataStream::getStreamData()
	{ 
		return nullptr; 
	}

	const char* DataStream::getCurrentStreamData()
	{
		return nullptr;
	}
	std::string DataStream::getBaseDir()
	{
		std::string dir;
		size_t pos = mStreamName.find_last_of('/');

		if (pos == String::npos)
		{
			pos = mStreamName.find_last_of('\\');
		}

		if (pos != String::npos)
		{
			dir = mStreamName.substr(0, pos);
		}

		return dir;
	}

	String DataStream::getAsString(void)
	{
		// Read the entire buffer - ideally in one read, but if the size of
		// the buffer is unknown, do multiple fixed size reads.
		size_t bufSize = (mSize > 0 ? mSize : 4096);
		seek(0);
		String result;
		result.resize(bufSize);
		size_t nr = 0;
		char* data = result.data();
		while (!eof())
		{
			nr = read(data, bufSize);
			data += nr;
		}
		return result;
	}
}