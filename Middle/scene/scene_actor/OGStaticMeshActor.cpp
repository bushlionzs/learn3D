#include "OgreHeader.h"
#include "OGStaticMeshActor.h"
#include "OGActorFactory.h"
#include "OGActorProxy.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"
#include "OgreMeshManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "myutils.h"
#include "OgreStringConverter.h"
#include "OgreControllerManager.h"
#include "OgreAnimationState.h"

namespace Orphigine
{

	class AnimationControllerValue : public Ogre::ControllerValue<float>
	{
	private:
		AnimationState* mAnimationState;
	public:

		AnimationControllerValue(AnimationState* aniState)
		{
			mAnimationState = aniState;
		}

		float getValue(void) const
		{
			return 0;
		}

		void setValue(float value)
		{
			mAnimationState->addTime(value);
		}
	};

	const String StaticMeshActor::msType = "StaticEntity";
	const String StaticMeshActor::msCategory = "StaticObject";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class StaticMeshActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new StaticMeshActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// StaticMeshActor class
	//////////////////////////////////////////////////////////////////////////


	StaticMeshActor::StaticMeshActor(void)
		: PlacementActor()
		//, mSystem(NULL)
		, mProxy(nullptr)
		, mEntity(nullptr)
		, mMeshName()
		, mAnimationLevel(50)
		, mTransparency()
		, mCastShadows(false)
		, mReceiveShadows(false)
		, mReceiveDecals(false)
		, mEntityTransparentor(NULL)
		, mTransparentTime(1.0f)
		//, mExtraEffect(NULL)
		, mBEnableTransparent( true )
		,mHaveDestroyRenderInstanceFlag(false)
		,mHaveThreadLoadResFlag(false)
		//,mThreadLoadResRequest(NULL)
		,mIsCTMFlag(false)
		,mIsBatchMesh(false)
		,mUseLodMaterial(false)
	{
		mController = nullptr;
	}
	//-----------------------------------------------------------------------
	StaticMeshActor::~StaticMeshActor()
	{
		if (mController)
		{
			ControllerManager::getSingleton().destroyController(mController);
		}
	}
	void StaticMeshActor::setName(const String& name)
	{
		
	}
	//-----------------------------------------------------------------------
	const String& StaticMeshActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& StaticMeshActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::queryReferenceResources(ResourceCollection* resourceCollection)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::checkMaterialLod(Ogre::Vector3 & focusPos, float fogEndPos)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::queryBakableEntities(EntityList& entities)
	{
		
	}
	
