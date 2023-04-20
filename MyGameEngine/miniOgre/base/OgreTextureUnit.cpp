#include "OgreHeader.h"
#include "OgreTextureUnit.h"
#include "OgreTextureManager.h"
#include "OgreControllerManager.h"


void TextureAnimationControllerValue::setValue(Ogre::Real value)
{
    mTexUnit->addTime(value);
}

TextureUnit::TextureUnit():
    mRotate(0),
    mUMod(0.0f),
    mVMod(0.0f),
    mU(0.0f),
    mV(0.0f),
    mUScale(1.0f),
    mVScale(1.0f)
{
    mControllerOwner = std::make_shared<TextureAnimationControllerValue>(this);
}


TextureUnit::~TextureUnit()
{
    Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
    if(mAnimController)
        controllerManager.destroyController(mAnimController);
}

void TextureUnit::setTexture(std::shared_ptr<ITexture> tex)
{
    if (mTextures.empty())
    {
        mTextures.push_back(tex);
    }
    else
    {
        mTextures[0] = tex;
    }
}

void TextureUnit::setTexture(const std::string& name, Ogre::TextureProperty* texProperty)
{
    mNameList.clear();
    mNameList.push_back(name);
    if (texProperty)
    {
        mTextureProperty = *texProperty;
    }
}

void TextureUnit::setAnimtexture(const std::vector<String>& namelist, float duration)
{
    mNameList = namelist;
    mAnimDuration = duration;
    mUseAnimation = true;
}

void TextureUnit::setTextureUScale(float u)
{
    mUScale = u;
    mRecalcTexMatrix = true;
}
void TextureUnit::setTextureVScale(float v)
{
    mVScale = v;
    mRecalcTexMatrix = true;
}

void TextureUnit::setTextureScale(float u, float v)
{
    mUScale = u;
    mVScale = v;
    mRecalcTexMatrix = true;
}

void TextureUnit::setTextureUScroll(float u)
{
    mUMod = u;
    mRecalcTexMatrix = true;
    mUseScroll = true;
}

void TextureUnit::setTextureVScroll(float v)
{
    mVMod = v;
    mRecalcTexMatrix = true;
    mUseScroll = true;
}

void TextureUnit::setTextureScroll(float u, float v)
{
    mUMod = u;
    mVMod = v;
    mRecalcTexMatrix = true;
    mUseScroll = true;
}

void TextureUnit::setTextureRotate(const Ogre::Radian& angle)
{
    mRotate = angle;
    mRecalcTexMatrix = true;
}

void TextureUnit::_load()
{
    //_unload();
    mTextures.reserve(mNameList.size());
    for (auto& name : mNameList)
    {
        auto tex = TextureManager::getSingletonPtr()->load(name, &mTextureProperty);
        mTextures.push_back(tex);
    }
    
    if (mUseAnimation || mUseScroll)
    {
        Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
        mAnimController = controllerManager.createFrameTimePassthroughController(
            mControllerOwner);
    }

    mLoad = true;
}

void TextureUnit::_unload()
{
    if (mAnimController)
    {
        ControllerManager::getSingleton().destroyController(mAnimController);
        mAnimController = nullptr;
    }

    for (auto itor = mTextures.begin(); itor != mTextures.end(); itor++)
    {
        String TexName;
        if (!(*itor))
            TexName = (*itor)->getName();
        (*itor).reset();
        if (Ogre::TextureManager::getSingletonPtr()->unloadUnreferencedResource(TexName))
        {
            Ogre::TextureManager::getSingletonPtr()->remove(TexName);
        }
                
    }
}

std::shared_ptr<ITexture> TextureUnit::getTexture()
{
    return mTextures[mTextureIndex];
}

ITexture* TextureUnit::getRaw()
{
    return mTextures[mTextureIndex].get();
}

TextureProperty* TextureUnit::getTextureProperty()
{
    return &mTextureProperty;
}

std::shared_ptr<TextureUnit> TextureUnit::clone()
{
    std::shared_ptr<TextureUnit> tu = std::make_shared<TextureUnit>();

    tu->mNameList = mNameList;
    tu->mTextureProperty = mTextureProperty;
    tu->mAnimDuration = mAnimDuration;
    return tu;
}

