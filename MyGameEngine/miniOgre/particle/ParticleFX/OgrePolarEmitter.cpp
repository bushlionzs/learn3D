/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright ) 2002 Tels <http://bloodgate.com> Based on OgrreBoxEmitter
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
#include "OgrePolarEmitter.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreParticleSystem.h"

namespace Ogre {

    // Instatiate statics
    PolarEmitter::CmdRadiusMin PolarEmitter::msRadiusMinCmd;
	PolarEmitter::CmdRadiusStep PolarEmitter::msRadiusStepCmd;
	PolarEmitter::CmdRadiusMax PolarEmitter::msRadiusMaxCmd;

    PolarEmitter::CmdThetaMin PolarEmitter::msThetaMinCmd;
	PolarEmitter::CmdThetaStep PolarEmitter::msThetaStepCmd;
	PolarEmitter::CmdThetaMax PolarEmitter::msThetaMaxCmd;

    PolarEmitter::CmdPhiMin PolarEmitter::msPhiMinCmd;
    PolarEmitter::CmdPhiStep PolarEmitter::msPhiStepCmd;
	PolarEmitter::CmdPhiMax PolarEmitter::msPhiMaxCmd;

	PolarEmitter::CmdUsePolarStep PolarEmitter::msUsePolarStepCmd;
	PolarEmitter::CmdFlipYZAxis PolarEmitter::msFlipYZAxisCmd;

    PolarEmitter::CmdResetCount PolarEmitter::msResetRadiusCountCmd;
    PolarEmitter::CmdReset PolarEmitter::msResetRadiusCmd;

    PolarEmitter::PolarEmitter(ParticleSystem* psys)
        : ParticleEmitter(psys)
		, mRadiusMin(0.0f)
		, mRadiusStep(0.0f)
		, mRadiusMax(0.0f)
	    , mThetaMin(0.0f)
		, mThetaStep(0.0f)
		, mThetaMax(0.0f)
	    , mPhiMin(0.0f)
	    , mPhiStep(0.0f)
		, mPhiMax(0.0f)
		, mThetaTotal(0.0f)
		, mPhiTotal(0.0f)
		, mRadiusTotal(0.0f)
		, mUsePolarStep(false)
		, mFlipYZAxis(false)
        , mResetRadiusCount(0)
        , mResetRadius(false)
        , mCurrentResetRadiusCount(0)

    {
        mType = "PolarEmitter";

        // Set up parameters
        if (createParamDictionary("PolarEmitter"))
        {
            addBaseParameters();

            // Add extra paramaters
            ParamDictionary* dict = getParamDictionary();
            dict->addParameter(ParameterDef("radius_start", 
                "The vector representing the force to apply.",
                PT_REAL),&msRadiusMinCmd);

			dict->addParameter(ParameterDef("radius_step", 
				"The vector representing the force to apply.",
				PT_REAL),&msRadiusStepCmd);

			dict->addParameter(ParameterDef("radius_end", 
				"The vector representing the force to apply.",
				PT_REAL),&msRadiusMaxCmd);

            dict->addParameter(ParameterDef("theta_start", 
                "The vector representing the force to apply.",
                PT_REAL),&msThetaMinCmd);

            dict->addParameter(ParameterDef("theta_step", 
                "The vector representing the force to apply.",
                PT_REAL),&msThetaStepCmd);

			dict->addParameter(ParameterDef("theta_end", 
				"The vector representing the force to apply.",
				PT_REAL),&msThetaMaxCmd);

			dict->addParameter(ParameterDef("phi_start", 
				"The vector representing the force to apply.",
				PT_REAL),&msPhiMinCmd);

            dict->addParameter(ParameterDef("phi_step", 
                "The vector representing the force to apply.",
                PT_REAL),&msPhiStepCmd);

			dict->addParameter(ParameterDef("phi_end", 
				"The vector representing the force to apply.",
				PT_REAL),&msPhiMaxCmd);

			dict->addParameter(ParameterDef("use_polar_step", 
				"The vector representing the force to apply.",
				PT_BOOL),&msUsePolarStepCmd);

			dict->addParameter(ParameterDef("flip_yz_axis", 
				"The vector representing the force to apply.",
				PT_BOOL),&msFlipYZAxisCmd);

            dict->addParameter(ParameterDef("reset_radius_count", 
                "when you use the radius step, this value can control the radius reset"
                "by emitting reset_radius_count particles.",
                PT_INT),&msResetRadiusCountCmd);

            dict->addParameter(ParameterDef("reset_radius", 
                "when you use the radius step, this value can control the radius reset.",
                PT_BOOL),&msResetRadiusCmd);
        }
    }  

