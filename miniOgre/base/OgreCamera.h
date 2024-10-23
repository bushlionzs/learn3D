#pragma once
#include "camera_impl.h"
#include "OgreMoveObject.h"
#include "OgreCommon.h"

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
        virtual void setCameraCull(bool cull) override;

        Ogre::SortMode getSortMode() const { return mSortMode; }

        bool getAutoAspectRatio(void) const;

        virtual const AxisAlignedBox& getBoundingBox(void) const;

        float getNear();
        float getFar();

        Real getAspectRatio();
        void setAspectRatio(float aa);
        

        void needUpdate();
        void updatePosition(const Ogre::Vector3& position);
        void updateViewMatrix(const Ogre::Matrix4& m);
        void updateProjectMatrix(const Ogre::Matrix4& m);

        Ray getCameraToViewportRay(Real screenX, Real screenY) const;
        void getCameraToViewportRay(Real screenx, Real screeny, Ray* outRay) const;

        void setNearClipDistance(float znear);
        void setFarClipDistance(float zfar);
        void setPolygonMode(PolygonMode sd);
        void setProjectionType(Ogre::ProjectionType pt);
        virtual Ogre::ProjectionType getProjectionType() override
        {
            return mCameraImpl->getProjectionType();
        }
        void setOrthoWindow(float w, float h);

        bool isReflected();
        virtual void enableReflection(const Plane& p);
        virtual void disableReflection(void);
        virtual void enableCustomNearClipPlane(const Plane& plane);
        virtual void disableCustomNearClipPlane(void);
        virtual SceneManager* getCreator();
    private:
        CameraImpl* mCameraImpl;
        std::vector<Renderable*> mRenderableList;
        

        Ogre::SortMode mSortMode = Ogre::SM_DISTANCE;


        SceneManager* mCreator = nullptr;

        Ogre::Vector3 mPosition;
        mutable bool mNeedUpdate = true;

        bool mCull = true;
    };
}
