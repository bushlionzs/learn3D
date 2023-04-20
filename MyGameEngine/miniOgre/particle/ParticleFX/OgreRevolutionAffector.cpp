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
#include "OgreRevolutionAffector.h"
#include "OgreParticleSystem.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreNode.h"
#include "OgreSceneNode.h"


namespace Ogre {

    // Instantiate statics
    RevolutionAffector::CmdRotationSpeed RevolutionAffector::msRotationSpeedCmd;
    RevolutionAffector::CmdRotationAxis RevolutionAffector::msRotationAxisCmd;
	RevolutionAffector::CmdRadiusIncrement RevolutionAffector::msRadiusIncrementCmd;
	RevolutionAffector::CmdRadiusIncrementAdjust		RevolutionAffector::msRadiusIncrementAdjustCmd[MAX_STAGES];
	RevolutionAffector::CmdTimeAdjust		RevolutionAffector::msTimeCmd[MAX_STAGES];
	RevolutionAffector::CmdRepeatTimes		RevolutionAffector::msRepeatTimesCmd;


	RevolutionAffector::CmdUseRadiusIncrementScale		RevolutionAffector::msUseRadiusIncrementScaleCmd;
	RevolutionAffector::CmdCenterOffsetMin      RevolutionAffector::msCenterOffsetMinCmd;
	RevolutionAffector::CmdCenterOffsetMax      RevolutionAffector::msCenterOffsetMaxCmd;


