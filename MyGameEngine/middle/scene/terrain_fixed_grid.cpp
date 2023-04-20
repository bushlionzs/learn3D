#include "OgreHeader.h"
#include "terrain_fixed_grid.h"
#include "vertex_data.h"
#include "terrain.h"
#include "vertex_declaration.h"
#include "OgreHardwareVertexBuffer.h"
#include "custom_renderable.h"

//-----------------------------------------------------------------------
TerrainFixedGrid::TerrainFixedGrid(
	SceneNode* parent, 
	Terrain*owner,
	int32_t xbase, int32_t zbase, int32_t xsize, int32_t zsize, int32_t TileIndex)
    : TerrainGrid(parent, owner, xbase, zbase, xsize, zsize)
{
	mTileIndex = TileIndex;
	mBounds.setNull();
}

TerrainFixedGrid::~TerrainFixedGrid()
{
	
}

const std::vector<Renderable*>& TerrainFixedGrid::getRenderableList()
{
	return mRenderables;
}

const String& TerrainFixedGrid::getMovableType(void) const
{
	static const String type = "TerrainFixedGrid";
    return type;
}

void TerrainFixedGrid::_updateRenderQueue()//ÿ֡����
{
	
}

//-----------------------------------------------------------------------

bool TerrainFixedGrid::destoryGeometry(void)
{	
	return true;
}

