#pragma once

#include "OgreSingleton.h"
#include "OgreTexture.h"
#include "OgrePixelFormat.h"

namespace filament
{
    struct TextureInfo;
}

namespace Ogre {
    enum class CacheResult {
        NOT_EXIST,
        NOT_READY,
        FOUND,
        MISS,
    };
    static const intptr_t DECODING_NOT_READY = 0x0;
    static const intptr_t DECODING_ERROR = 0x1;
    class TextureManager : public Ogre::Singleton<TextureManager>
    {
        using TextureCache = tsl::robin_map<String, Texture*>;
    public:
        TextureManager();
        ~TextureManager();

        std::shared_ptr<OgreTexture> load(
            const String& name, 
            TextureProperty* texProperty,
            bool read = true);
        std::shared_ptr<OgreTexture> loadImage(
            const String& name, 
            const CImage& img,
            TextureType texType = TEX_TYPE_2D,
            int numMipmaps = -1, 
            Real gamma = 1.0f, 
            bool isAlpha = false,
            PixelFormat desiredFormat = PF_UNKNOWN, 
            bool hwGammaCorrection = false);

        std::pair<Texture*, CacheResult> getOrCreateTexture(const String& name);
        void remove(const std::string& name);
        std::shared_ptr<OgreTexture> getByName(const String& name, const String& group = BLANKSTRING) const;

        virtual TexturePtr createManual(const String& name, TextureProperty& texProperty);

        virtual TexturePtr loadRawData(const String& name, DataStreamPtr& stream, TextureProperty& texProperty);

        virtual bool isFormatSupported(Ogre::TextureType ttype, Ogre::PixelFormat format, int usage);

        bool unloadUnreferencedResource(const String& name);

        void updateTextures();
    private:
        std::unordered_map<std::string, std::shared_ptr<OgreTexture>> mTexMap;

        TextureCache mTextureCache;

        std::vector<std::unique_ptr<TextureInfo> > mTextureInfos;

        Engine* mEngine;

        utils::JobSystem::Job* mDecoderRootJob = nullptr;
    };
}