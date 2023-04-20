#ifndef OGAASBlendByRidingNode_h__
#define OGAASBlendByRidingNode_h__


#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByRidingNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByRidingNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByRidingNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*						getRidingPort() const;
		void							setRidingPort(AASPort* val);

		AASPort*						getNonridingPort() const;
		void							setNonridingPort(AASPort* val);

	protected:
		AASPort*					m_ridingPort;
		AASPort*					m_nonridingPort;

	private:
	};
}
#endif // OGAASBlendByRidingNode_h__
