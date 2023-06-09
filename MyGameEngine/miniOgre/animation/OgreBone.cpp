#include "OgreHeader.h"
#include "OgreBone.h"

namespace Ogre {

    Bone::Bone(const std::string& name, uint32_t boneId)
        :Node(name, nullptr), mBoneId(boneId)
    {

    }

    Bone::Bone(Bone& other)
        : Node(mName, nullptr)
    {
        *this = other;
    }

    Bone::~Bone()
    {

    }

    void Bone::updateParent(Bone* parent)
    {
        if (parent)
        {
            assert(mParent == nullptr);
        }
        mParent = parent;
    }

    Bone* Bone::getParent()
    {
        return (Bone*)mParent;
    }

    uint32_t Bone::getBoneId()
    {
        return mBoneId;
    }

    void Bone::setBindingPose(void)
    {
        setInitialState();

        // Save inverse derived position/scale/orientation, used for calculate offset transform later
        mBindDerivedInversePosition = -_getDerivedPosition();
        mBindDerivedInverseScale = Ogre::Vector3(1.0f, 1.0f, 1.0f) / _getDerivedScale();
        mBindDerivedInverseOrientation = _getDerivedOrientation().Inverse();
    }


    void Bone::setInverseBindMatrix(const Ogre::Matrix4& m)
    {
        mInverseMatrix = m;
    }


    const Ogre::Matrix4& Bone::getInverseBindMatrix() const
    {
        return mInverseMatrix;
    }

    void Bone::reset(void)
    {
        resetToInitialState();
    }

    void Bone::_getOffsetTransform(Ogre::Matrix4& m)
    {
        Ogre::Vector3 locScale = _getDerivedScale() * mBindDerivedInverseScale;

        // Combine orientation with binding pose inverse orientation
        Ogre::Quaternion locRotate = _getDerivedOrientation() * mBindDerivedInverseOrientation;

        // Combine position with binding pose inverse position,
        // Note that translation is relative to scale & rotation,
        // so first reverse transform original derived position to
        // binding pose bone space, and then transform to current
        // derived bone space.

        Ogre::Vector3 DerivedPosition = _getDerivedPosition();
        Ogre::Vector3 locTranslate = DerivedPosition + locRotate * (locScale * mBindDerivedInversePosition);

        m.makeTransform(locTranslate, locScale, locRotate);
    }
}




