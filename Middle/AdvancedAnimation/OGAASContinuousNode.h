#ifndef OGAASContinuousNode_h__
#define OGAASContinuousNode_h__

#include "OGAASNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASContinuousNode : public AASNode
	{
	public:
		AASContinuousNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASContinuousNode();

		virtual	void		tickAnimation(const float elapsedTime,
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection,
			TraverseBranchMaskCollection& traverseBranchMaskCollection);

		AASPort*			getPort1() const;
		void				setPort1(AASPort* val);
		AASPort*			getPort2() const;
		void				setPort2(AASPort* val);

	protected:
		virtual	Real		_refreshContinuousBlendValue() = 0;

		//virtual	Real		_getBlendTime() = 0;
	protected:
		AASPort*			m_port1;
		AASPort*			m_port2;

	private:
	};
}
#endif // OGAASContinuousNode_h__
