/********************************************************************
Copyright (c) 2010 Beijing Kylin Network Information 
Science and Technology Co, Ltd. All Rights Reserved.
author:		changhao

purpose:	
*********************************************************************/

//第二层纹理坐标动画
#include "OgreHeader.h"
#include "OgreTexture2PosInterpolatorAffector.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"
#include "OgreParticle.h"
#include "OgreParticleSystemRenderer.h"
#include "OgreMaterialManager.h"
#include "OgreTextureUnit.h"

namespace Ogre {
    
    // init statics
    Texture2PosInterpolatorAffector::CmdTexturePosAdjust		Texture2PosInterpolatorAffector::msTexturePosCmd[MAX_STAGES];
    Texture2PosInterpolatorAffector::CmdTimeAdjust		Texture2PosInterpolatorAffector::msTimeCmd[MAX_STAGES];

    //-----------------------------------------------------------------------
    Texture2PosInterpolatorAffector::Texture2PosInterpolatorAffector(ParticleSystem* psys)
        : ParticleAffector(psys)
    {
		for (int i=0;i<MAX_STAGES;i++)
		{
			mTexturePos[i]	= Vector3::ZERO;
			mTimeAdj[i]		= 1.0f;
		}

        mType = "Texture2PosInterpolator";

        // Init parameters
        if (createParamDictionary("Texture2PosInterpolatorAffector"))
        {
            ParamDictionary* dict = getParamDictionary();

			for (int i=0;i<MAX_STAGES;i++)
			{
				msTexturePosCmd[i].mIndex	= i;
				msTimeCmd[i].mIndex		= i;

				std::stringstream stage;
				stage << i;
				String	pos_title	= String("pos") + stage.str();
				String	time_title		= String("time") + stage.str();
				String	pos_descr	= String("Stage ") + stage.str() + String(" pos.");
				String	time_descr		= String("Stage ") + stage.str() + String(" time.");

				dict->addParameter(ParameterDef(pos_title, pos_descr, PT_VECTOR3), &msTexturePosCmd[i]);
				dict->addParameter(ParameterDef(time_title, time_descr,   PT_REAL), &msTimeCmd[i]);
			}
        }
    }
    //-----------------------------------------------------------------------
    void Texture2PosInterpolatorAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
    {
        Particle*			p;
		const std::vector<Particle*>& particles = pSystem->_getActiveParticles();

		for (auto it = particles.begin(); it != particles.end(); it++)
        {
            p = *it;
			const Real		life_time		= p->mTotalTimeToLive;
			Real			particle_time	= 1.0f - (p->mTimeToLive / life_time);

			float u = 0.0f;
			float v = 0.0f;

			if (particle_time <= mTimeAdj[0])
			{
				u = mTexturePos[0].x;
				v = mTexturePos[0].y;
			} 
			else if (particle_time >= mTimeAdj[MAX_STAGES - 1])
			{
				u = mTexturePos[MAX_STAGES-1].x;
				v = mTexturePos[MAX_STAGES-1].y;
			}
			else
			{
				for (int i=0;i<MAX_STAGES-1;i++)
				{
					if (particle_time >= mTimeAdj[i] && particle_time < mTimeAdj[i + 1])
					{
						particle_time -= mTimeAdj[i];
						particle_time /= (mTimeAdj[i+1]-mTimeAdj[i]);
						u = ((mTexturePos[i+1].x * particle_time) + (mTexturePos[i].x * (1.0f - particle_time)));
						v = ((mTexturePos[i+1].y * particle_time) + (mTexturePos[i].y * (1.0f - particle_time)));
	
						break;
					}
				}
			}

			if (pSystem->getRenderer())
			{
				Ogre::String name = pSystem->getRenderer()->_getMaterialName();
				if (!name.empty())
				{
					auto mat = MaterialManager::getSingleton().getByName(name);
					if (mat)
					{
						auto texUnit = mat->getTextureUnit(1);
						texUnit->setTextureScroll(u, v);
					}
				}
			}
		}
    }
    
