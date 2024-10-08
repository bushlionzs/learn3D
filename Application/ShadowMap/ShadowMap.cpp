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
    base1();
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

    //clear buffer pass
    

    VBConstants constants[2];
    memset(&constants[0], 0, sizeof(VBConstants) * 2);
    auto* rs = mRenderSystem;
    {
        ComputePassInput computeInput;
        ShaderInfo shaderInfo;
        shaderInfo.shaderName = "clearBuffer";
        computeInput.programHandle = rs->createComputeProgram(shaderInfo);
      
        Handle<HwDescriptorSetLayout> dslh = rs->getDescriptorSetLayout(computeInput.programHandle, 0);
        computeInput.ds = rs->createDescriptorSet(dslh);

        Handle<HwBufferObject> vbconstantHandle =
            mRenderSystem->createBufferObject(BufferObjectBinding::UNIFORM, BufferUsage::STATIC, sizeof(VBConstants) * 2);
        Handle<HwBufferObject> indirectDrawHandle =
            mRenderSystem->createBufferObject(BufferObjectBinding::SHADER_STORAGE, BufferUsage::DYNAMIC, 320);
        rs->updateDescriptorSetBuffer(computeInput.ds, 0, indirectDrawHandle, 0, 320);
        rs->updateDescriptorSetBuffer(computeInput.ds, 2, vbconstantHandle, 0, sizeof(VBConstants) * 2);

        computeInput.computeGroup._x = 1;
        computeInput.computeGroup._y = 1;
        computeInput.computeGroup._z = 1;
        auto clearBufferPass = createComputePass(computeInput);
        mPassList.push_back(clearBufferPass);
    }
    
    enum
    {
        GEOMSET_OPAQUE = 0,
        GEOMSET_ALPHA_CUTOUT
    };

   
    uint32_t visibilityBufferFilteredIndexCount[NUM_GEOMETRY_SETS] = {};

    //filter triangles pass
    {
        ShaderInfo shaderInfo;
        shaderInfo.shaderName = "filterTriangles";
        Handle<HwComputeProgram> computeHandle = rs->createComputeProgram(shaderInfo);
        ComputePassInput computeInput;
        auto filterTrianglesPass = createComputePass(computeInput);

        auto numFrame = ogreConfig.swapBufferCount;

        auto subMeshCount = mesh->getSubMeshCount();

        std::vector<MeshConstants> meshConstants(subMeshCount);
        
        for (auto i = 0; i < subMeshCount; i++)
        {
            auto subMesh = mesh->getSubMesh(i);

            auto mat = subMesh->getMaterial();

            auto materialFlag = mat->getMaterialFlags();

            uint32_t geomSet = materialFlag & MATERIAL_FLAG_ALPHA_TESTED?GEOMSET_ALPHA_CUTOUT:GEOMSET_OPAQUE;

            auto indexView = subMesh->getIndexView();
            visibilityBufferFilteredIndexCount[geomSet] += indexView->mIndexCount;

            meshConstants[i].indexOffset = indexView->mIndexLocation;
            meshConstants[i].vertexOffset = indexView->mBaseVertexLocation;
            meshConstants[i].materialID = i;
            meshConstants[i].twoSided = (materialFlag & MATERIAL_FLAG_TWO_SIDED) ? 1 : 0;
        }

        uint32_t maxIndices = 0;
        for (uint32_t geomSet = 0; geomSet < NUM_GEOMETRY_SETS; ++geomSet)
        {
            maxIndices += visibilityBufferFilteredIndexCount[geomSet];
        }

        uint32_t computeThread = 256;
        auto maxFilterBatches = (maxIndices / 3) / (computeThread >> 1);

        uint32_t filterDispatchGroupSize = maxFilterBatches * sizeof(FilterDispatchGroupData);
        mFrameData.resize(numFrame);
        for (uint32_t i = 0; i < numFrame; i++)
        {
            mFrameData[i].filterDispatchGroupDataBuffer = 
                rs->createBufferObject(
                    BufferObjectBinding::SHADER_STORAGE,
                    BufferUsage::DYNAMIC,
                    filterDispatchGroupSize,
                    "FilterDispatchGroupDataBuffer");
            mFrameData[i].indirectDataBuffer =
                rs->createBufferObject(
                    BufferObjectBinding::SHADER_STORAGE,
                    BufferUsage::DYNAMIC,
                    maxIndices * sizeof(uint32_t),
                    "IndirectDataBuffer");
            
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

        indirectDrawArgBuffer = 
            rs->createBufferObject(
                BufferObjectBinding::SHADER_STORAGE,
                BufferUsage::DYNAMIC,
                NUM_GEOMETRY_SETS * NUM_CULLING_VIEWPORTS * 8 * sizeof(uint32_t),
                "IndirectDrawArgBuffer");
        uint32_t indexOffset = 0;
        for (auto i = 0; i < NUM_GEOMETRY_SETS; i++)
        {
            vbConstants[i].indexOffset = indexOffset;
            indexOffset += visibilityBufferFilteredIndexCount[i];
            vbConstantsBuffer[i] =
                rs->createBufferObject(
                    BufferObjectBinding::SHADER_STORAGE,
                    BufferUsage::DYNAMIC,
                    NUM_GEOMETRY_SETS * sizeof(VBConstants),
                    "VBConstantBuffer");
        }
       // mPassList.push_back(filterTrianglesPass);
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
