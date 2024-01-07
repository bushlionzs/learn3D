

#include "CEGUIFont.h"
#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUIFontManager.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUITexture.h"
#include "CEGUILogger.h"
#include "CEGUITextUtils.h"
#include "CEGUIFont_xmlHandler.h"
#include "CEGUIResourceProvider.h"
#include "CEGUIXMLParser.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIHyperLinkManager.h"
#include "CEGUIWindow.h"



namespace CEGUI
{

const argb_t	Font::DefaultColour			= 0xFFFFFFFF;
const uint		Font::InterGlyphPadSpace	= 2;
const uint		Font::FontGlyphImagesetSize	= 512;
const uint		Font::LineSpace				= 3;

const utf32		UnderlineCharCode				= 0x5F;

static colour	g_curTextColor					= 0;	
static colour	g_curTextBakColor				= 0;
static colour	g_curHyperLinkColor				= 0;
static int		g_isHyperLinkNow				= 0;
static String	g_keyHyperLink					= "";
static int		g_isKeyHyperLink				= 0;
static int		g_keyHyperLinkMaxCount			= 0;

static bool		g_isBlink						= false;
static bool		g_isUnderline					= false;


const char		Font::FontSchemaName[]		= "Font.xsd";

const char		Font::DefaultPrepareString[]= "\xE5\x95\x8A a"; 

class Window;

Font::Font(const String& filename, const String& resourceGroup) :
	d_currentGlyphImageset(0),
    d_lineHeight(0),
    d_lineSpacing(0),
	d_outlineSpacing(1), 
    d_max_bearingY(0),
    d_maxGlyphHeight(0),
	d_ptSize(0),
	d_ptNext_X(0),
	d_ptNext_Y(0),
	d_autoScale(false),
    d_horzScaling(1.0f),
    d_vertScaling(1.0f),
    d_nativeHorzRes(DefaultNativeHorzRes),
	d_nativeVertRes(DefaultNativeVertRes),
	d_bold(false)
{
	d_textureSize = 512;
	d_underlineImage = NULL;

	
	d_minSize = 10;
	d_maxSize = 50;
}


void Font::load(const String& filename, const String& resourceGroup)
{
	
	unload();


	if (filename.empty() || (filename == (utf8*)""))
	{
		throw InvalidRequestException((utf8*)"Font::load - Filename supplied for Font loading must be valid");
	}

    
    Font_xmlHandler handler(this);

	
	try
	{
        System::getSingleton().getXMLParser()->parseXMLFile(handler, filename, FontSchemaName, resourceGroup);
	}
	catch(...)
	{
		unload();

        Logger::getSingleton().logEvent("Font::load - loading of Font from file '" + filename +"' failed.", Errors);
		throw;
	}
}



Font::~Font(void)
{
	unload();
}


void Font::unload(void)
{
	clearAllFontFaces();
}


void Font::notifyScreenResolution(const Size& size)
{	
	d_underlineImage = NULL;

	GlyphImagesetList::iterator it, end = d_listGlyphImagesets.end();
	
	for(it=d_listGlyphImagesets.begin(); it!=end; it++)
	{
		glyphImageset* thisGlyph = *it;

		if(thisGlyph->d_imageset)
		{
			thisGlyph->d_imageset->notifyScreenResolution(size);
		}
	}

	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
#else	
		GlyphImagesetList::iterator it, end = d_listGlyphImagesetsOutline.end();
		
		for(it=d_listGlyphImagesetsOutline.begin(); it!=end; it++)
		{
			glyphImageset* thisGlyph = *it;

			if(thisGlyph->d_imageset)
			{
				thisGlyph->d_imageset->notifyScreenResolution(size);
			}
		}
#endif
	}

	d_horzScaling = size.d_width / d_nativeHorzRes;
	d_vertScaling = size.d_height / d_nativeVertRes;

	if (FreeType == getType() && d_autoScale)
	{
		resetFontFaces();
	}
}


void Font::setNativeResolution(const Size& size)
{
	d_nativeHorzRes = size.d_width;
	d_nativeVertRes = size.d_height;

	
	if(Bitmap == getType())
	{
		GlyphImagesetList::iterator it, end = d_listGlyphImagesets.end();
		
		for(it=d_listGlyphImagesets.begin(); it!=end; it++)
		{
			glyphImageset* thisGlyph = *it;

			if(thisGlyph->d_imageset)
			{
				thisGlyph->d_imageset->setNativeResolution(size);
			}
		}
	}
	
	notifyScreenResolution(System::getSingleton().getRenderer()->getSize());
}


void Font::setAutoScalingEnabled(bool setting)
{
	if (FreeType == getType() && setting != d_autoScale)
	{
		d_autoScale = setting;
		resetFontFaces();
	}
}


void Font::prepareString(const String& text)
{
	if(text.empty()) return;
	size_t char_count = text.length();

	CodepointMap::const_iterator end = d_cp_map.end();
	for (size_t c = 0; c < char_count; ++c)
	{
		utf32 code = text[c];

		
		if(code==(utf32)'\r' || code==(utf32)'\n') continue;
		utf32 control_value = (code>>24)&0XFF;
		if(control_value > 0)	continue;

		
		if(d_cp_map.find(code) == end)
		{
			createFontGlyph(code);
		}
	}

}



