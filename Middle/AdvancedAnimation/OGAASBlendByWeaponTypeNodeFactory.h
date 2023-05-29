#ifndef OGAASBlendByWeaponTypeNodeFactory_h__
#define OGAASBlendByWeaponTypeNodeFactory_h__

#include "OGAASNodeFactory.h"
#include "OGAASBlendByWeaponTypeNode.h"

namespace Orphigine
{
	class AASBlendByWeaponTypeNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "BlendByWeaponType";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASBlendByWeaponTypeNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};
}
#endif // OGAASBlendByWeaponTypeNodeFactory_h__