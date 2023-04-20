#include "OgreHeader.h"
#include "dx12RenderSystem.h"
#include "dx12HardwareBufferManager.h"
#include "OgreMoveObject.h"
#include "OgreMaterial.h"
#include "OgreRenderable.h"
#include "dx12Renderable.h"
#include "dx12Shader.h"
#include "dx12Texture.h"
#include "OgreTextureUnit.h"
#include "vertex_data.h"
#include "index_data.h"
#include "OgreCamera.h"
#include "dx12RenderTarget.h"
#include "dx12TextureHandleManager.h"
#include "dx12ShadowMap.h"
#include "dx12RenderWindow.h"
#include "dx12Helper.h"
#include "OgreViewport.h"
#include "dx12Frame.h"
#include "OgreRoot.h"

Dx12RenderSystem::Dx12RenderSystem(HWND wnd)
{
	mClearColor = DirectX::Colors::LightBlue;

	mRenderSystemName = "Directx12";
}


Dx12RenderSystem::~Dx12RenderSystem()
{

}

bool Dx12RenderSystem::engineInit()
{
	RenderSystem::engineInit();
	new Dx12HardwareBufferManager(this);

	if (!initDirect3D())
	{
		return false;
	}

	buildRootSignature();
	return true;
}

void Dx12RenderSystem::ready()
{
	auto cl = getCurrentFrame()->getCommandList();
	cl->Close();
	DX12Helper::getSingleton().executeCommand(cl);
	DX12Helper::getSingleton().FlushCommandQueue();
}

void Dx12RenderSystem::_resourceLoaded()
{
	//DX12Helper::getSingleton()._createMipmapPrepare();
}

void Dx12RenderSystem::update(float delta)
{

	UpdateShadowTransform(delta);
	
}

void Dx12RenderSystem::frameStart()
{
	DX12Helper::getSingleton()._submitCommandList(true);
	mTriangleCount = 0;
	mBatchCount = 0;
	mLoadResCount = 0;
	mCurrentFrame = mFrameList[mCurrFrameResourceIndex++];

	mCurrFrameResourceIndex = mCurrFrameResourceIndex % FRAME_RESOURCE_COUNT;

	if (mCurrentFrame->getFence() != 0 &&
		DX12Helper::getSingleton().getFenceCompletedValue() < mCurrentFrame->getFence())
	{
		DX12Helper::getSingleton().waitFence(mCurrentFrame->getFence());
	}

	mCurrentFrame->resetCommandList();
	auto commandlist = mCurrentFrame->getCommandList();

	mFrameConstantBuffer.Shadow = 0;

	const std::vector<ID3D12DescriptorHeap*> dhs = mDx12TextureHandleManager->getHeaps();
	commandlist->SetDescriptorHeaps(dhs.size(), dhs.data());
	commandlist->SetGraphicsRootSignature(mRootSignature.Get());

	mCurrentPass.mRootSignature = mRootSignature.Get();
	mCurrentPass.mPassState = PassState_Normal;
}

void Dx12RenderSystem::frameEnd()
{
	postRender();
	auto commandList = DX12Helper::getSingleton().getCurrentCommandList();
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mRenderWindow->getCurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	// Done recording commands.
	ThrowIfFailed(commandList->Close());

	// Add the command list to the queue for execution.

	DX12Helper::getSingleton().executeCommand(commandList);

	mRenderWindow->present();
	mCurrentFrame->setFence(DX12Helper::getSingleton().incrFence());
	DX12Helper::getSingleton().signalFence(mCurrentFrame->getFence());
}

