/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "OgreHeader.h"
#include "OgreColourFadingAffector.h"
#include "OgreParticleSystem.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreString.h"



namespace Ogre {

	// Instantiate statics
	ColourFadingAffector::CmdOpacity ColourFadingAffector::msOpacityCmd;
	ColourFadingAffector::CmdFadeInTime ColourFadingAffector::msFadeInTimeCmd;
	ColourFadingAffector::CmdFadeOutTime ColourFadingAffector::msFadeOutTimeCmd;
	ColourFadingAffector::CmdColourAdjust		ColourFadingAffector::msColourCmd[MAX_STAGES];
	ColourFadingAffector::CmdTimeAdjust		ColourFadingAffector::msTimeCmd[MAX_STAGES];
	ColourFadingAffector::CmdRepeatTimes		ColourFadingAffector::msRepeatTimesCmd;

	//-----------------------------------------------------------------------
	ColourFadingAffector::ColourFadingAffector(ParticleSystem* psys)
		:ParticleAffector(psys)
	{
		mType = "ColourFading";

		mOpacity = 1.0f;
		mFadeInTime = 0.0f;
		mFadeOutTime = 1.0f;

		for (int i=0;i<MAX_STAGES;i++)
		{
			// set default colour to transparent grey, transparent since we might not want to display the particle here
			// grey because when a colour component is 0.5f the maximum difference to another colour component is 0.5f
			mColourAdj[i]	= ColourValue(0.5f, 0.5f, 0.5f, 0.0f);
			mTimeAdj[i]		= 1.0f;
		}

		mRepeatTimes = 1.0f;

		// Set up parameters
		if (createParamDictionary("ColourFadingAffector"))
		{
			addBaseParameters();
			// Add extra paramaters
			ParamDictionary* dict = getParamDictionary();

			for (int i=0;i<MAX_STAGES;i++)
			{
				msColourCmd[i].mIndex	= i;
				msTimeCmd[i].mIndex		= i;

				std::stringstream stage;
				stage << i;
				String	colour_title	= String("colour") + stage.str();
				String	time_title		= String("time") + stage.str();
				String	colour_descr	= String("Stage ") + stage.str() + String(" colour.");
				String	time_descr		= String("Stage ") + stage.str() + String(" time.");

				dict->addParameter(ParameterDef(colour_title, colour_descr, PT_COLOURVALUE), &msColourCmd[i]);
				dict->addParameter(ParameterDef(time_title,   time_descr,   PT_REAL),		 &msTimeCmd[i]);
			}

			dict->addParameter(ParameterDef("repeat_times", 
				"the repeat times of the colour interpolate.",
				PT_REAL), &msRepeatTimesCmd);

			dict->addParameter(ParameterDef("opacity", 
				"the type of particle rotation.",
				PT_REAL),&msOpacityCmd);
			dict->addParameter(ParameterDef("fade_in_time", 
				"the speed of particle circle rotation.",
				PT_REAL),&msFadeInTimeCmd);
			dict->addParameter(ParameterDef("fade_out_time", 
				"The vector representing the force to apply.",
				PT_REAL),&msFadeOutTimeCmd);
		}

	}
	void ColourFadingAffector::_initParticle(Particle* pParticle)
	{
		// we set the colour of the particle to BLACK when it was born, so the colour of 
		// particle will not be affected by the colour of particle emitter.
		///fs
		pParticle->mColour =ColourValue(0.0,0.0,0.0,0.0);
	}
	//-----------------------------------------------------------------------
	void ColourFadingAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
	{
		Particle*			p;

        bool needFmod = mRepeatTimes != 1.0f;

		const std::vector<Particle*>&  particles = pSystem->_getActiveParticles();

		for(auto it = particles.begin(); it != particles.end(); it++)
		{
			p = *it;

			const Real		life_time		= p->mTotalTimeToLive;
			Real			particle_time	= 1.0f - (p->mTimeToLive / life_time);

			// wrap the particle time
			Real            repeatedParticleTime = 
                needFmod ? fmod( particle_time * mRepeatTimes, 1.0f ) : particle_time;

			if (repeatedParticleTime <= mTimeAdj[0])
			{
				p->mColour = mColourAdj[0];
			} 
			else if (repeatedParticleTime >= mTimeAdj[MAX_STAGES - 1])
			{
				p->mColour = mColourAdj[MAX_STAGES-1];
			} 
			else
			{
				for (int i=0;i<MAX_STAGES-1;i++)
				{
					if (repeatedParticleTime >= mTimeAdj[i] && repeatedParticleTime < mTimeAdj[i + 1])
					{
						repeatedParticleTime -= mTimeAdj[i];
						repeatedParticleTime /= (mTimeAdj[i+1]-mTimeAdj[i]);

						p->mColour.r = ((mColourAdj[i+1].r * repeatedParticleTime) + (mColourAdj[i].r * (1.0f - repeatedParticleTime)));
						p->mColour.g = ((mColourAdj[i+1].g * repeatedParticleTime) + (mColourAdj[i].g * (1.0f - repeatedParticleTime)));
						p->mColour.b = ((mColourAdj[i+1].b * repeatedParticleTime) + (mColourAdj[i].b * (1.0f - repeatedParticleTime)));
						p->mColour.a = ((mColourAdj[i+1].a * repeatedParticleTime) + (mColourAdj[i].a * (1.0f - repeatedParticleTime)));
		
						break;
					}
				}
			}

			Real currentOpacity = mOpacity;
			// compute the opacity based on the real life time of particle
			if (particle_time <= mFadeInTime)
			{
				currentOpacity *= (particle_time / mFadeInTime);
			}
			else if (particle_time >= mFadeOutTime)
			{
				currentOpacity *= 1.0f - (particle_time - mFadeOutTime) / (1.0f - mFadeOutTime);
			}
			p->mColour *= currentOpacity;
		}
	}
	//-----------------------------------------------------------------------
	void ColourFadingAffector::setColourAdjust(size_t index, ColourValue colour)
	{
		mColourAdj[index] = colour;
	}
	//-----------------------------------------------------------------------
	ColourValue ColourFadingAffector::getColourAdjust(size_t index) const
	{
		return mColourAdj[index];
	}
	//-----------------------------------------------------------------------
	void ColourFadingAffector::setTimeAdjust(size_t index, Real time)
	{
		mTimeAdj[index] = time;
	}
	//-----------------------------------------------------------------------
	Real ColourFadingAffector::getTimeAdjust(size_t index) const
	{
		return mTimeAdj[index];
	}
	//-----------------------------------------------------------------------
	///*
	char * ColourFadingAffector::readFromBuffer(char * pCurrent)
	{
		int length = sizeof(ColourValue) * MAX_STAGES +
			sizeof(Real) * MAX_STAGES + sizeof(Real) * 4;

		memcpy(&mColourAdj[0],pCurrent,length);
		pCurrent += length;

		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void ColourFadingAffector::saveToFile(std::ofstream & of)
	{
		/*of.write((const char *)(&mColourAdj[0]),sizeof(ColourValue) * MAX_STAGES +
			sizeof(Real) * MAX_STAGES + sizeof(Real) * 4);*/
	}
	//*/
	bool ColourFadingAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_COLOUR_FADING_AFFECTOR)
			{
				pSerializer->skipChunk(stream);
				return false;
			}			
			//ÊôÐÔ
			pSerializer->readData(stream,mColourAdj,1,MAX_STAGES * sizeof(ColourValue));
			pSerializer->readData(stream,mTimeAdj,1,MAX_STAGES * sizeof(Real));
			pSerializer->readData(stream,&mRepeatTimes,1,sizeof(mRepeatTimes));
			
