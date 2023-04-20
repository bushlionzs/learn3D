#ifndef OGAASBlendByDanceNodeFactory_h__
#define OGAASBlendByDanceNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByDanceNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByDanceNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByDance";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByDanceNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByDanceNodeFactory_h__