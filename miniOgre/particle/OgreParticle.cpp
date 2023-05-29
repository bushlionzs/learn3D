#include "OgreHeader.h"
#include "OgreParticle.h"
#include "OgreParticleSystem.h"

namespace Ogre
{

    Particle::Particle()
        : mWidth(0), mHeight(0), mOwnDimensions(false),
        mRotation(0), mPosition(Vector3::ZERO), mDirection(Vector3::ZERO),
        mXAxis(Vector3::ZERO), mYAxis(Vector3::ZERO), mNeedRecalAxis(false),
        mColour(0xFFFFFFFF), mTimeToLive(10), mTotalTimeToLive(10),
        mRotationSpeed(0), mParticleType(Visual), mTexcoordIndex(0), mRandomTexcoordOffset(0)
    {
    }
    void Particle::setDimensions(float width, float height)
    {
        mWidth = width;
        mHeight = height;
        mOwnDimensions = true;
        mParentSystem->_notifyParticleResized();
    }

    void Particle::setRotation(const Radian& rad)
    {
        mRotation = rad;
        mParentSystem->_notifyParticleRotated();
    }

    void Particle::_notifyOwner(ParticleSystem* owner)
    {
        mParentSystem = owner;
    }

    void Particle::resetDimensions(void)
    {
        mOwnDimensions = false;
    }

}

