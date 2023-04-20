#include "OgreHeader.h"
#include "OGAASBlendByWeaponTypeNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByWeaponTypeNode::CmdBranchBoneName			AASBlendByWeaponTypeNode::ms_branchBoneNameCmd;

	AASBlendByWeaponTypeNode::AASBlendByWeaponTypeNode( AdvancedAnimationSystem* system ,unsigned short handle)
		: AASCrossFadeByValNode("BlendByWeaponType",system,handle),
		AASMask(system)
	{
		m_defaultPort = addPort("Default");
		m_weaponPort = addPort("Weapon");

		if (initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByWeaponTypeNode::~AASBlendByWeaponTypeNode()
	{

	}

	AASPort* AASBlendByWeaponTypeNode::getWeaponPort() const
	{
		return m_weaponPort;
	}

	void AASBlendByWeaponTypeNode::setWeaponPort( AASPort* val )
	{
		m_weaponPort = val;
	}

	AASPort* AASBlendByWeaponTypeNode::getDefaultPort() const
	{
		return m_defaultPort;
	}

	void AASBlendByWeaponTypeNode::setDefaultPort( AASPort* val )
	{
		m_defaultPort = val;
	}

	Ogre::Real AASBlendByWeaponTypeNode::_refreshTwoNodesCrossFadePercentage()
	{
		return 1.0f;
	}

	void AASBlendByWeaponTypeNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection)
	{
		
	}

	Ogre::String AASBlendByWeaponTypeNode::CmdBranchBoneName::doGet( const void* target ) const
	{
		return static_cast<const AASBlendByWeaponTypeNode*>(target)->getBonesNameVec();
	}

	void AASBlendByWeaponTypeNode::CmdBranchBoneName::doSet( void* target, const String& val )
	{
		static_cast<AASBlendByWeaponTypeNode*>(target)->setBonesNameVec(val);
	}
}