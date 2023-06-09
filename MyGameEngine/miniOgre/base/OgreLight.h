#pragma once
#include "OgreMoveObject.h"
#include "OgreColourValue.h"
namespace Ogre {

    class Light: public MoveObject
    {
    public:
        void setDiffuseColour(float red, float green, float blue);
        void setDiffuseColour(const ColourValue& colour);

        const ColourValue& getDiffuseColour(void) const;

        void setSpecularColour(float red, float green, float blue);
        void setSpecularColour(const ColourValue& colour);

        void setAttenuation(float range, float constant, float linear, float quadratic);
    public:
        Ogre::Vector3 Strength = { 0.5f, 0.5f, 0.5f };
        float FalloffStart = 1.0f;                          // point/spot light only
        Ogre::Vector3 Direction = { 0.0f, -1.0f, 0.0f };// directional/spot light only
        float FalloffEnd = 10.0f;                           // point/spot light only
        Ogre::Vector3 Position = { 0.0f, 0.0f, 0.0f };  // point/spot light only
        float SpotPower = 64.0f;                            // spot light only
    };
}