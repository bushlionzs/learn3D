

#ifndef _CEGUIListboxTextItem_h_
#define _CEGUIListboxTextItem_h_
#include "elements/CEGUIListboxItem.h"



namespace CEGUI
{

class CEGUIEXPORT ListboxTextItem : public ListboxItem
{
public:
	
	static const colour	DefaultTextColour;			


	
	
	ListboxTextItem(const String& text, uint item_id = 0, void* item_data = NULL, bool disabled = false, bool auto_delete = true);


	
	virtual ~ListboxTextItem(void) {}


	
	
	const Font*	getFont(void) const;


	
	ColourRect	getTextColours(void) const		{return d_textCols;}


	
	
	void	setFont(const Font* font)		{d_font = font;}


	
	void	setFont(const String& font_name);


	
	void	setTextColours(const ColourRect& cols)			{d_textCols = cols;}


	
	void	setTextColours(colour top_left_colour, colour top_right_colour, colour bottom_left_colour, colour bottom_right_colour);


	
	void	setTextColours(colour col)		{setTextColours(col, col, col, col);}


	
    Size getPixelSize( const Window* pParent);
    virtual void draw(const Vector3& position, float alpha, const Rect& clipper) const;
    virtual void draw(RenderCache& cache,const Rect& targetRect, float zBase,  float alpha, const Rect* clipper) const;


	void setHorzFomate( TextFormatting horzFormate ){ d_horzFormateing = horzFormate; };
protected:
	
	ColourRect		d_textCols;			
	const Font*	d_font;				

	TextFormatting  d_horzFormateing;
};

} 


#endif	
