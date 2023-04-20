#include "OgreHeader.h"
#include "OgreNode.h"
#include "OgreMatrix4.h"
#include "OgreCamera.h"

SVertexElement::SVertexElement()
{
}

SVertexElement::SVertexElement(
    float px, float py, float pz,
    float nx, float ny, float nz,
    float tx, float ty, float tz,
    float u, float v
)
{
    mPosition.x = px;
    mPosition.y = py;
    mPosition.z = pz;
    mNormal.x = nx;
    mNormal.y = ny;
    mNormal.z = nz;
    mTangent.x = tx;
    mTangent.y = ty;
    mTangent.z = tz;
    mUV.x = u;
    mUV.y = v;

}

SVertexElement::~SVertexElement()
{

}

namespace Ogre {

    Node::Node(const std::string& name, Node* parent)
        :
        mName(name),
        mParent(parent),
        mOrientation(1.0f, 0.0f, 0.0f, 0.0f)
    {
        mModel = Ogre::Matrix4::IDENTITY;
        mPosition = Ogre::Vector3::ZERO;
        mScale = Ogre::Vector3::UNIT_SCALE;
    }

    Node::~Node()
    {

    }

    Ogre::Matrix4  buildTransform(Ogre::Vector3& scale, Ogre::Vector3& trans, Ogre::Quaternion& orientation)
    {
        assert(false);
        Ogre::Matrix4 m2;
  
        return m2;
    }
    const Ogre::Matrix4& Node::getWorldModelMatrix()
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();

            
        }

        if (mNeedWorldMatrix)
        {
            mCacheMatrix.makeTransform(mDerivedPosition, mDerivedScale, mDerivedOrientation);
            //mWorldModel = mCacheMatrix.transpose();
            mWorldModel = mCacheMatrix;
            mNeedWorldMatrix = false;
        }
        

        return mWorldModel;
    }

    const Ogre::Matrix4& Node::getLocalModelMatrix()
    {
        return mModel;
    }

    void Node::setLocalModelMatrix(const Ogre::Matrix4& matrix)
    {
        mModel = matrix;
    }

    void Node::addReflect(Node* node)
    {
        mReflect = node;
    }

    Node* Node::getReflect()
    {
        return mReflect;
    }

    void Node::setTransparent(bool transparent)
    {
        mTransparent = transparent;
    }

    bool Node::isTransparent()
    {
        return mTransparent;
    }

    void Node::setMirror(bool mirror)
    {
        mMirror = mirror;
    }

    bool Node::isMirror()
    {
        return mMirror;
    }

    void Node::setDynamicReflect(bool enable)
    {
        mDynamicReflect = enable;
    }

    bool Node::isDynamicReflect()
    {
        return mDynamicReflect;
    }

    void Node::setVisible(bool visible)
    {
        mVisible = visible;
    }

    bool Node::isVisible()
    {
        return mVisible;
    }


    void Node::update(float timeSinceLastFrame)
    {

    }


    const Ogre::Matrix4& Node::_getFullTransform(void) const
    {
        mCachedTransform.makeTransform(
            _getDerivedPosition(),
            _getDerivedScale(),
            _getDerivedOrientation());
        return mCachedTransform;
    }


    void Node::needUpdate(bool forceParentUpdate)
    {
        mNeedParentUpdate = true;
    }

    void Node::updatechildren()
    {
        for (auto child : mChildren)
        {
            child->needUpdate(true);
            child->updatechildren();
        }
    }

    void Node::setPosition(float x, float y, float z)
    {
        mPosition.x = x;
        mPosition.y = y;
        mPosition.z = z;
        mNeedParentUpdate = true;
    }

    void Node::setPosition(const Ogre::Vector3& position)
    {
        mPosition.x = position.x;
        mPosition.y = position.y;
        mPosition.z = position.z;

        mNeedParentUpdate = true;
    }

    void Node::setOrientation(float w, float x, float y, float z)
    {
        mOrientation.w = w;
        mOrientation.x = x;
        mOrientation.y = y;
        mOrientation.z = z;
        mNeedParentUpdate = true;
    }

    void Node::setOrientation(const Ogre::Quaternion& q)
    {
        mOrientation.x = q.x;
        mOrientation.y = q.y;
        mOrientation.z = q.z;
        mOrientation.w = q.w;
        mNeedParentUpdate = true;
    }

    void Node::setScale(float x, float y, float z)
    {
        mScale.x = x;
        mScale.y = y;
        mScale.z = z;
        mNeedParentUpdate = true;
    }
    void Node::setScale(const Ogre::Vector3& scale)
    {
        mScale.x = scale.x;
        mScale.y = scale.y;
        mScale.z = scale.z;
        mNeedParentUpdate = true;
    }

    const Ogre::Vector3& Node::getScale() const
    {
        return mScale;
    }

    const Ogre::Vector3& Node::getPosition() const
    {
        return mPosition;
    }

    const Ogre::Quaternion& Node::getQuaternion() const
    {
        return mOrientation;
    }

    const Ogre::Quaternion& Node::getOrientation() const
    {
        return mOrientation;
    }

    void Node::rotate(const Ogre::Quaternion& q, TransformSpace relativeTo)
    {
        switch (relativeTo)
        {
        case TS_PARENT:
            // Rotations are normally relative to local axes, transform up
            mOrientation = q * mOrientation;
            break;
        case TS_WORLD:
            // Rotations are normally relative to local axes, transform up
            mOrientation = mOrientation * _getDerivedOrientation().Inverse()
                * q * _getDerivedOrientation();
            break;
        case TS_LOCAL:
            // Note the order of the mult, i.e. q comes after
            mOrientation = mOrientation * q;
            break;
        }

        // Normalise quaternion to avoid drift
        mOrientation.normalise();

        needUpdate();
    }

    void Node::scale(const Ogre::Vector3& inScale)
    {
        mScale = mScale * inScale;
        needUpdate();
    }

    void Node::translate(const Ogre::Vector3& d, TransformSpace relativeTo)
    {
        switch (relativeTo)
        {
        case TS_LOCAL:
            // position is relative to parent so transform downwards
            mPosition += mOrientation * d;
            break;
        case TS_WORLD:
            assert(false);
            break;
        case TS_PARENT:
            mPosition += d;
            break;
        }
        needUpdate();
    }


    void Node::yaw(const Ogre::Radian& angle, TransformSpace relativeTo)
    {
        rotate(Ogre::Quaternion(angle, Ogre::Vector3::UNIT_Y), relativeTo);
    }

    void Node::pitch(const Ogre::Radian& angle, TransformSpace relativeTo)
    {
        rotate(Ogre::Quaternion(angle, Ogre::Vector3::UNIT_X), relativeTo);
    }

    const Ogre::Quaternion& Node::_getDerivedOrientation(void) const
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }
        return mDerivedOrientation;
    }

    //-----------------------------------------------------------------------
    const Ogre::Vector3& Node::_getDerivedPosition(void) const
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }

        
        return mDerivedPosition;
    }
    //-----------------------------------------------------------------------
    const Ogre::Vector3& Node::_getDerivedScale(void) const
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }
        return mDerivedScale;
    }

    void Node::_updateFromParent() const
    {
        if (mParent)
        {
            // Update orientation
            const Ogre::Quaternion& parentOrientation = mParent->_getDerivedOrientation();
            if (mInheritOrientation)
            {
                // Combine orientation with that of parent
                mDerivedOrientation = parentOrientation * mOrientation;
            }
            else
            {
                // No inheritance
                mDerivedOrientation = mOrientation;
            }

            // Update scale
            const Ogre::Vector3& parentScale = mParent->_getDerivedScale();
            if (mInheritScale)
            {
                // Scale own position by parent scale, NB just combine
                // as equivalent axes, no shearing
                mDerivedScale = parentScale * mScale;
            }
            else
            {
                // No inheritance
                mDerivedScale = mScale;
            }

            // Change position vector based on parent's orientation & scale
            mDerivedPosition = parentOrientation * (parentScale * mPosition);

            // Add altered position vector to parents
            mDerivedPosition += mParent->_getDerivedPosition();
        }
        else
        {
            // Root node, no parent
            mDerivedOrientation = mOrientation;
            mDerivedPosition = mPosition;
            mDerivedScale = mScale;
        }

        mNeedParentUpdate = false;
        mNeedWorldMatrix = true;
    }

    void Node::setInitialState(void)
    {
        mInitialPosition = mPosition;
        mInitialOrientation = mOrientation;
        mInitialScale = mScale;
    }
    //-----------------------------------------------------------------------
    void Node::resetToInitialState(void)
    {
        mPosition = mInitialPosition;
        mOrientation = mInitialOrientation;
        mScale = mInitialScale;

        needUpdate();
    }

    void Node::resetPosition()
    {
        mPosition = Ogre::Vector3::ZERO;


    }

    void Node::resetOrientation()
    {
        mOrientation = Ogre::Quaternion::IDENTITY;
    }

    void Node::resetScale()
    {
        mScale = Ogre::Vector3::UNIT_SCALE;
    }

    void Node::buildModelMatrix()
    {
        /* DirectX::XMFLOAT3 s = DirectX::XMFLOAT3(mDerivedScale.x, mDerivedScale.y, mDerivedScale.z);
         DirectX::XMVECTOR S = DirectX::XMLoadFloat3(&s);
         DirectX::XMFLOAT3 p = DirectX::XMFLOAT3(mDerivedPosition.x, mDerivedPosition.y, mDerivedPosition.z);
         DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&p);
         DirectX::XMFLOAT4 q = DirectX::XMFLOAT4(mDerivedOrientation.x, mDerivedOrientation.y, mDerivedOrientation.z, mDerivedOrientation.w);
         DirectX::XMVECTOR Q = DirectX::XMLoadFloat4(&q);
         DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

         mModel =  DirectX::XMMatrixAffineTransformation(S, zero, Q, P);*/


    }

    Ogre::Vector3 Node::convertWorldToLocalPosition(const Ogre::Vector3& worldPos)
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }

        return mDerivedOrientation.Inverse() * (worldPos - mDerivedPosition) / mDerivedScale;
    }

    Ogre::Vector3 Node::convertLocalToWorldPosition(const Ogre::Vector3& localPos)
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }


        mCachedTransform.makeTransform(
            _getDerivedPosition(),
            _getDerivedScale(),
            _getDerivedOrientation()
        );

        return mCachedTransform * localPos;
    }

    Ogre::Quaternion Node::convertWorldToLocalOrientation(const Ogre::Quaternion& worldOrientation)
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }
        return mDerivedOrientation.Inverse() * worldOrientation;
    }

    Ogre::Quaternion Node::convertLocalToWorldOrientation(const Ogre::Quaternion& localOrientation)
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }
        return mDerivedOrientation * localOrientation;

    }

    Ogre::Vector3 Node::convertLocalToWorldDirection(const Ogre::Vector3& localDir, bool useScale)
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }

        if (useScale)
        {
            Ogre::Matrix3 mat3;
            _getFullTransform().extract3x3Matrix(mat3);
            return mat3 * localDir;
        }

        return mDerivedOrientation * localDir;
    }

    Ogre::Vector3 Node::convertWorldToLocalDirection(const Ogre::Vector3& worldDir, bool useScale)
    {
        if (mNeedParentUpdate)
        {
            _updateFromParent();
        }

        return useScale ?
            mDerivedOrientation.Inverse() * worldDir / mDerivedScale :
            mDerivedOrientation.Inverse() * worldDir;
    }

    Real Node::getSquaredViewDepth(const Camera* cam) const
    {
        Ogre::Vector3 diff = _getDerivedPosition() - cam->getDerivedPosition();
        Ogre::Vector3 zAxis = cam->getDerivedDirection();

        // NB use squared length to avoid square root
        return cam->getSortMode() == Ogre::SM_DISTANCE ? diff.squaredLength() :
            Ogre::Math::Sqr(zAxis.dotProduct(diff));
    }

    void Node::setListener(Listener* listener)
    {
        mListener = listener;
    }

    Node::Listener* Node::getListener()
    {
        return mListener;
    }

    Node* Node::createChild(
        const Vector3& translate,
        const Quaternion& rotate)
    {
        return nullptr;
    }

    void Node::updateFromParentImpl(void) const
    {

    }

    void Node::addChild(Node* child)
    {
        if (child->mParent)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "Node '" + child->getName() + "' already was a child of '" +
                child->mParent->getName() + "'.",
                "Node::addChild");
        }

        mChildren.push_back(child);
        child->mParent = this;
    }

    void Node::removeChild(Node* child)
    {
        ChildNodeMap::iterator i = std::find(mChildren.begin(), mChildren.end(), child);
        if (i != mChildren.end() && *i == child)
        {
            std::swap(*i, mChildren.back());
            mChildren.pop_back();
            child->mParent = nullptr;
        }
    }

    const Node::ChildNodeMap& Node::getChildren() const
    {
        static Node::ChildNodeMap aa;
        return aa;
    }

    void Node::queueNeedUpdate(Node* n)
    {

    }
}
