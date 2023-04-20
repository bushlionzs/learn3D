#include "OgreHeader.h"
#include "OgreMoveObject.h"
#include "OgreSceneNode.h"

namespace Ogre {

    MoveObject::MoveObject(const std::string& name)
    {
        mName = name;
        mParent = nullptr;
        mWorldAABB.setNull();
    }

    MoveObject::MoveObject()
    {
        mParent = nullptr;
        mWorldAABB.setNull();
    }

    MoveObject::~MoveObject()
    {

    }

    void MoveObject::_notifyAttached(Node* parent, bool isTagPoint)
    {
        assert(!mParent);
        mParent = parent;
    }

    void MoveObject::_notifyCurrentCamera(Camera* cam)
    {

    }

    const Ogre::Matrix4& MoveObject::getModelMatrix()
    {
        return mParent->getWorldModelMatrix();
    }

    bool MoveObject::isTransparent()
    {
        return mParent->isTransparent();
    }

    bool MoveObject::isDynamicReflect()
    {
        return mParent->isDynamicReflect();
    }

    const Ogre::Matrix4& MoveObject::_getParentNodeFullTransform(void) const
    {
        return mParent->_getFullTransform();
    }

    SceneNode* MoveObject::getParentSceneNode(void) const
    {
        return static_cast<SceneNode*>(mParent);
    }

    void MoveObject::setPosition(Ogre::Vector3& pos)
    {
        mPosition = pos;
        mLocal.makeTransform(pos, Ogre::Vector3(1.0f, 1.0f, 1.0f), Ogre::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
    }

    void MoveObject::setCastShadows(bool cast)
    {

    }
    void MoveObject::setVisible(bool visible)
    {
        mVisible = visible;
    }

    void MoveObject::setVisibilityFlags(uint32_t flags)
    {

    }

    UserObjectBindings& MoveObject::getUserObjectBindings()
    {
        return mUserObjectBindings;
    }

    const std::string& MoveObject::getMovableType() const
    {
        return mObjectType;
    }

    void MoveObject::_notifyMoved(void)
    {

    }


    const AxisAlignedBox& MoveObject::getWorldBoundingBox(bool derive) const
    {
        if (derive)
        {
            mWorldAABB = this->getBoundingBox();
            mWorldAABB.transform(_getParentNodeFullTransform());
        }

        return mWorldAABB;
    }

    Node* MoveObject::getParentNode(void)
    {
        return mParent;
    }

    MoveObject* MovableObjectFactory::createInstance(
        const String& name, SceneManager* manager,
        const NameValuePairList* params)
    {
        MoveObject* m = createInstanceImpl(name, params);
        /*m->_notifyCreator(this);
        m->_notifyManager(manager);*/
        return m;
    }

    void MovableObjectFactory::destroyInstance(MoveObject* obj)
    {
        delete obj;
    }
}