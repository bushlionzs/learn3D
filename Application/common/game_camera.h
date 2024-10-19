#pragma once
#include "InputManager.h"
#include "engine_struct.h"

class GameCamera: public InputListener
{
private:
    Ogre::Camera* mCamera = nullptr;
    SceneManager* mSceneMgr = nullptr;

    Real  mYaw = 0.0f;
    Real  mPitch = 0.0f;

    Real  mDistance = 1000.0f;

    int mLastZ = 0;
    
    bool mGoingForward = false;
    bool mGoingBack = false;
    bool mGoingLeft = false;
    bool mGoingRight = false;
    bool mGoingUp = false;
    bool mGoingDown = false;
    bool mFastMove = false;
    bool mPickup = false;

    bool mDistanceMove = false;

    SceneNode* mCameraNode = nullptr;
    SceneNode* mCameraSubNode = nullptr;

    int32_t mMousePickX = 0;
    int32_t mMousePickY = 0;

    int32_t mMouseDeltaX = 0;
    int32_t mMouseDeltaY = 0;


    bool mEditMode = true;

    Ogre::Vector3 mUpVector = Ogre::Vector3::UNIT_Y;
    Ogre::Vector3 mLeftVector = -Ogre::Vector3::UNIT_X;

    Ogre::Vector3 mLookAtPosition;
    Ogre::Vector3 mCameraPosition;


    Ogre::Vector3 mCameraRelPosition;

    Real mSpeed = 500.0f;

    CameraMoveType mCameraType;


public:
    GameCamera(Ogre::Camera* camera, SceneManager* sceneMgr);

    Ogre::String getCameraString();
    Ogre::Camera* getCamera()
    {
        return mCamera;
    }

    const Ogre::Vector3 getPosition();

    void setDistance(float distance);
    void setHeight(float height);

    void setMoveSpeed(Real speed);


    void updateCamera(const Ogre::Vector3& camPosition, const Ogre::Vector3& lookAtPosition);


    virtual void injectMouseMove(int _absx, int _absy, int _absz);
    virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
    virtual void injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id);
    virtual void injectKeyPress(KeyCode _key, uint32_t _text);
    virtual void injectKeyRelease(KeyCode _key);

    virtual void injectMouseWheel(int _absz);
    virtual bool update(float delta);
};