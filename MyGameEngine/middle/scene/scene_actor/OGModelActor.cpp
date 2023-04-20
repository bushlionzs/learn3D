#include "OgreHeader.h"
#include "OGModelActor.h"
#include "OGActorFactory.h"
#include "OGActorProxy.h"
#include "scene_serializer.h"
#include "OgreDataStream.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OGModelComponent.h"

namespace Orphigine
{
	const String ModelActor::msType = "Model";
	const String ModelActor::msCategory = "Model";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class ModelActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new ModelActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// ModelActor class
	//////////////////////////////////////////////////////////////////////////


	ModelActor::ModelActor(void)
		: PlacementActor()
		, mProxy(NULL)
		, mModel(NULL)
		, mModelName()
		, mAnimationLevel(50)
		, mCastShadows(false)
		//, mSystem(NULL)
		, mTransparentTime(2.0f)
		, mTransparent(0)
		, mBEnableTransparent(true)
	{
		
	}
	//-----------------------------------------------------------------------
	ModelActor::~ModelActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& ModelActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& ModelActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void ModelActor::createRenderInstance()
	{
		PlacementActor::createRenderInstance();

		mProxy = new ActorProxy(shared_from_this());

		if (!mModelName.empty())
		{
			createModel();
		}
	}
	//-----------------------------------------------------------------------
	void ModelActor::destroyRenderInstance(void)
	{
		if (mModel)
		{
			destroyModel();
		}

		if (mProxy)
		{
			delete mProxy;
			mProxy = NULL;
		}

		PlacementActor::destroyRenderInstance();
	}
	bool ModelActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != SceneSerializer::SFF_MODEL_OBJ)
			{

				pSerializer->skipChunk(stream);
				return false;
			}
			//基类成员
			pSerializer->readData(stream,&mTransform,1,sizeof(mTransform));
			pSerializer->readData(stream,&mCreateLevel,1,sizeof(Ogre::Real));
			//自身成员
			String strModelName = pSerializer->readStringBin(stream);
			setModelName(strModelName);
			pSerializer->readData(stream,&mAnimationLevel,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mTransparent,1,sizeof(Ogre::Real));

			pSerializer->readData(stream,&mCastShadows,1,sizeof(bool));
			pSerializer->readData(stream,&mTransparentTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mBEnableTransparent,1,sizeof(bool));
			return true;			
		}
		return false;		
	}
	bool ModelActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;			
	}	
	std::size_t	ModelActor::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void ModelActor::setModelName(const String& modelName)
	{
		if (mModelName != modelName)
		{
			if (mModel)
			{
				destroyModel();
			}

			mModelName = modelName;

			if (mProxy && !mModelName.empty())
			{
				createModel();
			}
		}
	}
	//-----------------------------------------------------------------------
	void ModelActor::setAnimationLevel(Real level)
	{

	}
	//-----------------------------------------------------------------------
	void ModelActor::setCastShadows(bool castShadows)
	{
		
	}
	//-----------------------------------------------------------------------
	void ModelActor::createModel(void)
	{
		assert(!mModel);
		assert(mProxy && !mModelName.empty());

		Ogre::SceneNode* parent = getSceneNode();
		assert(parent);

		mModel = new Orphigine::ModelComponent(parent, mModelName, "khan");
		mModel->setUserObject(mProxy);

		mModel->setAnimationType(AT_FULL);
		mModel->setCastShadows(false);
		if (mTransparent > 0)
			mModel->updateTransparent(mTransparent);
	}
	//-----------------------------------------------------------------------
	void ModelActor::destroyModel(void)
	{

	}
	
	
	

	void  ModelActor::setTransparency( Real &newTrans )
	{
		
	}

	Real  ModelActor::getTransparency() const
	{
		return mTransparent;
	}

	//-----------------------------------------------------------------------
	ActorFactory* ModelActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

}