void Dx12RenderSystem::render(Renderable* r, RenderListType t)
{
	const std::shared_ptr<Material>& mat = r->getMaterial();
	if (!mat)
	{
		return;
	}

	mat->load();

	
	const std::shared_ptr<Shader>& shader = mat->getShader();
	mCurrentPass.mRenderListType = t;
	mCurrentPass.mMaterial = mat.get();
	mCurrentPass.mShader = (Dx12Shader*)shader.get();
	mCurrentPass.mRenderable = r;
	mCurrentPass.mDx12RenderableData = (Dx12RenderableData*)r->getRenderableData();
	mCurrentPass.mDx12RenderableData->updateCurrentFrame(mCurrentFrame->getFrameIndex());
	VertexData* vertexData = r->getVertexData();
	auto vd = vertexData->vertexDeclaration;
	mCurrentPass.mShader->updateInputDesc(vd);

	ID3D12PipelineState* pso = mCurrentPass.mShader->BuildPSO(&mCurrentPass);
	mCurrentFrame->getCommandList()->SetPipelineState(pso);

	RawData* rd = r->getShaderConstantData(2);
	if (rd)
	{
		mCurrentPass.mDx12RenderableData->updateSkinedConstanctBuffer(rd);

		D3D12_GPU_VIRTUAL_ADDRESS frameAddress = 
			mCurrentPass.mDx12RenderableData->getSkinedAddress();
		mCurrentFrame->getCommandList()->SetGraphicsRootConstantBufferView(
			mSkinedConstantIndex, frameAddress);
	}

	mCurrentPass.mDx12RenderableData->buildMaterial(mCurrentPass.mMaterial);
	renderImpl(&mCurrentPass);
}

void Dx12RenderSystem::postRender()
{
	auto commandlist = mCurrentFrame->getCommandList();
	auto backBuffer = mActiveDx12RenderTarget->getCurrentBackBuffer();
	if (mActiveDx12RenderTarget->useMsaa())
	{
		{
			D3D12_RESOURCE_STATES states = mActiveDx12RenderTarget->getResourceStates();
			D3D12_RESOURCE_BARRIER barriers[2] =
			{
				CD3DX12_RESOURCE_BARRIER::Transition(
					m_msaaRenderTarget.Get(),
					D3D12_RESOURCE_STATE_RENDER_TARGET,
					D3D12_RESOURCE_STATE_RESOLVE_SOURCE),
				CD3DX12_RESOURCE_BARRIER::Transition(
					backBuffer,
					states,
					D3D12_RESOURCE_STATE_RESOLVE_DEST)
			};

			commandlist->ResourceBarrier(2, barriers);
		}
		//mCommandList->CopyResource(backBuffer, m_msaaRenderTarget.Get());
		commandlist->ResolveSubresource(backBuffer, 0, m_msaaRenderTarget.Get(), 0, mBackBufferFormat);

		{
			D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
				backBuffer,
				D3D12_RESOURCE_STATE_RESOLVE_DEST,
				D3D12_RESOURCE_STATE_RENDER_TARGET);
			commandlist->ResourceBarrier(1, &barrier);
		}
	}
}

Camera* Dx12RenderSystem::getCurrentCamera()
{
	return mCamera;
}


ITexture* Dx12RenderSystem::createTextureFromFile(const std::string& name, TextureProperty* texProperty)
{
	Dx12Texture* tex = new Dx12Texture(name, texProperty, this);

	if (!tex->load())
	{
		delete tex;
		return nullptr;
	}

	return tex;
}

