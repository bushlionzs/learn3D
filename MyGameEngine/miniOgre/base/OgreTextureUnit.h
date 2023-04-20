#pragma once

#include "texture.h"
#include "engine_struct.h"
#include "OgreBlendMode.h"
#include "OgreController.h"
class TextureUnit;
class TextureAnimationControllerValue : public Ogre::ControllerValue<Real>
{
protected:
    TextureUnit* mTexUnit;

public:
    TextureAnimationControllerValue(TextureUnit* unit)
        : mTexUnit(unit)
    {
    }

    Ogre::Real getValue(void) const
    {
        return 0;
    }

    void setValue(Ogre::Real value);
};

class TextureUnit
{
public:
    TextureUnit();
    ~TextureUnit();

    void setTexture(std::shared_ptr<ITexture> tex);
    void setTexture(const std::string& name, Ogre::TextureProperty* texProperty);
    void setAnimtexture(const std::vector<String>& namelist, float duration);
    void setTextureUScale(float u);
    void setTextureVScale(float v);
    void setTextureScale(float u, float v);
    void setTextureUScroll(float u);
    void setTextureVScroll(float v);
    void setTextureScroll(float u, float v);
    void setTextureRotate(const Ogre::Radian& angle);
    void _load();
    void _unload();
    std::shared_ptr<ITexture> getTexture();
    ITexture* getRaw();
    TextureProperty* getTextureProperty();

    std::shared_ptr<TextureUnit> clone();

    void setColourOperationEx(
        LayerBlendOperationEx op,
        LayerBlendSource source1 = LBS_TEXTURE,
        LayerBlendSource source2 = LBS_CURRENT,

        const ColourValue& arg1 = ColourValue::White,
        const ColourValue& arg2 = ColourValue::White,

        Real manualBlend = 0.0);

    void setProjectiveTexturing(bool enable,
        const Frustum* projectionSettings);

    int32_t getNumFrames();

    unsigned int getCurrentFrame(void) const;
    void setCurrentFrame(unsigned int frameNumber);

    void addTime(float delta);

    float getAnimationDuration();
    String getFrameTextureName(uint32_t index);
    void setAnimatedTextureName(
        const String& name,
        unsigned int numFrames,
        Real duration = 0);

    bool isLoaded();

    const Matrix4& getTextureTransform() const;
    void recalcTextureMatrix() const;
private:
    std::vector<TexturePtr> mTextures;
    std::vector<String> mNameList;

    int32_t mTextureIndex = 0;
    float mAnimDuration = 0.0f;
    bool mUseAnimation = false;
    bool mUseScroll = false;
    float mAnimAccumulate = 0.0f;
    Ogre::ControllerReal* mAnimController = nullptr;
    std::shared_ptr<TextureAnimationControllerValue> mControllerOwner;
    bool mLoad = false;
    TextureProperty mTextureProperty;

    Real mUMod, mVMod;

    Real mU, mV;
    Real mUScale, mVScale;
    Ogre::Radian mRotate;
    mutable Matrix4 mTexModMatrix;
    mutable bool mRecalcTexMatrix = true;
};