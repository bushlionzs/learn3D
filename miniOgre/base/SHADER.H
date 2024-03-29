#pragma once

#include "OgreLight.h"
#include "OgreColourValue.h"

struct ObjectConstantBuffer
{
    Ogre::Matrix4 world;
    Ogre::Matrix4 projector;
    Ogre::Matrix4 worldViewProj;
};

#define MaxLightsEachType 4



struct TestConstantBuffer
{
    Ogre::Matrix4 world = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 view = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 proj = Ogre::Matrix4::IDENTITY;
};

struct LightInfo
{
    Ogre::Vector3 Strength = { 0.5f, 0.5f, 0.5f };
    float FalloffStart = 1.0f;                          // point/spot light only
    Ogre::Vector3 Direction = { 0.0f, -1.0f, 0.0f };// directional/spot light only
    float FalloffEnd = 10.0f;                           // point/spot light only
    Ogre::Vector3 Position = { 0.0f, 0.0f, 0.0f };  // point/spot light only
    float SpotPower = 64.0f;                            // spot light only
};
struct FrameConstantBuffer
{
    Ogre::Matrix4 View = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 InvView = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 Proj = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 InvProj = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 ViewProj = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 InvViewProj = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 ShadowTransform = Ogre::Matrix4::IDENTITY;
    Ogre::Vector3 EyePosW = { 0.0f, 0.0f, 0.0f };
    uint32_t Shadow = 0;
    Ogre::Vector2 RenderTargetSize = { 0.0f, 0.0f };
    Ogre::Vector2 InvRenderTargetSize = { 0.0f, 0.0f };
    float NearZ = 0.0f;
    float FarZ = 0.0f;
    float TotalTime = 0.0f;
    float DeltaTime = 0.0f;

    Ogre::ColourValue AmbientLight = ColourValue(0.45f, 0.45f, 0.45f, 1.0f);
    LightInfo directionLights[MaxLightsEachType];
    LightInfo pointLights[MaxLightsEachType];
    LightInfo spotLights[MaxLightsEachType];
};

struct MaterialConstantBuffer
{
    Ogre::Vector4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
    Ogre::Vector3 FresnelR0 = { 0.98f, 0.97f, 0.95f };
    float Roughness = 0.1f;

    // Used in texture mapping.
    Ogre::Matrix4 TexScale = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 TexTransform = Ogre::Matrix4::IDENTITY;
    uint32_t DiffuseMapIndex = 0;
    uint32_t MaterialPad0;
    uint32_t MaterialPad1;
    uint32_t MaterialPad2;
};


struct PbrMaterialConstanceBuffer
{
    //some constance value;
    Ogre::Vector2 u_MetallicRoughnessValues = {1.0f, 1.0f};
    Real u_OcclusionStrength = 1.0f;
    Real Pad1;
    Ogre::Vector3 u_EmissiveFactor = { 1.0f, 1.0f, 1.0f };
    Real Pad2;
    Ogre::Vector4 u_BaseColorFactor = { 1.0f, 1.0f, 1.0f, 1.0f };
    Ogre::Vector4 u_ScaleIBLAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
    Ogre::Matrix4 TexScale = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 TexTransform = Ogre::Matrix4::IDENTITY;
};

class SkinnedConstantBuffer
{
public:
    Ogre::Matrix4 BoneTransforms[200];
};

struct ShaderInfo
{
    String shaderName;
    std::vector<std::pair<std::string,std::string>> shaderMacros;
};

class Shader
{
public:
    Shader();
    virtual ~Shader();

    virtual bool load() = 0;
};