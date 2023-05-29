#ifndef OGAASBlendByMoodNode_h__
#define OGAASBlendByMoodNode_h__

#include "OGAASCrossFadeByTimeWithMaskNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByMoodNode : public AASCrossFadeByTimeWithMaskNode
	{
	public:
		AASBlendByMoodNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByMoodNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*						getMoodPort() const;
		void							setMoodPort(AASPort* val);

		AASPort*						getNonmoodPort() const;
		void							setNonmoodPort(AASPort* val);

		static CmdBranchBoneName		ms_branchBoneNameCmd;
	
	protected:
		AASPort*						m_nonmoodPort;
		AASPort*						m_moodPort;
	private:
	};
}
#endif // OGAASBlendByMoodNode_h__
