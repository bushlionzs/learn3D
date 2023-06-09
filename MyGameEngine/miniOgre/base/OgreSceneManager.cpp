#include "OgreHeader.h"
#include "OgreSceneManager.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "renderSystem.h"
#include "OgremeshManager.h"
#include "OgreEntity.h"
#include "WaterEntity.h"
#include "OgreMaterialManager.h"
#include "OgreParticleSystemManager.h"
#include "OgreParticleSystem.h"
#include "OgreRoot.h"
#include "OgreMoveObject.h"
#include "OgreSky.h"
#include "myutils.h"
#include "OgreViewport.h"

namespace Ogre {
    SceneManager::SceneManager()
    {
        mRenderSystem = Ogre::Root::getSingleton().getRenderSystem();

        mRoot = new SceneNode(this, std::string("__root"));
    }

    SceneManager::~SceneManager()
    {

    }

    Camera* SceneManager::createCamera(const std::string& name)
    {
        auto itor = mCameraMap.find(name);
        if (itor != mCameraMap.end())
        {
            return nullptr;
        }

        Camera* camera = new Camera(name, this);
        mCameraMap[name] = camera;
        return camera;
    }

    void SceneManager::_renderScene(Camera* camera, Ogre::Viewport* vp)
    {
        
        mCurrentViewport = vp;
        mCameraInProgress = camera;
        mEngineRenderList.mOpaqueList.clear();
        mEngineRenderList.mTransparentList.clear();

        mRenderSystem->_setViewport(vp);

        mRoot->traverse(mEngineRenderList, camera);

        if (mCurrentViewport->getClearEveryFrame())
        {
            mRenderSystem->clearFrameBuffer(
                mCurrentViewport->getClearBuffers(),
                mCurrentViewport->getBackgroundColour(),
                mCurrentViewport->getDepthClear());
        }
        
        {
            std::sort(mEngineRenderList.mOpaqueList.begin(), mEngineRenderList.mOpaqueList.end(),
                [](Ogre::Renderable* a, Ogre::Renderable* b)
                {
                return a->getSortValue() < b->getSortValue();
                }
            );
            for (auto r : mEngineRenderList.mOpaqueList)
            {
                mRenderSystem->render(r, RenderListType_Opaque);
            }

            for (auto r : mEngineRenderList.mTransparentList)
            {
                mRenderSystem->render(r, RenderListType_Transparent);
            }
        }
        
    }

    void SceneManager::update(float timeSinceLastFrame)
    {
        mRoot->update(timeSinceLastFrame);
    }

    Entity* SceneManager::createEntity(const std::string& name, const std::string& meshName)
    {
        std::shared_ptr<Mesh> mesh = MeshManager::getSingleton().load(meshName);

        if (!mesh)
        {
            return nullptr;
        }

        Entity* entity = new Entity(name, mesh);

        return entity;
    }

    Entity* SceneManager::createEntity(const std::string& name, const MeshPtr& mesh)
    {
        Entity* entity = new Entity(name, mesh);

        return entity;
    }

    Entity* SceneManager::createWaterEntity(const std::string& name,
        int m, int n, float dx, float dt, float speed, float damping)
    {
        Entity* entity = new WaterEntity(name);
        return entity;
    }

    SceneNode* SceneManager::getRoot()
    {
        return mRoot;
    }

    SceneNode* SceneManager::createSceneNode(const String& name)
    {
        auto itor = mNamedNodes.find(name);
        if (itor != mNamedNodes.end())
        {
            assert(false);
        }
        auto node = OGRE_NEW SceneNode(this, name);
        mNamedNodes[name] = node;
        return node;
    }

    SceneNode* SceneManager::getSceneNode(const String& name)
    {
        auto itor = mNamedNodes.find(name);
        if (itor != mNamedNodes.end())
        {
            return itor->second;
        }
        return nullptr;
    }

    Ogre::ParticleSystem* SceneManager::createParticleSystem(const String& name,
        const String& templateName)
    {
        NameValuePairList params;
        params["templateName"] = templateName;

        return static_cast<Ogre::ParticleSystem*>(
            createMovableObject(name, Ogre::ParticleSystemFactory::FACTORY_TYPE_NAME,
                &params));
    }

