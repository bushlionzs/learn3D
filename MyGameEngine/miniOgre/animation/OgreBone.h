#pragma once
#include "OgreNode.h"

namespace Ogre {
	class Bone : public Node
	{
	public:
		Bone(const std::string& name, uint32_t boneId);
		Bone(Bone& other);
		~Bone();

		Bone* getParent();
		void updateParent(Bone* parent);

		uint32_t getBoneId();

		void setBindingPose(void);

		void reset(void);

		void _getOffsetTransform(Ogre::Matrix4& m);

		void setInverseBindMatrix(const Ogre::Matrix4& m);
		const Ogre::Matrix4& getInverseBindMatrix() const;
	private:
		uint32_t mBoneId;

		Ogre::Vector3 mBindDerivedInverseScale;
		/// The inversed derived orientation of the bone in the binding pose
		Ogre::Quaternion mBindDerivedInverseOrientation;
		/// The inversed derived position of the bone in the binding pose
		Ogre::Vector3 mBindDerivedInversePosition;


		Ogre::Matrix4 mInverseMatrix;
	};
}