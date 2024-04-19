#include "OgreHeader.h"
#include "terrain.h"
#include "terrain_serializer.h"
#include "terrain_info.h"
#include "OgreMaterialManager.h"
#include "OgreImage.h"
#include "OgreTexture.h"
#include "OgreTextureUnit.h"
#include "OgreTextureManager.h"
#include "index_data.h"
#include "OgreHardwareBufferManager.h"
#include "renderSystem.h"
#include "terrain_fixed_grid.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "OgreSceneNode.h"
#include "OgreResourceManager.h"

Terrain::Terrain()
{
	mAtlasTextureSize = 512;//���γߴ�	
	mAtlasPixmapSize = 64;//Сͼ�ߴ�
	//mAtlasNumMipMaps = 6;
	mAtlasNumMipMaps = 0;//���ε�mipmap

	assert(mAtlasPixmapSize >= ((size_t)1 << mAtlasNumMipMaps));
	//����=8
	mAtlasBlockSize = mAtlasTextureSize / mAtlasPixmapSize;
	//����Id=64
	mMaxAtlasBlockId = mAtlasBlockSize * mAtlasBlockSize;
	//������������
	mAtlasBlockTexCoordInc = 1.0f / mAtlasBlockSize;

	// Mark as invalidate
	//=64
	mSolidAtlasAllocInfo.blockId = mMaxAtlasBlockId;
	mTransparentAtlasAllocInfo.blockId = mMaxAtlasBlockId;
}

Terrain::~Terrain()
{

}

bool Terrain::load(std::shared_ptr<DataStream>& stream)
{

	TerrainGeneralSerializerImpl_v1_2 serializer;

	serializer.import(stream, &mTerrainInfo);

	mTerrainInfo.resetDeriveValues();

	if (!mTerrainInfo.mHeightmapFilename.empty())
	{
		std::shared_ptr<DataStream> datastream =
			ResourceManager::getSingletonPtr()->openResource(mTerrainInfo.mHeightmapFilename);
		TerrainHeightMapSerializer heightMapSerializer;
		heightMapSerializer.import(datastream, &mTerrainInfo);
	}
	

	if (!mTerrainInfo.mGridInfoFilename.empty())
	{
		std::shared_ptr<DataStream> datastream =
			ResourceManager::getSingletonPtr()->openResource(mTerrainInfo.mGridInfoFilename);
		TerrainGridInfoSerializer gridInfoSerializer;
		gridInfoSerializer.import(datastream, &mTerrainInfo);
	}
	
	if (!mTerrainInfo.mLightmapFilename.empty())
	{
		/*std::shared_ptr<DataStream> datastream =
			ResManager::getSingletonPtr()->createDataStream(mTerrainInfo.mLightmapFilename);
		TerrainLightMapSerializer lightMapSerializer;
		lightMapSerializer.import(datastream, &mTerrainInfo);*/
	}
	
	return true;
}

IndexData* Terrain::getIndexData()
{
	return mIndexData.get();
}

void Terrain::buildTerrain()
{
	TerrainInfo* pTerrainInfo = &mTerrainInfo;
	_initIndexBuffer(pTerrainInfo->mTileGridSize * pTerrainInfo->mTileGridSize);
	int32_t mGridXNum = pTerrainInfo->mXGridSize / (int)pTerrainInfo->mTileGridSize;
	int32_t mGridZNum = pTerrainInfo->mZGridSize / (int)pTerrainInfo->mTileGridSize;

	for (int32_t i = 0; i < mGridZNum; ++i)
	{
		for (int32_t j = 0; j < mGridXNum; ++j)
		{
			int32_t gridIndex = i * mGridXNum + j;

			createTileRenderInstance(gridIndex);
		}
	}

	int32_t i = 0;
	for (auto itor = mTiles.begin(); itor != mTiles.end(); itor++, i++)
	{
		if (i == 99)
		{
			int kk = 0;
		}
		auto pTerTile = (TerrainFixedGrid*)itor->second;
		pTerTile->createGeometryData();
	}
}


void Terrain::_initIndexBuffer(size_t maxQuads)
{
	mIndexData = std::make_unique<IndexData>();

	mIndexData->mIndexCount = maxQuads * 6;
	mIndexData->createBuffer(4, mIndexData->mIndexCount);
	HardwareBufferLockGuard lockGuard(mIndexData->mIndexBuffer.get());
	uint32_t* pIndex = (uint32_t*)lockGuard.data();
	//�������
	for (int32_t i = 0; i < maxQuads; ++i)
	{
		// NB: We should take care with the clockwise ordered quad vertices
		/*
		0      1
		+------+
		|     /|
		|    / |
		|   /  |
		|  /   |
		| /    |
		|/     |
		+------+
		2      3
		*/

		* pIndex++ = i * 4 + 1;
		*pIndex++ = i * 4 + 0;
		*pIndex++ = i * 4 + 2;

		*pIndex++ = i * 4 + 1;
		*pIndex++ = i * 4 + 2;
		*pIndex++ = i * 4 + 3;
	}
}

