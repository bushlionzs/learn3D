#ifndef OGBullet_h__
#define OGBullet_h__

namespace Orphigine
{
	class SceneNode;
}

namespace Orphigine
{
	class _OrphigineExport Bullet
	{
	public:
		Bullet();
		virtual ~Bullet();

		const Ogre::Vector3& getPositionWorld() const;
		void setPositionWorld(const Ogre::Vector3& val);

		const Ogre::Quaternion& getOrientationWorld() const;
		void setOrientationWorld(const Ogre::Quaternion& val);

		const Ogre::Vector3& getVelocityWorld() const;
		void setVelocityWorld(const Ogre::Vector3& val);

		const Ogre::Vector3& getAngularVelocityWorld() const;
		void				 setAngularVelocityWorld(const Ogre::Vector3& val);

		const Ogre::Vector3& getAccelerationWorld() const;
		void setAccelerationWorld(const Ogre::Vector3& val);

		unsigned int getClusterIndex() const;
		void setClusterIndex(unsigned int val);

	protected:
		Ogre::Vector3		m_positionWorld;
		Ogre::Quaternion	m_orientationWorld;
		Ogre::Vector3		m_velocityWorld;
		Ogre::Vector3		m_angularVelocityWorld;
		Ogre::Vector3		m_accelerationWorld;
		Ogre::SceneNode*	m_sceneNode;
		unsigned int		m_clusterIndex;
		
	private:
	};
}
#endif // OGBullet_h__