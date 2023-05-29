#pragma once

#include "texture.h"
#include <d3d11_1.h>

class Dx11RenderSystem;

class Dx11Texture :public ITexture
{
public:
    Dx11Texture(
        const std::string& name, 
        TextureProperty* texProperty, 
        Dx11RenderSystem* rs);
    ~Dx11Texture();

    ID3D11ShaderResourceView* getResourceView()
    {
        return mTextureView;
    }

    ID3D11Resource* getTextureResource()
    {
        return mTex;
    }

    bool hasAutoMipMapGenerationEnabled()
    {
        return mAutoMipMapGeneration;
    }

    DXGI_FORMAT getD3dFormat()
    {
        return mD3DFormat;
    }

    ID3D11Texture2D* getTexture()
    {
        return mTex;
    }

private:
    virtual void createInternalResourcesImpl(void);
    virtual void freeInternalResourcesImpl(void);
    void _create2DTex();
    void _createSurfaceList(void);
    virtual void postLoad();
private:

    ID3D11Texture2D* mTex = nullptr;

    ID3D11ShaderResourceView* mTextureView = nullptr;

    Dx11RenderSystem* mRenderSystem = nullptr;
    DXGI_FORMAT mD3DFormat;

    bool mAutoMipMapGeneration = false;
};