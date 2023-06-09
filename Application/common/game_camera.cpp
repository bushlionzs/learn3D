#include "OgreHeader.h"
#include "game_camera.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNOde.h"
#include "engine_manager.h"

GameCamera::GameCamera(Camera* camera, SceneManager* sceneMgr, HWND hwnd)
{
    mCameraRelPosition = Ogre::Vector3::ZERO;
    mCamera = camera;
    mSceneMgr = sceneMgr;

    m_hWnd = hwnd;

    mCameraNode = mSceneMgr->getRoot()->createChildSceneNode(std::string("playerCamera"));
    mCameraSubNode = mCameraNode->createChildSceneNode(std::string("CameraSubNode"));

    mCameraSubNode->attachObject(mCamera);
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

    return;
}
void GameCamera::injectMouseMove(int _absx, int _absy, int _absz)
{
    if (!mPickup)
        return;
    mMouseDeltaX = _absx - mMousePickX;
    mMouseDeltaY = _absy - mMousePickY;

    if (mMouseDeltaX != 0)
    {
        mYaw += mMouseDeltaX * 0.15f;
    }


    if (mMouseDeltaY != 0)
    {
        mPitch += mMouseDeltaY * 0.15f;
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
            sidesway = -speed * delta;
        }

        if (mGoingLeft)
        {
            sidesway = speed * delta;
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

        
        Ogre::Vector3 target = EngineManager::getSingletonPtr()->getMyPosition();
        Ogre::Vector3 position = getPosition();
        position.y = target.y;
        Ogre::Vector3 aheadVector = (target - position);
        aheadVector.normalise();
        Ogre::Vector3 leftVector = mUp.crossProduct(aheadVector);


        target += aheadVector * goahead;
        target += leftVector * sidesway;
        target += mUp * height;

        EngineManager::getSingletonPtr()->setMyPosition(target);
    }
    
    {
        mCameraNode->resetOrientation();
        mCameraSubNode->resetOrientation();
        {
            Ogre::Vector3 playerPos = EngineManager::getSingletonPtr()->getMyPosition();
            //playerPos = Vector3(6550, -568.960022, -5300.00000);
            mCameraNode->setPosition(playerPos);
            mCameraSubNode->setPosition(mCameraRelPosition);

            mCameraNode->yaw(Ogre::Degree(mYaw));

            mCameraNode->pitch(Ogre::Degree(mPitch));

        }
    }

    mCamera->needUpdate();
    

    return true;
}

Ogre::String GameCamera::getCameraString()
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "x:%d,y:%d", mMousePickX, mMousePickY);
    return Ogre::String(buffer);
}
