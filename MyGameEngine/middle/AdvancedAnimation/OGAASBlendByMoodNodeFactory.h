#ifndef OGAASBlendByMoodNodeFactory_h__
#define OGAASBlendByMoodNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByMoodNode.h"
#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	class AASBlendByMoodNodeFactory : public AASNodeFactory
	{
	public:

		virtual String getName() const 
		{
			return "BlendByMood";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByMoodNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByMoodNodeFactory_h__