void Font::prepareFontTexture(void)
{
	GlyphImagesetList::iterator it, end = d_listGlyphImagesets.end();
	
	for(it=d_listGlyphImagesets.begin(); it!=end; it++)
	{
		glyphImageset* thisGlyph = *it;

		
		if(thisGlyph->d_dirty)
		{
			thisGlyph->d_imageset->getTexture()->loadFromMemoryLA(
				thisGlyph->d_memory, d_textureSize, d_textureSize);
			thisGlyph->d_dirty = false;
		}
	}

	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
#else
		GlyphImagesetList::iterator it, end = d_listGlyphImagesetsOutline.end();
		
		for(it=d_listGlyphImagesetsOutline.begin(); it!=end; it++)
		{
			glyphImageset* thisGlyph = *it;

			
			if(thisGlyph->d_dirty)
			{
				thisGlyph->d_imageset->getTexture()->loadFromMemoryLA(
					thisGlyph->d_memory, d_textureSize, d_textureSize);
				thisGlyph->d_dirty = false;
			}
		}
#endif
	}
}


void Font::clearAllFontFaces(void)
{
	
	d_cp_map.clear();

	
	GlyphImagesetList::iterator it, end = d_listGlyphImagesets.end();
	for(it=d_listGlyphImagesets.begin(); it!=end; it++)
	{
		glyphImageset* thisGlyph = *it;

		delete[] thisGlyph->d_memory;
		thisGlyph->d_memory = NULL;

		thisGlyph->d_imageset->undefineAllImages();
		ImagesetManager::getSingleton().destroyImageset(thisGlyph->d_imageset->getName());

		delete thisGlyph;
	}

	d_listGlyphImagesets.clear();
	d_currentGlyphImageset = 0;


	if(d_outline)
	{
		d_ptNext_X = d_ptNext_Y = d_outlineSpacing;
	}
	else
	{
		d_ptNext_X = d_ptNext_Y = 0;
	}

	d_maxGlyphHeight = 0;
	d_max_bearingY = 0;
	d_lineSpacing = 0;
	d_lineHeight = 0;

	
	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
#else
		GlyphImagesetList::iterator it, end = d_listGlyphImagesetsOutline.end();
		for(it=d_listGlyphImagesetsOutline.begin(); it!=end; it++)
		{
			glyphImageset* thisGlyph = *it;

			delete [] thisGlyph->d_memory;
			thisGlyph->d_memory = NULL;

			thisGlyph->d_imageset->undefineAllImages();
			ImagesetManager::getSingleton().destroyImageset(thisGlyph->d_imageset->getName());

			delete thisGlyph;
		}
		d_listGlyphImagesetsOutline.clear();
		d_currentGlyphImagesetOutline = 0;
#endif
	}


}


Font::glyphImageset* Font::createFontImageset(void)
{
	
	if(d_currentGlyphImageset)
	{
		d_currentGlyphImageset->d_dirty = true;
	}

	
	d_currentGlyphImageset = new glyphImageset;
	d_currentGlyphImageset->d_dirty = true;

	
	d_currentGlyphImageset->d_memory = new uint16[d_textureSize * d_textureSize];
	memset(d_currentGlyphImageset->d_memory, 0, ((d_textureSize * d_textureSize) * sizeof(uint16)));

	
	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
#else	
		d_currentGlyphImagesetOutline = new glyphImageset;
		d_currentGlyphImagesetOutline->d_dirty = true;
		d_currentGlyphImagesetOutline->d_memory = new uint16[d_textureSize * d_textureSize];
		memset(d_currentGlyphImagesetOutline->d_memory, 0, ((d_textureSize * d_textureSize) * sizeof(uint16)));
#endif
	}

	
	char szTemp[260] = {0};
	_snprintf(szTemp, 260, "%s_bigchar_%d", d_name.c_str(), (int)d_listGlyphImagesets.size());
	d_currentGlyphImageset->d_imageset = 
		ImagesetManager::getSingleton().createImageset( 
			String(szTemp), 
			System::getSingleton().getRenderer()->createTexture(float(d_textureSize)));
	d_currentGlyphImageset->d_imageset->setAutoFree( false );
	d_currentGlyphImageset->d_imageset->setAutoScalingEnabled( false );
	d_currentGlyphImageset->d_imageset->setTextureLoadDelay( false );
	d_currentGlyphImageset->d_imageset->defineImage(
		"view", Point( 0.0f, 0.0f ), 
		Size((float)d_textureSize, (float)d_textureSize ), 
		Point(0.0f, 0.0f));

	
	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
#else	
		_snprintf(szTemp, 260, "_%s_bigchar_%d_", d_name.c_str(), (int)d_listGlyphImagesets.size());
		d_currentGlyphImagesetOutline->d_imageset = ImagesetManager::getSingleton().createImageset( 
				String(szTemp), 
				System::getSingleton().getRenderer()->createTexture(float(d_textureSize)));
		d_currentGlyphImagesetOutline->d_imageset->setAutoFree( false );
		d_currentGlyphImagesetOutline->d_imageset->setAutoScalingEnabled( false );
		d_currentGlyphImagesetOutline->d_imageset->setTextureLoadDelay( false );
		d_currentGlyphImagesetOutline->d_imageset->defineImage(
			"view", Point( 0.0f, 0.0f ), 
			Size((float)d_textureSize, (float)d_textureSize ), 
			Point(0.0f, 0.0f));
