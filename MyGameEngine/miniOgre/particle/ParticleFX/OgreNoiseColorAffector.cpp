#include "OgreHeader.h"
#include "OgreNoiseColorAffector.h"
#include "OgreParticle.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"


namespace Ogre
{
	NoiseColorAffector::CmdFrequency NoiseColorAffector::ms_frequencyCmd;
	NoiseColorAffector::CmdPersistence NoiseColorAffector::ms_persistenceCmd;


	NoiseColorAffector::NoiseColorAffector( ParticleSystem* particleSystem )
		: ParticleAffector(particleSystem)
	{
		mType = "NoiseColor";

		if (createParamDictionary("NoiseColorAffectorDictionary"))
		{
			ParamDictionary* tmpDic = getParamDictionary();
			
			tmpDic->addParameter(ParameterDef("frequency","Noise frequency",PT_REAL),
				&ms_frequencyCmd);
			tmpDic->addParameter(ParameterDef("persistence","Noise persistence",PT_REAL),
				&ms_persistenceCmd);
		}
	}

	void NoiseColorAffector::_affectParticles( ParticleSystem* pSystem, Real timeElapsed )
	{
		
	}


	Ogre::Real Ogre::NoiseColorAffector::getFrequency() const
	{
		return m_frequency;
	}

	void Ogre::NoiseColorAffector::setFrequency( const Ogre::Real& val )
	{
		m_frequency = val;
	}

	Ogre::Real Ogre::NoiseColorAffector::getPersistence() const
	{
		return m_persistence;
	}

	void Ogre::NoiseColorAffector::setPersistence( const Ogre::Real& val )
	{
		m_persistence = val;
	}
	bool NoiseColorAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_NOISE_COLOR_AFFECTOR)
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
	bool NoiseColorAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		return false;
	}
	std::size_t	NoiseColorAffector::calcSerializedSize()
	{
		return 0;
	}

	Ogre::String NoiseColorAffector::CmdFrequency::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const NoiseColorAffector*>(target)->getFrequency());
	}

	void NoiseColorAffector::CmdFrequency::doSet( void* target, const String& val )
	{
		static_cast<NoiseColorAffector*>(target)->setFrequency(
			Ogre::StringConverter::parseReal(val));
	}

	Ogre::String NoiseColorAffector::CmdPersistence::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const NoiseColorAffector*>(target)->getPersistence());
	}

	void NoiseColorAffector::CmdPersistence::doSet( void* target, const String& val )
	{
		static_cast<NoiseColorAffector*>(target)->setPersistence(
			Ogre::StringConverter::parseReal(val));
	}
}