void Terrain::_createAtlasPixmap(int32_t pixmapId)//�������������id��Ӧ�Ĳ���������飨���൱��image��texture�Ķ�Ӧ��ϵ����������鱣������id������)
{
	//pixmapId--->imageId--->textureName(ͼƬ����)
	const TerrainInfo::ImageArea& pixmap = mTerrainInfo.mImageAreas[pixmapId];
	int32_t imageId = pixmap.imageId;//����������Ӧ������Id
	assert(imageId < mTerrainInfo.mImages.size());
	//imageId���textureName
	const String& textureName = mTerrainInfo.mImages[imageId].texName;//�õ���������

	//����TextureName�ҵ���Ӧ��Atlases�������AtlasPixmap
	AtlasArray::const_iterator it;
	for (it = mAtlases.begin(); it != mAtlases.end(); ++it)//�����Ƿ񴴽���
	{
		if (it->texName == textureName)
		{
			// ��̬���ؿ��ܸ������Ѿ�ɾ��
			// ��ɾ���򴴽����������ü��� by Nick
			if (!it->texture)
			{
				Atlas& atlas = (Atlas&)*it;

				//��̨���ص������� dscky edit//////////////////////////////////
				//�����ͼ������OrphigineTexInfo.xml���� �ļ�����/��ͼ��.jpg�������ã������ļ�����Ϊ�༭������ͼ�����ã�
				//��Ϊ�����ʽ����Ҫ���·�����Ե����ļ������в��ң������ڿͻ��˶�ȡʱ�����ļ������޳�
				std::string tmpCorrectedName, tmpPath;
				
				tmpCorrectedName = textureName;
				atlas.texture = TextureManager::getSingleton().load(tmpCorrectedName, nullptr);
			}
			break;
		}
	}
	if (it != mAtlases.end())//Atlas���ڣ����atlasPixmap������
	{
		// Fill up atlas pixmap info
		size_t atlasId = it - mAtlases.begin() + 1;
		mAtlasPixmaps[pixmapId].atlasId = atlasId;
		mAtlasPixmaps[pixmapId].left = pixmap.left;
		mAtlasPixmaps[pixmapId].top = pixmap.top;
		mAtlasPixmaps[pixmapId].right = pixmap.right;
		mAtlasPixmaps[pixmapId].bottom = pixmap.bottom;
		return;
	}
	//Atlas�����ڣ�����
	//�鿴��������Ҫ�������Ƿ���ڣ� If texture already loaded and is composited, use it without any modify.
	//texture����
	auto texture = TextureManager::getSingleton().getByName(textureName);
	if (texture &&
		(texture->getWidth() > mAtlasPixmapSize || texture->getHeight() > mAtlasPixmapSize))
	{
		//���������atlas
		mAtlases.push_back(Atlas());//��Ӳ�
		Atlas& atlas = mAtlases.back();//����

		atlas.texName = textureName;
		atlas.texture = texture;//ֻ���Texture��û���image

		// Fill up atlas pixmap info
		//���atlasPixmap������
		size_t atlasId = mAtlases.size();
		mAtlasPixmaps[pixmapId].atlasId = atlasId;//������ν��id����ʵ����vector�е����
		mAtlasPixmaps[pixmapId].left = pixmap.left;
		mAtlasPixmaps[pixmapId].top = pixmap.top;
		mAtlasPixmaps[pixmapId].right = pixmap.right;
		mAtlasPixmaps[pixmapId].bottom = pixmap.bottom;
		return;
	}
	//texture�����ڣ�atlasҲ������
	//�������ڣ�����Ӵ�������image������texture�������ᣬ������������
	// Load the image
	//�����ͼ������OrphigineTexInfo.xml���� �ļ�����/��ͼ��.jpg�������ã������ļ�����Ϊ�༭������ͼ�����ã�
	//��Ϊ�����ʽ����Ҫ���·�����Ե����ļ������в��ң������ڿͻ��˶�ȡʱ�����ļ������޳�
	//����texture
	std::string tmpCorrectedName, tmpPath;
	tmpCorrectedName = textureName;

	CImage image;
	if (!image.loadImage(tmpCorrectedName))
	{
		WARNING_LOG("fail to load texture:%s", tmpCorrectedName.c_str());
		return;
	}


	//dscky edit ��Ӻ�̨���صļ��ݴ���/////////////////////////////////////////////////////////////////
	//image.load(tmpCorrectedName, BRUSH_RESOURCE_GROUP_NAME);//����ͼƬ���ӻ�ˢ��Դ�����룬brush��
	// If the image is composited, use it without any modify.
	if (image.getWidth() > mAtlasPixmapSize || image.getHeight() > mAtlasPixmapSize)//����ߴ����64,��ͼƬ
	{
		//����atlas
		mAtlases.push_back(Atlas());//��Ӳ�
		Atlas& atlas = mAtlases.back();//����

		atlas.texName = textureName;
		// re-use the loaded image avoid load it again
		atlas.texture =
			TextureManager::getSingleton()
			.loadImage(textureName, image);//ֻ���Texture��û���image

		//���atlasPixmap��������
		size_t atlasId = mAtlases.size();
		mAtlasPixmaps[pixmapId].atlasId = atlasId;
		mAtlasPixmaps[pixmapId].left = pixmap.left;
		mAtlasPixmaps[pixmapId].top = pixmap.top;
		mAtlasPixmaps[pixmapId].right = pixmap.right;
		mAtlasPixmaps[pixmapId].bottom = pixmap.bottom;

		return;
	}
	

	assert(false);
}

