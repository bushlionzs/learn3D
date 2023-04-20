#ifndef OGAdvancedAnimationSystemInstance_h__
#define OGAdvancedAnimationSystemInstance_h__

#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	/*
	 *	高级动画系统实例，其是AdvancedAnimationSystem的拷贝，用户只能使用此拷贝，且对其的任何修改不影响
	 *	AdvancedAnimationSystem
	 */
	class _OrphigineExport AdvancedAnimationSystemInstance : public AdvancedAnimationSystem
	{
	public:
		AdvancedAnimationSystemInstance(const AdvancedAnimationSystemPtr& masterCopy);
		virtual ~AdvancedAnimationSystemInstance();

		void							cloneNode(AASNode* source);

		void							cloneConnection(AASNode* source);

		void							cloneAnimation();

		void							init();
	
		void							initAnimTree();
	protected:
		virtual	void					loadImpl();

		virtual void					unloadImpl(void);
	protected:
		AdvancedAnimationSystemPtr		m_advancedAnimationSystem;
	private:
	};
}
#endif // OGAdvancedAnimationSystemInstance_h__