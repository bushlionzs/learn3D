#ifndef OGAASBlendByEquitationNodeFactory_h__
#define OGAASBlendByEquitationNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByEquitationNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByEquitationNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByEquitation";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByEquitationNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}

#endif // OGAASBlendByEquitationNodeFactory_h__
