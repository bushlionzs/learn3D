#pragma once

#include "OgreRenderTexture.h"
#include "OgreRenderTarget.h"
#include "d3dutil.h"
#include "dx12RenderTarget.h"
class Dx12HardwarePixelBuffer;
class Dx12RenderSystem;
class Dx12Texture;

class Dx12RenderTexture : public Ogre::RenderTexture, public Dx12RenderTarget
{
public:
	Dx12RenderTexture(
		const String& name, 
		Dx12HardwarePixelBuffer* buffer,
		uint32_t zoffset);
	~Dx12RenderTexture();

	void rebind(Dx12HardwarePixelBuffer* buffer);
	virtual void copyContentsToMemory(const Box& src, const PixelBox& dst, FrameBuffer buffer = FB_AUTO);

	virtual bool requiresTextureFlipping() const;

	virtual void preRender(ID3D12GraphicsCommandList* cl);

	virtual void swapBuffers();

	virtual D3D12_RESOURCE_STATES getResourceStates();
	virtual ID3D12Resource* getCurrentBackBuffer() const;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

	virtual bool useMsaa()
	{
		return true;
	}
private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencil;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    mDSVDescriptorHeap;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuHandleOfRenderTarget;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mGpuHandleOfRenderTarget;

	int32_t mResourceViewIndex;
	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuHandleOfResourceView;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mGpuHandleOfResourceView;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuHandleOfDepth;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mGpuHandleOfDepth;

	D3D12_VIEWPORT mViewport;
	D3D12_RECT mScissorRect;

	Dx12RenderSystem* mRenderSystem;

	ID3D12GraphicsCommandList* mCommandList;

	Dx12Texture* mParentTexture;
};