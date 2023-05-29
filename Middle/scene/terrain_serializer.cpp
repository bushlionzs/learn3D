#include "OgreHeader.h"
#include "terrain_serializer.h"
#include "terrain_info.h"
#include "OgreDataStream.h"
#include "OgrePixelFormat.h"
#include "OgreImage.h"
#include "OgreResourceManager.h"

TerrainElementSerializer::TerrainElementSerializer()
{

}

TerrainElementSerializer::~TerrainElementSerializer()
{

}

void TerrainElementSerializer::import(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	unsigned short headerID = 0;
	readShorts(stream, &headerID, 1);
	if (headerID == HEADER_STREAM_ID)
	{
		String version = readStringBin(stream);
		if (version != mVersion)
		{
			OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR,
				"Invalid file: version incompatible, file reports " + version +
				" Serializer is version " + mVersion,
				"TerrainElementSerializerImpl::importFromStream");
		}
	}
	else
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "Invalid file: no header", "TerrainElementSerializerImpl::importFromStream");
	}

	String FileType = readStringBin(stream);
	String CopyRight = readStringBin(stream);

	if (FileType != mFileType)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR,
			"Invalid file: type incompatible, file reports " + String(FileType) +
			" Serializer is type " + mFileType,
			"TerrainElementSerializerImpl::importFromStream");
	}

	readElement(stream, pTerrain);
}

String TerrainElementSerializer::readVersion(std::shared_ptr<DataStream>& stream)
{
	//文件头
	unsigned short headerID = 0;
	readShorts(stream, &headerID, 1);

	unsigned int length = 0;
	readData(stream, &length, 1, sizeof(unsigned int));

	char* pStr = new char[length];
	stream->read(pStr, sizeof(char) * length);
	pStr[length - 1] = 0;

	String version = String(pStr);
	delete[] pStr;

	return version;
}
TerrainSerializer::TerrainSerializer()
{
	mVersion = "[GeneralSerializer_v1.20]";
	mFileType = "TEGB";
}

TerrainSerializer::~TerrainSerializer()
{

}


void TerrainSerializer::readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	uint16_t chunkId = readChunk(stream);

	if (chunkId != TFF_GENERAL)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "read terrain element error");
	}

	pTerrain->mName = readStringBin(stream);

	//通用信息

	readGeometryInfo(stream, pTerrain);


	readHeightmapInfo(stream, pTerrain);

	readGridInfo(stream, pTerrain);

	readLightmapInfo(stream, pTerrain);

	readExtendInfo(stream, pTerrain);

	//textures信息
	readImageNames(stream, pTerrain);

	//pixmap信息
	readPixmap(stream, pTerrain);

	//TerrainTexNameSet信息
	readTextureNameSet(stream, pTerrain);

	//TerrainTile信息
	readTileInfo(stream, pTerrain);

	//MaterialTemplate信息
	readMaterialTemplate(stream, pTerrain);

	//FogReplacement信息
	readFogInfo(stream, pTerrain);


	//SurfaceParam信息
	readSurfaceParameter(stream, pTerrain);

	assert(stream->eof());
}

void TerrainSerializer::readGeometryInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	readData(stream, &pTerrain->mXGridSize, 1, sizeof(pTerrain->mXGridSize));
	readData(stream, &pTerrain->mZGridSize, 1, sizeof(pTerrain->mZGridSize));

	readData(stream, &pTerrain->mTileGridSize, 1, sizeof(pTerrain->mTileGridSize));
	
	readObject(stream, pTerrain->mWorldUnit);

	readObject(stream, pTerrain->mWorldCenter);

	const Ogre::Vector3& worldUnit = pTerrain->mWorldUnit;
	const Ogre::Vector3& worldCenter = pTerrain->mWorldCenter;
	const int xGridSize = pTerrain->mXGridSize;
	const int zGridSize = pTerrain->mZGridSize;

	if (worldUnit.x <= 0 || worldUnit.y <= 0 || worldUnit.z <= 0)
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Invalidate scale definition in terrain file",
			"TerrainGeneralSerializerImpl::readGeometryInfo");
	}

	pTerrain->mFirstGridWorldPos = Ogre::Vector3(worldCenter.x - worldUnit.x * xGridSize / 2, 
		worldCenter.y, worldCenter.z - worldUnit.z * zGridSize / 2);
}

