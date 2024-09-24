#pragma once
#include "OgreMoveObject.h"
#include "OgreColourValue.h"
#include "OgreBase.h"
namespace Ogre {
    enum LightType
    {
        LightType_Direction = 0
    };
    class Light: public MoveObject, public ICamera
    {
    public:
        void setDiffuseColour(float red, float green, float blue);
        void setDiffuseColour(const ColourValue& colour);

        const ColourValue& getDiffuseColour(void) const;

        void setSpecularColour(float red, float green, float blue);
        void setSpecularColour(const ColourValue& colour);

        void setAttenuation(
            float range, 
            float constant, 
            float linear, 
            float quadratic);

        virtual const Ogre::Matrix4& getViewMatrix() const;
        virtual const Ogre::Matrix4& getProjectMatrix() const;
        virtual const Ogre::Vector3& getDerivedPosition() const;
        virtual bool isVisible(const AxisAlignedBox& bound) const;
        const AxisAlignedBox& getBoundingBox(void) const;
        virtual const CameraType getCameraType();

        void setLightType(LightType type, uint32_t lightNumber);
        LightType getLightType();
        uint32_t getLightNumber();
        Ogre::Vector3 getLightDirection();

    public:
        Ogre::Vector3 Strength = { 0.5f, 0.5f, 0.5f };
        float FalloffStart = 1.0f;                          // point/spot light only
        Ogre::Vector3 Direction = { 0.0f, -1.0f, 0.0f };// directional/spot light only
        float FalloffEnd = 10.0f;                           // point/spot light only
        Ogre::Vector3 Position = { 0.0f, 0.0f, 0.0f };  // point/spot light only
        float SpotPower = 64.0f;                            // spot light only

        uint32_t mLightNumber = 0;
        LightType mLightType = LightType_Direction;
        //for shadow only
        mutable Ogre::Vector3 mPosition;
        mutable Ogre::Matrix4 mViewMatrix;
        mutable Ogre::Matrix4 mProjMatrix;
    };
}