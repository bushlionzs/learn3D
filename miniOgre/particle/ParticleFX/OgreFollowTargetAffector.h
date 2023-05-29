#ifndef OgreFollowTargetAffector_h__
#define OgreFollowTargetAffector_h__

#include "OgreParticleAffector.h"

namespace Ogre
{
	class   FollowTargetAffector : public ParticleAffector
	{
	public:
		class CmdDistanceConstraint : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdDelayTime : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdTargetNodeName : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		FollowTargetAffector(ParticleSystem* particleSystem);

		virtual void	_affectParticles(ParticleSystem* pSystem, Real timeElapsed);

		Ogre::Real		getDistanceContraint() const;
		void			setDistanceConstraint(Ogre::Real val);

		Ogre::Real		getDelayTime() const;
		void			setDelayTime(Ogre::Real val);

		Ogre::String	getTargetNodeName() const;
		void			setTargetNodeName(Ogre::String val);
		virtual bool loadFromStream(Serializer* pSerializer,DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		static CmdDistanceConstraint ms_distanceCmd;
		static CmdDelayTime ms_delayTime;
		static CmdTargetNodeName ms_targetNodeName;

	protected:
		Real m_distanceConstraint;
		Real m_delayTime;
		String m_targetNodeName;

	private:
	};
}

#endif // OgreFollowTargetAffector_h__
