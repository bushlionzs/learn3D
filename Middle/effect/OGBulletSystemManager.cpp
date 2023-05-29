#include "OgreHeader.h"
#include "OGBulletSystemManager.h"
#include "OGSpellRibandModule.h"
#include "OGSpellImpactModule.h"
#include "OGSpellSoundModule.h"
#include "OGSpellSceneLightModule.h"
#include "OGBulletSystemBeamElement.h"
#include "OGMainSceneLight.h"
#include "OGBulletSystem.h"
#include "OGBulletSystemEffectElement.h"
#include "OgreStringConverter.h"
#include "platform_log.h"


template<> Orphigine::BulletSystemManager* Ogre::Singleton<Orphigine::BulletSystemManager>::msSingleton = NULL;

namespace Orphigine
{
	BulletSystemManager::BulletSystemManager()		
	{
		m_systemTemplate.clear();

		/*m_scriptPatterns.push_back("*.bullet");
		Ogre::ResourceGroupManager::getSingleton()._registerScriptLoader(this);*/

	}

	BulletSystemManager::~BulletSystemManager()
	{
		//Ogre::ResourceGroupManager::getSingleton()._unregisterScriptLoader(this);

		std::map<String,BulletSystem*>::iterator iter;
		for (iter = m_systemTemplate.begin();iter != m_systemTemplate.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		m_systemTemplate.clear();
	}

	void BulletSystemManager::parseScript(Ogre::DataStreamPtr& stream, const String& groupName)
	{
	}

	void BulletSystemManager::parseBulletSystemTemplateSegment( const String& templateName, Ogre::DataStreamPtr& stream, const String& groupName, bool reload )
	{
		String line;
		BulletSystem *pBulletSystem = NULL;

		if (reload)
		{
			destroyBulletSystemTemplate(templateName);
		}

		pBulletSystem = createBulletSystemTemplate(templateName);

		std::vector<String> vecparams;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++mWrongLineNum;

			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{
				if (line == "}")
				{
					pBulletSystem = NULL;
					return;
				}
				else if ( line == "AnimEffect" )
				{
					// 解析anim effect info

					skipToNextOpenBrace(stream);
					parseAnimEffectInfo(stream, pBulletSystem);
				}
				else if ( line == "Ribbon" )
				{
					skipToNextOpenBrace(stream);
					parseAnimRibbon(stream, pBulletSystem);
				}
				else if ( line == "Sound" )
				{
					skipToNextOpenBrace(stream);
					parseAnimSound(stream, pBulletSystem);
				}
				else if ( line == "SceneLight" )
				{
					skipToNextOpenBrace(stream);
					parseAnimSceneLightInfo(stream, pBulletSystem);
				}
				else if ( line == "Beam" )
				{
					skipToNextOpenBrace(stream);
					parseAnimBeamElement(stream,pBulletSystem);
				}
				// 一个新的element
				else
				{						
					parseAttrib(line, pBulletSystem);
				}				
				
			}
		}
	}

