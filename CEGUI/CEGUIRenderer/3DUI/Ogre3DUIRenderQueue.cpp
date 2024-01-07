
#include "Ogre3DUIRenderQueue.h"
#include "OgreRenderable.h"
#include "OgreMaterial.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreMaterialManager.h"


namespace CEGUI
{

	using namespace Ogre;

	Ogre3DUIRenderQueue::Ogre3DUIRenderQueue()
	{
		mRenderableList = 0;
	}
	Ogre3DUIRenderQueue::~Ogre3DUIRenderQueue()
	{
	}
	void Ogre3DUIRenderQueue::addRenderable(Renderable* rend, uint8 groupID, ushort priority)
	{
		Technique* pTech;

		if (!rend->getMaterial().isNull())
			rend->getMaterial()->touch();

		if(rend->getMaterial().isNull() || !rend->getTechnique())
		{
			MaterialPtr baseWhite = MaterialManager::getSingleton().getByName("BaseWhite");
			pTech = baseWhite->getTechnique(0);
		}
		else
		{
			pTech = rend->getTechnique();
		}
		
		assert(mRenderableList);

		Technique::PassIterator p = pTech->getPassIterator();
		while (p.hasMoreElements())
		{
			Pass* pass = p.getNext();
			mRenderableList->push_back(RenderablePass(rend, pass));
		}
		
	}
	void Ogre3DUIRenderQueue::clear(bool destroyPassMaps)
	{
	}
	void Ogre3DUIRenderQueue::addRenderable(Renderable* pRend, uint8 groupID)
	{
		addRenderable(pRend,0,0);
	}
	void Ogre3DUIRenderQueue::addRenderable(Renderable* pRend)
	{
		addRenderable(pRend, 0,0);
	}
	void Ogre3DUIRenderQueue::setQueueGroupVector(RenderableList *l)
	{
		mRenderableList = l;
	}
}

