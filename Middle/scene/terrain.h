#pragma once
#include "terrain_info.h"
class TerrainGrid;
class IndexData;
class Terrain
{
public:
	

	struct MaterialId//所谓的材质id，只是包含了纹理信息
	{
		int32_t textureId0;	//纹理0对应的atlasPixmap中的序号(atlasPixmap中，序号是pixmapid，内容包含texture指针)
		int32_t textureId1;	//纹理1对应的atlasPixmap中的序号(atlasPixmap中，序号是pixmapid，内容包含texture指针)
		int32_t depthBias;	//深度偏移，直接调用Ogre::Pass::setDepthBias函数设置，避免"depth fighting"现象
		int32_t lightmapId;	//光照图Id

		MaterialId()
			: textureId0()
			, textureId1()
			, depthBias()
			, lightmapId()
		{
		}

		MaterialId(int32_t textureId0, int32_t textureId1, int32_t lightmapId, int32_t depthBias)
			: textureId0(textureId0)
			, textureId1(textureId1)
			, lightmapId(lightmapId)
			, depthBias(depthBias)
		{
		}

		bool operator== (const MaterialId& rhs) const
		{
			return textureId0 == rhs.textureId0 &&
				textureId1 == rhs.textureId1 &&
				lightmapId == rhs.lightmapId &&
				depthBias == rhs.depthBias;
		}

		bool operator!= (const MaterialId& rhs) const
		{
			return !(*this == rhs);
		}

		bool operator< (const MaterialId& rhs) const
		{
			if (textureId0 < rhs.textureId0) return true;
			if (rhs.textureId0 < textureId0) return false;
			if (textureId1 < rhs.textureId1) return true;
			if (rhs.textureId1 < textureId1) return false;
			if (lightmapId < rhs.lightmapId) return true;
			if (rhs.lightmapId < lightmapId) return false;
			if (depthBias < rhs.depthBias) return true;
			if (rhs.depthBias < depthBias) return false;
			return false;
		}
	};


	struct ThreadMatStr
	{
		String		matName;	//材质名称
		MaterialId  id;			//材质id
	};

	struct AtlasPixmap//渲染册像素映射信息
	{
		size_t atlasId;//册Id=册vector中的序号
		Real left;
		Real top;
		Real right;
		Real bottom;
	};
	struct Atlas//渲染册
	{
		std::shared_ptr<Ogre::CImage> image;	//图片，存在的话，则是对应的lightMap的image
		std::shared_ptr<Ogre::ITexture> texture;		//纹理指针
		String texName;

		Atlas(void) : image(), texture(), texName("") { }
	};
	struct AtlasAllocInfo//渲染册分配信息
	{
		size_t atlasId;	//册id
		size_t blockId;	//块id
	};
	struct LightmapItem
	{
		std::shared_ptr<Ogre::ITexture> texture;	// 纹理指针
		int	refCount;				// 引用计数

		LightmapItem(void) : refCount(), texture() { }
	};

/////////////////////////
	typedef std::map<MaterialId, ThreadMatStr>  TempMaterialMap;
	typedef std::map<MaterialId, std::shared_ptr<Ogre::Material>> MaterialMap;
	typedef std::vector<AtlasPixmap> AtlasPixmapArray;
	typedef std::vector<Atlas> AtlasArray;
	typedef std::map<String, LightmapItem> TextureList;
public:
	Terrain();
	~Terrain();

	bool load(std::shared_ptr<Ogre::DataStream>& stream);

	TerrainInfo* getTerrainInfo();

	void _createAtlasPixmap(int32_t pixmapId);
	int32_t _getPixmapAtlasId(int32_t pixmapId);

	const std::shared_ptr<Ogre::Material>& _getGridMaterial(
		const TerrainInfo::GridInfoStr& gridInfo,
		int32_t depthBias,
		int32_t gridXIndex,
		int32_t gridZIndex);

	void _applySurfaceParams(const std::shared_ptr<Ogre::Material>& material) const;

	const ThreadMatStr& _getGridMaterialData(
		const TerrainInfo::GridInfoStr& gridInfo,
		int32_t depthBias,
		int32_t gridXIndex,
		int32_t gridZIndex);

	String getTerrainMaterialName(
		const
		TerrainInfo::GridInfoStr& gridInfo,
		int32_t depthBias,
		int32_t lightmapXIndex,
		int32_t lightmapZIndex);

	String getTerrainMaterialNameData(
		const TerrainInfo::GridInfoStr& gridInfo,
		int32_t depthBias,
		int32_t lightMapXIndex,
		int32_t lightMapZIndex);

	TerrainInfo::LightmapQualityEnum getLightmapQuality(void) const;
	int32_t _getPixmapAtlasIdData(int32_t pixmapId);
	bool _createAtlasPixmapData(size_t pixmapId);
	std::pair<Real, Real> _getPixmapCorner(
		const TerrainInfo::ImageAreaLayerStr& layerInfo,
		TerrainInfo::AreaVertexEnum corner,
		uint32_t flags) const;
	std::pair<Real, Real> _getPixmapCornerData(
		const TerrainInfo::ImageAreaLayerStr& layerInfo,
		TerrainInfo::AreaVertexEnum corner,
		uint32_t flags) const;
	IndexData* getIndexData();
	void buildTerrain();
	void createLightmapTexture(int tileIndex);
	void createLightmapTexture(int tileXIndex, int tileZIndex);
	bool createTileRenderInstance(int32_t tileIndex);
	bool _isLightmapUsed(void) const;

	String	getTerrainTileName(int32_t TileXIndex, int32_t TileZIndex);
	String	getTerrainTileName(int32_t TileIndex);
	String	getTileVBResName(int32_t TileIndex);

	bool isTerrainLoaded();
private:
	void _initIndexBuffer(size_t maxQuads);
private:
	TerrainInfo mTerrainInfo;

	AtlasPixmapArray		mAtlasPixmaps;
	AtlasArray				mAtlases;
	AtlasAllocInfo			mSolidAtlasAllocInfo;
	AtlasAllocInfo			mTransparentAtlasAllocInfo;

	std::unordered_map<int32_t, TerrainGrid*> mTiles;

	std::vector<AtlasPixmap>				mTempAtlasPixmaps;//序号是pixmapId，内容是mTempAtlas中的序号
	std::vector<String>						mTempAtlas;//序号是textueId，内容是所需要的texture的图片名称
	std::map<MaterialId, ThreadMatStr>			mTempMaterials; //材质列表

	MaterialMap mAllMaterials;

	int32_t					mAtlasTextureSize;
	int32_t					mAtlasPixmapSize;
	int32_t					mAtlasNumMipMaps;        //!< mAtlasPixmapSize >= (1 << mAtlasNumMipMaps)
	int32_t					mAtlasBlockSize;         //!< = mAtlasTextureSize / mAtlasPixmapSize
	int32_t					mMaxAtlasBlockId;        //!< = mAtlasBlockSize * mAtlasBlockSize
	Real					mAtlasBlockTexCoordInc;    //!< = 1.0f / mAtlasBlockSize

	TextureList				mLightmapTextures;

	std::unique_ptr<IndexData> mIndexData;
};