    //-----------------------------------------------------------------------
    RevolutionAffector::RevolutionAffector(ParticleSystem* psys)
        :ParticleAffector(psys)
    {
        mType = "Revolution";

		mRotateAxis = Ogre::Vector3::UNIT_Y;
		mRotationSpeed = 0.0f;

		for (int i=0;i<MAX_STAGES;i++)
		{
			// set default colour to transparent grey, transparent since we might not want to display the particle here
			// grey because when a colour component is 0.5f the maximum difference to another colour component is 0.5f
			mRadiusIncrementAdj[i]	= 0.0f;
			mTimeAdj[i]		= 1.0f;
		}

		mRepeatTimes = 1.0f;

		mCenterOffsetMin = Ogre::Vector3::ZERO;
		mCenterOffsetMax = Ogre::Vector3::ZERO;

		mUseRadiusIncrementScale = false;

		mRadiusIncrement = 0.0f;

        // Default to gravity-like

        // Set up parameters
        if (createParamDictionary("RevolutionAffector"))
        {
            addBaseParameters();
            // Add extra paramaters
            ParamDictionary* dict = getParamDictionary();

			dict->addParameter(ParameterDef("rotation_speed", 
                "the speed of particle circle rotation.",
                PT_REAL),&msRotationSpeedCmd);

            dict->addParameter(ParameterDef("rotation_axis", 
                "The vector representing the force to apply.",
                PT_VECTOR3),&msRotationAxisCmd);

			dict->addParameter(ParameterDef("radius_increment", 
				"the speed of particle circle rotation.",
				PT_REAL),&msRadiusIncrementCmd);

			dict->addParameter(ParameterDef("center_offset_min", 
				"The vector representing the force to apply.",
				PT_VECTOR3),&msCenterOffsetMinCmd);

			dict->addParameter(ParameterDef("center_offset_max", 
				"The vector representing the force to apply.",
				PT_VECTOR3),&msCenterOffsetMaxCmd);

			for (int i=0;i<MAX_STAGES;i++)
			{
				msRadiusIncrementAdjustCmd[i].mIndex	= i;
				msTimeCmd[i].mIndex		= i;

				Ogre::StringStream stage;
				stage << i;
				String	speed_title	= String("radius_increment_scale") + stage.str();
				String	time_title		= String("time") + stage.str();
				String	speed_descr	= String("Stage ") + stage.str() + String(" RadiusIncrementScale.");
				String	time_descr		= String("Stage ") + stage.str() + String(" time.");

				dict->addParameter(ParameterDef(speed_title, speed_descr, PT_REAL), &msRadiusIncrementAdjustCmd[i]);
				dict->addParameter(ParameterDef(time_title,   time_descr,   PT_REAL),		 &msTimeCmd[i]);
			}		

			dict->addParameter(ParameterDef("use_radius_increment_scale", 
				"the repeat times of the colour interpolate.",
				PT_BOOL), &msUseRadiusIncrementScaleCmd);

			dict->addParameter(ParameterDef("repeat_times", 
				"the repeat times of the colour interpolate.",
				PT_REAL), &msRepeatTimesCmd);
        }

    }
    //-----------------------------------------------------------------------
    void RevolutionAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
    {
        // ��ΪtimeElapsed�п�����0�������жϣ������0��
        if (false == Ogre::Math::RealEqual(timeElapsed, 0.0f))
        {
            Particle *p;

            Quaternion q( Radian(Degree(mRotationSpeed*timeElapsed).valueRadians()), mRotateAxis);
            Matrix3 mat(Matrix3::IDENTITY);
            q.ToRotationMatrix(mat);

            Ogre::Vector3 randomPoint;
            randomPoint.x = Math::RangeRandom(mCenterOffsetMin.x, mCenterOffsetMax.x);
            randomPoint.y = Math::RangeRandom(mCenterOffsetMin.y, mCenterOffsetMax.y);
            randomPoint.z = Math::RangeRandom(mCenterOffsetMin.z, mCenterOffsetMax.z);

            Vector3 particleSystemPos(Vector3::ZERO);

            bool localSpace = pSystem->getKeepParticlesInLocalSpace();

            particleSystemPos = pSystem->getParentSceneNode()->_getDerivedPosition();

            Ogre::Vector3 destPoint = particleSystemPos + randomPoint;

            Vector3 particlePos(Vector3::ZERO);

            Vector3 RadiusIncrementDir(Vector3::ZERO);

            bool needFmod = mRepeatTimes != 1.0f;

			const std::vector<Particle*>& particles = pSystem->_getActiveParticles();

			for (auto it = particles.begin(); it != particles.end(); it++)
            {
                p = *it;

                particlePos = p->mPosition;

                /** �����localSpace����ôp->position�õ��������ӵ����λ�ã�����Ҫ����
                ����ϵͳ��λ��particleSystemPos���õ�����λ�ã��ټ�ȥdestPoint���ܵõ�
                ��ȷ������
                particlePos + particleSystemPos - destPoint
                =   particlePos + particleSystemPos - particleSystemPos - randomPoint
                =   particlePos - randomPoint
                */
                if (localSpace)
                {
                    RadiusIncrementDir = particlePos - randomPoint;
                    RadiusIncrementDir.normalise();

                    particlePos = mat *( particlePos - randomPoint ) + randomPoint - particlePos;
                }
                else
                {
                    RadiusIncrementDir = particlePos - destPoint;
                    RadiusIncrementDir.normalise();

                    particlePos = mat *( particlePos - destPoint ) + destPoint - particlePos;
                }

                p->mDirection = particlePos / timeElapsed;

                if (mUseRadiusIncrementScale)
                {
                    const Real		life_time		= p->mTotalTimeToLive;
                    Real			particle_time	= 1.0f - (p->mTimeToLive / life_time);

                    // wrap the particle time
                    Real            repeatedParticleTime = 
                        needFmod ? fmod( particle_time * mRepeatTimes, 1.0f ) : particle_time;

                    if (repeatedParticleTime <= mTimeAdj[0])
                    {
                        p->mDirection += RadiusIncrementDir * mRadiusIncrementAdj[0];
                    } 
                    else if (repeatedParticleTime >= mTimeAdj[MAX_STAGES - 1])
                    {
                        p->mDirection += RadiusIncrementDir * mRadiusIncrementAdj[MAX_STAGES - 1];
                    } 
                    else
                    {
                        for (int i=0;i<MAX_STAGES-1;i++)
                        {
                            if (repeatedParticleTime >= mTimeAdj[i] && repeatedParticleTime < mTimeAdj[i + 1])
                            {
                                repeatedParticleTime -= mTimeAdj[i];
                                repeatedParticleTime /= (mTimeAdj[i+1]-mTimeAdj[i]);
                                p->mDirection += RadiusIncrementDir *
                                    ( (mRadiusIncrementAdj[i+1] * repeatedParticleTime) + (mRadiusIncrementAdj[i] * (1.0f - repeatedParticleTime)) );
                                break;
                            }
                        }
                    }
                }
                else
                {
                    p->mDirection += RadiusIncrementDir*mRadiusIncrement;
                }
				//p->mNeedRecalAxis = true; todo123

                
            }
        }
    }

