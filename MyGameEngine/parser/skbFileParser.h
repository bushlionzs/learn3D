#pragma once

#include "OgreScriptLoader.h"

class SkbfileParser : public ScriptLoader
{
public:
	SkbfileParser();
	~SkbfileParser();
	virtual String getSuffix();
	virtual void parseScript(ResourceInfo* res, const String& groupName);
	virtual Real getLoadingOrder(void) const;


private:
	std::vector<std::shared_ptr<DataStream>> mPackList;

	std::unordered_map<String, Ogre::StreamContent> mPackMap;
};