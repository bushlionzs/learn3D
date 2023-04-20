#ifndef OGImpactManager_h__
#define OGImpactManager_h__


// ogre header
#include <OgreSingleton.h>
#include <OgreDataStream.h>
#include <OgreQuaternion.h>
#include <OgreIteratorWrapper.h>
#include <OgreColourValue.h>
#include "OGSpellSerializer.h"
#include "OgreController.h"
#include "OgreScriptLoader.h"

// 前向声明
namespace Ogre	
{
	class SceneNode;
}

namespace Orphigine	
{
	class Impact;
	class ImpactModuleFactory;
	class ImpactModule;
	class Engine;
	class ImpactBasic;
	class Spell;
	class SpellImpactModule;
	class SpellBulletFlowModule;
	class SpellRibbonModule;
	class SpellSoundModule;
	class SpellSceneLightModule;
	class MainSceneLight;
	class SpellModelModule;
	class SkeletonMeshComponent;
	class SpellImpactModule;
}	
namespace Orphigine
{	
	// 特效级别，默认为HIGH
	enum ImpactLevel
	{
		EL_LOW,
		EL_MID,
		EL_HIGH,
	};

	struct ImpactFreeListCache 
	{
		ImpactFreeListCache()
		{
			mEffectFreeList.clear();
			mCurrentLifeTime = 0.0f;
			mBeyondMaxFreeListNumTime = 0.f;
		}

		void			resetLifeTime()
		{
			mCurrentLifeTime = 0.0f;
		}

		typedef std::list<Impact *> FreeImpactList;

		FreeImpactList	mEffectFreeList;
		Real			mCurrentLifeTime;
		Real            mBeyondMaxFreeListNumTime;
	};

	const static int EFFECT_PRIORITY_NUM = 4;
	class _OrphigineExport ImpactManager : public Ogre::Singleton<ImpactManager>, public ScriptLoader
	{
	public:

		typedef std::map<String, Impact *>				EffectTemplateMap;
		typedef std::list<Impact *>						ActiveEffectList;
		//key是特效的模板名
		typedef std::map<String, ImpactFreeListCache *> FreeEffectMap;
		//特效名--特效文件名的map，比如:001 --- 001.effect
		typedef std::map<String, String>				EffectTemplateScriptFileMap;
		typedef std::vector<String>						LoadedScripts;
		typedef std::map<String, Spell *>				SkillMap;

		struct SkeletonMeshComponentImpactParam
		{
			SkeletonMeshComponent * model;
			int    reqType; //0, addEffect, 1,_createAnimationEffect		

			String effectName;
			String locatorName;
			int    transformType;
			Ogre::ColourValue colour;
			String name;

			SpellImpactModule *effectInfo;
			Ogre::Vector3 position;
			Ogre::Quaternion rotation;
			Spell * skill;
			int priority;
			Real squaredDist;

			//effect参数
			SkeletonMeshComponentImpactParam& operator = (const SkeletonMeshComponentImpactParam& rhs)
			{
				model = rhs.model;	
				reqType = rhs.reqType;
				effectName = rhs.effectName;
				locatorName = rhs.locatorName;
				transformType = rhs.transformType;
				colour = rhs.colour;
				name = rhs.name;
				effectInfo = rhs.effectInfo;
				position = rhs.position;
				rotation = rhs.rotation;
				squaredDist = rhs.squaredDist;
				skill = rhs.skill;
				priority = rhs.priority;

				return *this;
			}
			SkeletonMeshComponentImpactParam()
			{
				model = 0;
				squaredDist = 0.f;
				reqType = -1;
				skill = 0;
				effectInfo = 0;
				priority = 3;
			}
			SkeletonMeshComponentImpactParam( const SkeletonMeshComponentImpactParam& rkVector )				
			{
				*this = rkVector;
			}
		};
		//end

		bool mEnablePriority[EFFECT_PRIORITY_NUM];
		//end
	public:

		ImpactManager();
		~ImpactManager();

		//Ogre::ScriptLoader函数重载
		virtual String	getSuffix(void);
		virtual void						parseScript(Ogre::DataStreamPtr& stream, const String& groupName);
		virtual Real						getLoadingOrder(void) const;
	
		static ImpactManager&				getSingleton(void);       
		static ImpactManager*				getSingletonPtr(void);

	
		void	dump(const String &fileName);
		bool	outputEffectInfo(std::ofstream& outfileName);

		void createController(void);


		
		Impact*			addEffect(const String& effectTemplateName);
		
		ActiveEffectList::iterator destroyEffect( Impact *effect );
		
		void updateActiveEffects(Real time);
	
		void	updateEffectFreeListCache(Real time);
		size_t getNumEffectTemplates(void);