	void RevolutionAffector::setRadiusIncrementAdjust(size_t index, Real speed)
	{
		mRadiusIncrementAdj[index] = speed;
	}
	//-----------------------------------------------------------------------
	Real RevolutionAffector::getRadiusIncrementAdjust(size_t index) const
	{
		return mRadiusIncrementAdj[index];
	}


	//-----------------------------------------------------------------------
	void RevolutionAffector::setTimeAdjust(size_t index, Real time)
	{
		mTimeAdj[index] = time;
	}
	//-----------------------------------------------------------------------
	Real RevolutionAffector::getTimeAdjust(size_t index) const
	{
		return mTimeAdj[index];
	}
	//-----------------------------------------------------------------------
	///*
	char * RevolutionAffector::readFromBuffer(char * pCurrent)
	{
		int length = sizeof(Radian) + sizeof(Vector3) * 3 +
			sizeof(Real) * (MAX_STAGES * 2 + 2) + sizeof(int);

		memcpy(&mRotationSpeed,pCurrent,length);
		pCurrent += length;

		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void RevolutionAffector::saveToFile(std::ofstream & of)
	{
		/*of.write((const char *)(&mRotationSpeed),sizeof(Radian) + sizeof(Vector3) * 3 +
			sizeof(Real) * (MAX_STAGES * 2 + 2) + sizeof(int));*/
	}
	//*/
	bool RevolutionAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_REVOLUTION_AFFECTOR)
			{
				pSerializer->skipChunk(stream);
				return false;
			}			
			//����
			pSerializer->readData(stream,&mRotationSpeed,1,sizeof(mRotationSpeed));
			pSerializer->readData(stream,&mRotateAxis,1,sizeof(mRotateAxis));
			pSerializer->readData(stream,&mRadiusIncrement,1,sizeof(mRadiusIncrement));
			pSerializer->readData(stream,&mCenterOffsetMin,1,sizeof(mCenterOffsetMin));
			pSerializer->readData(stream,&mCenterOffsetMax,1,sizeof(mCenterOffsetMax));

			pSerializer->readData(stream,mRadiusIncrementAdj,1,MAX_STAGES * sizeof(Real));
			pSerializer->readData(stream,mTimeAdj,1,MAX_STAGES * sizeof(Real));
			pSerializer->readData(stream,&mUseRadiusIncrementScale,1,sizeof(mUseRadiusIncrementScale));
			pSerializer->readData(stream,&mRepeatTimes,1,sizeof(mRepeatTimes));
			return true;
		}
		return false;
	}
	bool RevolutionAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	RevolutionAffector::calcSerializedSize()
	{
		return 0;
	}

	//-----------------------------------------------------------------------
	String RevolutionAffector::CmdRepeatTimes::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->getRepeatTimes() );
	}
	void RevolutionAffector::CmdRepeatTimes::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->setRepeatTimes(
			StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdRepeatTimes::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->setRepeatTimes(
            static_cast<const RevolutionAffector*>(source)->getRepeatTimes() );
    }
