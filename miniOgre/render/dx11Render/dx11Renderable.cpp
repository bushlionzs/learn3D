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




Dx11RenderableData::Dx11RenderableData(Ogre::Renderable* r):RenderableData(r)
{
	_initialise();
}

Dx11RenderableData::~Dx11RenderableData()
{

}


void Dx11RenderableData::updateData(Dx11Pass& pass, ICamera* cam)
{
	auto dx11Context = DX11Helper::getSingleton().getDeviceContext();
	const Ogre::Matrix4& model = pass._render->getModelMatrix();
	mObjectConstantBuffer.world = model.transpose();

	{
		const Ogre::Matrix4& view = cam->getViewMatrix();
		const Ogre::Matrix4& proj = cam->getProjectMatrix();
		mObjectConstantBuffer.projector = pass._render->getProjectorMatrix();
		Ogre::Matrix4 T(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f);
		mObjectConstantBuffer.worldViewProj = model.transpose() * view * proj;
	}

	updateObject(cam);

	applyMaterialTexture(pass._mat);
	
	ID3D11VertexShader* vertexShader = pass._shader->getVertexShader();
	ID3D11PixelShader* pixelShader = pass._shader->getPixelShader();

	dx11Context->VSSetShader(vertexShader, nullptr, 0);
	dx11Context->PSSetShader(pixelShader, nullptr, 0);

	// VS常量缓冲区对应HLSL寄存于b0的常量缓冲区
	ID3D11Buffer* buf = getObjectBuffer(cam);
	dx11Context->VSSetConstantBuffers(0, 1, &buf);

	ID3D11Buffer* matbuf = nullptr;
	
	if (pass._mat->isPbr())
	{
		matbuf = mPbrMaterialCB->Resource();
	}
	else
	{
		matbuf = mMaterialCB->Resource();
	}
	
	dx11Context->VSSetConstantBuffers(2, 1, &matbuf);
	dx11Context->PSSetConstantBuffers(2, 1, &matbuf);
	
	
	

	RawData* rd = pass._render->getSkinnedData(2);
	if (rd)
	{
		mSkinnedCB->CopyData(rd->mData, rd->mDataSize);
		buf = mSkinnedCB->Resource();
		dx11Context->VSSetConstantBuffers(3, 1, &buf);
	}

	DX11Helper::getSingleton()._setDepthBufferWriteEnabled(
		pass._mat->isWriteDepth());
	

	auto blendState = pass._mat->getBlendState();
	DX11Helper::getSingleton()._setColourBlendState(blendState);

	auto cullingmode = pass._mat->getCullMode();
	DX11Helper::getSingleton()._setCullingMode(cullingmode);
	
}

void Dx11RenderableData::_initialise()
{
	mMaterialCB =
		std::make_unique<Dx11UploadBuffer<MaterialConstantBuffer>>(1, true);
	mSkinnedCB = 
		std::make_unique<Dx11UploadBuffer<SkinnedConstantBuffer>>(1, true);
}

void Dx11RenderableData::updateObject(ICamera* cam)
{
	auto itor = mCamaraDataMap.find(cam);
	if (itor != mCamaraDataMap.end())
	{
		itor->second->CopyData(0, mObjectConstantBuffer);
	}
	else
	{
		auto tmp = std::make_shared< Dx11UploadBuffer<ObjectConstantBuffer>>(1, true);
		mCamaraDataMap[cam] = tmp;
		tmp->CopyData(0, mObjectConstantBuffer);
	}
}

ID3D11Buffer* Dx11RenderableData::getObjectBuffer(ICamera* cam)
{
	auto itor = mCamaraDataMap.find(cam);
	if (itor != mCamaraDataMap.end())
	{
		return itor->second->Resource();
	}
	return nullptr;
}

void Dx11RenderableData::applyMaterialTexture(Material* mat)
{
	auto dx11Context = DX11Helper::getSingleton().getDeviceContext();
	if (mat->isPbr())
	{
		if (!mPbrMaterialCB)
		{
			mPbrMaterialCB = 
				std::make_unique<Dx11UploadBuffer<PbrMaterialConstanceBuffer>>(1, true);
		}
		mPbrMaterialCB->CopyData(0, mPbrMaterialConstanceBuffer);
		
		auto texs = mat->getAllTexureUnit();
		std::vector<ID3D11ShaderResourceView*> res(6);
		res.reserve(texs.size());
		std::vector<ID3D11ShaderResourceView*> rescube(2);
		rescube.reserve(texs.size());
		for (int i = 0; i < texs.size(); i++)
		{
			Dx11Texture* current = (Dx11Texture*)texs[i]->getRaw();
			ID3D11ShaderResourceView* texView = current->getResourceView();

			TextureProperty* tp = texs[i]->getTextureProperty();

			if (current->isCubeTexture())
			{
				uint32_t index = tp->_pbrType - TextureTypePbr_IBL_Diffuse;
				rescube[index] = texView;
			}
			else
			{
				uint32_t index = tp->_pbrType - TextureTypePbr_Albedo;
				res[index] = texView;
			}
			
		}

		if (!rescube.empty())
		{
			dx11Context->PSSetShaderResources(0, rescube.size(), rescube.data());
		}

		if (!res.empty())
		{
			dx11Context->PSSetShaderResources(3, res.size(), res.data());
		}
	}
	else
	{
		const MaterialConstantBuffer& mcb = mat->getMatInfo();
		if (mat->getTextureUnitCount())
		{
			auto unit = mat->getTextureUnit(0);
			mMaterialConstantBuffer.TexTransform =
				unit->getTextureTransform().transpose();

			mMaterialCB->CopyData(0, mMaterialConstantBuffer);
		}
		auto texs = mat->getAllTexureUnit();
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

		if (!rescube.empty())
		{
			dx11Context->PSSetShaderResources(0, rescube.size(), rescube.data());
		}

		if (!res.empty())
		{
			dx11Context->PSSetShaderResources(3, res.size(), res.data());
		}
	}
}