#pragma
#include "InputManager.h"

class GameCamera: public InputListener
{
private:
    Camera* mCamera = nullptr;
    SceneManager* mSceneMgr = nullptr;

    Real  mYaw = 0.0f;
    Real  mPitch = 0.0f;

    Real  mDistance = 1000.0f;

    int mLastZ = 0;
    Ogre::Vector3 mTargetPosition;
    Ogre::Vector3 mEyePosition;
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

    HWND m_hWnd = 0;


    bool mEditMode = true;

    Ogre::Vector3 mUp = Ogre::Vector3::UNIT_Y;
    Ogre::Vector3 mCameraRelPosition;

    Real mSpeed = 500.0f;

public:
    GameCamera(Camera* camera, SceneManager* sceneMgr, HWND hwnd);

    String getCameraString();
    Camera* getCamera()
    {
        return mCamera;
    }

    const Ogre::Vector3 getPosition();

    void setDistance(float distance);
    void setHeight(float height);

    void setMoveSpeed(Real speed);


    virtual void injectMouseMove(int _absx, int _absy, int _absz);
    virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
    virtual void injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id);
    virtual void injectKeyPress(KeyCode _key, uint32_t _text);
    virtual void injectKeyRelease(KeyCode _key);

    virtual void injectMouseWheel(int _absz);
    virtual bool update(float delta);
};