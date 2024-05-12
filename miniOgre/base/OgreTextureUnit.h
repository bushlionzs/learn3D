#pragma once

#include "OgreTexture.h"
#include "engine_struct.h"
#include "OgreBlendMode.h"
#include "OgreController.h"
#include <filament/Texture.h>
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

enum TextureEffectType
{
    /// Generate all texture coords based on angle between camera and vertex
    ET_ENVIRONMENT_MAP,
    /// Generate texture coords based on a frustum
    ET_PROJECTIVE_TEXTURE,
    /// Constant u/v scrolling effect
    ET_UVSCROLL,
    /// Constant u scrolling effect
    ET_USCROLL,
    /// Constant u/v scrolling effect
    ET_VSCROLL,
    /// Constant rotation
    ET_ROTATE,
    /// More complex transform
    ET_TRANSFORM

};

/** Internal structure defining a texture effect.
        */
struct TextureEffect {
    TextureEffectType type;
    int subtype;
    Real arg1, arg2;
    WaveformType waveType;
    Real base;
    Real frequency;
    Real phase;
    Real amplitude;
    Controller<Real>* controller;
    const Frustum* frustum;
};

class TextureUnit
{
public:
    TextureUnit(Ogre::Material* owner);
    ~TextureUnit();

    void setTexture(std::shared_ptr<OgreTexture> tex);
    void setTexture(uint32_t index, std::shared_ptr<OgreTexture> tex);
    void setTexture(const std::string& name, Ogre::TextureProperty* texProperty);
    void setAnimtexture(const std::vector<String>& namelist, float duration);
    void setTextureUScale(float u);
    void setTextureVScale(float v);
    void setTextureScale(float u, float v);
    void setTextureUScroll(float u);
    void setTextureVScroll(float v);
    void setTextureScroll(float u, float v);
    void setTextureRotate(const Ogre::Radian& angle);
    void preLoad();
    void _load(utils::JobSystem::Job* job);
    void _unload();
    ResourceState getResourceState()
    {
        return mResourceState;
    }
    void updateResourceState();

    std::shared_ptr<OgreTexture> getTexture();
    OgreTexture* getRaw();
    TextureProperty* getTextureProperty();

    std::shared_ptr<TextureUnit> clone(Ogre::Material* owner);

    void setColourOperationEx(
        LayerBlendOperationEx op,
        LayerBlendSource source1 = LBS_TEXTURE,
        LayerBlendSource source2 = LBS_CURRENT,

        const ColourValue& arg1 = ColourValue::White,
        const ColourValue& arg2 = ColourValue::White,

        Real manualBlend = 0.0);

    void setProjectiveTexturing(bool enable,
        const Frustum* projectionSettings);
    void addEffect(TextureEffect& effect);
    void removeEffect(const TextureEffectType type);
    void createEffectController(TextureEffect& effect);
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

    /** Texture effects in a multimap paired array
       */
    typedef std::multimap<TextureEffectType, TextureEffect, std::less<TextureEffectType> > EffectMap;

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
    Ogre::Radian mCurrentRotate;
    mutable Matrix4 mTexModMatrix;
    mutable bool mRecalcTexMatrix = true;

    //
    EffectMap mEffects;

    Ogre::Material* mOwner;


    //
    std::vector<Texture*> mFTextures;
    ResourceState mResourceState = ResourceState::NONE;
};