	void BulletSystemManager::parseAttrib( const String& line, BulletSystem* bulletSystem )
	{
		std::vector<String> vecparams = Ogre::StringUtil::split(line," \t",1);

		if (2 != (int)vecparams.size())
		{
			_logErrorInfo("The number of parameters must be 2",line,"BulletSystemManager::parseAttrib");
		}
		else if (!bulletSystem->setParameter(vecparams[0],vecparams[1]))
		{
			_logErrorInfo("Bad bullet system attribute line",line,"BulletSystemManager::parseAttrib");
		}
	}

	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimEffectInfo(Ogre::DataStreamPtr &stream, BulletSystem *bullet)
	{
		assert (bullet);

		BulletSystemEffectElement *effectInfo = bullet->addBulletSystemEffectElement();

		assert (effectInfo);

		String line;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++mWrongLineNum;

			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{				
				if (line == "}")
				{
					// Finished emitter
					break;
				}
				else
				{
					// Attribute
					//	Ogre::StringUtil::toLowerCase(line);
					parseAnimEffectInfoAttrib(line, effectInfo);
				}
			}
		}
	}

	void BulletSystemManager::parseAnimEffectInfoAttrib( const String& line, BulletSystemEffectElement *effectInfo )
	{
		// 设置element的属性
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		if (vecparams.size() != 2)
		{
			_logErrorInfo("the number of parameters must be 2!", line, "BulletSystemManager::parseAnimEffectInfoAttrib");
			return;
		}

		if ( false == effectInfo->setParameter(vecparams[0], vecparams[1]) )
		{
			_logErrorInfo("Bad Anim Effect Info attribute line", line, "BulletSystemManager::parseAnimEffectInfoAttrib");
		}
	}

	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimRibbon(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem)
	{
		assert (bulletSystem);

		SpellRibbonModule *ribbon = bulletSystem->addAnimationRibbon();

		assert (ribbon);

		// Parse emitter details
		String line;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++mWrongLineNum;

			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{				
				if (line == "}")
				{
					// Finished emitter
					break;
				}
				else
				{
					// Attribute
					//	Ogre::StringUtil::toLowerCase(line);
					parseAnimRibbonAttrib(line, ribbon);
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimRibbonAttrib(const String& line, SpellRibbonModule *ribbon)
	{
		// 设置element的属性
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		if (  vecparams.size() != 2 || false == ribbon->setParameter(vecparams[0], vecparams[1]) )
		{
			_logErrorInfo("Bad Anim ribbon attribute line", line, "OrphigineBulletSystemManager::parseAnimRibbonAttrib");
		}
	}
	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimSound(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem)
	{
		assert (bulletSystem);

		SpellSoundModule *sound = bulletSystem->addAnimationSound();

		assert (sound);

		// Parse emitter details
		String line;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++mWrongLineNum;

			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{				
				if (line == "}")
				{
					// Finished emitter
					break;
				}
				else
				{
					// Attribute
					//	Ogre::StringUtil::toLowerCase(line);
					parseAnimSoundAttrib(line, sound);
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimSoundAttrib(const String& line, SpellSoundModule *sound)
	{
		// 设置element的属性
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		if (  vecparams.size() != 2 || false == sound->setParameter(vecparams[0], vecparams[1]) )
		{
			_logErrorInfo("Bad Anim sound attribute line", line, "OrphigineBulletSystemManager::parseAnimSoundAttrib");
		}
	}	
	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimSceneLightInfo(Ogre::DataStreamPtr &stream, BulletSystem *bulletSystem)
	{
		assert (bulletSystem);

		SpellSceneLightModule *sceneLightInfo = bulletSystem->addAnimationSceneLightInfo();

		assert (sceneLightInfo);

		// Parse emitter details
		String line;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++mWrongLineNum;

			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{				
				if (line == "}")
				{
					// Finished emitter
					break;
				}
				else
				{
					// Attribute
					//	Ogre::StringUtil::toLowerCase(line);
					parseAnimSceneLightInfoAttrib(line, sceneLightInfo);
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void BulletSystemManager::parseAnimSceneLightInfoAttrib(const String& line, SpellSceneLightModule *sceneLightInfo)
	{
		// 设置element的属性
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		if (vecparams.size() != 2)
		{
			_logErrorInfo("the number of parameters must be 2!", line, "OrphigineBulletSystemManager::parseAnimSceneLightInfoAttrib");
			return;
		}

		if ( false == sceneLightInfo->setParameter(vecparams[0], vecparams[1]) )
		{
			_logErrorInfo("Bad Anim Scene Light Info attribute line", line, "OrphigineBulletSystemManager::parseAnimSceneLightInfoAttrib");
		}
	}

	void BulletSystemManager::parseAnimBeamElement(Ogre::DataStreamPtr& stream,BulletSystem* bulletSystem)
	{
		assert (bulletSystem);

		BulletSystemBeamElement *beamElement = bulletSystem->addBulletSystemBeamElement();

		assert (beamElement);

		// Parse emitter details
		String line;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++mWrongLineNum;

			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{				
				if (line == "}")
				{
					// Finished emitter
					break;
				}
				else
				{
					// Attribute
					//	Ogre::StringUtil::toLowerCase(line);
					parseAnimBeamElementAttrib(line, beamElement);
				}
			}
		}
	}

	void BulletSystemManager::parseAnimBeamElementAttrib(const String& line,BulletSystemBeamElement* beamElement)
	{
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		if (vecparams.size() != 2)
		{
			_logErrorInfo("the number of parameters must be 2!", line, "OrphigineBulletSystemManager::parseAnimBeamElementAttrib");
			return;
		}

		if ( false == beamElement->setParameter(vecparams[0], vecparams[1]) )
		{
			_logErrorInfo("Bad Anim Beam Element attribute line", line, "OrphigineBulletSystemManager::parseAnimBeamElementAttrib");
		}
	}

	//-----------------------------------------------------------------------
	void BulletSystemManager::skipToNextCloseBrace(Ogre::DataStreamPtr& stream)
	{
		String line = "";
		while (!stream->eof() && line != "}")
		{
			line = stream->getLine(true);
			++mWrongLineNum;
		}

	}
	//-----------------------------------------------------------------------
	void BulletSystemManager::skipToNextOpenBrace(Ogre::DataStreamPtr& stream)
	{
		String line = "";
		while (!stream->eof() && line != "{")
		{
			line = stream->getLine(true);
			++mWrongLineNum;
		}

	}
	void BulletSystemManager::_logErrorInfo(const String& errorInfo, const String& lineContent, 
		const String& functionName)
	{
		String errorDesc;

		errorDesc += "\n------------OrphigineBulletSystemManager Error Description------------------------";
		errorDesc += "\nfile : " + mParsingFileName;
		errorDesc += "\nline : " + Ogre::StringConverter::toString(mWrongLineNum);
		errorDesc += "\nline content : " + lineContent;
		errorDesc += "\nfunction : " + functionName;
		errorDesc += "\ndescription : " + errorInfo;
		errorDesc += "\n-------------------------------------------------------------------";

		WARNING_LOG(errorDesc.data());
	}

	BulletSystem* BulletSystemManager::createBulletSystemTemplate( const String& name )
	{
		if (m_systemTemplate.find(name) != m_systemTemplate.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"ParticleSystem template with name '" + name + "' already exists.", 
				"ParticleSystemManager::createBulletSystemTemplate");
		}

		BulletSystem* tmpBulletSystem = OGRE_NEW BulletSystem(name);
		addBulletSystemTemplate(name,tmpBulletSystem);
		return tmpBulletSystem;
	}

	void BulletSystemManager::addBulletSystemTemplate( const String& name,BulletSystem* bulletSystem )
	{
		if (m_systemTemplate.find(name) != m_systemTemplate.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"BulletSystem template with name '" + name + "' already exists.", 
				"BulletSystemManager::addTemplate");
		}

		m_systemTemplate.insert(std::map<String,BulletSystem*>::value_type(name,bulletSystem));
	}

	BulletSystem* BulletSystemManager::getBulletSystemTemplate( const String& name )
	{
		std::map<String,BulletSystem*>::iterator iter = m_systemTemplate.find(name);

		if (iter == m_systemTemplate.end())
			return NULL;
		else
			return iter->second;
	}

	BulletSystem* BulletSystemManager::createBulletSystem( const String& name )
	{
		BulletSystem* tmpTemplate = getBulletSystemTemplate(name);

		if (NULL == tmpTemplate)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, 
				"BulletSystemManager Can not found require template '" + name + "'.", 
				"BulletSystemManager::createBulletSystem");
		}

		BulletSystem* tmpBulletSystem = OGRE_NEW BulletSystem(name);

		*tmpBulletSystem = * tmpTemplate;

		return tmpBulletSystem;
	}

	const StringVector& BulletSystemManager::getScriptPatterns( void ) const
	{
		return m_scriptPatterns;
	}

	Real BulletSystemManager::getLoadingOrder( void ) const
	{
		return 1000.0f;
	}

	BulletSystemManager::BulletSystemTemplateIterator BulletSystemManager::getBulletSystemTemplateIterator()
	{
		return BulletSystemTemplateIterator(
			m_systemTemplate.begin(),m_systemTemplate.end());
	}

	void BulletSystemManager::destroyBulletSystem( BulletSystem* bulletSystem )
	{
		bulletSystem->removeSceneNode();
		OGRE_DELETE bulletSystem;
	}

	void BulletSystemManager::destroyBulletSystemTemplate( const String& name )
	{
		std::map<String,BulletSystem*>::iterator iter = m_systemTemplate.find(name);
		
		if (m_systemTemplate.end() != iter)
		{
			OGRE_DELETE iter->second;
			iter->second = NULL;

			m_systemTemplate.erase(iter);
		}
	}
}