	//-----------------------------------------------------------------------
	void StaticMeshActor::createRenderInstance()
	{
		return;
		auto mesh = MeshManager::getSingletonPtr()->load(mMeshName);

		if (!mesh)
		{
			WARNING_LOG("fail to load mesh:%s", mMeshName.c_str());
			return;
		}

		auto sub = mesh->getSubMesh(0);

		auto& mat = sub->getMaterial();

		if (!mat)
		{
			return;
		}

		mEntity = mSceneManager->createEntity(mName, mesh);

		auto root = mSceneManager->getRoot();

		SceneNode* node = root->createChildSceneNode(mName);
		node->attachObject(mEntity);
		node->setPosition(mTransform.mPosition);
		node->setOrientation(mTransform.mRotation);
		node->setScale(mTransform.mScale);

		auto animationState = mEntity->getAnimationState("[auto]");

		if (animationState)
		{
			//NOTICE_LOG("%s has animation", mMeshName.c_str());
			animationState->setEnabled(true);
			animationState->setLoop(true);
			auto aa = ControllerValueRealPtr(new AnimationControllerValue(animationState));
			mController = Ogre::ControllerManager::getSingleton().createFrameTimePassthroughController(
				aa);
		}
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::createRenderInstanceFromLoadThread()
	{
		      
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::destroyRenderInstanceFromLoadThread()
	{		
		
	}
	void StaticMeshActor::destroyRenderInstance(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::setMeshName(const String& meshName)
	{
		this->mMeshName = meshName;
	}
	bool StaticMeshActor::setIsCTMFlag(bool Flag)
	{
		mIsCTMFlag = Flag;
		return true;
	}
	bool StaticMeshActor::getIsCTMFlag() const 
	{
		return mIsCTMFlag;
	}
	bool StaticMeshActor::setWorldBoundingBox(const Ogre::AxisAlignedBox& aabb)
	{
		mAxisAlignedBox = aabb;
		return true;
	}
	const Ogre::AxisAlignedBox& StaticMeshActor::getWorldBoundingBox() const
	{
		return mAxisAlignedBox;
	}	
	bool StaticMeshActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{	
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != SceneSerializer::SFF_STATICENTITY_OBJ)
			{

				pSerializer->skipChunk(stream);
				return false;
			}
			//基类成员
			pSerializer->readData(stream,&mTransform,1,sizeof(mTransform));
			pSerializer->readData(stream,&mCreateLevel,1,sizeof(Ogre::Real));
			//自身成员
			String strMeshName = pSerializer->readStringBin(stream);

			stringToLower(strMeshName);
			setMeshName(strMeshName);

			
			pSerializer->readData(stream,&mAnimationLevel,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mTransparency,1,sizeof(Ogre::Real));

			pSerializer->readData(stream,&mCastShadows,1,sizeof(bool));
			pSerializer->readData(stream,&mReceiveShadows,1,sizeof(bool));
			pSerializer->readData(stream,&mReceiveDecals,1,sizeof(bool));
			pSerializer->readData(stream,&mIsCTMFlag,1,sizeof(bool));

			// 因为初始的代码是直接读写Ogre::AxisAlignedBox类对象，而sizeof(Ogre::AxisAlignedBox)
			// 是28个字节，其中，mMinimum占12个字节,mMaximum占12个字节,而mNull因为字节对齐的缘故,
			// 在后面追加了3个字节的废数据，共4个字节，改写成各个成员单独读写的话，需要写3个字节
			// 的废数据,这3个字节可以在场景文件升级时，去除掉 [dscky edit 2009/08/03]
			//pSerializer->readData(stream,&mAxisAlignedBox,1,sizeof(Ogre::AxisAlignedBox));
			Ogre::Vector3 AABBmin;
			Ogre::Vector3 AABBmax;
			bool  isNull = true;
			char temp[3] = { 0 , 0 };
			pSerializer->readData(stream,&AABBmin,1,sizeof(Ogre::Vector3));
			pSerializer->readData(stream,&AABBmax,1,sizeof(Ogre::Vector3));
			pSerializer->readData(stream,&isNull,1,sizeof(bool));
			pSerializer->readData(stream,temp,3,sizeof(char));
			mAxisAlignedBox.setMinimum(AABBmin);
			mAxisAlignedBox.setMaximum(AABBmax);
			if(isNull)
				mAxisAlignedBox.setNull();	
			pSerializer->readData(stream,&mTransparentTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mBEnableTransparent,1,sizeof(bool));
			if(mIsBatchMesh)
				mBEnableTransparent = false;

			if (version >= 102)
			{
				pSerializer->readData(stream, &mIsCameraCollision, 1, sizeof(bool));
				pSerializer->readData(stream, &mViewDistance, 1, sizeof(Ogre::Real));
			}

			return true;			
		}
		return false;		
	}
	bool StaticMeshActor::saveToBinaryFile(Serializer* pSerializer)
	{		
		
		return false;			
	}	
	std::size_t	StaticMeshActor::calcSerializedSize()
	{
		return 0;
	}		

	String StaticMeshActor::getPropertyAsString(const String& name) const
	{
		if (name == "bounding box" && mEntity)
		{
			const Ogre::AxisAlignedBox& aabb = mEntity->getBoundingBox();
			return Ogre::StringConverter::toString(aabb.getMinimum()) + ", " +
				Ogre::StringConverter::toString(aabb.getMaximum());
		}

		return PlacementActor::getPropertyAsString(name);
	}

	bool StaticMeshActor::getEntityWorldBoundingBox(Ogre::AxisAlignedBox& aabb) const
	{

		return false;
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::setAnimationLevel(Real level)
	{
		mAnimationLevel = level;
		updateAnimationType();
	}

	void StaticMeshActor::setInputTransparency( Real transparency )
	{
		
	}

	//-----------------------------------------------------------------------
	void StaticMeshActor::setTransparency(Real transparency)
	{
		

	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::setCastShadows(bool castShadows)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::setReceiveShadows(bool receiveShadows)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::setReceiveDecals(bool receiveDecals)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::createEntity(void)
	{
				
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::destroyEntity(void)
	{
					
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::updateAnimationType(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::setAutoAnimationState(bool play, bool loop)
	{
		
	}

	//-----------------------------------------------------------------------
	void StaticMeshActor::ResetAutoAnimation()
	{
				
	}

	std::pair<bool, Real> StaticMeshActor::queryIntersect(Ogre::Ray& ray)
	{
		return ray.intersects(mAxisAlignedBox);
	}

	//-----------------------------------------------------------------------
	void StaticMeshActor::updateNormaliseNormals(void)
	{

	}
	//-----------------------------------------------------------------------
	void StaticMeshActor::updateTransparency(void)
	{
		
	}
	
	
	//-----------------------------------------------------------------------
	ActorFactory* StaticMeshActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}
	
}
