#pragma once
#include <DirectXMath.h>
class KeyFrame
{
	friend class AnimationTrack;
public:
	KeyFrame(Real timePos);
	~KeyFrame();

	
	void setTranslation(const DirectX::XMFLOAT3& tran);
	void setScale(const DirectX::XMFLOAT3& scale);
	void setRotation(const DirectX::XMFLOAT4& quat);

	void setTranslate(const Ogre::Vector3& tran);
	void setScale(const Ogre::Vector3& scale);
	void setRotation(const Ogre::Quaternion& quat);

	void setTimePos(float timePos);
	float getTimePos();
	//for ogre
	const Ogre::Vector3& getScale() const;
	const Ogre::Vector3& getTranslation() const;
	const Ogre::Quaternion& getRotationQuat() const;
private:
	Real mTimePos;
	Ogre::Vector3 mTranslation;
	Ogre::Vector3 mScale;
	Ogre::Quaternion mRotationQuat;
};