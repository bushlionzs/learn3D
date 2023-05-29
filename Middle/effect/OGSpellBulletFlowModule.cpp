#include "OgreHeader.h"
#include "OGSpellBulletFlowModule.h"
#include "OGBulletFlowSystemManager.h"

#include <OgreStringConverter.h>

namespace Orphigine	{

	SpellBulletFlowModule::CmdAttachTime	SpellBulletFlowModule::ms_attachTimeCmd;
	SpellBulletFlowModule::CmdAttachPoint		SpellBulletFlowModule::ms_attachPointCmd;
	SpellBulletFlowModule::CmdBulletFlowTemplateName	SpellBulletFlowModule::ms_bulletFlowTemplateNameCmd;
	SpellBulletFlowModule::CmdOffsetPos	 SpellBulletFlowModule::ms_offsetPosCmd;
	SpellBulletFlowModule::CmdOffsetRotation	SpellBulletFlowModule::ms_offsetRotationCmd;
	SpellBulletFlowModule::CmdAttach		SpellBulletFlowModule::ms_attachCmd;
	SpellBulletFlowModule::CmdUseAttachRotation	SpellBulletFlowModule::msUseAttachRotationCmd;
	//////////////////////////////////////////////////////////////////////////
	SpellBulletFlowModule::SpellBulletFlowModule() :
	m_attachTime(0.0f), m_attachPoint(""), m_bulletFlowTemplateName(""),
		m_offsetPos(Ogre::Vector3::ZERO), m_offsetRotation(Ogre::Quaternion::IDENTITY),m_isAttach(false),mUseAttachRotation(true)
	{
		initParamDictionary();
	}
	//---------------------------------------------------------------------
	SpellBulletFlowModule::~SpellBulletFlowModule()
	{
	}
	//---------------------------------------------------------------------
	bool SpellBulletFlowModule::initParamDictionary(void)
	{
		if (createParamDictionary("AnimationBulletFlow"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();			

			dict->addParameter(Ogre::ParameterDef("AttachTime", 
				"the time that showing the effect.",
				Ogre::PT_REAL),&ms_attachTimeCmd);	  

			dict->addParameter(Ogre::ParameterDef("AttachPoint", 
				"the attached bone or locator.",
				Ogre::PT_STRING),&ms_attachPointCmd);	  

			dict->addParameter(Ogre::ParameterDef("BulletFlowTemplateName", 
				"name of BulletFlow template.",
				Ogre::PT_STRING),&ms_bulletFlowTemplateNameCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetPos", 
				"offset position to the attach point.",
				Ogre::PT_VECTOR3),&ms_offsetPosCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetRotation", 
				"offset orientation to the attach point.",
				Ogre::PT_QUATERNION),&ms_offsetRotationCmd);	  

			dict->addParameter(Ogre::ParameterDef("Attach", 
				"whether the effect will move along with the attach point.",
				Ogre::PT_BOOL),&ms_attachCmd);	  

			dict->addParameter(Ogre::ParameterDef("UseAttachRotation",
				"Use attach point rotation to update offset position and offset rotation.",
				Ogre::PT_BOOL),&msUseAttachRotationCmd);
			return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	void SpellBulletFlowModule::copyParameters(SpellBulletFlowModule& newInfo) const
	{
		newInfo.m_attachTime = m_attachTime;
		newInfo.m_attachPoint = m_attachPoint;
		newInfo.m_bulletFlowTemplateName = m_bulletFlowTemplateName;
		newInfo.m_offsetPos = m_offsetPos;
		newInfo.m_offsetRotation = m_offsetRotation;
		newInfo.m_isAttach = m_isAttach;
		newInfo.mUseAttachRotation=mUseAttachRotation;
	}

	void SpellBulletFlowModule::setAttachTime( float time )
	{
		m_attachTime = time;
	}

	float SpellBulletFlowModule::getAttachTime( void ) const
	{
		return m_attachTime;
	}

	void SpellBulletFlowModule::setAttachPoint( const String &point )
	{
		m_attachPoint = point;
	}

	const String& SpellBulletFlowModule::getAttachPoint( void ) const
	{
		return m_attachPoint;
	}

	void SpellBulletFlowModule::setBulletFlowTemplateName( const String &name )
	{
		m_bulletFlowTemplateName = name;
	}

	const String& SpellBulletFlowModule::getBulletFlowTemplateName( void ) const
	{
		return m_bulletFlowTemplateName;
	}

	void SpellBulletFlowModule::setOffsetPos( const Ogre::Vector3 &pos )
	{
		m_offsetPos = pos;
	}

	const Ogre::Vector3& SpellBulletFlowModule::getOffsetPos( void ) const
	{
		return m_offsetPos;
	}

	void SpellBulletFlowModule::setOffsetRotation( const Ogre::Quaternion &rotation )
	{
		m_offsetRotation = rotation;
	}

	const Ogre::Quaternion& SpellBulletFlowModule::getOffsetRotation( void ) const
	{
		return m_offsetRotation;
	}

	const bool& SpellBulletFlowModule::getAttach() const
	{
		return m_isAttach;
	}

	void SpellBulletFlowModule::setAttach( const bool& val )
	{
		m_isAttach = val;
	}


	//////////////////////////////////////////////////////////////////////////
	String SpellBulletFlowModule::CmdAttachTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellBulletFlowModule *>(target)->getAttachTime() );
	}
	void SpellBulletFlowModule::CmdAttachTime::doSet(void* target, const String& val)
	{
		static_cast<SpellBulletFlowModule *>(target)->setAttachTime(Ogre::StringConverter::parseReal(val));
	}

	String SpellBulletFlowModule::CmdAttachPoint::doGet(const void* target) const
	{
		return static_cast<const SpellBulletFlowModule *>(target)->getAttachPoint();
	}
	void SpellBulletFlowModule::CmdAttachPoint::doSet(void* target, const String& val)
	{
		static_cast<SpellBulletFlowModule *>(target)->setAttachPoint(val);
	}

	String SpellBulletFlowModule::CmdBulletFlowTemplateName::doGet(const void* target) const
	{
		return static_cast<const SpellBulletFlowModule *>(target)->getBulletFlowTemplateName();
	}
	void SpellBulletFlowModule::CmdBulletFlowTemplateName::doSet(void* target, const String& val)
	{
		static_cast<SpellBulletFlowModule *>(target)->setBulletFlowTemplateName(val);
	}

	String SpellBulletFlowModule::CmdOffsetPos::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellBulletFlowModule *>(target)->getOffsetPos() );
	}
	void SpellBulletFlowModule::CmdOffsetPos::doSet(void* target, const String& val)
	{
		static_cast<SpellBulletFlowModule *>(target)->setOffsetPos(Ogre::StringConverter::parseVector3(val));
	}

	String SpellBulletFlowModule::CmdOffsetRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellBulletFlowModule *>(target)->getOffsetRotation() );
	}
	void SpellBulletFlowModule::CmdOffsetRotation::doSet(void* target, const String& val)
	{
		static_cast<SpellBulletFlowModule *>(target)->setOffsetRotation(Ogre::StringConverter::parseQuaternion(val));
	}

	Ogre::String SpellBulletFlowModule::CmdAttach::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellBulletFlowModule*>(target)->getAttach());
	}

	void SpellBulletFlowModule::CmdAttach::doSet( void* target, const String& val )
	{
		static_cast<SpellBulletFlowModule*>(target)->setAttach(
			Ogre::StringConverter::parseBool(val));
	}

	String SpellBulletFlowModule::CmdUseAttachRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellBulletFlowModule*>(target)->getUseAttachRotation());
	}
	void SpellBulletFlowModule::CmdUseAttachRotation::doSet(void* target,const String& val)
	{
		static_cast<SpellBulletFlowModule*>(target)->setUseAttachRotation(Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellBulletFlowModule::CmdUseAttachRotation::doCopy(void* target,const void* source)
	{
		static_cast<SpellBulletFlowModule*>(target)->setUseAttachRotation(
			static_cast<const SpellBulletFlowModule*>(source)->getUseAttachRotation());
	}
#endif

	//////////////////////////////////////////////////////////////////////////
	/*
	float					m_attachTime;
	String					m_attachPoint;
	String					m_bulletFlowTemplateName;
	Ogre::Vector3			m_offsetPos;
	Ogre::Quaternion		m_offsetRotation;
	bool					m_isAttach;
	bool					mUseAttachRotation;
	*/
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	void SpellBulletFlowModule::loadBinary( SpellsSerializer* serializer,Ogre::DataStreamPtr& stream )
	{
		serializer->readFloats(stream,&m_attachTime,1);
		m_attachPoint = serializer->readString(stream);
		m_bulletFlowTemplateName = serializer->readString(stream);
		serializer->readObject(stream,m_offsetPos);
		serializer->readObject(stream,m_offsetRotation);
		serializer->readBools(stream,&m_isAttach,1);
		serializer->readBools(stream,&mUseAttachRotation,1);
	}

	void SpellBulletFlowModule::saveBinary( SpellsSerializer* serializer )
	{
		
	}

	std::size_t SpellBulletFlowModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(float);
		tmpSize += m_attachPoint.length() + 1;
		tmpSize += m_bulletFlowTemplateName.length() + 1;
		tmpSize += sizeof(Ogre::Vector3);
		tmpSize += sizeof(Ogre::Quaternion);
		tmpSize += sizeof(bool) * 2;

		return tmpSize;
	}
}


