#pragma once
#include "OgreUserObjectBindings.h"
class SVertexElement
{
public:
    SVertexElement();
    SVertexElement(
        float px, float py, float pz,
        float nx, float ny, float nz,
        float u, float v
    );
    ~SVertexElement();
public:
    Ogre::Vector3 mPosition;
    Ogre::Vector3 mNormal;
    Ogre::Vector2 mUV;
};

namespace Ogre {

    class Node
    {
    public:
        class  Listener
        {
        public:
            Listener() {}
            virtual ~Listener() {}
            /** Called when a node gets updated.
            @remarks
                Note that this happens when the node's derived update happens,
                not every time a method altering it's state occurs. There may
                be several state-changing calls but only one of these calls,
                when the node graph is fully updated.
            */
            virtual void nodeUpdated(const Node*) {}
            /** Node is being destroyed */
            virtual void nodeDestroyed(const Node*) {}
            /** Node has been attached to a parent */
            virtual void nodeAttached(const Node*) {}
            /** Node has been detached from a parent */
            virtual void nodeDetached(const Node*) {}
        };
    public:
        /** Enumeration denoting the spaces which a transform can be relative to.
        */
        enum TransformSpace
        {
            /// Transform is relative to the local space
            TS_LOCAL,
            /// Transform is relative to the space of the parent node
            TS_PARENT,
            /// Transform is relative to world space
            TS_WORLD
        };

        typedef std::vector<Node*> ChildNodeMap;
    public:
        Node(const std::string& name, Node* parent);
        ~Node();

        const Ogre::Matrix4& getWorldModelMatrix();
        const Ogre::Matrix4& getLocalModelMatrix();
        void setLocalModelMatrix(const Ogre::Matrix4& matrix);
        void addReflect(Node* node);
        Node* getReflect();
        void setTransparent(bool transparent);
        bool isTransparent();
        void setMirror(bool mirror);
        bool isMirror();

        void setDynamicReflect(bool enable);
        bool isDynamicReflect();

        void setVisible(bool visible);
        bool isVisible();


        virtual void update(float timeSinceLastFrame);
        virtual const Ogre::Matrix4& _getFullTransform(void) const;
        virtual void needUpdate(bool forceParentUpdate = false);
        void updatechildren();
        void setPosition(float x, float y, float z);
        void setPosition(const Ogre::Vector3& position);
        void setOrientation(float w, float x, float y, float z);
        void setOrientation(const Ogre::Quaternion& q);
        void setScale(float x, float y, float z);
        void setScale(const Ogre::Vector3& s);

        const Ogre::Vector3& getScale() const;
        const Ogre::Vector3& getPosition() const;
        const Ogre::Quaternion& getQuaternion() const;
        const Ogre::Quaternion& getOrientation() const;

        void rotate(const Ogre::Quaternion& q, TransformSpace relativeTo = TS_LOCAL);
        void scale(const Ogre::Vector3& inScale);
        void translate(const Ogre::Vector3& d, TransformSpace relativeTo = TS_PARENT);

        void yaw(const Ogre::Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        void pitch(const Ogre::Radian& angle, TransformSpace relativeTo = TS_LOCAL);

        const Ogre::Quaternion& _getDerivedOrientation(void) const;
        const Ogre::Vector3& _getDerivedPosition(void) const;
        const Ogre::Vector3& _getDerivedScale(void) const;
        void _updateFromParent() const;
        void setInitialState(void);
        void resetToInitialState(void);
        void resetPosition();
        void resetOrientation();
        void resetScale();
        void buildModelMatrix();

        Ogre::Vector3 convertWorldToLocalPosition(const Ogre::Vector3& worldPos);
        Ogre::Vector3 convertLocalToWorldPosition(const Ogre::Vector3& localPos);
        Ogre::Quaternion convertWorldToLocalOrientation(const Ogre::Quaternion& worldOrientation);
        Ogre::Quaternion convertLocalToWorldOrientation(const Ogre::Quaternion& localOrientation);

        Ogre::Vector3 convertLocalToWorldDirection(const Ogre::Vector3& localDir, bool useScale);
        Ogre::Vector3 convertWorldToLocalDirection(const Ogre::Vector3& worldDir, bool useScale);
        Real getSquaredViewDepth(const Camera* cam) const;

        String& getName()
        {
            return mName;
        }

        void setListener(Listener* listener);
        Listener* getListener();

        virtual Node* createChild(
            const Vector3& translate = Vector3::ZERO,
            const Quaternion& rotate = Quaternion::IDENTITY);

        virtual void updateFromParentImpl(void) const;

        void addChild(Node* child);
        void removeChild(Node* child);
        const ChildNodeMap& getChildren() const;
        UserObjectBindings& getUserObjectBindings() 
        { 
            return mUserObjectBindings; 
        }
        static void queueNeedUpdate(Node* n);
    protected:
        Ogre::Matrix4 mModel;
        Ogre::Matrix4 mWorldModel;

        Ogre::Vector3 mPosition;
        Ogre::Vector3 mScale;
        Ogre::Quaternion mOrientation;

        mutable Ogre::Matrix4 mCachedTransform;

        Node* mParent;
        ChildNodeMap mChildren;

        std::string mName;

        bool mVisible = true;
        Node* mReflect = nullptr;

        bool mTransparent = false;
        bool mMirror = false;

        bool mDynamicReflect = false;

        //
        mutable  bool mNeedParentUpdate = true;
        mutable bool mNeedWorldMatrix = true;
        mutable  Ogre::Vector3 mDerivedScale;
        mutable Ogre::Vector3 mDerivedPosition;
        mutable Ogre::Quaternion mDerivedOrientation;

        Ogre::Vector3 mInitialPosition;
        /// The orientation to use as a base for keyframe animation
        Ogre::Quaternion mInitialOrientation;
        /// The scale to use as a base for keyframe animation
        Ogre::Vector3 mInitialScale;

        bool mInheritOrientation = true;
        /// Stores whether this node inherits scale from it's parent
        bool mInheritScale = true;

        Ogre::Matrix4 mCacheMatrix;

        Listener* mListener = nullptr;

        UserObjectBindings mUserObjectBindings;
    };
}