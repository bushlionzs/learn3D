#include "OgreHeader.h"
#include <cmath>
#include "game_camera.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNOde.h"

GameCamera::GameCamera(Camera* camera, SceneManager* sceneMgr)
{
    mCamera = camera;
    mSceneMgr = sceneMgr;

    mCameraType = CameraMoveType_FirstPerson;
}

const Ogre::Vector3 GameCamera::getPosition()
{
    return position;
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

void GameCamera::updateCamera(
    const Ogre::Vector3& camPosition, 
    const Ogre::Vector3& camRotate)
{
    position = camPosition;
    rotation = camRotate;
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
    mMouseDeltaX = _absx - mMousePickX;
    mMouseDeltaY = _absy - mMousePickY;

    float pitch = 0.0f;

    bool need = false;

    float yaw = 0.0f;
    if (mMouseDeltaX != 0)
    {
        mYaw -= mMouseDeltaX * 0.15f;
        need = true;

        yaw = mMouseDeltaX * 0.15f;
    }


    if (mMouseDeltaY != 0)
    {
        mPitch -= mMouseDeltaY * 0.15f;
        pitch = mMouseDeltaY * 0.15f;
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
    if (mGoingForward || mGoingBack || mGoingLeft || mGoingRight || mGoingUp || mGoingDown)
    {
        Ogre::Vector3 camFront;

        float x = Ogre::Radian(Ogre::Degree(rotation.x)).valueRadians();
        float y = Ogre::Radian(Ogre::Degree(rotation.y)).valueRadians();
        camFront.x = -cos(x) * sin(y);
        camFront.y = sin(x);
        camFront.z = cos(x) * cos(y);
        camFront.normalise();

        float moveSpeed = delta * mMoveSpeed;

        if (mGoingForward)
        {
            position += camFront * moveSpeed;
        }

        if (mGoingBack)
        {
            position -= camFront * moveSpeed;
        }

        if (mGoingLeft)
        {
            auto left = camFront.crossProduct(Ogre::Vector3(0.0f, 1.0f, 0.0f));
            position -= left * moveSpeed;
        }


        if (mGoingRight)
        {
            auto left = camFront.crossProduct(Ogre::Vector3(0.0f, 1.0f, 0.0f));

            position += left * moveSpeed;
        }

        if (mGoingUp)
        {
            position += Ogre::Vector3(0.0f, 1.0f, 0.0f) * moveSpeed;
        }

        if (mGoingDown)
        {
            position -= Ogre::Vector3(0.0f, 1.0f, 0.0f) * moveSpeed;
        }
    }
    Ogre::Matrix4 rotM = Ogre::Matrix4::IDENTITY;

    Ogre::Matrix4 transM;

    rotM = Ogre::Math::makeRotateMatrix(rotM, rotation.x, Ogre::Vector3(1.0f, 0.0f, 0.0f));
    rotM = Ogre::Math::makeRotateMatrix(rotM, rotation.y, Ogre::Vector3(0.0f, 1.0f, 0.0f));

    Ogre::Vector3 translation = position;

    transM = Ogre::Math::makeTranslateMatrix(translation);

    Ogre::Matrix4 m = rotM * transM;

    mCamera->updateCamera(m);

    return true;
}

Ogre::String GameCamera::getCameraString()
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "x:%d,y:%d,yaw:%f,pitch:%f", 
        mMousePickX, mMousePickY, mYaw, mPitch);
    return Ogre::String(buffer);
}
