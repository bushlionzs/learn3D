#include "OgreHeader.h"
#include "OGSkyLayerActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"

namespace Orphigine
{

	//-----------------------------------------------------------------------
	const String SkyLayerActor::msType = "SkyLayer";
	const String SkyLayerActor::msCategory = "Enviroment";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class SkyLayerActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new SkyLayerActor;
		}
	};

	


	SkyLayerActor::SkyLayerActor(void)
		: Actor()
		, mMeshName("") 
		,mLayerIndex(-1)
		,mDrawFirst(false)
		,mScale(1.0f)
		,mYScale(1.0f)
		,mKeepDistance(true)
		,mKeepHeight(true)
		,mKeepOrient(false)
		,mEnableLight(false)
		,mHeightOffset(0.f)
		,mAngle(0.f)
		,mUScroll(0.f)
		,mVScroll(0.f)
		,mAffectByFog(false)
	{
		
	}
	//-----------------------------------------------------------------------
	SkyLayerActor::~SkyLayerActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& SkyLayerActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& SkyLayerActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void SkyLayerActor::createRenderInstance()
	{
		
	}
	//-----------------------------------------------------------------------
	void SkyLayerActor::destroyRenderInstance(void)
	{
	}

	//-----------------------------------------------------------------------
	bool SkyLayerActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(pSerializer && stream->eof() == false )
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SceneSerializer::SFF_SKYLAYER_OBJ)
			{
				NOTICE_LOG("Load SkyPlaneActor From Stream Failed. ChunkId Error");
				pSerializer->skipChunk(stream);
				return false;
			}
			mMeshName = pSerializer->readStringBin(stream);
			int temp;
			pSerializer->readData(stream, &temp, 1, sizeof(int));
			mAffectByFog = temp & 0x00010000;
			mLayerIndex = temp & 0x0000FFFF;
			pSerializer->readData(stream, &mScale, 1, sizeof(Ogre::Real));	
			pSerializer->readData(stream, &mKeepDistance, 1 ,sizeof(bool));
			pSerializer->readData(stream, &mKeepHeight, 1 ,sizeof(bool));
			pSerializer->readData(stream, &mKeepOrient, 1 ,sizeof(bool));
			pSerializer->readData(stream, &mEnableLight, 1 ,sizeof(bool));			
			pSerializer->readData(stream, &mHeightOffset, 1, sizeof(Ogre::Real));
			pSerializer->readData(stream, &mAngle, 1, sizeof(Ogre::Real));			
			pSerializer->readData(stream, &mUScroll, 1, sizeof(Ogre::Real));			
			pSerializer->readData(stream, &mVScroll, 1, sizeof(Ogre::Real));			
			pSerializer->readData(stream, &mYScale, 1, sizeof(Ogre::Real));
			mDrawFirst = false;

			if (version >= 103)
			{
				pSerializer->readData(stream, &mIndex, 1, sizeof(mIndex));
			}

			return true;			
		}
		return false;			
	}
	//-----------------------------------------------------------------------
	bool SkyLayerActor::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;		
	}	
	//-----------------------------------------------------------------------
	std::size_t	SkyLayerActor::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void SkyLayerActor::updateRenderInstanceImpl(void)
	{
	}
	//-----------------------------------------------------------------------
	void SkyLayerActor::updateRenderInstance(void)
	{
		
	}
	//-----------------------------------------------------------------------
	ActorFactory* SkyLayerActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

}
