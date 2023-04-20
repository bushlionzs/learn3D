#ifndef OGSkeletonMeshComponentManager_h__
#define OGSkeletonMeshComponentManager_h__


#include <OgreSingleton.h>
#include <OgreDataStream.h>
#include <OgreIteratorWrapper.h>
#include <OgreAnimation.h>
#include <OgreMaterial.h>
#include <ogreskeleton.h>
#include "OgreCpuResource.h"
#include "OgreController.h"
#include "OgreScriptLoader.h"
namespace Ogre  {

	class CollisionManager;
	class UserCollider;
};

class TiXmlNode;

namespace Orphigine	{

	class Engine;
	class GroundInfo;
	class SkeletonMeshComponent;
	class TerrainCollider;  
	class SkeletonMeshActor;


	class _OrphigineExport SkeletonMeshComponentManager : public Ogre::ScriptLoader, public Ogre::Singleton<SkeletonMeshComponentManager>
	{

		typedef std::vector<Ogre::CpuResource::ResArchiveInfoStr> ResInfoVector;
		struct LModelHeader
		{

			LModelHeader()
			{
				mFOUCC = 0;
				mVer = 0;
			}
			void init()
			{
				mFOUCC = 'LMOD';
				mVer = 100;
				mInfo = "Copyright (c) 2009 Beijing Kylin Network Information Science and Technology Co, Ltd. All Rights Reserved.";
			}
			bool isValid() 
			{
				if (mFOUCC != 'LMOD')
					return false;
				return true;
			}
			int mFOUCC;
			int mVer;
			String mInfo;
		};
	public:

		typedef std::unordered_map<Ogre::String, SkeletonMeshComponent*> SkeletonMeshComponentMap;

		/// 骨骼与动作之间的关联map，key为动作名称，value为包含这个动作的骨骼文件名称
		typedef std::unordered_map<String, String> AnimationSkeletonLinks;
		/// key为logic model的名称，如 女主角.obj
		typedef std::unordered_map<String, AnimationSkeletonLinks* > AnimationSkeletonLinksMap;

		/// key为logic model的名称，如 女主角.obj,value为需要在后台加载的skeleton
		typedef std::unordered_map<String, Ogre::OStringSet > AnimationSkeletonBackgroupLoadMap;

		typedef unsigned long MaterialHandle;
		typedef std::list<MaterialHandle > MaterialPool;

		struct MaterialCache
		{
			MaterialCache(const Ogre::MaterialPtr& mat, MaterialPool::iterator it)
				: mMaterial(mat)
				, mPoolIterator(it)
			{
			}

			Ogre::MaterialPtr mMaterial;
			MaterialPool::iterator mPoolIterator;
		};

		typedef std::unordered_map<MaterialHandle, MaterialCache> MaterialCaches;

	public:

		SkeletonMeshComponentManager( Orphigine::Engine *system );
		~SkeletonMeshComponentManager();

		/// @copydoc ScriptLoader::getScriptPatterns
		virtual String getSuffix();
		/// @copydoc ScriptLoader::parseScript
		void parseScript(Ogre::DataStreamPtr& stream, const Ogre::String& groupName);
		/// @copydoc ScriptLoader::getLoadingOrder
		Ogre::Real getLoadingOrder(void) const;

		static SkeletonMeshComponentManager& getSingleton(void);       
		static SkeletonMeshComponentManager* getSingletonPtr(void);	

		SkeletonMeshComponent* createLogicModel(const String& modelName,int type=4);

		SkeletonMeshComponent* createLogicModel(const String& name,const String& modelName,int type=4);

		void destroyLogicModel(const String& name);
		void destroyLogicModel(SkeletonMeshComponent* model);

		/// 删除所有已经创建出来的LogicModel
		void destroyAllLogicModels(void);

		/// 删除所有LogicModel template
		void destroyAllLogicModelTemplates(void);

		/// enable dynamic load template 
		const SkeletonMeshComponent * getTemplateByName(const String& modelName);// const;

		SkeletonMeshComponent * getModelByName(const String& modelName);	

		void updateAllLogicModel(Real time);

		/// 设置全局的是否可以投影
		void setShadowCastable(bool castable);
		bool getShadowCastable(void)
		{
			return mShadowCastable;
		}
		//ConfigManager调用[15/1/2009 dscky add]
		bool addLogicModelShadowProjector();
		bool removeLogicModelShadowProjector();
		/// 设置全局的行走特效开关
		void setEnableWalkingEffect(bool enable);
		bool getEnableWalkingEffect(void)
		{
			return mEnableWalkingEffect;
		}

		/** 读取指定obj的资源
		@param modelName 要读取的obj名称
		@param groupName 在哪个资源组中读取资源，如果没有提供，就自动检测资源组
		@remarks 这个操作并不会真正地创建Logic Model的实例，只是把
		obj所用到的mesh，贴图，skeleton等资源都读取进来
		*/
		void loadModelResource(const String& modelName, 
			const String& groupName = "Bootstrap");

