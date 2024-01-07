
#ifndef _CEGUIBitmapFont_h_
#define _CEGUIBitmapFont_h_

#include "CEGUIBase.h"
#include "CEGUIFont.h"


namespace CEGUI
{
class RawDataContainer;


class CEGUIEXPORT BitmapFont : public Font
{
	friend class FontManager;

public:
	

	
	virtual FontType	getType(void) const { return Bitmap; }

private:
	
	struct FontImplData;


	
	
	BitmapFont(const String& filename, const String& resourceGroup);

public:		
	
	virtual ~BitmapFont();

protected:
	

	
	virtual void	constructor_impl(const String& name, const String& fontname, const String& resourceGroup, uint size);

	
	virtual const Image*	createFontGlyph(utf32 code);

	
	virtual void	resetFontFaces(void);

	
	virtual void	drawGlyphToBuffer(utf32 code, uint16* buffer, uint buf_width);

	
	virtual void    drawGlyphToBufferOutline(utf32 code, uint16* buffer, uint16* buffer_outline, uint buf_width);

	
    RawDataContainer*	d_fontData;
	const char*			d_dataBuf;
};

} 

#endif	