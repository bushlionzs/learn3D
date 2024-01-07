

#include "OgreCEGUIResourceProvider.h"

#include <CEGUIExceptions.h>
#include <ku.h>
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

        Ogre::DataStreamPtr input = 
            Ogre::ResourceManager::getSingleton().openResource(filename.c_str(), orpGroup.c_str());

		if (!input)
		{
            throw InvalidRequestException((utf8*)
                "OgreCEGUIResourceProvider::loadRawDataContainer - Unable to open resource file '" + filename + (utf8*)"' in resource group '" + orpGroup + (utf8*)"'.");
        }

		Ogre::String buf = input->getName();
		size_t buffsz = buf.length();
		unsigned char* mem = NULL;
		if(1==Ogre::Root::getSingleton().getVersionType())
		{
			
			size_t pos = filename.find(".xml");
			if( pos != std::string::npos)
			{
				mem = new unsigned char[buffsz+1];			
				ku::CKU clientUtil;				
				clientUtil.FileConversion(buf.c_str(),(char*)(mem),buffsz);
				mem[buffsz] = 0;
			}	
			else
			{
				mem = new unsigned char[buffsz];	
                memcpy(mem, buf.c_str(), buffsz);		
			}
		}
		else
		{
			mem = new unsigned char[buffsz];	
			memcpy(mem, buf.c_str(), buffsz);	
		}       
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