bool TerrainFixedGrid::createGeometry(
	TerrainInfo* data,
	int32_t xbase, int32_t zbase, int32_t xsize, int32_t zsize)
{
	destoryGeometry();


	//��������ͼƬ
	Terrain* pTerrain = mTerrain;
	const String& tileName = data->getTerrainTileName(mTileIndex);
	TerrainInfo::GroundTileImageNameSet* pTexNameSet = NULL;

	auto iter = data->mGroundImageNameMap.find(tileName.c_str());
	if( iter != data->mGroundImageNameMap.end() )
	{
		pTexNameSet = &(iter->second);
	}
	if (NULL == pTexNameSet)
		return false;
	return true;

}
bool TerrainFixedGrid::directCreateGeometry(
	TerrainInfo* data, int xbase, int zbase, int xsize, int zsize )
{
	return true;
}
bool TerrainFixedGrid::createGeometryData( )
{
	static const unsigned short MAIN_BINDING = 0;

	{
		// vb��Դ����
		Terrain* pTerrain = mTerrain;

		//��ʼ����
		//��ò�����Ϣ(����������Ͳ���)
		TempMaterialBucketMap tempMaterialBucketMap;
		buildMaterialBucketMapData( tempMaterialBucketMap );	

		bool includeLightmap = mTerrain->_isLightmapUsed();

		mVertexDatas.resize(VDI_LAYER_COUNT);

		for (int32_t i = 0; i < VDI_LAYER_COUNT; i++)
		{
			mVertexDatas[i] = new VertexData;
		}

		//ÿ��ĸ�����Ŀ(������Ŀ)=���ݲ���������
		for (auto im = tempMaterialBucketMap.begin(); im != tempMaterialBucketMap.end(); ++im )
		{
			mVertexDatas[im->second.layerIndex]->vertexCount += im->second.grids.size();
		}

		// �������㻺��
		for ( size_t layerIndex = 0; layerIndex <VDI_LAYER_COUNT; ++layerIndex ) //���ݲ�������vb
		{
			VertexData* vertexData = mVertexDatas[layerIndex];
			vertexData->vertexCount *= 4;//�������

			setVertexData(*vertexData, layerIndex, true );
		}

		auto data = pTerrain->getTerrainInfo();

		float* pBuffer[VDI_LAYER_COUNT];

		for ( size_t i = 0; i < VDI_LAYER_COUNT; ++ i )
		{
			pBuffer[i] = NULL;
			VertexData* vertexData = mVertexDatas[i];
			if (vertexData->vertexCount == 0)
				continue;
			auto& back = vertexData->vertexSlotInfo.back();
			pBuffer[i] = (float*)back.hardwareVertexBuffer->lock();
		}

		const int lightmapGridXSize = pTerrain->getTerrainInfo()->mLightmapGridXSize;
		const int lightmapGridZSize = pTerrain->getTerrainInfo()->mLightmapGridZSize;

		//�������(�������������)
		for (auto im = tempMaterialBucketMap.begin(); im != tempMaterialBucketMap.end(); ++im )
		{
			const ThreadMaterialBucketStr* mb = &im->second;
			size_t layerIndex = mb->layerIndex;
			size_t numQuads = mb->grids.size();
			size_t vertexCount = numQuads * 4;

			float*& pFloat = pBuffer[layerIndex];
			if ( pFloat == NULL )
				continue;

			
			for (auto igrid = mb->grids.begin(); igrid != mb->grids.end(); ++igrid )//����ÿ��Grid
			{
				size_t grid = *igrid;
				const TerrainInfo::GridInfoStr& gridInfo = data->mGridInfos[grid];//������Ϣ
				const TerrainInfo::AreaVertexEnum* corners = gridInfo.getVertexes( );//�ǵ���Ϣ
				int x = grid % data->mXGridSize;//�õ���ǰ���ӵ�x��zλ��
				int z = grid / data->mXGridSize;

				//ÿ��Grid��4������
				for (size_t i = 0; i < 4; ++i)
				{
					Ogre::Vector3 v;
					std::pair<Real, Real> t;
					TerrainInfo::AreaVertexEnum corner = corners[i];

					// position
					v = data->getWorldPosFromGridIndex( (x+(corner&1)), (z+(corner>>1)) );
	
					*pFloat++ = v.x; *pFloat++ = v.y; *pFloat++ = v.z;

					// normal
					v = data->getGridJointNormal( (x+(corner&1)), (z+(corner>>1)) );
					*pFloat++ = v.x; *pFloat++ = v.y; *pFloat++ = v.z;

					// layer 0
					t = mTerrain->_getPixmapCornerData( gridInfo.imageLayers[0], corner, gridInfo.gridOperationFlags );
					*pFloat++ = t.first; *pFloat++ = t.second;

					// layer 1
					if ( gridInfo.imageLayers[1].imageAreaId )
					{
						t = mTerrain->_getPixmapCornerData( gridInfo.imageLayers[1], corner, gridInfo.gridOperationFlags );
						*pFloat++ = t.first; *pFloat++ = t.second;
					}
					// light-map
					if ( includeLightmap )
					{
						int lightmapXSize, lightmapZSize;
						mTerrain->getTerrainInfo()->getLightmapGridSize( x, z, lightmapXSize, lightmapZSize );

						const Real xScale = 1.0 / lightmapXSize;
						const Real zScale = 1.0 / lightmapZSize;

						if ( ( corner & 1 ) == 0 )
						{
							*pFloat++ = xScale * ( x % lightmapGridXSize );
						}
						else
						{
							int rightIndex = ( x + 1 ) % lightmapGridXSize;
							*pFloat++ = rightIndex == 0 ? 1.0f : rightIndex * xScale;
						}

						if ( ( corner >> 1 ) == 0 )
						{
							*pFloat++ = zScale * ( z % lightmapGridZSize );
						}
						else
						{
							int bottomIndex = ( z + 1 ) % lightmapGridZSize;
							*pFloat++ = bottomIndex == 0 ? 1.0f : bottomIndex * zScale;
						}
					}
				}
			}
		}


		for (size_t i = 0; i < VDI_LAYER_COUNT; ++i)
		{
			VertexData* vertexData = mVertexDatas[i];
			if (vertexData->vertexCount == 0)
				continue;
			auto& back = vertexData->vertexSlotInfo.back();
			back.hardwareVertexBuffer->unlock();
		}
		createGeometryFromData(tempMaterialBucketMap);

		mTerrain->getTerrainInfo()->setGroundTileAABB(mBounds, mXBase, mZBase, mXSize, mZSize);
	}

	return true;
}
bool TerrainFixedGrid::createGeometryFromData(TempMaterialBucketMap& matMap)
{
	Terrain* pTerrain = mTerrain;
	TerrainInfo* data = pTerrain->getTerrainInfo();


	std::set<String> BrushTexName;

	//�������ʺ�����ͬʱ������ʺ���������ƣ��Ա�ж��
	mMaterialNames.clear( );

	String tileName = pTerrain->getTerrainInfo()->getTerrainTileName( mTileIndex );

	auto iter = data->mGroundImageNameMap.find( tileName );
	if( iter != data->mGroundImageNameMap.end( ) )
	{
		TerrainInfo::GroundTileImageNameSet tileNameSet = iter->second;
		BrushTexName.insert( tileNameSet.begin(), tileNameSet.end() );
	}

	if (mTileIndex >= 16)
	{
		int kk = 0;
	}
	pTerrain->createLightmapTexture(mTileIndex);

	//��������Ͳ���(ͬʱ������ʺ���������)
	MaterialBucketMap materialBucketMap;
	buildMaterialBucketMap( materialBucketMap );	

	for (int32_t i = 0; i < 2; i++)
	{
		mVertexDatas[i]->buildHardBuffer();
	}

	//ÿ�ֲ��ʴ���һ��renderable
	size_t vertexStarts[2] = { 0 };
	for (auto im = materialBucketMap.begin( ); im != materialBucketMap.end( ); ++im )
	{
		//����renderable
		auto* mb = &im->second;
		size_t layerIndex = mb->layerIndex;
		size_t numQuads = mb->grids.size();
		size_t vertexCount = numQuads * 4;

		// Clone vertex data but shared vertex buffers
		VertexData* vertexData = mVertexDatas[layerIndex];

		CustomRenderable* renderable = addRenderable(*vertexData, mb->material);

		IndexDataView* view = renderable->getIndexView();

		view->mBaseVertexLocation = vertexStarts[layerIndex];
		view->mIndexCount = numQuads * 6;
		view->mIndexLocation = 0;

		//����ƫ��
		vertexStarts[layerIndex] += vertexCount;
	}

	//����lod todo
	return true;
}