#endif
	}

	d_listGlyphImagesets.push_back(d_currentGlyphImageset);

	if(d_outline)
	{
		d_ptNext_X = d_ptNext_Y = d_outlineSpacing;
#if OUTLINE_USE_SAME_TEXTURE
#else
		d_listGlyphImagesetsOutline.push_back(d_currentGlyphImagesetOutline);
#endif
	}
	else
	{
		d_ptNext_X = d_ptNext_Y = 0;
	}

	return d_currentGlyphImageset;
}


float Font::getTextExtent(const String& text, float x_scale, utf32* color, utf32* bakColor, bool bNeedPrepare) const
{
	
	if(bNeedPrepare)
		((Font*)this)->prepareString(text);
	
	x_scale = x_scale*getXScale();

    float cur_extent = 0, adv_extent = 0;
	const String KeyParserBegin	= "{";
	const String KeyParserEnd	= "}";

	bool bIsKeyHyperLink = false, bIsHyperLink = false;

    size_t char_count = text.length();
    CodepointMap::const_iterator pos, end = d_cp_map.end();

    for (size_t c = 0; c < char_count; ++c)
    {
        pos = d_cp_map.find(text[c]);

        if (pos != end)
        {
			if(bIsHyperLink)
			{
				if(text[c] == KeyParserBegin[0])
				{
					bIsKeyHyperLink = true;
					continue;
				}
				else if(text[c] ==KeyParserEnd[0])
				{
					bIsKeyHyperLink = false;
					continue;
				}
				else if(bIsKeyHyperLink)
				{
					continue;
				}
			}
            
            adv_extent += (float)pos->second.d_horz_advance * x_scale;
			
        }
		else
		{

			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type = (text[c] >> 24)&0xFF;
			switch(type)
			{
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;

					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id)) break;
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);

					adv_extent += (float)animate->getSize().d_width * x_scale;
				}
				break;
			case 0xFD:
				{
					bIsHyperLink = true;
				}
				break;
			case 0xFE:
				{
					bIsHyperLink = false;
				}
				break;
			case 0xE4:
				break;
			case 0xFC:
				{
					if (bakColor)
						*bakColor = value + 0xFC000000;
				}
				break;
			case 0xFB:
				{
					if(color)
						*color	= value + 0xFF000000;
				}
				break;
			default:
				break;
			}
		}

    }

    return std::max(adv_extent, cur_extent);
}


float Font::getFormattedTextExtent(const String& text, const Rect& format_area, TextFormatting fmt, float x_scale) const
{
	float lineWidth;
	float widest = 0;

	size_t lineStart = 0, lineEnd = 0;
	String	currLine;

	while (lineEnd < text.length())
	{
		if ((lineEnd = text.find_first_of('\n', lineStart)) == String::npos)
		{
			lineEnd = text.length();
		}

		currLine = text.substr(lineStart, lineEnd - lineStart);
		lineStart = lineEnd + 1;	

		switch(fmt)
		{
		case Centred:
		case RightAligned:
		case LeftAligned:
			lineWidth = getTextExtent(currLine, x_scale);
			break;

		case Justified:
			
			lineWidth = std::max(format_area.getWidth(), getTextExtent(currLine, x_scale));
			break;

		case WordWrapLeftAligned:
		case WordWrapRightAligned:
		case WordWrapCentred:
			lineWidth = getWrappedTextExtent(currLine, format_area.getWidth(), x_scale);
			break;

		case WordWrapJustified:
			
			lineWidth = std::max(format_area.getWidth(), getWrappedTextExtent(currLine, format_area.getWidth(), x_scale));
			break;

		default:
			throw InvalidRequestException((utf8*)"Font::getFormattedTextExtent - Unknown or unsupported TextFormatting value specified.");
		}

		if (lineWidth > widest)
		{
			widest = lineWidth;
		}

	}

	return widest;
}



float Font::getWrappedTextExtent(const String& text, float wrapWidth, float x_scale) const
{
	float lineWidth = getTextExtent(text, x_scale);
	if( lineWidth > wrapWidth )
		return wrapWidth;
	return lineWidth;
}


size_t Font::getCharAtPixel(const String& text, size_t start_char, float pixel, float x_scale) const
{
	float cur_extent = 0;
	size_t char_count = text.length();

	x_scale = x_scale*getXScale();
	
	if ((pixel <= 0) || (char_count <= start_char))
	{
		return start_char;
	}

	CodepointMap::const_iterator pos, end = d_cp_map.end();

	for (size_t c = start_char; c < char_count; ++c)
	{
		pos = d_cp_map.find(text[c]);

		if (pos != end)
		{
			cur_extent += (float)pos->second.d_horz_advance * x_scale;

			if (pixel < cur_extent)
			{
				return c;
			}

		}
		
		else
		{
			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type  = (text[c] >> 24)&0xFF;

			switch(type)
			{
			
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;

					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id)) break;

					const KeyImageAnimation *animate = KeyImageAnimationManager::getSingleton().getAnimate(id);
					cur_extent += animate->getSize().d_width;

					if (pixel < cur_extent)
					{
						return c;
					}
				}
				break;

			default:
				break;
			}

		}

	}

	return char_count;
}


