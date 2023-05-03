#include "OgreHeader.h"
#include "OGSkeletonMeshComponent.h"
#include "OGImpactManager.h"
#include "OGImpact.h"
#include "OGImpactModuleFactory.h"
#include "OGImpactModule.h"
#include "OGSpell.h"
#include "OGSpellRibandModule.h"
#include "OGSpellImpactModule.h"
#include "OGSpellBulletFlowModule.h"
#include "OGSpellSoundModule.h"
#include "OGSpellSceneLightModule.h"
#include "OGMainSceneLight.h"
#include "OGSpellModelModule.h"
#include "OGImpactParticleModule.h"
#include "OGFlags.h"
#include "OgreMemoryStream.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreString.h>
#include <OgreStringConverter.h>
#include <OgreControllerManager.h>
#include <OgreController.h>
#include <OgreParticleSystemManager.h>
#include <OgreMaterialManager.h>
#include <OgreParticleAffector.h>
#include <OgreParticleSystemRenderer.h>
#include <OgreParticleEmitter.h>
#include "OGImpactSerializer.h"

#include "OgreRoot.h"
#include "engine_manager.h"
//#include "OgreTimer.h"


template<> Orphigine::ImpactManager * Ogre::Singleton<Orphigine::ImpactManager>::msSingleton = 0;

namespace Orphigine
{

#define CLEAR_EFFECT_CACHE_TIME 15.0f

	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class Orphigine::ImpactManager;

		class EffectControllerValue : public Ogre::ControllerValue<float>
		{
		protected:
			ImpactManager *mEffectMgr;

		public:

			EffectControllerValue(ImpactManager *effectMgr)
				: mEffectMgr(effectMgr)
			{
			}

			float getValue(void) const
			{
				return 0;
			}

			void setValue(float value)

