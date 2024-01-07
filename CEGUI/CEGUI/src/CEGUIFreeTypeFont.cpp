#include <OgreHeader.h>
#include "CEGUIFreeTypeFont.h"
#include "CEGUIFont_ImplData.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUISystem.h"
#include "CEGUIExceptions.h"
#include "CEGUIFontManager.h"
#include <OgreMath.h>
#include "CEGUILogger.h"
#include <freetype/ftsynth.h>


#include <OgreImage.h>


namespace CEGUI
{

FreeTypeFont::FreeTypeFont(const String& filename, const String& resourceGroup, FontImplData* dat) :
	Font(filename, resourceGroup),
	d_impldat(dat),
	d_antiAliase(true)
{

}


FreeTypeFont::~FreeTypeFont(void)
{
    unload();
    delete d_impldat;
}


void FreeTypeFont::constructor_impl(const String& name, const String& fontname, const String& resourceGroup, uint size)
{
	String		errMsg;

	
	
	if(FontManager::getSingleton().isFontRawDataPresent(fontname))
	{
		d_impldat->fontData = FontManager::getSingleton().getFontRawData(fontname);
	}
	else
	{
		d_impldat->fontData = FontManager::getSingleton().createFontRawData(fontname,resourceGroup);
	}
	assert(d_impldat->fontData);

	

	
	
	if (FT_New_Memory_Face(d_impldat->library, d_impldat->fontData->getDataPtr(), 
                (FT_Long)d_impldat->fontData->getSize(), 0, &d_impldat->fontFace) == 0)
	{
		
		if (d_impldat->fontFace->charmap != NULL)	
		{
			try
			{
				d_name = name;
				d_ptSize = size;
				
				
				
				resetFontFaces();

				return;
			}
			catch(...)
			{
				Logger::getSingleton().logEvent("Font::resetFontFaces failed.", Errors);

				FT_Done_Face(d_impldat->fontFace);

				
				Logger::getSingleton().logEvent("FreeTypeFont::constructor_impl - reset Font Faces '" + name +"' failed.", Errors);
				throw;
			}

		}
		
		else
		{
			FT_Done_Face(d_impldat->fontFace);

			errMsg = (utf8*)"FreeTypeFont::constructor_impl - The source font '" + fontname +"' does not have a Unicode charmap, and cannot be used.";
		}

	}
	
	else
	{
		errMsg = (utf8*)"FreeTypeFont::constructor_impl - An error occurred while trying to create a FreeType face from source font '" + fontname + "'.";
	}

	throw GenericException(errMsg);
}



void FreeTypeFont::unload(void)
{
    d_cp_map.clear();

    
	if(d_impldat)
	{
		FT_Done_Face(d_impldat->fontFace);
	
	    
		d_impldat->fontData=NULL;
	
    }
}


void FreeTypeFont::resetFontFaces(void)
{
	if(d_impldat->fontFace == 0) return;

	uint horzDpi = System::getSingleton().getRenderer()->getHorzScreenDPI();
	uint vertDpi = System::getSingleton().getRenderer()->getVertScreenDPI();


	size_t pointsize = d_ptSize;
	if (d_autoScale)
		pointsize = d_ptSize * d_vertScaling;

	
	if( pointsize < d_minSize )
		pointsize = d_minSize;
	if( pointsize > d_maxSize )
		pointsize = d_maxSize;

	if(d_autohint)
		d_antiAliase = true;
	else
		d_antiAliase = false;


	//m_pointSize = pointsize;
    
	
	if (FT_Set_Pixel_Sizes(d_impldat->fontFace, 0, pointsize) != 0)
	{
		
		throw GenericException((utf8*)"FreeTypeFont::createFontFromFT_Face - An error occurred while creating a source font with the requested size.");
	}
	

	
	clearAllFontFaces();

	
	prepareString((utf8*)DefaultPrepareString);


	d_lineHeight = (float)d_maxGlyphHeight;

	
    d_max_bearingY = ((float)d_impldat->fontFace->ascender / (float)d_impldat->fontFace->units_per_EM) * (float)d_impldat->fontFace->size->metrics.y_ppem;
	d_lineSpacing = ((float)d_impldat->fontFace->height / (float)d_impldat->fontFace->units_per_EM) * (float)d_impldat->fontFace->size->metrics.y_ppem;
}

void FreeTypeFont::UpdateNextPos(int nWidth, int nHeight)
{
	int space_x = 0;
	if(d_outline)
		space_x = d_outlineSpacing;
	
	if( d_ptNext_X + nWidth + space_x > d_textureSize ) 
	{
		d_ptNext_Y += nHeight;
		
		int space_y = 0;
		if(d_outline)
		{
			d_ptNext_Y += d_outlineSpacing;
			d_ptNext_Y += InterGlyphPadSpace;

			d_ptNext_X = d_outlineSpacing;
			space_y = d_outlineSpacing;
		}
		else
		{
			d_ptNext_X = 0;
		}
		
		if(d_ptNext_Y + nHeight + space_y > d_textureSize)
		{
			d_currentGlyphImageset = createFontImageset();
		}

	}
}
/*
Point FreeTypeFont::GetNearestOffset()
{
	Point offset;
	int count = d_impldat->fontFace->glyph->metrics.horiBearingX
	while()
	d_pointSize.
	offset.d_x		=  (float)(d_impldat->fontFace->glyph->metrics.horiBearingX >> 6);
	offset.d_y		= -(float)(d_impldat->fontFace->glyph->metrics.horiBearingY >> 6);

	return pt;
}
*/
const Image* FreeTypeFont::createFontGlyph(const utf32 code)
{
	uint8 ctrlCode = (code >> 24) & 0xFF;
	if(ctrlCode != 0)
		return NULL;
	/*
	FT_Int32 flags = FT_LOAD_RENDER;
	if(d_antiAliase)
		flags |= FT_LOAD_FORCE_AUTOHINT;
	else
		flags |= FT_LOAD_NO_AUTOHINT;

	if(d_antiAliase)
		flags |= FT_LOAD_TARGET_NORMAL;
	else
		flags |= (FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO);
	*/
	//test
	FT_Int32 flags = FT_LOAD_RENDER;
	if(d_antiAliase)
		flags |= FT_LOAD_TARGET_LIGHT;
	else
		flags |= (FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO);

	if (FT_Load_Char(d_impldat->fontFace, code, flags))
		return NULL;

	if(d_bold)
		FT_GlyphSlot_Embolden( d_impldat->fontFace->glyph );

	uint rowHeight;
	rowHeight = (uint)d_impldat->fontFace->glyph->bitmap.rows;
	if(rowHeight > d_maxGlyphHeight)
		d_maxGlyphHeight = rowHeight;

	uint nWidth = d_impldat->fontFace->glyph->bitmap.width + InterGlyphPadSpace;
//	if(d_outline)
//	{
//#if OUTLINE_USE_SAME_TEXTURE
//		nWidth += 2;
//#else
//#endif
//	}

	if(!d_currentGlyphImageset)
	{
		d_currentGlyphImageset = createFontImageset();
	}
	else
	{
		UpdateNextPos(nWidth, d_maxGlyphHeight);
	}
	
	glyphDat dat;

	// fill & define code
	uint16* dest_buff = d_currentGlyphImageset->d_memory + (d_ptNext_Y) * d_textureSize + (d_ptNext_X);
	drawGlyphToBuffer(code, dest_buff, d_textureSize);

	Rect rect;
	char imageName[16];
	char imageNameOutline[16];

	rect.d_left		= (float)(d_ptNext_X);
	rect.d_top		= (float)(d_ptNext_Y);
	rect.d_right	= (float)((d_ptNext_X) + nWidth - InterGlyphPadSpace);
	rect.d_bottom	= (float)((d_ptNext_Y) + d_maxGlyphHeight);

	Point offset;// = GetNearestOffset();//d_pointSize
	offset.d_x		=  (float)(d_impldat->fontFace->glyph->metrics.horiBearingX >> 6);
	offset.d_y		= -(float)(d_impldat->fontFace->glyph->metrics.horiBearingY >> 6);
	//offset.d_y -= 1; //////向上移一个像素14号字取的结果是12 ?

	_snprintf(imageName, 16, "%X", code);
	d_currentGlyphImageset->d_imageset->defineImage(imageName, rect, offset);
	dat.d_image = (d_currentGlyphImageset->d_imageset->getImage(imageName));
	assert(dat.d_image != 0);
	dat.d_horz_advance = d_impldat->fontFace->glyph->advance.x >> 6;

	// fill & define code outline
	if(d_outline)
	{
		_snprintf(imageNameOutline, 16, "_%X_", code);

#if OUTLINE_USE_SAME_TEXTURE
		d_ptNext_X += nWidth;
		UpdateNextPos(nWidth, d_maxGlyphHeight);

		dest_buff = d_currentGlyphImageset->d_memory + (d_ptNext_Y) * d_textureSize + d_ptNext_X;
		uint16* dest_buff_outline = d_currentGlyphImageset->d_memory + (d_ptNext_Y-1) * d_textureSize + (d_ptNext_X-1);
		if(dest_buff_outline)
		{
			drawGlyphToBufferOutline(code, dest_buff, dest_buff_outline, d_textureSize);
		}
		rect.d_left		= (float)d_ptNext_X - 1;
		rect.d_top		= (float)d_ptNext_Y - 1;
		rect.d_right	= (float)(d_ptNext_X + nWidth - InterGlyphPadSpace) + 1;
		rect.d_bottom	= (float)(d_ptNext_Y + d_maxGlyphHeight) + 1;

		d_currentGlyphImageset->d_imageset->defineImage(imageNameOutline, rect, offset);

		d_ptNext_X += nWidth;
#else
		dest_buff = d_currentGlyphImagesetOutline->d_memory + (d_ptNext_Y) * d_textureSize + d_ptNext_X;
		uint16* dest_buff_outline = d_currentGlyphImagesetOutline->d_memory + (d_ptNext_Y-1) * d_textureSize + (d_ptNext_X-1);
		if(dest_buff_outline)
			drawGlyphToBufferOutline(code, dest_buff, dest_buff_outline, d_textureSize);

		rect.d_left -= 1;
		rect.d_top -= 1;
		rect.d_right += 1;
		rect.d_bottom += 1;

		d_currentGlyphImagesetOutline->d_imageset->defineImage(imageNameOutline, rect, offset);
#endif
	}

	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
#else
		d_ptNext_X += nWidth;
#endif
	}
	else
	{
		d_ptNext_X += nWidth;
	}
	
