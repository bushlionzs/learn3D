#pragma once

#include "OgreSingleton.h"
#include "texture.h"
#include "OgrePixelFormat.h"

namespace Ogre {
    class TextureManager : public Ogre::Singleton<TextureManager>
    {
    public:
        TextureManager();
        ~TextureManager();

        std::shared_ptr<ITexture> load(
            const String& name, 
            TextureProperty* texProperty);
        std::shared_ptr<ITexture> loadImage(
            const String& name, 
            const CImage& img,
            TextureType texType = TEX_TYPE_2D,
            int numMipmaps = -1, 
            Real gamma = 1.0f, 
            bool isAlpha = false,
            PixelFormat desiredFormat = PF_UNKNOWN, 
            bool hwGammaCorrection = false);
        void remove(const std::string& name);
        std::shared_ptr<ITexture> getByName(const String& name, const String& group = BLANKSTRING) const;

        virtual TexturePtr createManual(const String& name, TextureProperty& texProperty);

        virtual bool isFormatSupported(Ogre::TextureType ttype, Ogre::PixelFormat format, int usage);

        bool unloadUnreferencedResource(const String& name);
    private:
        std::unordered_map<std::string, std::shared_ptr<ITexture>> mTexMap;
    };
}