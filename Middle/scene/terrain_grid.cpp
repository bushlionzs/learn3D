#include "OgreHeader.h"
#include "terrain_grid.h"
#include "terrain_info.h"
#include "terrain.h"
#include "OgreMaterial.h"
#include "OgreSceneNode.h"

TerrainGrid::TerrainGrid(SceneNode* parent,
	Terrain* owner,
	int xbase, int zbase, int xsize, int zsize)
	:MoveObject(std::string("TerrainGrid"))
{
	mTerrain = owner;
	mXBase = xbase;
	mZBase = zbase;
	mXSize = xsize;
	mZSize = zsize;
	/*mName = Ogre::String("TerrainTile_") + mNode->getn*/

	mNode = parent->createChildSceneNode(std::string());
	mNode->attachObject(this);
}

TerrainGrid::~TerrainGrid()
{

}

void TerrainGrid::buildMaterialBucketMap(MaterialBucketMap& materialBucketMap)
{
	//得到地形数据
	TerrainInfo* data = mTerrain->getTerrainInfo();
	int patch = data->mXGridSize;
	int xbase = mXBase;
	int zbase = mZBase;
	int xsize = mXSize;
	int zsize = mZSize;

	for (int z = 0; z < zsize; ++z)
	{
		for (int x = 0; x < xsize; ++x)
		{
			//格子索引
			size_t grid = (z + zbase) * patch + (x + xbase);
			//格子信息
			const TerrainInfo::GridInfoStr& gridInfo = data->mGridInfos[grid];

			// If doesn't exists base layer, nothing to do
			if (!gridInfo.imageLayers[0].imageAreaId)
			{
				assert(!gridInfo.imageLayers[1].imageAreaId);
				continue;
			}
			//是否有2层纹理
			size_t layerIndex = gridInfo.imageLayers[1].imageAreaId ? 1 : 0;
			//得到材质信息(创建纹理、创建材质)
			auto material = mTerrain->_getGridMaterial(gridInfo, 0, x + xbase, z + zbase);
			//材质句柄+材质
			//MaterialBucketMap::iterator it = materialBucketMap.find(material->getHandle());
			MaterialBucketMap::iterator it = materialBucketMap.find(material->getName());
			if (it == materialBucketMap.end())//材质没有的话，添加
			{
				std::pair<MaterialBucketMap::iterator, bool> inserted =
					materialBucketMap.insert(
						//MaterialBucketMap::value_type(material->getHandle(),
						//							  MaterialBucket(layerIndex, material)));
						MaterialBucketMap::value_type(material->getName(),
							MaterialBucket(layerIndex, material)));
				assert(inserted.second);
				it = inserted.first;

				// Pre-reserve memory for less thrashing
				it->second.grids.reserve(zsize * xsize / data->mImages.size());
			}
			it->second.grids.push_back(grid);
			//保存材质名称
			mMaterialNames.insert(material->getName());
		}
	}
}

bool TerrainGrid::buildMaterialBucketMapData(TempMaterialBucketMap& tempMaterialBucketMap)
{
	TerrainInfo* pTerrainInfo = mTerrain->getTerrainInfo();
	int patch = pTerrainInfo->mXGridSize;
	int xbase = mXBase;
	int zbase = mZBase;
	int xsize = mXSize;
	int zsize = mZSize;

	for (int z = 0; z < zsize; ++z)
	{
		for (int x = 0; x < xsize; ++x)
		{
			//格子索引
			size_t grid = (z + zbase) * patch + (x + xbase);

			if (grid < 0 || grid > 102400)
			{
				int kk = 0;
			}
			//格子信息
			const TerrainInfo::GridInfoStr& gridInfo = pTerrainInfo->mGridInfos[grid];

			// If doesn't exists base layer, nothing to do
			if (!gridInfo.imageLayers[0].imageAreaId)
			{
				assert(!gridInfo.imageLayers[1].imageAreaId);
				continue;
			}
			//是否有2层纹理
			size_t layerIndex = gridInfo.imageLayers[1].imageAreaId ? 1 : 0;
			//得到材质信息
			const Terrain::ThreadMatStr& MatParam = 
				mTerrain->_getGridMaterialData(gridInfo, 0, x + xbase, z + zbase);
			//材质句柄+材质
			TempMaterialBucketMap::iterator it = tempMaterialBucketMap.find(MatParam.matName);
			if (it == tempMaterialBucketMap.end())//添加
			{
				ThreadMaterialBucketStr   tempMat;
				tempMat.layerIndex = layerIndex;
				tempMat.matName = MatParam.matName;
				tempMat.textureId0 = MatParam.id.textureId0;
				tempMat.textureId1 = MatParam.id.textureId1;
				tempMat.depthBias = MatParam.id.depthBias;
				tempMat.lightmapId = MatParam.id.lightmapId;
				std::pair<TempMaterialBucketMap::iterator, bool> inserted =
					tempMaterialBucketMap.insert(TempMaterialBucketMap::value_type(MatParam.matName,
						tempMat));
				assert(inserted.second);
				it = inserted.first;
				//分配空间
				it->second.grids.reserve(zsize * xsize / pTerrainInfo->mImages.size());
			}
			it->second.grids.push_back(grid);//格子插入
		}
	}
	return true;
}