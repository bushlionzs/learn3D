#include "OgreHeader.h"
#include "OGSpellSoundModule.h"

#include <OgreStringConverter.h>

namespace Orphigine	{

	SpellSoundModule::CmdAttachTime	SpellSoundModule::msAttachTimeCmd;
	SpellSoundModule::CmdSoundName    SpellSoundModule::msSoundNameCmd;
	SpellSoundModule::CmdLooping		SpellSoundModule::ms_isLoopingCmd;

	//////////////////////////////////////////////////////////////////////////
	SpellSoundModule::SpellSoundModule() :	
	mAttachTime(0.0f), mSoundName(""), mSoundHandle(-1), mPlayed(false)
	{
		if (createParamDictionary("AnimationSound"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("SoundName", 
				"the file name of sound.",
				Ogre::PT_STRING),&msSoundNameCmd);	

			dict->addParameter(Ogre::ParameterDef("AttachTime", 
				"the time that play sound.",
				Ogre::PT_REAL),&msAttachTimeCmd);	

			dict->addParameter(Ogre::ParameterDef("IsLooping",
				"Is the sound looping",
				Ogre::PT_BOOL),&ms_isLoopingCmd);
		}
	}
	//-----------------------------------------------------------------------
	void SpellSoundModule::copyParameters(SpellSoundModule& newInfo) const
	{
		newInfo.mAttachTime = mAttachTime;
		newInfo.mSoundName = mSoundName;
		newInfo.m_isLooping = m_isLooping;
	}

	bool SpellSoundModule::getLooping() const
	{
		return m_isLooping;
	}

	void SpellSoundModule::setLooping( bool val )
	{
		m_isLooping = val;
	}
	//////////////////////////////////////////////////////////////////////////
	String SpellSoundModule::CmdAttachTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSoundModule *>(target)->getAttachTime() );
	}
	void SpellSoundModule::CmdAttachTime::doSet(void* target, const String& val)
	{
		static_cast<SpellSoundModule *>(target)->setAttachTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSoundModule::CmdAttachTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellSoundModule *>(target)->setAttachTime(
			static_cast<const SpellSoundModule *>(source)->getAttachTime() );
	}
#endif

	String SpellSoundModule::CmdSoundName::doGet(const void* target) const
	{
		return static_cast<const SpellSoundModule *>(target)->getSoundName();
	}
	void SpellSoundModule::CmdSoundName::doSet(void* target, const String& val)
	{
		static_cast<SpellSoundModule *>(target)->setSoundName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellSoundModule::CmdSoundName::doCopy(void* target, const void* source)
	{
		static_cast<SpellSoundModule *>(target)->setSoundName(
			static_cast<const SpellSoundModule *>(source)->getSoundName() );
	}
#endif

	Ogre::String SpellSoundModule::CmdLooping::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellSoundModule*>(target)->getLooping());
	}

	void SpellSoundModule::CmdLooping::doSet( void* target, const String& val )
	{
		static_cast<SpellSoundModule*>(target)->setLooping(
			Ogre::StringConverter::parseBool(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void SpellSoundModule::CmdLooping::doCopy( void* target, const void* source )
	{
		static_cast<SpellSoundModule*>(target)->setLooping(
			static_cast<const SpellSoundModule*>(source)->getLooping());
	}
#endif // OGRE_STRING_INTERFACE_COPY

	//////////////////////////////////////////////////////////////////////////
	/*
	float	mAttachTime;
	String	mSoundName;
	bool	m_isLooping;
	*/
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	void SpellSoundModule::loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream)
	{
		serializer->readFloats(stream,&mAttachTime,1);
		mSoundName = serializer->readString(stream);
		serializer->readBools(stream,&m_isLooping,1);
	}

	void SpellSoundModule::saveBinary( SpellsSerializer* serializer )
	{

	}

	std::size_t SpellSoundModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(float);
		tmpSize += mSoundName.length() + 1;
		tmpSize += sizeof(bool);

		return tmpSize;
	}
}