#ifndef OGAASMoodAnimSequenceNodeFactory_h__
#define OGAASMoodAnimSequenceNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASMoodAnimSequenceNode.h"

namespace Orphigine
{
	class AASMoodAnimSequenceNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const 
		{
			return "MoodAnimSequence";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASMoodAnimSequenceNode(system,handle);

			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASMoodAnimSequenceNodeFactory_h__