#include "OgreHeader.h"
#include "OgreTextureManager.h"
#include "renderSystem.h"
#include "OgreRoot.h"



namespace Ogre {
    template<> TextureManager* Ogre::Singleton<TextureManager>::msSingleton = 0;
    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {

    }

    std::shared_ptr<ITexture> TextureManager::load(const std::string& name, TextureProperty* texProperty)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            return it->second;
        }

        ITexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, texProperty);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        std::shared_ptr<ITexture> tex(tmp);

        mTexMap[name] = tex;

        return tex;
    }

    std::shared_ptr<ITexture> TextureManager::loadImage(
        const String& name,
        const CImage& img,
        TextureType texType,
        int numMipmaps,
        Real gamma,
        bool isAlpha,
        PixelFormat desiredFormat,
        bool hwGammaCorrection)
    {
        ITexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, nullptr);

        tmp->setNumMipmaps(1000);

        tmp->loadImage(img);

        return std::shared_ptr<ITexture>(tmp);
    }

    std::shared_ptr<ITexture> TextureManager::getByName(
        const String& name,
        const String& group) const
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            return it->second;
        }

        return std::shared_ptr<ITexture>();
    }

    void TextureManager::remove(const std::string& name)
    {

    }

    TexturePtr TextureManager::createManual(const String& name, TextureProperty& texProperty)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "duplicated texture name");
        }

        ITexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, &texProperty);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        tmp->createInternalResources();
        std::shared_ptr<ITexture> tex(tmp);

        mTexMap[name] = tex;

        return tex;
    }

    bool TextureManager::isFormatSupported(Ogre::TextureType ttype, Ogre::PixelFormat format, int usage)
    {
        return true;
    }

    bool TextureManager::unloadUnreferencedResource(const String& name)
    {
        assert(false);
        return true;
    }
}