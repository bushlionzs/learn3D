#pragma once
#include "dx12Common.h"
#include "dx12Commands.h"


class Dx12RenderTarget;
class Dx12Texture;
struct DX12Fence;
struct DX12CommandQueue;
struct DX12CommandBuffer;

class DX12SwapChain: public HwSwapChain
{
    struct DX12RenderTargetInfo
    {
        Microsoft::WRL::ComPtr<ID3D12Resource> swapChainBuffer;
        ComPtr<ID3D12DescriptorHeap> rtvHeap;
    };

public:
    DX12SwapChain(
        HWND hWnd,
        uint64_t flags);
    void resize(DX12CommandQueue*);
    void present(
        DX12CommandQueue* cq,
        DX12Fence* fence,
        ID3D12GraphicsCommandList** cb,
        uint32_t cb_size
        );
    void acquire(bool& reized);

    uint32 getWidth()
    {
        return mWidth;
    }
    uint32_t getHeight()
    {
        return mHeight;
    }

    Dx12Texture* getDepthTexture();
    Dx12Texture* getCurrentColor();

    DXGI_FORMAT getColorFormat()
    {
        return mColorFormat;
    }

    DXGI_FORMAT getDepthFormat()
    {
        return mDepthFormat;
    }

    uint32 getImageIndex()
    {
        return mSwapChain3->GetCurrentBackBufferIndex();
    }

private:
    void releaseSwapChain();
    void createSwapChain2(DX12CommandQueue* cq, bool srgb);
    
private:
    IDXGISwapChain3* mSwapChain3;
    Dx12Texture* mDepth;
    std::vector<Dx12Texture*> mColors;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

    uint32_t mBackBufferIndex;

    HWND mHwnd;

    uint32_t mWidth;
    uint32_t mHeight;

    DXGI_FORMAT mColorFormat;
    DXGI_FORMAT mDepthFormat;

    bool mUseSRGB;
};