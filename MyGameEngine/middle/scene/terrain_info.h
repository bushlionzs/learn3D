#pragma once
#include "OgreColourValue.h"

class TerrainInfo
{
	friend class TerrainSerializer;
public:

	

	enum LightmapQualityEnum
	{
		LMQ_UNKOWN = 0,
		LMQ_NONE = 1,//LMQ_NONE已废弃
		LMQ_LOW = 2,
		LMQ_MID = 3,
		LMQ_HIGH = 4,
		LMQ_FUTURE = 5
	};

	enum ImageLayerEnum
	{
		IL_UNKNOWN = 0,
		IL_NUM = 2,
		IL_FUTURE = 3
	};

	enum GridOperationEnum
	{
		GO_UNKOWN = 0,
		GO_FLIP_DIAGONAL = 1 << 0,
		GO_DISABLE_DECAL = 1 << 1,
		GO_FUTURE = 1 << 2
	};

	enum AreaOperationEnum
	{
		AO_UNKOWN = 0,
		AO_FLIP_HORIZONTAL = 1 << 0,
		AO_FLIP_VERTICAL = 1 << 1,
		AO_ANTICLOCKWISE_ROTATE_90 = 1 << 2,
		AO_DIAGONAL_MIRROR = 1 << 3,
		AO_FUTURE = 1 << 4
	};
	enum AreaVertexEnum
	{
		V_UNKNOWN = -1,
		V_LEFT_TOP = 0,
		V_RIGHT_TOP = 1,
		V_LEFT_BOTTOM = 2,
		V_RIGHT_BOTTOM = 3,
		V_FUTURE = 4
	};

	/** Fog modes. */
	enum FogMode : uint8
	{
		/// No fog. Duh.
		FOG_NONE,
		/// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
		FOG_EXP,
		/// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
		FOG_EXP2,
		/// Fog density increases linearly between the start and end distances
		FOG_LINEAR
	};


	static const AreaVertexEnum		mAreaVertexLayout[2][4];

	struct ImageItemStr
	{
		String texName;
		int   refCount;
		ImageItemStr() :refCount(0), texName("") {	}
	};
	struct ImageArea
	{
		int32_t imageId;
		Real left;
		Real top;
		Real right;
		Real bottom;
		ImageArea() {}
		explicit ImageArea(int32_t imageId) : imageId(imageId), left(0), top(0), right(1), bottom(1) {}
		ImageArea(int32_t imageId, Real left, Real top, Real right, Real bottom) :
			imageId(imageId), left(left), top(top), right(right), bottom(bottom)
		{
		}

		bool operator== (const ImageArea& imageArea) const
		{
			return imageId == imageArea.imageId && left == imageArea.left &&
				right == imageArea.right && top == imageArea.top && bottom == imageArea.bottom;
		}

		bool operator!= (const ImageArea& imageArea) const
		{
			return !(*this == imageArea);
		}

		bool operator< (const ImageArea& imageArea) const
		{
			//纹理id--左--上--右--下
			if (imageId < imageArea.imageId)
				return true;
			if (imageId > imageArea.imageId)
				return false;
			if (left < imageArea.left)
				return true;
			if (left > imageArea.left)
				return false;
			if (top < imageArea.top)
				return true;
			if (top > imageArea.top)
				return false;
			if (right < imageArea.right)
				return true;
			if (right > imageArea.right)
				return false;
			if (bottom < imageArea.bottom)
				return true;
			if (bottom > imageArea.bottom)
				return false;
			return false;
		}
	};
	struct ImageAreaLayerStr
	{
		ushort		imageAreaId;				// 0 表示空
		ushort		gridAndAreaOperationFlags;
		bool operator== (const ImageAreaLayerStr& imageAreaLayer) const
		{
			return imageAreaId == imageAreaLayer.imageAreaId && gridAndAreaOperationFlags == imageAreaLayer.gridAndAreaOperationFlags;
		}
		bool operator!= (const ImageAreaLayerStr& imageAreaLayer) const
		{
			return !(*this == imageAreaLayer);
		}
	};
	

	struct GridInfoStr
	{
		ImageAreaLayerStr	imageLayers[IL_NUM];
		uint32_t			gridOperationFlags;		//GridOperationEnum值组合
		const AreaVertexEnum* getVertexes(void) const
		{
			return mAreaVertexLayout[(gridOperationFlags & GO_FLIP_DIAGONAL) ? 1 : 0];
		}
		bool operator== (const GridInfoStr& gridInfo) const
		{
			return imageLayers[0] == gridInfo.imageLayers[0] &&
				imageLayers[1] == gridInfo.imageLayers[1] &&
				gridOperationFlags == gridInfo.gridOperationFlags;
		}
		bool operator!= (const GridInfoStr& rhs) const
		{
			return !(*this == rhs);
		}
	};

