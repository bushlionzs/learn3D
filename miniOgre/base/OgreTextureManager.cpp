#include "OgreHeader.h"
#include "OgreTextureManager.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreResourceManager.h"
#include <backend/Texture.h>
#include <backend/DriverEnums.h>
#include <backend/engine.h>
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

    std::pair<Texture*, CacheResult> TextureManager::getOrCreateTexture(const String& name)
    {
        if (auto iter = mTextureCache.find(name); iter != mTextureCache.end())
        {
            return { iter->second, CacheResult::FOUND };
        }

        std::shared_ptr<DataStream> stream
            = ResourceManager::getSingleton().openResource(name);

        if (!stream)
        {
            return { nullptr, CacheResult::NOT_EXIST };
        }

        const uint8_t* data = (const uint8_t*)stream->getStreamData();
        uint32_t bytecount = stream->getStreamLength();

        TextureInfo* info = mTextureInfos.emplace_back(new TextureInfo).get();

        int width, height, numComponents;
        CImage::loadImageInfo(data, bytecount, &width, &height, &numComponents);

        Texture* texture = Texture::Builder()
            .width(width)
            .height(height)
            .levels(0xff)
            .format(filament::backend::TextureFormat::RGBA8)
            .build(*mEngine);

        info->texture = texture;
        info->state = TextureState::DECODING;
        info->sourceBuffer.assign(data, data + bytecount);
        info->decodedTexelsBaseMipmap.store(DECODING_NOT_READY);

        utils::JobSystem* js = &mEngine->getJobSystem();
        info->decoderJob = utils::jobs::createJob(*js, mDecoderRootJob, [info] {
            auto& source = info->sourceBuffer;
            int width, height, comp;

            // Test asynchronous loading by uncommenting this line.
            // std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 10000));
            CImage image;

            image.loadImage(info->sourceBuffer.data(), info->sourceBuffer.size());

            auto texels = image.getImageData();
            source.clear();
            source.shrink_to_fit();
            info->decodedTexelsBaseMipmap.store(texels ? intptr_t(texels) : DECODING_ERROR);
            });

        js->runAndRetain(info->decoderJob);
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
                Texture::PixelBufferDescriptor pbd((uint8_t*)data,
                    texture->getWidth() * texture->getHeight() * 4, Texture::Format::RGBA,
                    Texture::Type::UBYTE, [](void* mem, size_t, void*) { free(mem); });
                texture->setImage(*mEngine, 0, std::move(pbd));

                // Call generateMipmaps unconditionally to fulfill the promise of the TextureProvider
                // interface. Providers of hierarchical images (e.g. KTX) call this only if needed.
                texture->generateMipmaps(*mEngine);

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