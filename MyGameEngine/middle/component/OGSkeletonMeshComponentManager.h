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

		/// �����붯��֮��Ĺ���map��keyΪ�������ƣ�valueΪ������������Ĺ����ļ�����
		typedef std::unordered_map<String, String> AnimationSkeletonLinks;
		/// keyΪlogic model�����ƣ��� Ů����.obj
		typedef std::unordered_map<String, AnimationSkeletonLinks* > AnimationSkeletonLinksMap;

		/// keyΪlogic model�����ƣ��� Ů����.obj,valueΪ��Ҫ�ں�̨���ص�skeleton
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

		/// ɾ�������Ѿ�����������LogicModel
		void destroyAllLogicModels(void);

		/// ɾ������LogicModel template
		void destroyAllLogicModelTemplates(void);

		/// enable dynamic load template 
		const SkeletonMeshComponent * getTemplateByName(const String& modelName);// const;

		SkeletonMeshComponent * getModelByName(const String& modelName);	

		void updateAllLogicModel(Real time);

		/// ����ȫ�ֵ��Ƿ����ͶӰ
		void setShadowCastable(bool castable);
		bool getShadowCastable(void)
		{
			return mShadowCastable;
		}
		//ConfigManager����[15/1/2009 dscky add]
		bool addLogicModelShadowProjector();
		bool removeLogicModelShadowProjector();
		/// ����ȫ�ֵ�������Ч����
		void setEnableWalkingEffect(bool enable);
		bool getEnableWalkingEffect(void)
		{
			return mEnableWalkingEffect;
		}

		/** ��ȡָ��obj����Դ
		@param modelName Ҫ��ȡ��obj����
		@param groupName ���ĸ���Դ���ж�ȡ��Դ�����û���ṩ�����Զ������Դ��
		@remarks ������������������ش���Logic Model��ʵ����ֻ�ǰ�
		obj���õ���mesh����ͼ��skeleton����Դ����ȡ����
		*/
		void loadModelResource(const String& modelName, 
			const String& groupName = "Bootstrap");

		Ogre::CollisionManager* getCollisionManager(void);

		Ogre::UserCollider* getTerrainCollider(void);

		const String& getSkeletonFromAnimationName(const String& modelName, const String& animName);

		/// ��ȡ��ָ����ģ�͵Ķ������Ƶ�����
		typedef Ogre::ConstMapIterator<AnimationSkeletonLinks> AnimationSkeletonLinksIterator;
		AnimationSkeletonLinksIterator getAnimationSkeletonLinksIterator(const String& modelName);

		//����.skeleton�Ͷ����ӿ� by changhao
		typedef Ogre::MapIterator<AnimationSkeletonLinksMap> SkeletonLinkIterator;
		SkeletonLinkIterator getSkeletonLinkIterator(void)
		{
			return SkeletonLinkIterator(mAnimationSkeletonLinksMap.begin(), mAnimationSkeletonLinksMap.end());
		}

		/// modelģ�������
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

		//dscky add �ӳټ���///////////////////////////////////////////
		//��̨�̴߳����ӳټ��ص�LogicModel
		bool createDelayLogicModelObject(Ogre::String& lmName);
		//dscky add �ӳټ���///////////////////////////////////////////		
	protected:

		void _parseFailed( SkeletonMeshComponent *model, const char *errorDesc );

		void _createController(void);

		void _destroyController(void);

		/// ɾ�����õ�terrain collider
		//void _destroyTerrainCollider(void);

		///// ɾ��collider manager
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

		/// �Ƿ����ͶӰ
		bool mShadowCastable;

		/// �Ƿ��������Ч
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