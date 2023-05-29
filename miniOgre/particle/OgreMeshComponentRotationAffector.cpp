#include "OgreHeader.h"
#include "OgreMeshComponentRotationAffector.h"
#include "OgreParticleSystem.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreMeshComponentParticleVisualData.h"
#include "OgreSerializer.h"
#include "platform_log.h"

namespace Ogre {

	// Instantiate statics
	MeshComponentOrientationAffector::CmdYawOrientationSpeedRangeStart	MeshComponentOrientationAffector::msYawOrientationSpeedRangeStartCmd;
	MeshComponentOrientationAffector::CmdYawOrientationSpeedRangeEnd		MeshComponentOrientationAffector::msYawOrientationSpeedRangeEndCmd;
	MeshComponentOrientationAffector::CmdYawOrientationRangeStart			MeshComponentOrientationAffector::msYawOrientationRangeStartCmd;
	MeshComponentOrientationAffector::CmdYawOrientationRangeEnd			MeshComponentOrientationAffector::msYawOrientationRangeEndCmd;

	MeshComponentOrientationAffector::CmdPitchOrientationSpeedRangeStart	MeshComponentOrientationAffector::msPitchOrientationSpeedRangeStartCmd;
	MeshComponentOrientationAffector::CmdPitchOrientationSpeedRangeEnd		MeshComponentOrientationAffector::msPitchOrientationSpeedRangeEndCmd;
	MeshComponentOrientationAffector::CmdPitchOrientationRangeStart			MeshComponentOrientationAffector::msPitchOrientationRangeStartCmd;
	MeshComponentOrientationAffector::CmdPitchOrientationRangeEnd			MeshComponentOrientationAffector::msPitchOrientationRangeEndCmd;

	MeshComponentOrientationAffector::CmdRollOrientationSpeedRangeStart	MeshComponentOrientationAffector::msRollOrientationSpeedRangeStartCmd;
	MeshComponentOrientationAffector::CmdRollOrientationSpeedRangeEnd		MeshComponentOrientationAffector::msRollOrientationSpeedRangeEndCmd;
	MeshComponentOrientationAffector::CmdRollOrientationRangeStart			MeshComponentOrientationAffector::msRollOrientationRangeStartCmd;
	MeshComponentOrientationAffector::CmdRollOrientationRangeEnd			MeshComponentOrientationAffector::msRollOrientationRangeEndCmd;

