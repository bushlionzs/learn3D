

#ifndef __Ogre3DUIRenderQueue_H__
#define __Ogre3DUIRenderQueue_H__

#include "OgreRenderable.h"


namespace CEGUI 
{
	class Ogre3DUIRenderQueue
	{
	public:
		struct RenderablePass
		{
			Ogre::Renderable* renderable;
			RenderablePass(Ogre::Renderable* rend) :renderable(rend){}
		};

		typedef std::vector<RenderablePass> RenderableList;

	public:
		Ogre3DUIRenderQueue();
		virtual ~Ogre3DUIRenderQueue();
		void clear(bool destroyPassMaps = false);
		virtual void addRenderable(Ogre::Renderable* pRend, uint32_t groupID, Ogre::ushort priority);
		virtual void addRenderable(Ogre::Renderable* pRend, uint32_t groupId);
		virtual void addRenderable(Ogre::Renderable* pRend);
		void setQueueGroupVector(RenderableList *l);
	private:
		RenderableList *mRenderableList;
	};
}


#endif