    unsigned short PolarEmitter::_getEmissionCount(Real timeElapsed)
    {
        // Use basic constant emission 
        return genConstantEmissionCount(timeElapsed);
    }

    void PolarEmitter::_initParticle(Particle* pParticle)
    { 
		Vector3 pos;

		// if we want to control the step of the parameter
		if (mUsePolarStep)
		{
			pos.x = mRadiusTotal * Math::Sin(Degree(mThetaTotal).valueRadians()) * Math::Cos(Degree(mPhiTotal).valueRadians());
		
			if (mFlipYZAxis)
			{
				pos.z = mRadiusTotal * Math::Sin(Degree(mThetaTotal).valueRadians()) * Math::Sin(Degree(mPhiTotal).valueRadians());
				pos.y = mRadiusTotal * Math::Cos(Degree(mThetaTotal).valueRadians());
			}
			else
			{
				pos.y = mRadiusTotal * Math::Sin(Degree(mThetaTotal).valueRadians()) * Math::Sin(Degree(mPhiTotal).valueRadians());
				pos.z = mRadiusTotal * Math::Cos(Degree(mThetaTotal).valueRadians());
			}

            // wrap the angle between 0 and 360
            mThetaTotal = fmod( mThetaTotal + mThetaStep, 360.0f );
			mPhiTotal = fmod( mPhiTotal + mPhiStep, 360.0f );

            // 判断是否需要reset radius
            if (mResetRadius && (++mCurrentResetRadiusCount > mResetRadiusCount))
            {
                mCurrentResetRadiusCount = 0;
                mRadiusTotal = mRadiusMin;
            }
            else
                mRadiusTotal += mRadiusStep;
		}
		else
		{
			Real currentXAngle = Math::RangeRandom(mThetaMin, mThetaMax);

			Real currentYAngle = Math::RangeRandom(mPhiMin, mPhiMax);

			Real currentSphereRadius = Math::RangeRandom(mRadiusMin, mRadiusMax);

			pos.x = currentSphereRadius * Math::Sin(Degree(currentXAngle).valueRadians()) * Math::Cos(Degree(currentYAngle).valueRadians());
			
			if (mFlipYZAxis)
			{
				pos.z = currentSphereRadius * Math::Sin(Degree(currentXAngle).valueRadians()) * Math::Sin(Degree(currentYAngle).valueRadians());
				pos.y = currentSphereRadius * Math::Cos(Degree(currentXAngle).valueRadians());
			}
			else
			{
				pos.y = currentSphereRadius * Math::Sin(Degree(currentXAngle).valueRadians()) * Math::Sin(Degree(currentYAngle).valueRadians());
				pos.z = currentSphereRadius * Math::Cos(Degree(currentXAngle).valueRadians());
			}
		}

        pParticle->mPosition = mPosition + pos;

        // Generate complex data by reference
        genEmissionColour(pParticle->mColour);
        genEmissionDirection(pParticle->mPosition, pParticle->mDirection);
        genEmissionVelocity(pParticle->mDirection);

        // Generate simpler data
        pParticle->mTimeToLive = pParticle->mTotalTimeToLive = genEmissionTTL();
    }

	void PolarEmitter::setEnabled(bool enabled)
	{
		resetParameter();

		ParticleEmitter::setEnabled(enabled);
	}

	///*
	char * PolarEmitter::readFromBuffer(char * pCurrent)
	{

		

		return nullptr;
	}

