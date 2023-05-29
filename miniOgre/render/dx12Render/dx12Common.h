#pragma once

#include "d3dutil.h"
#include "UploadBuffer.h"
#include "shader.h"
#include "engine_struct.h"

class Dx12Shader;
class Dx12RenderableData;
class Dx12Frame;

enum Dx12PassState
{
	PassState_Normal = 0,
	PassState_Shadow,
	PassState_CubeMap
};
#define FRAME_RESOURCE_COUNT 1

class Dx12Pass
{
public:
	Ogre::Material* mMaterial;
	Dx12Shader* mShader;
	Ogre::Renderable* mRenderable;
	uint32_t  mPassState;
	ID3D12RootSignature* mRootSignature;
	Dx12RenderableData* mDx12RenderableData;
	RenderListType mRenderListType;	
};