#pragma once
#include "OgreHardwareBuffer.h"
#include "OgrePixelFormat.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreImage.h"
#include <utils/JobSystem.h>

namespace Ogre {
    enum TextureTypePbr
    {
        TextureTypePbr_general = 0,
        TextureTypePbr_Albedo = 1,
        TextureTypePbr_AmbientOcclusion = 2,
        TextureTypePbr_NormalMap = 3,
        TextureTypePbr_Emissive = 4,
        TextureTypePbr_MetalRoughness = 5,
        TextureTypePbr_BRDF_LUT = 6,
        TextureTypePbr_IBL_Diffuse = 7,
        TextureTypePbr_IBL_Specular = 8
    };
    

    enum TextureType : uint8_t
    {
        /// 1D texture, used in combination with 1D texture coordinates
        TEX_TYPE_1D = 1,
        /// 2D texture, used in combination with 2D texture coordinates (default)
        TEX_TYPE_2D = 2,
        /// 3D volume texture, used in combination with 3D texture coordinates
        TEX_TYPE_3D = 3,
        /// cube map (six two dimensional textures, one for each cube face), used in combination with 3D
        /// texture coordinates
        TEX_TYPE_CUBE_MAP = 4,
        /// 2D texture array
        TEX_TYPE_2D_ARRAY = 5,
        /// GLES2 only OES texture type
        TEX_TYPE_EXTERNAL_OES = 6
    };

    enum TextureUsage
    {
        /// same as #HBU_GPU_TO_CPU
        TU_STATIC = HBU_GPU_TO_CPU,
        /// same as #HBU_CPU_ONLY
        TU_DYNAMIC = HBU_CPU_ONLY,
        /// same as #HBU_DETAIL_WRITE_ONLY
        TU_WRITE_ONLY = HBU_DETAIL_WRITE_ONLY,
        /// same as #HBU_GPU_ONLY
        TU_STATIC_WRITE_ONLY = HBU_GPU_ONLY,
        /// same as #HBU_CPU_TO_GPU
        TU_DYNAMIC_WRITE_ONLY = HBU_CPU_TO_GPU,
        /// Mipmaps will be automatically generated for this texture
        TU_AUTOMIPMAP = 0x10,
        /** This texture will be a render target, i.e. used as a target for render to texture
            setting this flag will ignore all other texture usages except TU_AUTOMIPMAP, TU_UAV, TU_NOT_SRV */
        TU_RENDERTARGET = 0x20,
        /// Texture would not be used as Shader Resource View, i.e. as regular texture.
        /// That flag could be combined with TU_RENDERTARGET or TU_UAV to remove possible limitations on some hardware
        TU_NOT_SRV = 0x40,
        /// Texture can be bound as an Unordered Access View
        /// (imageStore/imageRead/glBindImageTexture in GL jargon)
        TU_UAV = 0x80,
        /// Texture can be used as an UAV, but not as a regular texture.
        TU_UAV_NOT_SRV = TU_UAV | TU_NOT_SRV,
        /// Default to automatic mipmap generation static textures
        TU_DEFAULT = TU_AUTOMIPMAP | HBU_GPU_ONLY,
    };

    class TextureProperty
    {
    public:
        TextureType _texType = TEX_TYPE_2D;
        TextureTypePbr _pbrType = TextureTypePbr_general;
        uint32_t _width = 0;
        uint32_t _height = 0;
        uint32_t _depth = 1;
        uint32_t _numMipmaps = 0;
        Ogre::PixelFormat _tex_format = Ogre::PF_R8G8B8A8;
        float _gamma = 1.0f;
        uint32_t _fsaa = 0;
        TextureUsage _tex_usage = TU_DEFAULT;
        ColourValue _backgroudColor = ColourValue::Black;
        TextureAddressingMode  _tex_addr_mod = Ogre::TAM_WRAP;
    };

    class OgreTexture
    {
    public:
        OgreTexture(const String& name, TextureProperty* texProperty);
        ~OgreTexture();
        const String& getName()
        {
            return mName;
        }

        void setWidth(int32_t width)
        {
            mTextureProperty._width = width;
        }

        int32_t getWidth()
        {
            return mTextureProperty._width;
        }

        void setHeight(int32_t height)
        {
            mTextureProperty._height = height;
        }

        void setNumMipmaps(uint32 num)
        {
            mNumMipmaps = num;
        }

        int32_t getHeight()
        {
            return mTextureProperty._height;
        }

        int32_t getDepth()
        {
            return mTextureProperty._depth;
        }

        uint32_t getSize()
        {
            return PixelUtil::getMemorySize(mTextureProperty._width, mTextureProperty._height,
                mTextureProperty._depth, mTextureProperty._tex_format);
        }

        Ogre::PixelFormat getFormat()
        {
            return mTextureProperty._tex_format;
        }

        uint32_t getSourceMipmaps()
        {
            return mTextureProperty._numMipmaps;
        }
        uint32_t getNumMipmaps()
        {
            return mNumMipmaps;
        }

        uint32_t getFace()
        {
            return mFace;
        }

        bool isCubeTexture()
        {
            return mTextureProperty._texType == TEX_TYPE_CUBE_MAP;
        }
        bool isLoaded()
        {
            return mLoad;
        }

        TextureProperty* getTextureProperty()
        {
            return &mTextureProperty;
        }

        TextureType getTextureType();

        virtual const HardwarePixelBufferPtr& getBuffer(size_t face = 0, size_t mipmap = 0);
        void createInternalResources();
        void freeInternalResources(void);
        virtual void createInternalResourcesImpl(void) = 0;
        virtual void freeInternalResourcesImpl(void) = 0;
        virtual void preLoad();
        bool load(utils::JobSystem::Job* job);
        void loadImpl();
        virtual void postLoad();
        uint32 getMaxMipmaps() const;
        void loadImage(const CImage& img);
        void _loadImages(const std::vector<const CImage*>& images);
        virtual void unload();

        void loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight, PixelFormat format);
    protected:
        String mName;
        TextureProperty mTextureProperty;
        uint32_t mFace = 1;
        uint32_t mNumMipmaps = 0;
        PixelFormat mFormat;
        int mUsage;

        PixelFormat mSrcFormat;
        uint32 mSrcWidth, mSrcHeight, mSrcDepth;

        std::vector<String> mLayerNames;

        typedef std::vector<HardwarePixelBufferPtr> SurfaceList;
        SurfaceList mSurfaceList;

        bool mLoad = false;

        bool mInternalResourcesCreated = false;
    };
}