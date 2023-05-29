#ifndef OGAASWeaponAnimSequenceNodeFactory_h__
#define OGAASWeaponAnimSequenceNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASWeaponAnimSequenceNode.h"

namespace Orphigine
{
	class AASWeaponAnimSequenceNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "WeaponAnimSequence";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASWeaponAnimSequenceNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASWeaponAnimSequenceNodeFactory_h__