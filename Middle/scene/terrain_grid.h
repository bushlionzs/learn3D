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

struct ThreadMaterialBucketStr//材质桶
{
	ThreadMaterialBucketStr() {}
	String		           matName;	//材质名称
	std::shared_ptr<Material> material;	//材质
	std::vector<int32_t>   grids;		//格子Id
	int32_t 			   layerIndex;	//层索引
	int32_t				   textureId0;
	int32_t				   textureId1;
	int32_t				   depthBias;
	int32_t				   lightmapId;
};

struct MaterialBucket//材质桶
{
	size_t						layerIndex;	//层索引
	const std::shared_ptr<Material>  material;	//材质
	std::vector<int32_t>	   grids;		//格子Id
	MaterialBucket(size_t layerIndex, const std::shared_ptr<Material>& material)
		: layerIndex(layerIndex), material(material) { }
};

class Terrain;
class TerrainInfo;

class TerrainGrid: public MoveObject
{
public:
	typedef std::map<Ogre::String, ThreadMaterialBucketStr> TempMaterialBucketMap;//Key是材质名
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