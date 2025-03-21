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

        uint32_t addTexture(const std::string& texFileName, Ogre::TextureProperty* texProperty = nullptr);
        uint32_t addTexture(const Ogre::TexturePtr& tex);
        uint32_t addAnimTexture(const std::vector<String>& namelist, float duration);
        
        void preLoad();
        void load(utils::JobSystem::Job* job);
        bool isLoaded();

        std::shared_ptr<Material> clone(const String& name);
        std::shared_ptr<TextureUnit>& getTextureUnit(uint32_t index);
        std::shared_ptr<TextureUnit>& getTextureUnit(const char* name);

        bool hasTextureUnit(const char* name);
       
        int32_t getTextureUnitCount();
        std::vector<std::shared_ptr<TextureUnit>>& getAllTexureUnit();
        OgreTexture* getPbrTexture(TextureTypePbr type);
        OgreTexture* getTexture(uint32_t index);
        void addShader(ShaderInfo& sinfo);

        ShaderInfo& getShaderInfo();

        void scale(Real u, Real v);
        void animation(Real u, Real v);

        PbrMaterialConstanceBuffer& getPbrMatInfo();
        GeneralMaterialConstantBuffer& getMatInfo();
        void update(Real delta);
        void setFresnelR0(Ogre::Vector3& fresnelR0);
        void setRoughness(Real roughness);

        const Ogre::Vector3& getDiffuseColor();
        void setDiffuseColor(const Ogre::Vector3& diffuseColor);
        const Ogre::Vector3& getSpecularColor();
        void setSpecularColor(const Ogre::Vector3& specularColor);
        const Ogre::Vector3& getEmissiveColor();
        void setEmissiveColor(const Ogre::Vector3& emissiveColor);
        float getOpacity();
        void setOpacity(float opacity);
        float getShininess();
        void setShininess(float shininess);
        bool hasAnimation();
        Ogre::Vector2 getTexAnimationOffset();
        const Ogre::ColourBlendState& getBlendState() const;

        void setBlendState(Ogre::ColourBlendState& state);

        void setCullMode(filament::backend::CullingMode mode);
        filament::backend::CullingMode getCullMode();

        bool isPbr() const
        {
            return mPbr;
        }

        const String& getName() const
        {
            return mMaterialName;
        }

        void setName(const std::string& name)
        {
            mMaterialName = name;
        }

        void setMaterialFlags(uint32_t flags)
        {
            mMaterialFlags = flags;
        }

        uint32_t getMaterialFlags()
        {
            return mMaterialFlags;
        }

        bool isDepthTest();

        void setDepthTest(bool test);

        bool isWriteDepth();
        void setWriteDepth(bool bWrite);
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

        filament::backend::RasterState& getRasterState()
        {
            return mRasterState;
        }

        void updateVertexDeclaration(VertexDeclaration* decl)
        {
            mVertexDeclaration = decl;
        }
        filament::backend::Handle<filament::backend::HwPipeline> getPipeline()
        {
            return mPipelineHandle;
        }
        filament::backend::Handle<filament::backend::HwProgram> getProgram()
        {
            return mProgramHandle;
        }

    private:
        void createFrameResourceInfo();
    private:
        std::string mMaterialName;
 
        uint32_t mMaterialFlags = 0;
        bool mAnimation = false;
        float mUOffset = 0.0f;
        float mVOffset = 0.0f;
        float mUFactor = 0.1f;
        float mVFactor = 0.02f;

        std::vector<std::shared_ptr<TextureUnit>> mTextureUnits;
        ShaderInfo mShaderInfo;
        PbrMaterialConstanceBuffer mPbrMatInfo;
        GeneralMaterialConstantBuffer mMatInfo;

        Ogre::Vector3 mDiffuseColor = Ogre::Vector3(1.0f);
        Ogre::Vector3 mSpecularColor = Ogre::Vector3(1.0f);
        Ogre::Vector3 mEmissiveColor = Ogre::Vector3(0.0f);
        float mOpacity = 1.0f;
        float mShininess = 0.0f;
        bool mPbr;
        bool mLoad = false;

        Ogre::ColourBlendState mBlendState;

        ResourceState mState = ResourceState::ResourceState_None;

        
        
        filament::backend::RasterState mRasterState;
        filament::backend::Handle<filament::backend::HwPipeline> mPipelineHandle;
        filament::backend::Handle<filament::backend::HwProgram> mProgramHandle;
        filament::backend::Handle<filament::backend::HwDescriptorSetLayout> mUboLayoutHandle;
        filament::backend::Handle<filament::backend::HwDescriptorSetLayout> mSamplerLayoutHandle;

        VertexDeclaration* mVertexDeclaration = nullptr;
    };
}