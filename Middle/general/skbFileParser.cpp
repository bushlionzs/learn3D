#include "OgreHeader.h"
#include "skbFileParser.h"
#include "OgreResourceManager.h"
#include "OgreMemoryStream.h"
#include "OGImpactManager.h"

SkbfileParser::SkbfileParser()
{

}

SkbfileParser::~SkbfileParser()
{

}

String SkbfileParser::getSuffix()
{
	return ".skb";
}

void SkbfileParser::parseScript(
	ResourceInfo* res, const String& groupName)
{
	Orphigine::ImpactManager::getSingleton().parseScript(res, groupName);
}

Real SkbfileParser::getLoadingOrder(void) const
{
	return 1000.0f;
}