int32_t Terrain::_getPixmapAtlasId(int32_t pixmapId)//������������������id��Ӧ�Ĳ�
{
	int32_t tempSize = mTerrainInfo.mImageAreas.size();
	assert(pixmapId < mTerrainInfo.mImageAreas.size());
	//���
	if (pixmapId >= mAtlasPixmaps.size())
		mAtlasPixmaps.resize(pixmapId + 1);

	{
		_createAtlasPixmap(pixmapId);//����texture
	}

	if (mAtlasPixmaps[pixmapId].atlasId <=0  ||  mAtlasPixmaps[pixmapId].atlasId > mAtlases.size())
	{
		WARNING_LOG("mAtlases size error:%lld", mAtlases.size());
		return 0;
	}
	return mAtlasPixmaps[pixmapId].atlasId - 1;
}

void Terrain::_applySurfaceParams(const std::shared_ptr<Material>& material) const
{
	/*material->setAmbient(mTerrainInfo.mAmbient);
	material->setDiffuse(mTerrainInfo.mDiffuse);

	material->setSpecular(mTerrainInfo.mSpecular);
	material->setSelfIllumination(mTerrainInfo.mEmissive);
	material->setShininess(mTerrainInfo.mShininess);*/

}

const std::shared_ptr<Material>& Terrain::_getGridMaterial(
	const TerrainInfo::GridInfoStr& gridInfo,
	int32_t depthBias, 
	int32_t gridXIndex,
	int32_t gridZIndex)
{
	//AtlasPixmaps�е�Id
	size_t textureIds[TerrainInfo::IL_NUM] = { 0 };
	for (size_t i = 0; i < TerrainInfo::IL_NUM; ++i)
	{
		if (gridInfo.imageLayers[i].imageAreaId)
		{
			//����pixmapId��������,���ص���AtlasPixmap�е�ֵ
			textureIds[i] = _getPixmapAtlasId(gridInfo.imageLayers[i].imageAreaId - 1) + 1;
		}
	}
	assert(textureIds[0] && "Internal fault while create grid material");

	bool lightmapped = _isLightmapUsed();

	int lightMapXIndex = gridXIndex / mTerrainInfo.mLightmapGridXSize;
	int lightMapZIndex = gridZIndex / mTerrainInfo.mLightmapGridZSize;

	uint32_t lightmapId = lightmapped ? (lightMapZIndex << 16) | lightMapXIndex : ~0;//lightMapid��һ������ֵ
	//imageId��ʵ��Ӧ����ʵ��AtlasPixmaps�е�Id
	MaterialId id(textureIds[0], textureIds[1], lightmapId, depthBias);

	// find the material that already created
	auto it = mAllMaterials.find(id);
	if (it != mAllMaterials.end())
		return it->second;
	String lightmapName = mTerrainInfo.getLightmapName(lightMapXIndex, lightMapZIndex);
	//��ò�������
	String name = getTerrainMaterialName(gridInfo, depthBias, lightMapXIndex, lightMapZIndex);
	std::shared_ptr<Material> material = MaterialManager::getSingleton().getByName(name);//ÿһ��grid����һ������
	//���ﴴ���Ĳ��ʵĳ�ʼ״̬�ǣ�δ����
	if (!material)
	{
		//��ò���ģ�������(�����Ƿ���2�㡢�Ƿ��й���ͼ�����Ҳ���ģ��)
		String templateName = textureIds[1] ? "TwoLayer" : "OneLayer";
		if (lightmapped)
			templateName += "Lightmap";
		//�ҵ�����ģ������
		auto it = mTerrainInfo.mTemplateMats.find(templateName);
		if (it == mTerrainInfo.mTemplateMats.end())
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
				"Can't found grid material template for '" + templateName + "'!",
				"Ground::_getGridMaterial");
		//��ò���ģ���Ӧ�������Ĳ���
		const String& baseName = it->second;
		auto templateMaterial = MaterialManager::getSingleton().getByName(baseName);
		if (!templateMaterial)
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
				"Can't load grid material template '" + baseName + "'!",
				"Ground::_getGridMaterial");

		//��¡����
		material = templateMaterial->clone(name);

		CImage image;

		//��������


		{
			const String& layer0 = mAtlases[textureIds[0] - 1].texture->getName();

			auto texUnit = material->getTextureUnit(0);
			texUnit->setTexture(layer0, nullptr);
			int index = 1;
			if (textureIds[1] > 0)
			{
				const String& layer1 = mAtlases[textureIds[1] - 1].texture->getName();
				auto texUnit2 = material->getTextureUnit(1);
				texUnit2->setTexture(layer1, nullptr);
				index++;
			}

			if (!lightmapName.empty())
			{
				auto texUnitLightMap = material->getTextureUnit(index);
				texUnitLightMap->setTexture(lightmapName, nullptr);
			}

		}
		material->preLoad();
		//��������
		_applySurfaceParams(material);


		String schemeName = "ShaderGeneratorDefaultScheme";
		auto materialname = material->getName();

		//todo set depthbias

	}
	//�ŵ�����map��
	//
	std::pair<MaterialMap::iterator, bool> inserted =
		mAllMaterials.insert(MaterialMap::value_type(id, material));
	assert(inserted.second && "Internal fault while create grid material");
	return inserted.first->second;
}

