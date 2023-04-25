#include "OgreHeader.h"
#include "engine_struct.h"
#include "dx12Renderable.h"
#include "shader.h"
#include "OgreMaterial.h"
#include "renderSystem.h"
#include "dx12Shader.h"
#include "dx12RenderSystem.h"
#include "dx12Texture.h"
#include "OgreCamera.h"
#include "OgreTextureUnit.h"
#include "dx12TextureHandleManager.h"
#include "OgreRenderable.h"
#include "dx12Helper.h"


Dx12RenderableData::Dx12RenderableData(Dx12RenderSystem* engine)
{
	mEngine = engine;
	ID3D12Device* device = DX12Helper::getSingleton().getDevice();
	mFrameRenderableDatas.resize(FRAME_RESOURCE_COUNT);

	for (int32_t i = 0; i < FRAME_RESOURCE_COUNT; i++)
	{
		mFrameRenderableDatas[i].mObjectCB = 
			std::make_unique<UploadBuffer<ObjectConstantBuffer>>(device, 1, true);
		mFrameRenderableDatas[i].mMaterialCB = 
			std::make_unique<UploadBuffer<MaterialConstantBuffer>>(device, 1, true);
		mFrameRenderableDatas[i].mPBrMaterialCB = 
			std::make_unique<UploadBuffer<PbrMaterialConstanceBuffer>>(device, 1, true);
		mFrameRenderableDatas[i].mSkinnedCB = 
			std::make_unique<UploadBuffer<SkinnedConstantBuffer>>(device, 1, true);
	}
    
	
}

D3D12_GPU_VIRTUAL_ADDRESS Dx12RenderableData::getObjectAddress()
{
    return mCurrentFrameData->mObjectCB->Resource()->GetGPUVirtualAddress();
}

D3D12_GPU_VIRTUAL_ADDRESS Dx12RenderableData::getMaterialAddress()
{
    return mCurrentFrameData->mMaterialCB->Resource()->GetGPUVirtualAddress();
}

D3D12_GPU_VIRTUAL_ADDRESS Dx12RenderableData::getSkinedAddress()
{
	return mCurrentFrameData->mSkinnedCB->Resource()->GetGPUVirtualAddress();
}

void Dx12RenderableData::updateObjectConstantBuffer()
{
	mCurrentFrameData->mObjectCB->CopyData(0, mCurrentFrameData->mObjectConstantBuffer);
}

void Dx12RenderableData::updateMaterialConstantBuffer()
{
	mCurrentFrameData->mMaterialCB->CopyData(0, mCurrentFrameData->mMaterialConstantBuffer);
}

void Dx12RenderableData::updatePbrMaterialConstantBuffer()
{
	mCurrentFrameData->mPBrMaterialCB->CopyData(0, mCurrentFrameData->mPbrMaterialConstanceBuffer);
}

void Dx12RenderableData::updateSkinedConstanctBuffer(RawData* rd)
{
	mCurrentFrameData->mSkinnedCB->CopyData(rd->mData, rd->mDataSize);
}

void Dx12RenderableData::buildMaterial(Material* mat)
{
	if (mat->isPbr())
	{
		buildPbrMaterial(mat);
	}
	else
	{
		buildCommonMaterial(mat);
	}
}

void Dx12RenderableData::updateCurrentFrame(int32_t index)
{
	mCurrentFrameData = &mFrameRenderableDatas[index];
}

void Dx12RenderableData::updateData(Dx12Pass* pass, ICamera* cam)
{
	const Ogre::Matrix4& model = pass->mRenderable->getModelMatrix();
	mCurrentFrameData->mObjectConstantBuffer.world = model.transpose();
	mCurrentFrameData->mObjectConstantBuffer.invWorld = model.inverse().transpose();
	{
		const Ogre::Matrix4& view = cam->getViewMatrix();
		const Ogre::Matrix4& proj = cam->getProjectMatrix();
		//mCurrentFrameData->mObjectConstantBuffer.worldViewProj = (model * view * proj);
		mCurrentFrameData->mObjectConstantBuffer.worldViewProj = (proj * view * model).transpose();
	}

	const MaterialConstantBuffer& mcb = pass->mMaterial->getMatInfo();

	if (pass->mMaterial->isPbr())
	{
		mCurrentFrameData->mPbrMaterialConstanceBuffer.TexScale = mcb.TexScale;
		mCurrentFrameData->mPbrMaterialConstanceBuffer.TexTransform = mcb.TexTransform;
	}
	else
	{
		if (pass->mMaterial->getTextureUnitCount())
		{
			auto unit = pass->mMaterial->getTextureUnit(0);
			mCurrentFrameData->mMaterialConstantBuffer.TexTransform =
				unit->getTextureTransform().transpose();
		}
		
	}
	

	updateObjectConstantBuffer();
	updateMaterialConstantBuffer();

	/*if (pass->mRenderListType == RenderListType_Transparent)
	{
		materialConstantBuffer.DiffuseAlbedo = Ogre::Vector4(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else
	{
		materialConstantBuffer.DiffuseAlbedo = Ogre::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}*/

	
}

