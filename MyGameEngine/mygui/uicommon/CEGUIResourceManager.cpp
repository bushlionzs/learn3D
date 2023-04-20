#include "OgreHeader.h"
#include "CEGUIResourceManager.h"
#include "MyGUI_XmlDocument.h"
#include "MyGUI_DataManager.h"
#include "MyGUI_IDataStream.h"
#include "MyGUI_DataStreamHolder.h"
#include "tinyxml/tinyxml.h"
#include "OgreResourceManager.h"
#include "OgreString.h"
#include "OgreStringConverter.h"

using namespace MyGUI;

template<> CEGUIResourceManager* Ogre::Singleton<CEGUIResourceManager>::msSingleton = 0;

CEGUIResourceManager::CEGUIResourceManager()
{
	
}

CEGUIResourceManager::~CEGUIResourceManager()
{

}

bool CEGUIResourceManager::load(const std::string& name)
{
	auto res = Ogre::ResourceManager::getSingleton().getResource(name);

	TiXmlDocument doc;
	doc.LoadFile(res->_fullname.c_str());

	TiXmlElement* pRoot = doc.RootElement();

	while (pRoot != nullptr)
	{
		const char* aa = pRoot->Value();

		if (strcmp(aa, "Imageset") == 0)
		{
			const char* Name = pRoot->Attribute("Name");
			bool icon = false;
			

			CEGUIImageSet* imageset = new CEGUIImageSet;
			mGroupMap.emplace(Name, imageset);
			
			auto itor = mGroupMap.find(Name);


			const char* imagefile = pRoot->Attribute("Imagefile");

			if (strncmp(imagefile, "Icons", 5) == 0)
			{
				imagefile += 6;
				icon = true;
			}

			imageset->_mageFilename = imagefile;

			TiXmlElement* child = pRoot->FirstChildElement();

			const char* value;
			CEGUIImage item;
			while (child != nullptr)
			{

				Name = child->Attribute("Name");
				item._imagename = imageset->_mageFilename;
				value = child->Attribute("XPos");
				
				item._coord.left = Ogre::StringConverter::parseInt(value);
				value = child->Attribute("YPos");
				item._coord.top = Ogre::StringConverter::parseInt(value);
				value = child->Attribute("Width");
				item._size.width = Ogre::StringConverter::parseInt(value);
				value = child->Attribute("Height");
				item._size.height = Ogre::StringConverter::parseInt(value);
				item._coord.width = item._coord.left + item._size.width;
				item._coord.height = item._coord.top + item._size.height;
				imageset->_imageMap.emplace(Name, item);
				child = child->NextSiblingElement();

				if (icon)
				{
					mIconMap[Name] = imageset;
				}
			}
		}

		

		pRoot = pRoot->NextSiblingElement();
	}
	return true;
}

static CEGUIImage dummy;
CEGUIImage& CEGUIResourceManager::getImageInfo(
	const String& imageset, const String& imagename)
{
	auto itor = mGroupMap.find(imageset);
	if (itor != mGroupMap.end())
	{
		auto itor2 = itor->second->_imageMap.find(imagename);

		if (itor2 != itor->second->_imageMap.end())
		{
			return itor2->second;
		}
	}

	return dummy;
}

CEGUIImage& CEGUIResourceManager::getIconImageInfo(const String& iconname)
{
	auto itor = mIconMap.find(iconname);
	if (itor != mIconMap.end())
	{
		auto itor2 = itor->second->_imageMap.find(iconname);

		if (itor2 != itor->second->_imageMap.end())
		{
			return itor2->second;
		}
	}

	return dummy;
}