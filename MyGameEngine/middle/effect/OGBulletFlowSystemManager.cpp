#include "OgreHeader.h"
#include "OGBulletFlowSystemManager.h"
#include "OGBulletEventSystem.h"
#include "OGBulletOperatorFactory.h"
#include "OGBulletDeleterOperatorFactory.h"
#include "OGBulletSpawnOperatorFactory.h"
#include "OGBulletFindTargetTesterFactory.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletSpeedOperatorFactory.h"
#include "OGBulletHeightFieldCollisionTesterFactory.h"
#include "OGBulletForceOperatorFactory.h"
#include "OGBulletBirthOperatorFactory.h"
#include "OGBulletAgeTesterFactory.h"
#include "OGBulletScaleTesterFactory.h"
#include "OGBulletScriptTesterFactory.h"
#include "OGBulletCameraShakeOperatorFactory.h"
#include "OGBulletSpawnTesterFactory.h"
#include "OGBulletSystem.h"
#include "OGBulletSystemManager.h"
#include "platform_log.h"
#include "OgreStringConverter.h"
#include "OgreMemoryStream.h"


template<> Orphigine::BulletFlowSystemManager* Ogre::Singleton<Orphigine::BulletFlowSystemManager>::msSingleton = NULL;

namespace Orphigine
{


	BulletFlowSystemManager::BulletFlowSystemManager()
	{
		m_scriptPatterns.push_back("*.bullet");
		m_operatorFactories.clear();
		m_bulletFlowSystemTemplate.clear();
		m_createBulletFlowCallback = NULL;
		m_afterCreatedBulletSystemCallback = NULL;
		m_beforeDeleteBulletSystemCallback = NULL;
		m_bulletSystemHitTargetCallback = NULL;

		registerOperatorFactories();

		new BulletSystemManager;
	}

	BulletFlowSystemManager::~BulletFlowSystemManager()
	{
		std::map<String,BulletFlowSystem*>::iterator iter;
		for (iter = m_bulletFlowSystemTemplate.begin();iter != m_bulletFlowSystemTemplate.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		m_bulletFlowSystemTemplate.clear();

		std::map<String,BulletOperatorFactory*>::iterator iter2;
		for (iter2 = m_operatorFactories.begin();iter2 != m_operatorFactories.end();iter2 ++)
		{
			delete iter2->second;
			iter2->second = NULL;
		}
		m_operatorFactories.clear();

	}

	String BulletFlowSystemManager::getSuffix( void )
	{
		return ".bullet";
	}

	/*
	 *	bulletflow ...
		{
			eventsystem ...
			{
				operator ...
				{

				}
				.
				.
				.
			}
			eventsystem ...
			{
				operator ...
				{

				}
				.
				.
				.
			}
		}
	 */
	void BulletFlowSystemManager::parseScript(ResourceInfo* res, const String& groupName)
	{
		String line;
		BulletFlowSystem *tmpBulletFlowSystem = NULL;

		std::vector<String> vecparams;
		std::shared_ptr<DataStream> stream = std::make_shared<MemoryDataStream>(res);
		while(!stream->eof())
		{
			line = stream->getLine(true);
			++m_WrongLineNum;

			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{
				vecparams = Ogre::StringUtil::split(line, "\t ");
				if (vecparams.size() < 2)
				{
					//_logErrorInfo("Wrong bulletflow name line", line, "BulletFlowSystemManager::parseScript");
					skipToNextCloseBrace(stream);
				}
				else if ("bulletflow" == vecparams[0])
				{
					skipToNextOpenBrace(stream);
					parseBulletFlowTemplateSegment(vecparams[1],stream,groupName);
				}
				else if ("bulletsystem" == vecparams[0])
				{
					skipToNextOpenBrace(stream);
					BulletSystemManager::getSingleton().parseBulletSystemTemplateSegment(vecparams[1],stream,groupName);
				}
			}
		}
	}

	void BulletFlowSystemManager::reloadParseScript(Ogre::DataStreamPtr& stream, const String& groupName)
	{
		String line;
		BulletFlowSystem *tmpBulletFlowSystem = NULL;

		std::vector<String> vecparams;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++m_WrongLineNum;

			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{
				vecparams = Ogre::StringUtil::split(line, "\t ");
				if (vecparams.size() < 2)
				{
					//_logErrorInfo("Wrong bulletflow name line", line, "BulletFlowSystemManager::parseScript");
					skipToNextCloseBrace(stream);
				}
				else if ("bulletflow" == vecparams[0])
				{
					skipToNextOpenBrace(stream);
					parseBulletFlowTemplateSegment(vecparams[1],stream,groupName, true);
				}
				else if ("bulletsystem" == vecparams[0])
				{
					skipToNextOpenBrace(stream);
					BulletSystemManager::getSingleton().parseBulletSystemTemplateSegment(vecparams[1],stream,groupName, true);
				}
			}
		}
	}

