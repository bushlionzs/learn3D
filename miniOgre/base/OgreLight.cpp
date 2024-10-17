#include "OgreHeader.h"
#include "OgreLight.h"
#include "OgreNode.h"

namespace Ogre
{
void Light::setDiffuseColour(float red, float green, float blue)
{

}

void Light::setDiffuseColour(const ColourValue& colour)
{

}

const ColourValue& Light::getDiffuseColour(void) const
{
	return ColourValue::Black;
}

void Light::setSpecularColour(float red, float green, float blue)
{

}

void Light::setSpecularColour(const ColourValue& colour)
{

}

void Light::setAttenuation(float range, float constant, float linear, float quadratic)
{

}

const Ogre::Matrix4& Light::getViewMatrix() const
{
	return mViewMatrix;
}



const Ogre::Matrix4& Light::getProjectMatrix() const
{
	return mProjMatrix;
}

const Ogre::Vector3& Light::getDerivedPosition() const
{
	mPosition = mViewMatrix.getTrans();
	return mPosition;
}

bool Light::isVisible(const AxisAlignedBox& bound) const
{
	return true;
}

const AxisAlignedBox& Light::getBoundingBox(void) const
{
	static AxisAlignedBox box;
	box.setNull();
	return box;
}

const CameraType Light::getCameraType()
{
	return CameraType_Light;
}

void Light::setLightType(LightType type, uint32_t lightNumber)
{
	mLightType = type;
	mLightNumber = lightNumber;
}

LightType Light::getLightType()
{
	return mLightType;
}

uint32_t Light::getLightNumber()
{
	return mLightNumber;
}

Ogre::Vector3 Light::getLightUp()
{
	const Ogre::Quaternion& q = mParent->_getDerivedOrientation();
	Matrix3 rot;
	q.ToRotationMatrix(rot);
	return rot.GetColumn(1);
}

Ogre::Vector3 Light::getLightDirection()
{
	const Ogre::Quaternion& q = mParent->_getDerivedOrientation();
	Matrix3 rot;
	q.ToRotationMatrix(rot);
	return rot.GetColumn(2);
}

}