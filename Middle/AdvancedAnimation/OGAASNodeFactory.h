#ifndef OGAASNodeFactory_h__
#define OGAASNodeFactory_h__

#include "OGAdvancedAnimationSystem.h"

#include <vector>

namespace Orphigine
{

	class AdvancedAnimationSystem;
	class AASNode;

	class AASNodeFactory
	{
	public:
		AASNodeFactory() {}
		virtual ~AASNodeFactory(){}
		
		virtual	String			getName() const = 0;

		virtual AASNode*		createNode(AdvancedAnimationSystem* system,unsigned short handle) = 0;

		virtual	void			destroyNode(AASNode* node);
	protected:
		AASNodeVector			m_nodes;
	private:
	};
}
#endif // OGAASNodeFactory_h__