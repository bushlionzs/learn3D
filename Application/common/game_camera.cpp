#include "OgreHeader.h"
#include <cmath>
#include "game_camera.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNOde.h"

GameCamera::GameCamera(Ogre::Camera* camera, Ogre::SceneManager* sceneMgr)
{
    mCamera = camera;
    mSceneMgr = sceneMgr;
    mChanged = true;
    mCameraType = Ogre::CameraMoveType_FirstPerson;
}

const Ogre::Vector3& GameCamera::getPosition() const
{
    return eyePosition;
}

void GameCamera::setDistance(float distance)
{
    mDistance = distance;
    
}

void GameCamera::setHeight(float height)
{
}

void GameCamera::setMoveSpeed(Real speed)
{
    mMoveSpeed = speed;
}

void GameCamera::setRotateSpeed(Real speed)
{
    mRotateSpeed = speed;
}

void GameCamera::updatePosition(const Ogre::Vector3& camPosition)
{
    eyePosition = camPosition;
}

void GameCamera::updateRotate(const Ogre::Vector3& camRotate)
{
    rotation = camRotate;
}

void GameCamera::lookAt(
    const Ogre::Vector3& camPos,
    const Ogre::Vector3& targetPos,
    const Ogre::Vector3& up)
{
    mRelativePosition = targetPos - camPos;
    mRelativePosition.normalise();
    eyePosition = camPos;
    targetPosition = targetPos;
   
    Ogre::Matrix4 viewMatrix = Ogre::Math::makeLookAt(camPos, targetPos, up);
    Ogre::Matrix4 m = viewMatrix.transpose();
    mCamera->updateViewMatrix(viewMatrix);
    mCamera->updatePosition(camPos);
    Ogre::Vector3 lookDir = targetPos - camPos;
    lookDir.normalise();
    float y = lookDir.y;
    rotation.x = -asinf(y) ;

    float x = lookDir.x;
    float z = lookDir.z;
    float n = sqrtf((x * x) + (z * z));
    if (n > 0.01f)
    {
        // don't change the Y rotation if we're too close to vertical
        x /= n;
        z /= n;
        rotation.y = atan2f(x, z) ;

        if (Ogre::Math::isRightHanded())
        {
            rotation.y -= Ogre::Math::PI;
        }
    }
}

void GameCamera::injectMouseWheel(int _absz)
{
    mDistance += _absz * 0.2f;

    if (mDistance <= 50.0f)
    {
        mDistance = 50.0f;
    }

    if (mDistance >= 1200.0f)
    {
        mDistance = 1200.0f;
    }
}
void GameCamera::injectMouseMove(int _absx, int _absy, int _absz)
{
    if (!mPickup)
        return;
    mChanged = true;
    mMouseDeltaX = _absx - mMousePickX;
    mMouseDeltaY = _absy - mMousePickY;

    float pitch = 0.0f;

    bool need = false;

    float yaw = 0.0f;
    if (mMouseDeltaX != 0)
    {
        mYaw -= mMouseDeltaX * mRotateSpeed;
        need = true;

        yaw = mMouseDeltaX * mRotateSpeed;
    }


    if (mMouseDeltaY != 0)
    {
        mPitch -= mMouseDeltaY * mRotateSpeed;
        pitch = mMouseDeltaY * mRotateSpeed;
        need = true;
    }

    rotation += Ogre::Vector3(pitch, -yaw, 0.0f);


    mMousePickX = _absx;
    mMousePickY = _absy;
}

void GameCamera::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
    if (_id == OIS::MouseButtonID::MB_Right)
    {
        mMousePickX = _absx;
        mMousePickY = _absy;
        mPickup = true;
    }
}

void GameCamera::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
    if (_id == OIS::MouseButtonID::MB_Right)
    {
        mPickup = false;
    }
}

void GameCamera::injectKeyPress(KeyCode _key, uint32_t _text)
{
    if (_key == KeyCode::W || _key == KeyCode::ArrowUp)
    {
        mGoingForward = true;
    }
    else if (_key == KeyCode::S || _key == KeyCode::ArrowDown)
    {
        mGoingBack = true;
    }
    else if (_key == KeyCode::A || _key == KeyCode::ArrowLeft)
    {
        mGoingLeft = true;
    }
    else if (_key == KeyCode::D || _key == KeyCode::ArrowRight)
    {
        mGoingRight = true;
    }
    else if (_key == KeyCode::LeftShift)
    {
        mFastMove = true;
    }
    else if (_key == KeyCode::Q)
    {
        mGoingUp = true;
    }
    else if (_key == KeyCode::E)
    {
        mGoingDown = true;
    }
}

void GameCamera::injectKeyRelease(KeyCode _key)
{
    if (_key == KeyCode::W || _key == KeyCode::ArrowUp)
    {
        mGoingForward = false;
    }
    else if (_key == KeyCode::S || _key == KeyCode::ArrowDown)
    {
        mGoingBack = false;
    }
    else if (_key == KeyCode::A || _key == KeyCode::ArrowLeft)
    {
        mGoingLeft = false;
    }
    else if (_key == KeyCode::D || _key == KeyCode::ArrowRight)
    {
        mGoingRight = false;
    }
    else if (_key == KeyCode::LeftShift)
    {
        mFastMove = false;
    }
    else if (_key == KeyCode::Q)
    {
        mGoingUp = false;
    }
    else if (_key == KeyCode::E)
    {
        mGoingDown = false;
    }
}

