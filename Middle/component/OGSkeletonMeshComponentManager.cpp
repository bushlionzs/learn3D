#include "OgreHeader.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGSkeletonMeshComponent.h"  
#include "OGUtils.h"
#include "OGSkeletonMeshActor.h"
#include "OGImpactManager.h"
#include <OgreSceneManager.h>
#include <platform_log.h>
#include <OgreStringConverter.h>
#include <OgreControllerManager.h>
#include <OgreController.h>
#include <OgreMaterialManager.h>
#include <OgreMeshManager.h>
#include <OgreSkeletonManager.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreEntity.h>
#include "OgreRoot.h"
#include <mbstring.h>
#include "OGSkeletonMeshComponentSerializer.h"
#include "OgreString.h"
#include "OgreAnimationState.h"
#include "myutils.h"
#include "engine_manager.h"
#include "OgrePredefinedControllers.h"
#include "OgreMemoryStream.h"

template<> Orphigine::SkeletonMeshComponentManager * Ogre::Singleton<Orphigine::SkeletonMeshComponentManager>::msSingleton = 0;

namespace
{
	class Orphigine::SkeletonMeshComponentManager;

	class SkeletonMeshComponentControllerValue : public Ogre::ControllerValue<float>
	{
	protected:
		Orphigine::SkeletonMeshComponentManager* mSkeletonMeshComponentMgr;

	public:
		SkeletonMeshComponentControllerValue(Orphigine::SkeletonMeshComponentManager* mgr)
			: mSkeletonMeshComponentMgr(mgr)
		{
		}

		float getValue(void) const
		{
			return 0.0f;
		}

		void setValue(float value)
		{
			mSkeletonMeshComponentMgr->updateAllLogicModel(value);
		}
	};
}