#endif
	String RevolutionAffector::CmdCenterOffsetMin::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->getCenterOffsetMin() );
	}
	void RevolutionAffector::CmdCenterOffsetMin::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->setCenterOffsetMin(
			StringConverter::parseVector3(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdCenterOffsetMin::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->setCenterOffsetMin(
            static_cast<const RevolutionAffector*>(source)->getCenterOffsetMin() );
    }
#endif
	String RevolutionAffector::CmdCenterOffsetMax::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->getCenterOffsetMax() );
	}
	void RevolutionAffector::CmdCenterOffsetMax::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->setCenterOffsetMax(
			StringConverter::parseVector3(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdCenterOffsetMax::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->setCenterOffsetMax(
            static_cast<const RevolutionAffector*>(source)->getCenterOffsetMax() );
    }
#endif
	String RevolutionAffector::CmdRadiusIncrementAdjust::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->getRadiusIncrementAdjust(mIndex) );
	}
	void RevolutionAffector::CmdRadiusIncrementAdjust::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->setRadiusIncrementAdjust(mIndex,
			StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdRadiusIncrementAdjust::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->setRadiusIncrementAdjust(mIndex,
            static_cast<const RevolutionAffector*>(source)->getRadiusIncrementAdjust(mIndex) );
    }
#endif
	//-----------------------------------------------------------------------
	String RevolutionAffector::CmdTimeAdjust::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->getTimeAdjust(mIndex) );
	}
	void RevolutionAffector::CmdTimeAdjust::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->setTimeAdjust(mIndex,
			StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdTimeAdjust::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->setTimeAdjust(mIndex,
            static_cast<const RevolutionAffector*>(source)->getTimeAdjust(mIndex) );
    }
#endif
	String RevolutionAffector::CmdUseRadiusIncrementScale::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->getUseRadiusIncrementScale() );
	}
	void RevolutionAffector::CmdUseRadiusIncrementScale::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->setUseRadiusIncrementScale(
			StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdUseRadiusIncrementScale::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->setUseRadiusIncrementScale(
            static_cast<const RevolutionAffector*>(source)->getUseRadiusIncrementScale() );
    }
#endif
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    // Command objects
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------   
	
    //-----------------------------------------------------------------------
    String RevolutionAffector::CmdRotationSpeed::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const RevolutionAffector*>(target)->mRotationSpeed );
    }
    void RevolutionAffector::CmdRotationSpeed::doSet(void* target, const String& val)
    {
        static_cast<RevolutionAffector*>(target)->mRotationSpeed = StringConverter::parseAngle(val);
    }
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdRotationSpeed::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->mRotationSpeed =
            static_cast<const RevolutionAffector*>(source)->mRotationSpeed;
    }
#endif
    String RevolutionAffector::CmdRotationAxis::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const RevolutionAffector*>(target)->mRotateAxis );
    }
    void RevolutionAffector::CmdRotationAxis::doSet(void* target, const String& val)
    {
        static_cast<RevolutionAffector*>(target)->mRotateAxis = StringConverter::parseVector3(val);
    }
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdRotationAxis::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->mRotateAxis =
            static_cast<const RevolutionAffector*>(source)->mRotateAxis;
    }
#endif
	String RevolutionAffector::CmdRadiusIncrement::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RevolutionAffector*>(target)->mRadiusIncrement );
	}
	void RevolutionAffector::CmdRadiusIncrement::doSet(void* target, const String& val)
	{
		static_cast<RevolutionAffector*>(target)->mRadiusIncrement = StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void RevolutionAffector::CmdRadiusIncrement::doCopy(void* target, const void* source)
    {
        static_cast<RevolutionAffector*>(target)->mRadiusIncrement = 
            static_cast<const RevolutionAffector*>(source)->mRadiusIncrement;
    }
#endif
}

