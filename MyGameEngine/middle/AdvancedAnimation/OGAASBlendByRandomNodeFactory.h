#ifndef OGAASBlendByRandomNodeFactory_h__
#define OGAASBlendByRandomNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByRandomNode.h"

namespace Orphigine
{
	class AASBlendByRandomNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "BlendByRandom";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByRandomNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByRandomNodeFactory_h__