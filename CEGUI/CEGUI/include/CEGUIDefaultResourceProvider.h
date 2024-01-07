

#ifndef _CEGUIDefaultResourceProvider_h_
#define _CEGUIDefaultResourceProvider_h_

#include "CEGUIBase.h"
#include "CEGUIResourceProvider.h"



namespace CEGUI
{
class CEGUIEXPORT DefaultResourceProvider : public ResourceProvider
{
public:
	
	DefaultResourceProvider() {}
	~DefaultResourceProvider(void) {}


    void loadRawDataContainer(const String& filename, RawDataContainer& output, const String& resourceGroup);
};

} 

#endif	
