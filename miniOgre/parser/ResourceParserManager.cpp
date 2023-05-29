#include "OgreHeader.h"
#include "ResourceParserManager.h"
#include "OgreScriptLoader.h"
#include "MaterialScriptParser.h"
#include "ParticleScriptParser.h"
#include "OGImpactManager.h"
#include "OgreResourceManager.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGAdvancedAnimationSystemManager.h"
#include "shaderManager.h"
#include "packFileParser.h"
#include "WowResourceParser.h"
#include "platform_file_system.h"
#include "skbFileParser.h"
#include "OGBulletFlowSystemManager.h"
#include "OGSpellManager.h"
namespace Ogre {

	template<> ResourceParserManager* Ogre::Singleton<ResourceParserManager>::msSingleton = 0;

	ResourceParserManager::ResourceParserManager()
	{

	}

	ResourceParserManager::~ResourceParserManager()
	{

	}

	bool ResourceParserManager::_initialise()
	{
		new Orphigine::AdvancedAnimationSystemManager;
		new ShaderManager;
		new Orphigine::SpellManager;
		registerParser(new MaterialScriptParser);
		registerParser(new ParticleScriptParser);
		registerParser(new Orphigine::ImpactManager);
		registerParser(new SkbfileParser);
		registerParser(Orphigine::SkeletonMeshComponentManager::getSingletonPtr());
		registerParser(Orphigine::AdvancedAnimationSystemManager::getSingletonPtr());
		registerParser(ShaderManager::getSingletonPtr());
		registerParser(new PackfileParser);
		registerParser(new WowResourceParser);
		registerParser(new Orphigine::BulletFlowSystemManager);
		return true;
	}

	bool ResourceParserManager::parserAll()
	{
		std::vector<ScriptLoader*> loaderlist;
		loaderlist.reserve(mResourceParserMap.size());
		for (auto& res : mResourceParserMap)
		{
			loaderlist.push_back(res.second);
		}
		std::sort(loaderlist.begin(), loaderlist.end(), [](ScriptLoader* src, ScriptLoader* dst)
		{
			return src->getLoadingOrder() < dst->getLoadingOrder();
		}
		);
		
		std::for_each(loaderlist.begin(), loaderlist.end(), [](ScriptLoader* loader)
		{
			loader->parserAll();
		});



		/*auto stream = ResourceManager::getSingletonPtr()->openResource("cj_csjj_01.efb", BLANKSTRING);
		Orphigine::ImpactManager::getSingletonPtr()->parseScript(stream, BLANKSTRING);*/
		return true;
	}

	bool ResourceParserManager::registerParser(ScriptLoader* loader)
	{
		String suffix = loader->getSuffix();

		auto itor = mResourceParserMap.find(suffix);

		if (itor != mResourceParserMap.end())
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "parser already exists");
		}

		mResourceParserMap[suffix] = loader;
		return true;
	}


	ScriptLoader* ResourceParserManager::getLoader(const String& name)
	{
		auto itor = mResourceParserMap.find(name);
		if (itor != mResourceParserMap.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	
}