#include "OgreHeader.h"
#include "OgreRoot.h"
#include "camera_impl.h"


CameraImpl::CameraImpl(Ogre::SceneManager* sceneMgr)
{
	mSceneManager = sceneMgr;
    mFovy = 3.141592653 / 2.0f;

    auto config = Ogre::Root::getSingleton().getEngineConfig();
    uint32_t width = config.width;
    uint32_t height = config.height;
    mAspectRation = (float)width / (float)height;

    mViewMatrix = Ogre::Matrix4::IDENTITY;
    

    if (mProjectType == Ogre::PT_ORTHOGRAPHIC)
    {
        Real left = -mOrthoWidth / 2.0f;
        Real right = mOrthoWidth / 2.0f;
        Real top = mOrthoHeight / 2.0f;
        Real bottom = -mOrthoHeight / 2.0f;

        left = 0.0f;
        top = 0.0f;
        right = mOrthoWidth;
        bottom = mOrthoHeight;
        mProjectMatrix =
            Ogre::Math::makeOrthoLH(left, right, bottom, top, mNear, mFar);
    }
    else
    {
        mProjectMatrix =
            Ogre::Math::makePerspectiveMatrixLH(mFovy, mAspectRation, mNear, mFar);
    }
}

CameraImpl::~CameraImpl()
{

}

void CameraImpl::updateView(const Ogre::Vector3& position, const Ogre::Quaternion& orientation)
{
	mViewMatrix = Ogre::Math::makeViewMatrix(position, orientation);
    updateFrustum();
}


void CameraImpl::updateView(const Ogre::Matrix4& view)
{
    mViewMatrix = view;
    updateFrustum();
}

void CameraImpl::updateProject(const Ogre::Matrix4& project)
{
    mProjectMatrix = project;
    updateFrustum();
}


void CameraImpl::updateFrustum()
{
    Ogre::Matrix4 combo = mProjectMatrix * mViewMatrix;

    mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal.x = combo[3][0] + combo[0][0];
    mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal.y = combo[3][1] + combo[0][1];
    mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal.z = combo[3][2] + combo[0][2];
    mFrustumPlanes[FRUSTUM_PLANE_LEFT].d = combo[3][3] + combo[0][3];

    mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal.x = combo[3][0] - combo[0][0];
    mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal.y = combo[3][1] - combo[0][1];
    mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal.z = combo[3][2] - combo[0][2];
    mFrustumPlanes[FRUSTUM_PLANE_RIGHT].d = combo[3][3] - combo[0][3];

    mFrustumPlanes[FRUSTUM_PLANE_TOP].normal.x = combo[3][0] - combo[1][0];
    mFrustumPlanes[FRUSTUM_PLANE_TOP].normal.y = combo[3][1] - combo[1][1];
    mFrustumPlanes[FRUSTUM_PLANE_TOP].normal.z = combo[3][2] - combo[1][2];
    mFrustumPlanes[FRUSTUM_PLANE_TOP].d = combo[3][3] - combo[1][3];

    mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].normal.x = combo[3][0] + combo[1][0];
    mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].normal.y = combo[3][1] + combo[1][1];
    mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].normal.z = combo[3][2] + combo[1][2];
    mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].d = combo[3][3] + combo[1][3];

    mFrustumPlanes[FRUSTUM_PLANE_NEAR].normal.x = combo[3][0] + combo[2][0];
    mFrustumPlanes[FRUSTUM_PLANE_NEAR].normal.y = combo[3][1] + combo[2][1];
    mFrustumPlanes[FRUSTUM_PLANE_NEAR].normal.z = combo[3][2] + combo[2][2];
    mFrustumPlanes[FRUSTUM_PLANE_NEAR].d = combo[3][3] + combo[2][3];

    mFrustumPlanes[FRUSTUM_PLANE_FAR].normal.x = combo[3][0] - combo[2][0];
    mFrustumPlanes[FRUSTUM_PLANE_FAR].normal.y = combo[3][1] - combo[2][1];
    mFrustumPlanes[FRUSTUM_PLANE_FAR].normal.z = combo[3][2] - combo[2][2];
    mFrustumPlanes[FRUSTUM_PLANE_FAR].d = combo[3][3] - combo[2][3];

    for (int i = 0; i < 6; i++)
    {
        Real length = mFrustumPlanes[i].normal.normalise();
        mFrustumPlanes[i].d /= length;
    }
}

