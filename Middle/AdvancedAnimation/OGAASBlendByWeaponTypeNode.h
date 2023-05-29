#ifndef OGAASBlendByWeaponTypeNode_h__
#define OGAASBlendByWeaponTypeNode_h__

#include "OGAASCrossFadeByValNode.h"
#include "OGAASMask.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByWeaponTypeNode : public AASCrossFadeByValNode , public AASMask
	{
	public:
		AASBlendByWeaponTypeNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByWeaponTypeNode();

		class CmdBranchBoneName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		AASPort*				getWeaponPort() const;
		void					setWeaponPort(AASPort* val);

		AASPort*				getDefaultPort() const;
		void					setDefaultPort(AASPort* val);

		virtual	void			tickAnimation(const float elapsedTime,
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		static	CmdBranchBoneName		ms_branchBoneNameCmd;

	protected:
		virtual	Real			_refreshTwoNodesCrossFadePercentage();

	protected:
		AASPort*			m_defaultPort;
		AASPort*			m_weaponPort;

	private:
	};
}
#endif // OGAASBlendByWeaponTypeNode_h__
