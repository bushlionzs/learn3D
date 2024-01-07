

#ifndef _CEGUIFont_xmlHandler_h_
#define _CEGUIFont_xmlHandler_h_

#include "CEGUIFont.h"
#include "CEGUIXMLHandler.h"


namespace CEGUI
{


class Font_xmlHandler : public XMLHandler
{
public:
	
	
	Font_xmlHandler(Font* font) : d_font(font) {}

	
	virtual ~Font_xmlHandler(void) {}

	
	
    virtual void elementStart(const String& element, const XMLAttributes& attributes);
    virtual void elementEnd(const String& element);

private:
	
	
	static const String FontElement;					
	static const char	FontNameAttribute[];			
    static const char	FontFilenameAttribute[];		
    static const char	FontResourceGroupAttribute[];   
	static const char	FontTypeAttribute[];			
	static const char	FontSizeAttribute[];			
	static const char	FontFirstCodepointAttribute[];	
	static const char	FontLastCodepointAttribute[];	
	static const char	FontNativeHorzResAttribute[];	
	static const char	FontNativeVertResAttribute[];	
	static const char	FontAutoScaledAttribute[];		
	static const char	FontTextureSizeAttribute[];		
	static const char	FontAntiAliasedAttribute[];		
	
	static const char	FontOutlineAttribute[];
	
	static const char   FontAutoHintAttribute[];
	static const char   FontBoldAttribute[];
	
	static const char   FontMinSizeAttribute[];
	static const char   FontMaxSizeAttribute[];
	
	static const char   FontVertOffsetAttribute[];


	
	Font*	d_font;			
};

} 

#endif
