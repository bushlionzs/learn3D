#ifndef OgreMeshComponentParticleVisualData_h__
#define OgreMeshComponentParticleVisualData_h__

#include <OgreParticle.h>
#include <OgreMaterial.h>

namespace Ogre {

	class SceneNode;
	class Entity;

	class MeshComponentParticleVisualData : public ParticleVisualData
	{
	public:
		MeshComponentParticleVisualData();
		~MeshComponentParticleVisualData();

		void setPosition( const Vector3 &pos );

		/** ���ݴ���ķ������÷�λ��Ϣ
		@param dir Ҫ���õķ���
		@param parentOrientation ����ϵͳ�ڵ�ķ�λ
		*/
		void setDirection( const Vector3 &dir, const Quaternion& parentOrientation);	

		void setOrientation( const Radian &yaw, const Radian &pitch, const Radian &roll );
		void setOrientation( const Quaternion& q );

		/** ���÷�λ
		@param rotate �Ƿ�Ҫ������ת��
		@param parentOrientation ����ϵͳ�ڵ�ķ�λ
		*/
		void setOrientation(bool rotate, const Quaternion& parentOrientation);

		void setScale( Real xzSize, Real ySize );

		void setVisible(bool visible);
		bool getVisible(void);

		void setColour( const ColourValue &colour );

		void modifyMesh(const String &meshName);
		void modifyMaterial(const String &matName);

		void setAnimationSpeedFactor(Real factor);

		void updateAnimation(void);

		void resetAnimation(void);

		void setRenderQueueGroup(uint8 queueID);

		//	protected:

		void createVisualData(const String &meshName, const String &matName, Node* parentNode);
		void destroyVisualData(void);

		void cloneMaterial(const String& matName);

		bool isInit(void);

		void setPoolIndex(size_t index);
		size_t getPoolIndex(void) const;

	protected:
		SceneNode *mSceneNode;
		Entity *mEntity;
		MaterialPtr mMaterial;
		bool mInit;
		bool mVisible;
		AnimationState* mAnimtionState;
		size_t mPoolIndex;
		uint8 mRenderQueue_ID;
	public:
		Radian mYawRotation;
		Radian mPitchRotation;
		Radian mRollRotation;
		Radian mYawRotationSpeed;
		Radian mPitchRotationSpeed;
		Radian mRollRotationSpeed;
		Quaternion mOrientation;
		Real mDeltaTime;
		bool mAnimationLoop;
		String mAnimationName;
		Real mAnimSpeedFactor;
		bool mAnimationUpdated;

	};
}

#endif // OgreMeshComponentParticleVisualData_h__