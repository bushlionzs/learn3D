#include "OgreHeader.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"
#include "OgreMaterialManager.h"
#include "VideoManager.h"
#include "shaderManager.h"
#include "OgreResourceManager.h"
#include "glslUtil.h"
#include <OgreRoot.h>
#include <renderSystem.h>
#include <filament/DriverEnums.h>
#include <filament/DriverBase.h>

namespace Ogre {

    Material::Material(const std::string& name, bool pbr)
    {
        if (name == "3low")
        {
            int kk = 0;
        }
        mTransform = Ogre::Matrix4::IDENTITY;

        mMaterialName = name;

        mPbr = pbr;
    }


    Material::~Material()
    {

    }

    uint32_t Material::addTexture(const std::string& name, Ogre::TextureProperty* texProperty)
    {
        std::shared_ptr<TextureUnit> tu(new TextureUnit(this));

        tu->setTexture(name, texProperty);

        mTextureUnits.push_back(tu);
        return mTextureUnits.size() - 1;
    }

    uint32_t Material::addAnimTexture(const std::vector<String>& namelist, float duration)
    {
        std::shared_ptr<TextureUnit> tu(new TextureUnit(this));

        tu->setAnimtexture(namelist, duration);

        mTextureUnits.push_back(tu);

        return mTextureUnits.size() - 1;
    }

    uint32_t Material::addTexture(const Ogre::TexturePtr& tex)
    {
        std::shared_ptr<TextureUnit> tu(new TextureUnit(this));
        tu->setTexture(tex);
        mTextureUnits.push_back(tu);
        return mTextureUnits.size() - 1;
    }

    void Material::preLoad()
    {
        if (mLoad)
        {
            return;
        }
        for (auto& it : mTextureUnits)
        {
            it->preLoad();
        }
    }

    void Material::load(utils::JobSystem::Job* job)
    {
        if (mLoad)
        {
            return;
        }


        if (!mVideoName.empty())
        {

            VideoManager::getSingleton()._playVideoMaterial(mMaterialName);
        }


        for (auto& it : mTextureUnits)
        {
            if (!it->isLoaded())
            {
                it->_load(job);
            }
        }

        mLoad = true;

    }

    void Material::updateResourceState()
    {
        if (mState == ResourceState::LOADING)
        {
            bool ready = true;
            for (auto& it : mTextureUnits)
            {
                it->updateResourceState();
                if (it->getResourceState() != ResourceState::READY)
                {
                    ready = false;
                }
            }

            if (ready)
            {
                mState = ResourceState::READY;
            }
        }
    }