	struct FogModeStr
	{
		String programNames[4];
	};

	struct TileInfo
	{
		unsigned int mLightmapIndex;
		Ogre::Vector2 mLightmapScale;
		Ogre::Vector2 mLightmapOffset;

		TileInfo() : mLightmapIndex(-1), mLightmapScale(Ogre::Vector2::UNIT_SCALE), mLightmapOffset(Ogre::Vector2::ZERO)
		{
		}
	};


	typedef std::set<String>	GroundTileImageNameSet;
public:
	TerrainInfo();
	~TerrainInfo();
	public:
		int getLightmapXNumber() const
		{
			return mLightmapGridXSize == 0 ? 0 : (mXGridSize + mLightmapGridXSize - 1) / mLightmapGridXSize;
		}

		int	getLightmapZNumber() const
		{
			return mLightmapGridXSize == 0 ? 0 : (mZGridSize + mLightmapGridZSize - 1) / mLightmapGridZSize;
		}

		String getLightmapName(int lightmapIndex) const
		{
			int lightMapXNum = getLightmapXNumber();

			if (lightMapXNum == 0)
				return "";

			int lightMapXIndex = lightmapIndex % lightMapXNum;
			int lightMapZIndex = lightmapIndex / lightMapXNum;
			return getLightmapName(lightMapXIndex, lightMapZIndex);
		}
		String getLightmapName(int lightMapXIndex, int lightMapZIndex) const
		{
			if (mLightmapType == "multiimage" && mLightmapFilename != String(""))
			{
				return  mLightmapFilename + "_" + std::to_string(lightMapXIndex) + "_" + std::to_string(lightMapZIndex) + ".png";
			}
			else
			{
				return "<Lightmap>(" + std::to_string(lightMapXIndex) + "," + std::to_string(lightMapZIndex) + ")";
			}
		}

		bool getLightmapTileImageWidthAndHeight(uint32_t& width, uint32_t& height) const
		{
			getLightmapGridTextureWidthAndHeight(width, height);

			width *= mLightmapGridXSize;
			height *= mLightmapGridZSize;

			return true;
		}

		void getLightmapTileImageWidthAndHeight(int xIndex, int zIndex, uint32_t& width, uint32_t& height) const
		{
			int xSize, zSize;
			getLightmapGridSize(xIndex * mLightmapGridXSize, zIndex * mLightmapGridZSize, xSize, zSize);
			getLightmapGridTextureWidthAndHeight(width, height);

			width *= xSize;
			height *= zSize;
		}


		void getLightmapGridSize(int xGridIndex, int zGridIndex, int& xSize, int& zSize) const
		{
			if (mLightmapGridXSize == 0)
			{
				xSize = 0;
			}
			else
			{
				int lightmapXIndex = xGridIndex / mLightmapGridXSize;
				xSize = lightmapXIndex == mXGridSize / mLightmapGridXSize ? mXGridSize - lightmapXIndex * mLightmapGridXSize : mLightmapGridXSize;
			}

			if (mLightmapGridZSize == 0)
			{
				zSize = 0;
			}
			else
			{
				int lightmapZIndex = zGridIndex / mLightmapGridZSize;
				zSize = lightmapZIndex == mZGridSize / mLightmapGridZSize ? mZGridSize - lightmapZIndex * mLightmapGridZSize : mLightmapGridZSize;
			}
		}

		void getLightmapGridTextureWidthAndHeight(uint32_t& width, uint32_t& height) const;
		bool getLightmapImageWidthAndHeight(uint32_t& width, uint32_t& height) const
		{
			getLightmapGridTextureWidthAndHeight(width, height);

			width *= mXGridSize;
			height *= mZGridSize;

			return true;
		}

