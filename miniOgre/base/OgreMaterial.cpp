#include "OgreHeader.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"
#include "OgreMaterialManager.h"
#include "VideoManager.h"
#include "shaderManager.h"
#include "OgreResourceManager.h"
#include "glslUtil.h"
#include <OgreRoot.h>
#include <filament/Program.h>
#include <filament/FEngine.h>
#include <filament/DriverEnums.h>
#include <filament/DriverBase.h>
#include <filament/FTexture.h>
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
        if (job)
        {
            if (mState > ResourceState::NONE)
            {
                return;
            }

            mState = ResourceState::LOADING;

            for (auto& it : mTextureUnits)
            {
                it->_load(job);
            }

            auto* engine = Ogre::Root::getSingleton().getEngine();

            backend::Program p(mMaterialName.c_str());
            Ogre::ShaderPrivateInfo* privateInfo =
                ShaderManager::getSingleton().getShader(mShaderInfo.shaderName, EngineType_Vulkan);

            String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
            auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);

            std::string vertexSpv;

            glslCompileShader(
                vertexSpv,
                res->_fullname,
                *vertexContent,
                privateInfo->vertexShaderEntryPoint,
                mShaderInfo.shaderMacros,
                shaderc_glsl_vertex_shader);

            p.shader(backend::ShaderStage::VERTEX, vertexSpv.data(), vertexSpv.size());

            String* fragContent = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);
            res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);
            std::string fragSpv;

            glslCompileShader(
                fragSpv,
                res->_fullname,
                *fragContent,
                privateInfo->fragShaderEntryPoint,
                mShaderInfo.shaderMacros,
                shaderc_glsl_fragment_shader);

            p.shader(backend::ShaderStage::FRAGMENT, fragSpv.data(), fragSpv.size());

            p.shaderLanguage(backend::ShaderLanguage::SPIRV);

            utils::FixedCapacityVector<std::pair<utils::CString, uint8_t>>  uniformBlockBindings(4);

            uniformBlockBindings[0] = {"ObjectUniforms", 0};
            uniformBlockBindings[1] = { "FrameUniforms", 1 };
            uniformBlockBindings[2] = { "MaterialUniforms", 2 };
            uniformBlockBindings[3] = { "SkinnedUniforms", 3 };

            p.uniformBlockBindings(uniformBlockBindings);
            std::array<backend::Program::Sampler, backend::MAX_SAMPLER_COUNT> samplers{};

            samplers[0] = {"first", 0};
            samplers[1] = { "second", 1 };
            samplers[2] = { "third", 2 };
            samplers[3] = { "gCubeMap", 3 };

            

            if (mMaterialName == "Â¥À¼µØ¹¬Ç½012")
            {
                int kk = 0;
            }

            uint32_t samplerCount = 0;
            uint32_t samplerCubeCount = 0;
            for (uint32_t i = 0; i < mTextureUnits.size(); i++)
            {
                if (mTextureUnits[i]->getTextureProperty()->_texType == TEX_TYPE_CUBE_MAP)
                {
                    samplerCubeCount++;
                }
                else
                {
                    samplerCount++;
                }
            }

            p.setSamplerGroup(0, backend::ShaderStageFlags::FRAGMENT, samplers.data(), samplerCount);

            if (samplerCubeCount > 0)
            {
                p.setSamplerGroup(1, backend::ShaderStageFlags::FRAGMENT, samplers.data() + 3, 1);
            }
            

            if (samplerCount > 0)
            {
                if (samplerCount == 3)
                {
                    int kk = 0;
                }
                mSamplerHandle = engine->getDriverApi().createSamplerGroup(
                    samplerCount, utils::FixedSizeString<32>(mMaterialName.c_str()));

                uint32_t index = 0;
                backend::SamplerGroup sg(samplerCount);
                for (uint32_t i = 0; i < mTextureUnits.size(); i++)
                {
                    backend::SamplerDescriptor sd;
                    FTexture* ftex = (FTexture*)mTextureUnits[i]->getFTexture();
                    sd.t = ftex->getHwHandle();
                    sd.s.filterMag = filament::backend::SamplerMagFilter::LINEAR;
                    sd.s.filterMin = filament::backend::SamplerMinFilter::LINEAR;
                    sd.s.wrapR = filament::backend::SamplerWrapMode::REPEAT;
                    sd.s.wrapS = filament::backend::SamplerWrapMode::REPEAT;
                    sd.s.wrapT = filament::backend::SamplerWrapMode::REPEAT;
                    if (mTextureUnits[i]->getTextureProperty()->_texType == TEX_TYPE_2D)
                    {
                        sg.setSampler(index++, sd);
                    }

                }

                engine->getDriverApi().updateSamplerGroup(mSamplerHandle, sg.toBufferDescriptor(engine->getDriverApi()));
            }
            

            if (samplerCubeCount > 0)
            {
                mSamplerCubeHandle = engine->getDriverApi().createSamplerGroup(
                    samplerCubeCount, utils::FixedSizeString<32>(mMaterialName.c_str()));

                uint32_t index = 0;
                backend::SamplerGroup sg(samplerCubeCount);
                for (uint32_t i = 0; i < mTextureUnits.size(); i++)
                {
                    backend::SamplerDescriptor sd;
                    FTexture* ftex = (FTexture*)mTextureUnits[i]->getFTexture();
                    sd.t = ftex->getHwHandle();
                    sd.s.filterMag = filament::backend::SamplerMagFilter::LINEAR;
                    sd.s.filterMin = filament::backend::SamplerMinFilter::LINEAR;
                    sd.s.wrapR = filament::backend::SamplerWrapMode::REPEAT;
                    sd.s.wrapS = filament::backend::SamplerWrapMode::REPEAT;
                    sd.s.wrapT = filament::backend::SamplerWrapMode::REPEAT;
                    if (mTextureUnits[i]->getTextureProperty()->_texType == TEX_TYPE_CUBE_MAP)
                    {
                        sg.setSampler(index++, sd);
                    }

                }

                engine->getDriverApi().updateSamplerGroup(mSamplerCubeHandle, sg.toBufferDescriptor(engine->getDriverApi()));
            }

            mProgram = engine->getDriverApi().createProgram(std::move(p));

            mMaterialBufferHandle = engine->getDriverApi().createBufferObject(sizeof(MaterialConstantBuffer), backend::BufferObjectBinding::UNIFORM, backend::BufferUsage::DYNAMIC);

            engine->getDriverApi().updateBufferObject(mMaterialBufferHandle, backend::BufferDescriptor(&mMatInfo, sizeof(MaterialConstantBuffer)), 0);
        }
        else
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

            mShader = MaterialManager::getSingletonPtr()->buildShader(mShaderInfo);

            mShader->load();

            mLoad = true;
        }

    }


    void Material::bindSamplerGroup()
    {
        auto* engine = Ogre::Root::getSingleton().getEngine();
        if (mSamplerHandle)
        {
            engine->getDriverApi().bindSamplers(0, mSamplerHandle);
        }

        if (mSamplerCubeHandle)
        {
            engine->getDriverApi().bindSamplers(1, mSamplerCubeHandle);
        }
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

    const std::shared_ptr<Shader>& Material::getShader() const
    {
        return mShader;
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