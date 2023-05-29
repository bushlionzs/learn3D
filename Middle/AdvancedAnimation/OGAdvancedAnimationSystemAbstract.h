#ifndef OGAdvancedAnimationSystemAbstract_h__
#define OGAdvancedAnimationSystemAbstract_h__


#include "OGAASCommon.h"
#include "OgreResource.h"
#include "OgreResourceManager.h"
#include "OgreIteratorWrapper.h"
#include "OGAASAnimation.h"

namespace Orphigine
{
	class AASAnimation;

	class AdvancedAnimationSystemAbstract : public Ogre::Resource
	{
	protected:
		AdvancedAnimationSystemAbstract(Ogre::ResourceManager* creator, const String& name, 
			Ogre::ResourceHandle handle,const String& group, bool isManual, Ogre::ManualResourceLoader* loader);
		AdvancedAnimationSystemAbstract();

		virtual ~AdvancedAnimationSystemAbstract();


	protected:
		AASAnimationVector	m_animations;		
		AnimationIndexMap	m_animationIndexMap;

	public:
		typedef		Ogre::VectorIterator< AASAnimationVector >	AnimationsIterator;
		AnimationsIterator			getAnimationsIterator();

		typedef		Ogre::MapIterator< AnimationIndexMap >	AnimationIndexMapIterator;
		AnimationIndexMapIterator	getAnimationsIndexMapIterator();

	private:
	};
}
#endif // OGAdvancedAnimationSystemAbstract_h__