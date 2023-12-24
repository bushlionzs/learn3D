#pragma once

#include "shader.h"
#include "engine_struct.h"
#include "OgreBlendMode.h"
#include "OgreCommon.h"
#include "texture.h"
class TextureUnit;

class MaterialInfo
{
public:
    std::string mTexname;
    float mTexScale = 1.0f;
    bool mCube = false;
    std::string mVSname="basic.hlsl";
    std::string mPSname="basic.hlsl";
    MaterialConstantBuffer mMatInfo;
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
        void load();
        bool isLoaded();

        std::shared_ptr<Material> clone(const String& name);
        std::shared_ptr<TextureUnit>& getTextureUnit(uint32_t index);
        std::shared_ptr<TextureUnit>& getTextureUnit(const String& name);
       
        int32_t getTextureUnitCount();
        std::vector<std::shared_ptr<TextureUnit>>& getAllTexureUnit();

        void addShader(ShaderInfo& sinfo);
        const std::shared_ptr<Shader>& getShader() const;

        void scale(Real u, Real v);
        void animation(Real u, Real v);

        void updateMatInfo(MaterialConstantBuffer& mcb);
        const MaterialConstantBuffer& getMatInfo();
        void update(Real delta);
        void setFresnelR0(Ogre::Vector3& fresnelR0);
        void setRoughness(Real roughness);
        void setDiffuseAlbedo(Ogre::Vector4& diffuseAlbedo);

        bool hasAnimation();
        Ogre::Vector2 getTexAnimationOffset();
        const Ogre::ColourBlendState& getBlendState() const
        {
            return mBlendState;
        }

        void setBlendState(Ogre::ColourBlendState& state)
        {
            mBlendState = state;
        }

        void setCullMode(Ogre::CullingMode mode);
        Ogre::CullingMode getCullMode();

        const Ogre::Matrix4& getTransform() const
        {
            return mTransform;
        }

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

        uint64_t getHandle();

        void setAmbient(float red, float green, float blue);
        void setAmbient(const ColourValue& selfIllum);
        void setDiffuse(float red, float green, float blue, float alpha);
        void setDiffuse(const ColourValue& selfIllum);
        void setSelfIllumination(float red, float green, float blue);
        void setSpecular(float red, float green, float blue, float alpha);

        /// @overload
        void setSpecular(const ColourValue& specular);

        /// @overload
        void setSelfIllumination(const ColourValue& selfIllum);
        const ColourValue& getSelfIllumination();

        void setShininess(Real val);

        void setFog(
            bool overrideScene,
            FogMode mode = FOG_NONE,
            const ColourValue& colour = ColourValue::White,
            Real expDensity = 0.001f, Real linearStart = 0.0f, Real linearEnd = 1.0f);

        void setSceneBlending(const SceneBlendType sbt);

        void touch();

        //for video material
        void setVideoName(const String& videoName);
        bool _isVideo();
        String getVideoName();
    private:
        std::string mMaterialName;
        Ogre::Vector4 mAmbient;
        Ogre::Vector4 mDiffuse;
        Ogre::Vector4 mSpecular;
        Ogre::Vector4 mReflect;
        Ogre::Matrix4 mTransform;

        bool mAnimation = false;
        float mUOffset = 0.0f;
        float mVOffset = 0.0f;
        float mUFactor = 0.1f;
        float mVFactor = 0.02f;

        std::vector<std::shared_ptr<TextureUnit>> mTextureUnits;

        std::shared_ptr<Shader> mShader;

        ShaderInfo mShaderInfo;
        MaterialConstantBuffer mMatInfo;

        bool mPbr;

        bool mLoad = false;

        bool mWriteDepth = true;

        bool mDepthTest = true;

        String mVideoName;
        Ogre::ColourBlendState mBlendState;

        Ogre::CullingMode mCullingMode = CULL_CLOCKWISE;
    };
}