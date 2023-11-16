#include "OgreHeader.h"
#include "OGSkyActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"
#include "engine_manager.h"

namespace Orphigine
{
	const String SkyPlaneActor::msType = "SkyPlane";
	const String SkyPlaneActor::msCategory = "Enviroment";

	//////////////////////////////////////////////////////////////////////////
	// Plane/String converter
	//////////////////////////////////////////////////////////////////////////

	static String toString(const Ogre::Plane& val)
	{
		return String();
	}

	static Ogre::Plane parsePlane(const String& val)
	{
		return Ogre::Plane();
	}

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class SkyPlaneActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new SkyPlaneActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// SkyPlaneActor class
	//////////////////////////////////////////////////////////////////////////

	SkyPlaneActor::SkyPlaneActor(void)
		: Actor()
		,mMaterialName("BaseWhite")
		,mLayer(6)
		,mScale(1000)
		,mTiling(10)
		,mBow(0)
		,mXsegments(1)
		,mYsegments(1)
		,mDrawFirst(false)
	{
		mPlane = Ogre::Plane(Ogre::Vector3(0,1,0),0);
		
	}
	//-----------------------------------------------------------------------
	SkyPlaneActor::~SkyPlaneActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& SkyPlaneActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& SkyPlaneActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void SkyPlaneActor::createRenderInstance()
	{
		
	}
	//-----------------------------------------------------------------------
	void SkyPlaneActor::destroyRenderInstance(void)
	{
		
	}
	bool SkyPlaneActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(pSerializer && stream->eof() == false )
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SceneSerializer::SFF_SKYPLANE_OBJ)
			{

				pSerializer->skipChunk(stream);
				return false;
			}
			mMaterialName=pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mPlane,1,sizeof(Ogre::Plane));

			pSerializer->readData(stream,&mScale,1,sizeof(Ogre::Real));		
			pSerializer->readData(stream,&mTiling,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mBow,1,sizeof(Ogre::Real));

			pSerializer->readData(stream,&mDrawFirst,1,sizeof(bool));
			mDrawFirst = false;
			pSerializer->readData(stream,&mXsegments,1,sizeof(int));
			pSerializer->readData(stream,&mYsegments,1,sizeof(int));
			mLayer = 6;
			return true;			
		}
		return false;		
	}
	bool SkyPlaneActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;		
	}	
	std::size_t	SkyPlaneActor::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void SkyPlaneActor::updateRenderInstanceImpl(void)
	{

	}
	//-----------------------------------------------------------------------
	void SkyPlaneActor::updateRenderInstance(void)
	{

	}
	//-----------------------------------------------------------------------
	ActorFactory* SkyPlaneActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}


	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	const String SkyDomeActor::msType = "SkyDome";
	const String SkyDomeActor::msCategory = "Enviroment";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class SkyDomeActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new SkyDomeActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// SkyDomeActor class
	//////////////////////////////////////////////////////////////////////////

	SkyDomeActor::SkyDomeActor(void)
		: Actor()
		, mMaterialName("BaseWhite") 
		,mCurvature(10)
		,mTiling(8)
		,mDistance(4000)
		,mLayer(4)
		,mDrawFirst(false)
		,mOrientation(Ogre::Quaternion::IDENTITY)
		,mXsegments(16)
		,mYsegments(16)
		,mYsegments_keep(-1)
	{
		
	}
	//-----------------------------------------------------------------------
	SkyDomeActor::~SkyDomeActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& SkyDomeActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& SkyDomeActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void SkyDomeActor::createRenderInstance()
	{
		
	}
	//-----------------------------------------------------------------------
	void SkyDomeActor::destroyRenderInstance(void)
	{
		
	}
	bool SkyDomeActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(pSerializer && stream->eof() == false )
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SceneSerializer::SFF_SKYDOME_OBJ)
			{

				pSerializer->skipChunk(stream);
				return false;
			}
			mMaterialName=pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mCurvature,1,sizeof(Ogre::Real));		
			pSerializer->readData(stream,&mTiling,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mDistance,1,sizeof(Ogre::Real));

			pSerializer->readData(stream,&mDrawFirst,1,sizeof(bool));
			mDrawFirst = false;

			pSerializer->readData(stream,&mOrientation,1,sizeof(Ogre::Quaternion));
			pSerializer->readData(stream,&mXsegments,1,sizeof(int));
			pSerializer->readData(stream,&mYsegments,1,sizeof(int));
			pSerializer->readData(stream,&mYsegments_keep,1,sizeof(int));
			mLayer = 4;

			if (version >= 103)
			{
				pSerializer->readData(stream, &mIndex, 1, sizeof(mIndex));
			}

			return true;			
		}
		return false;		
	}
	bool SkyDomeActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;			
	}	
	std::size_t	SkyDomeActor::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void SkyDomeActor::updateRenderInstanceImpl(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void SkyDomeActor::updateRenderInstance(void)
	{
		
	}
	//-----------------------------------------------------------------------
	ActorFactory* SkyDomeActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	const String SkyBoxActor::msType = "SkyBox";
	const String SkyBoxActor::msCategory = "Enviroment";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class SkyBoxActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new SkyBoxActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// SkyBoxActor class
	//////////////////////////////////////////////////////////////////////////


	SkyBoxActor::SkyBoxActor(void)
		: Actor()
		, mMaterialName("BaseWhite")
		,mLayer(5)
		,mDistance(5000)
		,mDrawFirst(false)
		,mOrientation(Ogre::Quaternion::IDENTITY)
	{
		
	}
	//-----------------------------------------------------------------------
	SkyBoxActor::~SkyBoxActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& SkyBoxActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& SkyBoxActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void SkyBoxActor::createRenderInstance()
	{
		return;
		{
			mSceneManager = EngineManager::getSingleton().getSceneManager();

			updateRenderInstanceImpl();
		}
	}
	//-----------------------------------------------------------------------
	void SkyBoxActor::destroyRenderInstance(void)
	{
		
	}
	bool SkyBoxActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(pSerializer && stream->eof() == false )
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SceneSerializer::SFF_SKYBOX_OBJ)
			{

				pSerializer->skipChunk(stream);
				return false;
			}
			mMaterialName=pSerializer->readStringBin(stream);
			pSerializer->readData(stream,&mDistance,1,sizeof(Ogre::Real));	
			pSerializer->readData(stream,&mDrawFirst,1,sizeof(bool));
			mDrawFirst = false;
			pSerializer->readData(stream,&mOrientation,1,sizeof(Ogre::Quaternion));
			mLayer = 5;

			if (version >= 103)
			{
				pSerializer->readData(stream, &mIndex, 1, sizeof(mIndex));
			}

			return true;			
		}
		return false;			
	}
	bool SkyBoxActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;		
	}	
	std::size_t	SkyBoxActor::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void SkyBoxActor::updateRenderInstanceImpl(void)
	{
		mSceneManager->setSkyBox(true, mMaterialName, mDistance * 10);
	}
	//-----------------------------------------------------------------------
	void SkyBoxActor::updateRenderInstance(void)
	{
		
	}
	//-----------------------------------------------------------------------
	ActorFactory* SkyBoxActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

}