	//-----------------------------------------------------------------------
	void Texture2PosInterpolatorAffector::setPosAdjust(size_t index, const Ogre::Vector3& pos)
    {
        mTexturePos[index] = pos;
    }
    //-----------------------------------------------------------------------
	Ogre::Vector3 Texture2PosInterpolatorAffector::getPosAdjust(size_t index) const
    {
        return mTexturePos[index];
    }


    //-----------------------------------------------------------------------
    void Texture2PosInterpolatorAffector::setTimeAdjust(size_t index, Real time)
    {
        mTimeAdj[index] = time;
    }
    //-----------------------------------------------------------------------
    Real Texture2PosInterpolatorAffector::getTimeAdjust(size_t index) const
    {
        return mTimeAdj[index];
    }
	///*
	char * Texture2PosInterpolatorAffector::readFromBuffer( char * pCurrent )
	{
		std::size_t chunkSize = sizeof(Ogre::ColourValue) * MAX_STAGES + 
			sizeof(Real) * MAX_STAGES;

		memcpy(&mTexturePos,pCurrent,chunkSize);
		pCurrent += chunkSize;

		return pCurrent;
	}

	void Texture2PosInterpolatorAffector::saveToFile( std::ofstream & of )
	{
		/*of.write((const char*)&mTexturePos,sizeof(Ogre::ColourValue) * MAX_STAGES + 
			sizeof(Real) * MAX_STAGES);*/
	}
	//*/
	bool Texture2PosInterpolatorAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_COLOUR_INTERPOLATOR_AFFECTOR)
			{
				pSerializer->skipChunk(stream);
				return false;
			}			
			//属性
			pSerializer->readData(stream,mTexturePos,1,MAX_STAGES * sizeof(ColourValue));
			pSerializer->readData(stream,mTimeAdj,1,MAX_STAGES * sizeof(Real));
			return true;
		}
		return false;
	}
	bool Texture2PosInterpolatorAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	Texture2PosInterpolatorAffector::calcSerializedSize()
	{
		return 0;
	}
    
	//-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    // Command objects
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    String Texture2PosInterpolatorAffector::CmdTexturePosAdjust::doGet(const void* target) const
    {
        return StringConverter::toString(static_cast<const Texture2PosInterpolatorAffector*>(target)->getPosAdjust(mIndex) );
    }
    void Texture2PosInterpolatorAffector::CmdTexturePosAdjust::doSet(void* target, const String& val)
    {
		Texture2PosInterpolatorAffector* pAffector = (Texture2PosInterpolatorAffector*)target;
        pAffector->setPosAdjust(mIndex, StringConverter::parseVector3(val));
    }

#if OGRE_STRING_INTERFACE_COPY
    void Texture2PosInterpolatorAffector::CmdTexturePosAdjust::doCopy(void* target, const void* source)
    {
        static_cast<Texture2PosInterpolatorAffector*>(target)->setPosAdjust(mIndex,
            static_cast<const Texture2PosInterpolatorAffector*>(source)->getPosAdjust(mIndex));
    }
#endif
	//-----------------------------------------------------------------------
    String Texture2PosInterpolatorAffector::CmdTimeAdjust::doGet(const void* target) const
    {
        return StringConverter::toString(static_cast<const Texture2PosInterpolatorAffector*>(target)->getTimeAdjust(mIndex) );
    }
    void Texture2PosInterpolatorAffector::CmdTimeAdjust::doSet(void* target, const String& val)
    {
        static_cast<Texture2PosInterpolatorAffector*>(target)->setTimeAdjust(mIndex,
            StringConverter::parseReal(val));
    }
#if OGRE_STRING_INTERFACE_COPY
    void Texture2PosInterpolatorAffector::CmdTimeAdjust::doCopy(void* target, const void* source)
    {
        static_cast<Texture2PosInterpolatorAffector*>(target)->setTimeAdjust(mIndex,
            static_cast<const Texture2PosInterpolatorAffector*>(source)->getTimeAdjust(mIndex));
    }
#endif

}



