#pragma once

#include <unordered_map>
#include "shader.h"
#include "engine_struct.h"
#include "OgreBlendMode.h"
#include "OgreCommon.h"
#include "OgreTexture.h"
#include <filament/Handle.h>
#include <filament/DriverEnums.h>
#include <filament/DriverBase.h>

class TextureUnit;
class VertexDeclaration;
class MaterialInfo
{
public:
    std::string mTexname;
    float mTexScale = 1.0f;
    bool mCube = false;
    std::string mVSname="basic.hlsl";
    std::string mPSname="basic.hlsl";
    GeneralMaterialConstantBuffer mMatInfo;
};

namespace Ogre {
    class Material
    {
    public:
        Material(const std::string& name, bool pbr = false);
        ~Material();

        uint32_t addTexture(const std::string& name, Ogre::TextureProperty* texProperty = nullptr);
        uint32_t addAnimTexture(const std::vector<String>& namelist, float duration);
        uint32_t addTexture(const Ogre::TexturePtr& tex);
        void preLoad();
        void load(utils::JobSystem::Job* job);
        bool isLoaded();

        std::shared_ptr<Material> clone(const String& name);
        std::shared_ptr<TextureUnit>& getTextureUnit(uint32_t index);
        std::shared_ptr<TextureUnit>& getTextureUnit(const String& name);
       
        int32_t getTextureUnitCount();
        std::vector<std::shared_ptr<TextureUnit>>& getAllTexureUnit();

        void addShader(ShaderInfo& sinfo);

        const ShaderInfo& getShaderInfo();

        void scale(Real u, Real v);
        void animation(Real u, Real v);

        PbrMaterialConstanceBuffer& getMatInfo();
        void update(Real delta);
        void setFresnelR0(Ogre::Vector3& fresnelR0);
        void setRoughness(Real roughness);
        void setDiffuseAlbedo(Ogre::Vector4& diffuseAlbedo);

        bool hasAnimation();
        Ogre::Vector2 getTexAnimationOffset();
        const Ogre::ColourBlendState& getBlendState() const;

        void setBlendState(Ogre::ColourBlendState& state);

        void setCullMode(Ogre::CullingMode mode);
        Ogre::CullingMode getCullMode();

        bool isPbr() const
        {
            return mPbr;
        }

        const String& getName() const
        {
            return mMaterialName;
        }

        bool isDepthTest()
        {
            return mDepthTest;
        }

        void setDepthTest(bool test)
        {
            mDepthTest = test;
        }
        bool isWriteDepth()
        {
            return mWriteDepth;
        }
        void setWriteDepth(bool bWrite)
        {
            mWriteDepth = bWrite;
        }
        Material& operator=(const Material& rhs);

        bool isTransparent();

        ResourceState getResourceState()
        {
            return mState;
        }
        void updateResourceState();

        void setResourceState(ResourceState rs)
        {
            mState = rs;
        }

        RasterState& getRasterState()
        {
            return mRasterState;
        }

        void updateVertexDeclaration(VertexDeclaration* decl)
        {
            mVertexDeclaration = decl;
        }
        Handle<HwPipeline> getPipeline()
        {
            return mPipelineHandle;
        }
        Handle<HwProgram> getProgram()
        {
            return mProgramHandle;
        }

        FrameResourceInfo* getFrameResourceInfo(uint32_t frameIndex);
    private:
        void createFrameResourceInfo();
    private:
        std::string mMaterialName;
  
        bool mAnimation = false;
        float mUOffset = 0.0f;
        float mVOffset = 0.0f;
        float mUFactor = 0.1f;
        float mVFactor = 0.02f;

        std::vector<std::shared_ptr<TextureUnit>> mTextureUnits;
        ShaderInfo mShaderInfo;
        PbrMaterialConstanceBuffer mPbrMatInfo;
        GeneralMaterialConstantBuffer mMatInfo;
        bool mPbr;
        bool mHasSkinData = false;
        bool mLoad = false;

        bool mWriteDepth = true;

        bool mDepthTest = true;

        Ogre::ColourBlendState mBlendState;

        Ogre::CullingMode mCullingMode = CULL_CLOCKWISE;

        ResourceState mState = ResourceState::ResourceState_None;

        std::vector<FrameResourceInfo> mFrameResourceInfoList;
        
        RasterState mRasterState;
        Handle<HwPipeline> mPipelineHandle;
        Handle<HwProgram> mProgramHandle;
        Handle<HwDescriptorSetLayout> mUboLayoutHandle;
        Handle<HwDescriptorSetLayout> mSamplerLayoutHandle;

        VertexDeclaration* mVertexDeclaration = nullptr;
    };
}