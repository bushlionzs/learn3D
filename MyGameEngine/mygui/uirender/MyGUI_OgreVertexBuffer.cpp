/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
#include "OgreHeader.h"
#include "MyGUI_OgreVertexBuffer.h"

#include <OgreHardwareBufferManager.h>
#include "vertex_declaration.h"
#include "vertex_data.h"
#include "index_data.h"

namespace MyGUI
{

	const size_t VERTEX_BUFFER_REALLOCK_STEP = 5 * VertexQuad::VertexCount;

	OgreVertexBuffer::OgreVertexBuffer() :
		mVertexCount(0),
		mNeedVertexCount(0)
	{
	}

	OgreVertexBuffer::~OgreVertexBuffer()
	{
		destroy();
	}

	void OgreVertexBuffer::create()
	{
		auto vertexData = new VertexData();
		mRenderOperation.vertexData = vertexData;
		mRenderOperation.vertexData->vertexStart = 0;

		VertexDeclaration* vd = mRenderOperation.vertexData->vertexDeclaration;
		vd->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
		vd->addElement(0, 0, VertexElement::getTypeSize(VET_FLOAT3), VET_COLOUR, VES_DIFFUSE);
		vd->addElement(
			0,
			0,
			VertexElement::getTypeSize(VET_FLOAT3) + VertexElement::getTypeSize(VET_COLOUR),
			VET_FLOAT2,
			VES_TEXTURE_COORDINATES);

		vertexData->vertexSlotInfo.emplace_back();

		auto& slotInfo = vertexData->vertexSlotInfo.back();
		slotInfo.slot = 0;
		slotInfo.vertexSize = vd->getVertexSize(0);
		vertexData->vertexCount = mVertexCount;
		slotInfo.createBuffer(slotInfo.vertexSize, mVertexCount);

		/*mVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			mRenderOperation.vertexData->vertexDeclaration->getVertexSize(0), 
			mVertexCount,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);*/

		

		mRenderOperation.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		mRenderOperation.useIndexes = false;
	}

	void OgreVertexBuffer::destroy()
	{
		delete mRenderOperation.vertexData;
		mRenderOperation.vertexData = nullptr;
	}

	void OgreVertexBuffer::resize()
	{
		mVertexCount = mNeedVertexCount + VERTEX_BUFFER_REALLOCK_STEP;
		destroy();
		create();
	}

	void OgreVertexBuffer::setVertexCount(size_t _count)
	{
		if (_count == 3246)
		{
			int kk = 0;
		}
		mNeedVertexCount = _count;
	}

	size_t OgreVertexBuffer::getVertexCount() const
	{
		return mNeedVertexCount;
	}

	Vertex* OgreVertexBuffer::lock()
	{
		if (mNeedVertexCount > mVertexCount || mVertexCount == 0)
		{
			if (mVertexCount != 0)
			{
				int kk = 0;
			}
			resize();
		}
			

		auto& slotInfo = mRenderOperation.vertexData->vertexSlotInfo.back();
		return reinterpret_cast<Vertex*>(slotInfo.hardwareVertexBuffer->lock(Ogre::HardwareVertexBuffer::HBL_DISCARD));
	}

	void OgreVertexBuffer::unlock()
	{
		auto& slotInfo = mRenderOperation.vertexData->vertexSlotInfo.back();
		slotInfo.hardwareVertexBuffer->unlock();
	}

} // namespace MyGUI
