#pragma once

#include "OgreFrustum.h"
namespace Ogre
{ 
	enum CameraType
	{
		CameraType_Common = 0,
		CameraType_Light  = 1
	};
	class SceneManager;
class ICamera
{
public:
	virtual const Ogre::Matrix4& getViewMatrix() const = 0;
	virtual const Ogre::Matrix4& getProjectMatrix() const = 0;
	virtual const Ogre::Vector3& getDerivedPosition() const = 0;
	virtual bool isVisible(const AxisAlignedBox& bound) const = 0;
	virtual Ogre::ProjectionType getProjectionType() { return Ogre::PT_ORTHOGRAPHIC; }
	virtual const CameraType getCameraType();
	virtual SceneManager* getCreator() { return nullptr; }
	virtual void setCameraCull(bool cull) {}
};

}