const Terrain::ThreadMatStr& Terrain::_getGridMaterialData(
	const TerrainInfo::GridInfoStr& gridInfo,
	int32_t depthBias,
	int32_t gridXIndex,
	int32_t gridZIndex)
{
	//�����AtlasId
	size_t AtlasIds[TerrainInfo::IL_NUM] = { 0 };
	for (size_t i = 0; i < TerrainInfo::IL_NUM; ++i)
	{
		if (gridInfo.imageLayers[i].imageAreaId)
		{
			//pixmapId���ļ��ж�ȡ����1��ʼ����������Ҫ��һ������ֵ����ʵ��������1��ʾ��1��ʼ��0Ϊ��Чֵ
			AtlasIds[i] = _getPixmapAtlasIdData(gridInfo.imageLayers[i].imageAreaId - 1) + 1;
		}
	}
	assert(AtlasIds[0] && "Internal fault while create grid material");

	//LightMapId
	bool lightmapped = _isLightmapUsed();

	int lightMapXIndex = gridXIndex / mTerrainInfo.mLightmapGridXSize;
	int lightMapZIndex = gridZIndex / mTerrainInfo.mLightmapGridZSize;

	uint32_t lightmapId = lightmapped ? (lightMapZIndex << 16) | lightMapXIndex : ~0;//lightMapid��һ������ֵ

	//����id
	MaterialId id(AtlasIds[0], AtlasIds[1], lightmapId, depthBias);
	auto it = mTempMaterials.find(id);
	if (it != mTempMaterials.end())//�ҵ�
	{
		return it->second;
	}
	else//û�ҵ�
	{
		//��ò�������
		String name = getTerrainMaterialNameData(gridInfo, depthBias, lightMapXIndex, lightMapZIndex);
		//����
		ThreadMatStr str;
		str.matName = name;
		str.id.textureId0 = id.textureId0;
		str.id.textureId1 = id.textureId1;
		str.id.depthBias = id.depthBias;
		str.id.lightmapId = id.lightmapId;
		//����
		std::pair<TempMaterialMap::iterator, bool> inserted =
			mTempMaterials.insert(TempMaterialMap::value_type(id, str));
		assert(inserted.second && "Internal fault while create grid material");
		return inserted.first->second;
	}
}

String Terrain::getTerrainMaterialName(
	const 
	TerrainInfo::GridInfoStr& gridInfo,
	int32_t depthBias, 
	int32_t lightmapXIndex,
	int32_t lightmapZIndex)
{
	//��������(������=Ground/������/0���AtlasPixmap���.1���AtlasPixmap���_���ƫ��ֵ_lightmapName
	size_t textureIds[TerrainInfo::IL_NUM] = { 0,0 };
	for (size_t i = 0; i < TerrainInfo::IL_NUM; ++i)
	{
		if (gridInfo.imageLayers[i].imageAreaId)
		{
			//����pixmapId��������,���ص���AtlasPixmap�е�ֵ
			textureIds[i] = mAtlasPixmaps[gridInfo.imageLayers[i].imageAreaId - 1].atlasId;
		}
	}
	String name;
	if (!mTerrainInfo.mName.empty())
		name += mTerrainInfo.mName;
	name += "_TerrainMat";
	name += "_" + mAtlases[textureIds[0] - 1].texture->getName();
	if (textureIds[1])
		name += "_" + mAtlases[textureIds[1] - 1].texture->getName();
	if (depthBias)
	{
		char temp[256] = { 0,0 };
		sprintf(temp, "_%d", depthBias);
		name += String(temp);
		//name += "_" + Ogre::StringConverter::toString(depthBias);
	}
	if (_isLightmapUsed())
	{
		char temp[256] = { 0,0 };
		sprintf(temp, "_LightMap_%d_%d", lightmapXIndex, lightmapZIndex);
		name += String(temp);
		//name += "_LightMap_" + Ogre::StringConverter::toString(nTileX) + "_" + Ogre::StringConverter::toString(nTileZ);
	}
	return name;
}

