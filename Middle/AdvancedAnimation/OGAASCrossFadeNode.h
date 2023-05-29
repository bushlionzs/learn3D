#ifndef OGAASCrossFadeNode_h__
#define OGAASCrossFadeNode_h__

#include "OGAASNode.h"
#include "OGAASFIFO.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASCrossFadeNode : public AASNode
	{
	public:
		virtual ~AASCrossFadeNode();

		virtual void	tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		virtual void accumulateNodeTotalWeights(unsigned int index);

		virtual void	_getNodesInTree(AASNodeVector& nodes);

		virtual bool	initParameter(const String& typeName);

		virtual void	buildTickVec(AASNodeVector& tickVec);

	protected:
		AASCrossFadeNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);

		
		unsigned int	_generateAveragePortIndexByDegreeAuto(Real degree);

		virtual void	initAnim(AASNode* parentNode);

		Real			getTotalChildrenWeight(); 

	};
}
#endif // OGAASCrossFadeNode_h__
