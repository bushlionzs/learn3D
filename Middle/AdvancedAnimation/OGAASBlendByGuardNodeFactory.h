#ifndef OGAASBlendByGuardNodeFactory_h__
#define OGAASBlendByGuardNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByGuardNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByGuardNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByGuard";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByGuardNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByGuardNodeFactory_h__