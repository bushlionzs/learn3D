#ifndef OGAASBlendByDirectionalNode_h__
#define OGAASBlendByDirectionalNode_h__

#include "OGAASCrossFadeByValNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByDirectionalNode : public AASCrossFadeByValNode
	{
	public:
		AASBlendByDirectionalNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByDirectionalNode();

		virtual	Real	_refreshTwoNodesCrossFadePercentage();
	protected:
		AASPort*		m_forward;
		AASPort*		m_backward;
		AASPort*		m_left;
		AASPort*		m_right;
	private:
	};
}
#endif // OGAASBlendByDirectionalNode_h__
