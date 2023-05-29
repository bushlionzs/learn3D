#pragma once
#include "OgreMaterial.h"
#include "OgreMoveObject.h"
enum VertexDataIndex
{
	VDI_ONE_LAYER_INDEX = 0,
	VDI_TWO_LAYERS_INDEX = 1,
	VDI_LAYER_COUNT = 2,
	VDI_LOD_INDEX = 2,
	VDI_COUNT = 3
};

struct ThreadMaterialBucketStr//����Ͱ
{
	ThreadMaterialBucketStr() {}
	String		           matName;	//��������
	std::shared_ptr<Material> material;	//����
	std::vector<int32_t>   grids;		//����Id
	int32_t 			   layerIndex;	//������
	int32_t				   textureId0;
	int32_t				   textureId1;
	int32_t				   depthBias;
	int32_t				   lightmapId;
};

struct MaterialBucket//����Ͱ
{
	size_t						layerIndex;	//������
	const std::shared_ptr<Material>  material;	//����
	std::vector<int32_t>	   grids;		//����Id
	MaterialBucket(size_t layerIndex, const std::shared_ptr<Material>& material)
		: layerIndex(layerIndex), material(material) { }
};

class Terrain;
class TerrainInfo;

class TerrainGrid: public MoveObject
{
public:
	typedef std::map<Ogre::String, ThreadMaterialBucketStr> TempMaterialBucketMap;//Key�ǲ�����
	typedef std::map<Ogre::String, MaterialBucket> MaterialBucketMap;
public:
	TerrainGrid(SceneNode* parent,
		Terrain* owner,
		int xbase, int zbase, int xsize, int zsize);
	~TerrainGrid();

	void buildMaterialBucketMap(MaterialBucketMap& materialBucketMap);
	bool buildMaterialBucketMapData(TempMaterialBucketMap& tempMaterialBucketMap);
protected:
	Terrain* mTerrain;

	int32_t   mXBase;
	int32_t   mZBase;
	int32_t   mXSize;
	int32_t   mZSize;

	std::set<std::string> mMaterialNames;

	SceneNode* mNode;
};