	//-----------------------------------------------------------------------
	MeshComponentOrientationAffector::MeshComponentOrientationAffector(ParticleSystem* psys)
		:ParticleAffector(psys),
		mYawOrientationSpeedRangeStart(0),
		mYawOrientationSpeedRangeEnd(0),
		mYawOrientationRangeStart(0),
		mYawOrientationRangeEnd(0),
		mPitchOrientationSpeedRangeStart(0),
		mPitchOrientationSpeedRangeEnd(0),
		mPitchOrientationRangeStart(0),
		mPitchOrientationRangeEnd(0),
		mRollOrientationSpeedRangeStart(0),
		mRollOrientationSpeedRangeEnd(0),
		mRollOrientationRangeStart(0),
		mRollOrientationRangeEnd(0)
	{
		mType = "MeshRotator";

		// Init parameters
		if (createParamDictionary("MeshComponentOrientationAffector"))
		{
			ParamDictionary* dict = getParamDictionary();

			dict->addParameter(ParameterDef("yaw_rotation_speed_range_start", 
				"The start of a range of yaw rotation speed.", PT_REAL),
				&msYawOrientationSpeedRangeStartCmd);

			dict->addParameter(ParameterDef("yaw_rotation_speed_range_end", 
				"The end of a range of yaw rotation speed.", PT_REAL),
				&msYawOrientationSpeedRangeEndCmd);

			dict->addParameter(ParameterDef("yaw_rotation_range_start", 
				"The start of a range of yaw rotation angles.", PT_REAL),
				&msYawOrientationRangeStartCmd);

			dict->addParameter(ParameterDef("yaw_rotation_range_end", 
				"The end of a range of yaw rotation angles.", PT_REAL),
				&msYawOrientationRangeEndCmd);

			dict->addParameter(ParameterDef("pitch_rotation_speed_range_start", 
				"The start of a range of pitch rotation speed.", PT_REAL),
				&msPitchOrientationSpeedRangeStartCmd);

			dict->addParameter(ParameterDef("pitch_rotation_speed_range_end", 
				"The end of a range of pitch rotation speed.", PT_REAL),
				&msPitchOrientationSpeedRangeEndCmd);

			dict->addParameter(ParameterDef("pitch_rotation_range_start", 
				"The start of a range of pitch rotation angles.", PT_REAL),
				&msPitchOrientationRangeStartCmd);

			dict->addParameter(ParameterDef("pitch_rotation_range_end", 
				"The end of a range of pitch rotation angles.", PT_REAL),
				&msPitchOrientationRangeEndCmd);

			dict->addParameter(ParameterDef("roll_rotation_speed_range_start", 
				"The start of a range of roll rotation speed.", PT_REAL),
				&msRollOrientationSpeedRangeStartCmd);

			dict->addParameter(ParameterDef("roll_rotation_speed_range_end", 
				"The end of a range of roll rotation speed.", PT_REAL),
				&msRollOrientationSpeedRangeEndCmd);

			dict->addParameter(ParameterDef("roll_rotation_range_start", 
				"The start of a range of roll rotation angles.", PT_REAL),
				&msRollOrientationRangeStartCmd);

			dict->addParameter(ParameterDef("roll_rotation_range_end", 
				"The end of a range of roll rotation angles.", PT_REAL),
				&msRollOrientationRangeEndCmd);
		}
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::_initParticle(Particle* pParticle)
	{
		MeshComponentParticleVisualData *data = static_cast<MeshComponentParticleVisualData *>(pParticle->getVisualData());

		data->mYawRotationSpeed =
			mYawOrientationSpeedRangeStart + 
			(Math::UnitRandom() * 
			(mYawOrientationSpeedRangeEnd - mYawOrientationSpeedRangeStart));

		data->mPitchRotationSpeed =
			mPitchOrientationSpeedRangeStart + 
			(Math::UnitRandom() * 
			(mPitchOrientationSpeedRangeEnd - mPitchOrientationSpeedRangeStart));

		data->mRollRotationSpeed =
			mRollOrientationSpeedRangeStart + 
			(Math::UnitRandom() * 
			(mRollOrientationSpeedRangeEnd - mRollOrientationSpeedRangeStart));

		data->mYawRotation = mYawOrientationRangeStart + Math::UnitRandom() * (mYawOrientationRangeEnd - mYawOrientationRangeStart);
		data->mPitchRotation = mPitchOrientationRangeStart + Math::UnitRandom() * (mPitchOrientationRangeEnd - mPitchOrientationRangeStart);
		data->mRollRotation = mRollOrientationRangeStart + Math::UnitRandom() * (mRollOrientationRangeEnd - mRollOrientationRangeStart);
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::_affectParticles(ParticleSystem* pSystem, Real timeElapsed)
	{
		const std::vector<Particle*> & particles = pSystem->_getActiveParticles();
		Particle *p;
		Real ds;

		// Rotation adjustments by time
		ds = timeElapsed;

		for (auto pi = particles.begin(); pi != particles.end(); pi++)
		{
			p = *pi;

			MeshComponentParticleVisualData *data = static_cast<MeshComponentParticleVisualData *>(p->getVisualData());
			data->mYawRotation = data->mYawRotation + ds * data->mYawRotationSpeed;
			data->mPitchRotation = data->mPitchRotation + ds * data->mPitchRotationSpeed;
			data->mRollRotation = data->mRollRotation + ds * data->mRollRotationSpeed;

			if (data->mYawRotation != Radian(0) || data->mPitchRotation != Radian(0) ||
				data->mRollRotation != Radian(0))
			{
				//pSystem->_notifyParticleRotated(); todo123
				int kk = 0;
			}
				
		}

	}
	//-----------------------------------------------------------------------
	const Radian& MeshComponentOrientationAffector::getOrientationSpeedRangeStart(RotationType type) const
	{
		switch (type)
		{
		case YAW:
			return mYawOrientationSpeedRangeStart;
		case PITCH:
			return mPitchOrientationSpeedRangeStart;
		case ROLL:
			return mRollOrientationSpeedRangeStart;
		}

		// make complier happy
		return mYawOrientationSpeedRangeStart;
	}
	//-----------------------------------------------------------------------
	const Radian& MeshComponentOrientationAffector::getOrientationSpeedRangeEnd(RotationType type) const
	{
		switch (type)
		{
		case YAW:
			return mYawOrientationSpeedRangeEnd;

		case PITCH:
			return mPitchOrientationSpeedRangeEnd;

		case ROLL:
			return mRollOrientationSpeedRangeEnd;
		}

		// make complier happy
		return mYawOrientationSpeedRangeEnd;
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::setRotationOrientationRangeStart(const Radian& val, RotationType type)
	{
		switch (type)
		{
		case YAW:
			mYawOrientationSpeedRangeStart = val;
			break;

		case PITCH:
			mPitchOrientationSpeedRangeStart = val;
			break;

		case ROLL:
			mRollOrientationSpeedRangeStart = val;
			break;
		}
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::setOrientationSpeedRangeEnd(const Radian& val, RotationType type)
	{
		switch (type)
		{
		case YAW:
			mYawOrientationSpeedRangeEnd = val;
			break;

		case PITCH:
			mPitchOrientationSpeedRangeEnd = val;
			break;

		case ROLL:
			mRollOrientationSpeedRangeEnd = val;
			break;
		}
	}
	//-----------------------------------------------------------------------
	const Radian& MeshComponentOrientationAffector::getOrientationRangeStart(RotationType type) const
	{
		switch (type)
		{
		case YAW:
			return mYawOrientationRangeStart;
		case PITCH:
			return mPitchOrientationRangeStart;
		case ROLL:
			return mRollOrientationRangeStart;
		}

		// make complier happy
		return mYawOrientationRangeStart;
	}
	//-----------------------------------------------------------------------
	const Radian& MeshComponentOrientationAffector::getOrientationRangeEnd(RotationType type) const
	{
		switch (type)
		{
		case YAW:
			return mYawOrientationRangeEnd;
		case PITCH:
			return mPitchOrientationRangeEnd;
		case ROLL:
			return mRollOrientationRangeEnd;
		}

		// make complier happy
		return mYawOrientationRangeEnd;
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::setOrientationRangeStart(const Radian& val, RotationType type)
	{
		switch (type)
		{
		case YAW:
			mYawOrientationRangeStart = val;
			break;

		case PITCH:
			mPitchOrientationRangeStart = val;
			break;

		case ROLL:
			mRollOrientationRangeStart = val;
			break;
		}
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::setOrientationRangeEnd(const Radian& val, RotationType type)
	{
		switch (type)
		{
		case YAW:
			mYawOrientationRangeEnd = val;
			break;

		case PITCH:
			mPitchOrientationRangeEnd = val;
			break;

		case ROLL:
			mRollOrientationRangeEnd = val;
			break;
		}
	}
	//-----------------------------------------------------------------------
	///*
	char * MeshComponentOrientationAffector::readFromBuffer(char * pCurrent)
	{
		int length = sizeof(Ogre::Radian) * 12;
		memcpy(&mYawOrientationSpeedRangeStart,pCurrent,12);
		pCurrent += length;
		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void MeshComponentOrientationAffector::saveToFile(std::ofstream & of)
	{
		of.write((const char *)(&mYawOrientationSpeedRangeStart),sizeof(Ogre::Radian) * 12);
	}
	//*/
	bool MeshComponentOrientationAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_MESH_ROTATION_AFFECTOR)
			{
				WARNING_LOG("Load MeshComponentOrientationAffector From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}			
			//属性
			pSerializer->readData(stream,&mYawOrientationSpeedRangeStart,1,sizeof(mYawOrientationSpeedRangeStart));
			pSerializer->readData(stream,&mYawOrientationSpeedRangeEnd,1,sizeof(mYawOrientationSpeedRangeEnd));
			pSerializer->readData(stream,&mYawOrientationRangeStart,1,sizeof(mYawOrientationRangeStart));
			pSerializer->readData(stream,&mYawOrientationRangeEnd,1,sizeof(mYawOrientationRangeEnd));

			pSerializer->readData(stream,&mPitchOrientationSpeedRangeStart,1,sizeof(mPitchOrientationSpeedRangeStart));
			pSerializer->readData(stream,&mPitchOrientationSpeedRangeEnd,1,sizeof(mPitchOrientationSpeedRangeEnd));
			pSerializer->readData(stream,&mPitchOrientationRangeStart,1,sizeof(mPitchOrientationRangeStart));
			pSerializer->readData(stream,&mPitchOrientationRangeEnd,1,sizeof(mPitchOrientationRangeEnd));

			pSerializer->readData(stream,&mRollOrientationSpeedRangeStart,1,sizeof(mRollOrientationSpeedRangeStart));
			pSerializer->readData(stream,&mRollOrientationSpeedRangeEnd,1,sizeof(mRollOrientationSpeedRangeEnd));
			pSerializer->readData(stream,&mRollOrientationRangeStart,1,sizeof(mRollOrientationRangeStart));
			pSerializer->readData(stream,&mRollOrientationRangeEnd,1,sizeof(mRollOrientationRangeEnd));

			return true;
		}
		return false;
	}
	bool MeshComponentOrientationAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	MeshComponentOrientationAffector::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//属性
		tmpSize += sizeof(mYawOrientationSpeedRangeStart);
		tmpSize += sizeof(mYawOrientationSpeedRangeEnd);
		tmpSize += sizeof(mYawOrientationRangeStart);
		tmpSize += sizeof(mYawOrientationRangeEnd);

		tmpSize += sizeof(mPitchOrientationSpeedRangeStart);
		tmpSize += sizeof(mPitchOrientationSpeedRangeEnd);
		tmpSize += sizeof(mPitchOrientationRangeStart);
		tmpSize += sizeof(mPitchOrientationRangeEnd);

		tmpSize += sizeof(mRollOrientationSpeedRangeStart);
		tmpSize += sizeof(mRollOrientationSpeedRangeEnd);
		tmpSize += sizeof(mRollOrientationRangeStart);
		tmpSize += sizeof(mRollOrientationRangeEnd);
		return tmpSize;
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdYawOrientationSpeedRangeEnd::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationSpeedRangeEnd(YAW) );
	}
	void MeshComponentOrientationAffector::CmdYawOrientationSpeedRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationSpeedRangeEnd(StringConverter::parseAngle(val), YAW);
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdYawOrientationSpeedRangeStart::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationSpeedRangeStart(YAW) );
	}
	void MeshComponentOrientationAffector::CmdYawOrientationSpeedRangeStart::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setRotationOrientationRangeStart(StringConverter::parseAngle(val), YAW);
	}

	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdYawOrientationRangeEnd::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationRangeEnd(YAW) );
	}
	void MeshComponentOrientationAffector::CmdYawOrientationRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationRangeEnd(StringConverter::parseAngle(val), YAW);
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdYawOrientationRangeStart::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationRangeStart(YAW) );
	}
	void MeshComponentOrientationAffector::CmdYawOrientationRangeStart::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationRangeStart(StringConverter::parseAngle(val), YAW);
	}

	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdPitchOrientationSpeedRangeEnd::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationSpeedRangeEnd(PITCH) );
	}
	void MeshComponentOrientationAffector::CmdPitchOrientationSpeedRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationSpeedRangeEnd(StringConverter::parseAngle(val), PITCH);
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdPitchOrientationSpeedRangeStart::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationSpeedRangeStart(PITCH) );
	}
	void MeshComponentOrientationAffector::CmdPitchOrientationSpeedRangeStart::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setRotationOrientationRangeStart(StringConverter::parseAngle(val), PITCH);
	}

	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdPitchOrientationRangeEnd::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationRangeEnd(PITCH) );
	}
	void MeshComponentOrientationAffector::CmdPitchOrientationRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationRangeEnd(StringConverter::parseAngle(val), PITCH);
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdPitchOrientationRangeStart::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationRangeStart(PITCH) );
	}
	void MeshComponentOrientationAffector::CmdPitchOrientationRangeStart::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationRangeStart(StringConverter::parseAngle(val), PITCH);
	}

	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdRollOrientationSpeedRangeEnd::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationSpeedRangeEnd(ROLL) );
	}
	void MeshComponentOrientationAffector::CmdRollOrientationSpeedRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationSpeedRangeEnd(StringConverter::parseAngle(val), ROLL);
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdRollOrientationSpeedRangeStart::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationSpeedRangeStart(ROLL) );
	}
	void MeshComponentOrientationAffector::CmdRollOrientationSpeedRangeStart::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setRotationOrientationRangeStart(StringConverter::parseAngle(val), ROLL);
	}

	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdRollOrientationRangeEnd::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationRangeEnd(ROLL) );
	}
	void MeshComponentOrientationAffector::CmdRollOrientationRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationRangeEnd(StringConverter::parseAngle(val), ROLL);
	}
	//-----------------------------------------------------------------------
	String MeshComponentOrientationAffector::CmdRollOrientationRangeStart::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const MeshComponentOrientationAffector*>(target)->getOrientationRangeStart(ROLL) );
	}
	void MeshComponentOrientationAffector::CmdRollOrientationRangeStart::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentOrientationAffector*>(target)->setOrientationRangeStart(StringConverter::parseAngle(val), ROLL);
	}
}

