#ifndef OGPhyWorld_h__
#define OGPhyWorld_h__

#include "OgreStringInterface.h"
#include "OgreVector3.h"




class btSoftRigidDynamicsWorld;
class btCollisionDispatcher;
class btCollisionConfiguration;
class btBroadphaseInterface;
class btConstraintSolver;
class btCollisionObject;

namespace Orphigine
{
	class PhyActor;
	class PhyDefaultTimeController;
	class PhySoftBody;
	class PhyConstraint;

	class _OrphigineExport PhyWorld : public Ogre::StringInterface
	{
	public:
		PhyWorld(Real	gravity);
		virtual ~PhyWorld();

		class CmdGravity : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		/*
		 *	刚体管理
		 */
		void						addActor(PhyActor* actor);

		PhyActor*					getActor(unsigned int index);

		unsigned int				getNumActors() const;

		void						removeAllActors();

		void						removeActor(PhyActor* actor);

		/*
		 *	柔体管理
		 */
		void						addSoftBody(PhySoftBody* softBody);

		PhySoftBody*				getSoftBody(unsigned int index);

		unsigned int				getNumSoftBodies() const;

		void						removeAllSoftBodies();

		void						removeSoftBody(PhySoftBody* softBody);


		/*
		 *	约束管理
		 */
		void						addConstraint(PhyConstraint* constraint);

		PhyConstraint*				getConstraint(unsigned int index);

		unsigned int				getNumConstraints() const;

		void						removeAllConstraints();

		void						removeConstraints(PhyConstraint* constraint);

		bool						launchRay( const Ogre::Vector3& rayOrgin, const Ogre::Vector3& rayDir,btCollisionObject ** ppObject,Ogre::Vector3 * outPosition = NULL);

		bool						launchRay( const Ogre::Vector3& rayOrgin, const Ogre::Vector3& rayDir,Ogre::Vector3& outPosition );

		bool						sphereGroundTest(const Ogre::Vector3& pos, Real radius,const Ogre::AxisAlignedBox & aabb,bool & bAABBIntersect,btCollisionObject ** ppObject,std::vector<btCollisionObject *> & aryAllObject,Ogre::Vector3 * outPosition = 0);

		bool						rayTestSingle(const Ogre::Vector3 & pos,const Ogre::Vector3 & rayDir,btCollisionObject * pObject,Ogre::Vector3 & outPosition);

		void						simulate(Real time);

		Real					getGravity() const;

		void						setGravity(Real val);

		btBroadphaseInterface*		getBroadphase() const;

		static		CmdGravity		ms_gravityCmd;

	protected:
		void						_createBtWorld();

		void						_destroyBtWorld();

	protected:
		Real						m_gravity;
		std::vector<PhyActor*>		m_actors;
		std::vector<PhySoftBody*>	m_softBodies;
		std::vector<PhyConstraint*>	m_constraints;
		PhyDefaultTimeController*	m_timeController;

		btSoftRigidDynamicsWorld*	m_collisionWorld;
		btCollisionDispatcher*		m_collisionDispatcher;
		btCollisionConfiguration*	m_collisionConfiguration;
		btBroadphaseInterface*		m_broadphase;
		btConstraintSolver*			m_solver;
	private:
	};
}
#endif // OGPhyWorld_h__