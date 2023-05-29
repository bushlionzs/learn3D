/********************************************************************
Copyright (c) 2010 Beijing Kylin Network Information 
Science and Technology Co, Ltd. All Rights Reserved.
author:		changhao

purpose:	
*********************************************************************/

//第二层纹理坐标动画
#include "OgreHeader.h"
#include "OgreTexture2RotateInterpolatorAffector.h"
#include "OgreParticleSystem.h"
#include "OgreStringConverter.h"
#include "OgreParticle.h"
#include "OgreParticleSystemRenderer.h"
#include "OgreMaterialManager.h"
#include "OgreTextureUnit.h"

namespace Ogre {
    
    // init statics
    Texture2RotateInterpolatorAffector::CmdTextureRotateAdjust		Texture2RotateInterpolatorAffector::msTextureRotateCmd[MAX_STAGES];
    Texture2RotateInterpolatorAffector::CmdTimeAdjust		Texture2RotateInterpolatorAffector::msTimeCmd[MAX_STAGES];

    //-----------------------------------------------------------------------
    Texture2RotateInterpolatorAffector::Texture2RotateInterpolatorAffector(ParticleSystem* psys)
        : ParticleAffector(psys)
    {
		for (int i=0;i<MAX_STAGES;i++)
		{
			mTextureRotate[i] = 0.0f;
			mTimeAdj[i]		= 1.0f;
		}

        mType = "Texture2RotateInterpolator";

        // Init parameters
        if (createParamDictionary("Texture2RotateInterpolatorAffector"))
        {
            ParamDictionary* dict = getParamDictionary();

			for (int i=0;i<MAX_STAGES;i++)
			{
				msTextureRotateCmd[i].mIndex	= i;
				msTimeCmd[i].mIndex		= i;

				Ogre::StringStream stage;
				stage << i;
				String	rotate_title	= String("rotate") + stage.str();
				String	time_title		= String("time") + stage.str();
				String	rotate_descr	= String("Stage ") + stage.str() + String(" rotate.");
				String	time_descr		= String("Stage ") + stage.str() + String(" time.");

				dict->addParameter(ParameterDef(rotate_title, rotate_descr, PT_REAL), &msTextureRotateCmd[i]);
				dict->addParameter(ParameterDef(time_title, time_descr,   PT_REAL), &msTimeCmd[i]);
			}
        }
    }
    //-----------------------------------------------------------------------
    void Texture2RotateInterpolatorAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
    {
        Particle*			p;
		const std::vector<Particle*>& particles = pSystem->_getActiveParticles();

		for (auto it = particles.begin(); it != particles.end(); it++)
        {
            p = *it;
			const Real		life_time		= p->mTotalTimeToLive;
			Real			particle_time	= 1.0f - (p->mTimeToLive / life_time);

			float rotate = 0.0f;

			if (particle_time <= mTimeAdj[0])
			{
				rotate = mTextureRotate[0];
			} 
			else if (particle_time >= mTimeAdj[MAX_STAGES - 1])
			{
				rotate = mTextureRotate[MAX_STAGES-1];
			}
			else
			{
				for (int i=0;i<MAX_STAGES-1;i++)
				{
					if (particle_time >= mTimeAdj[i] && particle_time < mTimeAdj[i + 1])
					{
						particle_time -= mTimeAdj[i];
						particle_time /= (mTimeAdj[i+1]-mTimeAdj[i]);
						rotate = ((mTextureRotate[i+1] * particle_time) + (mTextureRotate[i] * (1.0f - particle_time)));

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
						Ogre::Degree degree(rotate);
						Ogre::Radian f(degree);
						texUnit->setTextureRotate(f);
					}
				}
			}
		}
    }
    
	//-----------------------------------------------------------------------
	void Texture2RotateInterpolatorAffector::setRotateAdjust(size_t index, float rotate)
    {
        mTextureRotate[index] = rotate;
    }
    //-----------------------------------------------------------------------
	float Texture2RotateInterpolatorAffector::getRotateAdjust(size_t index) const
    {
        return mTextureRotate[index];
    }

    //-----------------------------------------------------------------------
    void Texture2RotateInterpolatorAffector::setTimeAdjust(size_t index, Real time)
    {
        mTimeAdj[index] = time;
    }
    //-----------------------------------------------------------------------
    Real Texture2RotateInterpolatorAffector::getTimeAdjust(size_t index) const
    {
        return mTimeAdj[index];
    }
	///*
	char * Texture2RotateInterpolatorAffector::readFromBuffer( char * pCurrent )
	{
		std::size_t chunkSize = sizeof(Ogre::ColourValue) * MAX_STAGES + 
			sizeof(Real) * MAX_STAGES;

		memcpy(&mTextureRotate,pCurrent,chunkSize);
		pCurrent += chunkSize;

		return pCurrent;
	}

	void Texture2RotateInterpolatorAffector::saveToFile( std::ofstream & of )
	{
		/*of.write((const char*)&mTextureRotate,sizeof(Ogre::ColourValue) * MAX_STAGES + 
			sizeof(Real) * MAX_STAGES);*/
	}
	//*/
	bool Texture2RotateInterpolatorAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
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
			pSerializer->readData(stream,mTextureRotate,1,MAX_STAGES * sizeof(Real));
			pSerializer->readData(stream,mTimeAdj,1,MAX_STAGES * sizeof(Real));
			return true;
		}
		return false;
	}
	bool Texture2RotateInterpolatorAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	Texture2RotateInterpolatorAffector::calcSerializedSize()
	{
		return 0;
	}
    
	//-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    // Command objects
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    String Texture2RotateInterpolatorAffector::CmdTextureRotateAdjust::doGet(const void* target) const
    {
        return StringConverter::toString(static_cast<const Texture2RotateInterpolatorAffector*>(target)->getRotateAdjust(mIndex) );
    }
    void Texture2RotateInterpolatorAffector::CmdTextureRotateAdjust::doSet(void* target, const String& val)
    {
		Texture2RotateInterpolatorAffector* pAffector = (Texture2RotateInterpolatorAffector*)target;
        pAffector->setRotateAdjust(mIndex, StringConverter::parseReal(val));
    }

#if OGRE_STRING_INTERFACE_COPY
    void Texture2RotateInterpolatorAffector::CmdTextureRotateAdjust::doCopy(void* target, const void* source)
    {
        static_cast<Texture2RotateInterpolatorAffector*>(target)->setRotateAdjust(mIndex,
            static_cast<const Texture2RotateInterpolatorAffector*>(source)->getRotateAdjust(mIndex));
    }
#endif
	//-----------------------------------------------------------------------
    String Texture2RotateInterpolatorAffector::CmdTimeAdjust::doGet(const void* target) const
    {
        return StringConverter::toString(static_cast<const Texture2RotateInterpolatorAffector*>(target)->getTimeAdjust(mIndex) );
    }
    void Texture2RotateInterpolatorAffector::CmdTimeAdjust::doSet(void* target, const String& val)
    {
        static_cast<Texture2RotateInterpolatorAffector*>(target)->setTimeAdjust(mIndex,
            StringConverter::parseReal(val));
    }
#if OGRE_STRING_INTERFACE_COPY
    void Texture2RotateInterpolatorAffector::CmdTimeAdjust::doCopy(void* target, const void* source)
    {
        static_cast<Texture2RotateInterpolatorAffector*>(target)->setTimeAdjust(mIndex,
            static_cast<const Texture2RotateInterpolatorAffector*>(source)->getTimeAdjust(mIndex));
    }
#endif

}



