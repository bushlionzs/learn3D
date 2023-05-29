#pragma once
#include "engine_struct.h"
#include "OgreNode.h"
class RenderSystem;

class Shader;



class INodeEvent
{
public:
	virtual void updateShader(RenderSystem*engine, Shader* shader) = 0;
};

namespace Ogre {

    class SceneNode :public Node
    {
    public:
        typedef std::vector<MoveObject*> ObjectMap;
        SceneNode(SceneManager* creator, const String& name);
        ~SceneNode();

        SceneNode* createChildSceneNode(const String& name);
        void traverse(EngineRenderList& containter, ICamera* cam);
        void render(RenderSystem* engine);
        void update(float timeSinceLastFrame);

        virtual void attachObject(MoveObject* obj);

        SceneNode* getParent()
        {
            return (SceneNode*)mParent;
        }

        SceneManager* getCreator(void) const 
        { 
            return mCreator; 
        }

        void setDirection(const Vector3& vec, TransformSpace relativeTo = TS_PARENT,
            const Vector3& localDirectionVector = Vector3::NEGATIVE_UNIT_Z);

        virtual void detachObject(MoveObject* obj);
        virtual MoveObject* detachObject(const String& name);

        size_t numAttachedObjects(void) const;

        virtual void detachAllObjects(void);

        void removeAndDestroyAllChildren(void);

        const ObjectMap& getAttachedObjects() const {
            return mObjectsByName;
        }

        void setFixedYawAxis(bool useFixed, const Vector3& fixedAxis = Vector3::UNIT_Y);
        void lookAt(const Vector3& targetPoint, TransformSpace relativeTo,
            const Vector3& localDirectionVector = Vector3::NEGATIVE_UNIT_Z);
    private:
        std::vector<MoveObject*> mMoveObjects;
        SceneManager* mCreator;
        ObjectMap mObjectsByName;

        bool mYawFixed = false;
        Vector3 mYawFixedAxis;
    };
}