#include <OgreHeader.h>
#include "Ogre3DUIRenderQueue.h"
#include "OgreRenderable.h"
#include "OgreMaterial.h"
#include "OgreMaterialManager.h"


namespace CEGUI
{

	using namespace Ogre;

	Ogre3DUIRenderQueue::Ogre3DUIRenderQueue()
	{
	}
	Ogre3DUIRenderQueue::~Ogre3DUIRenderQueue()
	{
	}
	void Ogre3DUIRenderQueue::addRenderable(Renderable* r, uint32_t groupID, uint32_t priority)
	{
		mRenderables.push_back(r);
		
	}
	void Ogre3DUIRenderQueue::clear(bool destroyPassMaps)
	{
	}
	void Ogre3DUIRenderQueue::addRenderable(Renderable* pRend, uint32_t groupID)
	{
		addRenderable(pRend,0,0);
	}
	void Ogre3DUIRenderQueue::addRenderable(Renderable* pRend)
	{
		addRenderable(pRend, 0,0);
	}
	void Ogre3DUIRenderQueue::setQueueGroupVector(RenderableList *l)
	{
		
	}
}

