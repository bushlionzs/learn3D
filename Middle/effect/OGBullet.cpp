#include "OgreHeader.h"
#include "OGBullet.h"
#include "OgreSceneNode.h"

namespace Orphigine
{

	Bullet::Bullet()
	{
		m_positionWorld = Ogre::Vector3(0.0f,0.0f,0.0f);
		m_orientationWorld = Ogre::Quaternion::IDENTITY;
		m_velocityWorld = Ogre::Vector3(0.0f,0.0f,0.0f);
		m_angularVelocityWorld = Ogre::Vector3(0.0f,0.0f,0.0f);
		m_accelerationWorld = Ogre::Vector3(0.0f,0.0f,0.0f);
		m_sceneNode = NULL;
		m_clusterIndex = 0;
	}

	Bullet::~Bullet()
	{

	}

	const Ogre::Vector3& Bullet::getPositionWorld() const
	{
		return m_positionWorld;
	}

	void Bullet::setPositionWorld( const Ogre::Vector3& val )
	{
		m_positionWorld = val;
	}

	const Ogre::Vector3& Bullet::getVelocityWorld() const
	{
		return m_velocityWorld;
	}

	void Bullet::setVelocityWorld( const Ogre::Vector3& val )
	{
		m_velocityWorld = val;
	}

	const Ogre::Vector3& Bullet::getAccelerationWorld() const
	{
		return m_accelerationWorld;
	}

	void Bullet::setAccelerationWorld( const Ogre::Vector3& val )
	{
		m_accelerationWorld = val;
	}

	unsigned int Bullet::getClusterIndex() const
	{
		return m_clusterIndex;
	}

	void Bullet::setClusterIndex( unsigned int val )
	{
		m_clusterIndex = val;
	}

	const Ogre::Quaternion& Bullet::getOrientationWorld() const
	{
		return m_orientationWorld;
	}

	void Bullet::setOrientationWorld( const Ogre::Quaternion& val )
	{
		m_orientationWorld = val;
	}

	const Ogre::Vector3& Bullet::getAngularVelocityWorld() const
	{
		return m_angularVelocityWorld;
	}

	void Bullet::setAngularVelocityWorld( const Ogre::Vector3& val )
	{
		m_angularVelocityWorld = val;
	}
}