void Dx12RenderSystem::buildMassResource()
{
	bool msaa = DX12Helper::getSingleton().hasMsaa();
	D3D12_RESOURCE_DESC msaaRTDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DX12Helper::getSingleton().getBackBufferFormat(),
		mRenderWindow->getWidth(),
		mRenderWindow->getHeight(),
		1, // This render target view has only one texture.
		1, // Use a single mipmap level
		msaa ? 4 : 1
	);
	msaaRTDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	D3D12_CLEAR_VALUE msaaOptimizedClearValue = {};
	msaaOptimizedClearValue.Format = mBackBufferFormat;
	memcpy(msaaOptimizedClearValue.Color, mClearColor, sizeof(float) * 4);

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);

	auto device = DX12Helper::getSingleton().getDevice();
	ThrowIfFailed(device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&msaaRTDesc,
		D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
		&msaaOptimizedClearValue,
		IID_PPV_ARGS(m_msaaRenderTarget.ReleaseAndGetAddressOf())
	));

	m_msaaRenderTarget->SetName(L"MSAA Render Target");

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = mBackBufferFormat;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;

	device->CreateRenderTargetView(
		m_msaaRenderTarget.Get(), &rtvDesc,
		m_msaaRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	// Create an MSAA depth stencil view.
	D3D12_RESOURCE_DESC depthStencilDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		mDepthStencilFormat,
		mRenderWindow->getWidth(),
		mRenderWindow->getHeight(),
		1, // This depth stencil view has only one texture.
		1, // Use a single mipmap level.
		4
	);
	depthStencilDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
	depthOptimizedClearValue.Format = mDepthStencilFormat;
	depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
	depthOptimizedClearValue.DepthStencil.Stencil = 0;

	ThrowIfFailed(device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthOptimizedClearValue,
		IID_PPV_ARGS(m_msaaDepthStencil.ReleaseAndGetAddressOf())
	));

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = mDepthStencilFormat;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;

	device->CreateDepthStencilView(
		m_msaaDepthStencil.Get(), &dsvDesc,
		m_msaaDSVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
}


void Dx12RenderSystem::createFrameResource()
{
	auto device = DX12Helper::getSingleton().getDevice();

	mFrameList.resize(FRAME_RESOURCE_COUNT);

	for (int32_t i = 0; i < FRAME_RESOURCE_COUNT; i++)
	{
		mFrameList[i] = new Dx12Frame();
		mFrameList[i]->_initialise(i);
	}

	mCurrentFrame = mFrameList.front();
}


Shader* Dx12RenderSystem::createShader(ShaderInfo& sinfo)
{
	return new Dx12Shader(sinfo);
}

void* Dx12RenderSystem::createRenderableData()
{
	return new Dx12RenderableData(this);
}

ID3D12GraphicsCommandList* Dx12RenderSystem::getCommandList()
{
	return mCurrentFrame->getCommandList();
}

void Dx12RenderSystem::_setViewport(Viewport* vp)
{
	mViewport = vp;
	auto cam = vp->getCamera();

	
	mCamera = cam;
	UpdateMainPassCB(cam);
	
	
	RenderTarget* target;
	target = vp->getTarget();

	mActiveDx12RenderTarget = dynamic_cast<Dx12RenderTarget*>(target);
	mActiveDx12RenderTarget->preRender(mCurrentFrame->getCommandList());
}

EngineType Dx12RenderSystem::getRenderType()
{
	return EngineType_Dx12;
}

void Dx12RenderSystem::clearFrameBuffer(uint32 buffers,
	const ColourValue& colour,
	float depth, uint16 stencil)
{

	if (mActiveDx12RenderTarget->useMsaa())
	{
		D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			m_msaaRenderTarget.Get(),
			D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET);
		mCurrentFrame->getCommandList()->ResourceBarrier(1, &barrier);

		auto rtvDescriptor = m_msaaRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		auto dsvDescriptor = m_msaaDSVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		mCurrentFrame->getCommandList()->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);

		mCurrentFrame->getCommandList()->ClearRenderTargetView(rtvDescriptor, mClearColor, 0, nullptr);
		mCurrentFrame->getCommandList()->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	}
	else
	{
		auto backBuffer = mActiveDx12RenderTarget->getCurrentBackBuffer();


		auto backBufferView = mActiveDx12RenderTarget->CurrentBackBufferView();
		auto depthStencilView = mActiveDx12RenderTarget->DepthStencilView();
		// Clear the back buffer and depth buffer.
		mCurrentFrame->getCommandList()->ClearRenderTargetView(backBufferView, mClearColor, 0, nullptr);
		mCurrentFrame->getCommandList()->ClearDepthStencilView(depthStencilView, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

		// Specify the buffers we are going to render to.
		mCurrentFrame->getCommandList()->OMSetRenderTargets(1, &backBufferView, true, &depthStencilView);
	}
}

