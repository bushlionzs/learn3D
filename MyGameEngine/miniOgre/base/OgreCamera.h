#pragma once
#include "camera_impl.h"
#include "OgreMoveObject.h"
#include "OgreCommon.h"
#include "OgreFrustum.h"
#include "OgreBase.h"
namespace Ogre {
    class Camera: public MoveObject, public ICamera
    {
    public:
        // constructor with vectors
        Camera(const String&name, SceneManager* sceneMgr);
        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        const Ogre::Matrix4& getViewMatrix() const;
        const Ogre::Matrix4& getProjectMatrix() const;
        const Ogre::Matrix4& getProjectionMatrixWithRSDepth(void) const;
        const Ogre::Vector3& getDerivedPosition() const;
        const Ogre::Quaternion& getDerivedOrientation() const;

        Ogre::Vector3 getDerivedDirection(void) const;
        Ogre::Vector3 getDerivedUp(void) const;
        Ogre::Vector3 getDerivedRight(void) const;

        bool isVisible(const Ogre::Sphere& bound) const;
        bool isVisible(const AxisAlignedBox& bound) const;
        bool isVisible(const Ogre::Vector3& position) const;

        Ogre::SortMode getSortMode() const { return mSortMode; }


        Viewport* getViewport(void) const;
        /** Notifies this camera that a viewport is using it.*/
        void _notifyViewport(Viewport* viewport);

        bool getAutoAspectRatio(void) const;

        unsigned int _getNumRenderedFaces(void) const;

        unsigned int _getNumRenderedBatches(void) const;

        void _renderScene(Viewport* vp);

        virtual const AxisAlignedBox& getBoundingBox(void) const;

        Real getAspectRatio();
        void setAspectRatio(float aa);
        

        void needUpdate();

        Ray getCameraToViewportRay(Real screenX, Real screenY) const;
        void getCameraToViewportRay(Real screenx, Real screeny, Ray* outRay) const;

        void setNearClipDistance(float znear);
        void setFarClipDistance(float zfar);
        void setPolygonMode(PolygonMode sd);
        void setProjectionType(Ogre::ProjectionType pt);
        void setOrthoWindow(float w, float h);

        bool isReflected();
        virtual void enableReflection(const Plane& p);
        virtual void disableReflection(void);
        virtual void enableCustomNearClipPlane(const Plane& plane);
        virtual void disableCustomNearClipPlane(void);
    private:
        CameraImpl* mCameraImpl;
        std::vector<Renderable*> mRenderableList;
        

        Ogre::SortMode mSortMode = Ogre::SM_DISTANCE;

        Viewport* mViewport = nullptr; 

        SceneManager* mCreator = nullptr;

        mutable bool mNeedUpdate = true;
    };
}