		Ogre::CollisionManager* getCollisionManager(void);

		Ogre::UserCollider* getTerrainCollider(void);

		const String& getSkeletonFromAnimationName(const String& modelName, const String& animName);

		/// 获取所指定的模型的动作名称迭代器
		typedef Ogre::ConstMapIterator<AnimationSkeletonLinks> AnimationSkeletonLinksIterator;
		AnimationSkeletonLinksIterator getAnimationSkeletonLinksIterator(const String& modelName);

		//返回.skeleton和动作接口 by changhao
		typedef Ogre::MapIterator<AnimationSkeletonLinksMap> SkeletonLinkIterator;
		SkeletonLinkIterator getSkeletonLinkIterator(void)
		{
			return SkeletonLinkIterator(mAnimationSkeletonLinksMap.begin(), mAnimationSkeletonLinksMap.end());
		}

		/// model模板迭代器
		typedef Ogre::MapIterator<SkeletonMeshComponentMap> LogicModelTemplateIterator;
		LogicModelTemplateIterator getLogicModelTemplateIterator(void)
		{
			return LogicModelTemplateIterator(
				mSkeletonMeshComponentTemplateMap.begin(), mSkeletonMeshComponentTemplateMap.end());
		}
		typedef Ogre::MapIterator<SkeletonMeshComponentMap> LogicModelIterator;
		LogicModelIterator getLogicModelIterator(void)
		{
			return LogicModelIterator(
				mSkeletonMeshComponentMap.begin(), mSkeletonMeshComponentMap.end());
		}
		void _clearAnimationSkeletonLinks(void);

		void setAnimationInterpolationMode(Ogre::Animation::InterpolationMode mode)
		{
			mInterpolationMode = mode;
		}
		Ogre::Animation::InterpolationMode getAnimationInterpolationMode(void)
		{
			return mInterpolationMode;
		}

		void addToMaterialPool(MaterialHandle handle);

		Ogre::Entity* _createSkeletalEntity(const Ogre::SkeletonPtr& skeleton);
		void _destroySkeletalEntity(Ogre::Entity* entity);
		void _cleanupSkeletalEntityCache(void);

		//dscky add 延迟加载///////////////////////////////////////////
		//后台线程创建延迟加载的LogicModel
		bool createDelayLogicModelObject(Ogre::String& lmName);
		//dscky add 延迟加载///////////////////////////////////////////		
	protected:

		void _parseFailed( SkeletonMeshComponent *model, const char *errorDesc );

		void _createController(void);

		void _destroyController(void);

		/// 删除公用的terrain collider
		//void _destroyTerrainCollider(void);

		///// 删除collider manager
		//void _destroyColliderManager(void);

		AnimationSkeletonLinks* _createAnimationSkeletonLinksForModel(const Ogre::String& modelName);
	

		void _removeMaterialPool(void);	
		void _filterSkeletonResource(const String &logicModelName, ResInfoVector& curResInfo);
		void _filterSkeletonRes(const String &logicModelName, Ogre::OStringSet& curNoResName);
		void _checkBackgroupLoadSkeleton(String &objectName, String &skeletonName, String &animName);
		void _loadLogicModelCommonlySkeleton(SkeletonMeshComponent* model, int timeUsed);
		//end

	public:
		void loadSkeletonCache(Ogre::OStringSet& skeletonList);
		void unloadSkeletonCache();
		//end
	public:
		//SkeletonMeshComponent* _parseSingleLModel(Ogre::MemoryDataStream * stream);
	protected:

		AnimationSkeletonLinksMap mAnimationSkeletonLinksMap;

		AnimationSkeletonBackgroupLoadMap mAnimationSkeletonBackgroupLoadMap;
		//end

		Ogre::StringVector mScriptPatterns;

		//Orphigine::System *mSystem;

		SkeletonMeshComponentMap mSkeletonMeshComponentTemplateMap;
		SkeletonMeshComponentMap mSkeletonMeshComponentMap;

		ulong mAutoNamedModel;

		Ogre::Controller<Real>* mController;

		/// 是否可以投影
		bool mShadowCastable;

		/// 是否打开行走特效
		bool mEnableWalkingEffect;

		Ogre::CollisionManager* mCollisionManager;
		Ogre::UserCollider* mTerrainCollider;

		Ogre::Animation::InterpolationMode mInterpolationMode;

		MaterialPool mMaterialPool;
		MaterialCaches mMaterialCaches;

		typedef std::multimap<Ogre::Skeleton*, Ogre::Entity*> SkeletalEntityCache;

		SkeletalEntityCache mSkeletalEntityCache;

		typedef std::deque<Real >  DeltaTimeList;

		DeltaTimeList	mDeltaTimeList;
		Real               mAverageTime;
		//end

		typedef std::unordered_map<String, Ogre::SkeletonPtr > SkeletonCache;
		SkeletonCache mSkeletonCache;
		//end

	};

};

#endif // OGSkeletonMeshComponentManager_h__