Ogre::RenderWindow* Dx12RenderSystem::createRenderWindow(
	const String& name, unsigned int width, unsigned int height,
	const NameValuePairList* miscParams)
{
	mRenderWindow = new Dx12RenderWindow(this);

	mRenderWindow->create(name, width, height, false, miscParams);

	attachRenderTarget(*mRenderWindow);

	return mRenderWindow;
}

bool Dx12RenderSystem::initDirect3D()
{
	auto helper = new DX12Helper(this);
	helper->createBaseInfo();

	auto device = helper->getDevice();
	mDx12TextureHandleManager = new Dx12TextureHandleManager(device);
	mDx12ShadowMap = new Dx12ShadowMap(
		device,
		mDx12TextureHandleManager, 
		mShadowSize, 
		mShadowSize);
	createFrameResource();
	CreateRtvAndDsvDescriptorHeaps();

	return true;
}

void Dx12RenderSystem::buildRootSignature()
{
	ID3D12Device* device = DX12Helper::getSingleton().getDevice();

	CD3DX12_DESCRIPTOR_RANGE texTable0;
	texTable0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0);

	CD3DX12_DESCRIPTOR_RANGE texTable1;
	texTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1, 0);

	CD3DX12_DESCRIPTOR_RANGE texTable2;
	texTable2.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 5, 2, 0);


	CD3DX12_ROOT_PARAMETER slotRootParameter[7];


	slotRootParameter[0].InitAsDescriptorTable(1, &texTable0, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[1].InitAsDescriptorTable(1, &texTable1, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[2].InitAsDescriptorTable(1, &texTable2, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[3].InitAsConstantBufferView(0);
	slotRootParameter[4].InitAsConstantBufferView(1);
	slotRootParameter[5].InitAsConstantBufferView(2);
	slotRootParameter[6].InitAsConstantBufferView(3);


	auto staticSamplers = GetStaticSamplers();


	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(7, slotRootParameter,
		(UINT)staticSamplers.size(), staticSamplers.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(device->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature)));
}

void Dx12RenderSystem::CreateRtvAndDsvDescriptorHeaps()
{
	auto device = DX12Helper::getSingleton().getDevice();
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = 6;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(device->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(mRtvHeap.GetAddressOf())));


	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 3;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(device->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(mDsvHeap.GetAddressOf())));

	auto rtvCpuStart = mRtvHeap->GetCPUDescriptorHandleForHeapStart();

	int rtvOffset = 0;

	CD3DX12_CPU_DESCRIPTOR_HANDLE cubeRtvHandles[6];
	for (int i = 0; i < 6; ++i)
		cubeRtvHandles[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(
			rtvCpuStart, 
			rtvOffset + i, 
			DX12Helper::getSingleton().getRtvDescriptorSize());


	//shadow map
	

	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvhandle(mDsvHeap->GetCPUDescriptorHandleForHeapStart(),
		2,
		DX12Helper::getSingleton().getDsvDescriptorSize());

	mDx12ShadowMap->buildDescriptors(dsvhandle);

	auto index = mDx12TextureHandleManager->allocStartIndex();
	auto nullSrv = mDx12TextureHandleManager->getCpuHandleByIndex(index);
	mNullSrv = mDx12TextureHandleManager->getGpuHandleByIndex(index);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	srvDesc.TextureCube.MipLevels = 1;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	device->CreateShaderResourceView(nullptr, &srvDesc, nullSrv);

	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
	
	index = mDx12TextureHandleManager->allocStartIndex();
	nullSrv = mDx12TextureHandleManager->getCpuHandleByIndex(index);
	mNullCubeSrv = mDx12TextureHandleManager->getGpuHandleByIndex(index);
	device->CreateShaderResourceView(nullptr, &srvDesc, nullSrv);

	// Create descriptor heaps for MSAA render target views and depth stencil views.
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc = {};
	rtvDescriptorHeapDesc.NumDescriptors = 1;
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	ThrowIfFailed(device->CreateDescriptorHeap(&rtvDescriptorHeapDesc,
		IID_PPV_ARGS(m_msaaRTVDescriptorHeap.ReleaseAndGetAddressOf())));

	D3D12_DESCRIPTOR_HEAP_DESC dsvDescriptorHeapDesc = {};
	dsvDescriptorHeapDesc.NumDescriptors = 1;
	dsvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

	ThrowIfFailed(device->CreateDescriptorHeap(&dsvDescriptorHeapDesc,
		IID_PPV_ARGS(m_msaaDSVDescriptorHeap.ReleaseAndGetAddressOf())));
}

