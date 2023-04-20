#ifndef OGAASCrossFadeByValNode_h__
#define OGAASCrossFadeByValNode_h__

#include "OGAASNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASCrossFadeByValNode : public AASNode
	{
	public:
		virtual ~AASCrossFadeByValNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

	protected:
		AASCrossFadeByValNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);
		
		virtual	Real				_refreshTwoNodesCrossFadePercentage() = 0;
	protected:
		AASPort*	m_activePort1;
		AASPort*	m_activePort2;
	private:
	};
		
}
#endif // OGAASCrossFadeByValNode_h__