void TerrainSerializer::readHeightmapInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	pTerrain->mHeightmapType = readStringBin(stream);
	pTerrain->mHeightmapFilename = readStringBin(stream);
}

void TerrainSerializer::readGridInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	pTerrain->mGridInfoType = readStringBin(stream);//这个类型暂时没用
	pTerrain->mGridInfoFilename = readStringBin(stream);
}

void TerrainSerializer::readLightmapInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	pTerrain->mLightmapType = readStringBin(stream);
	pTerrain->mLightmapFilename = readStringBin(stream);

	pTerrain->mLightmapQuality = TerrainInfo::LMQ_HIGH;
	pTerrain->mLightmapGridXSize = pTerrain->mTileGridSize;
	pTerrain->mLightmapGridZSize = pTerrain->mTileGridSize;
}

void TerrainSerializer::readExtendInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	pTerrain->mExtraLeft = 0.0f;
	pTerrain->mExtraTop = 0.0f;
	pTerrain->mExtraRight = 0.0f;
	pTerrain->mExtraBottom = 0.0f;
}

void TerrainSerializer::readImageNames(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	uint32_t textureSize = 0;
	readInts(stream, &textureSize, 1);

	pTerrain->mImages.clear();
	for (int32_t textureIndex = 0; textureIndex != textureSize; ++textureIndex)
	{
		TerrainInfo::ImageItemStr item;
		String texType = readStringBin(stream);//类型暂时没用
		item.texName = readStringBin(stream); // Name
		pTerrain->mImages.push_back(item);//mTextures只保存了图片名称
	}

	//change imagename from tga to dds
	uint32_t size = pTerrain->mImages.size();
	for (uint32_t i = 0; i < size; i++)
	{

		auto& item = pTerrain->mImages.at(i);
		item.texName = Ogre::StringUtil::replaceAll(item.texName, ".tga", ".dds");
		if (!ResourceManager::getSingleton().hasResource(item.texName))
		{
			WARNING_LOG("fail to load terrain texture:%s", item.texName.c_str())
		}
	}

}

void TerrainSerializer::readPixmap(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	uint32_t pixmapSize = 0;
	readInts(stream, &pixmapSize, 1);
	pTerrain->mImageAreas.clear();
	for (int32_t pixmapIndex = 0; pixmapIndex != pixmapSize; ++pixmapIndex)
	{
		TerrainInfo::ImageArea pixmap;
		readData(stream, &(pixmap.imageId), 1, sizeof(pixmap.imageId));
		readData(stream, &(pixmap.left), 1, sizeof(pixmap.left));
		readData(stream, &(pixmap.top), 1, sizeof(pixmap.top));
		readData(stream, &(pixmap.right), 1, sizeof(pixmap.right));
		readData(stream, &(pixmap.bottom), 1, sizeof(pixmap.bottom));

		pTerrain->mImageAreas.push_back(pixmap);
	}
}

void TerrainSerializer::readTextureNameSet(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	uint32_t terrainTexNameSetSize = 0;
	readInts(stream, &terrainTexNameSetSize, 1);

	pTerrain->mGroundImageNameMap.clear();
	String terrainTileName;
	for (int32_t tileIndex = 0; tileIndex != terrainTexNameSetSize; ++tileIndex)
	{
		terrainTileName = readStringBin(stream);
		int32_t texSetSize = 0;
		readData(stream, &texSetSize, 1, sizeof(texSetSize));

		std::set<std::string> texSet;
		for (int32_t texIndex = 0; texIndex != texSetSize; ++texIndex)
		{
			String texName = readStringBin(stream);
			texSet.insert(texName.c_str());
		}
		pTerrain->mGroundImageNameMap.insert(make_pair(terrainTileName, texSet));
	}
}

void TerrainSerializer::readTileInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{

}

