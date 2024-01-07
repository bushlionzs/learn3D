
#include "CEGUIBitmapFont.h"
#include "CEGUIDataContainer.h"
#include "CEGUISystem.h"
#include "CEGUIExceptions.h"
#include "CEGUIImageset.h"
#include "CEGUIImage.h"
#include "CEGUIFontManager.h"

#include <windows.h>


namespace CEGUI
{

const int g_nAsciiBegin	= 0X20;
const int g_nAsciiEnd	= 0X7F;

const int g_n1GBKBegin	= 0X81;
const int g_n1GBKEnd	= 0XFE;

const int g_n2GBKBegin1	= 0X40;
const int g_n2GBKEnd1	= 0X7E;
const int g_n2GBKBegin2	= 0X80;
const int g_n2GBKEnd2	= 0XFE;

const int g_nLineCount  = g_n1GBKEnd-g_n1GBKBegin+1;
const int g_nLineWidth1 = g_n2GBKEnd1-g_n2GBKBegin1+1;
const int g_nLineWidth2 = g_n2GBKEnd2-g_n2GBKBegin2+1;


const int INVALID_FIRST		= 0xA1;
const int INVALID_SECOND	= 0xF5;

BitmapFont::BitmapFont(const String& filename, const String& resourceGroup) :
	Font(filename, resourceGroup),
	d_fontData(0),
	d_dataBuf(0)
{
	

	
}

BitmapFont::~BitmapFont()
{
	d_dataBuf = 0;

	


	
	d_fontData = 0;
}


void BitmapFont::constructor_impl(const String& name, const String& fontname, const String& resourceGroup, uint size)
{
	
	if(12!=size && 16!=size)
	{
		throw GenericException("BitmapFont::constructor_impl: Unsupported font size!(" + name + ")");
	}

	d_name = name;
	d_ptSize = size;
	
	
	if(FontManager::getSingleton().isFontRawDataPresent(fontname))
	{
		d_fontData = FontManager::getSingleton().getFontRawData(fontname);
	}
	else
	{
		d_fontData = FontManager::getSingleton().createFontRawData(fontname,resourceGroup);
	}
	assert(d_fontData);
	
	

	
	d_dataBuf = (char*)(d_fontData->getDataPtr());

	
	resetFontFaces();
}


void BitmapFont::resetFontFaces(void)
{
	if(d_dataBuf == 0) return;

	
	clearAllFontFaces();

	
	prepareString((utf8*)DefaultPrepareString);

	d_lineHeight = (float)d_ptSize+InterGlyphPadSpace;

	
    d_max_bearingY = (float)d_lineHeight;
	d_lineSpacing = (float)d_ptSize+InterGlyphPadSpace;
}


const Image* BitmapFont::createFontGlyph(utf32 code)
{
	
	if(((code >> 24)&0XFF) != 0) return NULL;

	int nWidth = (int)d_ptSize;
	int nHeight = (int)d_ptSize + InterGlyphPadSpace;

	if(!d_currentGlyphImageset)
	{
		d_currentGlyphImageset = createFontImageset();
	}
	else
	{
		
		if( d_ptNext_X + nWidth > d_textureSize ) 
		{
			d_ptNext_Y += nHeight;
			d_ptNext_X = 0;

			
			if(d_ptNext_Y + d_maxGlyphHeight > d_textureSize)
			{
				d_currentGlyphImageset = createFontImageset();
			}
		}
	}

	
	uint16* dest_buff = 
		d_currentGlyphImageset->d_memory + d_ptNext_Y*d_textureSize + d_ptNext_X;

	
	drawGlyphToBuffer(code, dest_buff, d_textureSize);

	
	Rect rect;
	rect.d_left		= (float)d_ptNext_X;
	rect.d_top		= (float)d_ptNext_Y;
	rect.d_right	= (float)(d_ptNext_X + nWidth);
	rect.d_bottom	= (float)(d_ptNext_Y + nHeight);

	Point offset;
	offset.d_x		=  -1;
	offset.d_y		= -(float)(nHeight-3);

	char imageName[16];
	_snprintf(imageName, 16, "%X", code);
	d_currentGlyphImageset->d_imageset->defineImage(imageName, rect, offset);

	
	d_ptNext_X += nWidth;

	if(nHeight > (int)d_maxGlyphHeight) d_maxGlyphHeight = nHeight;

	
	glyphDat	dat;
	dat.d_image = (d_currentGlyphImageset->d_imageset->getImage(imageName));
	dat.d_horz_advance = nWidth+1;
	if(code >= g_nAsciiBegin && code <= g_nAsciiEnd) dat.d_horz_advance /= 2;

	d_cp_map[code] = dat;

	
	d_currentGlyphImageset->d_dirty = true;

	return dat.d_image;
}


void BitmapFont::drawGlyphToBufferOutline(utf32 code, uint16* buffer, uint16* buffer_outline, uint buf_width)
{
}


void BitmapFont::drawGlyphToBuffer(utf32 code, uint16* buffer, uint buf_width)
{
	int nOffset = 0;
	int nFontSize = (int)d_ptSize;

	
	if( code >= (CEGUI::utf32)g_nAsciiBegin && code <= (CEGUI::utf32)g_nAsciiEnd )
	{
		nOffset = code-g_nAsciiBegin;
	}
	else
	{
		
		wchar_t wTemp[8];
		wTemp[0] = (wchar_t)(code&0xFFFF);
		wTemp[1] = 0;

		char pMBCS[8] = {0};
		::WideCharToMultiByte(UI_LANGUAGES_CODE, 0, wTemp, 1, pMBCS, 8, 0, 0);

		int nFirstCode  = (int)(unsigned char)pMBCS[0];
		int nSecondCode = (int)(unsigned char)pMBCS[1];

		
		if(	nFirstCode < g_n1GBKBegin		|| 
			nFirstCode > g_n1GBKEnd 		||
			nSecondCode < g_n2GBKBegin1		||
			nSecondCode > g_n2GBKEnd1 && nSecondCode < g_n2GBKBegin2 ||
			nSecondCode > g_n2GBKEnd2 )
		{
			
			nFirstCode = INVALID_FIRST;
			nSecondCode = INVALID_SECOND;
		}

		
		nOffset = (nFirstCode-g_n1GBKBegin)*(g_nLineWidth1+g_nLineWidth2) + (g_nAsciiEnd-g_nAsciiBegin+1);
		if(nSecondCode <= g_n2GBKEnd1)
		{
			nOffset += (nSecondCode-g_n2GBKBegin1);
		}
		else
		{
			nOffset += (nSecondCode-g_n2GBKBegin2 + g_nLineWidth1);
		}
	}

	const char* pPoint = d_dataBuf + nOffset*((nFontSize*nFontSize)>>3);

	switch(nFontSize)
	{
	case 12:
		{
			for( int i=0; i<12; i++)
			{
				if(i&1)	
				{
					unsigned char byTemp = 
						*((unsigned char*)(pPoint + (((unsigned int)(i-1))>>1)*3 + 2));

					
					for(register int j=0; j<8; j++)
					{
						register unsigned char* bytebuff = (unsigned char*)(buffer+j+4);

						*bytebuff++ = 0xFF;
						*bytebuff = (byTemp & (((unsigned char)1)<<(7-j))) ? 0xFF : 0;
					}

					buffer += buf_width;
				}
				else
				{
					unsigned short wTemp = 
						*((unsigned short*)(pPoint + (((unsigned int)i)>>1)*3));

					for(register int j=0; j<12; j++)
					{
						register unsigned char* bytebuff = (unsigned char*)(buffer+j);

						
						*bytebuff++ = 0xFF;
						*bytebuff = (wTemp & ((unsigned short)1)<<(15-j)) ? 0xFF : 0;
					}

					buffer += buf_width;

					for(register int j=0; j<4; j++)
					{
						register unsigned char* bytebuff = (unsigned char*)(buffer+j);

						
						*bytebuff++ = 0xFF;
						*bytebuff = (wTemp & ((unsigned short)1)<<(3-j)) ? 0xFF : 0;
					}
				}
			}
		}
		break;

	case 16:
		{
			for(register int i=0; i<16; i++)
			{
				unsigned short wTemp = *((unsigned short*)(pPoint + i*2));

				for(register int j=0; j<16; j++)
				{
					register unsigned char* bytebuff = (unsigned char*)(buffer+j);

					*bytebuff++ = 0xFF;
					*bytebuff = (wTemp & (1<<(15-j))) ? 0xFF : 0;
				}

				buffer += buf_width;
			}
		}
		break;

	default:
		assert(false);
		break;
	}


}

} 
