
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

        const char* data = input->getStreamData();
        auto size = input->getStreamLength();
		unsigned char* mem = NULL;
		
		mem = new unsigned char[size];
		memcpy(mem, data, size);
		      
        output.setData(mem);
        output.setSize(size);
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