void Dx12RenderSystem::renderImpl(Dx12Pass* pass)
{
	Camera* camera = mCamera;
	VertexData* vertexData = pass->mRenderable->getVertexData();
	IndexData* indexData = pass->mRenderable->getIndexData();
	auto vd = vertexData->vertexDeclaration;
	pass->mShader->updateInputDesc(vd);
	
	auto commandlist = mCurrentFrame->getCommandList();

	

	//bind texture

	if (pass->mPassState == PassState_Shadow)
	{
		commandlist->SetGraphicsRootDescriptorTable(mCubeMapIndex, mNullCubeSrv);
		commandlist->SetGraphicsRootDescriptorTable(mShadowMapIndex, mNullSrv);
	}
	else
	{
		commandlist->SetGraphicsRootDescriptorTable(mShadowMapIndex, mDx12ShadowMap->gpuSrvHandle());

		int32_t cubeIndex = pass->mDx12RenderableData->getCubeTexStartIndex();
		if (cubeIndex >= 0)
		{
			CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle = mDx12TextureHandleManager->getGpuHandleByIndex(cubeIndex);
			commandlist->SetGraphicsRootDescriptorTable(mCubeMapIndex, gpuHandle);
		}
	}

	int32_t startIndex = pass->mDx12RenderableData->getTexStartIndex();
	if (startIndex >= 0)
	{
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle = mDx12TextureHandleManager->getGpuHandleByIndex(startIndex);
		commandlist->SetGraphicsRootDescriptorTable(mTextureArrayIndex, gpuHandle);
	}

	//bind constant

	pass->mDx12RenderableData->updateData(pass, camera);
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = pass->mDx12RenderableData->getObjectAddress();
	commandlist->SetGraphicsRootConstantBufferView(mObjectConstantIndex, objCBAddress);
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = pass->mDx12RenderableData->getMaterialAddress();
	commandlist->SetGraphicsRootConstantBufferView(mMatConstantIndex, matCBAddress);


	//draw object

	vertexData->bind();
	if(indexData)
		indexData->getIndexBuffer()->bind();

	commandlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	IndexDataView* view = pass->mRenderable->getIndexView();

	if (view)
	{
		commandlist->DrawIndexedInstanced(
			view->mIndexCount,
			1, view->mIndexLocation, view->mBaseVertexLocation, 0);
		mTriangleCount += view->mIndexCount / 3;
	}
	else
	{
		commandlist->DrawInstanced(
			vertexData->vertexCount, 1, 0, 0);
		mTriangleCount += vertexData->vertexCount / 3;
	}
	mBatchCount++;
}


