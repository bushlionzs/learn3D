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

    mWorldMatrix = Ogre::Matrix4::IDENTITY;
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

    mLookOrientation = createOrientationYPR(rotation);
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
        auto forward = -rot.getForward();

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
        transM = Ogre::Math::makeTranslateMatrix(eyePosition);
        viewMatrix = transM * rotM;
    }
    
    mCamera->updateViewMatrix(mWorldMatrix * viewMatrix);
    mCamera->updatePosition(eyePosition);
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
