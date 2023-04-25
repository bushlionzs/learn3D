#pragma once

namespace Ogre
{ 
	enum CameraType
	{
		CameraType_Common = 0,
		CameraType_Light  = 1
	};
class ICamera
{
public:
	virtual const Ogre::Matrix4& getViewMatrix() const = 0;
	virtual const Ogre::Matrix4& getProjectMatrix() const = 0;
	virtual const Ogre::Vector3& getDerivedPosition() const = 0;
	virtual bool isVisible(const AxisAlignedBox& bound) const = 0;
	virtual const CameraType getCameraType();
};
}