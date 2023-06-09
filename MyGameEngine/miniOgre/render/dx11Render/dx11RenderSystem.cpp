#include "OgreHeader.h"
#include "dx11RenderSystem.h"
#include "dx11Renderable.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "dx11Texture.h"
#include "dx11HardwareBufferManager.h"
#include <DirectXColors.h>
#include "OgreMoveObject.h"
#include "vertex_data.h"
#include "index_data.h"
#include "dx11Shader.h"
#include "OgreCamera.h"
#include "dx11Helper.h"
#include "dx11RenderWindow.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"
#include "OgreViewport.h"
#include "dx11RenderTarget.h"
#include "OgreRoot.h"

Dx11RenderSystem::Dx11RenderSystem(HWND hWnd)
{
	mRenderSystemName = "Directx11";
}


Dx11RenderSystem::~Dx11RenderSystem()
{

}

bool Dx11RenderSystem::engineInit()
{
	RenderSystem::engineInit();
	new Dx11HardwareBufferManager(this);


	new DX11Helper(this);

	DX11Helper::getSingleton()._initialise();
	mDx11Device = DX11Helper::getSingleton().getDevice();
	mDx11Context = DX11Helper::getSingleton().getDeviceContext();
	mFrameCB = 
		std::make_unique<Dx11UploadBuffer<FrameConstantBuffer>>(1, true);
    return true;
}

void Dx11RenderSystem::update(float delta)
{

}

void Dx11RenderSystem::frameStart()
{
	mTriangleCount = 0;
	mBatchCount = 0;
	mLoadResCount = 0;
	
	//mDx11Context->RSSetState(nullptr);
}

void Dx11RenderSystem::frameEnd()
{
	mRenderWindow->present();

}

void Dx11RenderSystem::_setViewport(Ogre::Viewport* vp)
{
	mViewport = vp;
	auto cam = vp->getCamera();

	mCamera = cam;
	updateFrame();

	RenderTarget* target;
	target = vp->getTarget();

	mActiveRenderTarget = dynamic_cast<Dx11RenderTarget*>(target);
	mActiveRenderTarget->preRender();
}

void Dx11RenderSystem::clearFrameBuffer(uint32 buffers,
	const Ogre::ColourValue& colour,
	float depth, uint16 stencil)
{
	mActiveRenderTarget->clearFrameBuffer(
		buffers, colour, depth, stencil);
}

Ogre::RenderWindow* Dx11RenderSystem::createRenderWindow(
	const String& name, unsigned int width, unsigned int height,
	const NameValuePairList* miscParams)
{
	mRenderWindow = new Dx11RenderWindow(this);

	mRenderWindow->create(name, width, height, false, miscParams);

	attachRenderTarget(*mRenderWindow);

	return mRenderWindow;
}

void Dx11RenderSystem::ready()
{
	NOTICE_LOG("Dx11RenderSystem ready");
}

void Dx11RenderSystem::preRender()
{
	
}

void Dx11RenderSystem::render(Renderable* r, RenderListType t)
{
	mDx11Pass._render = r;
	mDx11Pass._mat = r->getMaterial().get();

	mDx11Pass._mat->load();
	

	mDx11Pass._shader = (Dx11Shader*)mDx11Pass._mat->getShader().get();
	mDx11Pass._renderData = (Dx11RenderableData*)r->getRenderableData();
	
	renderImpl(mDx11Pass);
}

void Dx11RenderSystem::postRender()
{
	
}

Camera* Dx11RenderSystem::getCurrentCamera()
{
	return mCamera;
}

ITexture* Dx11RenderSystem::createTextureFromFile(const std::string& name, TextureProperty* texProperty)
{
	Dx11Texture* tex = new Dx11Texture(name, texProperty, this);

	if (!tex->load())
	{
		delete tex;
		return nullptr;
	}

	return tex;
}

Shader* Dx11RenderSystem::createShader(ShaderInfo& sinfo)
{
	Dx11Shader* shader = new Dx11Shader(sinfo, this);
	return shader;
}

void* Dx11RenderSystem::createRenderableData()
{
	return new Dx11RenderableData;
}

EngineType Dx11RenderSystem::getRenderType()
{
	return EngineType_Dx11;
}

void Dx11RenderSystem::updateFrame()
{
	Camera* camera = mCamera;

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
	mFrameConstantBuffer.EyePosW = { camepos.x, camepos.y, camepos.z };
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


	Dx11UploadBuffer<FrameConstantBuffer>* cb = mFrameCB.get();
	cb->CopyData(0, mFrameConstantBuffer);

	auto context = DX11Helper::getSingleton().getDeviceContext();

	ID3D11Buffer* buf = cb->Resource();
	context->VSSetConstantBuffers(1, 1, &buf);
}

void Dx11RenderSystem::renderImpl(Dx11Pass& pass)
{
	pass._renderData->updateData(pass, mCamera);
	DX11Helper::getSingleton().updateRenderState();
	VertexData* vertexData = pass._render->getVertexData();
	IndexData* indexData = pass._render->getIndexData();

	
	auto vd = vertexData->vertexDeclaration;
	pass._shader->updateInputDesc(vd);


	mDx11Context->IASetInputLayout(pass._shader->getLayoutEx());
	mDx11Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vertexData->bind();

	if (indexData)
	{
		indexData->mIndexBuffer->bind();
		IndexDataView* view = pass._render->getIndexView();
		mDx11Context->DrawIndexedInstanced(
			view->mIndexCount,
			1, view->mIndexLocation, view->mBaseVertexLocation, 0);
		mTriangleCount += view->mIndexCount / 3;
	}
	else
	{
		mDx11Context->DrawInstanced(
			vertexData->vertexCount,
			1, 0, 0);
		mTriangleCount += vertexData->vertexCount / 3;
	}
	mBatchCount++;
}