void Dx12RenderableData::buildPbrMaterial(Material* mat)
{
	if (mTexStartIndex >= 0 || mCubeTexStartIndex >= 0)
	{
		return;
	}
	auto texs = mat->getAllTexureUnit();

	int32_t texCount = 0;
	for (auto& tex : texs)
	{
		Dx12Texture* current = (Dx12Texture*)tex->getRaw();

		if (current->isCubeTexture())
		{
			mCubeTexCount++;
		}
		else
		{
			mTexCount++;
		}


	}

	if (mCubeTexCount > 0)
	{
		Dx12TextureHandleManager* mgr = mEngine->getTextureHandleManager();
		mCubeTexStartIndex = mgr->allocStartIndex(mCubeTexCount);
		if (mCubeTexStartIndex < 0)
		{
			assert(false);
		}
		int32_t offset = 0;
		for (auto& tex : texs)
		{
			Dx12Texture* current = (Dx12Texture*)tex->getRaw();

			if (current->isCubeTexture())
			{
				current->buildDescriptorHeaps(mCubeTexStartIndex + offset);
				TextureProperty* texProperty = current->getTextureProperty();
				updatePbrTextureIndex(texProperty, offset);
				offset++;
			}
		}
	}
	if (mTexCount > 0)
	{
		Dx12TextureHandleManager* mgr = mEngine->getTextureHandleManager();
		mTexStartIndex = mgr->allocStartIndex(mTexCount);
		if (mTexStartIndex < 0)
		{
			assert(false);
		}
		int32_t offset = 0;
		for (auto& tex : texs)
		{
			Dx12Texture* current = (Dx12Texture*)tex->getRaw();
			TextureProperty* texProperty = current->getTextureProperty();
			if (current->isCubeTexture())
			{
				current->buildDescriptorHeaps(mTexStartIndex + offset);
				updatePbrTextureIndex(texProperty, offset);
				offset++;
			}
		}
	}
}

void Dx12RenderableData::buildCommonMaterial(Material* mat)
{
	auto texs = mat->getAllTexureUnit();

	int32_t texCount = 0;
	for (auto& tex : texs)
	{
		Dx12Texture* current = (Dx12Texture*)tex->getRaw();
		if (current->isCubeTexture())
		{
			mCubeTexCount++;
		}
		else
		{
			mTexCount++;
		}
	}

	if (mCubeTexCount > 0)
	{
		Dx12TextureHandleManager* mgr = mEngine->getTextureHandleManager();

		if (mCubeTexStartIndex < 0)
		{
			mCubeTexStartIndex = mgr->allocStartIndex(mCubeTexCount);
		}
		
		int32_t offset = 0;
		for (auto& tex : texs)
		{
			Dx12Texture* current = (Dx12Texture*)tex->getRaw();

			if (current->isCubeTexture())
			{
				current->buildDescriptorHeaps(mCubeTexStartIndex + offset);
				offset++;
			}
		}
	}
	if (mTexCount > 0)
	{
		Dx12TextureHandleManager* mgr = mEngine->getTextureHandleManager();
		if (mTexStartIndex < 0)
		{
			mTexStartIndex = mgr->allocStartIndex(mTexCount);
		}
		
		int32_t offset = 0;
		for (auto& tex : texs)
		{
			Dx12Texture* current = (Dx12Texture*)tex->getRaw();
			bool has = false;
			if (!current->isCubeTexture())
			{
				current->buildDescriptorHeaps(mTexStartIndex + offset);
				offset++;
				has = true;
			}
			if (!has)
			{
				int kk = 0;
			}
		}
	}
	else
	{
		int kk = 0;
	}
}

//TextureType_AmbientOcclusion = 2,
//TextureType_NormalMap = 3,
//TextureType_Emissive = 4,
//TextureType_MetalRoughness = 5,
//TextureType_IBL_Diffuse = 6,
//TextureType_IBL_Specular = 7
void Dx12RenderableData::updatePbrTextureIndex(Ogre::TextureProperty* texProperty, uint32_t index)
{
	switch (texProperty->_pbrType)
	{
	case TextureTypePbr_Albedo:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mAlbedoIndex = index;
		break;
	case TextureTypePbr_NormalMap:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mNormalMapIndex = index;
		break;
	case TextureTypePbr_Emissive:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mEmissiveIndex = index;
		break;
	case TextureTypePbr_MetalRoughness:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mMetalRoughnessIndex = index;
		break;
	case TextureTypePbr_BRDF_LUT:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mBrdfLutIndex = index;
		break;
	case TextureTypePbr_IBL_Diffuse:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mIBLDiffuseIndex = index;
		break;
	case TextureTypePbr_IBL_Specular:
		mCurrentFrameData->mPbrMaterialConstanceBuffer.mIBLSpecularIndex = index;
		break;
	default:
		assert(false);
		break;
	}
}

int32_t Dx12RenderableData::getTexStartIndex()
{
	return mTexStartIndex;
}

int32_t Dx12RenderableData::getCubeTexStartIndex()
{
	return mCubeTexStartIndex;
}