namespace Orphigine
{
	SkeletonMeshComponentManager::SkeletonMeshComponentManager( Orphigine::Engine *system ) :
	//mSystem(system),
	mAutoNamedModel(0),
		mShadowCastable(true),//更改默认值，与ogre内部的MovableObject中的mCastShadows值保持一致
		mCollisionManager(NULL),
		mTerrainCollider(NULL),
		mEnableWalkingEffect(true),
		mInterpolationMode(Ogre::Animation::IM_LINEAR),
		mAverageTime(0.03f)
	{
		mSkeletonMeshComponentTemplateMap.clear();

		mScriptPatterns.push_back("*.lmodel");

		_createController();
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponentManager::~SkeletonMeshComponentManager()
	{
		//clearDelayCreateLogicModelObject();

		_destroyController();

		destroyAllLogicModelTemplates();

		destroyAllLogicModels();

		_clearAnimationSkeletonLinks();

		_removeMaterialPool();

		_cleanupSkeletalEntityCache();

		unloadSkeletonCache();

		mAnimationSkeletonBackgroupLoadMap.clear();
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponentManager *SkeletonMeshComponentManager::getSingletonPtr(void)
	{
		return msSingleton;
	}
	//---------------------------------------------------------------------
	SkeletonMeshComponentManager & SkeletonMeshComponentManager::getSingleton(void)
	{  
		assert(msSingleton);  return ( *msSingleton);
	}
	//---------------------------------------------------------------------
	String SkeletonMeshComponentManager::getSuffix()
	{
		return ".lmodel";
	}	
	//-------------------------------------------------------------------	
	void SkeletonMeshComponentManager::loadSkeletonCache(Ogre::OStringSet &skeletonList)
	{
		Ogre::OStringSet::iterator iter;
		for (iter = skeletonList.begin(); iter != skeletonList.end(); iter++)
		{
			auto& skeletonName = *iter;
			{
				ResourcePtr res = Ogre::SkeletonManager::getSingleton().load(skeletonName.c_str());
				Ogre::SkeletonPtr skeleton = std::dynamic_pointer_cast<Ogre::Skeleton>(res);
				if (skeleton)
				{
					SkeletonCache::iterator it = mSkeletonCache.find(skeletonName.c_str());
					if (it == mSkeletonCache.end())
					{
						mSkeletonCache["skeletonName"] = skeleton;

						// 此处可能导致客户端占用内存增加一百多兆，所以注释掉
						//skeleton->setGCFlag(Ogre::Resource::GCF_NEVER);  // 预加载的角色动作，永远不被垃圾回收卸载
					}
				}
			}

		}
	}
	//-------------------------------------------------------------------	
	void SkeletonMeshComponentManager::unloadSkeletonCache()
	{
		mSkeletonCache.clear();
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_checkBackgroupLoadSkeleton(String &objectName, String &skeletonName, String &animName)
	{
		/*
		int nameNum = 4;
		char * names[] = {"站立", "步行", "跑步", "休闲"};
		*/
		int nameNum = 3;
		const char * names[] = {"站立", "步行", "跑步"};		

		AnimationSkeletonBackgroupLoadMap::iterator it;
		it = mAnimationSkeletonBackgroupLoadMap.find(objectName);
		if (it == mAnimationSkeletonBackgroupLoadMap.end())
		{
			Ogre::OStringSet skeletonNames;
			mAnimationSkeletonBackgroupLoadMap[objectName] = skeletonNames;
		}

		Ogre::OStringSet &skeletonNames = mAnimationSkeletonBackgroupLoadMap[objectName];

		for (int i=0; i<nameNum; i++) 
		{
			//除了名字中带有names中的几个关键字的不能跳过，其它的都不需要在后台装载
			if (strstr(animName.c_str(), names[i]))
			{
				skeletonNames.insert(skeletonName.c_str());
				break;
			}
		}

	}
	//---------------------------------------------------------------------	
	void SkeletonMeshComponentManager::parseScript(ResourceInfo* res, const Ogre::String& groupName)
	{		
		std::shared_ptr<DataStream> stream = std::make_shared<MemoryDataStream>(res);
		const Ogre::String& myname = stream->getName();


		//dscky edit 使用序列化来读写
		SkeletonMeshComponent *pSkeletonMeshComponent = OGRE_NEW SkeletonMeshComponent("");

		SkeletonMeshComponentSerializer serializer;
		if(Ogre::StringUtil::endsWith(stream->getName(),".lmodel",false))//旧的lmodel格式
		{
			SkeletonMeshComponentSerializer::skeletonAnimationsMapInfoStr skeletonanimationsMapInfo;
			if(!serializer.importSkeletonMeshComponentFromOldStream(stream,pSkeletonMeshComponent,&skeletonanimationsMapInfo))
			{
				OGRE_DELETE pSkeletonMeshComponent;
				return ;
			}
			//加载成功
			String skeletonMeshName = pSkeletonMeshComponent->getName();
			AnimationSkeletonLinks* links = _createAnimationSkeletonLinksForModel(skeletonMeshName);
			if(links)
			{ 
				std::map<std::string,std::string>::iterator itSkeletonAnimations = skeletonanimationsMapInfo.skeletonAnimationsMap.begin();
				while(itSkeletonAnimations != skeletonanimationsMapInfo.skeletonAnimationsMap.end())
				{
					String skeletonName = itSkeletonAnimations->first;
					Ogre::StringVector animationArray = Ogre::StringUtil::split(itSkeletonAnimations->second);
					assert (animationArray.size());
					for (size_t animationIndex = 0; animationIndex < animationArray.size(); ++animationIndex)
					{
						// 往link map中插入动作与骨骼名称的对应关系
						links->insert( AnimationSkeletonLinks::value_type( animationArray[animationIndex], skeletonName ) );
				
						_checkBackgroupLoadSkeleton(skeletonMeshName, skeletonName, animationArray[animationIndex]);
						//end
					}
					++itSkeletonAnimations;
				}			
			}						
		}
		else if(Ogre::StringUtil::endsWith(stream->getName(), ".smb", false))//新的smb格式
		{
			if(!serializer.importSkeletonMeshComponentFromStream(stream,pSkeletonMeshComponent))
			{
				OGRE_DELETE pSkeletonMeshComponent;
				return ;
			}			
		}
		//加载成功,保存到模板中
		String skeletonMeshName = pSkeletonMeshComponent->getName();
		Ogre::StringUtil::toLowerCase(skeletonMeshName);//文件名转换成小写
		std::pair<SkeletonMeshComponentMap::iterator, bool> inserted = 
			mSkeletonMeshComponentTemplateMap.insert( SkeletonMeshComponentMap::value_type(skeletonMeshName,pSkeletonMeshComponent));
		if (false == inserted.second)
		{
			OGRE_DELETE pSkeletonMeshComponent;
		}
		else
		{
			
		}	
        //dscky edit 使用序列化来读写
		/*
		Ogre::MemoryDataStream memStream(stream, true);
		_parseSingleObject(&memStream);
		*/
	}	
	//---------------------------------------------------------------------
	Ogre::Real SkeletonMeshComponentManager::getLoadingOrder(void) const
	{
		return 1000.0f;
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_parseFailed( SkeletonMeshComponent *model, const char *errorDesc )
	{
		if(model)
		{
			OGRE_DELETE model;
			model = NULL;
		}
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent* SkeletonMeshComponentManager::createLogicModel( const String& modelName,int type )

	{
		String autoName = "AutoNameModel_" + Ogre::StringConverter::toString(mAutoNamedModel++);

		return createLogicModel( autoName, modelName,type );
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent* SkeletonMeshComponentManager::createLogicModel(const String& name, const String& modelName,int type)
	{
		//Per_Profile("SkeletonMeshComponentManager::createLogicModel");

		if (mSkeletonMeshComponentMap.find(name) != mSkeletonMeshComponentMap.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"Logic Model with name '" + name + "' already exists.", 
				"SkeletonMeshComponentManager::createLogicModel");
		}
		const SkeletonMeshComponent* modelTemplate = getTemplateByName(modelName);//解析好的obj，只包含了属性，没有载入数据

		if (!modelTemplate)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Cannot find required actor Model template '" + modelName + "'",
				"SkeletonMeshComponentManager::createLogicModel");
		}

		SkeletonMeshComponent* newModel = OGRE_NEW SkeletonMeshComponent(modelName,type);

		// 先把指针记录下来，下面的任何操作如果抛出了异常，上面的new出来的指针才能被
		// 正确删除，因为它已经保存到map中了
		std::pair<SkeletonMeshComponentMap::iterator, bool> inserted = 
			mSkeletonMeshComponentMap.insert( SkeletonMeshComponentMap::value_type(name, newModel) );

		assert (inserted.second);

		*newModel = *modelTemplate;

		newModel->mSkeletonMeshType=type;

		unsigned long startTime = getMicroseconds();

		newModel->initModel();

		unsigned long endTime = getMicroseconds();
		float delta = (endTime-startTime)/1000.0f;

		//initModel所用的时间小于20ms才预加载skeleton
		if(delta < 20 )
		{			
			_loadLogicModelCommonlySkeleton(newModel, delta);
		}
		//end  

		// 设置默认的投影选项
		newModel->setShadowCastable(mShadowCastable);

		// 设置行走特效是否打开
		newModel->setEnableWalkingEffect(mEnableWalkingEffect);

		return newModel;	
	}	

	//-----------------------------------------------------------------------
	void SkeletonMeshComponentManager::destroyLogicModel(const String& name)
	{
		SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.find(name);

		if ( i != mSkeletonMeshComponentMap.end() )
		{
			ImpactManager::getSingleton().notifyLogicModelDestroyed(i->second);
			OGRE_DELETE i->second;
			i->second = NULL;

			mSkeletonMeshComponentMap.erase(i);
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponentManager::destroyLogicModel(SkeletonMeshComponent* model)
	{
		for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
			i != mSkeletonMeshComponentMap.end(); ++i )
		{
			if (i->second == model)
			{
		
				{
					ImpactManager::getSingleton().notifyLogicModelDestroyed(i->second);
				}
				

				{
					OGRE_DELETE i->second;
				}
				
				
				{
					i->second = NULL;
				}
				
			
				{

					mSkeletonMeshComponentMap.erase(i);
				}
				
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponentManager::destroyAllLogicModels(void)
	{
		for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
			i != mSkeletonMeshComponentMap.end(); ++i )
		{
			if (i->second)
			{
				ImpactManager::getSingleton().notifyLogicModelDestroyed(i->second);
				//end
				OGRE_DELETE i->second;
				i->second = NULL;
			}
		}
		mSkeletonMeshComponentMap.clear();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponentManager::destroyAllLogicModelTemplates(void)
	{
		for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentTemplateMap.begin();
			i != mSkeletonMeshComponentTemplateMap.end(); ++i )
		{
			if (i->second)
			{
				OGRE_DELETE i->second;
				i->second = NULL;
			}
		}
		mSkeletonMeshComponentTemplateMap.clear();
	}
	//-----------------------------------------------------------------------
	const SkeletonMeshComponent * SkeletonMeshComponentManager::getTemplateByName(const String& modelName)// const
	{
		// 把文件名统一转换成小写
		String tempStr = modelName;
		Ogre::StringUtil::toLowerCase(tempStr);
		SkeletonMeshComponentMap::const_iterator i = mSkeletonMeshComponentTemplateMap.find(tempStr);
		if (i != mSkeletonMeshComponentTemplateMap.end())
		{
			return i->second;
		}
		else
		{

			return nullptr;
		}
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent * SkeletonMeshComponentManager::getModelByName(const String& modelName)
	{
		SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.find(modelName);
		if (i != mSkeletonMeshComponentMap.end())
		{
			return i->second;
		}
		else
		{
			return NULL;
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_createController(void)
	{
		static Ogre::ControllerFunctionRealPtr gIdentityControllerFunction(new Ogre::ScaleControllerFunction(1.0f, false));
		Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
		mController = controllerManager.createController(
			controllerManager.getFrameTimeSource(),
			Ogre::ControllerValueRealPtr(new SkeletonMeshComponentControllerValue(this)),
			gIdentityControllerFunction);
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_destroyController(void)
	{
		if (mController)
		{
			Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
			controllerManager.destroyController(mController);
			mController = NULL;
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::updateAllLogicModel(Real time)
	{
#ifdef _ENABLE_TIME_LOG_
		unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();	
#endif
		//try
		{		
			const Real MAX_TIME_CAL = 0.5f;
			{
				//static Real lastAverageTime = 0.f; 

				Real timeSum = 0;
				DeltaTimeList::iterator iter;
				for (iter = mDeltaTimeList.begin(); iter != mDeltaTimeList.end(); iter++)
				{
					timeSum += *iter;
				} 

				size_t size = mDeltaTimeList.size();		
				if (size != 0)
					mAverageTime = (Real)timeSum / (Real) size;

				Real dt = time;


				mDeltaTimeList.push_back(time);
				size = mDeltaTimeList.size(); 

				int lastSize = size;

				int framenum = MAX_TIME_CAL * 1.f / mAverageTime;
				if (framenum > 300) framenum = 300;

				if ((int)size > framenum) 
				{
					Real decreaseNum =  size - framenum;
					decreaseNum *= 0.2f;

					while (decreaseNum > 0 && size > 1)
					{
						mDeltaTimeList.pop_front();
						size = mDeltaTimeList.size();
						decreaseNum -= 1;
					}
				}

				time = mAverageTime;
			}
			//end 

			for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
				i != mSkeletonMeshComponentMap.end(); ++i )
			{
				SkeletonMeshComponent* model = i->second; 

				assert (model);

				// 如果当前这个model是子model（武器），或挂在别的model上（骑乘上的人物），
				// 就不用execute，因为他们会在父model中的execute中被execute
				// !( model->isChildModel() || model->isAttached() ) == !(model->isChildModel()) && !(model->isAttached())
				if (model->isActive() && false == model->isChildModel() && false == model->isAttached())
				{
					model->execute(time);
				}
					
			}
		}		
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::setShadowCastable(bool castable)
	{
		if (mShadowCastable != castable)
		{
			mShadowCastable = castable;

			// 对当前所有活着的LogicModel都进行设置
			for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
				i != mSkeletonMeshComponentMap.end(); ++i )
			{
				SkeletonMeshComponent* model = i->second;

				assert (model);

				model->setShadowCastable(castable);
			}
		}        
	}
	//ConfigManager调用[15/1/2009 dscky add]
	bool SkeletonMeshComponentManager::addLogicModelShadowProjector()
	{
		// 对当前所有活着的LogicModel都进行设置
		for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
			i != mSkeletonMeshComponentMap.end(); ++i )
		{
			if(i->second && i->second->mHaveLogicModelShadow)
			i->second->addProjector(MPT_SHADOW,"shadow_projector",true,100.0f);
		}  
		return true;
	}
	bool SkeletonMeshComponentManager::removeLogicModelShadowProjector()
	{
		// 对当前所有活着的LogicModel都进行设置
		for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
			i != mSkeletonMeshComponentMap.end(); ++i )
		{
			SkeletonMeshComponent* model = i->second;
			assert (model);
			//判断是否主角相关，如果是主角相关的话，不移除
			if(model->mSkeletonMeshType == 0)
			{
				continue;
			}
			//保存mHaveLogicModelShadow用于下次重新设置脚下圈
			bool LogicModelShadowFlag = model->mHaveLogicModelShadow;
			model->removeProjector(MPT_SHADOW,"shadow_projector");
			model->mHaveLogicModelShadow=LogicModelShadowFlag;

		} 
		return true;
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::setEnableWalkingEffect(bool enable)
	{
		if (mEnableWalkingEffect != enable)
		{
			mEnableWalkingEffect = enable;

			// 对当前所有活着的LogicModel都进行设置
			for ( SkeletonMeshComponentMap::iterator i = mSkeletonMeshComponentMap.begin();
				i != mSkeletonMeshComponentMap.end(); ++i )
			{
				SkeletonMeshComponent* model = i->second;

				assert (model);

				model->setEnableWalkingEffect(enable);
			}
		}        
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::loadModelResource(const String& modelName, const String& groupName)
	{
		// 只有有一个为空就不进行创建
		if ( modelName.empty() || groupName.empty() )
			return;
		else
		{
			// 先获取model模板
			const SkeletonMeshComponent* modelTemplate = getTemplateByName(modelName);

			if (!modelTemplate)
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Cannot find required actor Model template '" + modelName + "'",
					"SkeletonMeshComponentManager::loadModelResource");
			}

			// 遍历entity列表并创建出相应的资源
			for ( SkeletonMeshComponent::EntityMap::const_iterator i = modelTemplate->mEntityMap.begin();
				i != modelTemplate->mEntityMap.end(); ++i )
			{
				const SkeletonMeshComponent::EntityValue& tempValue = i->second;

				String meshName = tempValue.mMeshName;
				String materialName = tempValue.mMaterialName;

				// 先load在obj文件中定义的material
				if (false == materialName.empty())
				{
					if (materialName.find(",") != String::npos)
					{
						Ogre::StringVector matNames = Ogre::StringUtil::split(materialName, ",");

						assert (matNames.size() > 1);

						for (size_t matNamesIndex = 0; matNamesIndex < matNames.size(); ++matNamesIndex)
						{
							const Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(matNames[matNamesIndex]);

							if (material)
								material->load();
						}
					}
					else
					{
						// 先检测是否有这个材质
						const Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(materialName);

						if (material)
							material->load();
					}
				}

				// 读取mesh和skeleton（如果有的话）
				if (false == meshName.empty())
				{
					Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(meshName);

					if (mesh)
					{
						// 如果在obj文件中没定义material，就在这里读取mesh自带的material
						if (materialName.empty())
						{
							unsigned short subMeshNum = mesh->getSubMeshCount();

							for (unsigned short subMeshIndex = 0;
								subMeshIndex < subMeshNum; ++subMeshIndex)
							{
								Ogre::SubMesh* subMesh = mesh->getSubMesh(subMeshIndex);

								assert (subMesh);

								const String& subMatName = subMesh->getMaterialName();

								const Ogre::MaterialPtr material = 
									Ogre::MaterialManager::getSingleton().getByName(subMatName);

								if (material)
									material->load();
							}
						}
					}                
				}			
			} // for each entity value

			// 读取locator上的model
			for ( SkeletonMeshComponent::LocatorMap::const_iterator itLocator = modelTemplate->mLocatorMap.begin();
				itLocator != modelTemplate->mLocatorMap.end(); ++itLocator )
			{
				const SkeletonMeshComponent::LocatorValue& tempValue = itLocator->second;

				for ( SkeletonMeshComponent::SlotMap::const_iterator itSlot = tempValue.mSlotMap.begin();
					itSlot != tempValue.mSlotMap.end(); ++itSlot )
				{
					const SkeletonMeshComponent::SlotValue& tempSlot = itSlot->second;

					loadModelResource(tempSlot.mModelName, groupName);
				}
			}
		}
	}
	//---------------------------------------------------------------------
	/*
	Ogre::CollisionManager* SkeletonMeshComponentManager::getCollisionManager(void)
	{
		if (NULL == mCollisionManager)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Cannot get CollisionManager,Plugin_Scorpio dll have been deleted",
				"SkeletonMeshComponentManager::getCollisionManager");
			return NULL;			
		}
		return mCollisionManager; 
	}
	//---------------------------------------------------------------------
	Ogre::UserCollider* SkeletonMeshComponentManager::getTerrainCollider(void)
	{
		if (NULL == mTerrainCollider)
		{
			// 顺便创建一个terrain collider
			//static TerrainCollider terrainCollider(gSystemPtr->getTerrainData(), 100);
			//mTerrainCollider = getCollisionManager()->createUserCollider(&terrainCollider);
		}

		return mTerrainCollider;        
	}
	//---------------------------------------------------------------------
	
	void SkeletonMeshComponentManager::_destroyTerrainCollider(void)
	{
		if (mTerrainCollider)
		{
			getCollisionManager()->destroyCollider(mTerrainCollider);
			mTerrainCollider = NULL;
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_destroyColliderManager(void)
	{		
		if (mCollisionManager)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Cannot destroy CollisionManager,Plugin_Scorpio dll have been deleted",
				"SkeletonMeshComponentManager::_destroyColliderManager");
			return ;			
		} 		
	}
	*/
	//---------------------------------------------------------------------
	SkeletonMeshComponentManager::AnimationSkeletonLinks* 
		SkeletonMeshComponentManager::_createAnimationSkeletonLinksForModel(const Ogre::String& modelName)
	{
		AnimationSkeletonLinksMap::iterator it =
			mAnimationSkeletonLinksMap.find(modelName);

		if (it != mAnimationSkeletonLinksMap.end())
		{
			return it->second;
		}
		else
		{
			AnimationSkeletonLinks* links = new AnimationSkeletonLinks;
			mAnimationSkeletonLinksMap.insert(AnimationSkeletonLinksMap::value_type(modelName, links));

			return links;
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_clearAnimationSkeletonLinks(void)
	{
		AnimationSkeletonLinksMap::iterator it =
			mAnimationSkeletonLinksMap.begin();

		while (it != mAnimationSkeletonLinksMap.end())
		{
			delete it->second;

			++it;
		}

		mAnimationSkeletonLinksMap.clear();
	}
	//---------------------------------------------------------------------
	const String& SkeletonMeshComponentManager::getSkeletonFromAnimationName(const String& modelName, const String& animName)
	{
		/// 先获取到所指定的模型的link map
		AnimationSkeletonLinksMap::iterator it =
			mAnimationSkeletonLinksMap.find(modelName);

		if (it == mAnimationSkeletonLinksMap.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
				"can't find the skeleton link map of the model '" + modelName + 
				"', get animation '" + animName + "' failed!",
				"SkeletonMeshComponentManager::_getSkeletonFromAnimationName");
		}

		AnimationSkeletonLinks* links = it->second;

		/// 在找出这个动作所对应的骨骼名称
		AnimationSkeletonLinks::const_iterator linksIt = 
			links->find(animName);

		if (linksIt == links->end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
				modelName + "can't find the skeleton link to the animation '" + 
				animName + ", get animation '" + animName + "' failed!",
				"SkeletonMeshComponentManager::_getSkeletonFromAnimationName"); 
		}

		return linksIt->second;
	}
	//---------------------------------------------------------------------
	SkeletonMeshComponentManager::AnimationSkeletonLinksIterator 
		SkeletonMeshComponentManager::getAnimationSkeletonLinksIterator(const String& modelName)
	{
		AnimationSkeletonLinksMap::iterator it =
			mAnimationSkeletonLinksMap.find(modelName);

		if ( it != mAnimationSkeletonLinksMap.end() )
		{
			AnimationSkeletonLinks* links = it->second;
			return AnimationSkeletonLinksIterator(links->begin(), links->end());
		}
		else
		{
			//return AnimationSkeletonLinksIterator(AnimationSkeletonLinks::iterator(0), AnimationSkeletonLinks::iterator(0));
			AnimationSkeletonLinks temp;
			return AnimationSkeletonLinksIterator(temp.end(), temp.end());
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::addToMaterialPool(MaterialHandle handle)
	{
		
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_removeMaterialPool(void)
	{
		
	}
	//---------------------------------------------------------------------
	Ogre::Entity* SkeletonMeshComponentManager::_createSkeletalEntity(const Ogre::SkeletonPtr& skeleton)
	{
		Ogre::Entity* entity;

		SkeletalEntityCache::iterator i =
			mSkeletalEntityCache.find(skeleton.get());
		if (i != mSkeletalEntityCache.end())
		{
			// Gather from cache
			entity = i->second;
			mSkeletalEntityCache.erase(i);

			// Should reset all animation states
			Ogre::AnimationStateSet* ass = entity->getAllAnimationStates();

			auto & easl = ass->getEnabledAnimationStates();

			auto it = easl.begin();
			while (it != easl.end())
			{
				Ogre::AnimationState* as = *it++;
				as->setEnabled(false);
			}
		}
		else
		{
			// Create null mesh first
			Ogre::MeshPtr mesh = createNullMeshForSkeleton(skeleton);

			// Create the entity
			static ulong gsCount = 0;
			//Ogre::StringConverter::toString(gsCount++, 4, '0')
			String id = Ogre::StringUtil::format("%s%.4d", mesh->getName().c_str(), gsCount++);

			auto sceneMgr = EngineManager::getSingletonPtr()->getSceneManager();
			entity = sceneMgr->createEntity(
				id,
				mesh->getName());
		}

		return entity;
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_destroySkeletalEntity(Ogre::Entity* entity)
	{
		const Ogre::MeshPtr& originMesh = entity->getMesh();
		const String& meshName = originMesh->getName();

		assert (originMesh);

		const Ogre::SkeletonPtr& originSke = originMesh->getSkeleton();
		const String& skeletonName = originSke->getName();

		assert (originSke);

		// Insert into cache
		//entity->destroy(); //todo123

		Ogre::MeshManager::getSingleton().remove(meshName);
		Ogre::SkeletonManager::getSingleton().remove(skeletonName);
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponentManager::_cleanupSkeletalEntityCache(void)
	{
		SkeletalEntityCache::iterator i, iend;
		iend = mSkeletalEntityCache.end();
		for (i = mSkeletalEntityCache.begin(); i != iend; ++i)
		{
			Ogre::Entity* entity = i->second;

			
			//entity->destroy(); todo123
		}
		mSkeletalEntityCache.clear();
	}	
	//-----------------------------------------------------------------------
	void SkeletonMeshComponentManager::_loadLogicModelCommonlySkeleton(SkeletonMeshComponent* model, int timeUsed)		
	{
		if (0 == model)
			return; 
		const String &name = model->getName();

		unsigned long startTime = getMicroseconds();

		AnimationSkeletonBackgroupLoadMap::iterator it;
		it = mAnimationSkeletonBackgroupLoadMap.find(name);
		if (it == mAnimationSkeletonBackgroupLoadMap.end())	
		{
			return;
		}

		Ogre::OStringSet &skeletonNames = mAnimationSkeletonBackgroupLoadMap[name];
		Ogre::OStringSet::iterator itSet;
		for (itSet = skeletonNames.begin(); itSet != skeletonNames.end(); itSet++)
		{
			auto &skelName = *itSet;
			model->loadSkeleton(skelName.c_str());
			//测试，写log，查看预加载骨骼的名称
			unsigned long time = (getMicroseconds() - startTime)/1000.0f + timeUsed;
			if (time > 30) //超过30ms就不再续继 
				break;
		}  
#ifdef _ENABLE_TIME_LOG_		
		unsigned long endTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
		size_t time = endTime-startTime;
		if( time > 10 ) 
		{
			char buf[1024];
			sprintf(buf, "_loadLogicModelCommonlySkeleton:前台装载skeleton耗时%d毫秒的logicmodel---%s, skeletonNum:%d\n", time, name.c_str(), skeletonNames.size());  
			OutputDebugString(buf);
		}
#endif
	}
	//-----------------------------------------------------------------------	
	void SkeletonMeshComponentManager::_filterSkeletonResource(const String &logicModelName, SkeletonMeshComponentManager::ResInfoVector &curResInfo)
	{
		AnimationSkeletonBackgroupLoadMap::iterator it;
		it = mAnimationSkeletonBackgroupLoadMap.find(logicModelName);
		if (it == mAnimationSkeletonBackgroupLoadMap.end())	
		{
			return;
		}

		SkeletonMeshComponentManager::ResInfoVector newResInfo;
		Ogre::OStringSet &skeletonNames = mAnimationSkeletonBackgroupLoadMap[logicModelName];

		Ogre::OStringSet::iterator itSet;
		SkeletonMeshComponentManager::ResInfoVector::iterator iter;
		for (iter = curResInfo.begin(); iter != curResInfo.end(); iter++)
		{
			auto &name = iter->ResName;
			int extPos = name.rfind('.');
			if (extPos > 0 && extPos <(int)name.size())
			{
				std::string ext = name.substr(extPos, name.size()).c_str();
				Ogre::StringUtil::toLowerCase(ext);
				if (ext == std::string(".skeleton")) 
				{
					itSet = skeletonNames.find(name.c_str());
					if (itSet != skeletonNames.end())
					{
						newResInfo.push_back(*iter);
					}
				}
				else 
				{
					newResInfo.push_back(*iter);
				}
			} 
			else 
			{
				newResInfo.push_back(*iter);
			}
		}		
		curResInfo = newResInfo;			
	}
	void SkeletonMeshComponentManager::_filterSkeletonRes(const String &logicModelName,  Ogre::OStringSet& curNoResName)
	{
		AnimationSkeletonBackgroupLoadMap::iterator it;
		it = mAnimationSkeletonBackgroupLoadMap.find(logicModelName);
		if (it == mAnimationSkeletonBackgroupLoadMap.end())	
		{
			return;
		}
		Ogre::OStringSet newResInfo;
		Ogre::OStringSet &skeletonNames = mAnimationSkeletonBackgroupLoadMap[logicModelName];

		Ogre::OStringSet::iterator itSet;
		Ogre::OStringSet::iterator iter;
		for (iter = curNoResName.begin(); iter != curNoResName.end(); iter++)
		{
			Ogre::String name((*iter).c_str());
			int extPos = name.rfind('.');
			if (extPos > 0 && extPos <(int)name.size())
			{
				std::string ext = name.substr(extPos, name.size());
				Ogre::StringUtil::toLowerCase(ext);
				if (ext == std::string(".skeleton")) 
				{
					itSet = skeletonNames.find(name.c_str());
					if (itSet != skeletonNames.end())
					{
						newResInfo.insert(*iter);
					}
				}
				else 
				{
					newResInfo.insert(*iter);
				}
			} 
			else 
			{
				newResInfo.insert(*iter);
			}
		}		
		curNoResName = newResInfo;
	}
	//end

	bool SkeletonMeshComponentManager::createDelayLogicModelObject(Ogre::String& lmName)
	{
		
		return false;		
	}	
}