		typedef Ogre::MapIterator<EffectTemplateMap> EffectTemplateIterator;
		EffectTemplateIterator getEffectTemplateIterator(void);
		const String & getFileNameByTemplateName( const String &templateName );
		void getTemplatesFromScriptFile( const String &fileName, std::vector<String> &templates );
		/// 清空特效池中的特效
		void clearAllFreeEffects(void);

		/// 设置特效级别
		void setEffectLevel(ImpactLevel level);
		ImpactLevel getEffectLevel(void)
		{
			return mEffectLevel;
		}

		void _destroyEffectTemplates(void);
		void removeEffect( Impact *effect, bool removeParentNode = true, bool removeNow = true );
		/// 根据模板名称来获取模板
		Impact * getTemplate(const String& name);

		Impact * createEffectTemplate(const String &name);
		bool addEffectTemplate(Impact *pEffect,const String& templateName);
		void addToEffectTemplateScriptFileMap( const String &templateName, const String &fileName );
	
		bool requestCreateEffect(SkeletonMeshComponentImpactParam &param);
		bool removeCreateEffectReq(String &name);
		bool removeCreateEffectReq(SkeletonMeshComponent * model);
		void notifyLogicModelDestroyed(SkeletonMeshComponent * model);
		//end

		void enableEffectPriority(int priority, bool enable);		
		void setEffectMaxNum(unsigned int maxNum) {mEffectMaxNum = maxNum;}

		Impact* createEffect( const String &templateName, int priority=2);
		//end
		//空闲链表是用来存放上次删除后的特效实例(重新初始化后的)，用于下次快速创建新特效
		Impact * getFromFreeMap( const String &templateName );
		/// 把一个特效加入到空闲链表中
		void addToFreeEffectMap(Impact *effect);	

		void _removeLogicModelEffect( Impact * effect );
		void _handleLogicModelEffectRequest();
		Impact*  _createLogicModelEffect(SkeletonMeshComponentImpactParam* param);
		void _onRemoveSkill(Spell * skill);
		int _getEnableEffectNum();
		//end



		//skill相关
		typedef Ogre::MapIterator<SkillMap> SkillIterator;

		SkillIterator getSkillIterator(void);	
		Spell * createSkillTemplate(const String &skillName);
		Spell * getSkillTemplate( const String &skillName );

		Spell * createSkill(const String &skillName);
		void removeSkill(Spell *skill);
		void _destroySkillTemplates(void);
		//其它
		/** 暂时地删除一个特效
		并不是真正地删除特效，而是把它从活动的特效链表中删除，放入
		空闲的特效的链表，以备后用
		@param removeParentNode 是否要把该effect的节点从他的父节点上卸下来，
		如果创建effect的节点调用的是createSceneNode，这个参数为false，
		如果创建effect的节点调用的是createSceneNode( Ogre::SceneNode *parentNode )，这个参数为true
		@param removeNow 是否马上就删除这个effect，如果为false，那么这个effect会在它完全播放完才
		被删除

		@remarks 如果removeNow为false，不会马上删除effect，这时要保证effect的SceneNode不会先于effect删除，
		所以如果需要removeNow为false，创建effect的scnenode最好使用createSceneNode()，这样，scenenode保存
		在effect内部，可以保证scenenode的删除时机
		*/
		void getLoadedScripts( std::vector<String> &files )	{	files = mLoadedScripts;	}

		MainSceneLight* getMainSceneLight(void)
		{
			return mMainSceneLight;
		}

		ActiveEffectList& getActiveEffectList() {return mActiveEffectList;} 

	private:
		//通用
		Ogre::Controller<Real>*			mController;
		Ogre::StringVector				mScriptPatterns;
		unsigned short					mMaxNumFreeEffectPerList;
		/// 当前场景上的灯光变化信息，只保存了2个主光源的信息
		MainSceneLight* mMainSceneLight;

		//effect相关
		EffectTemplateMap				mEffectTemplateMap;
		FreeEffectMap					mFreeEffectMap;
		ActiveEffectList				mActiveEffectList;
		EffectTemplateScriptFileMap		mEffectTemplateScriptFileMap;//特效名称和特效文件名称的map关联
		LoadedScripts					mLoadedScripts;
		/// 特效级别
		ImpactLevel mEffectLevel;
		unsigned int mEffectMaxNum;
	
		std::list<SkeletonMeshComponentImpactParam>	mLogicModelEffectReqList;
		std::map<Impact*, Impact*>  mActiveLogicModelEffectList; 		
		//end
		//skill相关
		SkillMap						mSkillTemplateMap;
	protected:
		
	};
}

#endif // OGImpactManager_h__