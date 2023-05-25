#include "OgreHeader.h"
#include "OGPhyWorld.h"
#include "OGPhyActor.h"
#include "OGPhySoftBody.h"
#include "OGPhyConstraint.h"
#include "OGPhyTimeController.h"
#include "OGPhyUtil.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "OgreStringConverter.h"


namespace Orphigine
{
	PhyWorld::CmdGravity				PhyWorld::ms_gravityCmd;

	PhyWorld::PhyWorld(Real	gravity)
		: m_gravity(gravity)
		, m_collisionWorld(NULL)
		, m_collisionConfiguration(NULL)
		, m_collisionDispatcher(NULL)
		, m_broadphase(NULL)
	{
		m_actors.clear();
		m_softBodies.clear();
		m_constraints.clear();

		if (createParamDictionary("PhysicsWorldDict"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("Gravity","The gravity of world",Ogre::PT_REAL),
				&ms_gravityCmd);
		}

		_createBtWorld();

		m_timeController = new PhyDefaultTimeController(this);

	}

	PhyWorld::~PhyWorld()
	{
		removeAllActors();
		
		removeAllSoftBodies();

		removeAllConstraints();

		_destroyBtWorld();

		delete m_timeController;
		m_timeController = NULL;
	}

	void PhyWorld::simulate( Real time )
	{
		m_collisionWorld->stepSimulation(time);
	}

	void PhyWorld::_createBtWorld()
	{
		btDefaultCollisionConstructionInfo collisioinConstructionInfo;
		collisioinConstructionInfo.m_defaultMaxPersistentManifoldPoolSize = 16;
		collisioinConstructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 16;

		m_collisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration(collisioinConstructionInfo);// 柔体碰撞配置，为布料做准备 [10/13/2008 JiangWei]

		m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfiguration);

		btVector3 worldAabbMin = btVector3(-10000.0f,-10000.0f,-10000.0f);
		btVector3 worldAabbMax = btVector3(10000.0f,10000.0f,10000.0f);

		//m_broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax);
		m_broadphase = new btDbvtBroadphase();

		m_solver = new btSequentialImpulseConstraintSolver();

