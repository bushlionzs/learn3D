/********************************************************************
Copyright (c) 2010 Beijing Kylin Network Information 
Science and Technology Co, Ltd. All Rights Reserved.
author:		changhao

purpose:	
*********************************************************************/

//第二层纹理缩放动画
#include "OgreHeader.h"
#include "OgreTexture2ScaleInterpolatorAffector.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"
#include "OgreParticle.h"
#include "OgreParticleSystemRenderer.h"
#include "OgreMaterialManager.h"
#include "OgreTextureUnit.h"

namespace Ogre {
    
    // init statics
    Texture2ScaleInterpolatorAffector::CmdTextureScaleAdjust		Texture2ScaleInterpolatorAffector::msTextureScaleCmd[MAX_STAGES];
    Texture2ScaleInterpolatorAffector::CmdTimeAdjust		Texture2ScaleInterpolatorAffector::msTimeCmd[MAX_STAGES];

    //-----------------------------------------------------------------------
    Texture2ScaleInterpolatorAffector::Texture2ScaleInterpolatorAffector(ParticleSystem* psys)
        : ParticleAffector(psys)
    {
		for (int i=0;i<MAX_STAGES;i++)
		{
			mTextureScale[i]	= Vector3(1, 1, 1);
			mTimeAdj[i]		= 1.0f;
		}

        mType = "Texture2ScaleInterpolator";

        // Init parameters
        if (createParamDictionary("Texture2ScaleInterpolatorAffector"))
        {
            ParamDictionary* dict = getParamDictionary();

			for (int i=0;i<MAX_STAGES;i++)
			{
				msTextureScaleCmd[i].mIndex	= i;
				msTimeCmd[i].mIndex		= i;

				std::stringstream stage;
				stage << i;
				String	scale_title	= String("scale") + stage.str();
				String	time_title		= String("time") + stage.str();
				String	scale_descr	= String("Stage ") + stage.str() + String(" scale.");
				String	time_descr		= String("Stage ") + stage.str() + String(" time.");

				dict->addParameter(ParameterDef(scale_title, scale_descr, PT_VECTOR3), &msTextureScaleCmd[i]);
				dict->addParameter(ParameterDef(time_title, time_descr,   PT_REAL), &msTimeCmd[i]);
			}
        }
    }
    //-----------------------------------------------------------------------
    void Texture2ScaleInterpolatorAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
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
				u = mTextureScale[0].x;
				v = mTextureScale[0].y;
			} 
			else if (particle_time >= mTimeAdj[MAX_STAGES - 1])
			{
				u = mTextureScale[MAX_STAGES-1].x;
				v = mTextureScale[MAX_STAGES-1].y;
			}
			else
			{
				for (int i=0;i<MAX_STAGES-1;i++)
				{
					if (particle_time >= mTimeAdj[i] && particle_time < mTimeAdj[i + 1])
					{
						particle_time -= mTimeAdj[i];
						particle_time /= (mTimeAdj[i+1]-mTimeAdj[i]);
						u = ((mTextureScale[i+1].x * particle_time) + (mTextureScale[i].x * (1.0f - particle_time)));
						v = ((mTextureScale[i+1].y * particle_time) + (mTextureScale[i].y * (1.0f - particle_time)));
	
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
					if (mat.get())
					{
						auto texUnit = mat->getTextureUnit(1);
						texUnit->setTextureScale(u, v);
					}
				}
			}
		}
    }
    
	//-----------------------------------------------------------------------
	void Texture2ScaleInterpolatorAffector::setScaleAdjust(size_t index, const Ogre::Vector3& pos)
    {
        mTextureScale[index] = pos;
    }
    //-----------------------------------------------------------------------
	Ogre::Vector3 Texture2ScaleInterpolatorAffector::getScaleAdjust(size_t index) const
    {
        return mTextureScale[index];
    }


    //-----------------------------------------------------------------------
    void Texture2ScaleInterpolatorAffector::setTimeAdjust(size_t index, Real time)
    {
        mTimeAdj[index] = time;
    }
    //-----------------------------------------------------------------------
    Real Texture2ScaleInterpolatorAffector::getTimeAdjust(size_t index) const
    {
        return mTimeAdj[index];
    }
	///*
	char * Texture2ScaleInterpolatorAffector::readFromBuffer( char * pCurrent )
	{
		std::size_t chunkSize = sizeof(Ogre::ColourValue) * MAX_STAGES + 
			sizeof(Real) * MAX_STAGES;

		memcpy(&mTextureScale,pCurrent,chunkSize);
		pCurrent += chunkSize;

		return pCurrent;
	}

	void Texture2ScaleInterpolatorAffector::saveToFile( std::ofstream & of )
	{
		/*of.write((const char*)&mTextureScale,sizeof(Ogre::ColourValue) * MAX_STAGES + 
			sizeof(Real) * MAX_STAGES);*/
	}
	//*/
	bool Texture2ScaleInterpolatorAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
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
			pSerializer->readData(stream,mTextureScale,1,MAX_STAGES * sizeof(ColourValue));
			pSerializer->readData(stream,mTimeAdj,1,MAX_STAGES * sizeof(Real));
			return true;
		}
		return false;
	}
	bool Texture2ScaleInterpolatorAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	Texture2ScaleInterpolatorAffector::calcSerializedSize()
	{
		return 0;
	}
    
	//-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    // Command objects
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    String Texture2ScaleInterpolatorAffector::CmdTextureScaleAdjust::doGet(const void* target) const
    {
        return StringConverter::toString(static_cast<const Texture2ScaleInterpolatorAffector*>(target)->getScaleAdjust(mIndex) );
    }
    void Texture2ScaleInterpolatorAffector::CmdTextureScaleAdjust::doSet(void* target, const String& val)
    {
		Texture2ScaleInterpolatorAffector* pAffector = (Texture2ScaleInterpolatorAffector*)target;
        pAffector->setScaleAdjust(mIndex, StringConverter::parseVector3(val));
    }

#if OGRE_STRING_INTERFACE_COPY
    void Texture2ScaleInterpolatorAffector::CmdTextureScaleAdjust::doCopy(void* target, const void* source)
    {
        static_cast<Texture2ScaleInterpolatorAffector*>(target)->setScaleAdjust(mIndex,
            static_cast<const Texture2ScaleInterpolatorAffector*>(source)->getScaleAdjust(mIndex));
    }
#endif
	//-----------------------------------------------------------------------
    String Texture2ScaleInterpolatorAffector::CmdTimeAdjust::doGet(const void* target) const
    {
        return StringConverter::toString(static_cast<const Texture2ScaleInterpolatorAffector*>(target)->getTimeAdjust(mIndex) );
    }
    void Texture2ScaleInterpolatorAffector::CmdTimeAdjust::doSet(void* target, const String& val)
    {
        static_cast<Texture2ScaleInterpolatorAffector*>(target)->setTimeAdjust(mIndex,
            StringConverter::parseReal(val));
    }
#if OGRE_STRING_INTERFACE_COPY
    void Texture2ScaleInterpolatorAffector::CmdTimeAdjust::doCopy(void* target, const void* source)
    {
        static_cast<Texture2ScaleInterpolatorAffector*>(target)->setTimeAdjust(mIndex,
            static_cast<const Texture2ScaleInterpolatorAffector*>(source)->getTimeAdjust(mIndex));
    }
#endif

}



