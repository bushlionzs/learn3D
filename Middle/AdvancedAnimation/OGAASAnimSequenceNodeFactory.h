#ifndef OGAASAnimSequenceNodeFactory_h__
#define OGAASAnimSequenceNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASAnimSequenceNode.h"

namespace Orphigine
{
	class AASAnimSequenceNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "AnimSequence";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASAnimSequenceNode(system,handle);

			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASAnimSequenceNodeFactory_h__