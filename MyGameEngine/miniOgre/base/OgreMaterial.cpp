#include "OgreHeader.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"
#include "OgreMaterialManager.h"
#include "VideoManager.h"

Material::Material(const std::string& name, bool pbr)
{
    mTransform = Ogre::Matrix4::IDENTITY;

    mMaterialName = name;

    mPbr = pbr;
}


Material::~Material()
{

}

void Material::addTexture(const std::string& name, Ogre::TextureProperty* texProperty)
{
    std::shared_ptr<TextureUnit> tu(new TextureUnit);

    tu->setTexture(name, texProperty);

    mTextureUnits.push_back(tu);
}

void Material::addAnimTexture(const std::vector<String>& namelist, float duration)
{
    std::shared_ptr<TextureUnit> tu(new TextureUnit);

    tu->setAnimtexture(namelist, duration);

    mTextureUnits.push_back(tu);
}

void Material::addTexture(const Ogre::TexturePtr& tex)
{
    std::shared_ptr<TextureUnit> tu(new TextureUnit);
    tu->setTexture(tex);
    mTextureUnits.push_back(tu);
}

void Material::load()
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
        if(!it->isLoaded())
            it->_load();
    }
    
    mShader = MaterialManager::getSingletonPtr()->buildShader(mShaderInfo);

    mShader->load();

    mLoad = true;
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

const std::vector<std::shared_ptr<TextureUnit>>& Material::getAllTexureUnit() const 
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
    mMatInfo.TexScale = Ogre::Math::makeScaleMatrix(Ogre::Vector3(u,v,0.0f));
}

void Material::animation(Real u, Real v)
{
    mAnimation = true;
    mUFactor = u;
    mVFactor = v;
}

void Material::updateMatInfo(MaterialConstantBuffer& mcb)
{
    mMatInfo = mcb;
}

const MaterialConstantBuffer& Material::getMatInfo()
{
    return mMatInfo;
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
    mMatInfo.FresnelR0 = fresnelR0;
}

void Material::setRoughness(Real roughness)
{
    mMatInfo.Roughness = roughness;
}

void Material::setDiffuseAlbedo(Ogre::Vector4& diffuseAlbedo)
{
    mMatInfo.DiffuseAlbedo = diffuseAlbedo;
}

bool Material::hasAnimation()
{
    return mAnimation;
}

Ogre::Vector2 Material::getTexAnimationOffset()
{
    return Ogre::Vector2(mUOffset, mVOffset);
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

    for (auto tu : rhs.mTextureUnits)
    {
        mTextureUnits.push_back(tu->clone());
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
    FogMode mode ,
    const ColourValue& colour,
    Real expDensity , Real linearStart , Real linearEnd )
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