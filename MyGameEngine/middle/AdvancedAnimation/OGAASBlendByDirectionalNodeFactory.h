#ifndef OGAASBlendByDirectionalNodeFactory_h__
#define OGAASBlendByDirectionalNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByDirectionalNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByDirectionalNodeFactory : public AASNodeFactory
	{
	public:

		virtual	String		getName() const
		{
			return "BlendByDirectional";
		}
		virtual AASNode*	createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByDirectionalNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByDirectionalNodeFactory_h__