#ifndef OGAASBlendByIdleNodeFactory_h__
#define OGAASBlendByIdleNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByIdleNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByIdleNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByIdle";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByIdleNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByIdleNodeFactory_h__