void TerrainSerializer::readMaterialTemplate(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	uint32_t materialTemplateSize = 0;
	readInts(stream, &materialTemplateSize, 1);

	pTerrain->mTemplateMats.clear();
	String name;
	String material;
	for (int32_t materialIndex = 0; materialIndex != materialTemplateSize; ++materialIndex)
	{
		name = readStringBin(stream);//name
		material = readStringBin(stream);//material
		pTerrain->mTemplateMats[name] = material;

	}
}

void TerrainSerializer::readFogInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	uint32_t fogReplacementSize = 0;
	readInts(stream, &fogReplacementSize, 1);

	pTerrain->mFogModes.clear();
	for (int32_t fogReplacementIndex = 0; fogReplacementIndex != fogReplacementSize; ++fogReplacementIndex)
	{
		TerrainInfo::FogModeStr fogReplacement;

		fogReplacement.programNames[TerrainInfo::FOG_NONE] = readStringBin(stream);
		fogReplacement.programNames[TerrainInfo::FOG_EXP] = readStringBin(stream);
		fogReplacement.programNames[TerrainInfo::FOG_EXP2] = readStringBin(stream);
		fogReplacement.programNames[TerrainInfo::FOG_LINEAR] = readStringBin(stream);

		pTerrain->mFogModes.push_back(fogReplacement);
	}
}

void TerrainSerializer::readSurfaceParameter(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	readData(stream, &(pTerrain->mAmbient), 1, sizeof(pTerrain->mAmbient));
	readData(stream, &(pTerrain->mDiffuse), 1, sizeof(pTerrain->mDiffuse));
	readData(stream, &(pTerrain->mSpecular), 1, sizeof(pTerrain->mSpecular));
	readData(stream, &(pTerrain->mEmissive), 1, sizeof(pTerrain->mEmissive));
	readData(stream, &(pTerrain->mShininess), 1, sizeof(pTerrain->mShininess));
}


TerrainGeneralSerializerImpl_v1_1::TerrainGeneralSerializerImpl_v1_1()
{

}

TerrainGeneralSerializerImpl_v1_1::~TerrainGeneralSerializerImpl_v1_1()
{

}

void TerrainGeneralSerializerImpl_v1_1::readExtendInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	TerrainSerializer::readExtendInfo(stream, pTerrain);

	readData(stream, &pTerrain->mExtraLeft, 1, sizeof(pTerrain->mExtraLeft));
	readData(stream, &pTerrain->mExtraTop, 1, sizeof(pTerrain->mExtraTop));
	readData(stream, &pTerrain->mExtraRight, 1, sizeof(pTerrain->mExtraRight));
	readData(stream, &pTerrain->mExtraBottom, 1, sizeof(pTerrain->mExtraBottom));
}


TerrainGeneralSerializerImpl_v1_2::TerrainGeneralSerializerImpl_v1_2()
{

}

TerrainGeneralSerializerImpl_v1_2::~TerrainGeneralSerializerImpl_v1_2()
{

}

void TerrainGeneralSerializerImpl_v1_2::readLightmapInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	TerrainGeneralSerializerImpl_v1_1::readLightmapInfo(stream, pTerrain);

	unsigned short quality;

	readData(stream, &quality, 1, sizeof(quality));
	readData(stream, &pTerrain->mLightmapGridXSize, 1, sizeof(pTerrain->mLightmapGridXSize));
	readData(stream, &pTerrain->mLightmapGridZSize, 1, sizeof(pTerrain->mLightmapGridZSize));

	pTerrain->mLightmapQuality = (TerrainInfo::LightmapQualityEnum)quality;
}

void TerrainGeneralSerializerImpl_v1_2::readTileInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	auto & tilesInfo = pTerrain->mTilesInfo;

	tilesInfo.clear();

	unsigned int tileNumber;
	readData(stream, &tileNumber, 1, sizeof(unsigned int));

	for (unsigned int i = 0; i < tileNumber; ++i)
	{
		TerrainInfo::TileInfo tileInfo;

		readData(stream, &tileInfo.mLightmapIndex, 1, sizeof(unsigned int));
		readData(stream, &tileInfo.mLightmapScale.x, 1, sizeof(Real));
		readData(stream, &tileInfo.mLightmapScale.y, 1, sizeof(Real));
		readData(stream, &tileInfo.mLightmapOffset.x, 1, sizeof(Real));
		readData(stream, &tileInfo.mLightmapOffset.y, 1, sizeof(Real));
	}
}

