#include "OgreHeader.h"
#include "OgreTextureManager.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreResourceManager.h"
#include <filament/Texture.h>
#include <filament/DriverEnums.h>
#include <filament/engine.h>
#include <filament/FTexture.h>
#include <filament/DriverApi.h>
#include <filament/OgreFilamentUtils.h>
#include <utils/JobSystem.h>


namespace Ogre {
    template<> TextureManager* Ogre::Singleton<TextureManager>::msSingleton = 0;
    TextureManager::TextureManager()
    {
        mEngine = Ogre::Root::getSingleton().getEngine();
    }

    TextureManager::~TextureManager()
    {

    }

    
    std::shared_ptr<OgreTexture> TextureManager::load(
        const std::string& name, 
        TextureProperty* texProperty,
        bool read)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            return it->second;
        }

        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, texProperty);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        if (read)
        {
            tmp->load(nullptr);
        }
        std::shared_ptr<OgreTexture> tex(tmp);

        mTexMap[name] = tex;

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
        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, nullptr);

        tmp->setNumMipmaps(1000);

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
    bool TextureManager::addTexture(const String& name, Texture* tex)
    {
        if (auto iter = mTextureCache.find(name); iter != mTextureCache.end())
        {
            assert(false);
            return false;
        }
        mTextureCache[name] = tex;
        return true;
    }

   

    std::pair<Texture*, CacheResult> TextureManager::getOrCreateTexture(const String& name, bool cube)
    {
        if (auto iter = mTextureCache.find(name); iter != mTextureCache.end())
        {
            return { iter->second, CacheResult::FOUND };
        }

        Ogre::ImageInfo imageInfo;
        bool get = getImageInfo(name, imageInfo, cube);
        assert(get);

        if (imageInfo.width > 2000)
        {
            int kk = 0;
        }
        TextureInfo* info = mTextureInfos.emplace_back(new TextureInfo).get();

        auto type = CImage::getImageType(name);
        

        auto filamentFormat = mappingOgreTextureFormat(imageInfo.format);
        Texture* texture = Texture::Builder()
            .width(imageInfo.width)
            .height(imageInfo.height)
            .levels(0xff)
            .imagetype(type)
            .format(filamentFormat)
            .sampler(cube? backend::SamplerType::SAMPLER_CUBEMAP: backend::SamplerType::SAMPLER_2D)
            .build(*mEngine);

        FTexture* ftex = (FTexture*)texture;
        mEngine->getDriverApi().updateTextureName(ftex->getHwHandle(), name.c_str(), name.size());
        info->texture = texture;
        info->state = TextureState::DECODING;
        info->textureName = name;
        info->decodedTexelsBaseMipmap.store(DECODING_NOT_READY);
        
        utils::JobSystem* js = &mEngine->getJobSystem();
        info->decoderJob = utils::jobs::createJob(*js, mDecoderRootJob, [info, cube] {
            int width, height, comp;

            // Test asynchronous loading by uncommenting this line.
            // std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 10000));
            CImage image;

            //todo: Warning!!! loading image in multi-thread  could not be safe
            image.loadImage(info->textureName, cube);

            auto texels = image.getImageData();
            info->decodeDataSize = image.getSize();
            if (cube)
            {
                int kk = 0;
            }
            info->decodedTexelsBaseMipmap.store(texels ? intptr_t(texels) : DECODING_ERROR);
            });

        js->runAndRetain(info->decoderJob);

        mTextureCache[name] = texture;
        return { texture, CacheResult::MISS };
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
        auto engine = Ogre::Root::getSingleton().getEngine();
        if (engine)
        {
            if (auto iter = mTextureCache.find(name); iter != mTextureCache.end())
            {
                info.width = iter->second->getWidth();
                info.height = iter->second->getHeight();
                return true;
            }
        }
        else
        {
            auto it = mTexMap.find(name);
            if (it != mTexMap.end())
            {
                info.width = it->second->getWidth();
                info.height = it->second->getHeight();
                return true;
            }
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

        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, &texProperty);

        if (tmp == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to create texture");
        }

        tmp->createInternalResources();
        std::shared_ptr<OgreTexture> tex(tmp);

        mTexMap[name] = tex;

        return tex;
    }

    TexturePtr TextureManager::loadRawData(const String& name, DataStreamPtr& stream, TextureProperty& texProperty)
    {
        auto it = mTexMap.find(name);
        if (it != mTexMap.end())
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "duplicated texture name");
        }

        OgreTexture* tmp = Ogre::Root::getSingleton().getRenderSystem()->createTextureFromFile(name, &texProperty);

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
        assert(false);
        return true;
    }

    void TextureManager::updateTextures()
    {
        if (mEngine)
        {
            utils::JobSystem* js = &mEngine->getJobSystem();
            for (auto& info : mTextureInfos) {
                if (info->state != TextureState::DECODING) {
                    continue;
                }
                Texture* texture = info->texture;
                if (intptr_t data = info->decodedTexelsBaseMipmap.load()) {
                    if (info->decoderJob) {
                        js->waitAndRelease(info->decoderJob);
                    }
                    if (data == DECODING_ERROR) {
                        info->state = TextureState::READY;
                        continue;
                    }

                    auto format = Texture::Format::RGBA;

                    auto source_format = texture->getFormat();
                    if (source_format == backend::TextureFormat::RGB8)
                    {
                        format = Texture::Format::RGB;
                    }

                    if (source_format == backend::TextureFormat::R8)
                    {
                        format = Texture::Format::R;
                    }


                    auto dataType = Texture::Type::UBYTE;

                    if (texture->getImageType() == backend::ImageType::ImageType_DDS)
                    {
                        dataType = Texture::Type::COMPRESSED;
                    }

                    Texture::PixelBufferDescriptor pbd((uint8_t*)data,
                        info->decodeDataSize, format,
                        dataType, [](void* mem, size_t, void*)
                        {
                            CImage::freeImageData(mem);
                        }
                    );
                    texture->setImage(*mEngine, 0, std::move(pbd));

                    // Call generateMipmaps unconditionally to fulfill the promise of the TextureProvider
                    // interface. Providers of hierarchical images (e.g. KTX) call this only if needed.
                    //texture->generateMipmaps(*mEngine);

                    texture->setReady(true);
                    info->state = TextureState::READY;
                }
            }

            while (!mTextureInfos.empty())
            {
                const auto& back = mTextureInfos.back();

                if (back->state == TextureState::READY)
                {
                    mTextureInfos.pop_back();
                }
                else
                {
                    break;
                }
            }
        }
        
    }
}