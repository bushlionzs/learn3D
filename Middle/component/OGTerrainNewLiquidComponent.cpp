#include "OgreHeader.h"
#include "OGTerrainNewLiquidComponent.h"
#include "terrain.h"
#include "OGBasicRenderable.h"
#include "engine_manager.h"
#include "OGBasicRenderable.h"
//#include "OGEnviromentManager.h"
//#include "OGGroundTypeInfo.h"
#include <OgreMaterialManager.h>
#include <OgreCamera.h>
#include <OgreNode.h>

#include <OgreSceneNode.h>
#include <OgreStringConverter.h>
#include <OgreRenderTexture.h>
#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include <renderSystem.h>
#include <OgreCamera.h>
#include <OgrePlane.h>
#include <OgreRenderTargetListener.h>
#include "OgreRoot.h"
#include "OgreTimer.h"
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>
#include "OgreViewport.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreTextureUnit.h"
#include "OgreSerializer.h"
#include "OgreHardwareBufferManager.h"
#include "OgreSceneManager.h"
#include "OgreMovablePlane.h"
namespace Orphigine
{
#define VERTEXSTREAM_POSITION 0
#define VERTEXSTREAM_DIFFUSE 1
#define VERTEXSTREAM_TEXCOORD_1 2
#define VERTEXSTREAM_NORMAL 3
#define REFLECT_TEXTURE_SIZE 256 //donot change 
#define REFLECT_PLANE_BIAS 0.0f
#define REFLECT_TEXTUREUNIT_NAME "reflect"
#define ANIMATION_TEXTUREUNIT_NAME "animation"

	//#define _ENABLE_LIQUID_TIME_LOG_ 1

	const String TerrainNewLiquidComponent::msMovableType = "TerrainLiquid";
	size_t TerrainNewLiquidComponent::mTextureNums = 0;

	ReflectRenderTargetListener::ReflectRenderTargetListener(TerrainNewLiquidComponent* liquid, const Ogre::Vector3& position, Ogre::String materialname)
		:mTerrainLiquid(liquid)
		, mReflectPlane(0)
		, mReflectTextureName(materialname)
		, mTimePosition(0)
		, mUpdateCycle(0)
	{
		mReflectPlane = new Ogre::Plane(Ogre::Vector3::UNIT_Y, position.y + REFLECT_PLANE_BIAS);

		mCamera = EngineManager::getSingleton().getMainCamera();
	
		mReflectTexture->load(nullptr);
		mRenderTarget = mReflectTexture->getBuffer(0)->getRenderTarget();
	}

	ReflectRenderTargetListener::~ReflectRenderTargetListener()
	{
		if (!mReflectTexture)
		{
			Ogre::String texName = mReflectTexture->getName();
			if (Ogre::TextureManager::getSingleton().unloadUnreferencedResource(texName))
				Ogre::TextureManager::getSingleton().remove(texName);
		}
		//mSceneManager->destroyCamera(mReflectCamera);
		delete mReflectPlane;
	}

	void ReflectRenderTargetListener::preRenderTargetUpdate(
		const Ogre::RenderTargetEvent& evt)
	{
		mCamera->enableReflection(*mReflectPlane);
		mCamera->enableCustomNearClipPlane(*mReflectPlane);
	}

	void ReflectRenderTargetListener::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
	{
		mTerrainLiquid->setReflectMatrix(
			mCamera->getProjectionMatrixWithRSDepth() * mCamera->getViewMatrix());
		mCamera->disableReflection();
		mCamera->disableCustomNearClipPlane();
		//mTerrainLiquid->setReflectMatrix(mReflectCamera->getProjectionMatrixWithRSDepth() * mReflectCamera->getViewMatrix());
	}

	void ReflectRenderTargetListener::setUpdateCycle(unsigned long millisecond)
	{
		mUpdateCycle = millisecond;
	}

	unsigned long ReflectRenderTargetListener::getUpdateCycle() const
	{
		return mUpdateCycle;
	}

	void ReflectRenderTargetListener::enableUpdate(bool enable)
	{
		if (mRenderTarget == NULL)
			return;
	}

	bool ReflectRenderTargetListener::isUpdateEnable() const
	{
		return mRenderTarget != NULL;
	}

	bool ReflectRenderTargetListener::needUpdate() const
	{
		//const Ogre::AxisAlignedBox &AABB =	mTerrainLiquid->getBoundingBox();
		//if( !mCamera->isVisible( AABB ) )
		//{
		//	return false;
		//}

		if (mUpdateCycle == 0)
		{
			return false;
		}

		// 最多每秒更新5次反射贴图
		unsigned long elapse = Ogre::Root::getSingleton().getTimer()->getMilliseconds() - mTimePosition;

		if (elapse < mUpdateCycle)
		{
			return false;
		}

		mTimePosition += elapse / mUpdateCycle * mUpdateCycle;

		return true;
	}

	class LiquidWarCraftRenderable : public GeneralRenderable
	{

	public:
		Ogre::AxisAlignedBox mBoundingBox;

	public:
		LiquidWarCraftRenderable(TerrainNewLiquidComponent* liquid)
			: GeneralRenderable(liquid)
			, mBoundingBox()
		{
		}

		~LiquidWarCraftRenderable()
		{
			//	delete mRenderOp.indexData;
		}


		virtual uint64_t getSortValue()
		{
			return 100;
		}

		Ogre::Real getSquaredViewDepth(const Ogre::Camera* camera) const
		{
			const Ogre::Vector3& cameraPos = camera->getDerivedPosition();
			const Ogre::AxisAlignedBox& aabb = mBoundingBox;
			Ogre::Vector3 diff(0, 0, 0);
			diff.makeFloor(cameraPos - aabb.getMinimum());
			diff.makeCeil(cameraPos - aabb.getMaximum());

			return diff.squaredLength();
		}

	private:

	};

	TerrainNewLiquidComponent::TerrainNewLiquidComponent(
		const Ogre::Vector3& position
		, const Ogre::String& materialname
		, const Ogre::ColourValue& colour
		, const Ogre::Real& alphadepth
		, const Ogre::Real& coordtimes
		, const Ogre::Real& speed)
		:mTerrainData(0)
		, mRenderableNum(0)
		, mVertexNum(0)
		, mVertexGridIndex(0)
		, mCellFacesNum(0)
		, mVertexData(0)
		, mIndexData(0)
		, mTempPositionBuffer(0)
		, mTempTexcoordBuffer(0)
		, mTempColourBuffer(0)
		, mTempIndexBuffer(0)
		, mCurrentCamera(0)
		, mPosition(position)
		, mLiquidColour(colour)
		, mAlphaDependDepth(alphadepth)
		, mTexCoordTimes(coordtimes)
		, mReflectRenderTargetListener(0)
		, mNumMaterials(0)
		, mCurrentMaterialType(LIQUID_UNKNOWN)
		, mHighLiquidColour()
		, mHighTexCoordTimes(10.0f)
		, mHighTexSpeed(10.0f)
		, mHighWaveSpeed(1.0f)
		, mHighGridSize(20.0f)
		, beyondFogDirty(true)
		,MoveObject("water")
	{
		mMaterialName = materialname;
		mTexSpeed = speed;
	}