			pSerializer->readData(stream,&mOpacity,1,sizeof(mOpacity));
			pSerializer->readData(stream,&mFadeInTime,1,sizeof(mFadeInTime));
			pSerializer->readData(stream,&mFadeOutTime,1,sizeof(mFadeOutTime));
			return true;
		}
		return false;
	}
	bool ColourFadingAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ColourFadingAffector::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	// Command objects
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------   
	String ColourFadingAffector::CmdColourAdjust::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const ColourFadingAffector*>(target)->getColourAdjust(mIndex) );
	}
	void ColourFadingAffector::CmdColourAdjust::doSet(void* target, const String& val)
	{
		static_cast<ColourFadingAffector*>(target)->setColourAdjust(mIndex,
			StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void ColourFadingAffector::CmdColourAdjust::doCopy(void* target, const void* source)
    {
        static_cast<ColourFadingAffector*>(target)->setColourAdjust(mIndex,
            static_cast<const ColourFadingAffector*>(source)->getColourAdjust(mIndex) );
    }
#endif
	//-----------------------------------------------------------------------
	String ColourFadingAffector::CmdTimeAdjust::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const ColourFadingAffector*>(target)->getTimeAdjust(mIndex) );
	}
	void ColourFadingAffector::CmdTimeAdjust::doSet(void* target, const String& val)
	{
		static_cast<ColourFadingAffector*>(target)->setTimeAdjust(mIndex,
			StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void ColourFadingAffector::CmdTimeAdjust::doCopy(void* target, const void* source)
    {
        static_cast<ColourFadingAffector*>(target)->setTimeAdjust(mIndex,
            static_cast<const ColourFadingAffector*>(source)->getTimeAdjust(mIndex) );
    }
#endif
	//-----------------------------------------------------------------------
	String ColourFadingAffector::CmdRepeatTimes::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const ColourFadingAffector*>(target)->getRepeatTimes() );
	}
	void ColourFadingAffector::CmdRepeatTimes::doSet(void* target, const String& val)
	{
		static_cast<ColourFadingAffector*>(target)->setRepeatTimes(
			StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void ColourFadingAffector::CmdRepeatTimes::doCopy(void* target, const void* source)
    {
        static_cast<ColourFadingAffector*>(target)->setRepeatTimes(
            static_cast<const ColourFadingAffector*>(source)->getRepeatTimes() );
    }
#endif
	//-----------------------------------------------------------------------
	String ColourFadingAffector::CmdOpacity::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const ColourFadingAffector*>(target)->getOpacity() );
	}
	void ColourFadingAffector::CmdOpacity::doSet(void* target, const String& val)
	{
		static_cast<ColourFadingAffector*>(target)->setOpacity( StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void ColourFadingAffector::CmdOpacity::doCopy(void* target, const void* source)
    {
        static_cast<ColourFadingAffector*>(target)->setOpacity(
            static_cast<const ColourFadingAffector*>(source)->getOpacity() );
    }
#endif
	//-----------------------------------------------------------------------
	String ColourFadingAffector::CmdFadeInTime::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const ColourFadingAffector*>(target)->getFadeInTime() );
	}
	void ColourFadingAffector::CmdFadeInTime::doSet(void* target, const String& val)
	{
		static_cast<ColourFadingAffector*>(target)->setFadeInTime( StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void ColourFadingAffector::CmdFadeInTime::doCopy(void* target, const void* source)
    {
        static_cast<ColourFadingAffector*>(target)->setFadeInTime(
            static_cast<const ColourFadingAffector*>(source)->getFadeInTime() );
    }
#endif
	//-----------------------------------------------------------------------
	String ColourFadingAffector::CmdFadeOutTime::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const ColourFadingAffector*>(target)->getFadeOutTime() );
	}
	void ColourFadingAffector::CmdFadeOutTime::doSet(void* target, const String& val)
	{
		static_cast<ColourFadingAffector*>(target)->setFadeOutTime( StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void ColourFadingAffector::CmdFadeOutTime::doCopy(void* target, const void* source)
    {
        static_cast<ColourFadingAffector*>(target)->setFadeOutTime(
            static_cast<const ColourFadingAffector*>(source)->getFadeOutTime() );
    }
#endif
}

