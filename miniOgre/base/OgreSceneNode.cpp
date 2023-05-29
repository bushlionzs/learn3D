#include "OgreHeader.h"
#include "OgreSceneNode.h"
#include "shader.h"
#include "renderSystem.h"
#include "OgreMoveObject.h"
#include "OgreCamera.h"

namespace Ogre {

    SceneNode::SceneNode(SceneManager* creator, const String& name)
        :Node(name, nullptr),
        mCreator(creator)
    {

    }

    SceneNode::~SceneNode()
    {

    }

    SceneNode* SceneNode::createChildSceneNode(const String& name)
    {
        SceneNode* node = new SceneNode(mCreator, name);
        addChild(node);
        return node;
    }

    void SceneNode::traverse(EngineRenderList& containter, ICamera* cam)
    {
        if (!mVisible)
            return;

        bool useShadow = cam->getCameraType() == CameraType_Light;
        for (auto it : mMoveObjects)
        {
            if (useShadow && !it->getCastShadows())
            {
                continue;
            }
            if (!useShadow)
            {
                it->_notifyCurrentCamera(cam);
            }
            
            const AxisAlignedBox& box = it->getWorldBoundingBox(true);
            if (!cam->isVisible(box))
            {
                continue;
            }
            const std::vector<Renderable*>& rs = it->getRenderableList();
            if (it->isTransparent())
            {
                for (auto r : rs)
                {
                    containter.mTransparentList.push_back(r);
                }
            }
            else
            {
                for (auto r : rs)
                {
                    containter.mOpaqueList.push_back(r);
                }
            }
        }

        for (auto child : mChildren)
        {
            SceneNode* sn = (SceneNode*)child;
            sn->traverse(containter, cam);
        }
    }

    void SceneNode::render(RenderSystem* engine)
    {
        if (!mVisible)
            return;
        /*for (auto it : mMoveObjects)
        {
            engine->render(it);
        }

        for (auto child : mChilds)
        {
            child->render(engine);
        }*/
    }

    void SceneNode::update(float timeSinceLastFrame)
    {
        if (mName == "effect")
        {
            int kk = 0;
        }
        for (auto o : mMoveObjects)
        {
            o->update(timeSinceLastFrame);
        }
        for (auto child : mChildren)
        {
            child->update(timeSinceLastFrame);
        }
    }

    void SceneNode::attachObject(MoveObject* obj)
    {
        mMoveObjects.push_back(obj);
        obj->_notifyAttached(this);
    }


    void SceneNode::setDirection(const Vector3& vec, TransformSpace relativeTo,
        const Vector3& localDirectionVector)
    {
        // Do nothing if given a zero vector
        if (vec == Vector3::ZERO) return;

        // The direction we want the local direction point to
        Vector3 targetDir = vec.normalisedCopy();

        // Transform target direction to world space
        switch (relativeTo)
        {
        case TS_PARENT:
            if (mInheritOrientation)
            {
                if (mParent)
                {
                    targetDir = mParent->_getDerivedOrientation() * targetDir;
                }
            }
            break;
        case TS_LOCAL:
            targetDir = _getDerivedOrientation() * targetDir;
            break;
        case TS_WORLD:
            // default orientation
            break;
        }

        // Calculate target orientation relative to world space
        Quaternion targetOrientation;
        if (mYawFixed)
        {
            // Calculate the quaternion for rotate local Z to target direction
            Vector3 xVec = mYawFixedAxis.crossProduct(targetDir);
            xVec.normalise();
            Vector3 yVec = targetDir.crossProduct(xVec);
            yVec.normalise();
            Quaternion unitZToTarget = Quaternion(xVec, yVec, targetDir);

            if (localDirectionVector == Vector3::NEGATIVE_UNIT_Z)
            {
                // Specail case for avoid calculate 180 degree turn
                targetOrientation =
                    Quaternion(-unitZToTarget.y, -unitZToTarget.z, unitZToTarget.w, unitZToTarget.x);
            }
            else
            {
                // Calculate the quaternion for rotate local direction to target direction
                Quaternion localToUnitZ = localDirectionVector.getRotationTo(Vector3::UNIT_Z);
                targetOrientation = unitZToTarget * localToUnitZ;
            }
        }
        else
        {
            const Quaternion& currentOrient = _getDerivedOrientation();

            // Get current local direction relative to world space
            Vector3 currentDir = currentOrient * localDirectionVector;

            if ((currentDir + targetDir).squaredLength() < 0.00005f)
            {
                // Oops, a 180 degree turn (infinite possible rotation axes)
                // Default to yaw i.e. use current UP
                targetOrientation =
                    Quaternion(-currentOrient.y, -currentOrient.z, currentOrient.w, currentOrient.x);
            }
            else
            {
                // Derive shortest arc to new direction
                Quaternion rotQuat = currentDir.getRotationTo(targetDir);
                targetOrientation = rotQuat * currentOrient;
            }
        }

        // Set target orientation, transformed to parent space
        if (mParent && mInheritOrientation)
            setOrientation(mParent->_getDerivedOrientation().UnitInverse() * targetOrientation);
        else
            setOrientation(targetOrientation);
    }

    void SceneNode::detachObject(MoveObject* obj)
    {
        
    }

    MoveObject* SceneNode::detachObject(const String& name)
    {
        return nullptr;
    }

    size_t SceneNode::numAttachedObjects(void) const
    {
        return 0;
    }

    void SceneNode::detachAllObjects(void)
    {

    }

    void SceneNode::removeAndDestroyAllChildren(void)
    {

    }

    void SceneNode::setFixedYawAxis(bool useFixed, const Vector3& fixedAxis)
    {
        mYawFixed = useFixed;
        mYawFixedAxis = fixedAxis;
    }

    void SceneNode::lookAt(const Vector3& targetPoint, TransformSpace relativeTo,
        const Vector3& localDirectionVector)
    {
        Vector3 origin;
        switch (relativeTo)
        {
        default:    // Just in case
        case TS_WORLD:
            origin = _getDerivedPosition();
            break;
        case TS_PARENT:
            origin = getPosition();
            break;
        case TS_LOCAL:
            origin = Vector3::ZERO;
            break;
        }

        setDirection(targetPoint - origin, relativeTo, localDirectionVector);
    }
}

