#ifndef OGAASBlendByLifeNodeFactory_h__
#define OGAASBlendByLifeNodeFactory_h__

#include "OGAASBlendByLifeNode.h"
#include "OGAASNodeFactory.h"

namespace Orphigine
{
	class AASBlendByLifeNodeFactory : public AASNodeFactory
	{
	public:
		virtual String	getName() const
		{
			return "BlendByLife";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByLifeNode(system,handle);
			m_nodes.push_back( tmpNode);

			return tmpNode;
		}

	protected:
	private:
	};
}
#endif // OGAASBlendByLifeNodeFactory_h__