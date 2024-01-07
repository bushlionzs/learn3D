

#ifndef _CEGUIImageset_xmlHandler_h_
#define _CEGUIImageset_xmlHandler_h_

#include "CEGUIImageset.h"
#include "CEGUIXMLHandler.h"


namespace CEGUI
{



class Imageset_xmlHandler : public XMLHandler
{
public:
	
	
	Imageset_xmlHandler(Imageset* imageset) : d_imageset(imageset) {}

	
	virtual ~Imageset_xmlHandler(void) {}

	 
	
    virtual void elementStart(const String& element, const XMLAttributes& attributes);
    virtual void elementEnd(const String& element);

	
	Imageset*	getImageset(void) const				{return d_imageset;}

private:
	
	static const String ImagesetElement;				
	static const String ImageElement;					
	static const char	ImagesetNameAttribute[];		
	static const char	ImagesetImageFileAttribute[];	
    static const char	ImagesetResourceGroupAttribute[];   
	static const char	ImagesetNativeHorzResAttribute[];	
	static const char	ImagesetNativeVertResAttribute[];	
	static const char	ImagesetAutoScaledAttribute[];	
	static const char	ImageNameAttribute[];			
	static const char	ImageXPosAttribute[];			
	static const char	ImageYPosAttribute[];			
	static const char	ImageWidthAttribute[];			
	static const char	ImageHeightAttribute[];			
	static const char	ImageXOffsetAttribute[];		
	static const char	ImageYOffsetAttribute[];		

	
	Imageset*	d_imageset;			
};

} 

#endif	
