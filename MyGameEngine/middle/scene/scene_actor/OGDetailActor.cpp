#include "OgreHeader.h"
#include "OGDetailActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"

namespace Orphigine
{
	const String DetailActor::msType = "DetailActor";
	const String DetailActor::msCategory = "StaticObject";

	class DetailActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new DetailActor;
		}
	};

	

	ActorFactory* DetailActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

	DetailActor::DetailActor()
	{

	}

	DetailActor::~DetailActor()
	{

	}

	//-----------------------------------------------------------------------
	const String& DetailActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& DetailActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void DetailActor::createRenderInstance()
	{
		PlacementActor::createRenderInstance();

		//    if (!mMaterialName.empty())
		{
			createDetailObject();
		}
	}
	//-----------------------------------------------------------------------
	void DetailActor::destroyRenderInstance(void)
	{
		//   if (mTerrainLiquid)
		{
			destroyDetailObject();
		}
		mMaterialName.clear();
		mSplitNumber=3;
		mDensity=0.1;
		mDetailWidth=64;
		mDetailHeight=32;
		mRegionWidth=20;
		mRegionHeight=20;
		mRandPos=0.1;
		mDetailRandSize = 0;
		mLightThrehold1=0.4f;
		mLightThrehold2=0.4f;
		mLightThrehold3=0.4f;
		mLightThrehold4=0.4f;
		PlacementActor::destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	void DetailActor::updateRenderInstance()
	{
		if (!mMaterialName.empty())
		{
			updateDetailObject();
		}
	}
	bool DetailActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{	
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != SceneSerializer::SFF_DETAIL_OBJ)
			{
				pSerializer->skipChunk(stream);
				return false;
			}
			mMaterialName = pSerializer->readStringBin(stream);
			mDetailFileName = pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mSplitNumber,1,sizeof(int));
			pSerializer->readData(stream,&mRandPos,1,sizeof(float));
			pSerializer->readData(stream,&mDensity,1,sizeof(float));
			pSerializer->readData(stream,&mDetailWidth,1,sizeof(float));
			pSerializer->readData(stream,&mDetailHeight,1,sizeof(float));
			pSerializer->readData(stream,&mDetailRandSize,1,sizeof(float));
			pSerializer->readData(stream,&mRegionWidth,1,sizeof(float));
			pSerializer->readData(stream,&mRegionHeight,1,sizeof(float));
			mImageName = pSerializer->readStringBin(stream);
			mOldImageName = pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mLightThrehold1,1,sizeof(float));
			pSerializer->readData(stream,&mLightThrehold2,1,sizeof(float));
			pSerializer->readData(stream,&mLightThrehold3,1,sizeof(float));
			pSerializer->readData(stream,&mLightThrehold4,1,sizeof(float));

			pSerializer->readData(stream,&xinc,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&zinc,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&xpos,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&zpos,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&offset,1,sizeof(Ogre::Vector4));
			return true;			
		}
		return false;	
	}
	bool DetailActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;		
	}	
	std::size_t	DetailActor::calcSerializedSize()
	{
		return 0;
	}

	void	DetailActor::createDetailObject()
	{
		
	}

	void	DetailActor::destroyDetailObject()
	{
		
	}

	void	DetailActor::updateDetailObject()
	{
		destroyDetailObject();
		createDetailObject();
	}

	void	DetailActor::onPosChange()
	{
		updateDetailObject();
	}

	

	

}