Size Font::getFormattedSize(const String& text, const Rect& draw_area, TextFormatting fmt, float x_scale, float y_scale, bool bSingleLine) const
{
	Size szRet(0.0f, 0.0f), sz;
	if(text.empty()) return szRet;

	Rect tmpDrawArea(
		PixelAligned(draw_area.d_left),
		PixelAligned(draw_area.d_top),
		PixelAligned(draw_area.d_right),
		PixelAligned(draw_area.d_bottom)
		);

	size_t lineStart = 0, lineEnd = 0;
	String	currLine;

	while (lineEnd < text.length())
	{
#if OPTIMIZE_DAMAGE
		
		if(bSingleLine)
		{
			lineEnd = text.length();
			currLine = text;
		}
		else
		{
#endif
			if(lineStart != 0) 
			{
				szRet.d_height += LineSpace;
			}

			if ((lineEnd = text.find_first_of('\n', lineStart)) == String::npos)
			{
				lineEnd = text.length();
			}

			currLine = text.substr(lineStart, lineEnd - lineStart);
			lineStart = lineEnd + 1;	

#if OPTIMIZE_DAMAGE
		}
#endif

		switch(fmt)
		{
		case LeftAligned:
		case RightAligned:
		case Centred:
		case Justified:
			sz = getLineSize(currLine, x_scale, y_scale);
			break;

		case WordWrapLeftAligned:
		case WordWrapRightAligned:
		case WordWrapCentred:
		case WordWrapJustified:
			sz = getWrappedSize(currLine, tmpDrawArea, x_scale, y_scale);
			
			break;

		default:
			throw InvalidRequestException((utf8*)"Font::drawText - Unknown or unsupported TextFormatting value specified.");
		}

		szRet.d_height += sz.d_height;
		szRet.d_width = std::max(szRet.d_width, sz.d_width);
	}


	return szRet;
}


#if OPTIMIZE_DAMAGE
Size Font::getWrappedSize(const String& text, const Rect& draw_area, float x_scale, float y_scale) const
{
	Size szRet( 0, 0 );
	float	wrap_width = draw_area.getWidth();
	((Font*)this)->prepareString(text);

	float adv_extent = 0.f, max_extent = 0.f, cur_extent = 0.f;
	float maxHeight = getFontHeight(), height;

    size_t char_count = text.length();
    CodepointMap::const_iterator pos, end = d_cp_map.end();

	const String KeyParserBegin	= "{";
	const String KeyParserEnd	= "}";
	bool bIsKeyHyperLink = false, bIsHyperLink = false;

    for (size_t c = 0; c < char_count; ++c)
    {
        pos = d_cp_map.find(text[c]);

		if( pos != d_cp_map.end() )
		{
			if(bIsHyperLink)
			{
				if(text[c] == KeyParserBegin[0])
				{
					bIsKeyHyperLink = true;
					continue;
				}
				else if(text[c] ==KeyParserEnd[0])
				{
					bIsKeyHyperLink = false;
					continue;
				}
				else if(bIsKeyHyperLink)
				{
					continue;
				}
			}

			cur_extent = ((float)pos->second.d_horz_advance * x_scale);
			adv_extent += cur_extent;
			if(adv_extent > max_extent)
				max_extent = adv_extent;

			const Image* img = pos->second.d_image;
			height = img->getHeight() * y_scale*getYScale();
			if(height > maxHeight) maxHeight = height;
		}
		else
		{
			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type = (text[c] >> 24)&0xFF;
			switch(type)
			{
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;
					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id)) break;
 
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);

					height = animate->getSize().d_height;
					if(height > maxHeight) maxHeight = height;

					cur_extent = (float)animate->getSize().d_width * x_scale;
					adv_extent += cur_extent;
					if(adv_extent > max_extent)
						max_extent = adv_extent;
				}
				break;
			case 0xFD:
				{
					bIsHyperLink = true;
				}
				break;
			case 0xFE:
				{
					bIsHyperLink = false;
				}
				break;
			default:
				break;
			}
		}
		
		if( adv_extent > wrap_width )
		{
			--c;
			max_extent -= cur_extent;
			//adv_extent = (float)pos->second.d_horz_advance * x_scale*getXScale();
			adv_extent = 0;
			szRet.d_height += maxHeight + LineSpace;
			maxHeight = height;
		}
    }

	szRet.d_width = max_extent;
	szRet.d_height += maxHeight;
	return szRet;
}
#else
Size Font::getWrappedSize(const String& text, const Rect& draw_area, float x_scale, float y_scale) const
{
	Size szRet( 0, 0 );
	float	wrap_width = draw_area.getWidth();
	((Font*)this)->prepareString(text);

    float cur_extent = 0;
	float maxHeight = getFontHeight(), height;

    size_t char_count = text.length();
    CodepointMap::const_iterator pos, end = d_cp_map.end();
	String thisLine;
	int  nCount = 0;
    for (size_t c = 0; c < char_count; ++c)
    {
        pos = d_cp_map.find(text[c]);

		String tempLine = thisLine + text[c];
		float adv_extent = getTextExtent( tempLine, x_scale );
        
        if ( adv_extent > cur_extent)
        {
            cur_extent = adv_extent;
        }

		if( pos != d_cp_map.end() )
		{
			const Image* img = pos->second.d_image;
			height = img->getHeight() * y_scale*getYScale();
			if(height > maxHeight) maxHeight = height;
		}
		else
		{
			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type = (text[c] >> 24)&0xFF;
			switch(type)
			{
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;
					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id)) break;
 
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);

					height = animate->getSize().d_height;
					if(height > maxHeight) maxHeight = height;
				}
				break;
			}
		}
		
		if( adv_extent > wrap_width )
		{
			cur_extent = wrap_width;
			adv_extent = (float)pos->second.d_horz_advance * x_scale*getXScale();
			szRet.d_height += maxHeight + LineSpace;
			maxHeight = 0;
			cur_extent = wrap_width;
			
			if(thisLine.size() > 1) --c;
			thisLine.clear(); 
		}
		else thisLine += text[c];
		nCount ++;
    }

	szRet.d_width = cur_extent;
	szRet.d_height += maxHeight;
	return szRet;
}
#endif


