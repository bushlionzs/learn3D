#ifndef OGAASAttackAnimSequenceNode_h__
#define OGAASAttackAnimSequenceNode_h__

#include "OGAASAnimSequenceNode.h"

#include "OgreAnimationState.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;

	class AASAttackAnimSequenceNode : public AASAnimSequenceNode
	{
	public:
		AASAttackAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASAttackAnimSequenceNode();

		virtual	void	_refreshAnimation();

	protected:

	private:
	};
}
#endif // OGAASAttackAnimSequenceNode_h__
