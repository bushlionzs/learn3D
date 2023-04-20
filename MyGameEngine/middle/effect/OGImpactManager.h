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

// ǰ������
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
	// ��Ч����Ĭ��ΪHIGH
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
		//key����Ч��ģ����
		typedef std::map<String, ImpactFreeListCache *> FreeEffectMap;
		//��Ч��--��Ч�ļ�����map������:001 --- 001.effect
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

			//effect����
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

		//Ogre::ScriptLoader��������
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
		/// �����Ч���е���Ч
		void clearAllFreeEffects(void);

		/// ������Ч����
		void setEffectLevel(ImpactLevel level);
		ImpactLevel getEffectLevel(void)
		{
			return mEffectLevel;
		}

		void _destroyEffectTemplates(void);
		void removeEffect( Impact *effect, bool removeParentNode = true, bool removeNow = true );
		/// ����ģ����������ȡģ��
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
		//������������������ϴ�ɾ�������Чʵ��(���³�ʼ�����)�������´ο��ٴ�������Ч
		Impact * getFromFreeMap( const String &templateName );
		/// ��һ����Ч���뵽����������
		void addToFreeEffectMap(Impact *effect);	

		void _removeLogicModelEffect( Impact * effect );
		void _handleLogicModelEffectRequest();
		Impact*  _createLogicModelEffect(SkeletonMeshComponentImpactParam* param);
		void _onRemoveSkill(Spell * skill);
		int _getEnableEffectNum();
		//end



		//skill���
		typedef Ogre::MapIterator<SkillMap> SkillIterator;

		SkillIterator getSkillIterator(void);	
		Spell * createSkillTemplate(const String &skillName);
		Spell * getSkillTemplate( const String &skillName );

		Spell * createSkill(const String &skillName);
		void removeSkill(Spell *skill);
		void _destroySkillTemplates(void);
		//����
		/** ��ʱ��ɾ��һ����Ч
		������������ɾ����Ч�����ǰ����ӻ����Ч������ɾ��������
		���е���Ч�������Ա�����
		@param removeParentNode �Ƿ�Ҫ�Ѹ�effect�Ľڵ�����ĸ��ڵ���ж������
		�������effect�Ľڵ���õ���createSceneNode���������Ϊfalse��
		�������effect�Ľڵ���õ���createSceneNode( Ogre::SceneNode *parentNode )���������Ϊtrue
		@param removeNow �Ƿ����Ͼ�ɾ�����effect�����Ϊfalse����ô���effect��������ȫ�������
		��ɾ��

		@remarks ���removeNowΪfalse����������ɾ��effect����ʱҪ��֤effect��SceneNode��������effectɾ����
		���������ҪremoveNowΪfalse������effect��scnenode���ʹ��createSceneNode()��������scenenode����
		��effect�ڲ������Ա�֤scenenode��ɾ��ʱ��
		*/
		void getLoadedScripts( std::vector<String> &files )	{	files = mLoadedScripts;	}

		MainSceneLight* getMainSceneLight(void)
		{
			return mMainSceneLight;
		}

		ActiveEffectList& getActiveEffectList() {return mActiveEffectList;} 

	private:
		//ͨ��
		Ogre::Controller<Real>*			mController;
		Ogre::StringVector				mScriptPatterns;
		unsigned short					mMaxNumFreeEffectPerList;
		/// ��ǰ�����ϵĵƹ�仯��Ϣ��ֻ������2������Դ����Ϣ
		MainSceneLight* mMainSceneLight;

		//effect���
		EffectTemplateMap				mEffectTemplateMap;
		FreeEffectMap					mFreeEffectMap;
		ActiveEffectList				mActiveEffectList;
		EffectTemplateScriptFileMap		mEffectTemplateScriptFileMap;//��Ч���ƺ���Ч�ļ����Ƶ�map����
		LoadedScripts					mLoadedScripts;
		/// ��Ч����
		ImpactLevel mEffectLevel;
		unsigned int mEffectMaxNum;
	
		std::list<SkeletonMeshComponentImpactParam>	mLogicModelEffectReqList;
		std::map<Impact*, Impact*>  mActiveLogicModelEffectList; 		
		//end
		//skill���
		SkillMap						mSkillTemplateMap;
	protected:
		
	};
}

#endif // OGImpactManager_h__