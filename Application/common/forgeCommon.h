#pragma once
#include <OgreCommon.h>
#define STRUCT(NAME) struct NAME
#define DATA(TYPE, NAME, SEM) TYPE NAME
STRUCT(VBConstants)
{
	DATA(uint32_t, indexOffset, None);
	DATA(uint32_t, pad_0, None);
	DATA(uint32_t, pad_1, None);
	DATA(uint32_t, pad_2, None);
};

STRUCT(Transform)
{
	DATA(Ogre::Matrix4, vp, None);
	DATA(Ogre::Matrix4, mvp, None);
	DATA(Ogre::Matrix4, projection, None);
	DATA(Ogre::Matrix4, invVP, None);
};

STRUCT(CullingViewPort)
{
	DATA(Ogre::Vector2, windowSize, None);
	DATA(uint32_t, sampleCount, None);
	DATA(uint32_t, _pad0, None);
};

STRUCT(PerFrameVBConstants)
{
	DATA(Transform, transform[5], None);
	DATA(CullingViewPort, cullingViewports[5], None);
	DATA(uint32_t, numViewports, None);
};

STRUCT(ObjectUniformBlock)
{
	DATA(Ogre::Matrix4, worldViewProjMat, None);
	DATA(uint32_t, viewID, None);
};

STRUCT(FilterDispatchGroupData)
{
	DATA(uint32_t, meshIndex, None);
	DATA(uint32_t, indexOffset, None);
	DATA(uint32_t, instanceDataIndex, None);
	DATA(uint32_t, geometrySet_faceCount, None);
};

STRUCT(MeshConstants)
{
	DATA(uint32_t, indexOffset, None);
	DATA(uint32_t, vertexOffset, None);
	DATA(uint32_t, materialID, None);
	DATA(uint32_t, twoSided, None);
};

STRUCT(VertexDataBuffer)
{
	DATA(Ogre::Vector3, vertexPosition, None);
	DATA(Ogre::Vector2, vertexTextureUV, None);
};

enum MaterialFlagBits
{
	MATERIAL_FLAG_NONE = 0,
	MATERIAL_FLAG_TWO_SIDED = (1 << 0),
	MATERIAL_FLAG_ALPHA_TESTED = (1 << 1),
	MATERIAL_FLAG_TRANSPARENT = (1 << 2),
	MATERIAL_FLAG_DOUBLE_VOXEL_SIZE = (1 << 3),
	MATERIAL_FLAG_ALL = MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE
};


#define VIEW_CAMERA          0
#define VIEW_SHADOW          1
std::shared_ptr<Mesh> loadSanMiguel(const std::string& name);