String Terrain::getTerrainMaterialNameData(
	const TerrainInfo::GridInfoStr& gridInfo, 
	int32_t depthBias, 
	int32_t lightMapXIndex,
	int32_t lightMapZIndex)
{
	//��������(������=Ground/������/0���AtlasPixmap���.1���AtlasPixmap���_���ƫ��ֵ_lightmapName
	size_t textureIds[TerrainInfo::IL_NUM] = { 0,0 };
	for (size_t i = 0; i < TerrainInfo::IL_NUM; ++i)
	{
		if (gridInfo.imageLayers[i].imageAreaId)
		{
			//����pixmapId��������,���ص���AtlasPixmap�е�ֵ
			textureIds[i] = mTempAtlasPixmaps[gridInfo.imageLayers[i].imageAreaId - 1].atlasId;
		}
	}
	String name;
	if (!mTerrainInfo.mName.empty())
		name += mTerrainInfo.mName;
	name += "_TerrainMat";
	name += "_" + mTempAtlas[textureIds[0] - 1];
	if (textureIds[1])
		name += "_" + mTempAtlas[textureIds[1] - 1];
	//��ΪOgre::StringConverter::toString��֧�ֶ��̲߳�����������뵥���ֹ����� [2009/04/23 dscky edit]
	if (depthBias)
	{
		char temp[256] = { 0,0 };
		sprintf(temp, "_%d", depthBias);
		name += String(temp);
		//name += "_" + Ogre::StringConverter::toString(depthBias);
	}
	if (_isLightmapUsed())
	{
		char temp[256] = { 0,0 };
		sprintf(temp, "_LightMap_%d_%d", lightMapXIndex, lightMapZIndex);
		name += String(temp);
		//name += "_LightMap_" + Ogre::StringConverter::toString(nTileX) + "_" + Ogre::StringConverter::toString(nTileZ);
	}
	return name;
}

TerrainInfo::LightmapQualityEnum Terrain::getLightmapQuality(void) const
{
	return mTerrainInfo.mLightmapQuality;
}

int32_t Terrain::_getPixmapAtlasIdData(int32_t pixmapId)
{
	assert(pixmapId < mTerrainInfo.mImageAreas.size());
	//���
	if (pixmapId >= mTempAtlasPixmaps.size())
		mTempAtlasPixmaps.resize(pixmapId + 1);//�������Ҳ����1��
	if (!mTempAtlasPixmaps[pixmapId].atlasId)//Ϊ0��ʾ��Чֵ
	{
		_createAtlasPixmapData(pixmapId);
	}
	assert(mTempAtlasPixmaps[pixmapId].atlasId > 0 && mTempAtlasPixmaps[pixmapId].atlasId <= mTempAtlas.size());
	return mTempAtlasPixmaps[pixmapId].atlasId - 1;//��1��ʾ����ʵ������ֵ
}


bool Terrain::_createAtlasPixmapData(size_t pixmapId)
{
	//ȡ����������
	const TerrainInfo::ImageArea& pixmap = mTerrainInfo.mImageAreas[pixmapId];
	size_t imageId = pixmap.imageId;
	assert(imageId < mTerrainInfo.mImages.size());
	const String& textureName = mTerrainInfo.mImages[imageId].texName;
	//����
	std::vector<String>::const_iterator itTempAtlas = mTempAtlas.begin();
	for (itTempAtlas = mTempAtlas.begin(); itTempAtlas != mTempAtlas.end(); ++itTempAtlas)
	{
		if (*itTempAtlas == textureName)
			break;
	}
	if (itTempAtlas != mTempAtlas.end())//Atlas���ڣ����atlasPixmap
	{
		size_t atlasId = itTempAtlas - mTempAtlas.begin() + 1;//���ﱣ��ı�ʵ������ֵ��1
		mTempAtlasPixmaps[pixmapId].atlasId = atlasId;
		mTempAtlasPixmaps[pixmapId].left = pixmap.left;
		mTempAtlasPixmaps[pixmapId].top = pixmap.top;
		mTempAtlasPixmaps[pixmapId].right = pixmap.right;
		mTempAtlasPixmaps[pixmapId].bottom = pixmap.bottom;
	}
	else//Atlas�����ڣ�����Atlas�����atlasPixmap
	{
		mTempAtlas.push_back(String(textureName));
		size_t atlasId = mTempAtlas.size();//���ﱣ��ı�ʵ������ֵ��1
		mTempAtlasPixmaps[pixmapId].atlasId = atlasId;
		mTempAtlasPixmaps[pixmapId].left = pixmap.left;
		mTempAtlasPixmaps[pixmapId].top = pixmap.top;
		mTempAtlasPixmaps[pixmapId].right = pixmap.right;
		mTempAtlasPixmaps[pixmapId].bottom = pixmap.bottom;
	}
	return true;
}


