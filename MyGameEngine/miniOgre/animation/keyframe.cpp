#include "OgreHeader.h"
#include "keyFrame.h"

KeyFrame::KeyFrame(Real timePos)
{
	mTimePos = timePos; 
	mScale.x = mScale.y = mScale.z = 1.0f;
	mTranslation.x = mTranslation.y = mTranslation.z = 0;
	mRotationQuat.x = mRotationQuat.y = mRotationQuat.z = 0;
	mRotationQuat.w = 1;
}

KeyFrame::~KeyFrame()
{

}

void KeyFrame::setTranslation(const DirectX::XMFLOAT3& tran)
{
	mTranslation.x = tran.x;
	mTranslation.y = tran.y;
	mTranslation.z = tran.z;
}

void KeyFrame::setScale(const DirectX::XMFLOAT3& scale)
{
	mScale.x = scale.x;
	mScale.y = scale.y;
	mScale.z = scale.z;
}

void KeyFrame::setRotation(const DirectX::XMFLOAT4& quat)
{
	mRotationQuat.x = quat.x;
	mRotationQuat.y = quat.y;
	mRotationQuat.z = quat.z;
	mRotationQuat.w = quat.w;
}

void KeyFrame::setTranslate(const Ogre::Vector3& tran)
{
	mTranslation = tran;
}

void KeyFrame::setScale(const Ogre::Vector3& scale)
{
	mScale = scale;
}

void KeyFrame::setRotation(const Ogre::Quaternion& quat)
{
	mRotationQuat = quat;

}

void KeyFrame::setTimePos(float timePos)
{
	mTimePos = timePos;
}

float KeyFrame::getTimePos()
{
	return mTimePos;
}

const Ogre::Vector3& KeyFrame::getScale() const
{
	return mScale;
}

const Ogre::Vector3& KeyFrame::getTranslation() const
{
	return mTranslation;
}

const Ogre::Quaternion& KeyFrame::getRotationQuat() const
{
	return mRotationQuat;
}