Size Font::getLineSize(const String& text, float x_scale, float y_scale) const
{
	
	((Font*)this)->prepareString(text);

	x_scale = x_scale*getXScale();
	y_scale = y_scale*getYScale();

    float cur_extent = 0, adv_extent = 0, width;
	float maxHeight = getFontHeight(), height;

	const String KeyParserBegin	= "{";
	const String KeyParserEnd	= "}";

	bool bIsKeyHyperLink = false,bIsHyperLink = false;

    size_t char_count = text.length();
    CodepointMap::const_iterator pos, end = d_cp_map.end();

    for (size_t c = 0; c < char_count; ++c)
    {
        pos = d_cp_map.find(text[c]);

        if (pos != end)
        {

			if(bIsHyperLink)
			{
				if(text[c] == KeyParserBegin[0])
				{
					bIsKeyHyperLink = true;
					continue;
				}
				else if(text[c] ==KeyParserEnd[0])
				{
					bIsKeyHyperLink = false;
					continue;
				}
				else 

				if(bIsKeyHyperLink)
				{
					continue;
				}
			}
            width = (pos->second.d_image->getWidth() + pos->second.d_image->getOffsetX()) * x_scale;
            
            if (adv_extent + width > cur_extent)
            {
                cur_extent = adv_extent + width;
            }
            
            adv_extent += (float)pos->second.d_horz_advance * x_scale;

			const Image* img = pos->second.d_image;
			height = img->getHeight() * y_scale;
			if(height > maxHeight) maxHeight = height;
			if(height/y_scale > d_lineHeight) *((float*)&d_lineHeight) = height/y_scale;
        }
		else
		{
			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type = (text[c] >> 24)&0xFF;
			switch(type)
			{
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;
					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id)) break;
 
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);

					height = animate->getSize().d_height;
					if(height > maxHeight) maxHeight = height;

					adv_extent += (float)animate->getFrame(0)->getSourceTextureArea().getWidth() * x_scale;
				}
				break;
			case 0xFD:
				{
					bIsHyperLink = true;
				}
				break;
			case 0xFE:
				{
					bIsHyperLink = false;
				}
				break;
 

			default:
				break;
			}
		}

    }

	Size szRet;
	szRet.d_width = std::max(adv_extent, cur_extent);
	szRet.d_height = maxHeight * y_scale;

	return szRet;
}


size_t Font::getNextWord(const String& in_string, size_t start_idx, String& out_string) const
{
	out_string = in_string.substr(start_idx, 1);
	return 1;
}


DrawTextResult Font::drawText(const Window* OwnerWindow, const String& text, const Rect& draw_area, float z, const Rect& clip_rect, TextFormatting fmt, const ColourRect& colours, float x_scale, float y_scale ) const
{
	size_t thisCount;
	size_t lineCount = 0;

	float	y_top = draw_area.d_top;

	Rect tmpDrawArea(
		PixelAligned(draw_area.d_left),
		PixelAligned(draw_area.d_top),
		PixelAligned(draw_area.d_right),
		PixelAligned(draw_area.d_bottom)
		);

	size_t lineStart = 0, lineEnd = 0;
	String	currLine;
	float totalHeight = 0.0f;
	DrawTextResult dtmp;

	while (lineEnd < text.length())
	{
		if ((lineEnd = text.find_first_of('\n', lineStart)) == String::npos)
		{
			lineEnd = text.length();
		}

		currLine = text.substr(lineStart, lineEnd - lineStart);
		lineStart = lineEnd + 1;	

		switch(fmt)
		{
		case LeftAligned:
			dtmp = drawTextLine(OwnerWindow, currLine, Vector3(tmpDrawArea.d_left, y_top, z), clip_rect, colours, x_scale, y_scale);
			thisCount = 1;
			y_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;

		case RightAligned:
			dtmp = drawTextLine(OwnerWindow, currLine, Vector3(tmpDrawArea.d_right - getTextExtent(currLine, x_scale), y_top, z), clip_rect, colours, x_scale, y_scale);
			thisCount = 1;
			y_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;

		case Centred:
			dtmp = drawTextLine(OwnerWindow, currLine, Vector3(PixelAligned(tmpDrawArea.d_left + ((tmpDrawArea.getWidth() - getTextExtent(currLine, x_scale)) / 2.0f))+1, y_top, z), clip_rect, colours, x_scale, y_scale);
			thisCount = 1;
			y_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;
		case WordWrapLeftAligned:
			dtmp = drawWrappedText( OwnerWindow, currLine, tmpDrawArea, z, clip_rect, LeftAligned, colours, x_scale, y_scale);
			thisCount = dtmp.d_lineCount;
			tmpDrawArea.d_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;

		case WordWrapRightAligned:
			dtmp = drawWrappedText( OwnerWindow, currLine, tmpDrawArea, z, clip_rect, RightAligned, colours, x_scale, y_scale);
			thisCount = dtmp.d_lineCount;
			tmpDrawArea.d_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;

		case WordWrapCentred:
			dtmp = drawWrappedText( OwnerWindow,currLine, tmpDrawArea, z, clip_rect, Centred, colours, x_scale, y_scale);
			thisCount = dtmp.d_lineCount;
			tmpDrawArea.d_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;

		case WordWrapJustified:
			
			dtmp = drawWrappedText(OwnerWindow, currLine, tmpDrawArea, z, clip_rect, Justified, colours, x_scale, y_scale);
			thisCount = dtmp.d_lineCount;
			tmpDrawArea.d_top += dtmp.d_totalHeight;
			totalHeight += dtmp.d_totalHeight;
			break;

		default:
			throw InvalidRequestException((utf8*)"Font::drawText - Unknown or unsupported TextFormatting value specified.");
		}

		lineCount += thisCount;

	}

	DrawTextResult dret;
    
	dret.d_lineCount = std::max(lineCount, (size_t)1);
	dret.d_totalHeight = totalHeight;

    return dret;
}


