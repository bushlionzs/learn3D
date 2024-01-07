

#ifndef _CEGUIFontBase_h_
#define _CEGUIFontBase_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIRect.h"
#include "CEGUIColour.h"
#include "CEGUIVector.h"
#include "CEGUIColourRect.h"


#include <list>
#include <map>
#include <vector>

#define OUTLINE_USE_SAME_TEXTURE   1

#define OPTIMIZE_DAMAGE  1

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{


enum FontType
{
	FreeType,	
	Bitmap,		
};


enum TextFormatting
{
	LeftAligned	= 0,			
	RightAligned,			
	Centred,				
	Justified,				
	WordWrapLeftAligned,	
	WordWrapRightAligned,	
	WordWrapCentred, 		
	WordWrapJustified 		
};


struct CEGUIEXPORT DrawTextResult
{
	int		d_lineCount;		
	float	d_totalHeight;		
};



class Window;
class CEGUIEXPORT Font
{
	friend class Font_xmlHandler;
	
public:
	
	static const argb_t		DefaultColour;			
	static const uint		LineSpace;
	

	

	
	virtual FontType	getType(void) const = 0;

	
	const String&	getName(void) const		{return	d_name;}

	
	void	notifyScreenResolution(const Size& size);

	
	void	prepareString(const String& text);

	
	void	setNativeResolution(const Size& size);

	
	void	setAutoScalingEnabled(bool setting);
	
	void	setTextureSize(int setting);

	
	void setOutline(bool bOutline);
	
	bool getOutline() const;
	
	void setAutoHint(bool bAutoHint);
	void setBold(bool bBold);
	
	void setMinSize(int nMinSize);
	void setMaxSize(int nMaxSize);

	
	bool	isCodepointAvailable(utf32 cp) const		{return (d_cp_map.find(cp) != d_cp_map.end());}

	
	
	DrawTextResult	drawText(const Window* OwnerWindow, const String& text, const Rect& draw_area, float z, const Rect& clip_rect, TextFormatting fmt, const ColourRect& colours, float x_scale = 1.0f, float y_scale = 1.0f ) const;


	
	DrawTextResult	drawText(const Window* OwnerWindow,const String& text, const Rect& draw_area, float z, const Rect& clip_rect, TextFormatting fmt, float x_scale = 1.0f, float y_scale = 1.0f) const
	{ return drawText( OwnerWindow, text, draw_area, z, clip_rect, fmt, ColourRect(DefaultColour, DefaultColour, DefaultColour, DefaultColour), x_scale, y_scale ); }


	
	void	drawText(const Window* OwnerWindow, const String& text, const Rect& draw_area, float z, const Rect& clip_rect, float x_scale = 1.0f, float y_scale = 1.0f) const
	{ drawText( OwnerWindow, text, draw_area, z, clip_rect, LeftAligned, ColourRect(DefaultColour, DefaultColour, DefaultColour, DefaultColour), x_scale, y_scale); }


	
	DrawTextResult	drawText(const Window* OwnerWindow,const String& text, const Rect& draw_area, float z, TextFormatting fmt, const ColourRect& colours, float x_scale = 1.0f, float y_scale = 1.0f) const
	{ return drawText( OwnerWindow, text, draw_area, z, draw_area, fmt, colours, x_scale, y_scale); }


	
	DrawTextResult	drawText(const Window* OwnerWindow,const String& text, const Rect& draw_area, float z, TextFormatting fmt, float x_scale = 1.0f, float y_scale = 1.0f ) const
	{ return drawText( OwnerWindow, text, draw_area, z, draw_area, fmt, ColourRect(DefaultColour, DefaultColour, DefaultColour, DefaultColour), x_scale, y_scale); }


	
	void	drawText(const Window* OwnerWindow,const String& text, const Rect& draw_area, float z, float x_scale = 1.0f, float y_scale = 1.0f) const
	{ drawText( OwnerWindow, text, draw_area, z, draw_area, LeftAligned, ColourRect(DefaultColour, DefaultColour, DefaultColour, DefaultColour), x_scale, y_scale); }


	
	void	drawText(const Window* OwnerWindow,const String& text, const Vector3& position, const Rect& clip_rect, const ColourRect& colours, float x_scale = 1.0f, float y_scale = 1.0f) const
	{ drawText( OwnerWindow, text, Rect(position.d_x, position.d_y, position.d_x, position.d_y), position.d_z, clip_rect, LeftAligned, colours, x_scale, y_scale); }


	
	void	drawText(const Window* OwnerWindow,const String& text, const Vector3& position, const Rect& clip_rect, float x_scale = 1.0f, float y_scale = 1.0f ) const
	{ drawText(OwnerWindow, text, Rect(position.d_x, position.d_y, position.d_x, position.d_y), position.d_z, clip_rect, LeftAligned, ColourRect(DefaultColour, DefaultColour, DefaultColour, DefaultColour), x_scale, y_scale); }

	
	Size	getFormattedSize(const String& text, const Rect& format_area, TextFormatting fmt, float x_scale = 1.0f, float y_scale = 1.0f, bool bSingleLine = false) const;

	
	float	getLineSpacing(float y_scale = 1.0f) const		{return d_lineSpacing * y_scale * getYScale();}


	
	float	getFontHeight(float y_scale = 1.0f) const	{return d_lineHeight * y_scale * getYScale();}


	
	float	getBaseline(float y_scale = 1.0f) const			{return d_max_bearingY * y_scale * getYScale();}

	
	float	getTextExtent(const String& text, float x_scale = 1.0f, utf32 *color = NULL, utf32* bakColor = NULL, bool bNeedPrepare = true ) const;

	
	float	getFormattedTextExtent(const String& text, const Rect& format_area, TextFormatting fmt, float x_scale = 1.0f) const;

	
	float	getWrappedTextExtent(const String& text, float wrapWidth, float x_scale = 1.0f) const;

	
	size_t	getCharAtPixel(const String& text, float pixel, float x_scale = 1.0f) const		{return getCharAtPixel(text, 0, pixel, x_scale);}

	
	size_t	getCharAtPixel(const String& text, size_t start_char, float pixel, float x_scale = 1.0f) const;

	
	
	int debug_GetFontImageset(std::vector< Imageset* >& vTexture);

	void drawExternBorder(const Window* OwnerWindow, const Image* img, const Size& szBorder, const Vector3& cur_pos, const Rect& clip_rect) const;

protected:
	
	
	Font(const String& filename, const String& resourceGroup);

public:		
	
	virtual ~Font(void);

protected:
	
	static const char	FontSchemaName[];			
	static const char	DefaultPrepareString[];		
	static const uint	InterGlyphPadSpace;			
	static const uint	FontGlyphImagesetSize;		

	
	friend class FontManager;

	
	
	struct glyphImageset
	{
		uint16*		d_memory;		
		Imageset*	d_imageset;		
		bool		d_dirty;		
	};

	
	struct glyphDat
	{
		const Image*	d_image;					
		int				d_horz_advance;				
		int				d_horz_advance_unscaled;	
		unsigned int	d_countsUsed;				
		
		const Image*    d_imageOutline;
	};

	
	
	void	load(const String& filename, const String& resourceGroup);


	
	virtual void	unload(void);

	
	virtual void	constructor_impl(const String& name, const String& fontname, const String& resourceGroup, uint size) = 0;

	
	virtual void	resetFontFaces(void) = 0;

	
	void	clearAllFontFaces(void);

	
	virtual const Image*	createFontGlyph(utf32 code) = 0;

	
	glyphImageset*	createFontImageset(void);

	
	void	prepareFontTexture(void);

	
	virtual void	drawGlyphToBuffer(utf32 code, uint16* buffer, uint buf_width) = 0;

	
	virtual void    drawGlyphToBufferOutline(utf32 code, uint16* buffer, uint16* buffer_outline, uint buf_width) = 0;

	
	DrawTextResult	drawWrappedText(const Window* OwnerWindow, const String& text, const Rect& draw_area, float z, const Rect& clip_rect, TextFormatting fmt, const ColourRect& colours, float x_scale = 1.0f, float y_scale = 1.0f) const;


	
	size_t	getNextWord(const String& in_string, size_t start_idx, String& out_string) const;


	

	
	DrawTextResult	drawTextLine(const Window* OwnerWindow, const String& text, const Vector3& position, const Rect& clip_rect, const ColourRect& colours, float x_scale = 1.0f, float y_scale = 1.0f) const;


	
	void	drawTextLineJustified(const Window* OwnerWindow,const String& text, const Rect& draw_area, const Vector3& position, const Rect& clip_rect, const ColourRect& colours, float x_scale = 1.0f, float y_scale = 1.0f) const;
public:
	
	Size	getLineSize(const String& text, float x_scale = 1.0f, float y_scale = 1.0f) const;

	
	Size	getWrappedSize(const String& text, const Rect& format_area, float x_scale = 1.0f, float y_scale = 1.0f) const;


	int  getFontVertOffset() const { return d_vertOffset; }
	void setFontVertOffset(int nOffset){ d_vertOffset = nOffset; }
protected:
	
	String	d_name;				
	uint	d_ptSize;			
	float	d_lineHeight;		
	float	d_lineSpacing;		
	float	d_max_bearingY;		


	uint	d_maxGlyphHeight;	
	
	int     d_outlineSpacing;   
	int     d_vertOffset;       

	typedef		std::map<utf32, glyphDat>		CodepointMap;
	CodepointMap	d_cp_map;	

	
	typedef		std::list< glyphImageset* >		GlyphImagesetList;
	GlyphImagesetList	d_listGlyphImagesets;	
	glyphImageset*		d_currentGlyphImageset;	
	
	
	bool    d_outline;
	
	bool    d_autohint;
	bool    d_bold;
	
	int     d_minSize;
	int     d_maxSize;

#if OUTLINE_USE_SAME_TEXTURE
#else
	GlyphImagesetList	d_listGlyphImagesetsOutline;
	glyphImageset*		d_currentGlyphImagesetOutline;
#endif

	uint				d_ptNext_X, d_ptNext_Y; 

	
	bool	d_autoScale;			
	float	d_horzScaling;			
	float	d_vertScaling;			
	float	d_nativeHorzRes;		
	float	d_nativeVertRes;		

	int		d_textureSize;



	const Image* d_underlineImage;


	inline float getXScale()const;
	inline float getYScale()const;


};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	