#ifndef OGAASCrossFadeByTimeListNodeFactory_h__
#define OGAASCrossFadeByTimeListNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASCrossFadeByTimeListNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASCrossFadeByTimeListNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "CrossFadeByTimeList";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASCrossFadeByTimeListNode("CrossFadeByTimeList",system,handle);
			
			{
				tmpNode->addPort("Child1");				
				tmpNode->addPort("Child2");
				tmpNode->addPort("Child3");
			}
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASCrossFadeByTimeListNodeFactory_h__