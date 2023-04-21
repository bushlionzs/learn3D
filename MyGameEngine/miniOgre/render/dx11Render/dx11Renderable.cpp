#include "OgreHeader.h"
#include "dx11Renderable.h"
#include "OgreSceneNode.h"
#include "shader.h"
#include "OgreMaterial.h"
#include "renderSystem.h"
#include "dx11Shader.h"
#include "dx11RenderSystem.h"
#include "dx11Texture.h"
#include "OgreCamera.h"
#include "OgreTextureUnit.h"
#include <DirectXMath.h>
#include "vertex_data.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreD3D11Mappings.h"




Dx11RenderableData::Dx11RenderableData()
{
	_initialise();
}

Dx11RenderableData::~Dx11RenderableData()
{

}


void Dx11RenderableData::updateData(Dx11Pass& pass, Camera* cam)
{

	auto dx11Context = DX11Helper::getSingleton().getDeviceContext();
	const Ogre::Matrix4& model = pass._render->getModelMatrix();
	mObjectConstantBuffer.world = model.transpose();
	mObjectConstantBuffer.invWorld = model.inverse().transpose();
	{
		const Ogre::Matrix4& view = cam->getViewMatrix();
		const Ogre::Matrix4& proj = cam->getProjectMatrix();
		mObjectConstantBuffer.worldViewProj = (proj * view * model).transpose();
	}

	mObjectCB->CopyData(0, mObjectConstantBuffer);

	const MaterialConstantBuffer& mcb = pass._mat->getMatInfo();
	if (pass._mat->getTextureUnitCount())
	{
		auto unit = pass._mat->getTextureUnit(0);
		mMaterialConstantBuffer.TexTransform =
			unit->getTextureTransform().transpose();

		mMaterialCB->CopyData(0, mMaterialConstantBuffer);
	}
	
	
	ID3D11VertexShader* vertexShader = pass._shader->getVertexShader();
	ID3D11PixelShader* pixelShader = pass._shader->getPixelShader();

	dx11Context->VSSetShader(vertexShader, nullptr, 0);
	dx11Context->PSSetShader(pixelShader, nullptr, 0);

	// VS������������ӦHLSL�Ĵ���b0�ĳ���������
	ID3D11Buffer* buf = mObjectCB->Resource();
	dx11Context->VSSetConstantBuffers(0, 1, &buf);

	ID3D11Buffer* matbuf = mMaterialCB->Resource();
	dx11Context->VSSetConstantBuffers(2, 1, &matbuf);
	dx11Context->PSSetConstantBuffers(2, 1, &matbuf);
	
	
	

	RawData* rd = pass._render->getShaderConstantData(2);
	if (rd)
	{
		mSkinnedCB->CopyData(rd->mData, rd->mDataSize);
		buf = mSkinnedCB->Resource();
		dx11Context->VSSetConstantBuffers(3, 1, &buf);
	}

	auto texs = pass._mat->getAllTexureUnit();
	std::vector<ID3D11ShaderResourceView*> res;
	res.reserve(texs.size());
	std::vector<ID3D11ShaderResourceView*> rescube;
	rescube.reserve(texs.size());
	for (int i = 0; i < texs.size(); i++)
	{
		Dx11Texture* current = (Dx11Texture*)texs[i]->getRaw();
		ID3D11ShaderResourceView* texView = current->getResourceView();

		if (current->isCubeTexture())
		{
			rescube.push_back(texView);
		}
		else
		{
			res.push_back(texView);
		}
	}

	if (texs.size() == 0)
	{
		int kk = 0;
	}
	if (!rescube.empty())
	{
		dx11Context->PSSetShaderResources(0, rescube.size(), rescube.data());
	}
	
	if (!res.empty())
	{
		dx11Context->PSSetShaderResources(2, res.size(), res.data());
	}
	

	
	DX11Helper::getSingleton()._setDepthBufferWriteEnabled(
		pass._mat->isWriteDepth());
	

	auto blendState = pass._mat->getBlendState();
	DX11Helper::getSingleton()._setColourBlendState(blendState);

	
}

void Dx11RenderableData::_initialise()
{
	mObjectCB =
		std::make_unique<Dx11UploadBuffer<ObjectConstantBuffer>>(1, true);
	mMaterialCB =
		std::make_unique<Dx11UploadBuffer<MaterialConstantBuffer>>(1, true);
	mSkinnedCB = 
		std::make_unique<Dx11UploadBuffer<SkinnedConstantBuffer>>(1, true);
}
