#ifndef OGBulletEventSystem_h__
#define OGBulletEventSystem_h__

#include "OgreStringInterface.h"



namespace Orphigine
{
	class BulletOperator;
	class BulletSystem;
	class BulletFlowSystem;

	struct BulletSystemCollection 
	{
		std::vector<BulletSystem*> m_bulletSystemCollectition;
	};

	class _OrphigineExport BulletEventSystem : public Ogre::StringInterface
	{
	public:
		BulletEventSystem(const String& templateName,BulletFlowSystem* parent);
		virtual ~BulletEventSystem();

		BulletEventSystem& operator = (const BulletEventSystem& rhs);

		void				addActiveBulletSystem(BulletSystem* bulletSystem);
		
		void				addNewTransferredBulletSystem(BulletSystem* bulletSystem);
		//void				clearNewTransferredBulletSystemList();

		void				removeActiveBulletSystem(BulletSystem* bulletSystem);

		enum BulletOperatorAddMode
		{
			BOAM_APPEND,
			BOAM_INSERT
		};
		BulletOperator*		addBulletOperator(const String& typeName,
			BulletOperatorAddMode addMode = BOAM_APPEND,
			unsigned int insertIndex = 0);
		void				removeBulletOperator(unsigned int index);
		void				removeAllBulletOperators();
		int					getNumBulletOperator() const;
		BulletOperator*		getBulletOperator(int index) const;

		void				update(Real time);

		void				addTransition(const String& eventName,BulletSystem* bulletSystem);

		BulletFlowSystem*	getParent();

		const String& getTemplateName() const ;

		std::vector<BulletSystem*>*		getActiveBulletSystem();

		std::vector<BulletSystem*>*		getNewTransferredBulletSystem();

	protected:
		String							m_templateName;

		BulletFlowSystem*				m_parent;
		std::vector<BulletOperator*>	m_operators;
		std::vector<BulletSystem*>		m_activeBulletSystem;
		std::map<String,BulletSystemCollection*> m_transitionCache;
		std::vector<BulletSystem*>		m_newTransferredBulletSystem;
	private:
	};
}
#endif // OGBulletEventSystem_h__