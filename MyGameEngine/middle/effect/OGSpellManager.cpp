#include "OgreHeader.h"
#include "OGSpellManager.h"
#include "OGSpell.h"
#include "OgreString.h"
#include "OgreArchive.h"
#include "OgreResourceManager.h"

template<> Orphigine::SpellManager * Ogre::Singleton<Orphigine::SpellManager>::msSingleton = 0;

namespace Orphigine	
{

	SpellManager *SpellManager::getSingletonPtr(void)
	{
		return msSingleton;
	}
	//---------------------------------------------------------------------
	SpellManager & SpellManager::getSingleton(void)
	{  
		assert(msSingleton);  return ( *msSingleton);
	}

	SpellManager::SpellManager():mDestroySkillCallback(NULL)
	{
		//������������ÿ֡����Skill
		//Ogre::ControllerManager &controllerManager = Ogre::ControllerManager::getSingleton();
		//mController = controllerManager.createFrameTimePassthroughController(Ogre::ControllerValueRealPtr(new EffectControllerValue(this)));
		//���ܶ�Ӧ�ĸ�ʽ
		mScriptPatterns.push_back("*.skb");
	}

	SpellManager::~SpellManager()
	{
		// ɾ��skill
		SkillIdMap::iterator itSkill = mSkillMap.begin();
		while(itSkill != mSkillMap.end())
		{
			if(itSkill->second)
			{
				delete itSkill->second;
				itSkill->second=NULL;
			}
			++itSkill;
		}
		mSkillMap.clear();
		//ɾ��TemplateSkill
		SkillMap::iterator itTemplateSkill = mTemplateSkillMap.begin();
		while(itTemplateSkill != mTemplateSkillMap.end())
		{
			if(itTemplateSkill->second)
			{
				delete itTemplateSkill->second;
				itTemplateSkill->second=NULL;
			}
			++itTemplateSkill;
		}
		mTemplateSkillMap.clear();       
	}	
	const Ogre::StringVector& SpellManager::getScriptPatterns(void) const
	{
		return mScriptPatterns;
	}
	//---------------------------------------------------------------------
	float SpellManager::getLoadingOrder(void) const
	{
		return 1000.0f;
	}
	void SpellManager::parseScript(Ogre::DataStreamPtr& stream, const String& groupName, const String& scriptPath)
	{
		String  parsingFileName = stream->getName();		
		if(Ogre::StringUtil::endsWith(parsingFileName,".skb",false))//����.skb�ļ�
		{
			SpellsSerializer tmpSerializer;
			SpellsSerializer::SkillInfoStr skillInfo;
			SpellsSerializer::SkillCollection sc;
			tmpSerializer.getSkillInfoFromStream(stream,skillInfo);
			if(skillInfo.skillNum >0 && skillInfo.skillNum == skillInfo.skillName.size())
			{
				for(int skillIndex =0; skillIndex != skillInfo.skillNum; ++ skillIndex)
				{
					String skillName = skillInfo.skillName[skillIndex];
					Spell* pSkill = getSkillTemplate(skillName);
					if (!pSkill)
					{
						Spell* pSkill = createSkillTemplate(skillName);
						sc.m_skillMap.insert(std::make_pair(skillName,pSkill));
					}
					else//ģ���ļ��Ѿ����ڣ����쳣
					{
						OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
							"skill template with name '" + skillName + "' already exists!",
							"SkillManager::parseScript");
					}
				}
				tmpSerializer.importSkillFromStream1(stream,&sc);
			}
			else//�ļ�����ʧ��
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, 
					"parse skill file with name " + parsingFileName + " failed!",
					"SkillManager::parseScript");
			}
		}
		else
		{
			// �쳣
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
				"wrong file name " + parsingFileName, "SkillManager::parseScript");
		}		
	}
	bool SpellManager::updateOneFrame()
	{
		//����ÿ��Skill
		SkillIdMap::iterator itSkill = mSkillMap.begin();
		while(itSkill != mSkillMap.end())
		{
			if(itSkill->second)
			{
				itSkill->second->update();
			}
			++itSkill;
		}
		return true;
	}
	int	SpellManager::createSkill(const String& skillTemplateName)
	{
		//��ģ����ѡȡ���ܽ���clone����������ڵĻ����ȴ���ģ�壬��Clone
		if(!skillTemplateName.empty())
		{
			String lowerSkillTemplateName = skillTemplateName;
			Ogre::StringUtil::toLowerCase(lowerSkillTemplateName);
			Spell* pSkill = getSkillTemplate(lowerSkillTemplateName);
			if(pSkill)//�ҵ�,Clone
			{
				Spell* pNewSkill = pSkill->Clone();
				mSkillMap.insert(std::make_pair(pSkill->getId(),pSkill));
				return pNewSkill->getId();
			}
			else//û�ҵ��������ļ�������ģ�壬Clone
			{
				//����skb�ļ�
				String fileName,ResGroupName;
				if(findTemplateSkill(skillTemplateName,fileName,ResGroupName))
				{
					Ogre::DataStreamPtr stream = ResourceManager::getSingleton().openResource(fileName,ResGroupName);
					//����
					Spell* pSkill = createSkillTemplate(lowerSkillTemplateName);
					SpellsSerializer tmpSerializer;
					SpellsSerializer::SkillCollection sc;
					sc.m_skillMap.insert(std::make_pair(lowerSkillTemplateName,pSkill));	
					tmpSerializer.importSkillFromStream1(stream,&sc);
					//Clone
					Spell* pNewSkill = pSkill->Clone();
					mSkillMap.insert(std::make_pair(pSkill->getId(),pSkill));
					return pNewSkill->getId();
				}
			}
		}
		return 0;
	}
	bool SpellManager::destroySkill(int skillId)
	{
		SkillIdMap::iterator itSkill = mSkillMap.find(skillId);
		if(itSkill != mSkillMap.end())
		{
			if(itSkill->second)
			{
				delete itSkill->second;
				itSkill->second=NULL;
			}
			mSkillMap.erase(itSkill);
			return true;
		}
		return false;
	}
	Spell* SpellManager::getSkill(int skillId)
	{
		SkillIdMap::iterator itSkill = mSkillMap.find(skillId);
		if(itSkill != mSkillMap.end())
		{
			return itSkill->second;			
		}
		return NULL;
	}
	Spell* SpellManager::createSkillTemplate(const String& skillTemplateName)
	{
		String lowerskillTemplateName = skillTemplateName;
		Ogre::StringUtil::toLowerCase( lowerskillTemplateName );
		Spell* pSkill = NULL;
		SkillMap::iterator itSkill = mTemplateSkillMap.find(lowerskillTemplateName);
		if (itSkill == mTemplateSkillMap.end())
		{
			pSkill = new Spell(lowerskillTemplateName);
			mTemplateSkillMap.insert(std::make_pair(lowerskillTemplateName,pSkill));
		}
		else
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"skill template with name '" + lowerskillTemplateName + "' already exists!",
				"SkillManager::createSkillTemplate");
		}
		return pSkill;
	}
	bool SpellManager::destroySkillTemplate(const String& skillTemplateName)
	{
		String lowerskillTemplateName = skillTemplateName;
		Ogre::StringUtil::toLowerCase( lowerskillTemplateName );
		SkillMap::iterator itSkill = mTemplateSkillMap.find(lowerskillTemplateName);
		if (itSkill != mTemplateSkillMap.end())
		{
			if(itSkill->second)
			{
				delete itSkill->second;
				itSkill->second=NULL;
			}
			mTemplateSkillMap.erase(itSkill);
			return true;
		}		
		return false;
	}
	Spell* SpellManager::getSkillTemplate(const String& skillTemplateName)
	{
		String lowerskillTemplateName = skillTemplateName;
		Ogre::StringUtil::toLowerCase( lowerskillTemplateName );
		SkillMap::iterator itSkill = mTemplateSkillMap.find(lowerskillTemplateName);
		if (itSkill != mTemplateSkillMap.end())
		{
			return itSkill->second;			
		}		
		return NULL;
	}
	SpellManager::SkillIterator SpellManager::getTemplateSkillIterator()
	{	
		return SkillIterator(mTemplateSkillMap.begin(), mTemplateSkillMap.end());
	}
	bool SpellManager::findTemplateSkill(const String& skillTemplateName,String& fileName,String& ResGroupName)
	{
		//�Ȳ��ҵ�ǰ��Դ��
		ResGroupName = "Bootstrap";
		if(findTemplateSkillInResourceGroup(skillTemplateName,fileName,ResGroupName))
		{
			return true;
		}		
		
		return false;		
	}
	bool SpellManager::findTemplateSkillInResourceGroup(const String& skillTemplateName,String& fileName,String& ResGroupName)
	{
		assert(false);
		return false;
	}
	DestroySkillCallback* SpellManager::getDestroySkillCallback() const
	{
		return mDestroySkillCallback;
	}
	bool SpellManager::setDestroySkillCallback(DestroySkillCallback* val)
	{
		mDestroySkillCallback = val;
		return true;
	}		
}