	TerrainNewLiquidComponent::~TerrainNewLiquidComponent(void)
	{
		clearUp();
	}
	int TerrainNewLiquidComponent::calculateGridIndex(const Ogre::Real x, const Ogre::Real z)
	{
		Ogre::Real diffx = x - mTerrainData->mFirstGridWorldPos.x;
		Ogre::Real diffz = z - mTerrainData->mFirstGridWorldPos.z;
		size_t indexx = diffx / mTerrainData->mWorldUnit.x;
		size_t indexz = diffz / mTerrainData->mWorldUnit.z;

		assert(indexx >= 0 && indexx <= mTerrainXSize && indexz >= 0 && indexz <= mTerrainZSize);
		return (mTerrainXSize + 1) * indexz + indexx;
	}

	bool TerrainNewLiquidComponent::isValidPoint(Real x, Real z)
	{
		std::pair<Real, Real> worldPos = mTerrainData->getWorldIndexFromRealGridIndex(x, z);
		return mPosition.y > mTerrainData->getWorldIndexWorldHeight(worldPos.first, worldPos.second);
	}

	bool TerrainNewLiquidComponent::isValidPoint(int index)
	{
		if (index < 0 || index >= (mTerrainXSize + 1) * (mTerrainZSize + 1))
			return false;

		int x = index % (mTerrainXSize + 1);
		int z = index / (mTerrainXSize + 1);

		return isValidPoint(x, z);
	}

	bool TerrainNewLiquidComponent::isGridValid(int x, int z)
	{
		Real vertices[4] =
		{
			mTerrainData->getGridJointWorldHeight(x + 0, z + 0),
			mTerrainData->getGridJointWorldHeight(x + 1, z + 0),
			mTerrainData->getGridJointWorldHeight(x + 0, z + 1),
			mTerrainData->getGridJointWorldHeight(x + 1, z + 1),
		};

		Real fSum = 0.0f;
		int nNum = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (mPosition.y > vertices[i])
			{
				fSum += (mPosition.y - vertices[i]);
				nNum++;
			}
		}
		if (nNum >= 3)
		{
			return true;
		}

		if (nNum == 2 && fSum > 40.0f)
		{
			return true;
		}

