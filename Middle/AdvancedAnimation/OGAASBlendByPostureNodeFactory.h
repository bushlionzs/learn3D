#ifndef OGAASBlendByPostureNodeFactory_h__
#define OGAASBlendByPostureNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByPostureNode.h"

namespace Orphigine
{
	class AASBlendByPostureNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "BlendByPosture";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByPostureNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByPostureNodeFactory_h__