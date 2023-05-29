#ifndef OGAASBlendByDamageNodeFactory_h__
#define OGAASBlendByDamageNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByDamageNode.h"

namespace Orphigine
{
	class AASBlendByDamageNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "BlendByDamage";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByDamageNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByDamageNodeFactory_h__