	if(d_outline)
	{
#if OUTLINE_USE_SAME_TEXTURE
		dat.d_imageOutline = (d_currentGlyphImageset->d_imageset->getImage(imageNameOutline));
		d_currentGlyphImageset->d_dirty = true;
#else
		dat.d_imageOutline = (d_currentGlyphImagesetOutline->d_imageset->getImage(imageNameOutline));
		d_currentGlyphImagesetOutline->d_dirty = true;
#endif
		assert(dat.d_imageOutline != 0);
	}
	else
	{
		dat.d_imageOutline = 0;
	}

	d_cp_map[code] = dat;
	d_currentGlyphImageset->d_dirty = true;

	return dat.d_image;
}


void FreeTypeFont::drawGlyphToBufferOutline(utf32 , uint16* buffer, uint16* buffer_outline, uint buf_width)
{
	FT_Bitmap* glyph_bitmap = &d_impldat->fontFace->glyph->bitmap;
	
	for (int i = 0; i < glyph_bitmap->rows + 2; ++i)
	{
		for (int j = 0; j < glyph_bitmap->width + 2; ++j)
		{
			buffer_outline[j] = 0x0000;
		}
	}

	for( int m=0; m<8; ++m)
	{
		uint16* p = buffer_outline;
		if(m==0)
			p ++; 
		else if(m==1)
			p += buf_width; 
		else if(m==2)
			p = (p + 1 + buf_width*2); 
		else if(m==3)
			p = (p + 2 + buf_width); 
		else if(m==4) 
			;
		else if(m==5) 
			p += 2;
		else if(m==6) 
			p += (buf_width*2);
		else if(m==7) 
			p = (p + 2 + buf_width*2);

		for (int i = 0; i < glyph_bitmap->rows; ++i)
		{
			for (int j = 0; j < glyph_bitmap->width; ++j)
			{
				switch (glyph_bitmap->pixel_mode)
				{
				case FT_PIXEL_MODE_GRAY:
					{
						uchar gray = glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j];
						if(gray > 0)
						{
							if(gray > p[j] >> 8)
								p[j] = (gray << 8) | 0xff;
						}
					}
					break;

				case FT_PIXEL_MODE_MONO:
					{
						int bPt = ((glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j / 8] << (j % 8)) & 0x80);
						if(bPt)
							p[j] =  0xFFFF;
					}
					break;

				default:
					throw InvalidRequestException((utf8*)"Font::drawGlyphToBufferOutline - The glyph could not be drawn because the pixel mode is unsupported.");
					break;
				}

			}

			buffer += buf_width;
			p += buf_width;
		}
	}
}


void FreeTypeFont::drawGlyphToBuffer(utf32 , uint16* buffer, uint buf_width)
{
	FT_Bitmap* glyph_bitmap = &d_impldat->fontFace->glyph->bitmap;

	for (int i = 0; i < glyph_bitmap->rows; ++i)
	{
		for (int j = 0; j < glyph_bitmap->width; ++j)
		{
			switch (glyph_bitmap->pixel_mode)
			{
			case FT_PIXEL_MODE_GRAY:
				{
					uchar* bytebuff = reinterpret_cast<uchar*>(&buffer[j]);
					*bytebuff++ = 0xFF;
					*bytebuff = glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j];
				}
				break;

			case FT_PIXEL_MODE_MONO:
				buffer[j] = ((glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j / 8] << (j % 8)) & 0x80) ? 0xFFFF : 0x0000;
				break;

			default:
				throw InvalidRequestException((utf8*)"Font::drawGlyphToBuffer - The glyph could not be drawn because the pixel mode is unsupported.");
				break;
			}

		}

		buffer += buf_width;
	}

}

} 
