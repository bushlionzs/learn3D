

#ifndef _CEGUIResourceProvider_h_
#define _CEGUIResourceProvider_h_

#include "CEGUIBase.h"
#include "CEGUIDataContainer.h"
#include "CEGUIString.h"



namespace CEGUI
{

class CEGUIEXPORT ResourceProvider
{
public:
	
    
	ResourceProvider() { }

    
	virtual ~ResourceProvider(void) { }

    













    
    virtual void loadRawDataContainer(const String& filename, RawDataContainer& output, const String& resourceGroup) = 0;

    
    virtual void unloadRawDataContainer(RawDataContainer& data)  { }

    
    const String&   getDefaultResourceGroup(void) const     { return d_defaultResourceGroup; }
    
    
    void    setDefaultResourceGroup(const String& resourceGroup)    { d_defaultResourceGroup = resourceGroup; }

protected:
    String  d_defaultResourceGroup;     
};

} 

#endif	
