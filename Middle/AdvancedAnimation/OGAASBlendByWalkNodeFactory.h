#ifndef OGAASBlendByWalkNodeFactory_h__
#define OGAASBlendByWalkNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByWalkNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByWalkNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByWalk";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByWalkNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByWalkNodeFactory_h__