bool CameraImpl::isVisible(const Ogre::Sphere& bound) const
{
    return true;
}

bool CameraImpl::isVisible(const Ogre::AxisAlignedBox& bound) const
{
    // Null boxes always invisible
    if (bound.isNull())
    {
        return false;
    }
    

    // Infinite boxes always visible
    if (bound.isInfinite())
    {
        return true;
    }

    // Get centre of the box
    Ogre::Vector3 centre = bound.getCenter();
    // Get the half-size of the box
    Ogre::Vector3 halfSize = bound.getHalfSize();

    // For each plane, see if all points are on the negative side
    // If so, object is not visible
    for (int plane = 0; plane < 6; ++plane)
    {
        // Skip far plane if infinite view frustum
        if (plane == FRUSTUM_PLANE_FAR)
            continue;

        Ogre::Plane::Side side = mFrustumPlanes[plane].getSide(centre, halfSize);
        if (side == Ogre::Plane::NEGATIVE_SIDE)
        {
            return false;
        }

    }

    return true;
}

bool CameraImpl::isVisible(const Ogre::Vector3& position) const
{
    for (int plane = 0; plane < 6; ++plane)
    {
        // Skip far plane if infinite view frustum
        if (plane == FRUSTUM_PLANE_FAR)
            continue;

        Ogre::Plane::Side side = mFrustumPlanes[plane].getSide(position);
        if (side == Ogre::Plane::NEGATIVE_SIDE)
        {
            return false;
        }

    }

    return true;
}

void CameraImpl::setAspectRatio(float aa)
{
    mAspectRation = aa;

    mUpdate = true;
}

void CameraImpl::setNearClipDistance(float znear)
{
    mNear = znear;
    mUpdate = true;
}

void CameraImpl::setFarClipDistance(float zfar)
{
    mFar = zfar;
    mUpdate = true;
}

void CameraImpl::setProjectionType(Ogre::ProjectionType pt)
{
    mProjectType = pt;
    mUpdate = true;
}

void CameraImpl::setOrthoWindow(float w, float h)
{
    mOrthoWidth = w;
    mOrthoHeight = h;
}

bool CameraImpl::isReflected()
{
    return mReflect;
}

void CameraImpl::enableReflection(const Ogre::Plane& p)
{
    mReflect = true;
    mReflectPlane = p;
    mLinkedReflectPlane = 0;
    mReflectMatrix = Ogre::Math::buildReflectionMatrix(p);
    mUpdate = true;
}

void CameraImpl::disableReflection(void)
{
    mReflect = false;
    mLinkedReflectPlane = 0;
    mLastLinkedReflectionPlane.normal = Ogre::Vector3::ZERO;
    mUpdate = true;
}

void CameraImpl::enableCustomNearClipPlane(const Ogre::Plane& plane)
{
    mObliqueDepthProjection = true;
    mLinkedObliqueProjPlane = 0;
    mObliqueProjPlane = plane;
    mUpdate = true;
}

void CameraImpl::disableCustomNearClipPlane(void)
{
    mObliqueDepthProjection = false;
    mLinkedObliqueProjPlane = 0;
    mUpdate = true;
}

const Ogre::Matrix4& CameraImpl::getViewMatrix()
{
    return mViewMatrix;
}

const Ogre::Matrix4& CameraImpl::getProjectMatrix()
{
    return mProjectMatrix;  
}

const Ogre::Matrix4& CameraImpl::getProjectionMatrixWithRSDepth(void) const
{
    assert(false);
    return mProjMatrixRSDepth;
}

