#ifndef OGBulletFlowSystem_h__
#define OGBulletFlowSystem_h__


#include "OgreStringInterface.h"
#include "OgreSceneNode.h"
#include "OgreController.h"


namespace Orphigine
{
	class BulletEventSystem;
	class BulletSystem;

	class _OrphigineExport BulletFlowSystem : public Ogre::StringInterface
	{
	public:
		BulletFlowSystem();
		virtual ~BulletFlowSystem();

		class CmdMaxTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdDefaultHitPoint : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdIterationInterval : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		BulletFlowSystem& operator = (const BulletFlowSystem& rhs);

		void update(Real time);

		BulletEventSystem*	addBulletEventSystem(const String& name);
		int					getNumBulletEventSystem() const;
		BulletEventSystem*	getBulletEventSystem(const String& name);
		const std::map<String,BulletEventSystem*>& getBulletEventSystemsMap() const;
		void				removeBulletEventSystem(const String& eventSystemName);
		void				removeBulletEventSystem(BulletEventSystem* eventSystem);
		void				removeAllBulletEventSystem();

		BulletSystem*		addBulletSystem(const String& name, unsigned int clusterIndex);
		int					getNumBulletSystem() const;
		BulletSystem*		getBulletSystem(int index) const;
		void				removeBulletSystem(unsigned int index);
		void				removeBulletSystem(BulletSystem* bulletSystem);
		void				removeAllBulletSystem();

		void					createSceneNodeFromBase();
		void					removeSceneNodeFromParent();

		const Ogre::Vector3&	getPosition() const;
		void					setPosition(const Ogre::Vector3& position);

		Ogre::Vector3			getTargetPosition(unsigned int index) const;
		void					addTargetPosition(const Ogre::Vector3& position);
		void					flushTargetPosition(unsigned int index,const Ogre::Vector3& position);
		int						getNumTargetPosition() const;

		Real				getMaxTime() const;
		void					setMaxTime(Real val);

		Real				getAge() const;
		void					setAge(Real val);

		int						getBirthBulletTimesPerCluster() const;
		void					setBirthBulletTimesPerCluster(int val);

		String			getDefaultHitPoint() const;
		void					setDefaultHitPoint(const String& val);

		Real				getIterationInterval() const;
		void					setIterationInterval(Real val);

		bool					getIterationIntervalSet() const;
		void					setIterationIntervalSet(bool val);

		void                    setPriority(int priority) { m_Priority = priority; }
		int                     getPriority() { return m_Priority;}
		//end

		static CmdMaxTime			ms_maxTimeCmd;
		static CmdDefaultHitPoint	ms_defaultHitPointCmd;
		static CmdIterationInterval	ms_iterationIntervalCmd;
	protected:
		void					integrateBulletSystemTransform(Real time);

	protected:
		Ogre::SceneNode*					m_sceneNode;
		std::map<String,BulletEventSystem*> m_bulletEventSystemMap;
		std::vector<BulletSystem*>			m_bulletSystems;
		bool								m_isCreated;
		bool								m_isActiveEventSystemListInitialised;
		Ogre::Controller<Real>*				m_timeController;
		Real								m_maxTime;
		Real								m_age;
		std::vector<Ogre::Vector3>			m_targetPositionVec;
		int									m_birthBulletTimesPerCluster;
		String								m_defaultHitPoint;
		Real								m_iterationInterval;
	
		Real								m_updateRemainTime;

		int									m_Priority;
		//end
	public:
		void*								m_userData;
														
	};
}
#endif // OGBulletFlowSystem_h__