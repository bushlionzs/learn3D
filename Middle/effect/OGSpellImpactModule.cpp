#include "OgreHeader.h"
#include "OGSpellImpactModule.h"
#include "OGImpactManager.h"

#include <OgreStringConverter.h>

namespace Orphigine	{

	SpellImpactModule::CmdAttachTime	SpellImpactModule::msAttachTimeCmd;
	SpellImpactModule::CmdAttachPoint		SpellImpactModule::msAttachPointCmd;
	SpellImpactModule::CmdEffectTemplateName	SpellImpactModule::msEffectTemplateNameCmd;
	SpellImpactModule::CmdOffsetPos	 SpellImpactModule::msOffsetPosCmd;
	SpellImpactModule::CmdOffsetRotation	SpellImpactModule::msOffsetRotationCmd;
	SpellImpactModule::CmdAttach	SpellImpactModule::msAttachCmd;
	SpellImpactModule::CmdUseAttachRotation	SpellImpactModule::msUseAttachRotationCmd;
	//////////////////////////////////////////////////////////////////////////
	SpellImpactModule::SpellImpactModule() :
	mAttachTime(0.0f), mAttachPoint(""), mEffectTemplateName(""), mEffect(NULL),
		mOffsetPos(Ogre::Vector3::ZERO), mOffsetRotation(Ogre::Quaternion::IDENTITY), mAttach(false),mUseAttachRotation(true)
	{
		initParamDictionary();
	}
	//---------------------------------------------------------------------
	SpellImpactModule::~SpellImpactModule()
	{
		if (mEffect)
		{
			ImpactManager::getSingleton().removeEffect(mEffect,false,false);
			mEffect = NULL;
		}	
	}
	//---------------------------------------------------------------------
	bool SpellImpactModule::initParamDictionary(void)
	{
		if (createParamDictionary("AnimationEffectInfo"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();			

			dict->addParameter(Ogre::ParameterDef("AttachTime", 
				"the time that showing the effect.",
				Ogre::PT_REAL),&msAttachTimeCmd);	  

			dict->addParameter(Ogre::ParameterDef("AttachPoint", 
				"the attached bone or locator.",
				Ogre::PT_STRING),&msAttachPointCmd);	  

			dict->addParameter(Ogre::ParameterDef("EffectTemplateName", 
				"name of effect template.",
				Ogre::PT_STRING),&msEffectTemplateNameCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetPos", 
				"offset position to the attach point.",
				Ogre::PT_VECTOR3),&msOffsetPosCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetRotation", 
				"offset orientation to the attach point.",
				Ogre::PT_QUATERNION),&msOffsetRotationCmd);	  

			dict->addParameter(Ogre::ParameterDef("Attach", 
				"whether the effect will move along with the attach point.",
				Ogre::PT_BOOL),&msAttachCmd);	  

			dict->addParameter(Ogre::ParameterDef("UseAttachRotation",
				"Use attach point rotation to update offset position and offset rotation.",
				Ogre::PT_BOOL),&msUseAttachRotationCmd);

			return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	void SpellImpactModule::copyParameters(SpellImpactModule& newInfo) const
	{
		newInfo.mAttachTime = mAttachTime;
		newInfo.mAttachPoint = mAttachPoint;
		newInfo.mEffectTemplateName = mEffectTemplateName;
		newInfo.mOffsetPos = mOffsetPos;
		newInfo.mOffsetRotation = mOffsetRotation;
		newInfo.mAttach = mAttach;
		newInfo.mUseAttachRotation=mUseAttachRotation;
	}
	//////////////////////////////////////////////////////////////////////////
	String SpellImpactModule::CmdAttachTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellImpactModule *>(target)->getAttachTime() );
	}
	void SpellImpactModule::CmdAttachTime::doSet(void* target, const String& val)
	{
		static_cast<SpellImpactModule *>(target)->setAttachTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdAttachTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellImpactModule *>(target)->setAttachTime(
			static_cast<const SpellImpactModule *>(source)->getAttachTime() );
	}
