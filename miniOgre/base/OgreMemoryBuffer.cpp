#include "OgreHeader.h"
#include "OgreMemoryBuffer.h"

namespace Ogre
{
	MemoryBuffer::MemoryBuffer(uint32_t vertexSize, uint32_t numVerts)
	{
		mVertexSize = vertexSize;
		mNumVerts = numVerts;
		mSizeInBytes = vertexSize * numVerts;
		mData = (char*)malloc(mSizeInBytes);
	}

	MemoryBuffer::~MemoryBuffer()
	{
		delete mData;
	}

    void* MemoryBuffer::lockimpl(size_t offset, size_t length, LockOptions options)
	{
		return mData;
	}
}