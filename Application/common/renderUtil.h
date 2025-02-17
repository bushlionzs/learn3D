#pragma once
#include <OgreRenderable.h>
#include <OgreCommon.h>
#include <DriverBase.h>
#include <engine_struct.h>

class GameCamera;
struct UserDefineShader;
using RenderableInitCallback = std::function< void(uint32_t frameIndex, Ogre::Renderable* r)>;
using RenderableUpdateCallback = std::function< void(Ogre::Renderable* r)>;
using RenderableBindCallback = std::function< void(uint32_t frameIndex, Ogre::Renderable*r)>;
using RenderableDrawCallback = std::function< void(uint32_t frameIndex, Ogre::Renderable* r)>;

struct UserDefineShader
{
    RenderableInitCallback initCallback;
    RenderableDrawCallback drawCallback;
    RenderableBindCallback bindCallback;
};

struct FrameResourceInfo
{
    filament::backend::Handle<filament::backend::HwDescriptorSet> zeroSet;
    filament::backend::Handle<filament::backend::HwDescriptorSet> firstSet;
    filament::backend::Handle<filament::backend::HwDescriptorSet> zeroShadowSet;
    filament::backend::Handle<filament::backend::HwBufferObject>  modelObjectHandle;
    filament::backend::Handle<filament::backend::HwBufferObject>  matObjectHandle;
    filament::backend::Handle<filament::backend::HwBufferObject>  skinObjectHandle;
    bool update;
};

void initFrameResource(uint32_t frameIndex, Ogre::Renderable* r);

void updateFrameResource(uint32_t frameIndex, Ogre::Renderable* r);

void updateMaterialInfo(Ogre::Renderable* r, bool updateTexture);


void renderScene(
    Ogre::ICamera* cam,
    Ogre::SceneManager* sceneManager,
    RenderPassInfo& renderPassInfo,
    UserDefineShader* userDefineShader);

void renderScene(
    Ogre::ICamera* cam,
    const std::vector<Ogre::Renderable*>& renderList,
    RenderPassInfo& renderPassInfo,
    UserDefineShader* userDefineShader);

void updateFrameData(
    Ogre::ICamera* camera,
    Ogre::ICamera* light,
    FrameConstantBuffer& frameConstantBuffer);

struct BaseVertex
{
    Ogre::Vector3 position;
    Ogre::Vector3 normal;
};

bool createManualMesh(
    const std::string& name,
    std::vector<BaseVertex>& vertices,
    std::vector<uint16_t>& indices);