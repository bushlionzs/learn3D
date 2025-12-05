#include "OgreHeader.h"
#include "OgreTextureManager.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreImage.h"
#include "OgreResourceManager.h"
#include "OgreResourceBackgroundQueue.h"
#include <utils/JobSystem.h>


namespace Ogre {
    template<> TextureManager* Ogre::Singleton<TextureManager>::msSingleton = 0;
    TextureManager::TextureManager()
    {
       
    }

    TextureManager::~TextureManager()
    {

    }

    
    std::shared_ptr<OgreTexture> TextureManager::load(
        const String& name,
        TextureProperty* texProperty,
        bool read)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            return it->second;
        }

        auto* rs = Ogre::Root::getSingleton().getRenderSystem();

        TextureProperty* tp = texProperty;
        if (tp)
        {
            if (tp->_width == 0)
            {
                ImageInfo info;
                CImage::loadImageInfo(name, info, false);
                tp->_width = info.width;
                tp->_height = info.height;
                tp->_depth = info.depth;
                tp->_tex_format = info.format;
            }
        }
        
        OgreTexture* tmp = rs->createManualTexture(name, tp);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        std::shared_ptr<OgreTexture> tex(tmp);

        mTexMap[name] = tex;

        if (read)
        {
            if (tex->loadAsync())
            {
                ResourceBackgroundQueue::getSingleton().load(tex);
            }
        }
       

        return tex;
    }

    std::shared_ptr<OgreTexture> TextureManager::loadImage(
        const String& name,
        const CImage& img,
        TextureType texType,
        int numMipmaps,
        Real gamma,
        bool isAlpha,
        PixelFormat desiredFormat,
        bool hwGammaCorrection)
    {
        assert_invariant(false);
        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createManualTexture(name, nullptr);


        tmp->loadImage(img);

        return std::shared_ptr<OgreTexture>(tmp);
    }

    bool TextureManager::addTexture(const String& name, OgreTexture* tex)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            return false;
        }

        mTexMap[name] = std::shared_ptr<OgreTexture>(tex);
        return true;
    }
    

    std::shared_ptr<OgreTexture> TextureManager::getByName(
        const String& name,
        const String& group) const
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            return it->second;
        }

        return std::shared_ptr<OgreTexture>();
    }

    bool TextureManager::getImageInfo(const String& name, ImageInfo& info, bool cube)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            info.width = it->second->getWidth();
            info.height = it->second->getHeight();
            return true;
        }
        return CImage::loadImageInfo(name, info, cube);
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

        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createManualTexture(name, &texProperty);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        std::shared_ptr<OgreTexture> tex(tmp);

        mTexMap[name] = tex;

        tex->createInternalResources();

        return tex;
    }

    TexturePtr TextureManager::loadRawData(
        const String& name, 
        DataStreamPtr& stream, 
        TextureProperty& texProperty)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "duplicated texture name");
        }

        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createManualTexture(
            name, &texProperty);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        tmp->loadRawData(stream, texProperty._width, texProperty._height, texProperty._tex_format);
        std::shared_ptr<OgreTexture> tex(tmp);

        mTexMap[name] = tex;

        return tex;
    }

    bool TextureManager::isFormatSupported(Ogre::TextureType ttype, Ogre::PixelFormat format, int usage)
    {
        return true;
    }

    bool TextureManager::unloadUnreferencedResource(const String& name)
    {
        assert_invariant(false);
        return true;
    }

    void TextureManager::updateTextures()
    {
        
        
    }
}