#include "OgreHeader.h"
#include "OGAASWeaponAnimSequenceNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASAnimation.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASWeaponAnimSequenceNode::CmdLongHandle		AASWeaponAnimSequenceNode::ms_longHandleCmd;
	AASWeaponAnimSequenceNode::CmdFalchion			AASWeaponAnimSequenceNode::ms_falchionCmd;
	AASWeaponAnimSequenceNode::CmdGavel				AASWeaponAnimSequenceNode::ms_gavelCmd;
	AASWeaponAnimSequenceNode::CmdBow				AASWeaponAnimSequenceNode::ms_bowCmd;
	AASWeaponAnimSequenceNode::CmdGun				AASWeaponAnimSequenceNode::ms_gunCmd;
	AASWeaponAnimSequenceNode::CmdSword				AASWeaponAnimSequenceNode::ms_swordCmd;
	AASWeaponAnimSequenceNode::CmdFlag				AASWeaponAnimSequenceNode::ms_flagCmd;
	AASWeaponAnimSequenceNode::CmdUnarmed			AASWeaponAnimSequenceNode::ms_unarmedCmd;
	AASWeaponAnimSequenceNode::CmdWand				AASWeaponAnimSequenceNode::ms_wandCmd;
	AASWeaponAnimSequenceNode::CmdEpee				AASWeaponAnimSequenceNode::ms_epeeCmd;

	AASWeaponAnimSequenceNode::AASWeaponAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASAnimSequenceNode("WeaponAnimSequence",system,handle)
	{
		initParameter("WeaponAnimSequence");
	}

	AASWeaponAnimSequenceNode::AASWeaponAnimSequenceNode(String name, AdvancedAnimationSystem* system,unsigned short handle)
		: AASAnimSequenceNode(name,system,handle)
	{		
	}

	bool AASWeaponAnimSequenceNode::initParameter(const String& typeName)	
	{
		m_longHandle = "";
		m_falchion = "";
		m_gavel = "";
		m_bow = "";
		m_gun = "";
		m_sword = "";
		m_flag = "";
		m_unarmed = "";
		m_wand = "";
		m_epee = "";
		m_currentWeaponType = "";

		if (AASAnimSequenceNode::initParameter(m_type.c_str()))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef(
				"LongHandle","The weapon type",Ogre::PT_STRING),&ms_longHandleCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Falchion","The weapon type",Ogre::PT_STRING),&ms_falchionCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Gavel","The weapon type",Ogre::PT_STRING),&ms_gavelCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Bow","The weapon type",Ogre::PT_STRING),&ms_bowCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Gun","The weapon type",Ogre::PT_STRING),&ms_gunCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Sword","The weapon type",Ogre::PT_STRING),&ms_swordCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Flag","The weapon type",Ogre::PT_STRING),&ms_flagCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Unarmed","The weapon type",Ogre::PT_STRING),&ms_unarmedCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Wand","The weapon type",Ogre::PT_STRING),&ms_wandCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Epee","The weapon type",Ogre::PT_STRING),&ms_epeeCmd);
			return true;

		}
		return false;
	}

	AASWeaponAnimSequenceNode::~AASWeaponAnimSequenceNode()
	{

	}

	void AASWeaponAnimSequenceNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
	}

	void AASWeaponAnimSequenceNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,
		Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		AASAnimSequenceNode::readFromBinary(serializer,stream,system);

		
		m_longHandle		= serializer->readString(stream).c_str();

		m_falchion			= serializer->readString(stream).c_str();

		m_gavel				= serializer->readString(stream).c_str();

		m_bow				= serializer->readString(stream).c_str();

		m_gun				= serializer->readString(stream).c_str();

		m_sword				= serializer->readString(stream).c_str();

		m_flag				= serializer->readString(stream).c_str();

		m_unarmed			= serializer->readString(stream).c_str();

		m_wand				= serializer->readString(stream).c_str();

		m_epee				= serializer->readString(stream).c_str();

	}

	size_t AASWeaponAnimSequenceNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = AASAnimSequenceNode::calcSize(serializer);


		tmpSize += m_longHandle.length() + 1;

		tmpSize += m_falchion.length() + 1;

		tmpSize += m_gavel.length() + 1;

		tmpSize += m_bow.length() + 1;

		tmpSize += m_gun.length() + 1;

		tmpSize += m_sword.length() + 1;

		tmpSize += m_flag.length() + 1;

		tmpSize += m_unarmed.length() + 1;

		tmpSize += m_wand.length() + 1;

		tmpSize += m_epee.length() + 1;

		return tmpSize;
	}

	void AASWeaponAnimSequenceNode::_refreshAnimation()
	{
		AASAnimSequenceNode::_refreshAnimation();

		String	tmpWeaponTypeName = m_owner->getWeaponTypeName();

		if(tmpWeaponTypeName.empty())
			return;

		if (m_currentWeaponType != tmpWeaponTypeName.c_str())
		{
			String	tmpActualWeaponAnimation = _getAnimationByWeaponTypeName(tmpWeaponTypeName);

			if(NULL != m_animation )
			{
				if(tmpActualWeaponAnimation != m_animation->getAnimationName())
				{
					_disableAnimState();

					m_animationID= m_owner->getAnimationIdByName(tmpActualWeaponAnimation);
					m_animation = m_owner->getAnimation(m_animationID);
				}
			}
			else
			{
				m_animationID= m_owner->getAnimationIdByName(tmpActualWeaponAnimation);
				m_animation = m_owner->getAnimation(m_animationID);
			}

			m_currentWeaponType = tmpWeaponTypeName.c_str();
		}
		
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getLongHandle() const
	{
		return m_longHandle;
	}

	void AASWeaponAnimSequenceNode::setLongHandle(const Ogre::String& val)
	{
		m_longHandle = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getFalchion() const
	{
		return m_falchion;
	}

	void AASWeaponAnimSequenceNode::setFalchion(const Ogre::String& val)
	{
		m_falchion = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getGavel() const
	{
		return m_gavel;
	}

	void AASWeaponAnimSequenceNode::setGavel(const Ogre::String& val)
	{
		m_gavel = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getBow() const
	{
		return m_bow;
	}

	void AASWeaponAnimSequenceNode::setBow(const Ogre::String& val)
	{
		m_bow = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getGun() const
	{
		return m_gun;
	}

	void AASWeaponAnimSequenceNode::setGun(const Ogre::String& val)
	{
		m_gun = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getSword() const
	{
		return m_sword;
	}

	void AASWeaponAnimSequenceNode::setSword(const Ogre::String& val)
	{
		m_sword = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getFlag() const
	{
		return m_flag;
	}

	void AASWeaponAnimSequenceNode::setFlag(const Ogre::String& val)
	{
		m_flag = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getUnarmed() const
	{
		return m_unarmed;
	}

	void AASWeaponAnimSequenceNode::setUnarmed(const Ogre::String& val)
	{
		m_unarmed = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getWand() const
	{
		return m_wand;
	}

	void AASWeaponAnimSequenceNode::setWand(const Ogre::String& val)
	{
		m_wand = val;
	}

	const Ogre::String& AASWeaponAnimSequenceNode::getEpee() const
	{
		return m_epee;
	}

	void AASWeaponAnimSequenceNode::setEpee(const Ogre::String& val)
	{
		m_epee = val;
	}

	Ogre::String AASWeaponAnimSequenceNode::_getAnimationByWeaponTypeName( const String& weaponType )
	{
	
		String tmpAnimationName = "";

		if( "LongHandle" == weaponType)
			tmpAnimationName = m_longHandle.c_str();
		else if( "Falchion" == weaponType)
			tmpAnimationName = m_falchion.c_str();
		else if( "Gavel" == weaponType)
			tmpAnimationName = m_gavel.c_str();
		else if("Bow" == weaponType)
			tmpAnimationName = m_bow.c_str();
		else if("Gun" == weaponType)
			tmpAnimationName = m_gun.c_str();
		else if("Sword" == weaponType)
			tmpAnimationName = m_sword.c_str();
		else if("Flag" == weaponType)
			tmpAnimationName = m_flag.c_str();
		else if("Unarmed" == weaponType)
			tmpAnimationName = m_unarmed.c_str();
		else if("Wand" == weaponType)
			tmpAnimationName = m_wand.c_str();
		else if("Epee" == weaponType)
			tmpAnimationName = m_epee.c_str();
		else
			tmpAnimationName = m_animationName.c_str();

		return tmpAnimationName;
	}

	void AASWeaponAnimSequenceNode::copyParameters( AASNode* dest )
	{
		AASAnimSequenceNode::copyParameters(dest);

		AASWeaponAnimSequenceNode* destNode = (AASWeaponAnimSequenceNode*)dest;
		assert(destNode && "AASWeaponAnimSequenceNode::copyParameters");

		destNode->m_longHandle	= m_longHandle;
		destNode->m_falchion =	  m_falchion;
		destNode->m_gavel = 	  m_gavel;
		destNode->m_bow	=		  m_bow;
		destNode->m_gun =		  m_gun;
		destNode->m_sword =		  m_sword;
		destNode->m_flag =		  m_flag;
		destNode->m_unarmed	= 	  m_unarmed;
		destNode->m_wand =		  m_wand;
		destNode->m_epee =		  m_epee;
	}
	String AASWeaponAnimSequenceNode::CmdLongHandle::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getLongHandle().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdLongHandle::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setLongHandle(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdFalchion::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getFalchion().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdFalchion::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setFalchion(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdGavel::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getGavel().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdGavel::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setGavel(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdBow::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getBow().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdBow::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setBow(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdGun::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getGun().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdGun::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setGun(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdSword::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getSword().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdSword::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setSword(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdFlag::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getFlag().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdFlag::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setFlag(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdUnarmed::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getUnarmed().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdUnarmed::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setUnarmed(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdWand::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getWand().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdWand::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setWand(val.c_str());
	}

	String AASWeaponAnimSequenceNode::CmdEpee::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimSequenceNode*>(target)->getEpee().c_str();
	}

	void AASWeaponAnimSequenceNode::CmdEpee::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimSequenceNode*>(target)->setEpee(val.c_str());
	}
}