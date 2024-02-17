#pragma once

#include "OgreUserObjectBindings.h"
#include "OgreAxisAlignedBox.h"
namespace Ogre {
    class MovableObjectFactory;
    class MoveObject
    {
    public:
        MoveObject(const std::string& name);
        MoveObject();
        virtual ~MoveObject();

        virtual void _notifyAttached(Node* parent, bool isTagPoint = false);

        virtual void _notifyCurrentCamera(ICamera* cam);

        virtual const std::vector<Renderable*>& getRenderableList()
        {
            return mRenderables;
        }

        const Ogre::Matrix4& getModelMatrix() const;

        virtual void update(float delta) {}
        virtual bool isTransparent();
        virtual bool isDynamicReflect();


        const Ogre::Matrix4& _getParentNodeFullTransform(void) const;

        SceneNode* getParentSceneNode(void) const;
        Node* getParentNode(void);
        void setPosition(Ogre::Vector3& pos);

        void setCastShadows(bool cast);
        bool getCastShadows()
        {
            return mCastShadows;
        }
        void setVisible(bool visible);

        bool isVisible() const
        {
            return mVisible;
        }

        void setVisibilityFlags(uint32_t flags);

        UserObjectBindings& getUserObjectBindings();

        const std::string& getMovableType() const;
        const std::string& getName() const
        {
            return mName;
        }

        virtual void _notifyMoved(void);

        uint32 getTypeFlags(void) const;

        void addQueryFlags(uint32 flags) 
        { 
            mQueryFlags |= flags; 
        }

        uint32_t getQueryFlags()
        {
            return mQueryFlags;
        }

        virtual Real getBoundingRadius(void) const { return 0; }
        virtual const AxisAlignedBox& getBoundingBox(void) const = 0;

        virtual const AxisAlignedBox& getWorldBoundingBox(bool derive = false) const;

        virtual void setUserAny(const Any& anything) { mUserAny = anything; }

        /** Retrieves the custom user value associated with this object.
        */
        virtual const Any& getUserAny(void) const { return mUserAny; }

        virtual void _notifyCreator(MovableObjectFactory* fact) 
        { 
            mCreator = fact; 
        }
    protected:
        Node* mParent;
        SceneManager* mManager;
        MovableObjectFactory* mCreator;
        std::string mName;
        Ogre::Matrix4 mWorld;
        Ogre::Matrix4 mLocal;
        Ogre::Vector3 mPosition;
        std::vector<Renderable*> mRenderables;
        UserObjectBindings mUserObjectBindings;
        uint32_t  mQueryFlags = 0;

        bool mVisible = true;

        String mObjectType;

        mutable AxisAlignedBox mWorldAABB;

        bool mCastShadows = false;

        Ogre::Any mUserAny;
    };


    class  MovableObjectFactory
    {
    private:
        /// Type flag, allocated if requested
        uint32_t mTypeFlag;

        /// Internal implementation of create method - must be overridden
        virtual MoveObject* createInstanceImpl(
            const String& name, const NameValuePairList* params = 0) = 0;
    public:
        MovableObjectFactory() : mTypeFlag(0xFFFFFFFF) {}
        virtual ~MovableObjectFactory() {}
        /// Get the type of the object to be created
        virtual const String& getType(void) const = 0;

        /** Create a new instance of the object.
        @param name The name of the new object
        @param manager The SceneManager instance that will be holding the
            instance once created.
        @param params Name/value pair list of additional parameters required to
            construct the object (defined per subtype). Optional.
        */
        MoveObject* createInstance(
            const String& name, SceneManager* manager,
            const NameValuePairList* params = 0);
        /** Destroy an instance of the object */
        virtual void destroyInstance(MoveObject* obj);

        /** Does this factory require the allocation of a 'type flag', used to
            selectively include / exclude this type from scene queries?

            The default implementation here is to return 'false', ie not to
            request a unique type mask from Root. For objects that
            never need to be excluded in SceneQuery results, that's fine, since
            the default implementation of MovableObject::getTypeFlags is to return
            all ones, hence matching any query type mask. However, if you want the
            objects created by this factory to be filterable by queries using a
            broad type, you have to give them a (preferably unique) type mask -
            and given that you don't know what other MovableObject types are
            registered, Root will allocate you one.
        */
        virtual bool requestTypeFlags(void) const { return false; }
        /** Notify this factory of the type mask to apply.

            This should normally only be called by Root in response to
            a 'true' result from requestTypeMask. However, you can actually use
            it yourself if you're careful; for example to assign the same mask
            to a number of different types of object, should you always wish them
            to be treated the same in queries.
        */
        void _notifyTypeFlags(uint32 flag) { mTypeFlag = flag; }

        /** Gets the type flag for this factory.

            A type flag is like a query flag, except that it applies to all instances
            of a certain type of object.
        */
        uint32 getTypeFlags(void) const { return mTypeFlag; }

    };
}