bool GameCamera::update(float delta)
{
    float x = rotation.x;
    float y = rotation.y;
 
    
    if (mGoingForward || mGoingBack || mGoingLeft || mGoingRight || mGoingUp || mGoingDown)
    {
        mChanged = true;
        auto rot = mCamera->getViewMatrix();
        auto right = rot.getRight();
        auto up = rot.getUp();
        auto forward = rot.getForward();

        if (Ogre::Math::isRightHanded())
        {
            forward = -forward;
        }

        float moveSpeed = delta * mMoveSpeed;

        Ogre::Vector3 move = Ogre::Vector3::ZERO;

        if (mGoingForward)
        {
            move += forward * moveSpeed;
        }

        if (mGoingBack)
        {
            move -= forward * moveSpeed;
        }

        if (mGoingLeft)
        {
            move -= right * moveSpeed;
        }


        if (mGoingRight)
        {
            move += right * moveSpeed;
        }

        if (mGoingUp)
        {
            move += up * moveSpeed;
        }

        if (mGoingDown)
        {
            move -= up * moveSpeed;
        }

        eyePosition += move;
    }
  
    auto rotM = Ogre::Math::makeRotateMatrixXY(x, y);
    Ogre::Matrix4 viewMatrix;
    Ogre::Matrix4 transM;
    if (mCameraType == Ogre::CameraMoveType_FirstPerson)
    {
        transM = Ogre::Math::makeTranslateMatrix(-eyePosition);
        viewMatrix = rotM * transM;
    }
    else
    {
        auto view = mCamera->getViewMatrix();
        /*Ogre::Vector3 forward = view.getForward();

        if (Ogre::Math::isRightHanded())
        {
            forward = Ogre::Vector3(0, 0, 1);
        }

        Real value = mRelativePosition.dotProduct(forward);
        if (value < 0.0f)
        {
            transM = Ogre::Math::makeTranslateMatrix(-eyePosition);
        }
        else
        {
            transM = Ogre::Math::makeTranslateMatrix(eyePosition);
        }*/
        transM = Ogre::Math::makeTranslateMatrix(-eyePosition);
        viewMatrix = transM * rotM;
    }
    Ogre::Vector3 pos = viewMatrix.getTrans();
    mCamera->updateViewMatrix(viewMatrix);
    mCamera->updatePosition(eyePosition);

    auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
    if (ogreConfig.width != mCameraInfo.width ||
        ogreConfig.height != ogreConfig.height)
    {
        mCameraInfo.width = ogreConfig.width;
        mCameraInfo.height = ogreConfig.height;
        updateProjectMatrix();
    }

    return true;
}

bool GameCamera::changed()
{
    return mChanged;
}
void GameCamera::updateChanged(bool change)
{
    mChanged = change;
}

Ogre::String GameCamera::getCameraString()
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "x:%d,y:%d,yaw:%f,pitch:%f",
        mMousePickX, mMousePickY, mYaw, mPitch);
    return Ogre::String(buffer);
}

Ogre::Vector3 GameCamera::createAnglesYPR(const Ogre::Quaternion& q)
{
    Ogre::Matrix3 m;
    q.ToRotationMatrix(m);

    float l = Ogre::Vector3(m[0][1], m[1][1], 0.0f).length();
    if (l > 0.0001)
    {
        return Ogre::Vector3(atan2f(-m[0][1] / l, m[1][1] / l), atan2f(m[2][1], l), atan2f(-m[2][0] / l, m[2][2] / l));
    }
    else
    {
        return Ogre::Vector3(0, atan2f(m[2][1], l), 0);
    }

}

template<typename T>
void sincos(T angle, T* pSin, T* pCos)
{
    *pSin = sin(angle); *pCos = cos(angle);
}
Ogre::Quaternion GameCamera::createOrientationYPR(const Ogre::Vector3& ypr)
{
    f32 sz, cz;
    sincos(ypr.x, &sz, &cz);            //!< Zaxis = YAW.
    f32 sx, cx;
    sincos(ypr.y, &sx, &cx);            //!< Xaxis = PITCH.
    f32 sy, cy;
    sincos(ypr.z, &sy, &cy);            //!< Yaxis = ROLL.
    Ogre::Matrix3 c;
    c[0][0] = cy * cz - sy * sz * sx;
    c[0][1] = -sz * cx;
    c[0][2] = sy * cz + cy * sz * sx;
    c[1][0] = cy * sz + sy * sx * cz;
    c[1][1] = cz * cx;
    c[1][2] = sy * sz - cy * sx * cz;
    c[2][0] = -sy * cx;
    c[2][1] = sx;
    c[2][2] = cy * cx;
    return c;
}

