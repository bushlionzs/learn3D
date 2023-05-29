#ifndef OGAASMoodAnimSequenceNode_h__
#define OGAASMoodAnimSequenceNode_h__

#include "OGAASAnimSequenceNode.h"

#include "OgreAnimationState.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;

	class AASMoodAnimSequenceNode : public AASAnimSequenceNode
	{
	public:
		AASMoodAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASMoodAnimSequenceNode();

		virtual	void	_refreshAnimation();

	protected:

	private:
	};
}
#endif // OGAASMoodAnimSequenceNode_h__