	void PolarEmitter::saveToFile(std::ofstream & of)
	{
			
	}
	//*/
	bool PolarEmitter::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_POLAR_EMITTER)
			{
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类ParticleEmitter的属性			
			pSerializer->readData(stream,&mEnabled,1,sizeof(mEnabled));
			pSerializer->readData(stream,&mAngle,1,sizeof(mAngle));
			pSerializer->readData(stream,&mColourRangeStart,1,sizeof(mColourRangeStart));
			pSerializer->readData(stream,&mColourRangeEnd,1,sizeof(mColourRangeEnd));
			Vector3 direction;
			pSerializer->readData(stream,&direction,1,sizeof(direction));
			setDirection(direction);
			pSerializer->readData(stream,&mEmissionRate,1,sizeof(mEmissionRate));
			pSerializer->readData(stream,&mPosition,1,sizeof(mPosition));

			pSerializer->readData(stream,&mMinSpeed,1,sizeof(mMinSpeed));
			pSerializer->readData(stream,&mMaxSpeed,1,sizeof(mMaxSpeed));
			pSerializer->readData(stream,&mMinTTL,1,sizeof(mMinTTL));
			pSerializer->readData(stream,&mMaxTTL,1,sizeof(mMaxTTL));
			Real DurMin,DurMax;
			pSerializer->readData(stream,&DurMin,1,sizeof(DurMin));
			pSerializer->readData(stream,&DurMax,1,sizeof(DurMax));
			setDuration(DurMin,DurMax);
			Real RepMin,RepMax;
			pSerializer->readData(stream,&RepMin,1,sizeof(RepMin));
			pSerializer->readData(stream,&RepMax,1,sizeof(RepMax));
			setRepeatDelay(RepMin,RepMax);
			//属性
			pSerializer->readData(stream,&mRadiusMin,1,sizeof(mRadiusMin));
			pSerializer->readData(stream,&mRadiusStep,1,sizeof(mRadiusStep));
			pSerializer->readData(stream,&mRadiusMax,1,sizeof(mRadiusMax));
			
			pSerializer->readData(stream,&mThetaMin,1,sizeof(mThetaMin));
			pSerializer->readData(stream,&mThetaStep,1,sizeof(mThetaStep));
			pSerializer->readData(stream,&mThetaMax,1,sizeof(mThetaMax));
			
			pSerializer->readData(stream,&mPhiMin,1,sizeof(mPhiMin));
			pSerializer->readData(stream,&mPhiStep,1,sizeof(mPhiStep));
			pSerializer->readData(stream,&mPhiMax,1,sizeof(mPhiMax));
			
			pSerializer->readData(stream,&mUsePolarStep,1,sizeof(mUsePolarStep));
			pSerializer->readData(stream,&mFlipYZAxis,1,sizeof(mFlipYZAxis));
			pSerializer->readData(stream,&mResetRadiusCount,1,sizeof(mResetRadiusCount));
			pSerializer->readData(stream,&mResetRadius,1,sizeof(mResetRadius));
		
			return true;
		}
		return false;
	}
	bool PolarEmitter::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	PolarEmitter::calcSerializedSize()
	{	
		return 0;
	}
    //-----------------------------------------------------------------------
    // Command objects
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    String PolarEmitter::CmdRadiusMin::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const PolarEmitter*>(target)->mRadiusMin );
    }
    void PolarEmitter::CmdRadiusMin::doSet(void* target, const String& val)
    {
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
		emitter->mRadiusMin = StringConverter::parseReal(val);
		
		emitter->resetParameter();
    }
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdRadiusMin::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mRadiusMin = static_cast<const PolarEmitter*>(source)->mRadiusMin;
        emitter->resetParameter();
    }
#endif
	String PolarEmitter::CmdRadiusStep::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mRadiusStep );
	}
	void PolarEmitter::CmdRadiusStep::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
		emitter->mRadiusStep = StringConverter::parseReal(val);

		emitter->resetParameter();
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdRadiusStep::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mRadiusStep = static_cast<const PolarEmitter*>(source)->mRadiusStep;
        emitter->resetParameter();
    }
#endif
	String PolarEmitter::CmdRadiusMax::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mRadiusMax );
	}
	void PolarEmitter::CmdRadiusMax::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
		emitter->mRadiusMax = StringConverter::parseReal(val);

		emitter->resetParameter();
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdRadiusMax::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mRadiusMax = static_cast<const PolarEmitter*>(source)->mRadiusMax;
        emitter->resetParameter();
    }
#endif
    //-----------------------------------------------------------------------
    String PolarEmitter::CmdThetaMin::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const PolarEmitter*>(target)->mThetaMin );
    }
    void PolarEmitter::CmdThetaMin::doSet(void* target, const String& val)
    {
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

        emitter->mThetaMin = StringConverter::parseReal(val);

		emitter->resetParameter();
    }
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdThetaMin::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mThetaMin = static_cast<const PolarEmitter*>(source)->mThetaMin;
        emitter->resetParameter();
    }
