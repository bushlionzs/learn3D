#include "OgreHeader.h"
#include "OGAdvancedAnimationSystemAbstract.h"

namespace Orphigine
{


	AdvancedAnimationSystemAbstract::AdvancedAnimationSystemAbstract(Ogre::ResourceManager* creator, const String& name, 
		Ogre::ResourceHandle handle,const String& group, bool isManual, Ogre::ManualResourceLoader* loader)
		: Resource(creator,name,handle,group,isManual,loader)
	{
		m_animations.clear();
		m_animationIndexMap.clear();
	}

	AdvancedAnimationSystemAbstract::AdvancedAnimationSystemAbstract()
	{
		m_animations.clear();
		m_animationIndexMap.clear();
	}
	AdvancedAnimationSystemAbstract::~AdvancedAnimationSystemAbstract()
	{
		
	}

	AdvancedAnimationSystemAbstract::AnimationsIterator AdvancedAnimationSystemAbstract::getAnimationsIterator()
	{
		return	AdvancedAnimationSystemAbstract::AnimationsIterator(m_animations.begin(),m_animations.end());
	}

	AdvancedAnimationSystemAbstract::AnimationIndexMapIterator AdvancedAnimationSystemAbstract::getAnimationsIndexMapIterator()
	{
		return AdvancedAnimationSystemAbstract::AnimationIndexMapIterator(m_animationIndexMap.begin(),m_animationIndexMap.end());
	}
}