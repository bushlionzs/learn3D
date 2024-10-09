#include "OgreHeader.h"
#include "ShadowMap.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMeshManager.h"
#include "OgreTextureManager.h"
#include "OgreRenderTexture.h"
#include "OgreCamera.h"
#include "OgreAnimationState.h"
#include "OgreLight.h"
#include "OgreMaterialManager.h"
#include "OgreViewport.h"
#include "OgreRenderWindow.h"
#include "renderSystem.h"
#include "game_camera.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreRoot.h"
#include "OgreVertexData.h"
#include "PassUtil.h"
#include "pass.h"
#include "shaderManager.h"
#include "forgeCommon.h"

ShadowMap::ShadowMap()
{

}

ShadowMap::~ShadowMap()
{

}


void ShadowMap::setup(
    RenderSystem* renderSystem,
    RenderWindow* renderWindow,
    Ogre::SceneManager* sceneManager,
    GameCamera* gameCamera
)
{
    mRenderSystem = renderSystem;
    mRenderWindow = renderWindow;
    mSceneManager = sceneManager;
    mGameCamera = gameCamera;
    base2();
}

void ShadowMap::update(float delta)
{
    mGameCamera->update(delta);
    if (mAnimationState)
    {
        mAnimationState->addTime(delta);
    }

    if (mLightNode)
    {
        mLightNode->yaw(Ogre::Radian(3.14) * delta * 0.1);
    }
}

void ShadowMap::updatePass(std::vector<PassBase*>& passlist)
{
    passlist = mPassList;   
}

FrameGraphId<FrameGraphTexture> ShadowMap::fgPass(FrameGraph& fg)
{
    FrameGraphTexture::Descriptor colorBufferDesc = {
        .width = mRenderWindow->getWidth(),
        .height = mRenderWindow->getHeight(),
        .format = backend::TextureFormat::RGB16F
    };

    PassUtil::PassConfig config;


    config.rs = mRenderSystem;
    config.target = mRenderWindow;
    config.scene = Ogre::Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);

    config.cam = config.scene->getCamera(MAIN_CAMERA);
    auto color = PassUtil::colorPass(fg, "Color Pass", colorBufferDesc, config);
    return color;
}
void ShadowMap::base1()
{
	auto root = mSceneManager->getRoot();

	MeshManager::getSingletonPtr()->CreateSphere("sphere.mesh", 0.5f, 20, 20);
	MeshManager::getSingletonPtr()->CreateCylinder("cylinder.mesh", 0.5f, 0.3f, 3.0f, 20, 20);

	float aa = 20.0f;
	float h = -2.0f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, h, -aa);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, h, aa);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, h, -aa);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, h, aa);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 1.0f, 0.0f);
	std::string meshName = "myrect";
	auto mesh = MeshManager::getSingletonPtr()->createRect(
		nullptr,
		meshName,
		leftop, leftbottom, righttop, rightbottom, normal);
	auto mat = MaterialManager::getSingleton().getByName("myground");
	mesh->getSubMesh(0)->setMaterial(mat);
	Entity* ground = mSceneManager->createEntity("ground", meshName);
	SceneNode* groundnode = root->createChildSceneNode("ground");
	groundnode->attachObject(ground);

	Entity* sphere = mSceneManager->createEntity("sphere", "sphere.mesh");
	SceneNode* spherenode = root->createChildSceneNode("sphere");
	spherenode->setPosition(Ogre::Vector3(0.0f, 1.5f, 0.0f));
	spherenode->attachObject(sphere);
	spherenode->_getDerivedPosition();
	Entity* cylinder = mSceneManager->createEntity("cylinder", "cylinder.mesh");
	SceneNode* cylindernode = root->createChildSceneNode("cylinder");
	cylindernode->attachObject(cylinder);
	cylindernode->setPosition(Ogre::Vector3(0, 0.0, 0.0f));


	mesh = MeshManager::getSingleton().load("ninja.mesh");
	Entity* ninja = mSceneManager->createEntity("ninja", "ninja.mesh");

	SceneNode* ninjanode = root->createChildSceneNode("ninja");
	ninjanode->attachObject(ninja);
	ninjanode->setPosition(Ogre::Vector3(-4, -2, -1.0f));
	ninjanode->yaw(Ogre::Radian(3.14f));
	float s = 0.015f;
	ninjanode->setScale(Ogre::Vector3(s, s, s));

	ninja->setCastShadows(true);
	sphere->setCastShadows(true);
	cylinder->setCastShadows(true);

	mAnimationState = ninja->getAnimationState(std::string("Walk"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}

	mGameCamera->updateCamera(Ogre::Vector3(0, 0.0f, 8.0f), Ogre::Vector3::ZERO);
	mGameCamera->setMoveSpeed(10.0f);

	light = mSceneManager->createLight("shadow");
	light->setLightType(LightType_Direction, 0);

	mLightNode = root->createChildSceneNode("light");

	auto m4 = Ogre::Math::makeLookAtLH(
		Ogre::Vector3(-20, 20, -20), Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_Y);

	auto q = m4.extractQuaternion();

	auto subnode = mLightNode->createChildSceneNode("shadow");
	subnode->attachObject(light);
	subnode->setOrientation(q);
	subnode->setPosition(Ogre::Vector3(-20, 20, -20));

	light->mViewMatrix = Ogre::Math::makeLookAtLH(
		Ogre::Vector3(-20, 20, -20), Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_Y);


	int width = 10;
	int height = 10;

	Real left = -width / 2.0f;
	Real right = width / 2.0f;
	Real top = height / 2.0f;
	Real bottom = -height / 2.0f;


	light->mProjMatrix = Ogre::Math::makeOrthoLH(left, right, bottom, top, 1.0f, 10000.0f);


	auto shadowSize = 1024;

	auto shadowMap = mRenderSystem->createRenderTarget(
		"shadow", shadowSize, shadowSize, Ogre::PF_DEPTH32_STENCIL8,
        Ogre::TextureUsage::DEPTH_ATTACHMENT);

    bool useShadow = true;
    RenderPassInput renderInput;
    renderInput.cam = light;
    renderInput.color = nullptr;
    renderInput.depth = shadowMap;
    renderInput.sceneMgr = mSceneManager;
    renderInput.shadowMap = nullptr;
    renderInput.shadowPass = true;
    if (useShadow)
    {
        auto shadowPass = createRenderPass(renderInput);
        mPassList.push_back(shadowPass);
    }
    

    renderInput.cam = mGameCamera->getCamera();
    renderInput.color = mRenderWindow->getColorTarget();
    renderInput.depth = mRenderWindow->getDepthTarget();
    renderInput.sceneMgr = mSceneManager;
    if (useShadow)
    {
        renderInput.shadowMap = shadowMap->getTarget();
        renderInput.light = light;
    }
    
    renderInput.shadowPass = false;
    
    auto mainPass = createRenderPass(renderInput);
    mPassList.push_back(mainPass);
}