void GameCamera::updateCameraInfo(const CameraInfo& cameraInfo)
{
    bool change = false;
    if (cameraInfo.width != mCameraInfo.width || 
        cameraInfo.height != mCameraInfo.height)
        {
            change = true;
        }
    mCameraInfo = cameraInfo;

    if (change)
    {
        updateProjectMatrix();
    }   
}

void GameCamera::updateProjectMatrix()
{
    Ogre::Matrix4 m;
    if (mCameraInfo.reverseDepth)
    {
        float aspectInverse = mCameraInfo.height / (float)mCameraInfo.width;
        m = Ogre::Math::makePerspectiveMatrixReverseZ(
            mCameraInfo.fovRadians, aspectInverse, mCameraInfo.nearClip, mCameraInfo.farClip);
    }
    else
    {
        float aspect = mCameraInfo.width / (float)mCameraInfo.height;
        m = Ogre::Math::makePerspectiveMatrix(
            mCameraInfo.fovRadians, aspect, mCameraInfo.nearClip, mCameraInfo.farClip);
    }
    mCamera->updateProjectMatrix(m);
}

void GameCamera::updateCascades(const Ogre::Vector3& lightDirection)
{
    float cascadeSplits[SHADOW_MAP_CASCADE_COUNT];

    float nearClip = mCameraInfo.nearClip;
    float farClip = mCameraInfo.farClip;
    float clipRange = farClip - nearClip;

    float minZ = nearClip;
    float maxZ = nearClip + clipRange;

    float range = maxZ - minZ;
    float ratio = maxZ / minZ;

    float cascadeSplitLambda = 0.95f;
    // Calculate split depths based on view camera frustum
    // Based on method presented in https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch10.html
    for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++) {
        float p = (i + 1) / static_cast<float>(SHADOW_MAP_CASCADE_COUNT);
        float log = minZ * std::pow(ratio, p);
        float uniform = minZ + range * p;
        float d = cascadeSplitLambda * (log - uniform) + uniform;
        cascadeSplits[i] = (d - nearClip) / clipRange;
    }

    // Calculate orthographic projection matrix for each cascade
    float lastSplitDist = 0.0;
    for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++) {
        float splitDist = cascadeSplits[i];

        Ogre::Vector3 frustumCorners[8] = {
            Ogre::Vector3(-1.0f,  1.0f, 0.0f),
            Ogre::Vector3(1.0f,  1.0f, 0.0f),
            Ogre::Vector3(1.0f, -1.0f, 0.0f),
            Ogre::Vector3(-1.0f, -1.0f, 0.0f),
            Ogre::Vector3(-1.0f,  1.0f,  1.0f),
            Ogre::Vector3(1.0f,  1.0f,  1.0f),
            Ogre::Vector3(1.0f, -1.0f,  1.0f),
            Ogre::Vector3(-1.0f, -1.0f,  1.0f),
        };
        const Ogre::Matrix4& proj = mCamera->getProjectMatrix();
        const Ogre::Matrix4& view = mCamera->getViewMatrix();
        // Project frustum corners into world space
        Ogre::Matrix4 invCam = (proj * view).inverse();
        for (uint32_t j = 0; j < 8; j++) {
            Ogre::Vector4 invCorner = invCam * Ogre::Vector4(frustumCorners[j]);
            invCorner = invCorner / invCorner.w;
            frustumCorners[j] = Ogre::Vector3(invCorner.ptr());
        }

        for (uint32_t j = 0; j < 4; j++) {
            Ogre::Vector3 dist = frustumCorners[j + 4] - frustumCorners[j];
            frustumCorners[j + 4] = frustumCorners[j] + (dist * splitDist);
            frustumCorners[j] = frustumCorners[j] + (dist * lastSplitDist);
        }

        // Get frustum center
        Ogre::Vector3 frustumCenter = Ogre::Vector3::ZERO;
        for (uint32_t j = 0; j < 8; j++) {
            frustumCenter += frustumCorners[j];
        }
        frustumCenter /= 8.0f;

        float radius = 0.0f;
        for (uint32_t j = 0; j < 8; j++) {
            float distance = (frustumCorners[j] - frustumCenter).length();
            radius = std::max(radius, distance);
        }
        radius = std::ceil(radius * 16.0f) / 16.0f;

        Ogre::Vector3 maxExtents = Ogre::Vector3(radius);
        Ogre::Vector3 minExtents = -maxExtents;

        Ogre::Vector3 lightDir = lightDirection;
        lightDir.normalise();
        cascades[i].lightViewMatrix = Ogre::Math::makeLookAt(
            frustumCenter - lightDir * -minExtents.z, frustumCenter, Ogre::Vector3::UNIT_Y);
        cascades[i].lightOrthoMatrix = Ogre::Math::makeOrthoRH(
            minExtents.x, maxExtents.x, minExtents.y, maxExtents.y, 0.0f, maxExtents.z - minExtents.z);

        // Store split distance and matrix in cascade
        cascades[i].splitDepth = (nearClip + splitDist * clipRange) * -1.0f;
        cascades[i].lightViewProjMatrix = cascades[i].lightOrthoMatrix * cascades[i].lightViewMatrix;
        lastSplitDist = cascadeSplits[i];
    }
}