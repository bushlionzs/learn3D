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
	mRenderSystemName = "Directx12";
}


Dx12RenderSystem::~Dx12RenderSystem()
{

}

bool Dx12RenderSystem::engineInit()
{
	RenderSystem::engineInit();
	new Dx12HardwareBufferManager(this);

	auto helper = new DX12Helper(this);
	helper->createBaseInfo();

	auto device = helper->getDevice();
	mDx12TextureHandleManager = new Dx12TextureHandleManager(device);
	createFrameResource();
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
	auto commandList = DX12Helper::getSingleton().getCurrentCommandList();

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

void Dx12RenderSystem::_setViewport(ICamera* cam, Ogre::Viewport* vp)
{
	mViewport = vp;
	
	mCamera = cam;
	updateMainPassCB(cam);
	
	
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
	mActiveDx12RenderTarget->clearFrameBuffer(buffers, colour, depth, stencil);
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

void Dx12RenderSystem::renderImpl(Dx12Pass* pass)
{
	ICamera* camera = mCamera;
	VertexData* vertexData = pass->mRenderable->getVertexData();
	IndexData* indexData = pass->mRenderable->getIndexData();
	auto vd = vertexData->vertexDeclaration;
	pass->mShader->updateInputDesc(vd);
	
	auto commandlist = mCurrentFrame->getCommandList();


	//bind texture
	int32_t cubeIndex = pass->mDx12RenderableData->getCubeTexStartIndex();
	if (cubeIndex >= 0)
	{
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle = mDx12TextureHandleManager->getGpuHandleByIndex(cubeIndex);
		commandlist->SetGraphicsRootDescriptorTable(mCubeMapIndex, gpuHandle);
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


void Dx12RenderSystem::updateMainPassCB(ICamera* camera)
{
	const Ogre::Matrix4& view = camera->getViewMatrix();
	const Ogre::Matrix4& proj = camera->getProjectMatrix();
	const Ogre::Vector3& camepos = camera->getDerivedPosition();

	Ogre::Matrix4 invView = view.inverse();
	Ogre::Matrix4 viewProj = proj * view;
	Ogre::Matrix4 invProj = proj.inverse();
	Ogre::Matrix4 invViewProj = viewProj.inverse();

	mFrameConstantBuffer.Shadow = 0;

	if (camera->getCameraType() == CameraType_Light)
	{
		mFrameConstantBuffer.Shadow = 1;

		mFrameConstantBuffer.ShadowTransform = 
			proj * view;

		mFrameConstantBuffer.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
		mFrameConstantBuffer.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
		mFrameConstantBuffer.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
	}
	
	int width = mRenderWindow->getWidth();
	int height = mRenderWindow->getHeight();

	mFrameConstantBuffer.View = view.transpose();
	mFrameConstantBuffer.InvView = invView.transpose();
	mFrameConstantBuffer.Proj = proj.transpose();
	mFrameConstantBuffer.InvProj = invProj.transpose();
	mFrameConstantBuffer.ViewProj = viewProj.transpose();
	mFrameConstantBuffer.InvViewProj = invViewProj.transpose();
	
	mFrameConstantBuffer.EyePosW = { camepos.x, camepos.y, camepos.z};
	mFrameConstantBuffer.RenderTargetSize = Ogre::Vector2((float)width, (float)height);
	mFrameConstantBuffer.InvRenderTargetSize = Ogre::Vector2(1.0f / width, 1.0f / height);
	mFrameConstantBuffer.NearZ = 0.1f;
	mFrameConstantBuffer.FarZ = 10000.0f;
	mFrameConstantBuffer.TotalTime += Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
	mFrameConstantBuffer.DeltaTime = Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
	
	UploadBuffer<FrameConstantBuffer>* cb = mCurrentFrame->getCameraFrameData(camera);
	cb->CopyData(0, mFrameConstantBuffer);

	D3D12_GPU_VIRTUAL_ADDRESS frameAddress = cb->Resource()->GetGPUVirtualAddress();
	mCurrentFrame->getCommandList()->SetGraphicsRootConstantBufferView(
		mMainConstantIndex, frameAddress);
}