		m_collisionWorld = new btSoftRigidDynamicsWorld(m_collisionDispatcher,m_broadphase,m_solver,m_collisionConfiguration);

	}

	void PhyWorld::_destroyBtWorld()
	{
		delete m_collisionWorld;
		m_collisionWorld = NULL;

		delete m_solver;
		m_solver = NULL;

		delete m_broadphase;
		m_broadphase = NULL;

		delete m_collisionDispatcher;
		m_collisionDispatcher = NULL;

		delete m_collisionConfiguration;
		m_collisionConfiguration = NULL;
	}


	bool PhyWorld::sphereGroundTest(const Ogre::Vector3& pos, Real radius, const Ogre::AxisAlignedBox & aabb,bool & bAABBIntersect,btCollisionObject ** ppObject,std::vector<btCollisionObject *> & aryAllObject,Ogre::Vector3 * outPosition)
	{
		btSoftRigidDynamicsWorld * collisionWorld = this->m_collisionWorld;

		//btTransform	sphereFromTrans, sphereToTrans;
		//sphereFromTrans.setIdentity();
		//sphereFromTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));		

		//sphereToTrans.setIdentity();
		//sphereToTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));	


		btVector3 tmpRayFrom(pos.x, pos.y, pos.z);
		btVector3 tmpRayTo = ogreToBulletVector3(pos + Ogre::Vector3::NEGATIVE_UNIT_Y * radius * 4);
		btTransform	rayFromTrans,rayToTrans;
		rayFromTrans.setIdentity();
		rayFromTrans.setOrigin(tmpRayFrom);

		rayToTrans.setIdentity();
		rayToTrans.setOrigin(tmpRayTo);

		//btCollisionWorld::ClosestConvexResultCallback cb(btVector3(pos.x, pos.y, pos.z), btVector3(pos.x, pos.y, pos.z));	
		btCollisionWorld::ClosestRayResultCallback cb(tmpRayFrom,tmpRayTo);

		/// go over all objects, and if the ray intersects their aabb, do a ray-shape query using convexCaster (CCD)
		int num = collisionWorld->getNumCollisionObjects();
		btCollisionObjectArray&  collisionObjects = collisionWorld->getCollisionObjectArray();
		
		for (int i=0; i<num; i++)		
		{
			///terminate further ray tests, once the closestHitFraction reached zero
			if (cb.m_closestHitFraction == btScalar(0.f))
				break;

			btCollisionObject*	collisionObject= collisionObjects[i];
			//only perform raycast if filterMask matches
			if(cb.needsCollision(collisionObject->getBroadphaseHandle())) {				
				btVector3 collisionObjectAabbMin,collisionObjectAabbMax;
				PhyActor * actor = (PhyActor*) collisionObject->getUserPointer();
				if (actor)
				{					
					Real radius1 = actor->getBoundingRadius();
					const Ogre::Vector3& pos1 = actor->getCenterPos();

					Real squaredLen = (pos1 - pos).squaredLength();
					Real squaredRadius = (radius + radius1) * (radius + radius1);

					//只有距离小于半径之和时，才有可能发生碰撞
					if (squaredLen < squaredRadius) 
					{
						const Ogre::AxisAlignedBox & box = actor->getBoundingBox();
						collisionObjectAabbMin = ogreToBulletVector3(box.getMinimum());
						collisionObjectAabbMax = ogreToBulletVector3(box.getMaximum());



						btScalar hitLambda = cb.m_closestHitFraction;
						btVector3 hitNormal;
						if ( aabb.intersects(box) )
						//if (btRayAabb(tmpRayFrom, tmpRayTo, collisionObjectAabbMin,collisionObjectAabbMax,hitLambda, hitNormal))
						{
							collisionWorld->rayTestSingle(rayFromTrans,rayToTrans,
								collisionObject,
								collisionObject->getCollisionShape(),
								collisionObject->getWorldTransform(),
								cb);
							aryAllObject.push_back(collisionObject);
							bAABBIntersect = true;
						}			
						/*
						btSphereShape castShape(radius);
						collisionWorld->objectQuerySingle(&castShape, sphereFromTrans, sphereToTrans,
							collisionObject,
							collisionObject->getCollisionShape(),
							collisionObject->getWorldTransform(),
							cb,
							collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
							*/

					}
				}
			}
		}
		
		if (cb.hasHit())
		{
			*ppObject = (btCollisionObject*)cb.m_collisionObject;
			if ( outPosition != NULL )
			{
				outPosition->x = cb.m_hitPointWorld.x();
				outPosition->y = cb.m_hitPointWorld.y();
				outPosition->z = cb.m_hitPointWorld.z();
			}
			return true;
		}
		
		return false;
	}

	//--------------------------------------------------------
	//bullet原生的getAabb每次都需要重新计算，本方法使用缓存的方式来加快计算速度
	void rayTest(btSoftRigidDynamicsWorld*	collisionWorld, const btVector3& rayFromWorld, 
		const btVector3& rayToWorld, btCollisionWorld::RayResultCallback& resultCallback)
	{
		btTransform	rayFromTrans,rayToTrans;
		rayFromTrans.setIdentity();
		rayFromTrans.setOrigin(rayFromWorld);
		rayToTrans.setIdentity(); 

		rayToTrans.setOrigin(rayToWorld);

		/// go over all objects, and if the ray intersects their aabb, do a ray-shape query using convexCaster (CCD)
		int num = collisionWorld->getNumCollisionObjects();
		btCollisionObjectArray&  collisionObjects = collisionWorld->getCollisionObjectArray();

		for (int i=0; i<num; i++)
		{
			///terminate further ray tests, once the closestHitFraction reached zero
			if (resultCallback.m_closestHitFraction == btScalar(0.f))
				break;

			btCollisionObject*	collisionObject= collisionObjects[i];
			//only perform raycast if filterMask matches
			if(resultCallback.needsCollision(collisionObject->getBroadphaseHandle())) {				
				btVector3 collisionObjectAabbMin,collisionObjectAabbMax;
				
				//collisionObject->getCollisionShape()->getAabb(collisionObject->getWorldTransform(),collisionObjectAabbMin,collisionObjectAabbMax);
				PhyActor * actor = (PhyActor*) collisionObject->getUserPointer();
				if (actor)
				{
					const Ogre::AxisAlignedBox & box = actor->getBoundingBox();
					collisionObjectAabbMin = ogreToBulletVector3(box.getMinimum());
					collisionObjectAabbMax = ogreToBulletVector3(box.getMaximum());

					btScalar hitLambda = resultCallback.m_closestHitFraction;
					btVector3 hitNormal;
					if (btRayAabb(rayFromWorld,rayToWorld,collisionObjectAabbMin,collisionObjectAabbMax,hitLambda,hitNormal))
					{
						collisionWorld->rayTestSingle(rayFromTrans,rayToTrans,
							collisionObject,
							collisionObject->getCollisionShape(),
							collisionObject->getWorldTransform(),
							resultCallback);
					}
				}
			}

		}

	}
	//end
	//------------------------------------------------------------------------

	bool PhyWorld::launchRay(const Ogre::Vector3& rayOrgin, const Ogre::Vector3& rayDir,btCollisionObject ** ppObject,Ogre::Vector3 * outPosition /* = NULL */)
	{

		btVector3 tmpRayFrom = btVector3(rayOrgin.x,rayOrgin.y,rayOrgin.z);
		btVector3 tmpRayTo = tmpRayFrom + btVector3(rayDir.x,rayDir.y,rayDir.z);
		btCollisionWorld::ClosestRayResultCallback cb(tmpRayFrom,tmpRayTo);


		rayTest(m_collisionWorld, tmpRayFrom, tmpRayTo, cb);
		//end
		if ( cb.hasHit() )
		{
			if ( outPosition != NULL )
			{
				outPosition->x = cb.m_hitPointWorld.x();
				outPosition->y = cb.m_hitPointWorld.y();
				outPosition->z = cb.m_hitPointWorld.z();
			}
			*ppObject = (btCollisionObject*)cb.m_collisionObject;
			return true;
		}


		return false;
	}

	bool PhyWorld::launchRay( const Ogre::Vector3& rayOrgin, const Ogre::Vector3& rayDir,Ogre::Vector3& outPosition )
	{
		btVector3 tmpRayFrom = btVector3(rayOrgin.x,rayOrgin.y,rayOrgin.z);
		btVector3 tmpRayTo = tmpRayFrom + btVector3(rayDir.x,rayDir.y,rayDir.z);

		btCollisionWorld::ClosestRayResultCallback cb(tmpRayFrom, tmpRayTo);

		rayTest(m_collisionWorld, tmpRayFrom, tmpRayTo, cb);

		if (cb.hasHit ())
		{
			outPosition.x = cb.m_hitPointWorld.x();
			outPosition.y = cb.m_hitPointWorld.y();
			outPosition.z = cb.m_hitPointWorld.z();

			return true;
		} 

		outPosition = Ogre::Vector3::ZERO;

		return false;
	}

	bool PhyWorld::rayTestSingle(const Ogre::Vector3 & pos,const Ogre::Vector3 & rayDir,btCollisionObject * pObject,Ogre::Vector3 & outPosition)
	{
		btVector3 tmpRayFrom(pos.x, pos.y, pos.z);
		btVector3 tmpRayTo = ogreToBulletVector3(pos + rayDir);
		btTransform	rayFromTrans,rayToTrans;
		rayFromTrans.setIdentity();
		rayFromTrans.setOrigin(tmpRayFrom);

		rayToTrans.setIdentity();
		rayToTrans.setOrigin(tmpRayTo);

		btCollisionWorld::ClosestRayResultCallback cb(tmpRayFrom,tmpRayTo);

		m_collisionWorld->rayTestSingle(rayFromTrans,rayToTrans,
			pObject,
			pObject->getCollisionShape(),
			pObject->getWorldTransform(),
			cb);



		if ( cb.hasHit () )
		{
			outPosition.x = cb.m_hitPointWorld.x();
			outPosition.y = cb.m_hitPointWorld.y();
			outPosition.z = cb.m_hitPointWorld.z();

			return true;
		} 

		outPosition = Ogre::Vector3::ZERO;

		return false;
	}

	void PhyWorld::addActor( PhyActor* actor)
	{
		m_actors.push_back(actor);
		btCollisionObject* bco = actor->getBtActor();
		if(bco->getCollisionShape())
			m_collisionWorld->addCollisionObject(bco);
	}

	unsigned int PhyWorld::getNumActors() const
	{
		return (unsigned int)m_actors.size();
	}

	PhyActor* PhyWorld::getActor( unsigned int index )
	{
		assert(index < (unsigned int)m_actors.size() && "PhyWorld::getPhysicsActor");

		return m_actors[index];
	}

	void PhyWorld::removeActor( PhyActor* actor )
	{
		std::vector<PhyActor*>::iterator iter = std::find(m_actors.begin(),m_actors.end(),actor);
		
		if (m_actors.end() == iter)
			return;

		PhyActor* phyActor = *iter;
		btCollisionObject*	collObj = actor->getBtActor();

		m_collisionWorld->removeCollisionObject(collObj);

		delete actor;
		actor = NULL;
			
		m_actors.erase(iter);
	}

	void PhyWorld::removeAllActors()
	{
		std::vector<PhyActor*>::iterator iter;
		for (iter = m_actors.begin();iter != m_actors.end();iter ++)
		{
			PhyActor* physicsActor = (*iter);

			btCollisionObject*	collObj = physicsActor->getBtActor();

			m_collisionWorld->removeCollisionObject(collObj);

			delete *iter;
			*iter = NULL;
		}
		m_actors.clear();
	}

	Real PhyWorld::getGravity() const
	{
		return m_gravity;
	}

	void PhyWorld::setGravity(Real val )
	{
		m_gravity = val;
	}

	void PhyWorld::addSoftBody( PhySoftBody* softBody )
	{
		m_collisionWorld->addSoftBody(softBody->getBtSoftBody());

		m_softBodies.push_back(softBody);
	}

	PhySoftBody* PhyWorld::getSoftBody( unsigned int index )
	{
		assert(index < (unsigned int)m_softBodies.size() && "PhyWorld::getSoftBody");

		return m_softBodies[index];
	}

	unsigned int PhyWorld::getNumSoftBodies() const
	{
		return (unsigned int)m_softBodies.size();
	}

	void PhyWorld::removeAllSoftBodies()
	{
		std::vector<PhySoftBody*>::iterator iter;
		for (iter = m_softBodies.begin();iter != m_softBodies.end();iter ++)
		{
			PhySoftBody* softBody = (*iter);

			btSoftBody* bulletSoftBody = softBody->getBtSoftBody();

			m_collisionWorld->removeSoftBody(bulletSoftBody);

			delete *iter;
			*iter = NULL;
		}

		m_softBodies.clear();
	}

	void PhyWorld::removeSoftBody( PhySoftBody* softBody )
	{
		std::vector<PhySoftBody*>::iterator iter = std::find(m_softBodies.begin(),m_softBodies.end(),softBody);

		if (m_softBodies.end() == iter)
			return;

		PhySoftBody* physicsSofyBody = *iter;
		btSoftBody* bulletSoftBody = physicsSofyBody->getBtSoftBody();

		m_collisionWorld->removeSoftBody(bulletSoftBody);

		delete *iter;
		*iter = NULL;

		m_softBodies.erase(iter);
	}

	void PhyWorld::addConstraint( PhyConstraint* constraint )
	{
		m_collisionWorld->addConstraint(constraint->getBtConstraint());
		m_constraints.push_back(constraint);
	}

	PhyConstraint* PhyWorld::getConstraint( unsigned int index )
	{
		assert(index < (unsigned int)m_constraints.size() && "PhyWorld::getConstraint");

		return m_constraints[index];
	}

	unsigned int PhyWorld::getNumConstraints() const
	{
		return (unsigned int)m_constraints.size();
	}

	void PhyWorld::removeAllConstraints()
	{
		std::vector<PhyConstraint*>::iterator iter;
		for (iter = m_constraints.begin();iter != m_constraints.end();iter ++)
		{
			PhyConstraint* constraint = *iter;
			btTypedConstraint* bulletConstraint = constraint->getBtConstraint();

			m_collisionWorld->removeConstraint(bulletConstraint);

			delete *iter;
			*iter = NULL;
		}

		m_constraints.clear();
	}

	void PhyWorld::removeConstraints( PhyConstraint* constraint )
	{
		std::vector<PhyConstraint*>::iterator iter = std::find(m_constraints.begin(),m_constraints.end(),constraint);

		if (m_constraints.end() == iter)
			return;

		PhyConstraint* physicsConstraint = *iter;
		btTypedConstraint* bulletConstraint = physicsConstraint->getBtConstraint();

		m_collisionWorld->removeConstraint(bulletConstraint);

		delete *iter;
		*iter = NULL;

		m_constraints.erase(iter);
	}

	btBroadphaseInterface* PhyWorld::getBroadphase() const
	{
		return m_broadphase;
	}

	Ogre::String PhyWorld::CmdGravity::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const PhyWorld*>(target)->getGravity());
	}

	void PhyWorld::CmdGravity::doSet( void* target, const String& val )
	{
		static_cast<PhyWorld*>(target)->setGravity(
			Ogre::StringConverter::parseReal(val));
	}
}