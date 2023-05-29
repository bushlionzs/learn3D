#include "OgreHeader.h"
#include "OGSpellSceneLightModule.h"

#include <OgreStringConverter.h>

namespace Orphigine
{
	SpellSceneLightModule::CmdAttachTime  SpellSceneLightModule::msAttachTimeCmd;
	SpellSceneLightModule::CmdLastTime    SpellSceneLightModule::msLastTimeCmd;
	SpellSceneLightModule::CmdFadeInTime  SpellSceneLightModule::msFadeInTimeCmd;
	SpellSceneLightModule::CmdFadeOutTime SpellSceneLightModule::msFadeOutTimeCmd;
	SpellSceneLightModule::CmdDestColour  SpellSceneLightModule::msDestColourCmd;

	//////////////////////////////////////////////////////////////////////////
	SpellSceneLightModule::SpellSceneLightModule(void) :
	mAttachTime(0.0f),
		mLastTime(0.0f),
		mFadeInTime(0.0f),
		mFadeOutTime(0.0f),
		mDestColour(Ogre::ColourValue::Black)
	{
		if (createParamDictionary("AnimationSceneLightInfo"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("AttachTime", 
				"the time that starting changing the light.",
				Ogre::PT_REAL),&msAttachTimeCmd);	

			dict->addParameter(Ogre::ParameterDef("LastTime", 
				"the last time that changing the light.",
				Ogre::PT_REAL),&msLastTimeCmd);			

			dict->addParameter(Ogre::ParameterDef("FadeInTime", 
				"the fade in time.",
				Ogre::PT_REAL),&msFadeInTimeCmd);

			dict->addParameter(Ogre::ParameterDef("FadeOutTime", 
				"the fade out time.",
				Ogre::PT_REAL),&msFadeOutTimeCmd);

			dict->addParameter(Ogre::ParameterDef("DestColour", 
				"the dest colour of light.",
				Ogre::PT_COLOURVALUE),&msDestColourCmd);
		}
	}
	//-----------------------------------------------------------------------
	void SpellSceneLightModule::copyParameters(SpellSceneLightModule& newInfo) const
	{
		newInfo.mAttachTime = mAttachTime;
		newInfo.mLastTime = mLastTime;
		newInfo.mFadeInTime = mFadeInTime;
		newInfo.mFadeOutTime = mFadeOutTime;
		newInfo.mDestColour = mDestColour;
	}
	//////////////////////////////////////////////////////////////////////////
	String SpellSceneLightModule::CmdAttachTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSceneLightModule *>(target)->getAttachTime() );
	}
	void SpellSceneLightModule::CmdAttachTime::doSet(void* target, const String& val)
	{
		static_cast<SpellSceneLightModule *>(target)->setAttachTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSceneLightModule::CmdAttachTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellSceneLightModule *>(target)->setAttachTime(
			static_cast<const SpellSceneLightModule *>(source)->getAttachTime() );
	}
#endif

	String SpellSceneLightModule::CmdLastTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSceneLightModule *>(target)->getLastTime() );
	}
	void SpellSceneLightModule::CmdLastTime::doSet(void* target, const String& val)
	{
		static_cast<SpellSceneLightModule *>(target)->setLastTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSceneLightModule::CmdLastTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellSceneLightModule *>(target)->setLastTime(
			static_cast<const SpellSceneLightModule *>(source)->getLastTime() );
	}
#endif

	String SpellSceneLightModule::CmdFadeInTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSceneLightModule *>(target)->getFadeInTime() );
	}
	void SpellSceneLightModule::CmdFadeInTime::doSet(void* target, const String& val)
	{
		static_cast<SpellSceneLightModule *>(target)->setFadeInTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSceneLightModule::CmdFadeInTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellSceneLightModule *>(target)->setFadeInTime(
			static_cast<const SpellSceneLightModule *>(source)->getFadeInTime() );
	}
#endif

	String SpellSceneLightModule::CmdFadeOutTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSceneLightModule *>(target)->getFadeOutTime() );
	}
	void SpellSceneLightModule::CmdFadeOutTime::doSet(void* target, const String& val)
	{
		static_cast<SpellSceneLightModule *>(target)->setFadeOutTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSceneLightModule::CmdFadeOutTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellSceneLightModule *>(target)->setFadeOutTime(
			static_cast<const SpellSceneLightModule *>(source)->getFadeOutTime() );
	}
#endif

	String SpellSceneLightModule::CmdDestColour::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSceneLightModule *>(target)->getDestColour() );
	}
	void SpellSceneLightModule::CmdDestColour::doSet(void* target, const String& val)
	{
		static_cast<SpellSceneLightModule *>(target)->setDestColour(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSceneLightModule::CmdDestColour::doCopy(void* target, const void* source)
	{
		static_cast<SpellSceneLightModule *>(target)->setDestColour(
			static_cast<const SpellSceneLightModule *>(source)->getDestColour() );
	}
#endif

	//////////////////////////////////////////////////////////////////////////
	/*
	float mAttachTime;
	float mLastTime;
	float mFadeInTime;
	float mFadeOutTime;
	Ogre::ColourValue mDestColour;
	*/
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	void SpellSceneLightModule::loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream)
	{
		serializer->readFloats(stream,&mAttachTime,1);
		serializer->readFloats(stream,&mLastTime,1);
		serializer->readFloats(stream,&mFadeInTime,1);
		serializer->readFloats(stream,&mFadeOutTime,1);
		stream->read(&mDestColour,sizeof(Ogre::ColourValue));
	}

	void SpellSceneLightModule::saveBinary( SpellsSerializer* serializer )
	{
	
	}

	std::size_t SpellSceneLightModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(float) * 4;
		tmpSize += sizeof(Ogre::ColourValue);

		return tmpSize;
	}
}