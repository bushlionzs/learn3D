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
#include <DirectXMath.h>
using namespace DirectX;
const Ogre::Matrix4& Light::getViewMatrix() const
{
	auto& q = mParent->_getDerivedOrientation();
	Matrix3 rot;
	q.ToRotationMatrix(rot);

	auto dir = rot.GetColumn(2);

	{
		Ogre::Vector3 target = Ogre::Vector3::ZERO;
		Ogre::Vector3 position = target + (dir) * 40;
		mParent->setPosition(position);
		mViewMatrix = Ogre::Math::makeLookAtLH(position, target, Ogre::Vector3::UNIT_Y);
		return mViewMatrix;
	}
	
}



const Ogre::Matrix4& Light::getProjectMatrix() const
{
	float width = 40.0f;
	float height = 40.0f;
	Real left = -width / 2.0f;
	Real right = width / 2.0f;
	Real top = height / 2.0f;
	Real bottom = -height / 2.0f;
	mProjMatrix =
		Ogre::Math::makeOrthoRH(left, right, bottom, top, 2, 100);
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

Ogre::Vector3 Light::getLightDirection()
{
	const Ogre::Quaternion& q = mParent->_getDerivedOrientation();
	Matrix3 rot;
	q.ToRotationMatrix(rot);
	return rot.GetColumn(2);
}

}