		return false;

	}
	void TerrainNewLiquidComponent::clearUp()
	{
		releaseGeometry();
		if (mVertexGridIndex)
		{
			delete[]mVertexGridIndex;
			mVertexGridIndex = NULL;
		}
		mVertexNum = 0;
		if (mCellFacesNum)//水体cell面数
		{
			delete[]mCellFacesNum;
			mCellFacesNum = 0;
		}
		if (!mCellList.empty())
		{
			mCellList.clear();
		}
		mRenderableNum = 0;

	}

	//-----------------------------------------------------------------------
	bool TerrainNewLiquidComponent::calculateLiquidGridIndex()//这个很耗，放到加载 [2009/06/09 dscky]
	{
#ifdef _ENABLE_LIQUID_TIME_LOG_
		unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
#endif
		int posGridIndex = calculateGridIndex(mPosition.x, mPosition.z);
		std::set<int>	invalidIndex;
		std::set<int>	validIndex;
		std::deque<int>	checkIndex;
		//计算水体所占用的格子，以指定位置为中心向四周蔓延
		checkIndex.push_back(posGridIndex);
		checkIndex.push_back(posGridIndex + 1);//right
		checkIndex.push_back(posGridIndex - 1);//left
		checkIndex.push_back(posGridIndex + mTerrainXSize + 1);//down
		checkIndex.push_back(posGridIndex - mTerrainXSize - 1);//up
		while (!checkIndex.empty())
		{
			int index = checkIndex.front();
			checkIndex.pop_front();
			if (invalidIndex.find(index) != invalidIndex.end())//无效格子
				continue;
			if (validIndex.find(index) != validIndex.end())//有效格子
				continue;
			if (isValidPoint(index))//未检测格子
			{
				validIndex.insert(index);						//有效
				//增加四周点进行检测
				checkIndex.push_back(index + 1);				//right
				checkIndex.push_back(index - 1);				//left
				checkIndex.push_back(index + mTerrainXSize + 1);//down
				checkIndex.push_back(index - mTerrainXSize - 1);//up
			}
			else
			{
				invalidIndex.insert(index);
			}
		}
		if (validIndex.empty())
		{

			WARNING_LOG("The pos = %f %f %f Ground Liquid No valid Index. You should delete this object.",
				mPosition.x, mPosition.y, mPosition.z);
			return false;
		}
		std::set<int> extendValidIndex(validIndex);
		for (std::set<int>::iterator i = validIndex.begin(); i != validIndex.end(); ++i)
		{
			int index = *i;
			size_t x = index % (mTerrainXSize + 1);
			size_t z = index / (mTerrainXSize + 1);
			if (x > 1 && x < mTerrainXSize && z > 1 && z < mTerrainZSize)
			{
				int NewIndex = 0;

				NewIndex = index + 1;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index + 1);
				}

				NewIndex = index - 1;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index - 1);
				}

				NewIndex = index + mTerrainXSize + 1;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index + mTerrainXSize + 1);
				}

				NewIndex = index - mTerrainXSize - 1;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index - mTerrainXSize - 1);
				}

				NewIndex = index + mTerrainXSize;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index + mTerrainXSize);
				}

				NewIndex = index + mTerrainXSize + 2;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index + mTerrainXSize + 2);
				}

				NewIndex = index - mTerrainXSize - 2;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index - mTerrainXSize - 2);
				}

				NewIndex = index - mTerrainXSize;

				if (NewIndex > 0 && NewIndex < (mTerrainXSize + 1) * (mTerrainZSize + 1))
				{
					extendValidIndex.insert(index - mTerrainXSize);
				}
			}
		}

		mVertexNum = extendValidIndex.size();

		if (mVertexGridIndex)
			delete[]mVertexGridIndex;
		mVertexGridIndex = new int[mVertexNum];
		int gridIndex = 0;
		for (std::set<int>::iterator itIndex = extendValidIndex.begin(); itIndex != extendValidIndex.end(); ++itIndex)
		{
			mVertexGridIndex[gridIndex++] = *itIndex;

			size_t x = *itIndex % (mTerrainXSize + 1);
			size_t z = *itIndex / (mTerrainXSize + 1);
			if (x < mTerrainXSize && z < mTerrainZSize && isGridValid(x, z))
			{
				//EngineManager::getSingleton().getTerrain()->setGroundTypeFromGridIndex(x, z, GroundTypeInfo::GT_LIQUID, mPosition.y);
			}
		}
		return true;
	}
	bool TerrainNewLiquidComponent::registerTerrainLiquildTypeInfo()
	{
		if (!mTerrainData && EngineManager::getSingleton().getTerrain())
		{
			mTerrainData = EngineManager::getSingleton().getTerrain()->getTerrainInfo();
			assert(mTerrainData);
			mTerrainXSize = mTerrainData->getXGridSize();
			mTerrainZSize = mTerrainData->getZGridSize();
			mHeightmap = &mTerrainData->mHeightmap[0];
		}
		for (int VertexIndex = 0; VertexIndex != mVertexNum; ++VertexIndex)
		{
			//注册水体
			size_t x = mVertexGridIndex[VertexIndex] % (mTerrainXSize + 1);
			size_t z = mVertexGridIndex[VertexIndex] / (mTerrainXSize + 1);
			if (x < mTerrainXSize && z < mTerrainZSize && isGridValid(x, z))
			{
				/*if (EngineManager::getSingleton().getTerrainTypeInfos())
					EngineManager::getSingleton()->getTerrainTypeInfos()->setGroundTypeFromGridIndex(
						x, z, GroundTypeInfo::GT_LIQUID, mPosition.y);*/
			}
		}
		return true;
	}
	//把水分割成64*64小块
	void TerrainNewLiquidComponent::calculateIB()//这个很耗，放到加载 [2009/06/09 dscky]
	{
#ifdef _ENABLE_LIQUID_TIME_LOG_
		unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
#endif
		size_t minIndexX = mTerrainXSize;
		size_t minIndexZ = mTerrainZSize;

		size_t maxIndexX = 0;
		size_t maxIndexZ = 0;

		//求出最大和最小索引
		size_t minVertexIndex = 0xFFFFFFFF;
		size_t maxVertexIndex = 0;

		for (size_t i = 0; i < mVertexNum; ++i)
		{
			if (mVertexGridIndex[i] > maxVertexIndex)
			{
				maxVertexIndex = mVertexGridIndex[i];
			}
			if (mVertexGridIndex[i] < minVertexIndex)
			{
				minVertexIndex = mVertexGridIndex[i];
			}
		}

		size_t* pVertexIndexMap = new size_t[maxVertexIndex - minVertexIndex + 1];
		int nXSize = mTerrainData->getXGridSize();
		int nZSize = mTerrainData->getZGridSize();
		bool* pVertexIsLiquid = new bool[(nXSize + 2) * (nZSize + 2)];
		memset(pVertexIsLiquid, 0, sizeof(bool) * (nXSize + 2) * (nZSize + 2));

		for (size_t i = 0; i < mVertexNum; ++i)
		{
			size_t x = mVertexGridIndex[i] % (mTerrainXSize + 1);
			size_t z = mVertexGridIndex[i] / (mTerrainXSize + 1);

			minIndexX = minIndexX > x ? x : minIndexX;
			maxIndexX = maxIndexX < x ? x : maxIndexX;
			minIndexZ = minIndexZ > z ? z : minIndexZ;
			maxIndexZ = maxIndexZ < z ? z : maxIndexZ;
			pVertexIndexMap[mVertexGridIndex[i] - minVertexIndex] = i;
			pVertexIsLiquid[mVertexGridIndex[i]] = true;
		}


		minIndexX = minIndexX / LiquidCellSize;
		minIndexZ = minIndexZ / LiquidCellSize;
		maxIndexX = maxIndexX / LiquidCellSize;
		maxIndexZ = maxIndexZ / LiquidCellSize;

		//计算索引,同时切割水体,计算边
		for (size_t j = minIndexZ; j <= maxIndexZ; ++j)
		{
			for (size_t i = minIndexX; i <= maxIndexX; ++i)
			{
				//每个一个LiquidCell 就是一个renderable
				LiquidCell tempinfo;
				tempinfo.mCellX = i;
				tempinfo.mCellZ = j;
				//基点偏移
				int basex = LiquidCellSize * i;
				int basez = LiquidCellSize * j;
				for (size_t l = 0; l < LiquidCellSize; ++l)
				{
					for (size_t k = 0; k < LiquidCellSize; ++k)
					{
						size_t realx = basex + k;
						size_t realz = basez + l;
						if (realx > mTerrainXSize || realz > mTerrainZSize)
							continue;
						int v0 = realz * (mTerrainXSize + 1) + realx;
						int v1 = v0 + 1;
						int v3 = (realz + 1) * (mTerrainXSize + 1) + realx;
						int v2 = v3 + 1;
						bool flag[4] = { false,false,false,false };
						int position[4];

						if (pVertexIsLiquid[v0])
						{
							flag[0] = true;
							position[0] = pVertexIndexMap[v0 - minVertexIndex];
						}

						if (pVertexIsLiquid[v1])
						{
							flag[1] = true;
							position[1] = pVertexIndexMap[v1 - minVertexIndex];
						}

						if (pVertexIsLiquid[v2])
						{
							flag[2] = true;
							position[2] = pVertexIndexMap[v2 - minVertexIndex];
						}

						if (pVertexIsLiquid[v3])
						{
							flag[3] = true;
							position[3] = pVertexIndexMap[v3 - minVertexIndex];
						}
						if (flag[0] && flag[3] && flag[2] && flag[0])
						{
							//first face 
							tempinfo.mFaces[l][k][0].mV0 = position[0];
							tempinfo.mFaces[l][k][0].mV1 = position[3];
							tempinfo.mFaces[l][k][0].mV2 = position[1];
							tempinfo.mFaces[l][k][0].mUsed = true;
							tempinfo.mFacesNum++;

							//second face
							tempinfo.mFaces[l][k][1].mV0 = position[3];
							tempinfo.mFaces[l][k][1].mV1 = position[2];
							tempinfo.mFaces[l][k][1].mV2 = position[1];
							tempinfo.mFaces[l][k][1].mUsed = true;
							tempinfo.mFacesNum++;

							continue;
						}

						if (flag[0] && flag[3] && flag[2])
						{
							//first face 
							tempinfo.mFaces[l][k][0].mV0 = position[0];
							tempinfo.mFaces[l][k][0].mV1 = position[3];
							tempinfo.mFaces[l][k][0].mV2 = position[2];
							tempinfo.mFaces[l][k][0].mUsed = true;
							tempinfo.mFacesNum++;
							continue;
						}
						//second face
						if (flag[3] && flag[2] && flag[1])
						{
							tempinfo.mFaces[l][k][1].mV0 = position[3];
							tempinfo.mFaces[l][k][1].mV1 = position[2];
							tempinfo.mFaces[l][k][1].mV2 = position[1];
							tempinfo.mFaces[l][k][1].mUsed = true;
							tempinfo.mFacesNum++;
							continue;
						}

						if (flag[2] && flag[1] && flag[0])
						{
							//first face 
							tempinfo.mFaces[l][k][0].mV0 = position[2];
							tempinfo.mFaces[l][k][0].mV1 = position[1];
							tempinfo.mFaces[l][k][0].mV2 = position[0];
							tempinfo.mFaces[l][k][0].mUsed = true;
							tempinfo.mFacesNum++;
							continue;
						}
						//second face
						if (flag[1] && flag[0] && flag[3])
						{
							tempinfo.mFaces[l][k][1].mV0 = position[1];
							tempinfo.mFaces[l][k][1].mV1 = position[0];
							tempinfo.mFaces[l][k][1].mV2 = position[3];
							tempinfo.mFaces[l][k][1].mUsed = true;
							tempinfo.mFacesNum++;
							continue;
						}
					}
				}
				if (tempinfo.mFacesNum)
					mCellList.push_back(tempinfo);
			}
		}

		delete[] pVertexIndexMap;
		delete[] pVertexIsLiquid;

		//写索引临时缓存
		// 保证16位索引，确保低端显卡兼容性 [12/2/2008 JiangWei]
		mRenderableNum = mCellList.size();
		mCellFacesNum = new int32_t[mRenderableNum];
		mTempIndexBuffer = new unsigned short* [mRenderableNum];
		//保存面个数
		for (size_t i = 0; i < mRenderableNum; i++)
		{
			mCellFacesNum[i] = mCellList[i].mFacesNum;
			mTempIndexBuffer[i] = new unsigned short[mCellFacesNum[i] * 3];
		}
		//填充索引buffer
		for (size_t i = 0; i < mRenderableNum; i++)
		{
			size_t j = 0;
			for (size_t l = 0; l < LiquidCellSize; ++l)
			{
				for (size_t m = 0; m < LiquidCellSize; ++m)
				{
					if (mCellList[i].mFaces[l][m][0].mUsed)
					{
						mTempIndexBuffer[i][3 * j] = mCellList[i].mFaces[l][m][0].mV0;
						mTempIndexBuffer[i][3 * j + 1] = mCellList[i].mFaces[l][m][0].mV1;
						mTempIndexBuffer[i][3 * j + 2] = mCellList[i].mFaces[l][m][0].mV2;
						j++;
					}
					if (mCellList[i].mFaces[l][m][1].mUsed)
					{
						mTempIndexBuffer[i][3 * j] = mCellList[i].mFaces[l][m][1].mV0;
						mTempIndexBuffer[i][3 * j + 1] = mCellList[i].mFaces[l][m][1].mV1;
						mTempIndexBuffer[i][3 * j + 2] = mCellList[i].mFaces[l][m][1].mV2;
						j++;
					}
				}
			}
			assert(j == mCellFacesNum[i]);
		}
	}
	bool TerrainNewLiquidComponent::isHaveValidVertex(void)
	{
		return mVertexNum != 0;
	}
	bool TerrainNewLiquidComponent::buildGeometry(void)
	{
		buildCpuData();
		buildGpuData();
		return true;
	}
	bool TerrainNewLiquidComponent::buildCpuData(void)
	{
		if (!mTerrainData)
		{
			mTerrainData = EngineManager::getSingleton().getTerrain()->getTerrainInfo();
			assert(mTerrainData);
			mTerrainXSize = mTerrainData->getXGridSize();
			mTerrainZSize = mTerrainData->getZGridSize();
			mHeightmap = &mTerrainData->mHeightmap[0];
		}

		if (calculateLiquidGridIndex())
		{
			//注册水体信息
			registerTerrainLiquildTypeInfo();
			if (mRenderableNum == 0 && mCellFacesNum == NULL)
			{
				calculateIB();
			}
			//计算顶点位置
			calculateVertexPosition();
			//计算顶点颜色
			calculateVertexColour();
			//计算纹理坐标
			calculateTexcoords();
			return true;
		}
		return false;
	}
	bool TerrainNewLiquidComponent::releaseCpuData(void)
	{
#ifdef _ENABLE_LIQUID_TIME_LOG_
		unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
#endif
		if (mTempPositionBuffer) //顶点
		{
			delete[]mTempPositionBuffer;
			mTempPositionBuffer = NULL;
		}
		if (mTempTexcoordBuffer)	//纹理坐标
		{
			delete[]mTempTexcoordBuffer;
			mTempTexcoordBuffer = NULL;
		}
		if (mTempColourBuffer)	//颜色
		{
			delete[]mTempColourBuffer;
			mTempColourBuffer = 0;
		}
		if (mTempIndexBuffer)	//面索引
		{
			for (size_t i = 0; i < mRenderableNum; ++i)
			{
				unsigned short* index = mTempIndexBuffer[i];
				if (index)
				{
					delete[]index;
				}
			}
			delete[]mTempIndexBuffer;
			mTempIndexBuffer = 0;
		}
		return true;
	}
	bool TerrainNewLiquidComponent::buildGpuData(void)
	{
		if (!isHaveValidVertex())
			return false;
		//生成硬件数据
		createHardwareBuffers();
		//生成renderables
		createRenderables();
		// 通知父节点
		if (mParent)
		{
			mParent->needUpdate();
		}
		setMaterialName(mMaterialName);
		setTexSpeed(mTexSpeed);

		return true;
	}
	bool TerrainNewLiquidComponent::releaseGpuData(void)
	{
		for (auto it = mLiquidRenderables.begin(); it != mLiquidRenderables.end(); ++it)
		{
			delete* it;
		}

		LiquidRenderableList emptyList;
		mLiquidRenderables.swap(emptyList);

		mPositionVertexBuffer.reset();
		mTexcoordVertexBuffer.reset();
		mColourVertexBuffer.reset();

		if (mVertexData)
		{
			delete mVertexData;
			mVertexData = 0;
		}
		if (mIndexData)
		{
			for (size_t renderableIndex = 0; renderableIndex != mRenderableNum; ++renderableIndex)
			{
				if (mIndexData[renderableIndex])
				{
					delete mIndexData[renderableIndex];
					mIndexData[renderableIndex] = 0;
				}
			}
			delete mIndexData;
			mIndexData = 0;
		}
		
		mMaterialBackupList.clear();

		Ogre::String matName;
		if (!mMaterial)
		{
			matName = mMaterial->getName();
			mMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		if (!mLowMaterial)
		{
			matName = mLowMaterial->getName();
			mLowMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		if (!mMiddleMaterial)
		{
			matName = mMiddleMaterial->getName();
			mMiddleMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		if (!mHighMaterial)
		{
			matName = mHighMaterial->getName();
			mHighMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		//清理反射纹理
		deleteReflectRenderTexture();
		return true;
	}
	bool TerrainNewLiquidComponent::releaseGeometry(void)
	{
		releaseGpuData();
		releaseCpuData();
		return true;
	}
	void TerrainNewLiquidComponent::calculateVertexPosition(void)
	{
		if (!mTerrainData)
		{
			mTerrainData = EngineManager::getSingleton().getTerrain()->getTerrainInfo();
			assert(mTerrainData);
			mTerrainXSize = mTerrainData->getXGridSize();
			mTerrainZSize = mTerrainData->getZGridSize();
			mHeightmap = &mTerrainData->mHeightmap[0];
		}
		if (!mTempPositionBuffer)
			mTempPositionBuffer = new float[mVertexNum * 3];
		Ogre::Real minX = 0;
		Ogre::Real minZ = 0;
		Ogre::Real maxX = 0;
		Ogre::Real maxZ = 0;
		for (size_t i = 0; i < mVertexNum; i++)
		{
			Ogre::Vector3 baseposition = mTerrainData->mFirstGridWorldPos;
			int index = mVertexGridIndex[i];
			int x = index % (mTerrainXSize + 1);
			int z = index / (mTerrainXSize + 1);
			mTempPositionBuffer[i * 3] = baseposition.x + x * mTerrainData->mWorldUnit.x;
			mTempPositionBuffer[i * 3 + 1] = mPosition.y;
			mTempPositionBuffer[i * 3 + 2] = baseposition.z + z * mTerrainData->mWorldUnit.z;
			if (i == 0)
			{
				minX = maxX = mTempPositionBuffer[i * 3];
				minZ = maxZ = mTempPositionBuffer[i * 3 + 2];
			}
			minX = minX > mTempPositionBuffer[i * 3] ? mTempPositionBuffer[i * 3] : minX;
			minZ = minZ > mTempPositionBuffer[i * 3 + 2] ? mTempPositionBuffer[i * 3 + 2] : minZ;
			maxX = maxX > mTempPositionBuffer[i * 3] ? maxX : mTempPositionBuffer[i * 3];
			maxZ = maxZ > mTempPositionBuffer[i * 3 + 2] ? maxZ : mTempPositionBuffer[i * 3 + 2];
		}
		// 设置包围盒
		mBoundingBox.setExtents(minX, mPosition.y, minZ, maxX, mPosition.y + 0.1f, maxZ);
	}
	void TerrainNewLiquidComponent::calculateVertexColour(void)
	{
		if (!mTerrainData)
		{
			mTerrainData = EngineManager::getSingleton().getTerrain()->getTerrainInfo();
			assert(mTerrainData);
			mTerrainXSize = mTerrainData->getXGridSize();
			mTerrainZSize = mTerrainData->getZGridSize();
			mHeightmap = &mTerrainData->mHeightmap[0];
		}

		//写colour临时缓存
		if (!mTempColourBuffer)
			mTempColourBuffer = new uint32_t[mVertexNum];
		Ogre::Real liquidHeight = (mPosition.y - mTerrainData->mFirstGridWorldPos.y) * mTerrainData->mInvWorldUnit.y;
		Ogre::Real InversAlphaDependDepth = 1.0f / (liquidHeight - mAlphaDependDepth);
		for (size_t i = 0; i < mVertexNum; i++)
		{
			//不能用高度图来计算颜色，否则alpha将出现裂缝
			Ogre::Vector3 baseposition = mTerrainData->mFirstGridWorldPos;
			int index = mVertexGridIndex[i];
			int x = index % (mTerrainXSize + 1);
			int z = index / (mTerrainXSize + 1);
			Ogre::Real terrainheight = mTerrainData->getWorldIndexWorldHeight(baseposition.x + x * mTerrainData->mWorldUnit.x, baseposition.z + z * mTerrainData->mWorldUnit.z);
			terrainheight = (terrainheight - baseposition.y) / mTerrainData->mWorldUnit.y;
			//color
			Ogre::ColourValue color = mLiquidColour;
			if (mAlphaDependDepth > liquidHeight)
			{
				color.a = 1.0f;
			}
			else
			{
				if (terrainheight > mAlphaDependDepth)
				{
					color.a = (liquidHeight - terrainheight) * InversAlphaDependDepth;
				}
				else
				{
					color.a = 1.0f;
				}
			}
			if (color.a > 1)
				color.a = 1;
			if (color.a < 0)
				color.a = 0;
			mTempColourBuffer[i] = VertexElement::convertColourValue(color, VET_COLOUR);
		}

	}
	//-----------------------------------------------------------------------
	void TerrainNewLiquidComponent::calculateTexcoords(void)
	{
		if (!mTerrainData )
		{
			mTerrainData = EngineManager::getSingleton().getTerrain()->getTerrainInfo();
			assert(mTerrainData);
			mTerrainXSize = mTerrainData->getXGridSize();
			mTerrainZSize = mTerrainData->getZGridSize();
			mHeightmap = &mTerrainData->mHeightmap[0];
		}

		if (!mTempTexcoordBuffer)
			mTempTexcoordBuffer = new float[mVertexNum * 2];
		for (size_t i = 0; i < mVertexNum; ++i)
		{
			size_t index = mVertexGridIndex[i];
			size_t x = index % (mTerrainXSize + 1);
			size_t z = index / (mTerrainXSize + 1);
			mTempTexcoordBuffer[i * 2] = ((Ogre::Real)x) / ((Ogre::Real)mTerrainXSize + 1) * mTexCoordTimes;
			mTempTexcoordBuffer[i * 2 + 1] = ((Ogre::Real)z) / ((Ogre::Real)mTerrainZSize + 1) * mTexCoordTimes;
		}

	}
	//-----------------------------------------------------------------------
	void TerrainNewLiquidComponent::createHardwareBuffers()
	{
		assert(!mVertexData && !mIndexData && mVertexNum);
		//顶点
		if (mVertexData)
		{
			delete mVertexData;
			mVertexData = 0;
		}
		mVertexData = new VertexData;
	    VertexData* vertexData = mVertexData; // cache to register for optimise
		//声明
	
		vertexData->setVertexCount(mVertexNum);


		vertexData->addElement(VERTEXSTREAM_POSITION, 0, 0, VET_FLOAT3, VES_POSITION);
		vertexData->addElement(VERTEXSTREAM_DIFFUSE, 0, 0, VET_COLOUR, VES_DIFFUSE);
		vertexData->addElement(VERTEXSTREAM_TEXCOORD_1, 0, 0, VET_FLOAT2, VES_TEXTURE_COORDINATES);
		//数据
		//mPositionVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(VertexElement::getTypeSize(VET_FLOAT3), mVertexNum, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
		//mPositionVertexBuffer->writeData(0, mVertexNum * VertexElement::getTypeSize(VET_FLOAT3), mTempPositionBuffer, true);
		{

			auto size = mVertexNum * VertexElement::getTypeSize(VET_FLOAT3);

			vertexData->addBindBuffer(VERTEXSTREAM_POSITION, VertexElement::getTypeSize(VET_FLOAT3), mVertexNum);
			vertexData->writeBindBufferData(VERTEXSTREAM_POSITION, (const char*)mTempPositionBuffer, size);
		}
		
		//mColourVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(VertexElement::getTypeSize(VET_COLOUR), mVertexNum, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
		//mColourVertexBuffer->writeData(0, mVertexNum * VertexElement::getTypeSize(VET_COLOUR), mTempColourBuffer, true);
		
		{
			auto size = mVertexNum * VertexElement::getTypeSize(VET_COLOUR);
			vertexData->addBindBuffer(VERTEXSTREAM_DIFFUSE, VertexElement::getTypeSize(VET_COLOUR), mVertexNum);
			vertexData->writeBindBufferData(VERTEXSTREAM_DIFFUSE, (const char*)mTempColourBuffer, size);
		}
		//mTexcoordVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(VertexElement::getTypeSize(VET_FLOAT2), mVertexNum, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
		//mTexcoordVertexBuffer->writeData(0, mVertexNum * VertexElement::getTypeSize(VET_FLOAT2), mTempTexcoordBuffer, true);
		{
			auto size = mVertexNum * VertexElement::getTypeSize(VET_FLOAT2);
			vertexData->addBindBuffer(VERTEXSTREAM_TEXCOORD_1, VertexElement::getTypeSize(VET_FLOAT2), mVertexNum);
			vertexData->writeBindBufferData(VERTEXSTREAM_TEXCOORD_1, (const char*)mTempTexcoordBuffer, size);
		}

		
		//索引
		if (mIndexData)
		{
			for (size_t renderableIndex = 0; renderableIndex != mRenderableNum; ++renderableIndex)
			{
				if (mIndexData[renderableIndex])
				{
					delete mIndexData[renderableIndex];
					mIndexData[renderableIndex] = 0;
				}
			}
			delete mIndexData;
			mIndexData = 0;
		}
		mIndexData = new IndexData * [mRenderableNum];
		for (size_t renderableIndex = 0; renderableIndex != mRenderableNum; ++renderableIndex)
		{
			mIndexData[renderableIndex] = new IndexData;
			IndexData* indexData = mIndexData[renderableIndex]; // cache to register for optimise

			auto indexCount = mCellFacesNum[renderableIndex] * 3;
			indexData->createBuffer(sizeof(unsigned short), mCellFacesNum[renderableIndex] * 3);

			assert(65535 > indexCount);
			indexData->writeData((const char*)mTempIndexBuffer[renderableIndex], 
				mCellFacesNum[renderableIndex] * 3 * sizeof(unsigned short));
		}
	}
	void TerrainNewLiquidComponent::createRenderables()
	{
		// 把旧的去掉
		for (auto it = mLiquidRenderables.begin(); it != mLiquidRenderables.end(); ++it)
		{
			LiquidWarCraftRenderable* pRenderable = *it;
			delete pRenderable;
		}
		mLiquidRenderables.clear();

		for (size_t i = 0; i < mRenderableNum; ++i)
		{
			LiquidWarCraftRenderable* liquidRenderable = new LiquidWarCraftRenderable(this);
			mLiquidRenderables.push_back(liquidRenderable);

			liquidRenderable->mRenderOp.indexData = mIndexData[i];
			liquidRenderable->mRenderOp.useIndexes = true;
			liquidRenderable->mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
			liquidRenderable->mRenderOp.vertexData = mVertexData;

			liquidRenderable->prepare(mVertexData, mIndexData[i]);
			//liquidRenderable->mMaterial = mMaterial;

			liquidRenderable->mBoundingBox.setExtents(
				mTerrainData->mWorldUnit.x * mCellList[i].mCellX * LiquidCellSize + mTerrainData->mFirstGridWorldPos.x,
				mPosition.y,
				mTerrainData->mWorldUnit.z * mCellList[i].mCellZ * LiquidCellSize + mTerrainData->mFirstGridWorldPos.z,
				mTerrainData->mWorldUnit.x * (mCellList[i].mCellX + 1) * LiquidCellSize + mTerrainData->mFirstGridWorldPos.x,
				mPosition.y + 1.0f,
				mTerrainData->mWorldUnit.z * (mCellList[i].mCellZ + 1) * LiquidCellSize + mTerrainData->mFirstGridWorldPos.z);
		}
	}
	const String& TerrainNewLiquidComponent::getMovableType(void) const
	{
		return msMovableType;
	}
	const Ogre::AxisAlignedBox& TerrainNewLiquidComponent::getBoundingBox(void) const
	{
		return mBoundingBox;
	}
	Real TerrainNewLiquidComponent::getBoundingRadius(void) const
	{
		return (mBoundingBox.getMaximum() - mBoundingBox.getCenter()).length();
	}
	void TerrainNewLiquidComponent::_notifyCurrentCamera(Ogre::Camera* camera)
	{
		mCurrentCamera = camera;

		bool enableReflect = true;
		Real boundRadius = getBoundingRadius();
		Real squaredDepth = (mPosition - camera->getDerivedPosition()).squaredLength();


		// 更新材质
		if (mManager != NULL && mManager->getFogMode() != Ogre::FOG_NONE && squaredDepth >= Ogre::Math::Sqr(mManager->getFogEnd() + boundRadius))
		{
			if (beyondFogDirty)
			{
				size_t numRenderables = mLiquidRenderables.size();
				mMaterialBackupList.resize(numRenderables);

				for (uint32 i = 0; i < numRenderables; ++i)
				{
					GeneralRenderable* pRenderable = mLiquidRenderables[i];
					const Ogre::MaterialPtr& material = pRenderable->getMaterial();
					mMaterialBackupList[i] = material;
					auto mat = Ogre::MaterialManager::getSingleton().getByName("FogColor");
					pRenderable->setMaterial(mat);
				}
				beyondFogDirty = false;
				enableReflect = false;
			}
		}
		else
		{
			if (!beyondFogDirty)
			{
				size_t numRenderables = mLiquidRenderables.size();
				for (uint32 i = 0; i < numRenderables; ++i)
				{
					GeneralRenderable* pRenderable = mLiquidRenderables[i];
					pRenderable->setMaterial(mMaterialBackupList[i]);
					mMaterialBackupList[i].reset();
				}
				beyondFogDirty = true;
				enableReflect = true;
			}
		}

		if (mReflectRenderTargetListener != NULL)
		{
			mReflectRenderTargetListener->enableUpdate(enableReflect);
		}
	}
	void TerrainNewLiquidComponent::_updateRenderQueue(Ogre::RenderQueue* queue)
	{
		
	}

	void TerrainNewLiquidComponent::createReflectRenderTexture(void)
	{
		if (mReflectRenderTargetListener)
		{
			delete mReflectRenderTargetListener;
			mReflectRenderTargetListener = 0;
		}
		mReflectRenderTargetListener = new ReflectRenderTargetListener(
			this
			, mPosition
			, mReflectTextureName);
	}

	void TerrainNewLiquidComponent::deleteReflectRenderTexture(void)
	{
		if (mReflectRenderTargetListener)//发射listener
		{
			delete mReflectRenderTargetListener;
			mReflectRenderTargetListener = 0;
		}
	}

	void TerrainNewLiquidComponent::setMaterialName(const String& materialName)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(materialName);
		if (!material)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
				"Could not find material " + materialName,
				"TerrainLiquid::setMaterialName");
			return;
		}
		mNumMaterials = 0;
		//生成唯一字符串
		std::ostringstream str;
		mTextureNums++;
		str.str(BLANKSTRING);
		str << mTextureNums << "low";
		mLowMaterialName = str.str();

		str.str(BLANKSTRING);
		str << mTextureNums << "middle";
		mMiddleMaterialName = str.str();

		str.str(BLANKSTRING);
		str << mTextureNums << "high";
		mHighMaterialName = str.str();

		str.str(BLANKSTRING);
		str << mTextureNums << "Reflect";
		mReflectTextureName = str.str();

		
		mNumMaterials |= LIQUID_LOW;
		mNumMaterials |= LIQUID_MIDDILE;
		//mNumMaterials |= LIQUID_HIGH;
		
		updateRenderables(LIQUID_MIDDILE);
	}

	void TerrainNewLiquidComponent::updateRenderables(LiquidRenderLevelEnum renderclass)
	{
		if (mCurrentMaterialType == renderclass)
		{
			return;
		}
		else
		{
			if (mNumMaterials & renderclass)
			{
				mCurrentMaterialType = renderclass;
			}
			else if (mNumMaterials & LIQUID_MIDDILE)
			{
				mCurrentMaterialType = LIQUID_MIDDILE;
			}
			else
			{
				mCurrentMaterialType = LIQUID_LOW;
			}
		}

		cleanClonedMaterials();

		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(mMaterialName);
		if (!material)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
				"Could not find material " + mMaterialName,
				"TerrainLiquid::setMaterialName");
			return;
		}

		switch (mCurrentMaterialType)
		{
		case LIQUID_HIGH:
		{
			cloneHighTechMaterial(material);
			break;
		}
		case LIQUID_MIDDILE:
		{
			cloneMidTechMaterial(material);
		}
		default:
		{
			cloneLowTechMaterial(material);
			break;
		}
		}

		for (auto it = mLiquidRenderables.begin(); it != mLiquidRenderables.end(); ++it)
		{
			(*it)->setMaterial(mMaterial);
		}

	}

	void TerrainNewLiquidComponent::cloneHighTechMaterial(Ogre::MaterialPtr& srcMat)
	{

		mHighMaterial = srcMat->clone(mHighMaterialName);


		auto unitState = mHighMaterial->getTextureUnit(REFLECT_TEXTUREUNIT_NAME);
		assert(unitState);
		unitState->setTexture(mReflectTextureName, nullptr);

		createReflectRenderTexture();

		mHighMaterial->preLoad();

		mMaterial = mHighMaterial;
		setUpdateFrequency(10.0f);
	}

	void TerrainNewLiquidComponent::cloneMidTechMaterial(Ogre::MaterialPtr& srcMat)
	{
		mMiddleMaterial = srcMat->clone(mMiddleMaterialName);


		mMiddleMaterial->preLoad();

		mMaterial = mMiddleMaterial;
	}

	void TerrainNewLiquidComponent::cloneLowTechMaterial(Ogre::MaterialPtr& srcMat)
	{
		mLowMaterial = srcMat->clone(mLowMaterialName);

		mLowMaterial->preLoad();
		mMaterial = mLowMaterial;
		setUpdateFrequency(0.0f);
	}

	void TerrainNewLiquidComponent::cleanClonedMaterials()
	{
		for (LiquidRenderableList::const_iterator it = mLiquidRenderables.begin(); it != mLiquidRenderables.end(); ++it)
		{
			
		}

		//清理材质
		mMaterialBackupList.clear();

		Ogre::String matName;
		if (mMaterial)
		{
			matName = mMaterial->getName();
			mMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		if (mLowMaterial)
		{
			matName = mLowMaterial->getName();
			mLowMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		if (mMiddleMaterial)
		{
			matName = mMiddleMaterial->getName();
			mMiddleMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}
		if (mHighMaterial)
		{
			matName = mHighMaterial->getName();
			mHighMaterial.reset();
			if (Ogre::MaterialManager::getSingleton().unloadUnreferencedResource(matName))
				Ogre::MaterialManager::getSingleton().remove(matName);
		}

		deleteReflectRenderTexture();
	}

	void TerrainNewLiquidComponent::setLiquidAlphaDependDepth(const Ogre::Real& depth)
	{
		mAlphaDependDepth = depth;
		//更新顶点颜色
		calculateVertexColour();
	}
	//
	void TerrainNewLiquidComponent::setLiquidColour(const Ogre::ColourValue& liquidColour)
	{
		mLiquidColour = liquidColour;
		//更新水体颜色
		calculateVertexColour();
	}
	Ogre::ColourValue TerrainNewLiquidComponent::getLiquidColour(void) const
	{
		return mLiquidColour;
	}

	//void TerrainNewLiquidComponent::setLiquidColourDependDepth(const Ogre::Real &depth)
	//{
	//	mColourDependDepth = depth;
	//	//更新水体颜色深度依赖值
	//	calculateVertexColour();
	//}

	void TerrainNewLiquidComponent::setTexCoordTimes(const Ogre::Real& times)
	{
		mTexCoordTimes = times;
		//更新纹理坐标
		calculateTexcoords();
	}

	void TerrainNewLiquidComponent::setTexSpeed(const Ogre::Real& speed)
	{
		if (mCurrentMaterialType == LIQUID_LOW)
		{
			auto texUnit = mLowMaterial->getTextureUnit(ANIMATION_TEXTUREUNIT_NAME);

			assert(texUnit && "TerrainNewLiquidComponent: There is no TextureUnit Animation");

			size_t framnum = texUnit->getNumFrames();

			assert(framnum > 0);

			//支持简单纹理
			if (framnum == 1)
				return;

			Ogre::Real texSpeed = texUnit->getAnimationDuration();

			Ogre::String texname = texUnit->getFrameTextureName(0);

			size_t duan, dian;
			duan = dian = 0;

			duan = texname.find_last_of("_");
			dian = texname.find_last_of(".");
			Ogre::String baseName = texname.substr(0, duan);
			Ogre::String extName = texname.substr(dian);
			texUnit->setAnimatedTextureName(baseName + extName, framnum, speed);
		}
	}

	void TerrainNewLiquidComponent::setHighTexSpeed(const Ogre::Real& speed)
	{
		if (mNumMaterials & LIQUID_MIDDILE)
		{
			auto texUnit = mMiddleMaterial->getTextureUnit(ANIMATION_TEXTUREUNIT_NAME);
			assert(texUnit && "TerrainNewLiquidComponent: There is no TextureUnit Animation");

			size_t framnum = texUnit->getNumFrames();
			assert(framnum > 1);

			Ogre::String texname = texUnit->getFrameTextureName(0);

			size_t duan, dian;
			duan = dian = 0;
			duan = texname.find_last_of("_");
			dian = texname.find_last_of(".");
			Ogre::String baseName = texname.substr(0, duan);
			Ogre::String extName = texname.substr(dian);
			texUnit->setAnimatedTextureName(baseName + extName, framnum, speed);
		}
		if (mNumMaterials & LIQUID_HIGH)
		{
			auto texUnit = mHighMaterial->getTextureUnit(ANIMATION_TEXTUREUNIT_NAME);
			assert(texUnit && "TerrainNewLiquidComponent: There is no TextureUnit Animation");

			size_t framnum = texUnit->getNumFrames();
			assert(framnum > 1);

			Ogre::String texname = texUnit->getFrameTextureName(0);

			size_t duan, dian;
			duan = dian = 0;
			duan = texname.find_last_of("_");
			dian = texname.find_last_of(".");
			Ogre::String baseName = texname.substr(0, duan);
			Ogre::String extName = texname.substr(dian);
			texUnit->setAnimatedTextureName(baseName + extName, framnum, speed);
		}
	}

	//-----------------------------------------------------------------------
	const String& TerrainNewLiquidComponent::getMaterialName(void) const
	{
		return mMaterialName;
	}

	void TerrainNewLiquidComponent::setReflectMatrix(const Ogre::Matrix4& m)
	{
		if (mCurrentMaterialType == LIQUID_LOW)
			return;
		if (mCurrentMaterialType == LIQUID_MIDDILE)
			return;
		if (mCurrentMaterialType == LIQUID_HIGH)
		{
			return;
		}
	}
	bool TerrainNewLiquidComponent::loadFromStream(
		Ogre::Serializer* pSerializer, 
		Ogre::DataStreamPtr& stream)
	{
		if (pSerializer && stream->eof() == false)
		{
			pSerializer->readData(stream, &mVertexNum, 1, sizeof(size_t));
			mVertexGridIndex = new int[mVertexNum];
			pSerializer->readData(stream, mVertexGridIndex, 1, mVertexNum * sizeof(int));
			pSerializer->readData(stream, &mRenderableNum, 1, sizeof(size_t));
			mCellFacesNum = new int32_t[mRenderableNum];
			mTempIndexBuffer = new unsigned short* [mRenderableNum];
			for (size_t renderableIndex = 0; renderableIndex != mRenderableNum; ++renderableIndex)
			{
				LiquidCell tempinfo;
				pSerializer->readData(stream, &(tempinfo.mCellX), 1, sizeof(size_t));
				pSerializer->readData(stream, &(tempinfo.mCellZ), 1, sizeof(size_t));
				mCellList.push_back(tempinfo);
				pSerializer->readData(stream, &(mCellFacesNum[renderableIndex]), 1, sizeof(size_t));
				mTempIndexBuffer[renderableIndex] = new unsigned short[mCellFacesNum[renderableIndex] * 3];
				pSerializer->readData(stream, mTempIndexBuffer[renderableIndex], 1, mCellFacesNum[renderableIndex] * 3 * sizeof(unsigned short));
			}
			return true;
		}
		return false;
	}
	bool TerrainNewLiquidComponent::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		return false;
	}
	std::size_t	TerrainNewLiquidComponent::calcSerializedSize()
	{
		size_t tmpSize = 0;

		tmpSize += sizeof(mVertexNum);
		tmpSize += mVertexNum * sizeof(int);
		tmpSize += sizeof(mRenderableNum);
		for (size_t renderableIndex = 0; renderableIndex != mRenderableNum; ++renderableIndex)
		{
			tmpSize += sizeof(mCellList[renderableIndex].mCellX);
			tmpSize += sizeof(mCellList[renderableIndex].mCellZ);
			tmpSize += sizeof(mCellFacesNum[renderableIndex]);
			tmpSize += mCellFacesNum[renderableIndex] * 3 * sizeof(unsigned short);
		}

		return tmpSize;
	}
	bool TerrainNewLiquidComponent::setTerrainRelatedData(TerrainInfo* pData)
	{
		if (pData)
		{
			mTerrainData = pData;
			mTerrainXSize = mTerrainData->getXGridSize();
			mTerrainZSize = mTerrainData->getZGridSize();
			mHeightmap = &mTerrainData->mHeightmap[0];
			return true;
		}
		return false;

	}

	Ogre::Real TerrainNewLiquidComponent::getUpdateFrequency() const
	{
		if (mReflectRenderTargetListener == NULL || mReflectRenderTargetListener->getUpdateCycle() == 0)
			return 0.0f;

		return 1000.0f / mReflectRenderTargetListener->getUpdateCycle();
	}

	void TerrainNewLiquidComponent::setUpdateFrequency(Ogre::Real updateFrequency)
	{
		if (mReflectRenderTargetListener == NULL)
			return;

		updateFrequency = Ogre::Math::Abs(updateFrequency);
		if (updateFrequency < 1.0e-6)
			mReflectRenderTargetListener->setUpdateCycle(0);
		else
			mReflectRenderTargetListener->setUpdateCycle(unsigned long(Ogre::Math::Floor(1000 / updateFrequency)));
	}

	const std::vector<Renderable*>& TerrainNewLiquidComponent::getRenderableList()
	{
		mRenderables.clear();
		for (auto r : mLiquidRenderables)
		{
			mRenderables.push_back(r);
		}
		return mRenderables;
	}
}