		void getLightmapTileTextureWidthAndHeight(uint32_t& width, uint32_t& height) const;
		void getLightmapNames(
			int32_t tileXIndex,
			int32_t tileZIndex,
			std::vector<std::string>& lightmaps) const;
		String getTerrainTileName(int tileXIndex, int tileZIndex) const;
		String getTerrainTileName(int tileIndex) const;
		Ogre::Vector3 getWorldPosFromGridIndex(int gridXIndex, int gridZIndex) const;
		Ogre::Vector3 getGridJointNormal(int gridXIndex, int gridZIndex) const;
		Real getGridJointGridHeight(int gridXIndex, int gridZIndex) const;
		int getGridJointIndex(int gridXIndex, int gridZIndex) const;
		bool isValidGridJoint(int gridXIndex, int gridZIndex) const;
		void resetDeriveValues(void);

		const GridInfoStr& TerrainInfo::getGridInfo(int gridIndex) const;
		int getGridIndex(int gridXIndex, int gridZIndex) const;
		int	getXGridSize() const;
		int	getZGridSize() const;

		std::pair<Real, Real>		getWorldIndexFromRealGridIndex(Real gridXIndex, Real gridZIndex) const;
		Real	getWorldIndexWorldHeight(Real worldXIndex, Real worldZIndex) const;
		Real	getGridJointWorldHeight(int gridXIndex, int gridZIndex) const;

		bool setGroundTileAABB(
			Ogre::AxisAlignedBox& box, 
			int gridXIndex, 
			int gridZIndex, 
			int gridXSize, 
			int gridZSize) const;

		bool isRayIntersectGround(
			const Ogre::Ray& ray, 
			Ogre::Vector3& intersectPos, 
			Ogre::Vector3* intersectNormal = nullptr,
			bool allowOutside = false, 
			bool positiveSide = true, 
			bool negativeSide = false) const;
	bool isValidWorldIndex(Real worldXIndex, Real worldZIndex) const
	{
		return mWorldMinX <= worldXIndex && 
			   worldXIndex <= mWorldMaxX && 
			   mWorldMinZ <= worldZIndex && 
			   worldZIndex <= mWorldMaxZ;
	}

	const Ogre::AxisAlignedBox& computerBoundBox() const;
	bool isValidGridIndex(int gridXIndex, int gridZIndex) const;
	std::pair<bool, Real>	isRayIntersectGrid(
		const Ogre::Ray& ray, 
		int gridXIndex, 
		int gridZIndex, 
		bool positiveSide, 
		bool negativeSide = false) const;

	bool getWorldIndexPosAndNormal(
		Real worldXIndex,
		Real worldZIndex,
		Ogre::Vector3& worldPos,
		Ogre::Vector3& worldNormal) const;

	std::pair<Real, Real> getRealGridIndexFromWorldIndex(Real worldXIndex, Real worldZIndex) const;
	
public:
	String mName;
	int32_t						    mXGridSize;
	int32_t						    mZGridSize;
	int32_t							mTileGridSize;
	Ogre::Vector3					mWorldUnit;
	Ogre::Vector3					mFirstGridWorldPos;
	
	String							mHeightmapType;
	String							mHeightmapFilename;
	std::vector<Real>			    mHeightmap;
	
	String							mGridInfoType;
	String							mGridInfoFilename;
	std::vector<GridInfoStr>		mGridInfos;
	
	String							mLightmapType;
	String							mLightmapFilename;
	
	int32_t								mLightmapGridXSize;
	int32_t								mLightmapGridZSize;
	LightmapQualityEnum				mLightmapQuality;
	Ogre::CImage* mLightmapImage;
	
	float mExtraLeft;
	float mExtraTop;
	float mExtraRight;
	float mExtraBottom;

	//
	std::vector<ImageArea> mImageAreas;
	std::vector<ImageItemStr> mImages;

	//
	std::map< String, std::set<std::string> > mGroundImageNameMap;
	//
	//材质模板
	std::map<String, String> mTemplateMats;

	///雾模式
	std::vector<FogModeStr>						mFogModes;
	std::vector<FogModeStr>						mSupportedFogModes;
	//表面材质属性
	Ogre::ColourValue				mAmbient;
	Ogre::ColourValue				mDiffuse;
	Ogre::ColourValue				mSpecular;
	Ogre::ColourValue				mEmissive;
	Ogre::Real						mShininess;

	//地形Tile信息
	std::vector<TileInfo>						mTilesInfo;

	//为了使用方便而保存的值
	Ogre::Vector3					mInvWorldUnit;
	Ogre::Vector3					mWorldCenter;
	Real							mWorldMinX, mWorldMaxX;
	Real							mWorldMinZ, mWorldMaxZ;
	int32_t							mXTileNum;
	int32_t							mZTileNum;


	mutable Ogre::AxisAlignedBox	mAABBox;
};