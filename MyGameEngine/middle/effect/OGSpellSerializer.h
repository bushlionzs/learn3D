#ifndef OGSpellSerializer_h__
#define OGSpellSerializer_h__

#include "OgreSerializer.h"
#include "OgreDataStream.h"

namespace Orphigine
{
	class _OrphigineExport SpellsSerializer : public Ogre::Serializer
	{
	public:
		friend	class	Spell;
		friend	class	SpellImpactModule;
		friend  class   SpellRibbonModule;
		friend	class	SpellSceneLightModule;
		friend	class	SpellSoundModule;
		friend  class	SpellModelModule;
		friend	class	SpellBulletFlowModule;
		enum SkillsFileFormat
		{
			SKILL_FILEHEADER =		0x1000,
			SKILL_EDITOR_SEGMENT =  0x2000,
			SKILL_SINGLE_SKILL =	0x3000,
			SKILL_EFFECT_INFO =		0x4000,
			SKILL_RIBBON_INFO =		0x5000,
			SKILL_LIGHT_INFO =		0x6000,
			SKILL_SOUND_INFO =		0x7000,
			SKILL_BF_INFO =			0x8000,
			SKILL_MODEL_INFO =		0x9000
		};
		struct	SkillCollection
		{
			String					m_editorSegment;
			std::map<String,Spell*>	m_skillMap;
		};
		struct  SkillInfoStr
		{
			String					editorSegment;
			int						skillNum;
			std::vector<String>		skillName;
		};


		//************************************
		// Method:    loadBinary
		// FullName:  Orphigine::SkillsSerializer::loadBinary
		// Access:    public 
		// Returns:   void
		// Parameter: Ogre::DataStreamPtr & stream
		// Parameter: EffectManager * effectMgr
		// Parameter: SkillCollection * sc
		// Parameter: bool loadOnDamand 如果为真，那么加载的Skill模板如果在内存中存在，
		//			则重现加载，刷新此模板，默认为不覆盖
		//************************************
		bool importSkillFromStream(Ogre::DataStreamPtr& stream,SkillCollection* sc,bool loadOnDamand = false);
		
		bool getSkillInfoFromStream(Ogre::DataStreamPtr& stream,SkillInfoStr& skillInfo);
		//临时函数	
		bool importSkillFromStream1(Ogre::DataStreamPtr& stream,SkillCollection* sc);

		static	String	ms_currentVersion;
	};
}
#endif // OGSpellSerializer_h__