TerrainHeightMapSerializer::TerrainHeightMapSerializer()
{
	mVersion = "[HeightMapSerializer_v1.00]";
	mFileType = "THMB";
}

TerrainHeightMapSerializer::~TerrainHeightMapSerializer()
{

}


void TerrainHeightMapSerializer::readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	unsigned short chunkId = readChunk(stream);
	if (chunkId != TFF_HEIGHTMAP)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "read terrain heightmap element error");
	}

	auto xGridSize = pTerrain->mXGridSize;
	auto zGridSize = pTerrain->mZGridSize;

	pTerrain->mHeightmap.resize((xGridSize + 1) * (zGridSize + 1));

	int xSize = 0;
	int zSize = 0;

	readData(stream, &xSize, 1, sizeof(xSize));
	readData(stream, &zSize, 1, sizeof(zSize));

	

	if (xSize != xGridSize + 1 || zSize != zGridSize + 1)
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"Dimensions of heightmap file doesn't match the dimensions of the terrain");
	}

	int32_t heightMapSize = 0;
	readData(stream, &heightMapSize, 1, sizeof(heightMapSize));

	if (heightMapSize != ((xGridSize + 1) * (zGridSize + 1)))
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"Dimensions of heightmap file doesn't match the dimensions of the terrain");
	}

	for (size_t i = 0; i < heightMapSize; ++i)
	{
		readData(stream, &(pTerrain->mHeightmap[i]), 1, sizeof(pTerrain->mHeightmap[i]));
	}

}

TerrainGridInfoSerializer::TerrainGridInfoSerializer()
{
	mVersion = "[GridInfoSerializer_v1.00]";
	mFileType = "TGIB";
}

TerrainGridInfoSerializer::~TerrainGridInfoSerializer()
{

}


void TerrainGridInfoSerializer::readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	unsigned short chunkId = readChunk(stream);
	if (chunkId != TFF_GRIDINFO)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "read gridinfo element error");
	}


	const int32_t xGridSize = pTerrain->mXGridSize;
	const int32_t zGridSize = pTerrain->mZGridSize;

	// Allocate buffers
	pTerrain->mGridInfos.resize(xGridSize * zGridSize);

	int xSize = 0;
	int zSize = 0;
	readData(stream, &xSize, 1, sizeof(xSize));
	readData(stream, &zSize, 1, sizeof(zSize));

	if (xSize != xGridSize || zSize != zGridSize)//地形尺寸不符
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"Dimensions of grid info file doesn't match the dimensions of the terrain");
	}

	bool pixmapId16BitsFlag = true;
	readData(stream, &pixmapId16BitsFlag, 1, sizeof(pixmapId16BitsFlag));

	int32_t gridInfoSize = 0;
	readData(stream, &gridInfoSize, 1, sizeof(gridInfoSize));

	if (gridInfoSize != xGridSize * zGridSize)//地形尺寸不符
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"Dimensions of grid info file doesn't match the dimensions of the terrain ");
	}

	size_t numPixmaps = pTerrain->mImageAreas.size();
	for (auto it = pTerrain->mGridInfos.begin(); it != pTerrain->mGridInfos.end(); ++it)//每个GridInfo信息
	{
		TerrainInfo::GridInfoStr& gridInfo = *it;
		for (size_t i = 0; i < TerrainInfo::IL_NUM; ++i)//每层数据
		{
			if (pixmapId16BitsFlag)
			{
				uint16 pixmapId;
				uchar orientation;
				readData(stream, &pixmapId, 1, sizeof(pixmapId));
				readData(stream, &orientation, 1, sizeof(orientation));

				gridInfo.imageLayers[i].imageAreaId = pixmapId;
				gridInfo.imageLayers[i].gridAndAreaOperationFlags = orientation;
			}
			else
			{
				uchar v[2];
				readData(stream, v, 1, sizeof(v));

				gridInfo.imageLayers[i].imageAreaId = v[0];
				gridInfo.imageLayers[i].gridAndAreaOperationFlags = v[1];
			}

			// imageAreaId == 0 is means hole
			if (gridInfo.imageLayers[i].imageAreaId > numPixmaps)
			{
				OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
					"Invalid pixmapId in grid info TerrainGridInfoSerializerImpl::readElement");
			}
		}

		uchar flags;
		readData(stream, &flags, 1, sizeof(flags));

		gridInfo.gridOperationFlags = flags;
	}
}