    MoveObject* SceneManager::createMovableObject(const String& name,
        const String& typeName, const NameValuePairList* params)
    {

        Ogre::MovableObjectFactory* factory =
            Ogre::Root::getSingleton().getMovableObjectFactory(typeName);
        // Check for duplicate names

        auto itor = mMoveObjectMap.find(name);
        if (itor != mMoveObjectMap.end())
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "duplicate name");
        }
        MoveObject* newObj = factory->createInstance(name, this, params);
        mMoveObjectMap[name] = newObj;
        return newObj;
    }

    void SceneManager::destroySceneNode(SceneNode* sn)
    {
        String& name = sn->getName();

        auto itor = mNamedNodes.find(name);
        if (itor != mNamedNodes.end())
        {
            delete sn;
            mNamedNodes.erase(itor);
        }
        else
        {
            delete sn;
        }
    }

    SceneNode* SceneManager::createSceneNode()
    {
        return nullptr;
    }
    RaySceneQuery*
        SceneManager::createRayQuery(const Ray& ray, uint32 mask)
    {
        return nullptr;
    }

    void SceneManager::destroyMovableObject(const String& name, const String& typeName)
    {

    }
    void SceneManager::destroyMovableObject(MoveObject* m)
    {

    }

    RibbonTrail* SceneManager::createRibbonTrail(const String& name)
    {
        return nullptr;
    }

    void SceneManager::destroyRibbonTrail(const String& name)
    {

    }

    Light* SceneManager::createLight(const String& name)
    {
        return nullptr;
    }

    void SceneManager::destroyLight(const String& name)
    {
        
    }

    void SceneManager::setAmbientLight(const ColourValue& colour)
    {

    }

    void SceneManager::destroyBillboardSet(MoveObject* set)
    {

    }

    void SceneManager::destroyBillboardSet(const String& name)
    {

    }

    BillboardSet* SceneManager::createBillboardSet(const String& name, unsigned int poolSize)
    {
        return nullptr;
    }


    FogMode SceneManager::getFogMode(void) const
    {
        return FOG_NONE;
    }

    const ColourValue& SceneManager::getFogColour(void) const
    {
        return Ogre::ColourValue::Black;
    }
    Real SceneManager::getFogStart(void) const
    {
        return 0.0f;
    }
    Real SceneManager::getFogEnd(void) const
    {
        return 10000.f;
    }

    void SceneManager::destroyEntity(MoveObject* ent)
    {

    }

    /// @overload
    void SceneManager::destroyEntity(const String& name)
    {

    }

    void SceneManager::destroyCamera(Camera* cam)
    {

    }

 
    void SceneManager::destroyCamera(const String& name)
    {

    }

    void SceneManager::removeBillboardSet(const String& name)
    {

    }

    void SceneManager::destroyStaticGeometry(const String& name)
    {

    }

    void SceneManager::destroyParticleSystem(MoveObject* obj)
    {

    }
    /// @overload
    void SceneManager::destroyParticleSystem(const String& name) 
    {

    }

    void SceneManager::setSkyBox(
        bool enable, const String& materialName, Real distance,
        bool drawFirst, const Quaternion& orientation)
    {
        _setSkyBox(enable, materialName, distance,orientation);
    }

    /// @overload
    void SceneManager::_setSkyBox(
        bool enable, const String& materialName, Real distance,
        const Quaternion& orientation)
    {
        mSkyBox = std::make_shared<SkyBoxRenderer>(this);
        mSkyBox->setSkyBox(enable, materialName, distance, 0, orientation, BLANKSTRING);
    }

    void SceneManager::setSkyLayer(int layerIndex, const String& meshName, 
        bool drawFirst,
        const Vector3& offset,
        const Vector3& scale,
        const Quaternion& orientation,
        float uScroll,
        float vScroll,
        bool keepDistance,
        bool keepHeight,
        bool keepOrient,
        bool affectByFog)
    {

    }

    void SceneManager::clearScene()
    {

    }

    void SceneManager::destroyAllCameras()
    {

    }

    void SceneManager::destroyAllEntities()
    {

    }
}
