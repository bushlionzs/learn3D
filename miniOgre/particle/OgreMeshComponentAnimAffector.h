#ifndef OgreMeshComponentAnimAffector_h__
#define OgreMeshComponentAnimAffector_h__

#include "OgreParticleAffector.h"
#include "OgreVector3.h"


namespace Ogre
{
	class MeshComponentAnimAffector : public ParticleAffector
	{
	public:

		class CmdAnimName : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdAnimLoop : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdAnimSpeed : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		//////////////////////////////////////////////////////////////////////////		
		static CmdAnimName	msAnimationNameCmd;
		static CmdAnimLoop	msAnimationLoopCmd;
		static CmdAnimSpeed msAnimationSpeedFactorCmd;

		/// Default constructor
		MeshComponentAnimAffector(ParticleSystem* psys);

		void setAnimName(const String& animName);
		const String& getAnimName(void) const;

		void setAnimLoop(bool loop);
		bool getAnimLoop(void) const;

		void setAnimSpeed(Real factor);
		Real getAnimSpeed(void) const;

		/** See ParticleAffector. */
		void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

		virtual bool loadFromStream(Serializer* pSerializer,DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

	protected:
		String mAnimationName;
		bool mAnimationLoop;
		Real mAnimSpeedFactor;
	};
}

#endif // OgreMeshComponentAnimAffector_h__