#endif
	//-----------------------------------------------------------------------
	String PolarEmitter::CmdThetaStep::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mThetaStep );
	}
	void PolarEmitter::CmdThetaStep::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mThetaStep = StringConverter::parseReal(val);

		emitter->resetParameter();
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdThetaStep::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mThetaStep = static_cast<const PolarEmitter*>(source)->mThetaStep;
        emitter->resetParameter();
    }
#endif
	String PolarEmitter::CmdThetaMax::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mThetaMax );
	}
	void PolarEmitter::CmdThetaMax::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mThetaMax = StringConverter::parseReal(val);

		emitter->resetParameter();
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdThetaMax::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mThetaMax = static_cast<const PolarEmitter*>(source)->mThetaMax;
        emitter->resetParameter();
    }
#endif
    //-----------------------------------------------------------------------
    String PolarEmitter::CmdPhiMin::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const PolarEmitter*>(target)->mPhiMin );
    }
    void PolarEmitter::CmdPhiMin::doSet(void* target, const String& val)
    {
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mPhiMin = StringConverter::parseReal(val);

		emitter->resetParameter();
    }    
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdPhiMin::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mPhiMin = static_cast<const PolarEmitter*>(source)->mPhiMin;
        emitter->resetParameter();
    }
#endif
    //-----------------------------------------------------------------------
    String PolarEmitter::CmdPhiStep::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const PolarEmitter*>(target)->mPhiStep );
    }
    void PolarEmitter::CmdPhiStep::doSet(void* target, const String& val)
    {
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mPhiStep = StringConverter::parseReal(val);

		emitter->resetParameter();
    }    
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdPhiStep::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mPhiStep = static_cast<const PolarEmitter*>(source)->mPhiStep;
        emitter->resetParameter();
    }
#endif
	String PolarEmitter::CmdPhiMax::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mPhiMax );
	}
	void PolarEmitter::CmdPhiMax::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mPhiMax = StringConverter::parseReal(val);

		emitter->resetParameter();
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdPhiMax::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mPhiMax = static_cast<const PolarEmitter*>(source)->mPhiMax;
        emitter->resetParameter();
    }
#endif
	String PolarEmitter::CmdUsePolarStep::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mUsePolarStep );
	}
	void PolarEmitter::CmdUsePolarStep::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mUsePolarStep = StringConverter::parseBool(val);

		emitter->resetParameter();
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdUsePolarStep::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mUsePolarStep = static_cast<const PolarEmitter*>(source)->mUsePolarStep;
        emitter->resetParameter();
    }
#endif
	String PolarEmitter::CmdFlipYZAxis::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const PolarEmitter*>(target)->mFlipYZAxis );
	}
	void PolarEmitter::CmdFlipYZAxis::doSet(void* target, const String& val)
	{
		assert (target);

		PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

		emitter->mFlipYZAxis = StringConverter::parseBool(val);
	}
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdFlipYZAxis::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mFlipYZAxis = static_cast<const PolarEmitter*>(source)->mFlipYZAxis;
    }
#endif
    String PolarEmitter::CmdResetCount::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const PolarEmitter*>(target)->mResetRadiusCount );
    }
    void PolarEmitter::CmdResetCount::doSet(void* target, const String& val)
    {
        assert (target);

        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

        emitter->mResetRadiusCount = StringConverter::parseInt(val);

        emitter->mRadiusTotal = emitter->mRadiusMin;
    }
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdResetCount::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mResetRadiusCount = static_cast<const PolarEmitter*>(source)->mResetRadiusCount;
        emitter->mRadiusTotal = emitter->mRadiusMin;
    }
#endif
    String PolarEmitter::CmdReset::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const PolarEmitter*>(target)->mResetRadius );
    }
    void PolarEmitter::CmdReset::doSet(void* target, const String& val)
    {
        assert (target);

        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);

        emitter->mResetRadius = StringConverter::parseBool(val);

        emitter->mRadiusTotal = emitter->mRadiusMin;
        emitter->mCurrentResetRadiusCount = 0;
    }
#if OGRE_STRING_INTERFACE_COPY
    //-----------------------------------------------------------------------
    void PolarEmitter::CmdReset::doCopy(void* target, const void* source)
    {
        PolarEmitter *emitter = static_cast<PolarEmitter*>(target);
        emitter->mResetRadius = static_cast<const PolarEmitter*>(source)->mResetRadius;
        emitter->mRadiusTotal = emitter->mRadiusMin;
        emitter->mCurrentResetRadiusCount = 0;
    }
#endif
}


