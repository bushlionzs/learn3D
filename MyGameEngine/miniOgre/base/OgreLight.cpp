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
	auto& position = mParent->getPosition();
	auto& orientation = mParent->getOrientation();
	mViewMatrix = Ogre::Math::makeViewMatrix(position, orientation);

	return mViewMatrix;
}

const Ogre::Matrix4& Light::getProjectMatrix() const
{
	float width = 20.0f;
	float height = 20.0f;
	Real left = -width / 2.0f;
	Real right = width / 2.0f;
	Real top = height / 2.0f;
	Real bottom = -height / 2.0f;
	mProjMatrix =
		Ogre::Math::makeOrthoLH(left, right, bottom, top, 1.0f, 100);
	return mProjMatrix;
}

const Ogre::Vector3& Light::getDerivedPosition() const
{
	return mParent->_getDerivedPosition();
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
}