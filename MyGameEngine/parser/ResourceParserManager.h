#pragma once

#include "OgreSingleton.h"

namespace Ogre {
	class ResourceParserManager : public Ogre::Singleton<ResourceParserManager>
	{
	public:
		ResourceParserManager();
		~ResourceParserManager();

		bool _initialise();

		bool parserAll();

		bool registerParser(ScriptLoader* loader);

		ScriptLoader* getLoader(const String& name);
	private:
		std::unordered_map<String, ScriptLoader*> mResourceParserMap;
	};
}
