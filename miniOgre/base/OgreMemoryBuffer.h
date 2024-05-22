#pragma once
#include "OgreHardwareBuffer.h"

namespace Ogre {
	class MemoryBuffer : public HardwareBuffer
	{
	public:
		MemoryBuffer(uint32_t vertexSize, uint32_t numVerts);
		~MemoryBuffer();
		virtual void* lockimpl(size_t offset, size_t length, LockOptions options) ;
		virtual void unlock() {}
	private:
		char* mData;
	};
}