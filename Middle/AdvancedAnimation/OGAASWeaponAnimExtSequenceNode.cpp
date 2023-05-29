#include "OgreHeader.h"
#include "OGAASWeaponAnimExtSequenceNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASAnimation.h"

namespace Orphigine
{

	//-------------
	AASWeaponAnimExtSequenceNode::CmdSpear				AASWeaponAnimExtSequenceNode::ms_spearCmd;
	AASWeaponAnimExtSequenceNode::CmdToken				AASWeaponAnimExtSequenceNode::ms_tokenCmd;
	AASWeaponAnimExtSequenceNode::CmdCrossbow			AASWeaponAnimExtSequenceNode::ms_crossbowCmd;
	AASWeaponAnimExtSequenceNode::CmdFiregun			AASWeaponAnimExtSequenceNode::ms_firegunCmd;
	AASWeaponAnimExtSequenceNode::CmdCross				AASWeaponAnimExtSequenceNode::ms_crossCmd;
	AASWeaponAnimExtSequenceNode::CmdFan				AASWeaponAnimExtSequenceNode::ms_fanCmd;
	//-------------

	AASWeaponAnimExtSequenceNode::AASWeaponAnimExtSequenceNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASWeaponAnimSequenceNode("WeaponAnimExtSequence",system,handle)
	{
		//---------
		m_Spear = "";
		m_Token = "";
		m_Crossbow = "";
		m_Firegun = "";
		m_Cross = "";
		m_Fan = "";
		//---------	

		if (AASWeaponAnimSequenceNode::initParameter(m_type.c_str()))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			//--------------------

			tmpDict->addParameter(Ogre::ParameterDef(
				"Spear","The weapon type",Ogre::PT_STRING),&ms_spearCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Token","The weapon type",Ogre::PT_STRING),&ms_tokenCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Crossbow","The weapon type",Ogre::PT_STRING),&ms_crossbowCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Firegun","The weapon type",Ogre::PT_STRING),&ms_firegunCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Cross","The weapon type",Ogre::PT_STRING),&ms_crossCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"Fan","The weapon type",Ogre::PT_STRING),&ms_fanCmd);
			//--------------------

		}
	}

	AASWeaponAnimExtSequenceNode::~AASWeaponAnimExtSequenceNode()
	{

	}

	void AASWeaponAnimExtSequenceNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
		//-------------------------------------
	}

	void AASWeaponAnimExtSequenceNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,
		Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		AASWeaponAnimSequenceNode::readFromBinary(serializer,stream,system);
	
		//---------------------------------------
		m_Spear				= serializer->readString(stream).c_str();

		m_Token				= serializer->readString(stream).c_str();

		m_Crossbow				= serializer->readString(stream).c_str();

		m_Firegun			= serializer->readString(stream).c_str();

		m_Cross				= serializer->readString(stream).c_str();

		m_Fan				= serializer->readString(stream).c_str();
		//---------------------------------------

	}

	size_t AASWeaponAnimExtSequenceNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = AASWeaponAnimSequenceNode::calcSize(serializer);
	
		//-----------------------
		tmpSize += m_Spear.length() + 1;

		tmpSize += m_Token.length() + 1;

		tmpSize += m_Crossbow.length() + 1;

		tmpSize += m_Firegun.length() + 1;

		tmpSize += m_Cross.length() + 1;

		tmpSize += m_Fan.length() + 1;
		//-----------------------
		return tmpSize;
	}

	Ogre::String AASWeaponAnimExtSequenceNode::_getAnimationByWeaponTypeName( const String& weaponType )
	{
	
		String tmpAnimationName = AASWeaponAnimSequenceNode::_getAnimationByWeaponTypeName(weaponType);
		if (tmpAnimationName != "")
			return tmpAnimationName;

	
		//-------------------------
		else if("Spear" == weaponType)
			tmpAnimationName = m_Spear.c_str();
		else if("Token" == weaponType)
			tmpAnimationName = m_Token.c_str();
		else if("Crossbow" == weaponType)
			tmpAnimationName = m_Crossbow.c_str();
		else if("Firegun" == weaponType)
			tmpAnimationName = m_Firegun.c_str();
		else if("Cross" == weaponType)
			tmpAnimationName = m_Cross.c_str();
		else if("Fan" == weaponType)
			tmpAnimationName = m_Fan.c_str();
		//-------------------------
		else
			tmpAnimationName = m_animationName.c_str();

		return tmpAnimationName;
	}

	void AASWeaponAnimExtSequenceNode::copyParameters( AASNode* dest )
	{
		AASWeaponAnimSequenceNode::copyParameters(dest);

		AASWeaponAnimExtSequenceNode* destNode = (AASWeaponAnimExtSequenceNode*)dest;
		assert(destNode && "AASWeaponAnimExtSequenceNode::copyParameters");

		//--------------------------------
		destNode->m_Spear =		  m_Spear;
		destNode->m_Token =		  m_Token;
		destNode->m_Crossbow =	  m_Crossbow;
		destNode->m_Firegun	= 	  m_Firegun;
		destNode->m_Cross =		  m_Cross;
		destNode->m_Fan =		  m_Fan;
		//--------------------------------
	}
	
	//--------------------------------------
	String AASWeaponAnimExtSequenceNode::CmdSpear::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimExtSequenceNode*>(target)->getSpear().c_str();
	}

	void AASWeaponAnimExtSequenceNode::CmdSpear::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimExtSequenceNode*>(target)->setSpear(val.c_str());
	}

	String AASWeaponAnimExtSequenceNode::CmdToken::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimExtSequenceNode*>(target)->getToken().c_str();
	}

	void AASWeaponAnimExtSequenceNode::CmdToken::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimExtSequenceNode*>(target)->setToken(val.c_str());
	}

	String AASWeaponAnimExtSequenceNode::CmdCrossbow::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimExtSequenceNode*>(target)->getCrossbow().c_str();
	}

	void AASWeaponAnimExtSequenceNode::CmdCrossbow::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimExtSequenceNode*>(target)->setCrossbow(val.c_str());
	}

	String AASWeaponAnimExtSequenceNode::CmdFiregun::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimExtSequenceNode*>(target)->getFiregun().c_str();
	}

	void AASWeaponAnimExtSequenceNode::CmdFiregun::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimExtSequenceNode*>(target)->setFiregun(val.c_str());
	}

	String AASWeaponAnimExtSequenceNode::CmdCross::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimExtSequenceNode*>(target)->getCross().c_str();
	}

	void AASWeaponAnimExtSequenceNode::CmdCross::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimExtSequenceNode*>(target)->setCross(val.c_str());
	}

	String AASWeaponAnimExtSequenceNode::CmdFan::doGet( const void* target ) const
	{
		return	static_cast<const	AASWeaponAnimExtSequenceNode*>(target)->getFan().c_str();
	}

	void AASWeaponAnimExtSequenceNode::CmdFan::doSet( void* target, const String& val )
	{
		static_cast<AASWeaponAnimExtSequenceNode*>(target)->setFan(val.c_str());
	}

	//--------------------------------------
}