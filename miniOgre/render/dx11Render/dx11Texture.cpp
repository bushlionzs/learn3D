#include "OgreHeader.h"
#include "dx11Texture.h"
#include "OgreImage.h"
#include "dx11RenderSystem.h"
#include "dx11Helper.h"
#include "OgreD3D11Mappings.h"
#include "dx11Helper.h"
#include "dx11HardwarePixelBuffer.h"


Dx11Texture::Dx11Texture(
    const std::string& name, 
    TextureProperty* texProperty,
    Dx11RenderSystem* rs):ITexture(name, texProperty)
{
    mName = name;

    mRenderSystem = rs;
}

Dx11Texture::~Dx11Texture()
{

}



void Dx11Texture::createInternalResourcesImpl(void)
{
    mFormat = D3D11Mappings::_getClosestSupportedPF(mFormat);

    mD3DFormat = D3D11Mappings::_getGammaFormat(D3D11Mappings::_getPF(mFormat), false);


    switch (mTextureProperty._texType)
    {
    case TEX_TYPE_2D:
    case TEX_TYPE_CUBE_MAP:
    case TEX_TYPE_2D_ARRAY:
        this->_create2DTex();
        break;
    default:
        this->freeInternalResources();
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "Unknown texture type", "D3D11Texture::createInternalResources");
    }

    _createSurfaceList();
}

void Dx11Texture::freeInternalResourcesImpl(void)
{

}

void Dx11Texture::_create2DTex()
{
    UINT numMips = mTextureProperty._numMipmaps + 1;

    D3D11_TEXTURE2D_DESC desc;
    UINT retVal = D3D11_BIND_SHADER_RESOURCE;
    if (mTextureProperty._numMipmaps == 0 && !PixelUtil::isCompressed(mTextureProperty._tex_format))
    {
        mNumMipmaps = getMaxMipmaps();
        numMips = mNumMipmaps + 1;
        retVal |= D3D11_BIND_RENDER_TARGET;
        mAutoMipMapGeneration = true;
    }

    if (mUsage & TU_RENDERTARGET)
    {
        mNumMipmaps = 0;
        numMips = 1;
        retVal |= D3D11_BIND_RENDER_TARGET;
    }
    

    
    
    desc.Width = static_cast<UINT>(getWidth());
    desc.Height = static_cast<UINT>(getHeight());
    desc.MipLevels = static_cast<UINT>(numMips);
    desc.ArraySize = static_cast<UINT>(mFace);
    desc.Format = mD3DFormat;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = retVal;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    if (retVal & D3D11_BIND_RENDER_TARGET)
    {
        desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
    }
    

    if (isCubeTexture())
    {
        desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
    }

    auto device = DX11Helper::getSingleton().getDevice();
    HRESULT hr = device->CreateTexture2D(
        &desc, nullptr, &mTex);
    if (FAILED(hr))
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateTexture2D failed!");
    }
    
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

    if (mUsage & TU_RENDERTARGET)
    {
        int kk = 0;
    }
   
    mTex->GetDesc(&desc);
    srvDesc.Format = desc.Format;
    if (isCubeTexture())
    {
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
        srvDesc.TextureCube.MostDetailedMip = 0;
        srvDesc.TextureCube.MipLevels = desc.MipLevels;
    }
    else
    {
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
    }
    

    hr = device->CreateShaderResourceView(mTex,
        &srvDesc,
        &mTextureView
    );

    if (FAILED(hr))
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateShaderResourceView failed!");
    }

}

void Dx11Texture::_createSurfaceList(void)
{
    // Create new list of surfaces
    mSurfaceList.clear();
    size_t depth = mTextureProperty._depth;

    for (size_t face = 0; face < mFace; ++face)
    {
        size_t width = mTextureProperty._width;
        size_t height = mTextureProperty._height;
        for (size_t mip = 0; mip <= mTextureProperty._numMipmaps; ++mip)
        {

            Dx11HardwarePixelBuffer* buffer;
            buffer = new Dx11HardwarePixelBuffer(
                this, // parentTexture
                mip,
                width,
                height,
                depth,
                face,
                mFormat,
                (HardwareBuffer::Usage)mUsage
            );

            mSurfaceList.push_back(HardwarePixelBufferPtr(buffer));

            if (width > 1) width /= 2;
            if (height > 1) height /= 2;
        }
    }
}

void Dx11Texture::postLoad()
{

}