void TextureUnit::setColourOperationEx(
    LayerBlendOperationEx op,
    LayerBlendSource source1 ,
    LayerBlendSource source2 ,

    const ColourValue& arg1 ,
    const ColourValue& arg2 ,

    Real manualBlend)
{

}

void TextureUnit::setProjectiveTexturing(bool enable,
    const Frustum* projectionSettings)
{

}

int32_t TextureUnit::getNumFrames()
{
    return 1;
}

unsigned int TextureUnit::getCurrentFrame(void) const
{
    return 0;
}

void TextureUnit::setCurrentFrame(unsigned int frameNumber)
{

}



void TextureUnit::addTime(float delta)
{
    if (mTextures.size() > 1)
    {
        float fragment = mAnimDuration / mTextures.size();

        mAnimAccumulate += delta;

        float exist = (mTextureIndex + 1) * fragment;

        if (mAnimAccumulate >= exist)
        {
            mTextureIndex++;
            if (mTextureIndex >= mTextures.size())
            {
                mTextureIndex = 0;
            }

            if (mAnimAccumulate > mAnimDuration)
            {
                mAnimAccumulate -= mAnimDuration;
            }
        }
    }

    if (mUseScroll)
    {
        mU += mUMod * delta;
        mV += mVMod * delta;
        mRecalcTexMatrix = true;
    }
}

float TextureUnit::getAnimationDuration()
{
    return mAnimDuration;
}

String TextureUnit::getFrameTextureName(uint32_t index)
{
    return mNameList[index];
}

void TextureUnit::setAnimatedTextureName(
    const String& name,
    unsigned int numFrames,
    Real duration)
{
    String ext;
    String baseName;

    size_t pos = name.find_last_of(".");
    baseName = name.substr(0, pos);
    ext = name.substr(pos);

    mNameList.resize(numFrames);
    mTextures.resize(numFrames);

    mAnimDuration = duration;
    mTextureIndex = 0;

    for (unsigned int i = 0; i < numFrames; ++i)
    {
        std::ostringstream str;
        str << baseName << "_" << i << ext;
        mNameList[i] = str.str();
        mTextures[i].reset();
    }

    // Load immediately if Material loaded
    if (isLoaded())
    {
        _load();
    }
}

bool TextureUnit::isLoaded()
{
    return mLoad;
}

const Matrix4& TextureUnit::getTextureTransform() const
{
    if (mRecalcTexMatrix)
        recalcTextureMatrix();
    return mTexModMatrix;
}

void TextureUnit::recalcTextureMatrix() const
{
    mTexModMatrix = Ogre::Matrix4::IDENTITY;
    if (mUScale != 1 || mVScale != 1)
    {
        // Offset to center of texture
        mTexModMatrix[0][0] = 1 / mUScale;
        mTexModMatrix[1][1] = 1 / mVScale;
        // Skip matrix concat since first matrix update
        mTexModMatrix[0][3] = (-0.5f * mTexModMatrix[0][0]) + 0.5f;
        mTexModMatrix[1][3] = (-0.5f * mTexModMatrix[1][1]) + 0.5f;
    }

    if (mUseScroll)
    {
        mTexModMatrix.setTrans(Ogre::Vector3(mU, mV, 0));
    }

    //if (mRotate != Radian(0))
    //{
    //    Affine3 rot = Affine3::IDENTITY;
    //    Radian theta(mRotate);
    //    Real cosTheta = Math::Cos(theta);
    //    Real sinTheta = Math::Sin(theta);

    //    rot[0][0] = cosTheta;
    //    rot[0][1] = -sinTheta;
    //    rot[1][0] = sinTheta;
    //    rot[1][1] = cosTheta;
    //    // Offset center of rotation to center of texture
    //    rot[0][3] = 0.5f + ((-0.5f * cosTheta) - (-0.5f * sinTheta));
    //    rot[1][3] = 0.5f + ((-0.5f * sinTheta) + (-0.5f * cosTheta));

    //    xform = rot * xform;
    //}

    mRecalcTexMatrix = false;

}