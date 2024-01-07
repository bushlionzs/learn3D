

#ifndef _CEGUIFontManager_implData_h_
#define _CEGUIFontManager_implData_h_

#include <ft2build.h>
#include FT_FREETYPE_H



namespace CEGUI
{
struct FontManager::FontManagerImplData
{
	FT_Library		d_ftlib;		
};

} 


#endif	
