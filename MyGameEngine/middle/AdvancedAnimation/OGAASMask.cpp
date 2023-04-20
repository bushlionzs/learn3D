#include "OgreHeader.h"
#include "OGAASMask.h"
#include "OGSkeletonMeshComponent.h"
#include "OGAdvancedAnimationSystem.h"

#include "OgreStringInterface.h"
#include "OgreBone.h"
#include "OgreString.h"

namespace Orphigine
{

	AASMask::AASMask(AdvancedAnimationSystem* system)
		: m_parent(system)
	{
		m_maskedBoneHandles.clear();
	}

	AASMask::~AASMask()
	{
		m_maskedBoneHandles.clear();
	}

	String AASMask::getBonesNameVec() const
	{
		return m_bonesNameVec;
	}

	void AASMask::setBonesNameVec( String val )
	{
		m_bonesNameVec = val;

		SkeletonMeshComponent* tmpModel = m_parent->getParent();
		if(NULL == tmpModel)
			return;

		m_maskedBoneHandles.clear();

		std::vector<String> tmpBonesNameVec = Ogre::StringUtil::split(val);

		for (int i = 0;i < (int)tmpBonesNameVec.size();i ++)
		{
			String tmpBoneName = tmpBonesNameVec[i];
			
			if("" == tmpBoneName)
				continue;

			Ogre::Bone*	tmpBone = tmpModel->getBone(tmpBoneName);

			m_maskedBoneHandles.push_back(tmpBone->getBoneId());
		}
	}

	unsigned short AASMask::getNumBonesHandle() const
	{
		return (unsigned short)m_maskedBoneHandles.size();
	}

	unsigned short AASMask::getBonesHandle( unsigned short index ) const
	{
		assert((unsigned short)m_maskedBoneHandles.size() > index && "Ô½½ç AASMask::getBonesHandle");

		return m_maskedBoneHandles[index];
	}

	std::vector<unsigned short>& AASMask::getBonesHandleVec()
	{
		return m_maskedBoneHandles;
	}
	
}