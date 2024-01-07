

#include "CEGUIRenderer.h"
#include "CEGUIEventSet.h"
#include "CEGUIEvent.h"
#include "CEGUIDefaultResourceProvider.h"



namespace CEGUI
{
const String Renderer::EventNamespace("Renderer");


const String Renderer::EventDisplaySizeChanged( (utf8*)"DisplayModeChanged" );



const float	Renderer::GuiZInitialValue		= 1.0f;
const float	Renderer::GuiZElementStep		= 0.0001f;		
const float	Renderer::GuiZLayerStep			= 0.0001f;		



Renderer::Renderer(void)
    : d_resourceProvider(0),
      d_identifierString("Unknown renderer (vendor did not set the ID string!)")
{
	
	addEvent(EventDisplaySizeChanged);

	
	resetZValue();
}


Renderer::~Renderer(void)
{
    if(d_resourceProvider)
    {
        delete d_resourceProvider;
        d_resourceProvider = 0;
    }
}

ResourceProvider* Renderer::createResourceProvider(void)
{
    d_resourceProvider = new DefaultResourceProvider();
    return d_resourceProvider;
}

const String& Renderer::getIdentifierString() const
{
    return d_identifierString;
}

} 
