#ifndef OGPhyActor_h__
#define OGPhyActor_h__



#include "OgreStringInterface.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "OgrePrerequisites.h"
#include "OgreMoveObject.h"
#include "OgreAxisAlignedBox.h"

#include "LinearMath/btMotionState.h"


class btCollisionObject;
class btTransform;

namespace Ogre
{
	class SceneNode;
}

namespace Orphigine
{
	class PhysicsMotionState : public btMotionState
	{
	public:
		PhysicsMotionState(const btTransform& startTransform,Ogre::SceneNode* sceneNode);
		~PhysicsMotionState();

		virtual void			getWorldTransform(btTransform& worldTrans ) const;

		virtual void			setWorldTransform(const btTransform& worldTrans);
	protected:
		Ogre::SceneNode*		m_sceneNode;
		btTransform				m_transform;
	private:
	};

	class PhyShape;

	class _OrphigineExport PhyActor : public Ogre::StringInterface ,public Ogre::MoveObject
	{
	public:
		PhyActor(const Ogre::Vector3& position = Ogre::Vector3::ZERO,
			const Ogre::Quaternion& rotation = Ogre::Quaternion::IDENTITY);

		virtual ~PhyActor();

		class CmdPositionWorld : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdOrientationWorld : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		/*
		*	重载Ogre函数，见Ogre::MovableObject
		*/
		virtual const String&					getMovableType(void) const;

		virtual const Ogre::AxisAlignedBox&		getBoundingBox(void) const;

		virtual Real							getBoundingRadius(void) const;

		virtual void							_updateRenderQueue(Ogre::RenderQueue* queue);


		const Ogre::Vector3&					getPositionWorld() const;

		void									setPositionWorld(const Ogre::Vector3& val);

		const uint32_t& getTypeWorld() const;

		void	setTypeWorld(const uint32_t& val);

		const Ogre::Quaternion&					getOrientationWorld() const;

		void									setOrientationWorld(const Ogre::Quaternion& val);

		PhyShape*								getShape() const;

		void									setShape(PhyShape* val);

		btCollisionObject*						getBtActor() const;
		//chunlin added
		const Ogre::Vector3&                    getCenterPos() const;
		//end
		
		static CmdPositionWorld					ms_positionWorldCmd;
		static CmdOrientationWorld				ms_orientationWorldCmd;
	protected:
		void									_createActorImpl(const Ogre::Vector3& position,const Ogre::Quaternion& rotation);
		//chunlin added
		void                                    updateBounds();
		//end
	protected:
		Ogre::Vector3							m_position;
		Ogre::Quaternion						m_rotation;
		PhyShape*								m_shape;

		btCollisionObject*						m_actor;
		Ogre::SceneNode*						m_sceneNode;
		Ogre::AxisAlignedBox					m_boundingBox;

		Ogre::Real								m_boundRadius;
		Ogre::Vector3                           m_centerPos;
		//end

		uint32_t m_iType;//碰撞类型：0为正常可以行走和阴影片的行走面驶,1为只给摄像机碰撞的行走面
	private:
	};
}
#endif // OGPhyActor_h__