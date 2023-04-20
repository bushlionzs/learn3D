#ifndef OGStaticMeshActor_h__
#define OGStaticMeshActor_h__

#include "OGPlacementActor.h"
#include "OgreAxisAlignedBox.h"
#include "OgreController.h"

namespace Orphigine
{
	class ActorFactory;
	class ActorProxy;
	class EntityTransparentor;

	class  StaticMeshActor : public PlacementActor
	{
	protected:
		class Factory;

	public:
		StaticMeshActor(void);
		virtual ~StaticMeshActor();

		virtual const String& getType(void) const;
		virtual const String& getCategory(void) const;
		virtual void queryReferenceResources(ResourceCollection* resourceCollection);
		virtual void queryBakableEntities(EntityList& entities);
		virtual void createRenderInstance();
		virtual void createRenderInstanceFromLoadThread();
		virtual void destroyRenderInstance(void);
		virtual void destroyRenderInstanceFromLoadThread(void);
		virtual void setName(const String& name);
		virtual bool loadFromStream(
			Serializer* pSerializer, 
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		String getPropertyAsString(const String& name) const;

		void checkMaterialLod(Ogre::Vector3 & focusPos, float fogEndDist);

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);

		//////////////////////////////////////////////////////////////////////////



		const String& getMeshName(void) const
		{
			return mMeshName;
		}

		void setMeshName(const String& meshName);

		Real getAnimationLevel(void) const
		{
			return mAnimationLevel;
		}

		void setAnimationLevel(Real level);

		void setTransparency(Real transparency);
		void setInputTransparency( Real transparency );

		Real getTransparency(void) const
		{
			return mTransparency;
		}

		bool getCastShadows(void) const
		{
			return mCastShadows;
		}

		void setCastShadows(bool castShadows);

		bool getReceiveShadows(void) const
		{
			return mReceiveShadows;
		}

		void setReceiveShadows(bool receiveShadows);

		bool getReceiveDecals(void) const
		{
			return mReceiveDecals;
		}

		void setReceiveDecals(bool receiveDecals);

		//const String& getCurrentEffectName() const;
		//void setCurrentEffectName( const String &sEffectName, const NameValuePairList *pVarList );

		bool setIsCTMFlag(bool Flag);
		bool getIsCTMFlag() const;
		bool setWorldBoundingBox(const Ogre::AxisAlignedBox& aabb);
		const Ogre::AxisAlignedBox& getWorldBoundingBox() const;
		bool getEntityWorldBoundingBox(Ogre::AxisAlignedBox& aabb) const;

		void setAutoAnimationState(bool play, bool loop);
		void ResetAutoAnimation();

		virtual std::pair<bool, Real> queryIntersect(Ogre::Ray& ray);
	protected:

		Ogre::Real mAnimationLevel;
		Ogre::Real mTransparency;
		bool mCastShadows;
		bool mReceiveShadows;
		bool mReceiveDecals;
		bool mIsCTMFlag;	//是否行走面，用于提高优先级，默认为false
		bool mIsBatchMesh;	//是否是Batch Mesh
		Ogre::AxisAlignedBox			mAxisAlignedBox;				//如果是行走面的话，需要这个属性
		bool mIsCameraCollision;

		Real mViewDistance;

		ControllerReal* mController;
public:
		Real	mTransparentTime;
		bool	mBEnableTransparent;
	protected:
		//System* mSystem;
		ActorProxy* mProxy;
		Ogre::Entity* mEntity;
		Ogre::String mMeshName;
		Ogre::String	mMaterialEffectName;
		
		EntityTransparentor* mEntityTransparentor;
		bool mUseLodMaterial;
		void createEntity(void);
		void destroyEntity(void);
		void updateAnimationType(void);
		void updateTransparency(void);
		void updateNormaliseNormals(void);

	public:
		bool							mHaveDestroyRenderInstanceFlag;	//主线程是否删除RenderInstance的标志
		bool							mHaveThreadLoadResFlag;			//资源线程是否已经开始加载资源的标志
		//Ogre::RequestResourceObject*	mThreadLoadResRequest;			//后台线程执行的加载请求对象
		//dscky add 需要的cpu资源集合//////////////////////////////////////////////////////////////////////////////////
	};
	
}

#endif // OGStaticMeshActor_h__