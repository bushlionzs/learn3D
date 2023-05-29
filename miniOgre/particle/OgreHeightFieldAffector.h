/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OgreHeightFeildAffector.h
	Created:    
	Description :	
    Revision :

=============================================================================*/

#ifndef OgreHeightFeildAffector_h__
#define OgreHeightFeildAffector_h__


#include "OgreParticleAffector.h"
#include "OgreSceneQuery.h"

namespace Ogre
{
	class  HeightFieldAffector : public ParticleAffector
	{
	public:
		class CmdOffset : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		HeightFieldAffector(ParticleSystem* particleSystem);
		~HeightFieldAffector();

		virtual void	_affectParticles(ParticleSystem* pSystem, Real timeElapsed);

		Ogre::Real		getOffset() const;
		void			setOffset(Ogre::Real val);
		virtual bool loadFromStream(Serializer* pSerializer,DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		static CmdOffset ms_offsetCmd;

	protected:
		Real m_offset;
		RaySceneQuery*	m_rayQuery;
	private:
	};
}
#endif // OgreHeightFeildAffector_h__