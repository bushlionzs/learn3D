#ifndef OGAASBlendByDamageNode_h__
#define OGAASBlendByDamageNode_h__

#include "OGAASCrossFadeByTimeWithMaskNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByDamageNode : public AASCrossFadeByTimeWithMaskNode
	{
	public:
		AASBlendByDamageNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByDamageNode();

		virtual void	tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*		getDefaultPort() const;
		void			setDefaultPort(AASPort* val);

		AASPort*		getDamagePort() const;
		void			setDamagePort(AASPort* val);

		static CmdBranchBoneName		ms_branchBoneNameCmd;

	protected:
		AASPort*			m_defaultPort;
		AASPort*			m_damagePort;

	private:
	};
}
#endif // OGAASBlendByDamageNode_h__