std::pair<Real, Real> Terrain::_getPixmapCorner(
	const TerrainInfo::ImageAreaLayerStr& layerInfo, 
	TerrainInfo::AreaVertexEnum corner,
	uint32_t flags) const
{
	assert(layerInfo.imageAreaId && "Internal fault get pixmap corner");
	assert(0 <= corner && corner < 4 && "Invalid corner");
	assert(0 <= layerInfo.gridAndAreaOperationFlags && layerInfo.gridAndAreaOperationFlags < 16 && "Invalid gridAndAreaOperationFlags");

	// NOTE: This enum should be as same order as fields of 'ImageArea', search [ImageArea Fields Order] for detail
	enum
	{
		Left,
		Top,
		Right,
		Bottom,
	};

	// NOTE: This map is dependence 'AreaOperationEnum' and 'AreaVertexEnum', search [AreaVertexEnum Map] for detail
	static const int cornerIndexMap[2][16][4][2] =
	{
		Left,   Top,    Right,  Top,    Left,   Bottom, Right,  Bottom,
		Right,  Top,    Left,   Top,    Right,  Bottom, Left,   Bottom,
		Left,   Bottom, Right,  Bottom, Left,   Top,    Right,  Top,
		Right,  Bottom, Left,   Bottom, Right,  Top,    Left,   Top,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Left,   Top,    Left,   Bottom,
		Left,   Top,    Left,   Bottom, Right,  Top,    Right,  Bottom,
		Right,  Bottom, Right,  Top,    Left,   Bottom, Left,   Top,
		Left,   Bottom, Left,   Top,    Right,  Bottom, Right,  Top,

		//------------------------------------------------------------

		Left,   Top,    Right,  Top,    Left,   Bottom, Left,   Top,
		Right,  Top,    Left,   Top,    Right,  Bottom, Right,  Top,
		Left,   Bottom, Right,  Bottom, Left,   Top,    Left,   Bottom,
		Right,  Bottom, Left,   Bottom, Right,  Top,    Right,  Bottom,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Left,   Top,    Right,  Top,
		Left,   Top,    Left,   Bottom, Right,  Top,    Left,   Top,
		Right,  Bottom, Right,  Top,    Left,   Bottom, Right,  Bottom,
		Left,   Bottom, Left,   Top,    Right,  Bottom, Left,   Bottom,

		//----------------------------------------------------------------------

		Left,   Top,    Right,  Top,    Left,   Bottom, Right,  Bottom,
		Right,  Top,    Left,   Top,    Right,  Bottom, Left,   Bottom,
		Left,   Bottom, Right,  Bottom, Left,   Top,    Right,  Top,
		Right,  Bottom, Left,   Bottom, Right,  Top,    Left,   Top,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Left,   Top,    Left,   Bottom,
		Left,   Top,    Left,   Bottom, Right,  Top,    Right,  Bottom,
		Right,  Bottom, Right,  Top,    Left,   Bottom, Left,   Top,
		Left,   Bottom, Left,   Top,    Right,  Bottom, Right,  Top,

		//------------------------------------------------------------

		Left,   Top,    Right,  Top,    Right,  Top,    Right,  Bottom,
		Right,  Top,    Left,   Top,    Left,   Top,    Left,   Bottom,
		Left,   Bottom, Right,  Bottom, Right,  Bottom, Right,  Top,
		Right,  Bottom, Left,   Bottom, Left,   Bottom, Left,   Top,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Right,  Bottom, Left,   Bottom,
		Left,   Top,    Left,   Bottom, Left,   Bottom, Right,  Bottom,
		Right,  Bottom, Right,  Top,    Right,  Top,    Left,   Top,
		Left,   Bottom, Left,   Top,    Left,   Top,    Right,  Top,
	};

	assert(layerInfo.imageAreaId <= mAtlasPixmaps.size());
	const AtlasPixmap& pixmap = mAtlasPixmaps[layerInfo.imageAreaId - 1];
	assert(pixmap.atlasId);
	const int* indices = cornerIndexMap[(flags & TerrainInfo::GO_FLIP_DIAGONAL) != 0][layerInfo.gridAndAreaOperationFlags][corner];
	return std::pair<Real, Real>((&pixmap.left)[indices[0]], (&pixmap.left)[indices[1]]);
}

