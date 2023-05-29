#ifndef OGAASBlendByWalkNode_h__
#define OGAASBlendByWalkNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByWalkNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByWalkNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByWalkNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*						getWalkPort() const;
		void							setWalkPort(AASPort* val);

		AASPort*						getRunPort() const;
		void							setRunPort(AASPort* val);

	protected:
		AASPort*						m_walkPort;
		AASPort*						m_runPort;

	private:
	};
}
#endif // OGAASBlendByWalkNode_h__
