#ifndef OgreNoiseScaleAffector_h__
#define OgreNoiseScaleAffector_h__


#include "OgreParticleAffector.h"


namespace Ogre
{
	class   NoiseScaleAffector : public ParticleAffector
	{
	public:
		class CmdFrequency : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdPersistence : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		NoiseScaleAffector(ParticleSystem* particleSystem);

		virtual void	_affectParticles(ParticleSystem* pSystem, Real timeElapsed);

		Ogre::Real		getFrequency() const;
		void			setFrequency(const Ogre::Real& val);

		Ogre::Real		getPersistence() const;
		void			setPersistence(const Ogre::Real& val);
		virtual bool loadFromStream(Serializer* pSerializer,DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		static CmdFrequency ms_frequencyCmd;
		static CmdPersistence ms_persistenceCmd;
	protected:
		Ogre::Real			m_frequency;
		Ogre::Real			m_persistence;
	private:
	};
}
#endif // OgreNoiseScaleAffector_h__