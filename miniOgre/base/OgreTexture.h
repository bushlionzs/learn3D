#pragma once
#include "OgreHardwareBuffer.h"
#include "OgrePixelFormat.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreImage.h"
#include "OgreResource.h"
#include <utils/JobSystem.h>
#include <filament/DriverEnums.h>

namespace Ogre {
    enum TextureTypePbr
    {
        TextureTypePbr_general = 0,
        TextureTypePbr_Albedo = 1,
        TextureTypePbr_AmbientOcclusion = 2,
        TextureTypePbr_NormalMap = 3,
        TextureTypePbr_Emissive = 4,
        TextureTypePbr_MetalRoughness = 5,
        TextureTypePbr_Roughness = 6,
        TextureTypePbr_Diffuse = 7,
        TextureTypePbr_Specular = 8,
        TextureTypePbr_Opacity = 9,
        TextureTypePbr_BRDF_LUT = 10,
        TextureTypePbr_IBL_Diffuse = 11,
        TextureTypePbr_IBL_Specular = 12
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
        TEX_TYPE_CUBE_MAP_ARRAY = 5,
        /// 2D texture array
        TEX_TYPE_2D_ARRAY = 6,
        /// GLES2 only OES texture type
        TEX_TYPE_EXTERNAL_OES = 7
    };

    class TextureProperty
    {
    public:
        TextureType _texType;
        TextureTypePbr _pbrType;
        std::string textureTypeName;
        uint32_t _width;
        uint32_t _height;
        uint32_t _depth;
        uint32_t _face;
        uint32_t _numMipmaps;
        Ogre::PixelFormat _tex_format;
        bool _need_mipmap;
        uint32_t _maxMipLevel;
        float _gamma;
        uint32_t _fsaa;
        BitField<TextureUsageBits> _tex_usage;
        ColourValue _backgroudColor;
        TextureAddressingMode  _tex_addr_mod;
        filament::backend::SamplerParams _samplerParams;
        TextureProperty();
        bool isRenderTarget();
        bool haveImageFile();
        void gltfSampler();
    };


    class OgreTexture: public Resource
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

        uint32_t getNumMipmaps()
        {
            return mTextureProperty._numMipmaps + 1;
        }

        uint32_t getFace()
        {
            return mTextureProperty._face;
        }

        bool isCubeTexture()
        {
            return mTextureProperty._texType == TEX_TYPE_CUBE_MAP ||
                mTextureProperty._texType == TEX_TYPE_CUBE_MAP_ARRAY;
        }
        

        TextureProperty* getTextureProperty()
        {
            return &mTextureProperty;
        }

        TextureType getTextureType();

        void createInternalResources();
        void freeInternalResources(void);
        virtual void createInternalResourcesImpl(void) = 0;
        virtual void freeInternalResourcesImpl(void) = 0;
        virtual void updateTexture(const std::vector<const CImage*>& images) = 0;
        bool isLoaded();
        void loadAsync();
        virtual void loadImpl()override;
        virtual void unloadImpl(void)override;
        uint32 getMaxMipmaps() const;
        
        virtual void uploadData() {}
        virtual void blitFromMemory(
            const PixelBox& src, const Box& dstBox, uint32_t face = 0, uint32_t mipmap = 0) {}
        virtual void uploadTextureData(const char* data, uint32_t size, TextureProperty& tp);
        void loadImage(const CImage& img);
        void loadRawData(DataStreamPtr& stream, ushort uWidth, ushort uHeight,
            PixelFormat format);

        uint32_t getDataOffset(uint32_t face, uint32_t mip);

        
    private:
        
        void _loadImages(const std::vector<const CImage*>& images);
    protected:
        String mName;
        TextureProperty mTextureProperty;
        std::vector<String> mLayerNames;

        bool mInternalResourcesCreated = false;

        std::vector<uint32_t> mOffsetList;
    };
}