DrawTextResult Font::drawWrappedText(const Window* OwnerWindow, const String& text, const Rect& draw_area, float z, const Rect& clip_rect, TextFormatting fmt, const ColourRect& colours, float x_scale, float y_scale ) const
{
	size_t	line_count = 0;
	Rect	dest_area(draw_area);
	float	wrap_width = draw_area.getWidth();
	String	thisLine, thisWord;
	float	total_height = 0.0f;
	DrawTextResult dtmp;
	size_t char_count = text.length();

	for (size_t c = 0; c < char_count; ++c)
	{
		CodepointMap::const_iterator pos = d_cp_map.find(text[c]);
		thisWord = text[ c ];

		String tempLine = thisLine + text[c];

		float warp_extern = getTextExtent(tempLine, x_scale );
		if( warp_extern > wrap_width )
		{
			
			dtmp = drawText(OwnerWindow, thisLine, dest_area, z, clip_rect, fmt, colours, x_scale, y_scale);
			line_count += dtmp.d_lineCount;

			
			if(thisLine.size() > 1) --c;
			thisLine.clear();

			
			dest_area.d_top += dtmp.d_totalHeight;
			dest_area.d_bottom += dtmp.d_totalHeight;
			total_height += dtmp.d_totalHeight;
			warp_extern = 0;
		}
		else 
		{
			
			thisLine += text[c];
		}
	}

	
	TextFormatting last_fmt = (fmt == Justified ? LeftAligned : fmt);
	
	dtmp = drawText(OwnerWindow, thisLine, dest_area, z, clip_rect, last_fmt, colours, x_scale, y_scale );
	line_count += dtmp.d_lineCount;
	total_height += dtmp.d_totalHeight;

	DrawTextResult dret;
	dret.d_lineCount = line_count;
	dret.d_totalHeight = total_height;
	return dret;
}

void Font::drawExternBorder(const Window* OwnerWindow, const Image* img, const Size& szBorder, const Vector3& cur_pos, 
							const Rect& clip_rect) const
{
	
	if((g_curTextBakColor.getRed() != 0.0f ||g_curTextBakColor.getGreen() != 0.0f || g_curTextBakColor.getBlue() != 0.0f) )
	{
		float blinkAlpha = 0;
		if(FontManager::getSingletonPtr())
			blinkAlpha = FontManager::getSingleton().getBlinkAlphaValue();

		colour col = g_curTextBakColor;
		col.setAlpha(g_isBlink ? blinkAlpha : g_curTextColor.getAlpha());

		//防止描边被切掉
		Rect clip_rect_2 = clip_rect;
		clip_rect_2.d_top -= 1;

		Size szTmp = szBorder;
		szTmp.d_height += 2;
		szTmp.d_width += 2;

		Vector3 posTmp = cur_pos;
		posTmp.d_x -= 1;
		posTmp.d_y -= 1;
		
		img->draw(posTmp, szTmp, clip_rect_2, ColourRect(col, col, col, col), TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow);
	}

}


