

#include "CEGUIFont_xmlHandler.h"

#include "CEGUIExceptions.h"
#include "CEGUIImageset.h"
#include "CEGUILogger.h"
#include "CEGUIXMLAttributes.h"

#include <ft2build.h>
#include FT_FREETYPE_H



namespace CEGUI
{




const String Font_xmlHandler::FontElement( (utf8*)"Font" );
const char	Font_xmlHandler::FontNameAttribute[]			= "Name";
const char	Font_xmlHandler::FontFilenameAttribute[]		= "Filename";
const char	Font_xmlHandler::FontResourceGroupAttribute[]   = "ResourceGroup";
const char	Font_xmlHandler::FontTypeAttribute[]			= "Type";
const char	Font_xmlHandler::FontSizeAttribute[]			= "Size";
const char	Font_xmlHandler::FontNativeHorzResAttribute[]	= "NativeHorzRes";
const char	Font_xmlHandler::FontNativeVertResAttribute[]	= "NativeVertRes";
const char	Font_xmlHandler::FontAutoScaledAttribute[]		= "AutoScaled";
const char	Font_xmlHandler::FontTextureSizeAttribute[]		= "TextureSize";
const char	Font_xmlHandler::FontAntiAliasedAttribute[]		= "AntiAlias";

const char	Font_xmlHandler::FontOutlineAttribute[]			= "Outline";

const char  Font_xmlHandler::FontAutoHintAttribute[]        = "AutoHint";
const char  Font_xmlHandler::FontBoldAttribute[]            = "Bold";

const char  Font_xmlHandler::FontMinSizeAttribute[]         = "MinSize";
const char  Font_xmlHandler::FontMaxSizeAttribute[]         = "MaxSize";

const char  Font_xmlHandler::FontVertOffsetAttribute[]         = "VertOffset";






void Font_xmlHandler::elementStart(const String& element, const XMLAttributes& attributes)
{
	if (element == FontElement)
	{
		
		String font_name(attributes.getValueAsString(FontNameAttribute));

		
        String filename(attributes.getValueAsString(FontFilenameAttribute));
        
        String resourceGroup(attributes.getValueAsString(FontResourceGroupAttribute));

		Logger::getSingleton().logEvent("Started creation of Font '" + font_name + "' via XML file.", Informative);

		
		
		
		float hres, vres;
		bool auto_scale;

		
        hres = (float)attributes.getValueAsInteger(FontNativeHorzResAttribute, 1024);
		
        vres = (float)attributes.getValueAsInteger(FontNativeVertResAttribute, 768);
		
		uint size = (uint)attributes.getValueAsInteger(FontSizeAttribute, 12);

		
		d_font->setNativeResolution(Size(hres, vres));

		
		auto_scale = attributes.getValueAsBool(FontAutoScaledAttribute, true);

		
		d_font->setAutoScalingEnabled(auto_scale);

		int textureSize = attributes.getValueAsInteger(FontTextureSizeAttribute, 512);
		d_font->setTextureSize(textureSize);

		
		int bOutline = attributes.getValueAsInteger(FontOutlineAttribute, 0);
		d_font->setOutline(bOutline==0 ? false : true);

		
		int bAutoHint = attributes.getValueAsInteger(FontAutoHintAttribute, 0);
		d_font->setAutoHint(bAutoHint);

		int bBold = attributes.getValueAsInteger(FontBoldAttribute, 0);
		d_font->setBold(bBold==0 ? false : true);

		
		int bMinSize = attributes.getValueAsInteger(FontMinSizeAttribute, 10);
		d_font->setMinSize(bMinSize);
		int bMaxSize = attributes.getValueAsInteger(FontMaxSizeAttribute, 50);
		if(bMaxSize < bMinSize) 
			bMaxSize = bMinSize;
		d_font->setMaxSize(bMaxSize);

		int vertOffset = attributes.getValueAsInteger(FontVertOffsetAttribute, 0);
		d_font->setFontVertOffset(vertOffset);
		
		
		d_font->constructor_impl(font_name, filename, resourceGroup, size);
	}
	
	else
	{
		throw FileIOException("Font::xmlHandler::startElement - Unexpected data was found while parsing the Font file: '" + element + "' is unknown.");
	}

}

void Font_xmlHandler::elementEnd(const String& element)
{
	if (element == FontElement)
	{
		Logger::getSingleton().logEvent("Finished creation of Font '" + d_font->d_name + "' via XML file.", Informative);
	}

}

} 
