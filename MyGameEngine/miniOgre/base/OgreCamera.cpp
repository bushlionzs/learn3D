#include "OgreHeader.h"
#include "OgreCamera.h"
#include "camera_impl.h"
#include "OgreNode.h"
#include "engine_manager.h"
#include "OgreViewport.h"
#include "OgreSceneManager.h"

namespace Ogre {
	// constructor with vectors
	Camera::Camera(const String& name, SceneManager* sceneMgr)
		:MoveObject(name),
		mCreator(sceneMgr)
	{

		mCameraImpl = new CameraImpl(sceneMgr);
	}


	const Ogre::Matrix4& Camera::getViewMatrix() const
	{
		return mCameraImpl->getViewMatrix();
	}

	const Ogre::Matrix4& Camera::getProjectMatrix() const
	{
		return mCameraImpl->getProjectMatrix();
	}

	const Ogre::Matrix4& Camera::getProjectionMatrixWithRSDepth(void) const
	{
		return mCameraImpl->getProjectionMatrixWithRSDepth();
	}

	const Ogre::Vector3& Camera::getDerivedPosition() const
	{
		if (mParent)
		{
			return mParent->_getDerivedPosition();
		}
		return Ogre::Vector3::ZERO;
	}

	const Ogre::Quaternion& Camera::getDerivedOrientation() const
	{
		if (mParent)
		{
			return mParent->_getDerivedOrientation();
		}
		return Ogre::Quaternion::IDENTITY;
	}


	Ogre::Vector3 Camera::getDerivedDirection(void) const
	{
		return -mParent->_getDerivedOrientation().zAxis();
	}

	/** Gets the derived up vector of the camera, including any
		rotation inherited from a node attachment and reflection matrix. */
	Ogre::Vector3 Camera::getDerivedUp(void) const
	{
		return -mParent->_getDerivedOrientation().yAxis();
	}
	/** Gets the derived right vector of the camera, including any
		rotation inherited from a node attachment and reflection matrix. */
	Ogre::Vector3 Camera::getDerivedRight(void) const
	{
		return -mParent->_getDerivedOrientation().xAxis();
	}

	bool Camera::isVisible(const Ogre::Sphere& bound) const
	{
		return true;
		return mCameraImpl->isVisible(bound);
	}

	bool Camera::isVisible(const AxisAlignedBox& bound) const
	{
		return true;
		return mCameraImpl->isVisible(bound);
	}

	bool Camera::isVisible(const Ogre::Vector3& position) const
	{
		return mCameraImpl->isVisible(position);
	}

	Viewport* Camera::getViewport(void) const
	{
		return mViewport;
	}

	/** Notifies this camera that a viewport is using it.*/
	void Camera::_notifyViewport(Viewport* viewport)
	{
		mViewport = viewport;
	}

	bool Camera::getAutoAspectRatio(void) const
	{
		return true;
	}

	unsigned int Camera::_getNumRenderedFaces(void) const
	{
		return 1;
	}

	unsigned int Camera::_getNumRenderedBatches(void) const
	{
		return 1;
	}

	void Camera::_renderScene(Viewport* vp)
	{
		mCreator->_renderScene(this, vp);
	}

	const AxisAlignedBox& Camera::getBoundingBox(void) const
	{
		static AxisAlignedBox aa;
		return aa;
	}

	Real Camera::getAspectRatio()
	{
		return 0.0f;
	}

	void Camera::setAspectRatio(float aa)
	{
		mCameraImpl->setAspectRatio(aa);
	}

	void Camera::needUpdate()
	{
		mNeedUpdate = true;
	}

	void Camera::updateCamera(
		const Ogre::Vector3& eyePos,
		const Ogre::Vector3& targetPos,
		const Ogre::Vector3& up)
	{
		mCameraImpl->updateView(eyePos, targetPos, up);
	}

	Ray Camera::getCameraToViewportRay(Real screenX, Real screenY) const
	{
		Ray ray;
		getCameraToViewportRay(screenX, screenY, &ray);
		return ray;
	}
	void Camera::getCameraToViewportRay(Real screenX, Real screenY, Ray* outRay) const
	{
		Matrix4 inverseVP = (getProjectMatrix() * getViewMatrix()).inverse();

		Real nx = (2.0f * screenX) - 1.0f;
		Real ny = 1.0f - (2.0f * screenY);
		Vector3 nearPoint(nx, ny, -1.f);
		// Use midPoint rather than far point to avoid issues with infinite projection
		Vector3 midPoint(nx, ny, 0.0f);

		// Get ray origin and ray target on near plane in world space
		Vector3 rayOrigin, rayTarget;

		rayOrigin = inverseVP * nearPoint;
		rayTarget = inverseVP * midPoint;

		Vector3 rayDirection = rayTarget - rayOrigin;
		rayDirection.normalise();

		outRay->setOrigin(rayOrigin);
		outRay->setDirection(rayDirection);
	}

	void Camera::setNearClipDistance(float znear)
	{
		mCameraImpl->setNearClipDistance(znear);
	}

	void Camera::setFarClipDistance(float zfar)
	{
		mCameraImpl->setFarClipDistance(zfar);
	}

	void Camera::setPolygonMode(PolygonMode sd)
	{

	}

	void Camera::setProjectionType(Ogre::ProjectionType pt)
	{
		mCameraImpl->setProjectionType(pt);
	}

	void Camera::setOrthoWindow(float w, float h)
	{
		mCameraImpl->setOrthoWindow(w, h);
	}

	bool Camera::isReflected()
	{
		return mCameraImpl->isReflected();
	}

	void Camera::enableReflection(const Plane& p)
	{
		mCameraImpl->enableReflection(p);
	}

	void Camera::disableReflection(void)
	{
		mCameraImpl->disableReflection();
	}

	void Camera::enableCustomNearClipPlane(const Plane& plane)
	{
		mCameraImpl->enableCustomNearClipPlane(plane);
	}

	void Camera::disableCustomNearClipPlane(void)
	{
		mCameraImpl->disableCustomNearClipPlane();
	}
}