std::pair<Real, Real> Terrain::_getPixmapCornerData(
	const TerrainInfo::ImageAreaLayerStr& layerInfo, 
	TerrainInfo::AreaVertexEnum corner,
	uint32_t flags) const//��ִ̨��
{
	assert(layerInfo.imageAreaId && "Internal fault get pixmap corner");
	assert(0 <= corner && corner < 4 && "Invalid corner");
	assert(0 <= layerInfo.gridAndAreaOperationFlags && layerInfo.gridAndAreaOperationFlags < 16 && "Invalid gridAndAreaOperationFlags");

	// NOTE: This enum should be as same order as fields of 'ImageArea', search [ImageArea Fields Order] for detail
	enum
	{
		Left,
		Top,
		Right,
		Bottom,
	};
	// NOTE: This map is dependence 'AreaOperationEnum' and 'AreaVertexEnum', search [AreaVertexEnum Map] for detail
	static const int cornerIndexMap[2][16][4][2] =
	{
		Left,   Top,    Right,  Top,    Left,   Bottom, Right,  Bottom,
		Right,  Top,    Left,   Top,    Right,  Bottom, Left,   Bottom,
		Left,   Bottom, Right,  Bottom, Left,   Top,    Right,  Top,
		Right,  Bottom, Left,   Bottom, Right,  Top,    Left,   Top,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Left,   Top,    Left,   Bottom,
		Left,   Top,    Left,   Bottom, Right,  Top,    Right,  Bottom,
		Right,  Bottom, Right,  Top,    Left,   Bottom, Left,   Top,
		Left,   Bottom, Left,   Top,    Right,  Bottom, Right,  Top,

		//------------------------------------------------------------

		Left,   Top,    Right,  Top,    Left,   Bottom, Left,   Top,
		Right,  Top,    Left,   Top,    Right,  Bottom, Right,  Top,
		Left,   Bottom, Right,  Bottom, Left,   Top,    Left,   Bottom,
		Right,  Bottom, Left,   Bottom, Right,  Top,    Right,  Bottom,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Left,   Top,    Right,  Top,
		Left,   Top,    Left,   Bottom, Right,  Top,    Left,   Top,
		Right,  Bottom, Right,  Top,    Left,   Bottom, Right,  Bottom,
		Left,   Bottom, Left,   Top,    Right,  Bottom, Left,   Bottom,

		//----------------------------------------------------------------------

		Left,   Top,    Right,  Top,    Left,   Bottom, Right,  Bottom,
		Right,  Top,    Left,   Top,    Right,  Bottom, Left,   Bottom,
		Left,   Bottom, Right,  Bottom, Left,   Top,    Right,  Top,
		Right,  Bottom, Left,   Bottom, Right,  Top,    Left,   Top,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Left,   Top,    Left,   Bottom,
		Left,   Top,    Left,   Bottom, Right,  Top,    Right,  Bottom,
		Right,  Bottom, Right,  Top,    Left,   Bottom, Left,   Top,
		Left,   Bottom, Left,   Top,    Right,  Bottom, Right,  Top,

		//------------------------------------------------------------

		Left,   Top,    Right,  Top,    Right,  Top,    Right,  Bottom,
		Right,  Top,    Left,   Top,    Left,   Top,    Left,   Bottom,
		Left,   Bottom, Right,  Bottom, Right,  Bottom, Right,  Top,
		Right,  Bottom, Left,   Bottom, Left,   Bottom, Left,   Top,

		//----------------------------------------

		Right,  Top,    Right,  Bottom, Right,  Bottom, Left,   Bottom,
		Left,   Top,    Left,   Bottom, Left,   Bottom, Right,  Bottom,
		Right,  Bottom, Right,  Top,    Right,  Top,    Left,   Top,
		Left,   Bottom, Left,   Top,    Left,   Top,    Right,  Top,
	};
	assert(layerInfo.imageAreaId <= mTempAtlasPixmaps.size());
	const AtlasPixmap& pixmap = mTempAtlasPixmaps[layerInfo.imageAreaId - 1];
	assert(pixmap.atlasId);
	const int* indices = cornerIndexMap[(flags & TerrainInfo::GO_FLIP_DIAGONAL) != 0][layerInfo.gridAndAreaOperationFlags][corner];
	return std::pair<Real, Real>((&pixmap.left)[indices[0]], (&pixmap.left)[indices[1]]);
}

void Terrain::createLightmapTexture(int tileIndex)
{
	int xIndex = tileIndex % mTerrainInfo.mXTileNum;
	int zIndex = tileIndex / mTerrainInfo.mXTileNum;

	createLightmapTexture(xIndex, zIndex);
}

