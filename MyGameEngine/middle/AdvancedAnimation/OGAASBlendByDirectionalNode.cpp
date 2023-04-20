#include "OgreHeader.h"
#include "OGAASBlendByDirectionalNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"

#include "OgreMath.h"

namespace Orphigine
{
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);


	AASBlendByDirectionalNode::AASBlendByDirectionalNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByValNode("BlendByDirectional",system,handle)
	{
		m_forward		=		addPort("Forward");
		m_backward		=		addPort("Backward");
		m_left			=		addPort("Left");
		m_right			=		addPort("Right");
	}

	AASBlendByDirectionalNode::~AASBlendByDirectionalNode()
	{

	}

	Ogre::Real AASBlendByDirectionalNode::_refreshTwoNodesCrossFadePercentage()
	{
		Real tmpDirectionalDegree = m_owner->getDirectionalDegree();

		Real tmpReciprocal = 1.0f / 0.25f;

		//			  Forward
		//			   -  |  -
		//			 /	  |    \	
		//	  Left -|---- | ----|- Right
		//		     \	  |    /
		//			   -  |  -
		//		      Backward
		//-180.0f---0.0f----180.0f
		//-180°~ -90°进行Backward 和 Left之间的融合,相应的Degree为0.0f ~ 0.25f
		//-90°~ 0°   进行Left和 Forward之间的融合,相应的Degree为0.25f ~ 0.5f
		//	0°~ 90°  进行Forward和 Right之间的融合,相应的Degree为0.5f ~ 0.75f
		//	90°~ 180°进行Right和 Backward之间的融合,相应的Degree为0.75f ~ 1.0f

		if( 0.25f > tmpDirectionalDegree)
		{
			Real tmpPercentage = tmpDirectionalDegree * tmpReciprocal;

			m_activePort1 = m_backward;
			m_activePort2 = m_left;

			return tmpPercentage;
		}
		else if (Ogre::Math::RealEqual(tmpDirectionalDegree,0.25f,0.001f) ||
			(0.25f < tmpDirectionalDegree && 0.5f > tmpDirectionalDegree) )
		{
			Real tmpPercentage = (tmpDirectionalDegree - 0.25f) * tmpReciprocal;

			m_activePort1 = m_left;
			m_activePort2 = m_forward;

			return tmpPercentage;
		}
		else if (Ogre::Math::RealEqual(tmpDirectionalDegree,0.5f,0.001f) ||
			(0.5f < tmpDirectionalDegree && 0.75f > tmpDirectionalDegree) )
		{
			Real tmpPercentage = (tmpDirectionalDegree - 0.5f) * tmpReciprocal;

			m_activePort1 = m_forward;
			m_activePort2 = m_right;

			return tmpPercentage;
		}
		else if(Ogre::Math::RealEqual(tmpDirectionalDegree,0.75f,0.001f) ||
			0.75f < tmpDirectionalDegree )
		{
			Real tmpPercentage = (tmpDirectionalDegree - 0.75) * tmpReciprocal;

			m_activePort1 = m_right;
			m_activePort2 = m_backward;

			return tmpPercentage;
		}

		return 0.0f;
	}

}