TerrainLightMapSerializer::TerrainLightMapSerializer()
{

}

TerrainLightMapSerializer::~TerrainLightMapSerializer()
{

}



void TerrainLightMapSerializer::readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain)
{
	pTerrain->mLightmapType = readStringBin(stream);
	pTerrain->mLightmapFilename = readStringBin(stream);

	if (pTerrain->mLightmapFilename.empty())
	{
		return;
	}

	return;
	Ogre::PixelFormat lightmapImageFormat = Ogre::PF_UNKNOWN;

	const int xLightMapNum = pTerrain->getLightmapXNumber();
	const int zLightMapNum = pTerrain->getLightmapZNumber();

	//分配空间
	CImage** pImage = new CImage * [zLightMapNum];

	for (int i = 0; i < zLightMapNum; ++i)
	{
		pImage[i] = new CImage[xLightMapNum];
	}

	//加载各个散文件

	String lightmapName;
	bool lightmapTileLoadFlag = true;
	for (int i = 0; i < zLightMapNum; ++i)
	{
		for (int j = 0; j < xLightMapNum; ++j)
		{
			CImage& image = pImage[i][j];

			lightmapName = pTerrain->getLightmapName(j, i);

			image.loadImage(lightmapName);

			if (lightmapImageFormat == Ogre::PF_UNKNOWN)
				lightmapImageFormat = image.getFormat();

			uint32_t uWidth = 0, uHeight = 0;
			pTerrain->getLightmapTileImageWidthAndHeight(j, i, uWidth, uHeight);

			if (image.getDepth() != 1 ||
				image.getWidth() != uWidth ||
				image.getHeight() != uHeight ||
				image.getFormat() != lightmapImageFormat)
			{
				OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "terrain image error");
			}
			//Ogre::PixelFormat LightmapImageFormat=pImage[i][j].getFormat();
		}
	}

	if (lightmapTileLoadFlag)//合并LightmapImage
	{
		CImage*& pImageRef = pTerrain->mLightmapImage;
		if (pImageRef != NULL)
		{
			delete pImageRef;
			pImageRef = NULL;
		}

		uint32_t lightmapImageWidth = 0, lightmapImageHeight = 0;
		pTerrain->getLightmapImageWidthAndHeight(lightmapImageWidth, lightmapImageHeight);

		uint32_t lightmapTileImageWidth = 0, lightmapTileImageHeight = 0;
		pTerrain->getLightmapTileImageWidthAndHeight(lightmapTileImageWidth, lightmapTileImageHeight);

		pImageRef = new CImage;
		//todo
		//pImageRef->loadDynamicImage(0, lightmapImageWidth, lightmapImageHeight, lightmapImageFormat);

		for (int i = 0; i < zLightMapNum; ++i)
		{
			for (int j = 0; j < xLightMapNum; ++j)
			{
				uint32_t uWidth = 0, uHeight = 0;
				pTerrain->getLightmapTileImageWidthAndHeight(j, i, uWidth, uHeight);

				size_t left = j * lightmapTileImageWidth;
				size_t right = left + uWidth;
				size_t top = i * lightmapTileImageHeight;
				size_t bottom = top + uHeight;

				Ogre::Box box(left, top, right, bottom);

				const CImage& image = pImage[i][j];
				Ogre::PixelUtil::bulkPixelConversion(image.getPixelBox(), pImageRef->getPixelBox().getSubVolume(box));
			}
		}
	}

	// 删除相关image
	for (int i = 0; i < zLightMapNum; ++i)
	{
		delete[](pImage[i]);
	}
	delete[] pImage;
}