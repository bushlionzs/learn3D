#ifndef OGAdvancedAnimationSystemInstance_h__
#define OGAdvancedAnimationSystemInstance_h__

#include "OGAdvancedAnimationSystem.h"

namespace Orphigine
{
	/*
	 *	�߼�����ϵͳʵ��������AdvancedAnimationSystem�Ŀ������û�ֻ��ʹ�ô˿������Ҷ�����κ��޸Ĳ�Ӱ��
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