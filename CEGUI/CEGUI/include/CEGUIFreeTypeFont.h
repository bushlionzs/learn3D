

#ifndef _CEGUIFreeTypeFont_h_
#define _CEGUIFreeTypeFont_h_

#include "CEGUIBase.h"
#include "CEGUIFont.h"


namespace CEGUI
{



class CEGUIEXPORT FreeTypeFont : public Font
{
	friend class FontManager;
public:
	

	//Point GetNearestOffset();

	virtual FontType	getType(void) const { return FreeType; }

private:
	
	struct FontImplData;


	
	
	FreeTypeFont(const String& filename, const String& resourceGroup, FontImplData* dat);

public:		
	
	~FreeTypeFont(void);

protected:
	

	
	virtual void	resetFontFaces(void);

	
	virtual void	unload(void);

	
	virtual const Image*	createFontGlyph(utf32 code);

	
	virtual void	constructor_impl(const String& name, const String& fontname, const String& resourceGroup, uint size);

	
	virtual void	drawGlyphToBuffer(utf32 code, uint16* buffer, uint buf_width);
	
	
	virtual void    drawGlyphToBufferOutline(utf32 code, uint16* buffer, uint16* buffer_outline, uint buf_width);

	void UpdateNextPos(int nWidth, int nHeight);
	
	FontImplData*	d_impldat;	
	bool			d_antiAliase;	
	//int             d_pointSize;
};

} 

#endif	