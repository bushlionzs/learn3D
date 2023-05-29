#ifndef OGAASBlendByAttackNode_h__
#define OGAASBlendByAttackNode_h__

#include "OGAASCrossFadeByTimeWithMaskNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByAttackNode : public AASCrossFadeByTimeWithMaskNode
	{
	public:
		AASBlendByAttackNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByAttackNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*						getAttackPort() const;
		void							setAttackPort(AASPort* val);

		AASPort*						getNonattackPort() const;
		void							setNonattackPort(AASPort* val);

		static CmdBranchBoneName		ms_branchBoneNameCmd;
	
	protected:
		AASPort*						m_nonattackPort;
		AASPort*						m_attackPort;
	private:
	};
}
#endif // OGAASBlendByAttackNode_h__