const AxisAlignedBox& TerrainFixedGrid::getBoundingBox(void) const
{
	return mBounds;
}

void TerrainFixedGrid::setVertexDeclaration(
	VertexDeclaration& vertexDeclaration, uint32 textureLayerNumber ) const
{
	uint32_t MAIN_BINDING = 0;

	int32_t offset = 0;
	int32_t texCoordSet = 0;

	bool includeLightmap = mTerrain->_isLightmapUsed();

	// positions
	vertexDeclaration.addElement(MAIN_BINDING, 0, offset, VET_FLOAT3, VES_POSITION);
	offset += 3 * sizeof( float );

	// normals
	vertexDeclaration.addElement(MAIN_BINDING, 0, offset, VET_FLOAT3, VES_NORMAL);
	offset += 3 * sizeof( float );

	// texture layer
	while ( texCoordSet <= textureLayerNumber )
	{
		vertexDeclaration.addElement( MAIN_BINDING, texCoordSet++ , offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
		offset += 2 * sizeof( float );
	}

	// light-map layer
	if ( includeLightmap )
	{
		vertexDeclaration.addElement( MAIN_BINDING, texCoordSet, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
		offset += 2 * sizeof( float );
	}
}

void TerrainFixedGrid::setVertexData(
	VertexData& vertexData, 
	uint32 textureLayerNumber, 
	bool memoryVertexBuffer ) const
{
	static const unsigned short MAIN_BINDING = 0;

	if ( vertexData.vertexCount == 0 )
		return;

	VertexDeclaration& vertexDeclaration = *vertexData.vertexDeclaration;
	setVertexDeclaration( vertexDeclaration, textureLayerNumber );

	vertexData.vertexStart = 0;

	vertexData.vertexSlotInfo.emplace_back();
	auto& back = vertexData.vertexSlotInfo.back();
	back.slot = MAIN_BINDING;
	back.vertexSize = vertexDeclaration.getVertexSize( MAIN_BINDING );
	back.createBuffer(back.vertexSize, vertexData.vertexCount);
}

CustomRenderable* TerrainFixedGrid::addRenderable(
	VertexData& vertexData, 
	const std::shared_ptr<Material>& mat)
{
	//����renderable
	CustomRenderable* renderable = new CustomRenderable(&vertexData, mTerrain->getIndexData());
	renderable->setMaterial(mat);
	mRenderables.push_back( renderable );
	return renderable;
}