void Terrain::createLightmapTexture(int tileXIndex, int tileZIndex)//����ָ��Tile��lightMap����
{
	if (mTerrainInfo.getLightmapXNumber() == 0 || mTerrainInfo.getLightmapZNumber() == 0)
		return;

	std::vector<std::string> lightmaps;

	mTerrainInfo.getLightmapNames(tileXIndex, tileZIndex, lightmaps);

	for (auto it = lightmaps.begin(); it != lightmaps.end(); ++it)
	{
		//�������ֲ��ң��Ҳ���������
		const String& lightmapName = *it;

		auto itTex = mLightmapTextures.find(lightmapName);
		if (itTex != mLightmapTextures.end())//�Ѿ�������
		{
			if (mTerrainInfo.mLightmapType == "multiimage")
			{
				++itTex->second.refCount;
				if (!itTex->second.texture)//���Ǳ�ж����
				{
					itTex->second.texture = TextureManager::getSingleton().load(
						lightmapName, nullptr);
					//end
				}
			}

			continue;
		}

		LightmapItem lightmapItem;

		// ��̬����
		if (mTerrainInfo.mLightmapType == "multiimage")
		{
			
			//lightmapItem.texture = Ogre::TextureManager::getSingleton().load(lightmapName,"Scene", Ogre::TEX_TYPE_2D, -1, 1.0f, false, Ogre::PF_L8);
			lightmapItem.texture = TextureManager::getSingleton().load(
				lightmapName, nullptr);
			//end
			++lightmapItem.refCount;
		}
		else if (mTerrainInfo.mLightmapType == "image") // һ�μ���
		{
			//��ҪlightMap��û��lightMapʱ��
			assert(false);
		}

		mLightmapTextures.insert(std::make_pair(lightmapName, lightmapItem));
	}
}

bool Terrain::createTileRenderInstance(int32_t tileIndex)
{
	auto itor = mTiles.find(tileIndex);
	if (itor != mTiles.end())
	{
		return true;
	}
		
	if (mTerrainInfo.mXGridSize == 0 ||
		!mTerrainInfo.mZGridSize)
	{
		return false;
	}
		
	//����x��z����
	int XIndex = tileIndex % mTerrainInfo.mXTileNum;
	int ZIndex = (tileIndex - XIndex) / mTerrainInfo.mXTileNum;
	//����tile
	int height = mTerrainInfo.mZGridSize;
	int width = mTerrainInfo.mXGridSize;
	int tileSize = mTerrainInfo.mTileGridSize;
	// Create the tile
	int tileX = XIndex * tileSize;
	int tileZ = ZIndex * tileSize;
	int tileWidth = std::min(width - tileX, tileSize);
	int tileHeight = std::min(height - tileZ, tileSize);

	auto mgr = Ogre::Root::getSingletonPtr()->getSceneManager(std::string("main"));

	TerrainFixedGrid* pTile = new TerrainFixedGrid(
		mgr->getRoot(), 
		this, 
		tileX, tileZ, tileWidth, tileHeight, tileIndex);
	
	mTiles.insert(std::make_pair(tileIndex, pTile));
	pTile->createGeometry(&mTerrainInfo, tileX, tileZ, tileWidth, tileHeight);

	return true;
}

bool Terrain::_isLightmapUsed(void) const
{
	if (mTerrainInfo.mLightmapType == "multiimage")
	{
		return getLightmapQuality() != TerrainInfo::LMQ_NONE;
	}
	return mTerrainInfo.mLightmapImage && getLightmapQuality() != TerrainInfo::LMQ_NONE;
}

String	Terrain::getTerrainTileName(int32_t TileXIndex, int32_t TileZIndex)
{
	return mTerrainInfo.getTerrainTileName(TileXIndex, TileZIndex);
}

String	Terrain::getTerrainTileName(int32_t TileIndex)
{
	return mTerrainInfo.getTerrainTileName(TileIndex);
}

String	Terrain::getTileVBResName(int32_t TileIndex)
{
	String name;

	int XIndex = TileIndex % mTerrainInfo.mXTileNum;
	int ZIndex = (TileIndex - XIndex) / mTerrainInfo.mXTileNum;
	char temp[256] = { 0,0 };
	sprintf(temp, "_TerrainTileVBRes_%d_%d", XIndex, ZIndex);
	name = mTerrainInfo.mName + String(temp);
	if (_isLightmapUsed())
	{
		name += "Lightmap";
	}
	return name;
}

bool Terrain::isTerrainLoaded()
{
	return mTerrainInfo.mXGridSize != 0;
}

TerrainInfo* Terrain::getTerrainInfo()
{
	return &mTerrainInfo;
}
