#include "OgreHeader.h"
#include "OgreNoiseScaleAffector.h"
#include "OgreParticle.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"


namespace Ogre
{
	NoiseScaleAffector::CmdFrequency NoiseScaleAffector::ms_frequencyCmd;
	NoiseScaleAffector::CmdPersistence NoiseScaleAffector::ms_persistenceCmd;


	NoiseScaleAffector::NoiseScaleAffector( ParticleSystem* particleSystem )
		: ParticleAffector(particleSystem)
	{
		mType = "NoiseScale";

		if (createParamDictionary("NoiseScaleAffectorDictionary"))
		{
			ParamDictionary* tmpDic = getParamDictionary();

			tmpDic->addParameter(ParameterDef("frequency","Noise frequency",PT_REAL),
				&ms_frequencyCmd);
			tmpDic->addParameter(ParameterDef("persistence","Noise persistence",PT_REAL),
				&ms_persistenceCmd);
		}
	}

	void NoiseScaleAffector::_affectParticles( ParticleSystem* pSystem, Real timeElapsed )
	{
		
	}


	Ogre::Real Ogre::NoiseScaleAffector::getFrequency() const
	{
		return m_frequency;
	}

	void Ogre::NoiseScaleAffector::setFrequency( const Ogre::Real& val )
	{
		m_frequency = val;
	}

	Ogre::Real Ogre::NoiseScaleAffector::getPersistence() const
	{
		return m_persistence;
	}

	void Ogre::NoiseScaleAffector::setPersistence( const Ogre::Real& val )
	{
		m_persistence = val;
	}
	bool NoiseScaleAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_NOISE_SCALE_AFFECTOR)
			{
				pSerializer->skipChunk(stream);
				return false;
			}			
			//ÊôÐÔ
			pSerializer->readData(stream,&m_frequency,1,sizeof(m_frequency));
			pSerializer->readData(stream,&m_persistence,1,sizeof(m_persistence));
			return true;
		}
		return false;
	}
	bool NoiseScaleAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		return false;
	}
	std::size_t	NoiseScaleAffector::calcSerializedSize()
	{
		return 0;
	}

	Ogre::String NoiseScaleAffector::CmdFrequency::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const NoiseScaleAffector*>(target)->getFrequency());
	}

	void NoiseScaleAffector::CmdFrequency::doSet( void* target, const String& val )
	{
		static_cast<NoiseScaleAffector*>(target)->setFrequency(
			Ogre::StringConverter::parseReal(val));
	}

	Ogre::String NoiseScaleAffector::CmdPersistence::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const NoiseScaleAffector*>(target)->getPersistence());
	}

	void NoiseScaleAffector::CmdPersistence::doSet( void* target, const String& val )
	{
		static_cast<NoiseScaleAffector*>(target)->setPersistence(
			Ogre::StringConverter::parseReal(val));
	}
}