	void BulletFlowSystemManager::parseBulletFlowTemplateSegment( const String& name,
		Ogre::DataStreamPtr& stream, const String& groupName, bool reload )
	{
		String line;
		BulletFlowSystem *tmpBulletFlowSystem = NULL;

		if (reload)
		{
			destroyBulletFlowSystemTemplate(name);
		}

		tmpBulletFlowSystem = createBulletFlowSystemTemplate(name);

		std::vector<String> vecparams;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			++m_WrongLineNum;

			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{
				//if (tmpBulletFlowSystem == NULL)
				//{                   
				//	// 创建了一个空的effect
				//	//tmpBulletFlowSystem = createBulletFlowSystemTemplate(name);
				//	//skipToNextOpenBrace(stream);
				//}				 
				//else
				//{
					if (line == "}")
					{
						tmpBulletFlowSystem = NULL;
						return;
					}
					else if ( line.substr(0,11) == "eventsystem" )
					{
						//解析EventSystem
						vecparams = Ogre::StringUtil::split(line, "\t ");
						if (vecparams.size() < 2)
						{
							//_logErrorInfo("Wrong bulletflow name line", line, "BulletFlowSystemManager::parseBulletFlowTemplateSegment");
							skipToNextCloseBrace(stream);
						}
						skipToNextOpenBrace(stream);
						parseNewBulletEventSystem(vecparams[1],stream,tmpBulletFlowSystem);
					}
					else
					{						
						parseAttrib(line,tmpBulletFlowSystem);
					}					
				//}
			}
		}
	}


	Real BulletFlowSystemManager::getLoadingOrder( void ) const
	{
		return 1000.0f;
	}

	BulletFlowSystem* BulletFlowSystemManager::createBulletFlowSystem( const String& templateName )
	{
		BulletFlowSystem* tmpBulletFlowSystemTemplate = getBulletFlowSystemTemplate(templateName);

		if (NULL == tmpBulletFlowSystemTemplate)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, 
				"Can not find template '" + templateName + "'.", 
				"BulletFlowSystemManager::createBulletFlowSystem");
		}

		BulletFlowSystem* tmpBulletFlowSystem = OGRE_NEW BulletFlowSystem();

		*tmpBulletFlowSystem = *tmpBulletFlowSystemTemplate;

		tmpBulletFlowSystem->createSceneNodeFromBase();

		return tmpBulletFlowSystem;
	}

	BulletFlowSystem* BulletFlowSystemManager::createBulletFlowSystemTemplate( const String& name )
	{
		if (m_bulletFlowSystemTemplate.find(name) != m_bulletFlowSystemTemplate.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"BulletFlowtSystem template with name '" + name + "' already exists.", 
				"BulletFlowSystemManager::createBulletFlowSystemTemplate");
		}

		BulletFlowSystem* tmpBulletFlowSystem = OGRE_NEW BulletFlowSystem();
		addBulletFlowSystemTemplate(name,tmpBulletFlowSystem);
		return tmpBulletFlowSystem;
	}

	void BulletFlowSystemManager::addBulletFlowSystemTemplate( const String& name, BulletFlowSystem* bulletFlowSystem )
	{
		if (m_bulletFlowSystemTemplate.find(name) != m_bulletFlowSystemTemplate.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, 
				"BulletFlowSystem template with name '" + name + "' already exists.", 
				"BulletFlowSystemManager::addBulletFlowSystemTemplate");
		}

		m_bulletFlowSystemTemplate.insert(std::map<String,BulletFlowSystem*>::
			value_type(name,bulletFlowSystem));
	}

	BulletFlowSystem* BulletFlowSystemManager::getBulletFlowSystemTemplate( const String& name )
	{	
		std::map<String,BulletFlowSystem*>::iterator iter = m_bulletFlowSystemTemplate.find(name);

		if (iter == m_bulletFlowSystemTemplate.end())
			return NULL;
		else
			return iter->second;
	}

	BulletOperator* BulletFlowSystemManager::createBulletOperator( const String& typeName,BulletEventSystem* eventSystem)
	{
		std::map<String,BulletOperatorFactory*>::iterator iter = m_operatorFactories.find(typeName);

		if (iter == m_operatorFactories.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "Cannot find requested affector type.", 
				"BulletFlowSystemManager::createBulletOperator");
		}

		return iter->second->createOperator(eventSystem);
	}

	void BulletFlowSystemManager::registerOperatorFactories()
	{
		addBulletOperatorFactory(new BulletDeleterOperatorFactory());
		addBulletOperatorFactory(new BulletSpawnOperatorFactory());
		addBulletOperatorFactory(new BulletFindTargetTesterFactory());
		addBulletOperatorFactory(new BulletSpeedOperatorFactory());
		addBulletOperatorFactory(new BulletHeightFieldTesterFactory());
		addBulletOperatorFactory(new BulletForceOperatorFactory());
		addBulletOperatorFactory(new BulletBirthOperatorFactory());
		addBulletOperatorFactory(new BulletAgeTesterFactory());
		addBulletOperatorFactory(new BulletScaleTesterFactory());
		addBulletOperatorFactory(new BulletScriptTesterFactory());
		addBulletOperatorFactory(new BulletCameraShakeOperatorFactory());
		addBulletOperatorFactory(new BulletSpawnTesterFactory());
	}

	void BulletFlowSystemManager::addBulletOperatorFactory( BulletOperatorFactory* operatorFactory )
	{
		String tmpFactoryName = operatorFactory->getName();

		m_operatorFactories.insert(
			std::map<String,BulletOperatorFactory*>::value_type(tmpFactoryName,operatorFactory));

		//WARNING_LOG("Bullet Operator Type '" 
		//	+ tmpFactoryName + "' registered",Ogre::LML_TRIVIAL);

	}


	//-----------------------------------------------------------------------
	void BulletFlowSystemManager::skipToNextCloseBrace(Ogre::DataStreamPtr& stream)
	{
		String line = "";
		while (!stream->eof() && line != "}")
		{
			line = stream->getLine(true);
			++m_WrongLineNum;
		}

	}
	//-----------------------------------------------------------------------
	void BulletFlowSystemManager::skipToNextOpenBrace(Ogre::DataStreamPtr& stream)
	{
		String line = "";
		while (!stream->eof() && line != "{")
		{
			line = stream->getLine(true);
			++m_WrongLineNum;
		}

	}

	void BulletFlowSystemManager::_logErrorInfo(const String& errorInfo, const String& lineContent, 
		const String& functionName)
	{
		String errorDesc;

		errorDesc += "\n------------OrphigineBulletSystemManager Error Description------------------------";
		errorDesc += "\nfile : " + m_ParsingFileName;
		errorDesc += "\nline : " + Ogre::StringConverter::toString(m_WrongLineNum);
		errorDesc += "\nline content : " + lineContent;
		errorDesc += "\nfunction : " + functionName;
		errorDesc += "\ndescription : " + errorInfo;
		errorDesc += "\n-------------------------------------------------------------------";

		WARNING_LOG(errorDesc.data());
	}

	void BulletFlowSystemManager::parseAttrib( const String& line ,BulletFlowSystem* bulletFlowSystem)
	{
		// Split params on space
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		// Look up first param (command setting)
		if (!bulletFlowSystem->setParameter(vecparams[0], vecparams[1]))
		{
			// BAD command. BAD!
			_logErrorInfo("Bad bullet flow system attrib line", line, "BulletFlowSystemManager::parseAttrib");

		}
	}

	/*
	 *	eventsystem event1
		{
			operator ...
			{

			}
			operator ...
			{

			}
		}
	 */
	void BulletFlowSystemManager::parseNewBulletEventSystem( const String& name,
		Ogre::DataStreamPtr& stream,BulletFlowSystem* bulletFlowSystem)
	{
		BulletEventSystem* tmpEventSystem = bulletFlowSystem->addBulletEventSystem(name);

		String line;
		std::vector<String> vecparams;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{
				if (line == "}")
				{
					// Finished eventsystem
					break;
				}
				else if ("operator" == line.substr(0,8) || 
						"tester" == line.substr(0,6)) 
				{
					//解析EventSystem
					vecparams = Ogre::StringUtil::split(line, "\t ");
					if (vecparams.size() < 2)
					{
						//_logErrorInfo("Wrong operator name line", line, "BulletFlowSystemManager::parseNewBulletEventSystem");
						skipToNextCloseBrace(stream);
					}
					skipToNextOpenBrace(stream);
					parseNewBulletOperator(vecparams[1],stream,tmpEventSystem);

				}
				else
				{
					// Attribute
					//StringUtil::toLowerCase(line);
					parseBulletEventSystemAttrib(line,tmpEventSystem);
				}
			}
		}

	}

	/*
	 *	operator ...
		{
			.
			.
			.
		}
	 */
	void BulletFlowSystemManager::parseNewBulletOperator( const String& name,Ogre::DataStreamPtr& stream,BulletEventSystem* eventSystem)
	{
		BulletOperator* tmpOperator = eventSystem->addBulletOperator(name);

		String line;
		std::vector<String> vecparams;

		while(!stream->eof())
		{
			line = stream->getLine(true);
			// Ignore comments & blanks
			if (!(line.length() == 0 || line.substr(0,2) == "//"))
			{
				if (line == "}")
				{
					// Finished operator
					break;
				}
				else
				{
					// Attribute
					//StringUtil::toLowerCase(line);
					parseBulletOperatorAttrib(line,tmpOperator);
				}
			}
		}
	}

	BulletEventSystem* BulletFlowSystemManager::createBulletEventSystem(const String& name,BulletFlowSystem* flowSystem)
	{
		return OGRE_NEW BulletEventSystem(name,flowSystem);
	}

	void BulletFlowSystemManager::parseBulletOperatorAttrib( const String& line,BulletOperator* bulletOperator )
	{
		// Split params on space
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		if(1 >= vecparams.size())
			return;

		// Look up first param (command setting)
		if (!bulletOperator->setParameter(vecparams[0], vecparams[1]))
		{
			// BAD command. BAD!
			_logErrorInfo("Bad bullet operator attrib line", line, "BulletFlowSystemManager::parseBulletOperatorAttrib");

		}
	}

	void BulletFlowSystemManager::parseBulletEventSystemAttrib( const String& line,BulletEventSystem* bulletEventSystem)
	{
		// Split params on space
		std::vector<String> vecparams = Ogre::StringUtil::split(line, "\t ", 1);

		// Look up first param (command setting)
		if (!bulletEventSystem->setParameter(vecparams[0], vecparams[1]))
		{
			// BAD command. BAD!
			_logErrorInfo("Bad bullet event system attrib line", line, "BulletFlowSystemManager::parseBulletEventSystemAttrib");

		}
	}

	void BulletFlowSystemManager::destroyBulletFlowSystem(BulletFlowSystem* bulletFlowSystem )
	{

		bulletFlowSystem->removeSceneNodeFromParent();
		OGRE_DELETE bulletFlowSystem;
	}

	void BulletFlowSystemManager::destroyBulletOperator( BulletOperator* bulletOperator )
	{
		std::map<String,BulletOperatorFactory*>::iterator iter = m_operatorFactories.find(bulletOperator->getType());

		if (iter == m_operatorFactories.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "Cannot find requested affector type.", 
				"BulletFlowSystemManager::destroyBulletOperator");
		}

		iter->second->destroyOperator(bulletOperator);
	}

	void BulletFlowSystemManager::destroyBulletEventSystem( BulletEventSystem* bulletEventSystem )
	{
		OGRE_DELETE bulletEventSystem;
	}

	CreateBulletFlowCallback* BulletFlowSystemManager::getCreateBulletFlowCallback() const
	{
		return m_createBulletFlowCallback;
	}

	void BulletFlowSystemManager::setCreateBulletFlowCallback( CreateBulletFlowCallback* val )
	{
		m_createBulletFlowCallback = val;
	}

	AfterCreatedBulletSystemCallback* BulletFlowSystemManager::getAfterCreatedBulletSystemCallback() const
	{
		return m_afterCreatedBulletSystemCallback;
	}

	void BulletFlowSystemManager::setAfterCreatedBulletSystemCallback( AfterCreatedBulletSystemCallback* val )
	{
		m_afterCreatedBulletSystemCallback = val;
	}

	BeforeDeleteBulletSystemCallback* BulletFlowSystemManager::getBeforeDeleteBulletSystemCallback() const
	{
		return m_beforeDeleteBulletSystemCallback;
	}

	void BulletFlowSystemManager::setBeforeDeleteBulletSystemCallback( BeforeDeleteBulletSystemCallback* val )
	{
		m_beforeDeleteBulletSystemCallback = val;
	}

	BulletSystemHitTargetCallback* BulletFlowSystemManager::getBulletSystemHitTargetCallback() const
	{
		return m_bulletSystemHitTargetCallback;
	}

	void BulletFlowSystemManager::setBulletSystemHitTargetCallback( BulletSystemHitTargetCallback* val )
	{
		m_bulletSystemHitTargetCallback = val;
	}

	void BulletFlowSystemManager::destroyBulletFlowSystemTemplate( const String& name )
	{
		std::map<String,BulletFlowSystem*>::iterator iter = m_bulletFlowSystemTemplate.find(name);

		if(m_bulletFlowSystemTemplate.end() != iter)
		{
			OGRE_DELETE iter->second;
			iter->second = NULL;
			m_bulletFlowSystemTemplate.erase(iter);
		}
	}
}








