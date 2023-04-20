#ifndef OGAASCrossFadeByTimeSlotNodeFactory_h__
#define OGAASCrossFadeByTimeSlotNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASCrossFadeByTimeSlotNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASCrossFadeByTimeSlotNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "CrossFadeByTimeSlot";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASCrossFadeByTimeSlotNode("CrossFadeByTimeSlot",system,handle);
			
			{
				tmpNode->addPort("Child1");				
				tmpNode->addPort("Child2");
				tmpNode->addPort("Child3");
			}
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	};
}
#endif // OGAASCrossFadeByTimeSlotNodeFactory_h__