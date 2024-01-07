

#ifndef _CEGUIFont_implData_h_
#define _CEGUIFont_implData_h_

#include <ft2build.h>
#include FT_FREETYPE_H
#include "CEGUIDataContainer.h"


namespace CEGUI
{
struct FreeTypeFont::FontImplData
{
	FontImplData(FT_Library lib) : library(lib), fontFace(0) {}

	FT_Library	library;
	FT_Face		fontFace;
 	
   
	RawDataContainer* fontData;
	
};

} 


#endif	
