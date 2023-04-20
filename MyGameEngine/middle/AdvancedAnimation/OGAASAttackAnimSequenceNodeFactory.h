#ifndef OGAASAttackAnimSequenceNodeFactory_h__
#define OGAASAttackAnimSequenceNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASAttackAnimSequenceNode.h"

namespace Orphigine
{
	class AASAttackAnimSequenceNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const 
		{
			return "AttackAnimSequence";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASAttackAnimSequenceNode(system,handle);

			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASAttackAnimSequenceNodeFactory_h__