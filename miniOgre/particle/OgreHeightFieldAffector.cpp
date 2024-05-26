/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OgreHeightFeildAffector.cpp
	Created:    
	Description :	
    Revision :

=============================================================================*/
#include "OgreHeader.h"
#include "OgreHeightFieldAffector.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"
#include "OgreParticle.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreSerializer.h"
#include "platform_log.h"
namespace Ogre
{
	HeightFieldAffector::CmdOffset HeightFieldAffector::ms_offsetCmd;

	HeightFieldAffector::HeightFieldAffector(ParticleSystem* particleSystem)
		: ParticleAffector(particleSystem)
	{
		mType = "HeightField";
		m_offset = 0;

		if (createParamDictionary("HeightFieldAffector"))
		{
			ParamDictionary* tmpDictionary = getParamDictionary();

			tmpDictionary->addParameter(
				ParameterDef("offset","Per particle is constrainted by heightField",PT_REAL),&ms_offsetCmd);

		}

		SceneManager* tmpManager = NULL;
		tmpManager = Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);
		if(NULL != tmpManager)
			m_rayQuery = tmpManager->createRayQuery(Ray());
	}

	HeightFieldAffector::~HeightFieldAffector()
	{
		delete m_rayQuery;
		m_rayQuery = NULL;
	}


	void HeightFieldAffector::_affectParticles( ParticleSystem* pSystem, Real timeElapsed )
	{
		Particle* tmpParticle = NULL;

		static Ray tmpRay;
		

		const std::vector<Particle*>& particles = pSystem->_getActiveParticles();
		for(auto it = particles.begin(); it != particles.end(); it++)
		{
			tmpParticle = *it;
			
			Vector3 tmpParticlePos = tmpParticle->mPosition;
			tmpParticlePos.y = 10000;

			tmpRay.setOrigin(tmpParticlePos);
			tmpRay.setDirection(Vector3::NEGATIVE_UNIT_Y);

			Vector3 tmpIntersectsPos = Vector3(0.0f,0.0f,0.0f);
			assert(false);
			//EngineManager::getSingleton().getTerrainIntersects(tmpRay, tmpIntersectsPos);

			tmpParticle->mPosition = Vector3(tmpParticle->mPosition.x,
				tmpIntersectsPos.y + m_offset,//加上偏移需求
				tmpParticle->mPosition.z);
		}
	}
	//-----------------------------------------------------------------------
	///*
	char * HeightFieldAffector::readFromBuffer(char * pCurrent)
	{
		int length = sizeof(Real);
		memcpy(&m_offset,pCurrent,length);
		pCurrent += length;
		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void HeightFieldAffector::saveToFile(std::ofstream & of)
	{
		of.write((const char *)(&m_offset),sizeof(Real));
	}
	//*/
	bool HeightFieldAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_HEIGHT_FIELD_AFFECTOR)
			{
				WARNING_LOG("Load HeightFieldAffector From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}			
			//属性
			pSerializer->readData(stream,&m_offset,1,sizeof(m_offset));
			return true;
		}
		return false;
	}
	bool HeightFieldAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	HeightFieldAffector::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//属性
		tmpSize += sizeof(m_offset);
		return tmpSize;
	}
	Ogre::Real HeightFieldAffector::getOffset() const
	{
		return m_offset;
	}

	void HeightFieldAffector::setOffset( Ogre::Real val )
	{
		m_offset = val;
	}


	/*
	 *	Command 对象
	 */
	Ogre::String HeightFieldAffector::CmdOffset::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const HeightFieldAffector*>(target)->getOffset());
	}

	void HeightFieldAffector::CmdOffset::doSet( void* target, const String& val )
	{
		static_cast<HeightFieldAffector*>(target)->setOffset(Ogre::StringConverter::parseReal(val));
	}
}