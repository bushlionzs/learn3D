/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OgreHeightFeildAffectorFactory.h
	Created:    
	Description :	
    Revision :

=============================================================================*/

#ifndef OgreHeightFeildAffectorFactory_h__
#define OgreHeightFeildAffectorFactory_h__


#include "OgreParticleAffector.h"
#include "OgreParticleAffectorFactory.h"
#include "OgreHeightFieldAffector.h"


namespace Ogre
{

	class  HeightFieldAffectorFactory : public ParticleAffectorFactory
	{
	public:
		virtual String getName() const
		{
			return "HeightField";
		}

		virtual ParticleAffector* createAffector(ParticleSystem* psys)
		{
			ParticleAffector* tmpParticleAffector = NULL;
			tmpParticleAffector = OGRE_NEW HeightFieldAffector(psys);
			mAffectors.push_back(tmpParticleAffector);

			return tmpParticleAffector;
		}

	protected:
		
	private:
	};
}
#endif // OgreHeightFeildAffectorFactory_h__