			{
#ifdef _ENABLE_TIME_LOG_
				unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();				
#endif

				mEffectMgr->updateActiveEffects(value);
				mEffectMgr->updateEffectFreeListCache(value);
				// 更新特效灯光
				//mEffectMgr->getMainSceneLight()->updateLight(value);


			}
		};
	}

	//////////////////////////////////////////////////////////////////////////

	ImpactManager *ImpactManager::getSingletonPtr(void)
	{
		return msSingleton;
	}
	//---------------------------------------------------------------------
	ImpactManager & ImpactManager::getSingleton(void)
	{  
		assert(msSingleton);  return ( *msSingleton);
	}
	//---------------------------------------------------------------------
	ImpactManager::ImpactManager()	:
	mController(NULL),
		mMaxNumFreeEffectPerList(10),
		mMainSceneLight(NULL),
		mEffectLevel(EL_HIGH)//,
	{
		mScriptPatterns.push_back("*.skb");
		mScriptPatterns.push_back("*.efb");

		mActiveEffectList.clear();
		mFreeEffectMap.clear();
		mEffectTemplateMap.clear();
		mEffectTemplateScriptFileMap.clear();
		mLoadedScripts.clear();

		Impact::registerEffectElementFactory();
		createController();


		for (int i=0; i<EFFECT_PRIORITY_NUM; i++)
			mEnablePriority[i] = true;		
		mEffectMaxNum = 200;


	}
	//---------------------------------------------------------------------
	ImpactManager::~ImpactManager()
	{

		// 删除Effect map
		for ( ActiveEffectList::iterator i = mActiveEffectList.begin();
			i != mActiveEffectList.end();	++i	)
		{
			if (*i)
			{
				OGRE_DELETE *i;
				*i = NULL;
			}
		}
		mActiveEffectList.clear();


		mActiveLogicModelEffectList.clear();
		mLogicModelEffectReqList.clear();


		clearAllFreeEffects();

		_destroyEffectTemplates();

		Impact::unregisterEffectElementFactory();

		// 删除skill map
		for ( SkillMap::iterator i = mSkillTemplateMap.begin();
			i != mSkillTemplateMap.end();	++i )
		{
			if (i->second)
			{				
				delete i->second;
				i->second = NULL;
			}
		}
		mSkillTemplateMap.clear();

		if (mController)
		{
			Ogre::ControllerManager &controllerManager = Ogre::ControllerManager::getSingleton();
			controllerManager.destroyController(mController);
			mController = NULL;
		}
	}
	//---------------------------------------------------------------------
	String ImpactManager::getSuffix(void)
	{
		return ".efb";
	}
	//---------------------------------------------------------------------
	void ImpactManager::parseScript(ResourceInfo* res, const String& groupName)
	{
		std::shared_ptr<DataStream> stream = std::make_shared<MemoryDataStream>(res);
		//当前解析的文件名称
		const String& parsingFileName = stream->getName();
		if(Ogre::StringUtil::endsWith(parsingFileName,".skb",false))
		{
			SpellsSerializer tmpSerializer;
			tmpSerializer.importSkillFromStream(stream,NULL);
		}		
		else if (Ogre::StringUtil::endsWith(parsingFileName, ".efb", false) )
		{
			ImpactSerializer serializer;
			Impact* pEffect = OGRE_NEW Impact("");
			serializer.importEffectFromStream(stream,pEffect);
			//解析完的后续工作	
			//注册
			std::map<String,Ogre::ParticleSystem*>::iterator itPSName = pEffect->mParticleSystemTemplateNameMap.begin();
			while(itPSName!=pEffect->mParticleSystemTemplateNameMap.end())
			{
				Ogre::ParticleSystemManager::getSingleton().addTemplate(itPSName->first,itPSName->second);
				itPSName->second=NULL;
				++itPSName;
			}
			pEffect->mParticleSystemTemplateNameMap.clear();
			//effect
			addEffectTemplate(pEffect,pEffect->getTemplateName());
			addToEffectTemplateScriptFileMap(pEffect->getTemplateName(),stream->getName());

		}
		else
		{
			// 异常
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
				"wrong file name " + parsingFileName, "EffectManager::parseScript");
		}		
	}	
	//---------------------------------------------------------------------
	float ImpactManager::getLoadingOrder(void) const
	{
		return 1000.0f;
	}	
	//---------------------------------------------------------------------
	Impact * ImpactManager::createEffectTemplate(const String &name)
	{
		String sLowerName = name;
		Ogre::StringUtil::toLowerCase( sLowerName );
		Impact *ret = NULL;
		EffectTemplateMap::iterator i = mEffectTemplateMap.find(sLowerName);
		if (i == mEffectTemplateMap.end())
		{
			//assert (gSystemPtr);
			ret = OGRE_NEW Impact(sLowerName);
			assert (ret);

			mEffectTemplateMap[sLowerName] = ret;//effect名字和对象指针的map

			DECLARE_SCRIPT_RESOURCE( sLowerName );
		}
		else
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"Effect template with name '" + name + "' already exists!",
				"EffectManager::createEffectTemplate");
		}

		return ret;
	}
	bool ImpactManager::addEffectTemplate(Impact *pEffect,const String& templateName)
	{
		if(pEffect && !templateName.empty())
		{
			String sLowerName = templateName;
			Ogre::StringUtil::toLowerCase( sLowerName );
			EffectTemplateMap::iterator i = mEffectTemplateMap.find(sLowerName);
			if (i == mEffectTemplateMap.end())
			{
				pEffect->setTemplateName(sLowerName);
				mEffectTemplateMap[sLowerName] = pEffect;//effect名字和对象指针的map
				DECLARE_SCRIPT_RESOURCE( sLowerName );
			}
			else
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
					"Effect template with name '" + templateName + "' already exists!",
					"EffectManager::addEffectTemplate");
			}
			return true;
		}
		return false;
	}
	//---------------------------------------------------------------------
	Spell * ImpactManager::createSkillTemplate(const String &name)
	{
		String sLowerName = name;
		Ogre::StringUtil::toLowerCase( sLowerName );
		Spell *ret = NULL;
		SkillMap::iterator i = mSkillTemplateMap.find(sLowerName);
		if (i == mSkillTemplateMap.end())
		{
			ret = new Spell(sLowerName);
			assert (ret);

			mSkillTemplateMap[sLowerName] = ret;

			DECLARE_SCRIPT_RESOURCE( sLowerName );
		}
		else
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"skill template with name '" + name + "' already exists!",
				"EffectManager::createSkillTemplate");
		}

		return ret;
	}
	//---------------------------------------------------------------------
	void ImpactManager::dump(const String &fileName)
	{
		
	}
	bool ImpactManager::outputEffectInfo(std::ofstream& outfileName)
	{
		outfileName << "//////////////Effect Res Info Start/////////////////////" << std::endl;
		int Index=0;
		for ( ActiveEffectList::iterator it = mActiveEffectList.begin(); it != mActiveEffectList.end(); ++it )
		{
			Impact* pEffect =*it;
			if(pEffect)
			{
				outfileName << " Index= " << Ogre::StringConverter::toString(Index) << " EffectName :" << pEffect->getTemplateName() << std::endl;
				++Index;
			}				
		}		
		outfileName << "///////////////Effect Res Info End/////////////////////" << std::endl;
		return true;
	}
	//---------------------------------------------------------------------
	Impact* ImpactManager::addEffect(const String& effectTemplateName)
	{
		//Per_Profile("EffectManager::addEffect");
		String sLowerTemplate = effectTemplateName;
		Ogre::StringUtil::toLowerCase( sLowerTemplate );
		Impact *newEffect = NULL;
		newEffect = getFromFreeMap(sLowerTemplate);

		if ( NULL == newEffect )
		{		
			// Look up template
			Impact *pTemplate = getTemplate(sLowerTemplate);
			if (!pTemplate)
			{	
				WARNING_LOG("Cannot find required Etemplate:%s", sLowerTemplate.c_str());
				return nullptr;

			}			

			newEffect = OGRE_NEW Impact(effectTemplateName);			

			// 复制参数，包括创建父子节点的连接关系
			*newEffect = *pTemplate;

			//		newEffect->createSceneNode();
		}	

		assert (newEffect);

		mActiveEffectList.push_back(newEffect);

		return newEffect;
	}
	//---------------------------------------------------------------------
	Spell *ImpactManager::getSkillTemplate( const String &skillName )
	{
		SkillMap::iterator i = mSkillTemplateMap.find(skillName);

		if ( i != mSkillTemplateMap.end() )
		{
			return i->second;
		}
		else
		{
			//CHECK_RES_AND_PARSE( skillName, this );
			//i = mSkillTemplateMap.find(skillName);
			//if ( i != mSkillTemplateMap.end() )
			//{
			//	return i->second;
			//}
			//else
			return NULL;
		}
	}
	//-----------------------------------------------------------------------
	Impact * ImpactManager::getTemplate(const String& name)
	{
		String sLowerTemplate = name;
		Ogre::StringUtil::toLowerCase( sLowerTemplate );
		EffectTemplateMap::iterator i = mEffectTemplateMap.find(sLowerTemplate);
		if (i != mEffectTemplateMap.end())
		{
			return i->second;
		}
		else
		{
			i = mEffectTemplateMap.find(sLowerTemplate);
			if (i != mEffectTemplateMap.end())
			{
				return i->second;
			}
			else
				return NULL;

			return NULL;
		}
	}
	//---------------------------------------------------------------------
	ImpactManager::ActiveEffectList::iterator ImpactManager::destroyEffect( Impact *effect )
	{
		assert (effect);

		ActiveEffectList::iterator i = mActiveEffectList.begin();

		while ( i != mActiveEffectList.end() )
		{
			if (*i == effect)
			{

				this->_removeLogicModelEffect(effect);
	

				OGRE_DELETE *i;
				*i = NULL;
				i = mActiveEffectList.erase(i);
				break;
			}

			++i;
		}

		return i;
	}
	//---------------------------------------------------------------------
	void ImpactManager::removeEffect( Impact *effect, bool removeParentNode, bool removeNow )
	{
		try
		{
			assert (effect);

			effect->setRemoveParentNode(removeParentNode);

			if (removeNow)
			{
				for ( ActiveEffectList::iterator i = mActiveEffectList.begin();
					i != mActiveEffectList.end(); ++i )
				{
					if (*i == effect)
					{
						/// 让所有的特效元素先睡眠
						effect->removeAllElements();

						if (effect->getRemoveParentNode())
						{
							effect->removeParentSceneNode();
						}

						addToFreeEffectMap(effect);
						mActiveEffectList.erase(i);
						break;
					}
				}
			}
			else
			{
				// 关闭特效（例如关闭粒子发生器等操作）
				effect->shutdown();
				effect->setDelayRemove(true);
			}
		}
		catch( const std::exception& e )
		{
			Ogre::String strCPPException = e.what();
			Ogre::String Msg = "EffectManager removeEffect Failed:" + strCPPException + "--EffectManager::removeEffect";
			throw;
		}
		catch(...) 
		{
			//WARNING_LOG("EffectManager removeEffect Failed.--EffectManager::removeEffect");
			throw;
		}
	}
	//---------------------------------------------------------------------
	Impact * ImpactManager::getFromFreeMap( const String &templateName )
	{
		FreeEffectMap::iterator i = mFreeEffectMap.find(templateName);

		if ( i != mFreeEffectMap.end() )
		{
			ImpactFreeListCache* freeListCache = i->second;

			freeListCache->resetLifeTime();

			ImpactFreeListCache::FreeImpactList *list = &freeListCache->mEffectFreeList;

			if (list->size() > 0 )
			{
				Impact *freeEffect = *(list->begin());
				list->erase( list->begin() );

				freeEffect->reborn();
				return freeEffect;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	//---------------------------------------------------------------------
	void ImpactManager::addToFreeEffectMap( Impact *effect )
	{

		this->_removeLogicModelEffect(effect);

		assert (effect);

		String templateName = effect->getTemplateName();
		Ogre::StringUtil::toLowerCase( templateName ); 

		FreeEffectMap::iterator i = mFreeEffectMap.find(templateName);

		if ( i != mFreeEffectMap.end() )
		{
			ImpactFreeListCache* freeListCache = i->second; 

			freeListCache->resetLifeTime();

			ImpactFreeListCache::FreeImpactList* list = &freeListCache->mEffectFreeList;

				
			if (list->size() >= (unsigned int)mMaxNumFreeEffectPerList * 10 ||	
				(freeListCache->mBeyondMaxFreeListNumTime > 5.f && list->size() >= mMaxNumFreeEffectPerList))
			{
				Impact *effect = *(list->begin());

				assert (effect);

				OGRE_DELETE effect;
				effect = NULL;

				list->pop_front();
			}
			if (list->size() < mMaxNumFreeEffectPerList)
			{
				freeListCache->mBeyondMaxFreeListNumTime = 0.f;
			}
			//end----------------------

			list->push_back(effect);
		}
		else
		{
			ImpactFreeListCache*	freeListCache = new ImpactFreeListCache;

			ImpactFreeListCache::FreeImpactList* list = &freeListCache->mEffectFreeList;

			list->push_back(effect);

			std::pair<FreeEffectMap::iterator, bool> inserted =
				mFreeEffectMap.insert( FreeEffectMap::value_type(templateName, freeListCache) );

			assert(inserted.second);
		}
	}
	//---------------------------------------------------------------------
	void ImpactManager::createController(void)
	{
		mController = Ogre::ControllerManager::getSingleton().createFrameTimePassthroughController(
			Ogre::ControllerValueRealPtr(new EffectControllerValue(this)));
	}
	//---------------------------------------------------------------------
	void ImpactManager::updateActiveEffects(float time)
	{	
			//OgreProfile("EffectManager::updateActiveEffects");

			ActiveEffectList::iterator i = mActiveEffectList.begin();
			while (i != mActiveEffectList.end())
			{
				Impact *effect = *i;

				assert (effect);

				if (effect->getDelayRemove())
				{
					if ( false == effect->existVisualElements() )
					{
						effect->removeAllElements();

						if (effect->getRemoveParentNode())
						{
							effect->removeParentSceneNode();
						}

						// 如果不回收，直接删除
						if (false == effect->mPutIntoFreePool)
						{
							i = destroyEffect(effect);
						}
						else
						{
							addToFreeEffectMap(effect);

							i = mActiveEffectList.erase(i);
						}
					}
					else
					{
						if ( effect->hasProjector() )
						{
							effect->updateEffect(time);
						}
						++i;
					}	
				}
				else
				{
					effect->updateEffect(time);
					++i;
				}
			}

			this->_handleLogicModelEffectRequest();
	
		
	}

	void ImpactManager::updateEffectFreeListCache( Real time )
	{
		try
		{

			FreeEffectMap::iterator mapIter;
			for ( mapIter = mFreeEffectMap.begin();
				mapIter != mFreeEffectMap.end();++ mapIter)
			{
				assert(NULL != mapIter->second && "EffectManager::updateEffectFreeListCache");

				if(NULL == mapIter->second)
					continue;

				ImpactFreeListCache* freeListCache = mapIter->second;
				freeListCache->mCurrentLifeTime += time;

	
				freeListCache->mBeyondMaxFreeListNumTime += time;
			

				if(CLEAR_EFFECT_CACHE_TIME > freeListCache->mCurrentLifeTime)
					continue;
				else
				{
					ImpactFreeListCache::FreeImpactList *list = &freeListCache->mEffectFreeList;

					ImpactFreeListCache::FreeImpactList::iterator listIter;
					for (listIter = list->begin();
						listIter != list->end(); ++listIter )
					{
						delete (*listIter);
						(*listIter) = NULL;
					}
					list->clear();
				}
			}
		}
		catch(...)
		{
			//WARNING_LOG("EffectManager::updateEffectFreeListCache Failed --EffectManager::updateEffectFreeListCache");
			//OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,"EffectManager::updateEffectFreeListCache Failed!", "EffectManager::updateEffectFreeListCache" );
			throw;
		}
	}

	//---------------------------------------------------------------------
	size_t ImpactManager::getNumEffectTemplates(void)
	{
		return mEffectTemplateMap.size();
	}
	//---------------------------------------------------------------------
	ImpactManager::EffectTemplateIterator 
		ImpactManager::getEffectTemplateIterator(void)
	{
		return EffectTemplateIterator(
			mEffectTemplateMap.begin(), mEffectTemplateMap.end());
	}
	//---------------------------------------------------------------------
	ImpactManager::SkillIterator 
		ImpactManager::getSkillIterator(void)
	{
		return SkillIterator(
			mSkillTemplateMap.begin(), mSkillTemplateMap.end());
	}	
	//---------------------------------------------------------------------
	void ImpactManager::addToEffectTemplateScriptFileMap( const String &templateName, const String &fileName )
	{
		assert ( false == templateName.empty() && false == fileName.empty() );

		std::pair<EffectTemplateScriptFileMap::iterator, bool> inserted = 
			mEffectTemplateScriptFileMap.insert( EffectTemplateScriptFileMap::value_type(templateName, fileName) );

		assert (inserted.second);
	}
	//---------------------------------------------------------------------
	const String & ImpactManager::getFileNameByTemplateName( const String &templateName )
	{
		EffectTemplateScriptFileMap::iterator i = mEffectTemplateScriptFileMap.find(templateName);

		assert ( i!= mEffectTemplateScriptFileMap.end() );

		return i->second;
	}
	//---------------------------------------------------------------------
	void ImpactManager::getTemplatesFromScriptFile( const String &fileName, std::vector<String> &templates )
	{
		for ( EffectTemplateScriptFileMap::iterator i = mEffectTemplateScriptFileMap.begin();
			i != mEffectTemplateScriptFileMap.end(); ++i )
		{
			if ( i->second == fileName )
			{
				templates.push_back(i->first);
			}
		}
	}
	//---------------------------------------------------------------------
	Spell * ImpactManager::createSkill(const String &skillName)
	{
		String sLowerCaseSkill = skillName;
		Ogre::StringUtil::toLowerCase( sLowerCaseSkill );
		Spell *skillTemplate = Orphigine::ImpactManager::getSingleton().getSkillTemplate(sLowerCaseSkill);

		if ( NULL == skillTemplate )
			return NULL;
		else
		{
			Spell *newSkill = new Spell(skillName);
			*newSkill = *skillTemplate;

			return newSkill;
		}
	}
	//---------------------------------------------------------------------
	void ImpactManager::removeSkill(Spell *skill)
	{
		assert (skill);
		_onRemoveSkill(skill);
		//end
		skill->shutdown();
		delete skill;
	}
	//---------------------------------------------------------------------
	void ImpactManager::clearAllFreeEffects(void)
	{
		// 删除free effect map
		for ( FreeEffectMap::iterator i = mFreeEffectMap.begin();
			i != mFreeEffectMap.end();	++i	)
		{
			if (i->second)
			{
				ImpactFreeListCache* freeListCache = i->second;
				ImpactFreeListCache::FreeImpactList *list = &freeListCache->mEffectFreeList;

				for ( ImpactFreeListCache::FreeImpactList::iterator i = list->begin();
					i != list->end(); ++i )
				{
					OGRE_DELETE (*i);
					(*i) = NULL;
				}
				list->clear();
			}

			delete i->second;
			i->second = NULL;
		}
		mFreeEffectMap.clear();
	}


	bool ImpactManager::requestCreateEffect(SkeletonMeshComponentImpactParam &param)
	{
		mLogicModelEffectReqList.push_back(param);
		return true;
	}
	//---------------------------------------------------------------------

	bool ImpactManager::removeCreateEffectReq(SkeletonMeshComponent * model)
	{
		notifyLogicModelDestroyed(model);

		return true;
	}
	//---------------------------------------------------------------------
	bool ImpactManager::removeCreateEffectReq(String &name)
	{
		std::list<SkeletonMeshComponentImpactParam>::iterator iter, next;
		for (iter = mLogicModelEffectReqList.begin(); iter != mLogicModelEffectReqList.end(); iter = next)
		{
			next = iter; next ++;

			SkeletonMeshComponentImpactParam & param = *iter;
			if (param.reqType == 0)
			{
				if (param.name == name) {
					mLogicModelEffectReqList.erase(iter);
				}
			}
		}
		return true;
	}
	//---------------------------------------------------------------------
	void ImpactManager::_onRemoveSkill(Spell * skill)
	{
		std::list<SkeletonMeshComponentImpactParam>::iterator iter, next;
		for (iter = mLogicModelEffectReqList.begin(); iter != mLogicModelEffectReqList.end(); iter = next)
		{
			next = iter; next ++;

			SkeletonMeshComponentImpactParam & param = *iter;
			if (param.reqType == 1)
			{
				if (param.skill == skill) 
				{
					mLogicModelEffectReqList.erase(iter);
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactManager::notifyLogicModelDestroyed(SkeletonMeshComponent * model)
	{
		std::list<SkeletonMeshComponentImpactParam>::iterator iter, next;
		for (iter = mLogicModelEffectReqList.begin(); iter != mLogicModelEffectReqList.end(); iter = next)
		{
			next = iter; next ++;

			SkeletonMeshComponentImpactParam & param = *iter;
			if (param.model == model) 
			{
				mLogicModelEffectReqList.erase(iter);
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactManager::_removeLogicModelEffect( Impact * effect )
	{
		mActiveLogicModelEffectList.erase(effect);
	}

	//---------------------------------------------------------------------
	namespace 
	{
		struct LogicModelEffectParamSortor
		{
			bool operator() (const ImpactManager::SkeletonMeshComponentImpactParam* a, const ImpactManager::SkeletonMeshComponentImpactParam* b) const
			{
				if ( a->squaredDist < b->squaredDist )
					return true;

				return false;
			}
		};
	}

	//---------------------------------------------------------------------
	Impact* ImpactManager::_createLogicModelEffect(SkeletonMeshComponentImpactParam* param)
	{
		Impact * effect = 0;

		if (param->reqType == 0) //addeffect  self
		{
			param->model->_addEffect(param->effectName, param->locatorName, (SkeletonMeshComponent::GetTransformInfoType)param->transformType, param->colour, param->name.c_str(), param->priority, param->position, param->rotation);
			effect = param->model->getEffect(param->name);
		}
		else if (param->reqType == 1) 
		{
			effect = ImpactManager::getSingleton().addEffect(param->effectName);
			if (effect)
			{				
				effect->createSceneNode();
				effect->setPriority(param->priority);
				param->effectInfo->setEffect(effect); 

				if (false == param->effectInfo->getAttach())
				{				
					TransformInfo info;
					info.mRotation = param->rotation;
					info.mPosition = param->position;
					effect->setTransformInfo(info);
				}
			}
		}

		if (effect)
			mActiveLogicModelEffectList[effect] = effect;
		return effect;
	}
	//---------------------------------------------------------------------
	int ImpactManager::_getEnableEffectNum()
	{
		int num = 0;
		std::map<Impact*, Impact*>::iterator iter;
		for (iter = mActiveLogicModelEffectList.begin(); iter != mActiveLogicModelEffectList.end(); iter++)
		{
			if (iter->first->isEnable())
				num ++;
		}
		return num;
	}
	//---------------------------------------------------------------------
	Impact *ImpactManager::createEffect( const String &templateName, int priority)
	{
		Impact * effect = addEffect(templateName);
		if (!effect)
			return effect; 

		effect->setPriority(priority);

		switch(priority)
		{
		case 0: //self,ui
			break;
		case 1:	//equip					
		case 2:	//skill,bullet
			effect->enableEffect(mEnablePriority[priority]);
			if (_getEnableEffectNum() >= this->mEffectMaxNum) 
			{
				effect->enableEffect(false);
			}
			break;
		case 3: //other
			if (_getEnableEffectNum() >= this->mEffectMaxNum) 
			{
				effect->enableEffect(false);
			}
			break;
		}
		return effect;
	}
	//---------------------------------------------------------------------
	//限制effect的数量,只创建离player最近的若干effect
	void ImpactManager::_handleLogicModelEffectRequest()
	{
		if (mLogicModelEffectReqList.empty())
			return;

		Ogre::Vector3& playerPos = EngineManager::getSingletonPtr()->getMyPosition();

		if (playerPos.length() >= 9999999.f) //末初始化
		{
			//一定创建
			std::list<SkeletonMeshComponentImpactParam>::iterator iter;
			for (iter = mLogicModelEffectReqList.begin(); iter != mLogicModelEffectReqList.end(); iter ++)
			{
				SkeletonMeshComponentImpactParam &param = *iter;
				_createLogicModelEffect(&param);
			}
			mLogicModelEffectReqList.clear();
			return;
		}

		std::vector<SkeletonMeshComponentImpactParam*> sortedRequestList;

		sortedRequestList.reserve(mLogicModelEffectReqList.size());

		//遍历mLogicModelEffectReqList,并按距离排序
		std::list<SkeletonMeshComponentImpactParam>::iterator iter;
		for (iter = mLogicModelEffectReqList.begin(); iter != mLogicModelEffectReqList.end(); iter ++)
		{
			SkeletonMeshComponentImpactParam &param = *iter;
			Ogre::Vector3 & modelPos = param.model->getPosition();

			// 如果是UI，排在最前面 Nick
			if( param.model->getVisibleFlag() != Orphigine::OVF_GUI_ELEMENTS )
			{
				Real squaredDist = modelPos.squaredDistance(playerPos);
				param.squaredDist = squaredDist;				
			}
			else
			{
				param.squaredDist = 0;
				param.priority = 0;//将UI上的特效设为最高，一定创建并显示
			}

			sortedRequestList.push_back(&param);
		}

		std::stable_sort(sortedRequestList.begin(), sortedRequestList.end(), LogicModelEffectParamSortor()); 

		//创建effect 
		for (unsigned int i=0; i<(unsigned int)sortedRequestList.size(); i++)
		{
			Impact * effect = 0;
			SkeletonMeshComponentImpactParam * param = sortedRequestList[i];
			switch (param->priority) 
			{
			case 0: //myself,ui element
				effect = _createLogicModelEffect(param);				
				break;
			case 1: //equip
				if (_getEnableEffectNum() < this->mEffectMaxNum)
				{
					if (mEnablePriority[param->priority]) 
						_createLogicModelEffect(param);					
					/*effect = _createLogicModelEffect(param);
					if (effect)
					{
					effect->enableEffect(mEnablePriority[param->priority]);
					}*/
				}
				break;
			case 2: //skill
				if (_getEnableEffectNum() < this->mEffectMaxNum)
				{
					if (mEnablePriority[param->priority])
						_createLogicModelEffect(param);					
				}
				break;
			case 3: //other
				if (_getEnableEffectNum() < this->mEffectMaxNum)
				{
					_createLogicModelEffect(param);
				}
				break;
			}				
		}

		mLogicModelEffectReqList.clear();
	}
	//end

	//---------------------------------------------------------------------
	void ImpactManager::enableEffectPriority(int priority, bool enable)
	{		
		if (priority >= EFFECT_PRIORITY_NUM)
			return;
		if (mEnablePriority[priority] == enable)
			return; 

		mEnablePriority[priority] = enable;

		ActiveEffectList::iterator i;
		for (i = mActiveEffectList.begin(); i != mActiveEffectList.end(); i++)		
		{
			Impact *effect = *i;
			assert (effect);
			if (effect->getDelayRemove())			
				continue;
			if (effect->getPriority() == priority)
			{
				effect->enableEffect(enable);
			}
		}
	}	
	//---------------------------------------------------------------------
	void ImpactManager::setEffectLevel(ImpactLevel level)
	{
		mEffectLevel = level;		
		// 清除effect pool中所有的特效，因为之前创建出来的特效用的都是不同于现在的级别的，所以不能重用
		clearAllFreeEffects();

		// 现存的特效也不进行回收
		for ( ActiveEffectList::iterator i = mActiveEffectList.begin();
			i != mActiveEffectList.end();	++i	)
		{
			if (*i)
			{
				(*i)->mPutIntoFreePool = false;
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactManager::_destroyEffectTemplates(void)
	{
		// 删除Effect template map
		for ( EffectTemplateMap::iterator i = mEffectTemplateMap.begin();
			i != mEffectTemplateMap.end();	++i	)
		{
			if (i->second)
			{
				OGRE_DELETE i->second;
				i->second = NULL;
			}
		}
		mEffectTemplateMap.clear();
	}	
	void ImpactManager::_destroySkillTemplates(void)
	{
		// 删除skill map
		for ( SkillMap::iterator i = mSkillTemplateMap.begin();
			i != mSkillTemplateMap.end();	++i )
		{
			if (i->second)
			{				
				delete i->second;
				i->second = NULL;
			}
		}
		mSkillTemplateMap.clear();
	}
}