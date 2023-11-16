#include "OgreHeader.h"
#include "OGTerrainLiquidActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"
#include "OgreAxisAlignedBox.h"
#include "engine_manager.h"
#include "OGTerrainNewLiquidComponent.h"

using Ogre::AxisAlignedBox;


namespace Orphigine {


	const String TerrainLiquidActor::msType = "TerrainLiquid";
	const String TerrainLiquidActor::msCategory = "StaticObject";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class TerrainLiquidActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new TerrainLiquidActor;
		}
	};


	//////////////////////////////////////////////////////////////////////////
	// TerrainLiquidActor class
	//////////////////////////////////////////////////////////////////////////
	TerrainLiquidActor::TerrainLiquidActor(void)
		: Actor()
		//,mSystem()
		,mLiquidIndex(-1)
		,mMaterialName()
		,mPosition(Ogre::Vector3::ZERO)
		,mLiquidColour()
		,mHighLiquidColour()
		,mAlphaDependDepth(-5.0f)
		,mTexCoordTimes(100.0f)
		,mHighTexCoordTimes(10.0f)
		,mHighTexSpeed(2.0f)
		,mTexSpeed(1)
		,mMaterialDirty(false)
		,mAlphaDepthDirty(false)
		,mPositionDirty(false)
		,mLiquidColourDirty(false)
		,mTexCoordTimesDirty(false)
		,mTexSpeedDirty(false)
		,mHighLiquidColourDirty(false)
		,mHighTexSpeedDirty(false)
		,mHighTexCoordTimesDirty(false)
		,mRenderClassDirty(false)
		, mTerrainLiquid(nullptr)
	{
		
	}
	//-----------------------------------------------------------------------
	TerrainLiquidActor::~TerrainLiquidActor()
	{
		
	}

	
	//-----------------------------------------------------------------------
	const String& TerrainLiquidActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& TerrainLiquidActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void TerrainLiquidActor::createRenderInstance()
	{
		return;
		assert(!mMaterialName.empty());

		if (!mTerrainLiquid)
		{
			mTerrainLiquid = new TerrainNewLiquidComponent(mPosition, mMaterialName,
				mLiquidColour, mAlphaDependDepth, mTexCoordTimes, mTexSpeed);
			mTerrainLiquid->buildCpuData();
		}
		else
		{
			mTerrainLiquid->registerTerrainLiquildTypeInfo();
			mTerrainLiquid->calculateVertexPosition();
			mTerrainLiquid->calculateVertexColour();
			mTerrainLiquid->calculateTexcoords();
		}
		mTerrainLiquid->buildGpuData();

		if (!mTerrainLiquid->getParentSceneNode())
		{
			Ogre::SceneNode* parent = 
				EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode("liquid");
			parent->attachObject(mTerrainLiquid);
		}
	}
	//-----------------------------------------------------------------------
	void TerrainLiquidActor::destroyRenderInstance(void)
	{
		Ogre::SceneNode* parent = mTerrainLiquid->getParentSceneNode();
		assert(parent);
		if (parent)
		{
			parent->getCreator()->destroySceneNode(parent);
		}

		mTerrainLiquid->releaseGpuData();
	}
	//-----------------------------------------------------------------------
	void TerrainLiquidActor::updateRenderInstance()
	{
		if (mTerrainLiquid)
		{
			destroyRenderInstance();
			destroyTerrainLiquid();

			createRenderInstance();
		}
	}




	//-----------------------------------------------------------------------
	void TerrainLiquidActor::createTerrainLiquid()
	{
		Ogre::SceneNode* parent = 
			EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode("liquid");

		mTerrainLiquid = new TerrainNewLiquidComponent(mPosition, mMaterialName, 
			mLiquidColour, mAlphaDependDepth, mTexCoordTimes, mTexSpeed);
		mTerrainLiquid->buildCpuData();
		mTerrainLiquid->buildGpuData();
		parent->attachObject(mTerrainLiquid);
	}

	//-----------------------------------------------------------------------
	void TerrainLiquidActor::destroyTerrainLiquid(void)
	{
		
	}
	
	//-----------------------------------------------------------------------
	void TerrainLiquidActor::setUpdateFrequency(Ogre::Real updateFrequency)
	{
		mTerrainLiquid->setUpdateFrequency(updateFrequency);
	}
	//-----------------------------------------------------------------------
	ActorFactory* TerrainLiquidActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

	bool TerrainLiquidActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(pSerializer && stream->eof() == false )
		{

			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SceneSerializer::SFF_LIQUID_OBJ)
			{
			
				pSerializer->skipChunk(stream);
				return false;
			}
			mMaterialName=pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mAlphaDependDepth,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mPosition,1,sizeof(Ogre::Vector3));	

			LiquidRenderLevelEnum renderClass;
			pSerializer->readData(stream,&renderClass,1,sizeof(LiquidRenderLevelEnum));

			pSerializer->readData(stream,&mLiquidColour,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mHighLiquidColour,1,sizeof(Ogre::ColourValue));

			pSerializer->readData(stream,&mTexCoordTimes,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mHighTexCoordTimes,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mTexSpeed,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mHighTexSpeed,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mHighWaveSpeed,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mHighGridSize,1,sizeof(Ogre::Real));

			pSerializer->readData(stream,&mLiquidIndex,1,sizeof(int));

			Ogre::Vector3 mMinimum;
			Ogre::Vector3 mMaximum;
			Ogre::AxisAlignedBox::Extent mExtent;
			pSerializer->readData(stream,&mMinimum,1,sizeof(Ogre::Vector3));
			pSerializer->readData(stream, &mMaximum, 1, sizeof(Ogre::Vector3));
			pSerializer->readData(stream, &mExtent, 1, sizeof(Ogre::AxisAlignedBox::Extent));
			
			int32_t mVertexNum = 0;
			pSerializer->readData(stream, &mVertexNum, 1, sizeof(int32_t));
			auto mVertexGridIndex = new int[mVertexNum];
			pSerializer->readData(stream, mVertexGridIndex, 1, mVertexNum * sizeof(int));
			int32_t mRenderableNum;
			pSerializer->readData(stream, &mRenderableNum, 1, sizeof(int32_t));
			auto mCellFacesNum = new int32_t[mRenderableNum];
			auto mTempIndexBuffer = new unsigned short* [mRenderableNum];
			for (int32_t renderableIndex = 0; renderableIndex != mRenderableNum; ++renderableIndex)
			{
				int32_t cellx;
				pSerializer->readData(stream, &(cellx), 1, sizeof(int32_t));
				pSerializer->readData(stream, &(cellx), 1, sizeof(int32_t));
				pSerializer->readData(stream, &(mCellFacesNum[renderableIndex]), 1, sizeof(int32_t));
				mTempIndexBuffer[renderableIndex] = new unsigned short[mCellFacesNum[renderableIndex] * 3];
				pSerializer->readData(stream, mTempIndexBuffer[renderableIndex], 1, mCellFacesNum[renderableIndex] * 3 * sizeof(unsigned short));
			}

			return true;			
		}
		return false;		
	}
	bool TerrainLiquidActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}	
	std::size_t	TerrainLiquidActor::calcSerializedSize()
	{
		return 0;
	}
	bool TerrainLiquidActor::buildTerrainLiquidAndCpuData(TerrainInfo* pData)
	{
		if (!mTerrainLiquid)
		{
			mTerrainLiquid = new TerrainNewLiquidComponent(mPosition, mMaterialName, mLiquidColour, mAlphaDependDepth, mTexCoordTimes, mTexSpeed);
		
			//初始化地形数据
			mTerrainLiquid->setTerrainRelatedData(pData);
			//生成cpu数据
			mTerrainLiquid->buildCpuData();
		}
		return true;
	}

	void TerrainLiquidActor::setVisible(bool show)
	{
		if (mTerrainLiquid)
		{
			if (mTerrainLiquid->getParentSceneNode())
			{
				mTerrainLiquid->getParentSceneNode()->setVisible(show);
			}
		}
	}

}
