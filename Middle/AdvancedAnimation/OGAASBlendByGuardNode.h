#ifndef OGAASBlendByGuardNode_h__
#define OGAASBlendByGuardNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByGuardNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByGuardNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByGuardNode();

		virtual	void				tickAnimation(const float elapsedTime,
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*		getNonguardedPort() const;
		void			setNonguardedPort(AASPort* val);

		AASPort*		getGuardPort() const;
		void			setGuardPort(AASPort* val);


	protected:
		AASPort*					m_nonguardedPort;
		AASPort*					m_guardPort;

	private:
	};
}
#endif // OGAASBlendByGuardNode_h__
