#ifndef OGSpellManager_h__
#define OGSpellManager_h__


#include <OgreSingleton.h>
#include <OgreIteratorWrapper.h>
#include "OGSpellSerializer.h"

namespace Orphigine	
{
	class DestroySkillCallback
	{
	public:
		virtual void onDestroySkill(Spell* skill) = 0;
	};	

	class _OrphigineExport SpellManager : public Ogre::Singleton<SpellManager>
	{
	public:
		//类型定义
		//key是skill的名称
		typedef std::map<String, Spell* >	SkillMap;
		typedef std::map<int, Spell* >		SkillIdMap;
		typedef Ogre::MapIterator<SkillMap> SkillIterator;


		SpellManager();
		~SpellManager();
		//Ogre::Singleton函数重载
		static SpellManager&				getSingleton(void);       
		static SpellManager*				getSingletonPtr(void);

		//Ogre::ScriptLoader函数重载
		virtual const Ogre::StringVector&	getScriptPatterns(void) const;
		virtual void						parseScript(Ogre::DataStreamPtr& stream, const String& groupName, const String& scriptPath = "");
		virtual Real						getLoadingOrder(void) const;
		//接口函数
		bool			updateOneFrame();
		int				createSkill(const String& skillTemplateName);
		bool			destroySkill(int skillId);
		Spell*			getSkill(int skillId);

		Spell*					createSkillTemplate(const String& skillTemplateName);
		bool					destroySkillTemplate(const String& skillTemplateName);
		Spell*					getSkillTemplate(const String& skillTemplateName);
		SkillIterator			getTemplateSkillIterator(void);
		bool					findTemplateSkill(const String& skillTemplateName,String& fileName,String& ResGroupName);
		bool					findTemplateSkillInResourceGroup(const String& skillTemplateName,String& fileName,String& ResGroupName);


		DestroySkillCallback*	getDestroySkillCallback() const;
		bool					setDestroySkillCallback(DestroySkillCallback* val);
	private:
		//通用
		Ogre::StringVector				mScriptPatterns;
		DestroySkillCallback*			mDestroySkillCallback;
		//skill相关
		//key是技能模板名
		SkillMap						mTemplateSkillMap;	//Skill模板，用于快速创建新的skill
		//key是技能id
		SkillIdMap						mSkillMap;			//Skill实例，当前真正使用的
	};


}//

#endif // OGSpellManager_h__