void Dx12RenderSystem::UpdateMainPassCB(Camera* camera)
{
	const Ogre::Matrix4& view = camera->getViewMatrix();
	const Ogre::Matrix4& proj = camera->getProjectMatrix();
	const Ogre::Vector3& camepos = camera->getDerivedPosition();

	Ogre::Matrix4 invView = view.inverse();
	Ogre::Matrix4 viewProj = proj * view;
	Ogre::Matrix4 invProj = proj.inverse();
	Ogre::Matrix4 invViewProj = viewProj.inverse();

	mFrameConstantBuffer.Shadow = 0;
	
	int width = mRenderWindow->getWidth();
	int height = mRenderWindow->getHeight();

	mFrameConstantBuffer.View = view.transpose();
	mFrameConstantBuffer.InvView = invView.transpose();
	mFrameConstantBuffer.Proj = proj.transpose();
	mFrameConstantBuffer.InvProj = invProj.transpose();
	mFrameConstantBuffer.ViewProj = viewProj.transpose();
	mFrameConstantBuffer.InvViewProj = invViewProj.transpose();
	mFrameConstantBuffer.ShadowTransform = mShadowTransform;
	mFrameConstantBuffer.EyePosW = { camepos.x, camepos.y, camepos.z};
	mFrameConstantBuffer.RenderTargetSize = Ogre::Vector2((float)width, (float)height);
	mFrameConstantBuffer.InvRenderTargetSize = Ogre::Vector2(1.0f / width, 1.0f / height);
	mFrameConstantBuffer.NearZ = 0.1f;
	mFrameConstantBuffer.FarZ = 10000.0f;
	mFrameConstantBuffer.TotalTime += Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
	mFrameConstantBuffer.DeltaTime = Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
	mFrameConstantBuffer.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	mFrameConstantBuffer.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	mFrameConstantBuffer.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
	mFrameConstantBuffer.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	mFrameConstantBuffer.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
	mFrameConstantBuffer.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	mFrameConstantBuffer.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };
	

	UploadBuffer<FrameConstantBuffer>* cb = mCurrentFrame->getCameraFrameData(camera);
	cb->CopyData(0, mFrameConstantBuffer);

	D3D12_GPU_VIRTUAL_ADDRESS frameAddress = cb->Resource()->GetGPUVirtualAddress();
	mCurrentFrame->getCommandList()->SetGraphicsRootConstantBufferView(
		mMainConstantIndex, frameAddress);
}


void Dx12RenderSystem::UpdateShadowTransform(float delta)
{
	mLightRotationAngle += 0.02f * delta;

	Ogre::Quaternion rotate(Ogre::Radian(mLightRotationAngle), Ogre::Vector3(0.0f, 1.0f, 0.0f));

	Ogre::Matrix4 R = Ogre::Matrix4::IDENTITY;

	R.makeTransform(Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Vector3(1.0f, 1.0f, 1.0f), rotate);

	for (int i = 0; i < 3; ++i)
	{
		Ogre::Vector3 lightDir = mBaseLightDirections[i];
		lightDir = R * lightDir;
		mRotatedLightDirections[i] = lightDir;
	}

	// Only the first "main" light casts a shadow.
	Ogre::Vector3 lightDir = mRotatedLightDirections[0];
	Ogre::Vector3 tmp = mRotatedLightDirections[0];
	tmp.x *= -2.0f * mSceneBounds.getRadius();
	tmp.y *= -2.0f * mSceneBounds.getRadius();
	tmp.z *= -2.0f * mSceneBounds.getRadius();
	Ogre::Vector3 lightPos = tmp;
	Ogre::Vector3 targetPos = mSceneBounds.getCenter();
	Ogre::Vector3 lightUp = Ogre::Vector3(0.0f, 1.0f, 0.0f);

	Ogre::Matrix4 lightView = Ogre::Math::makeLookAtLH(lightPos, targetPos, lightUp);

	mLightPosW = lightPos;

	// Transform bounding sphere to light space.
	Ogre::Vector3 sphereCenterLS = lightView * targetPos;

	// Ortho frustum in light space encloses scene.
	float l = sphereCenterLS.x - mSceneBounds.getRadius();
	float b = sphereCenterLS.y - mSceneBounds.getRadius();
	float n = sphereCenterLS.z - mSceneBounds.getRadius();
	float r = sphereCenterLS.x + mSceneBounds.getRadius();
	float t = sphereCenterLS.y + mSceneBounds.getRadius();
	float f = sphereCenterLS.z + mSceneBounds.getRadius();

	mLightNearZ = n;
	mLightFarZ = f;
	Ogre::Matrix4 lightProj = Ogre::Math::makeOrthographicOffCenterLH(l, r, b, t, n, f);

	// Transform NDC space [-1,+1]^2 to texture space [0,1]^2
	Ogre::Matrix4 T(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	Ogre::Matrix4 S = lightView * lightProj * T;
	mLightView =  lightView.transpose();
	mLightProj = lightProj.transpose();
	mShadowTransform = S.transpose();
}

void Dx12RenderSystem::updateShadowPassCB()
{
	
}