DrawTextResult Font::drawTextLine(const Window* OwnerWindow, const String& text, const Vector3& position, const Rect& clip_rect, const ColourRect& colours, float x_scale, float y_scale) const
{
	if( d_underlineImage == NULL )
	{
		CodepointMap::const_iterator	pos, end = d_cp_map.end();
		pos = d_cp_map.find( UnderlineCharCode );
		if( pos != end )
		{
			Font* fontBase = (Font*)this;
			fontBase->d_underlineImage = (const Image*)pos->second.d_image;
		}
	}
	Vector3	cur_pos(position);

	float top_y = position.d_y;
	const String	KeyParser	= "{}";

	x_scale = x_scale*getXScale();
	y_scale = y_scale*getYScale();

	size_t char_count = text.length();
	CodepointMap::const_iterator	pos, end = d_cp_map.end();

	float			blinkAlpha = 1.0f;
	unsigned long	lquid = 0;

	
	float total_height = getFontHeight();
	for (size_t c = 0; c < char_count; ++c)
	{
		pos = d_cp_map.find(text[c]);

		if (pos != end)
		{
			const Image* img = pos->second.d_image;
			float height = img->getHeight() * y_scale;
			if( height > total_height ) 
				total_height = height;
			if( height/y_scale > d_lineHeight )
				*((float*)&d_lineHeight) = height/y_scale;
		}
		else
		{
			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type = (text[c] >> 24)&0xFF;
			switch(type)
			{
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;
					if( !KeyImageAnimationManager::getSingleton().isAnimatePresent(id) )
						break;
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);
					
					float height = animate->getSize().d_height;
					if( height > total_height )
					{
						total_height = height;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	float base_y = top_y+total_height-InterGlyphPadSpace-1;

	if(FontManager::getSingletonPtr())
		blinkAlpha = FontManager::getSingleton().getBlinkAlphaValue();

	for (size_t c = 0; c < char_count; ++c)
	{
		pos = d_cp_map.find(text[c]);

		if (pos != end)
		{
			const Image* img = pos->second.d_image;
			cur_pos.d_y = base_y - (img->getOffsetY() - img->getOffsetY() * y_scale);
			Size sz(img->getWidth() * x_scale, img->getHeight() * y_scale);

			if(g_isHyperLinkNow)
			{
				if(text[c] == KeyParser[0] )
				{
					g_isKeyHyperLink = 1;
					g_keyHyperLinkMaxCount = 0;
					continue;
				}
				else if(text[c] == KeyParser[1] )
				{
					g_isKeyHyperLink = 0;
					continue;
				}
				else if (g_isKeyHyperLink == 1)
				{
					g_keyHyperLink += text[c];
					
					// 超链接最大字数限制, 避免外部逻辑错误导致永远找不到“}”的情况.
					++g_keyHyperLinkMaxCount;
					if (g_keyHyperLinkMaxCount > 100)
					{
						g_isKeyHyperLink = 0;
					}
					continue;
				}
				else
				{
					if( HyperLinkManager::getSingletonPtr() )
					{
						Vector2 vRange;
						vRange.d_x = cur_pos.d_x;
						vRange.d_y = top_y;

						Rect newRect(vRange,sz);

						
						if( sz.d_height < total_height )
							newRect.offset( Point( 0, total_height - sz.d_height ) );

						bool isActiveHyperLink = false;
						colour curTextBakColor = g_curHyperLinkColor;

						
						if( HyperLinkManager::getSingleton().addHyperLink(OwnerWindow, g_keyHyperLink, newRect) )
						{
							isActiveHyperLink = true;
						}

						
						if(d_outline)
						{
							const Image* img_outline = pos->second.d_imageOutline;
							if(img_outline)
							{
								drawExternBorder(OwnerWindow, img_outline, sz, cur_pos, clip_rect);
							}
						}

						if(g_isBlink && FontManager::getSingletonPtr())
						{
							g_curTextColor.setAlpha(blinkAlpha);
							lquid = img->draw( cur_pos, sz, clip_rect, ColourRect(curTextBakColor, curTextBakColor, curTextBakColor, curTextBakColor), 
												TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow, 
												isActiveHyperLink);

							FontManager::getSingleton().addRuntimeBlink(OwnerWindow, img, lquid, cur_pos, sz, clip_rect, 
								ColourRect(curTextBakColor, curTextBakColor, curTextBakColor, curTextBakColor));
						}
						else
						{
							lquid = img->draw( cur_pos, sz, clip_rect, ColourRect(curTextBakColor, curTextBakColor, curTextBakColor, curTextBakColor), 
											   TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow, 
											   isActiveHyperLink);
						}

						if( d_underlineImage )
						{
							/*
							Vector3 vBorderPos = cur_pos;
							vBorderPos.d_x -= 2;
							++vBorderPos.d_y;
							Rect tmp = clip_rect;
							--tmp.d_top;
							++tmp.d_bottom;
							tmp.d_left -= 2;
							tmp.d_right += 4;///////////
							sz.d_width += 4;////////////
							*/


							Vector3 vBorderPos = cur_pos;
							--vBorderPos.d_x;
							//++vBorderPos.d_y;
							++vBorderPos.d_y;++vBorderPos.d_y;
							Rect tmp = clip_rect;
							--tmp.d_top;
							++tmp.d_bottom;
							sz.d_width += 2;

							d_underlineImage->draw( vBorderPos, sz, tmp, ColourRect(curTextBakColor, curTextBakColor, curTextBakColor, curTextBakColor),
								TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow, isActiveHyperLink);
						}

						
						HyperLinkManager::getSingleton().addHyperLink(OwnerWindow, g_keyHyperLink, newRect, lquid);

						cur_pos.d_x += (float)pos->second.d_horz_advance * x_scale;

						continue;
					}
				}
			}

			if(d_outline)
			{
				const Image* img_outline = pos->second.d_imageOutline;
				if(img_outline)
				{
					drawExternBorder(OwnerWindow, img_outline, sz, cur_pos, clip_rect);
				}
			}

			if(g_isBlink && FontManager::getSingletonPtr())
			{
				
				colour blinkColor(g_curTextColor);
				blinkColor.setAlpha(blinkAlpha);

				
				lquid = img->draw(cur_pos, sz, clip_rect, ColourRect(blinkColor, blinkColor, blinkColor, blinkColor), TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow);
				FontManager::getSingleton().addRuntimeBlink(OwnerWindow, img, lquid, cur_pos, sz, clip_rect, 
					ColourRect(blinkColor, blinkColor, blinkColor, blinkColor));
			}
			else
			{
				img->draw(cur_pos, sz, clip_rect, ColourRect(g_curTextColor, g_curTextColor, g_curTextColor, g_curTextColor), TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow);
			}

			if( g_isUnderline && d_underlineImage )
			{
				/*
				Vector3 vBorderPos = cur_pos;
				vBorderPos.d_x -= 2;
				++vBorderPos.d_y;
				Rect tmp = clip_rect;
				--tmp.d_top;
				++tmp.d_bottom;
				tmp.d_left -= 2;
				sz.d_width += 2;////////////
				tmp.d_right += 2;///////////
				*/

				Vector3 vBorderPos = cur_pos;
				--vBorderPos.d_x;
				++vBorderPos.d_y;++vBorderPos.d_y;
				Rect tmp = clip_rect;
				--tmp.d_top;
				++tmp.d_bottom;
				sz.d_width += 2;


				d_underlineImage->draw( vBorderPos, sz, tmp, ColourRect(g_curTextColor, g_curTextColor, g_curTextColor, g_curTextColor), 
					TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow);
			}

			cur_pos.d_x += (float)pos->second.d_horz_advance * x_scale;
		}
		else
		{
			utf32 value = text[c] & 0x00FFFFFF;
			utf32 type = (text[c] >> 24)&0xFF;
			switch(type)
			{
			case 0xFA:
			case 0xE3:
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;
					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id)) break;
 
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);

					cur_pos.d_y = base_y - animate->getSize().d_height+LineSpace;
					Size sz(animate->getSize());
					
					if( g_isHyperLinkNow == 1)
					{
						if( g_isKeyHyperLink == 1 )
							break;
						if( HyperLinkManager::getSingletonPtr() )
						{
							Vector2 vRange;
							vRange.d_x = cur_pos.d_x;
							vRange.d_y = cur_pos.d_y;
							Rect newRect(vRange,sz);
							HyperLinkManager::getSingleton().addHyperLink(OwnerWindow, g_keyHyperLink, newRect);
						}
					}

					
					int time_total = animate->getFrameNumber()*100;
					int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);
					colour col( 1,1,1,1 );
					col.setAlpha( g_curTextColor.getAlpha() );
					KeyImageAnimationManager::getSingleton().draw(OwnerWindow, id, 0, time_now, time_total, 
						cur_pos, sz, clip_rect, col );
					cur_pos.d_x += animate->getSize().d_width;
				}
				break;
 
			case 0xFB:
				{
					value |= utf32( colours.d_top_left.getAlpha() * 255 ) << 24;
					g_curTextColor.setARGB( value );
				}
				break;
 
			case 0xFC:
				{
					value |= utf32( colours.d_top_left.getAlpha() * 255 ) << 24;
					g_curTextBakColor.setARGB( value );
				}
				break;
			case 0xFD:
				{
					//syq:HyperLinkColor
					g_curHyperLinkColor.setARGB( utf32(OwnerWindow->getHyperLinkColorDefault()) );
					g_curHyperLinkColor.setAlpha( colours.d_top_left.getAlpha() );
					g_isHyperLinkNow = 1;
				}
				break;
			case 0xFE:
				{
					g_isHyperLinkNow = 0;
					g_keyHyperLink = "";
				}
				break;
			case 0xE0:
				{
					g_isBlink = true;
				}
				break;
			case 0xE1:
				{
					g_isBlink = false;
				}
				break;
			case 0xE4:
				{
					value |= utf32( colours.d_top_left.getAlpha() * 255 ) << 24;
					g_curHyperLinkColor.setARGB( value );
				}
				break;
			case 0xE5:
				{
					g_isUnderline = true;
				}
				break;
			case 0xE6:
				{
					g_isUnderline = false;
				}
				break;
			default:
				break;
			}
		}
	}
 
	//无论有没有}都关闭链接状态
	/*g_isHyperLinkNow = 0;
	g_keyHyperLink = "";
	g_isKeyHyperLink = 0;*/

	DrawTextResult dret;
	dret.d_lineCount = 1;
	dret.d_totalHeight = total_height + LineSpace;
	return dret;
}

int Font::debug_GetFontImageset(std::vector< Imageset* >& vTexture)
{
	if(d_listGlyphImagesets.size() > vTexture.size()) 
		return (int)d_listGlyphImagesets.size();

	GlyphImagesetList::iterator it;
	int i=0;
	for(it=d_listGlyphImagesets.begin(); it!=d_listGlyphImagesets.end(); it++, i++)
	{
		vTexture[i] = (*it)->d_imageset;
	}
	return(int)d_listGlyphImagesets.size();
}

float Font::getXScale()const
{
	
	return 1.0f;
}
float Font::getYScale()const
{
	
	return 1.0f;
}

void Font::setTextureSize( int setting )
{
	d_textureSize = setting;
}


void Font::setOutline(bool bOutline)
{
	d_outline = bOutline;
}


bool Font::getOutline() const
{
	return d_outline;
}


void Font::setAutoHint(bool bAutoHint)
{
	d_autohint = bAutoHint;
}

void Font::setBold(bool bBold)
{
	d_bold = bBold;
}

void Font::setMinSize(int nMinSize)
{
	d_minSize = nMinSize;
}
void Font::setMaxSize(int nMaxSize)
{
	d_maxSize = nMaxSize;
}


} 

