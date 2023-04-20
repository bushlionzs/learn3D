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
		//���Ͷ���
		//key��skill������
		typedef std::map<String, Spell* >	SkillMap;
		typedef std::map<int, Spell* >		SkillIdMap;
		typedef Ogre::MapIterator<SkillMap> SkillIterator;


		SpellManager();
		~SpellManager();
		//Ogre::Singleton��������
		static SpellManager&				getSingleton(void);       
		static SpellManager*				getSingletonPtr(void);

		//Ogre::ScriptLoader��������
		virtual const Ogre::StringVector&	getScriptPatterns(void) const;
		virtual void						parseScript(Ogre::DataStreamPtr& stream, const String& groupName, const String& scriptPath = "");
		virtual Real						getLoadingOrder(void) const;
		//�ӿں���
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
		//ͨ��
		Ogre::StringVector				mScriptPatterns;
		DestroySkillCallback*			mDestroySkillCallback;
		//skill���
		//key�Ǽ���ģ����
		SkillMap						mTemplateSkillMap;	//Skillģ�壬���ڿ��ٴ����µ�skill
		//key�Ǽ���id
		SkillIdMap						mSkillMap;			//Skillʵ������ǰ����ʹ�õ�
	};


}//

#endif // OGSpellManager_h__