    bool Material::createUniformBuffer(uint32_t binding, uint32_t size)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        Handle<HwBufferObject> handle = rs->createBufferObject(BufferObjectBinding::UNIFORM, BufferUsage::STATIC, size);
        mUniformHandleMap[binding] = handle;
        return true;
    }

    bool Material::updateUniformBuffer(uint32_t binding, const char* data, uint32_t size)
    {
        auto itor = mUniformHandleMap.find(binding);
        if (itor != mUniformHandleMap.end())
        {
            auto* rs = Ogre::Root::getSingleton().getRenderSystem();
            rs->updateBufferObject(itor->second, data, size);
        }
        else
        {
            assert(false);
        }
        return true;
    }


    bool Material::isLoaded()
    {
        return mLoad;
    }

    std::shared_ptr<Material> Material::clone(const String& name)
    {
        Material* mat = new Material(name);
        *mat = *this;

        return std::shared_ptr<Material>(mat);
    }

    std::shared_ptr<TextureUnit>& Material::getTextureUnit(uint32_t index)
    {
        return mTextureUnits[index];
    }

    std::shared_ptr<TextureUnit>& Material::getTextureUnit(const String& name)
    {
        assert(false);
        return mTextureUnits[0];
    }

    int32_t Material::getTextureUnitCount()
    {
        return mTextureUnits.size();
    }

    std::vector<std::shared_ptr<TextureUnit>>& Material::getAllTexureUnit()
    {
        return mTextureUnits;
    }

    void Material::addShader(ShaderInfo& sinfo)
    {
        mShaderInfo = sinfo;
    }

    const ShaderInfo& Material::getShaderInfo()
    {
        return mShaderInfo;
    }

    void Material::scale(Real u, Real v)
    {
        mMatInfo.TexScale = Ogre::Math::makeScaleMatrix(Ogre::Vector3(u, v, 0.0f));
    }

    void Material::animation(Real u, Real v)
    {
        mAnimation = true;
        mUFactor = u;
        mVFactor = v;
    }

    void Material::updateMatInfo(PbrMaterialConstanceBuffer& mcb)
    {
        mPbrMatInfo = mcb;
    }

    PbrMaterialConstanceBuffer& Material::getMatInfo()
    {
        return mPbrMatInfo;
    }

    void Material::update(Real delta)
    {
        if (!mAnimation)
            return;
        mUOffset += mUFactor * delta;
        mVOffset += mVFactor * delta;

        if (mUOffset >= 1.0f)
        {
            mUOffset -= 1.0f;
        }

        if (mVOffset >= 1.0f)
        {
            mVOffset -= 1.0f;
        }

        mMatInfo.TexTransform = Ogre::Math::makeTranslateMatrix(Ogre::Vector3(mUOffset, mVOffset, 0.0f)).transpose();
    }

    void Material::setFresnelR0(Ogre::Vector3& fresnelR0)
    {

    }

    void Material::setRoughness(Real roughness)
    {

    }

    void Material::setDiffuseAlbedo(Ogre::Vector4& diffuseAlbedo)
    {

    }

    bool Material::hasAnimation()
    {
        return mAnimation;
    }

    Ogre::Vector2 Material::getTexAnimationOffset()
    {
        return Ogre::Vector2(mUOffset, mVOffset);
    }

    void Material::setCullMode(Ogre::CullingMode mode)
    {
        mCullingMode = mode;
    }

    Ogre::CullingMode Material::getCullMode()
    {
        return mCullingMode;
    }

    Material& Material::operator=(const Material& rhs)
    {
        mAmbient = rhs.mAmbient;
        mDiffuse = rhs.mDiffuse;
        mSpecular = rhs.mSpecular;
        mReflect = rhs.mReflect;
        mTransform = rhs.mTransform;
        mAnimation = rhs.mAnimation;
        mUOffset = rhs.mUOffset;
        mVOffset = rhs.mVOffset;
        mUFactor = rhs.mUFactor;
        mVFactor = rhs.mVFactor;
        mBlendState = rhs.mBlendState;
        mShaderInfo = rhs.mShaderInfo;
        mMatInfo = rhs.mMatInfo;
        mPbr = rhs.mPbr;
        mLoad = false;
        mWriteDepth = rhs.mWriteDepth;
        mCullingMode = rhs.mCullingMode;
        for (auto tu : rhs.mTextureUnits)
        {
            mTextureUnits.push_back(tu->clone(this));
        }
        return *this;
    }

    bool Material::isTransparent()
    {
        return false;
    }

    uint64_t Material::getHandle()
    {
        return 0;
    }

    void Material::setAmbient(float red, float green, float blue)
    {

    }

    void Material::setAmbient(const ColourValue& selfIllum)
    {

    }
    void Material::setDiffuse(float red, float green, float blue, float alpha)
    {

    }
    void Material::setDiffuse(const ColourValue& selfIllum)
    {

    }
    void Material::setSelfIllumination(float red, float green, float blue)
    {

    }
    void Material::setSpecular(float red, float green, float blue, float alpha)
    {

    }

    /// @overload
    void Material::setSpecular(const ColourValue& specular)
    {

    }

    /// @overload
    void Material::setSelfIllumination(const ColourValue& selfIllum)
    {

    }
    const ColourValue& Material::getSelfIllumination()
    {
        return ColourValue::Black;
    }

    void Material::setShininess(Real val)
    {

    }

    void Material::setFog(
        bool overrideScene,
        FogMode mode,
        const ColourValue& colour,
        Real expDensity, Real linearStart, Real linearEnd)
    {

    }

    void Material::setSceneBlending(const SceneBlendType sbt)
    {

    }

    void Material::touch()
    {

    }

    void Material::setVideoName(const String& videoName)
    {
        mVideoName = videoName;
    }

    bool Material::_isVideo()
    {
        return !mVideoName.empty();
    }

    String Material::getVideoName()
    {
        return mVideoName;
    }
}