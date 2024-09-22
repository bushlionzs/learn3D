#include "OgreHeader.h"
#include "game_camera.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNOde.h"

GameCamera::GameCamera(Camera* camera, SceneManager* sceneMgr)
{
    mCameraRelPosition = Ogre::Vector3::ZERO;
    mCamera = camera;
    mSceneMgr = sceneMgr;


    mCameraNode = mSceneMgr->getRoot()->createChildSceneNode(std::string("playerCamera"));
    mCameraSubNode = mCameraNode->createChildSceneNode(std::string("CameraSubNode"));

    mCameraSubNode->attachObject(mCamera);

    mCameraType = CameraMoveType_FirstPerson;
}

const Ogre::Vector3 GameCamera::getPosition()
{
    return mCameraSubNode->_getDerivedPosition();
}

void GameCamera::setDistance(float distance)
{
    mDistance = distance;
    
    mCameraRelPosition.z = distance;
}

void GameCamera::setHeight(float height)
{
    mCameraRelPosition.y = height;
}

void GameCamera::setMoveSpeed(Real speed)
{
    mSpeed = speed;
}

void GameCamera::updateCamera(const Ogre::Vector3& camPosition, const Ogre::Vector3& lookAtPosition)
{
    mCameraPosition = camPosition;
    mLookAtPosition = lookAtPosition;

    mCameraRelPosition = mCameraPosition - mLookAtPosition;
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

    float yaw = 0.0f;
    float pitch = 0.0f;

    bool need = false;
    if (mMouseDeltaX != 0)
    {
        mYaw -= mMouseDeltaX * 0.15f;
        yaw =  -mMouseDeltaX * 0.15f;
        need = true;
    }


    if (mMouseDeltaY != 0)
    {
        mPitch -= mMouseDeltaY * 0.15f;
        pitch = -mMouseDeltaY * 0.15f;
        need = true;
    }

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
    if (mEditMode)
    {
        float sidesway = 0.0f;
        float goahead = 0.0f;
        float height = 0.0f;
        float speed = mSpeed;

        if (mGoingRight)
        {
            sidesway = speed * delta;
        }

        if (mGoingLeft)
        {
            sidesway = -speed * delta;
        }


        if (mGoingForward)
        {
            goahead += delta * speed;
        }

        if (mGoingBack)
        {
            goahead -= delta * speed;
        }

        if (mGoingUp)
        {
            height += delta * speed;
        }

        if (mGoingDown)
        {
            height -= delta * speed;
        }


        Ogre::Vector3 target = mLookAtPosition;
        Ogre::Vector3 position = mCameraPosition;
        position.y = target.y;
        Ogre::Vector3 aheadVector = (target - position);
        aheadVector.normalise();
        Ogre::Vector3 leftVector = mUpVector.crossProduct(aheadVector);


        target += aheadVector * goahead;
        target += leftVector * sidesway;
        target += mUpVector * height;

        mLookAtPosition = target;
    }

    {
        mCameraNode->resetOrientation();
        mCameraSubNode->resetOrientation();
        {
            mCameraNode->setPosition(mLookAtPosition);
            mCameraSubNode->setPosition(mCameraRelPosition);
            mCameraNode->yaw(Ogre::Degree(mYaw));

            mCameraNode->pitch(Ogre::Degree(mPitch));

            mCameraPosition = mCameraSubNode->_getDerivedPosition();

            auto m2 = Ogre::Math::makeLookAtLH(mCameraPosition, mLookAtPosition, Ogre::Vector3::UNIT_Y);

            mCamera->updateCamera(m2);
        }
    }

    mCamera->needUpdate();
    

    return true;
}

Ogre::String GameCamera::getCameraString()
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "x:%d,y:%d,yaw:%f,pitch:%f", 
        mMousePickX, mMousePickY, mYaw, mPitch);
    return Ogre::String(buffer);
}