#endif

	String SpellImpactModule::CmdAttachPoint::doGet(const void* target) const
	{
		return static_cast<const SpellImpactModule *>(target)->getAttachPoint();
	}
	void SpellImpactModule::CmdAttachPoint::doSet(void* target, const String& val)
	{
		static_cast<SpellImpactModule *>(target)->setAttachPoint(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdAttachPoint::doCopy(void* target, const void* source)
	{
		static_cast<SpellImpactModule *>(target)->setAttachPoint(
			static_cast<const SpellImpactModule *>(source)->getAttachPoint() );
	}
#endif

	String SpellImpactModule::CmdEffectTemplateName::doGet(const void* target) const
	{
		return static_cast<const SpellImpactModule *>(target)->getEffectTemplateName();
	}
	void SpellImpactModule::CmdEffectTemplateName::doSet(void* target, const String& val)
	{
		static_cast<SpellImpactModule *>(target)->setEffectTemplateName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdEffectTemplateName::doCopy(void* target, const void* source)
	{
		static_cast<SpellImpactModule *>(target)->setEffectTemplateName(
			static_cast<const SpellImpactModule *>(source)->getEffectTemplateName() );
	}
#endif

	String SpellImpactModule::CmdOffsetPos::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellImpactModule *>(target)->getOffsetPos() );
	}
	void SpellImpactModule::CmdOffsetPos::doSet(void* target, const String& val)
	{
		static_cast<SpellImpactModule *>(target)->setOffsetPos(Ogre::StringConverter::parseVector3(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdOffsetPos::doCopy(void* target, const void* source)
	{
		static_cast<SpellImpactModule *>(target)->setOffsetPos(
			static_cast<const SpellImpactModule *>(source)->getOffsetPos() );
	}
#endif

	String SpellImpactModule::CmdOffsetRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellImpactModule *>(target)->getOffsetRotation() );
	}
	void SpellImpactModule::CmdOffsetRotation::doSet(void* target, const String& val)
	{
		static_cast<SpellImpactModule *>(target)->setOffsetRotation(Ogre::StringConverter::parseQuaternion(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdOffsetRotation::doCopy(void* target, const void* source)
	{
		static_cast<SpellImpactModule *>(target)->setOffsetRotation(
			static_cast<const SpellImpactModule *>(source)->getOffsetRotation() );
	}
#endif

	String SpellImpactModule::CmdAttach::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellImpactModule *>(target)->getAttach() );
	}
	void SpellImpactModule::CmdAttach::doSet(void* target, const String& val)
	{
		static_cast<SpellImpactModule *>(target)->setAttach(Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdAttach::doCopy(void* target, const void* source)
	{
		static_cast<SpellImpactModule *>(target)->setAttach(
			static_cast<const SpellImpactModule *>(source)->getAttach() );
	}
#endif

	String SpellImpactModule::CmdUseAttachRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellImpactModule*>(target)->getUseAttachRotation());
	}
	void SpellImpactModule::CmdUseAttachRotation::doSet(void* target,const String& val)
	{
		static_cast<SpellImpactModule*>(target)->setUseAttachRotation(Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellImpactModule::CmdUseAttachRotation::doCopy(void* target,const void* source)
	{
		static_cast<SpellImpactModule*>(target)->setUseAttachRotation(
			static_cast<const SpellImpactModule*>(source)->getUseAttachRotation());
	}
#endif

	/*
	float mAttachTime;
	String mAttachPoint;
	String mEffectTemplateName;
	Ogre::Vector3 mOffsetPos;
	Ogre::Quaternion mOffsetRotation;
	bool mAttach;
	bool mUseAttachRotation;
	*/

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	void SpellImpactModule::loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream)
	{
		serializer->readFloats(stream,&mAttachTime,1);
		mAttachPoint = serializer->readString(stream);
		mEffectTemplateName = serializer->readString(stream);
		serializer->readObject(stream,mOffsetPos);
		serializer->readObject(stream,mOffsetRotation);
		serializer->readBools(stream,&mAttach,1);
		serializer->readBools(stream,&mUseAttachRotation,1);
	}

	void SpellImpactModule::saveBinary( SpellsSerializer* serializer )
	{
		
	}

	std::size_t SpellImpactModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(float);
		tmpSize += mAttachPoint.length() + 1;
		tmpSize += mEffectTemplateName.length() + 1;
		tmpSize += sizeof(Ogre::Vector3);
		tmpSize += sizeof(Ogre::Quaternion);
		tmpSize += sizeof(bool);
		tmpSize += sizeof(bool);

		return tmpSize;
	}
}