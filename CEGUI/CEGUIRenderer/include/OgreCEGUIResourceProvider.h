

#ifndef _OgreCEGUIResourceProvider_h_
#define _OgreCEGUIResourceProvider_h_

#include <CEGUIResourceProvider.h>
#include "OgreCEGUIRenderer.h"


namespace CEGUI
{
class OGRE_GUIRENDERER_API OgreCEGUIResourceProvider : public ResourceProvider
{
public:
	
	OgreCEGUIResourceProvider();

	~OgreCEGUIResourceProvider(void) {}


    void loadRawDataContainer(const String& filename, RawDataContainer& output, const String& resourceGroup);
    void unloadRawDataContainer(RawDataContainer& output);
};

} 

#endif	
