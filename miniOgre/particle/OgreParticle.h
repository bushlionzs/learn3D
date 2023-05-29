/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __Particle_H__
#define __Particle_H__
#include "OgreColourValue.h"

namespace Ogre {

    class ParticleSystem;

    /** Class representing a single particle instance. */

    class  ParticleVisualData
    {
    public:
        ParticleVisualData() {}
        virtual ~ParticleVisualData() {}

    };

    class  Particle
    {
    protected:
        ParticleSystem* mParentSystem;
        ParticleVisualData* mVisual;
    public:
        /// Type of particle
        enum ParticleType : uint8
        {
            Visual,
            Emitter
        };
        /// Does this particle have it's own dimensions?
        bool mOwnDimensions;
        /// Particle width
        float mWidth;
        /// Particle height
        float mHeight;
        /// Current rotation value
        Radian mRotation;
        // Note the intentional public access to internal variables
        // Accessing via get/set would be too costly for 000's of particles
        /// World position
        Vector3 mPosition;
        /// Direction (and speed) 
        Vector3 mDirection;

        Vector3 mXAxis;
        Vector3 mYAxis;
        bool mNeedRecalAxis;
        /// Current colour
        ColourValue mColour;
        /// Time to live, number of seconds left of particles natural life
        float mTimeToLive;
        /// Total Time to live, number of seconds of particles natural life
        float mTotalTimeToLive;
        /// Speed of rotation in radians/sec
        Radian mRotationSpeed;
        /// Determines the type of particle.
        ParticleType mParticleType;
        /// Index into the array of texture coordinates @see BillboardSet::setTextureStacksAndSlices()
        uint8 mTexcoordIndex;
        uint8 mRandomTexcoordOffset;

        

        Particle();

        /** Sets the width and height for this particle.
        */

        ParticleVisualData* getVisualData()
        {
            return mVisual;
        }

        void setDimensions(float width, float height);

        /** Retrieves the particle's personal width, if hasOwnDimensions is true. */
        float getOwnWidth(void) const { return mWidth; }

        /** Retrieves the particle's personal width, if hasOwnDimensions is true. */
        float getOwnHeight(void) const { return mHeight; }
        
        /** Sets the current rotation */
        void setRotation(const Radian& rad);

        const Radian& getRotation(void) const { return mRotation; }

        void resetDimensions(void);
        void _notifyOwner(ParticleSystem* owner);
    };
    /** @} */
    /** @} */
}

#endif

