#ifndef OGBulletSystemManager_h__
#define OGBulletSystemManager_h__

#include "OgreSingleton.h"
#include "OgreStringInterface.h"
#include <OgreDataStream.h>
#include "OgreString.h"
#include "OgreIteratorWrapper.h"

namespace Orphigine
{
	class BulletSystem;
	class BulletSystemEffectElement;
	class SpellRibbonModule;
	class SpellSoundModule;
	class SpellSceneLightModule;
	class BulletSystemBeamElement;

	class _OrphigineExport BulletSystemManager : public Ogre::Singleton<BulletSystemManager>
	{
	public:
		BulletSystemManager();
		virtual ~BulletSystemManager();

		/*
		 *	重载ScriptLoader纯虚函数
		 */
		virtual const StringVector& getScriptPatterns(void) const;
		virtual void parseScript(Ogre::DataStreamPtr& stream, const String& groupName);
		virtual Real getLoadingOrder(void) const;

		void			parseBulletSystemTemplateSegment(const String& templateName,Ogre::DataStreamPtr& stream, const String& groupName, bool reload = false);

		BulletSystem*	createBulletSystem(const String& name);
		void			destroyBulletSystem(BulletSystem* bulletSystem);

		BulletSystem*	createBulletSystemTemplate(const String& name);
		void			addBulletSystemTemplate(const String& name,BulletSystem* bulletSystem);	
		BulletSystem*	getBulletSystemTemplate(const String& name);
		void			destroyBulletSystemTemplate(const String& name);

		typedef Ogre::MapIterator<std::map<String,BulletSystem*> > BulletSystemTemplateIterator;
		BulletSystemTemplateIterator getBulletSystemTemplateIterator();

	protected:
		void skipToNextCloseBrace(Ogre::DataStreamPtr& chunk);
		void skipToNextOpenBrace(Ogre::DataStreamPtr& chunk);
		/// 解析.bullet文件
		void parseAttrib(const String& line, BulletSystem* bulletSystem);
		void parseAnimEffectInfo(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem);	
		void parseAnimEffectInfoAttrib(const String& line, BulletSystemEffectElement *effectInfo);
		void parseAnimRibbon(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem);	
		void parseAnimRibbonAttrib(const String& line, SpellRibbonModule *ribbon);
		void parseAnimSound(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem);	
		void parseAnimSoundAttrib(const String& line, SpellSoundModule *sound);
		void parseAnimSceneLightInfo(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem);	
		void parseAnimSceneLightInfoAttrib(const String& line, SpellSceneLightModule *sceneLightInfo);
		void parseAnimBeamElement(Ogre::DataStreamPtr& stream,BulletSystem* bulletSystem);
		void parseAnimBeamElementAttrib(const String& line,BulletSystemBeamElement* beamElement);
		/// 输出错误信息
		void _logErrorInfo(const String& errorInfo, const String& lineContent, 
			const String& functionName);

	protected:
		/// 每次进行getLine的时候就递增行号，作为错误的输出信息
		int mWrongLineNum;
		/// 当前解析的文件名称
		String mParsingFileName;

		std::map<String,BulletSystem*> m_systemTemplate;
		
		StringVector	m_scriptPatterns;
	private:
	};
}

#endif // OGBulletSystemManager_h__