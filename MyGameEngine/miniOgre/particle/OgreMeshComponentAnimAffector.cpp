#include "OgreHeader.h"
#include "OgreMeshComponentAnimAffector.h"
#include "OgreParticleSystem.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreMeshComponentParticleVisualData.h"
#include "OgreSerializer.h"
#include "platform_log.h"
#include "OgreString.h"

namespace Ogre 
{
	MeshComponentAnimAffector::CmdAnimName	MeshComponentAnimAffector::msAnimationNameCmd;
	MeshComponentAnimAffector::CmdAnimLoop	MeshComponentAnimAffector::msAnimationLoopCmd;
	MeshComponentAnimAffector::CmdAnimSpeed	MeshComponentAnimAffector::msAnimationSpeedFactorCmd;

	//-----------------------------------------------------------------------
	MeshComponentAnimAffector::MeshComponentAnimAffector(ParticleSystem* psys)
		:ParticleAffector(psys),
		mAnimationName(""),
		mAnimationLoop(false),
		mAnimSpeedFactor(1.0f)
	{
		mType = "MeshAnimationAffector";

		if (createParamDictionary("MeshComponentAnimAffector"))
		{
			ParamDictionary* dict = getParamDictionary();

			dict->addParameter(ParameterDef("animation_name", 
				"the name of the animation.", PT_STRING),
				&msAnimationNameCmd);

			dict->addParameter(ParameterDef("animation_speed", 
				"set the speed factor of the animation.", PT_REAL),
				&msAnimationSpeedFactorCmd);		

			dict->addParameter(ParameterDef("animation_loop", 
				"Is the animation looping.", PT_BOOL),
				&msAnimationLoopCmd);	
		}
	}
	//-----------------------------------------------------------------------
	///*
	char * MeshComponentAnimAffector::readFromBuffer(char * pCurrent)
	{

		StringUtil::loadStringFromMemory(mAnimationName,pCurrent);

		unsigned int length = sizeof(int) + sizeof(Real);
		memcpy(&mAnimationLoop,pCurrent,length);
		pCurrent += length;

		return pCurrent;
	}	
	void MeshComponentAnimAffector::saveToFile(std::ofstream & of)
	{
		StringUtil::saveStringToStream(mAnimationName,of);

		int length = sizeof(int) + sizeof(Ogre::Real);
		of.write((const char *)(&mAnimationLoop),length);
	}
	//*/
	bool MeshComponentAnimAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_MESH_ANIMATION_AFFECTOR)
			{
				WARNING_LOG("Load MeshComponentAnimAffector From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}			
			//属性
			mAnimationName=pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mAnimationLoop,1,sizeof(mAnimationLoop));
			pSerializer->readData(stream,&mAnimSpeedFactor,1,sizeof(mAnimSpeedFactor));
			return true;
		}
		return false;
	}
	bool MeshComponentAnimAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	MeshComponentAnimAffector::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//属性
		tmpSize += mAnimationName.length() + 1 ;
		tmpSize += sizeof(mAnimationLoop);
		tmpSize += sizeof(mAnimSpeedFactor);
		return tmpSize;
	}

	void MeshComponentAnimAffector::setAnimName( const String& animName )
	{
		mAnimationName = animName;
	}

	const String& MeshComponentAnimAffector::getAnimName( void ) const
	{
		return mAnimationName;
	}

	void MeshComponentAnimAffector::setAnimLoop( bool loop )
	{
		mAnimationLoop = loop;
	}

	bool MeshComponentAnimAffector::getAnimLoop( void ) const
	{
		return mAnimationLoop;
	}

	void MeshComponentAnimAffector::setAnimSpeed( Real factor )
	{
		mAnimSpeedFactor = factor;
	}

	Ogre::Real MeshComponentAnimAffector::getAnimSpeed( void ) const
	{
		return mAnimSpeedFactor;
	}
	//-----------------------------------------------------------------------
	void MeshComponentAnimAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
	{
		Particle *p;


		const std::vector<Particle*>&  particles = pSystem->_getActiveParticles();
		for(auto pi = particles.begin(); pi != particles.end(); pi++)
		{
			p = *pi;

			MeshComponentParticleVisualData *data = static_cast<MeshComponentParticleVisualData *>(p->getVisualData());
			data->mAnimationName = mAnimationName;
			data->mDeltaTime = timeElapsed;
			data->mAnimationLoop = mAnimationLoop;
			data->mAnimSpeedFactor = mAnimSpeedFactor;
			data->mAnimationUpdated = true;
		}
	}
	//-----------------------------------------------------------------------
	String MeshComponentAnimAffector::CmdAnimName::doGet(const void* target) const
	{
		return static_cast<const MeshComponentAnimAffector*>(target)->getAnimName();
	}
	void MeshComponentAnimAffector::CmdAnimName::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentAnimAffector*>(target)->setAnimName(val);
	}
	//-----------------------------------------------------------------------
	String MeshComponentAnimAffector::CmdAnimLoop::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentAnimAffector*>(target)->getAnimLoop() );
	}
	void MeshComponentAnimAffector::CmdAnimLoop::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentAnimAffector*>(target)->setAnimLoop(StringConverter::parseBool(val));
	}
	//-----------------------------------------------------------------------
	String MeshComponentAnimAffector::CmdAnimSpeed::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentAnimAffector*>(target)->getAnimSpeed() );
	}
	void MeshComponentAnimAffector::CmdAnimSpeed::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentAnimAffector*>(target)->setAnimSpeed(StringConverter::parseReal(val));
	}
}