#define BATCH_FACE_COUNT_LOW_BIT 2
#define BATCH_FACE_COUNT_MASK 0x1FFC
#define BATCH_GEOMETRY_LOW_BIT 0
#define BATCH_GEOMETRY_MASK 0x3

void ShadowMap::base2()
{
    auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	auto rootNode = mSceneManager->getRoot();
	std::string meshname = "SanMiguel.bin";
    std::shared_ptr<Mesh> mesh = loadSanMiguel(meshname);
    
	Entity* sanMiguel = mSceneManager->createEntity(meshname, meshname);
	SceneNode* sanMiguelNode = rootNode->createChildSceneNode(meshname);
	sanMiguelNode->attachObject(sanMiguel);
	mGameCamera->updateCamera(Ogre::Vector3(0, 5.0f, 8.0f), Ogre::Vector3(0, 5.0f, 0.0f));
	mGameCamera->setMoveSpeed(10.0f);


    enum
    {
        GEOMSET_OPAQUE = 0,
        GEOMSET_ALPHA_CUTOUT
    };

    uint32_t visibilityBufferFilteredIndexCount[NUM_GEOMETRY_SETS] = {};
    auto numFrame = ogreConfig.swapBufferCount;

    auto subMeshCount = mesh->getSubMeshCount();
    std::vector<MeshConstants> meshConstants(subMeshCount);
    auto* rs = mRenderSystem;
    VBConstants constants[2];
    uint32_t indexOffset = 0;
    for (auto i = 0; i < subMeshCount; i++)
    {
        auto subMesh = mesh->getSubMesh(i);

        auto mat = subMesh->getMaterial();

        auto materialFlag = mat->getMaterialFlags();

        uint32_t geomSet = materialFlag & MATERIAL_FLAG_ALPHA_TESTED ? GEOMSET_ALPHA_CUTOUT : GEOMSET_OPAQUE;

        auto indexView = subMesh->getIndexView();
        visibilityBufferFilteredIndexCount[geomSet] += indexView->mIndexCount;

        meshConstants[i].indexOffset = indexView->mIndexLocation;
        meshConstants[i].vertexOffset = indexView->mBaseVertexLocation;
        meshConstants[i].materialID = i;
        meshConstants[i].twoSided = (materialFlag & MATERIAL_FLAG_TWO_SIDED) ? 1 : 0;


    }
    for (uint32_t geomSet = 0; geomSet < NUM_GEOMETRY_SETS; ++geomSet)
    {
        constants[geomSet].indexOffset = indexOffset;
        indexOffset += visibilityBufferFilteredIndexCount[geomSet];
    }

    vbConstantsBuffer =
        mRenderSystem->createBufferObject(BufferObjectBinding::UNIFORM, BufferUsage::STATIC, sizeof(VBConstants) * 2);

    rs->updateBufferObject(vbConstantsBuffer, (const char*)& constants[0], sizeof(VBConstants) * 2);

    uint32_t indirectDrawArgBufferSize = NUM_GEOMETRY_SETS * NUM_CULLING_VIEWPORTS * 8 * sizeof(uint32_t);

    indirectDrawArgBuffer =
        mRenderSystem->createBufferObject(
            BufferObjectBinding::SHADER_STORAGE, 
            BufferUsage::DYNAMIC, 
            indirectDrawArgBufferSize,
            "IndirectDrawArgBuffer");
    
    //clear buffer pass
    {
        ShaderInfo shaderInfo;
        shaderInfo.shaderName = "clearBuffer";
        auto clearBufferProgramHandle = rs->createComputeProgram(shaderInfo);
      
        Handle<HwDescriptorSetLayout> dslh = rs->getDescriptorSetLayout(clearBufferProgramHandle, 0);
        Handle<HwDescriptorSet> ds = rs->createDescriptorSet(dslh);
        

        
        rs->updateDescriptorSetBuffer(ds, 0, &indirectDrawArgBuffer, 1);
        rs->updateDescriptorSetBuffer(ds, 2, &vbConstantsBuffer, 1);

        ComputePassCallback callback = [ds, clearBufferProgramHandle](ComputePassInfo& info) {
            info.programHandle = clearBufferProgramHandle;
            info.computeGroup = Ogre::Vector3i(1, 1, 1);
            info.descSets.clear();
            info.descSets.push_back(ds);
            };
        auto clearBufferPass = createComputePass(callback);
        mPassList.push_back(clearBufferPass);
    }
    
    //filter triangles pass
    {
        ShaderInfo shaderInfo;
        shaderInfo.shaderName = "filterTriangles";
        filterTrianglesProgramHandle = rs->createComputeProgram(shaderInfo);
        
        uint32_t maxIndices = 0;
        for (uint32_t geomSet = 0; geomSet < NUM_GEOMETRY_SETS; ++geomSet)
        {
            maxIndices += visibilityBufferFilteredIndexCount[geomSet];
        }

        uint32_t dispatchGroupCount = 0;
        uint32_t computeThread = 256;
        
        auto maxFilterBatches = (maxIndices / 3) / (computeThread >> 1);

        uint32_t filterDispatchGroupSize = maxFilterBatches * sizeof(FilterDispatchGroupData);

        auto filterDispatchGroupDataBuffer =
            rs->createBufferObject(
                BufferObjectBinding::SHADER_STORAGE,
                BufferUsage::DYNAMIC,
                filterDispatchGroupSize,
                "FilterDispatchGroupDataBuffer");
        

        BufferHandleLockGuard lockGuard(filterDispatchGroupDataBuffer);

        FilterDispatchGroupData* dispatchGroupData = (FilterDispatchGroupData*)lockGuard.data();

        for (auto i = 0; i < subMeshCount; i++)
        {
            auto subMesh = mesh->getSubMesh(i);

            uint32_t triangleCount = subMesh->getIndexView()->mIndexCount / 3;
            uint32_t numDispatchGroups = (subMesh->getIndexView()->mIndexCount / 3 + computeThread - 1) / computeThread;
            auto mat = subMesh->getMaterial();

            auto materialFlag = mat->getMaterialFlags();

            uint32_t geomSet = materialFlag & MATERIAL_FLAG_ALPHA_TESTED ? GEOMSET_ALPHA_CUTOUT : GEOMSET_OPAQUE;
            for (uint32_t groupIdx = 0; groupIdx < numDispatchGroups; ++groupIdx)
            {
                FilterDispatchGroupData& groupData = dispatchGroupData[dispatchGroupCount++];
                const uint32_t firstTriangle = groupIdx * computeThread;
                const uint32_t lastTriangle = std::min(firstTriangle + computeThread, triangleCount);
                const uint32_t trianglesInGroup = lastTriangle - firstTriangle;

                // Fill GPU filter batch data
             
                groupData.meshIndex = i;
                groupData.instanceDataIndex = 0;

                groupData.geometrySet_faceCount = ((trianglesInGroup << BATCH_FACE_COUNT_LOW_BIT) & BATCH_FACE_COUNT_MASK) |
                    ((geomSet << BATCH_GEOMETRY_LOW_BIT) & BATCH_GEOMETRY_MASK);

                // Offset relative to the start of the mesh
                groupData.indexOffset = firstTriangle * 3;
            }
        }


        

        for (auto i = 0; i < NUM_CULLING_VIEWPORTS; i++)
        {
            filteredIndexBuffer[i] =
                rs->createBufferObject(
                    BufferObjectBinding::SHADER_STORAGE,
                    BufferUsage::DYNAMIC,
                    maxIndices * sizeof(uint32_t),
                    "FilteredIndexBuffer");
        }

        uint32_t meshConstantsBufferSize = subMeshCount * sizeof(MeshConstants);
        meshConstantsBuffer =
            rs->createBufferObject(
                BufferObjectBinding::SHADER_STORAGE,
                BufferUsage::DYNAMIC,
                meshConstantsBufferSize,
                "meshConstantsBuffer");

        rs->updateBufferObject(meshConstantsBuffer, (const char*)meshConstants.data(), meshConstantsBufferSize);


        auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();

        Handle<HwDescriptorSetLayout> defaultLayoutHandle =
            rs->getDescriptorSetLayout(filterTrianglesProgramHandle, 0);

        Handle<HwDescriptorSetLayout> frameLayoutHandle =
            rs->getDescriptorSetLayout(filterTrianglesProgramHandle, 1);
        
        mFrameData.resize(numFrame);
        for (auto i = 0; i < numFrame; i++)
        {
            auto indirectDataBuffer =
                rs->createBufferObject(
                    BufferObjectBinding::SHADER_STORAGE,
                    BufferUsage::DYNAMIC,
                    maxIndices * sizeof(uint32_t),
                    "IndirectDataBuffer");
            mFrameData[i].indirectDataBuffer = indirectDataBuffer;

            auto perFrameConstantsBuffer = 
                rs->createBufferObject(
                    BufferObjectBinding::UNIFORM,
                    BufferUsage::DYNAMIC,
                    sizeof(PerFrameVBConstants),
                    "PerFrameVBConstants Buffer Desc");
            mFrameData[i].perFrameConstantsBuffer = perFrameConstantsBuffer;
            Handle <HwDescriptorSet> defaultDescSet = rs->createDescriptorSet(defaultLayoutHandle);
            mFrameData[i].defaultDescSet = defaultDescSet;
            rs->updateDescriptorSetBuffer(defaultDescSet, 0, &indirectDrawArgBuffer, 1);

            VertexData* vertexData = mesh->getVertexData();
            Handle<HwBufferObject> vertexDataHandle = vertexData->getBuffer(0);
            rs->updateDescriptorSetBuffer(defaultDescSet, 1, &vertexDataHandle, 1);
            rs->updateDescriptorSetBuffer(defaultDescSet, 2, &vbConstantsBuffer, 1);
            IndexData* indexData = mesh->getIndexData();
            Handle<HwBufferObject> indexDataHandle = indexData->getHandle();
            rs->updateDescriptorSetBuffer(defaultDescSet, 4, &indexDataHandle, 1);
            rs->updateDescriptorSetBuffer(defaultDescSet, 5, &meshConstantsBuffer, 1);


            Handle <HwDescriptorSet> frameDescSet = rs->createDescriptorSet(frameLayoutHandle);
            mFrameData[i].frameDescSet = frameDescSet;
            rs->updateDescriptorSetBuffer(frameDescSet, 1, &mFrameData[frameIndex].perFrameConstantsBuffer, 1);

            rs->updateDescriptorSetBuffer(frameDescSet, 3, &filterDispatchGroupDataBuffer, 1);

            rs->updateDescriptorSetBuffer(frameDescSet, 6, &mFrameData[frameIndex].indirectDataBuffer, 1);

            rs->updateDescriptorSetBuffer(frameDescSet, 8, &filteredIndexBuffer[0], NUM_CULLING_VIEWPORTS);
        }
        
        ComputePassCallback callback = [&, dispatchGroupCount](ComputePassInfo& info) {
            auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
            info.programHandle = filterTrianglesProgramHandle;
            info.computeGroup = Ogre::Vector3i(dispatchGroupCount, 1, 1);
            info.descSets.clear();
            info.descSets.push_back(mFrameData[frameIndex].defaultDescSet);
            info.descSets.push_back(mFrameData[frameIndex].frameDescSet);
            };

        auto filterTrianglesPass = createComputePass(callback);
        mPassList.push_back(filterTrianglesPass);
    }
 

    
    //draw esm shadow map

    //visibility buffer pass

    //visibility shade pass

    RenderPassInput renderInput;
    renderInput.cam = mGameCamera->getCamera();
    renderInput.color = mRenderWindow->getColorTarget();
    renderInput.depth = mRenderWindow->getDepthTarget();
    renderInput.sceneMgr = mSceneManager;
    renderInput.shadowMap = nullptr;
    renderInput.shadowPass = false;
    auto mainPass = createRenderPass(renderInput);
    mPassList.push_back(mainPass);
}
