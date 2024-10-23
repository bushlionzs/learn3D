#pragma once
#include "OgreFrustum.h"
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class CameraImpl
{
public:
    enum FrustumPlane : uint8_t
    {
        FRUSTUM_PLANE_NEAR = 0,
        FRUSTUM_PLANE_FAR = 1,
        FRUSTUM_PLANE_LEFT = 2,
        FRUSTUM_PLANE_RIGHT = 3,
        FRUSTUM_PLANE_TOP = 4,
        FRUSTUM_PLANE_BOTTOM = 5
    };
public:
	CameraImpl(Ogre::SceneManager* sceneMgr);
	~CameraImpl();
    void updateView(
        const Ogre::Vector3& position, 
        const Ogre::Quaternion& orientation);
    void updateView(
        const Ogre::Matrix4& view);
    void updateProject(const Ogre::Matrix4& project);

    bool isVisible(const Ogre::Sphere& bound) const;
    bool isVisible(const Ogre::AxisAlignedBox& bound) const;
    bool isVisible(const Ogre::Vector3& position) const;

    void setAspectRatio(float aa);
    void setNearClipDistance(float znear);
    void setFarClipDistance(float zfar);
    float getNear()
    {
        return mNear;
    }
    float getFar()
    {
        return mFar;
    }
    void setProjectionType(Ogre::ProjectionType pt);
    Ogre::ProjectionType getProjectionType()
    {
        return mProjectType;
    }
    void setOrthoWindow(float w, float h);

    bool isReflected();
    virtual void enableReflection(const Ogre::Plane& p);
    virtual void disableReflection(void);
    virtual void enableCustomNearClipPlane(const Ogre::Plane& plane);
    virtual void disableCustomNearClipPlane(void);
private:
    void updateFrustum();
protected:
    mutable Ogre::Matrix4 mProjectMatrix;
    mutable Ogre::Matrix4 mProjMatrixRSDepth;
    mutable Ogre::Matrix4 mViewMatrix;
    Ogre::SceneManager* mSceneManager;

    /// The 6 main clipping planes
    mutable Ogre::Plane mFrustumPlanes[6];

    float mNear = 1.0f;
    float mFar = 50000.0f;

    float mAspectRation;
    float mFovy;

    bool mUpdate = true;
    Ogre::ProjectionType mProjectType = Ogre::PT_PERSPECTIVE;
    float mOrthoWidth;
    float mOrthoHeight;

    bool mReflect = false;
    mutable Ogre::Plane mReflectPlane;
    const Ogre::MovablePlane* mLinkedReflectPlane;
    mutable Ogre::Plane mLastLinkedReflectionPlane;
    mutable Ogre::Matrix4 mReflectMatrix;

    bool mObliqueDepthProjection = false;
    mutable Ogre::Plane mObliqueProjPlane;
    const Ogre::MovablePlane* mLinkedObliqueProjPlane;
    mutable Ogre::Plane mLastLinkedObliqueProjPlane;
public:
    const Ogre::Matrix4& getViewMatrix();

    const Ogre::Matrix4& getProjectMatrix();

    const Ogre::Matrix4& getProjectionMatrixWithRSDepth(void) const;
};