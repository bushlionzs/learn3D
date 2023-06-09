#include "OgreHeader.h"
#include "OgreScriptLoader.h"
#include "OgreMemoryStream.h"

namespace Ogre {

	ScriptLoader::ScriptLoader()
	{

	}

	ScriptLoader::~ScriptLoader()
	{

	}

	void ScriptLoader::addResourceInfo(ResourceInfo* info)
	{
		mResourceList.push_back(info);
	}

	void ScriptLoader::parserAll()
	{
		for (int32_t i = 0; i < mResourceList.size(); i++)
		{
			auto stream = std::shared_ptr<DataStream>(new MemoryDataStream(mResourceList[i]));
			parseScript(stream, BLANKSTRING);
		}
	}
}