#pragma once

#include "OgreScriptLoader.h"

class PackfileParser : public ScriptLoader, public PackFileBase
{
public:
	PackfileParser();
	~PackfileParser();
	virtual String getSuffix();
	virtual void parseScript(DataStreamPtr& stream, const String& groupName);
	virtual Real getLoadingOrder(void) const;

	Ogre::StreamContent* getPackfile(
		const String& name, const String& group);

private:
	std::shared_ptr<DataStream> mSourceFile;

	std::unordered_map<String, Ogre::StreamContent> mPackMap;
};