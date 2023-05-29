#ifndef OGAASAnimTreeOutputNodeFactory_h__
#define OGAASAnimTreeOutputNodeFactory_h__

#include "OGAASAnimTreeOutputNode.h"
#include "OGAASNodeFactory.h"

namespace Orphigine
{
	class AASAnimTreeOutputNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "AnimTree";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASAnimTreeOutputNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASAnimTreeOutputNodeFactory_h__