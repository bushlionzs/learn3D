#ifndef OGAASBlendByAttackNodeFactory_h__
#define OGAASBlendByAttackNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByAttackNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByAttackNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByAttack";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByAttackNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByAttackNodeFactory_h__