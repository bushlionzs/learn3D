
#include <OgreHeader.h>
#include "OgreCEGUIResourceProvider.h"

#include <CEGUIExceptions.h>
#include <OgreRoot.h>
#include <OgreResourceManager.h>


namespace CEGUI
{
    OgreCEGUIResourceProvider::OgreCEGUIResourceProvider() : ResourceProvider()
    {
        d_defaultResourceGroup = Ogre::ResourceManager::DEFAULT_RESOURCE_GROUP_NAME.c_str();
    }

    void OgreCEGUIResourceProvider::loadRawDataContainer(const String& filename, RawDataContainer& output,  const String& resourceGroup)
    {
        String orpGroup;
        if (resourceGroup.empty())
            orpGroup = d_defaultResourceGroup.empty() ? Ogre::ResourceManager::DEFAULT_RESOURCE_GROUP_NAME.c_str() : d_defaultResourceGroup;
        else
            orpGroup = resourceGroup;

        auto input = 
            Ogre::ResourceManager::getSingleton().openResource(filename.c_str(), orpGroup.c_str());

		if (!input)
		{
            throw InvalidRequestException((utf8*)
                "OgreCEGUIResourceProvider::loadRawDataContainer - Unable to open resource file '" + filename + (utf8*)"' in resource group '" + orpGroup + (utf8*)"'.");
        }

		auto& buf = input->getName();
		size_t buffsz = buf.length();
		unsigned char* mem = NULL;
		
		mem = new unsigned char[buffsz];	
		memcpy(mem, buf.c_str(), buffsz);	
		      
        output.setData(mem);
        output.setSize(buffsz);
    }
	
	void OgreCEGUIResourceProvider::unloadRawDataContainer(RawDataContainer& data)
	{
		if (data.getDataPtr())
		{
			delete[] data.getDataPtr();
			data.setData(0);
			data.setSize(0);
		}
	}
} 
