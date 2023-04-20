#ifndef FariyAASBlendByIdleNode_h__
#define FariyAASBlendByIdleNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByIdleNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByIdleNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByIdleNode();

		virtual	void				tickAnimation(const float elapsedTime,
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*						getIdlePort() const;
		void							setIdlePort(AASPort* val);

		AASPort*						getMovingPort() const;
		void							setMovingPort(AASPort* val);

	protected:
		AASPort*					m_idlePort;
		AASPort*					m_movingPort;

	private:
	};
}
#endif // FariyAASBlendByIdleNode_h__