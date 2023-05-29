#include "OgreHeader.h"
#include "OGPhyActor.h"
#include "OGPhyUtil.h"
#include "OGPhyShape.h"
#include "OGPhyUtil.h"

#include "OgreStringConverter.h"
#include "OgreAxisAlignedBox.h"
#include "OgreSceneNode.h"

#include "btBulletCollisionCommon.h"

namespace Orphigine
{

	PhysicsMotionState::PhysicsMotionState( const btTransform& startTransform,Ogre::SceneNode* sceneNode )
		: m_transform(startTransform)
		, m_sceneNode(sceneNode)		
	{
 
	}

	PhysicsMotionState::~PhysicsMotionState()
	{

	}

	void PhysicsMotionState::getWorldTransform( btTransform& worldTrans ) const
	{
		worldTrans = m_transform;
	}

	void PhysicsMotionState::setWorldTransform( const btTransform& worldTrans )
	{
		if(NULL == m_sceneNode)
			return;

		m_sceneNode->setPosition(bulletToOgreVector3(worldTrans.getOrigin()));

		m_sceneNode->setOrientation(bulletToOgreQuaternion(worldTrans.getRotation()));
	}
}

namespace Orphigine
{

	PhyActor::CmdPositionWorld			PhyActor::ms_positionWorldCmd;
	PhyActor::CmdOrientationWorld		PhyActor::ms_orientationWorldCmd;

	PhyActor::PhyActor(const Ogre::Vector3& position,const Ogre::Quaternion& rotation)
		: m_position(position)
		, m_rotation(rotation)
		, m_shape(NULL)
		, m_actor(NULL)
		, m_boundRadius(0.1f)		
	{
		if (createParamDictionary("PhyActorDict"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("Position","The position in world coordinate",Ogre::PT_VECTOR3),
				&ms_positionWorldCmd);

			dict->addParameter(Ogre::ParameterDef("Orientation","The orientation in world coordinate",Ogre::PT_QUATERNION),
				&ms_orientationWorldCmd);

		}
		_createActorImpl(position,rotation);
	}

	PhyActor::~PhyActor()
	{
		delete m_shape;
		m_shape = NULL;

		delete m_actor;
		m_actor = NULL;
	}

	const Ogre::Vector3& PhyActor::getPositionWorld() const
	{
		return m_position;
	}

	void PhyActor::setPositionWorld( const Ogre::Vector3& val )
	{
		m_position = val;

		if (m_actor)
		{
			btTransform actorTrans;
			actorTrans.setIdentity();
			actorTrans.setOrigin(ogreToBulletVector3(m_position));
			actorTrans.setRotation(ogreToBulletQuaternion(m_rotation));
			m_actor->setWorldTransform(actorTrans);
		}	
		updateBounds();
		//end
	}

	const uint32_t& PhyActor::getTypeWorld() const
	{
		return m_iType;
	}

	void	PhyActor::setTypeWorld(const uint32_t& val)
	{
		m_iType = val;
	}

	const Ogre::Quaternion& PhyActor::getOrientationWorld() const
	{
		return m_rotation;
	}

	void PhyActor::setOrientationWorld( const Ogre::Quaternion& val )
	{
		m_rotation = val;
		if (m_actor)
		{
			btTransform actorTrans;
			actorTrans.setIdentity();
			actorTrans.setOrigin(ogreToBulletVector3(m_position));
			actorTrans.setRotation(ogreToBulletQuaternion(m_rotation));
			m_actor->setWorldTransform(actorTrans);
		}	
		updateBounds();
		//end
	}

	btCollisionObject* PhyActor::getBtActor() const
	{
		return m_actor;
	}

	void PhyActor::_createActorImpl(const Ogre::Vector3& position,const Ogre::Quaternion& rotation )
	{
		m_actor = new btCollisionObject();

		m_actor->setUserPointer(this);
		//end

		btTransform actorTrans;
		actorTrans.setIdentity();

		m_position = position;
		m_rotation = rotation;
		m_centerPos = position;

		actorTrans.setOrigin(ogreToBulletVector3(position));

		actorTrans.setRotation(ogreToBulletQuaternion(rotation));

		m_actor->setWorldTransform(actorTrans);

	}

	PhyShape* PhyActor::getShape() const
	{
		return m_shape;
	}

	const Ogre::Vector3& PhyActor::getCenterPos() const 
	{
		return m_centerPos;
	}
	
	void PhyActor::updateBounds()
	{
		if (m_shape && m_actor) {

			btVector3 aabbMin, aabbMax;
			btTransform &actorTrans = m_actor->getWorldTransform();
			auto shape = m_shape->getBtShape();
			if (!shape)
			{
				return;
			}
			shape->getAabb(actorTrans, aabbMin, aabbMax);
			m_boundingBox = Ogre::AxisAlignedBox(bulletToOgreVector3(aabbMin), bulletToOgreVector3(aabbMax));
			Ogre::Vector3 size = m_boundingBox.getHalfSize();
			//ogre的aabbbox好象有bug，这里取绝对值
			size.x = abs(size.x); size.y = abs(size.y); size.z = abs(size.z);			
			m_boundRadius = size.length();
			m_centerPos = m_boundingBox.getCenter();
		}
		else {
			m_boundingBox = Ogre::AxisAlignedBox();
			m_boundRadius = 0.1f;
			m_centerPos = m_position;
		}
	}
	//end

	void PhyActor::setShape( PhyShape* val )
	{
		m_shape = val;		
		m_actor->setCollisionShape(val->getBtShape());
		updateBounds();
		//end
	}

	const String& PhyActor::getMovableType( void ) const
	{
		static String movableType = "PhyActor";

		return movableType;
	}

	const Ogre::AxisAlignedBox& PhyActor::getBoundingBox( void ) const
	{
		return m_boundingBox;
	}

	Ogre::Real PhyActor::getBoundingRadius( void ) const
	{
		return m_boundRadius;
	}
	//end

	void PhyActor::_updateRenderQueue( Ogre::RenderQueue* queue )
	{
		
	}

	Ogre::String PhyActor::CmdPositionWorld::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const PhyActor*>(target)->getPositionWorld());
	}

	void PhyActor::CmdPositionWorld::doSet( void* target, const String& val )
	{
		static_cast<PhyActor*>(target)->setPositionWorld(
			Ogre::StringConverter::parseVector3(val));
	}

	Ogre::String PhyActor::CmdOrientationWorld::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const PhyActor*>(target)->getOrientationWorld());
	}

	void PhyActor::CmdOrientationWorld::doSet( void* target, const String& val )
	{
		static_cast<PhyActor*>(target)->setOrientationWorld(
			Ogre::StringConverter::parseQuaternion(val));
	}
}