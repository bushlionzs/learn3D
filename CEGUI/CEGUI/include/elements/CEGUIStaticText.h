

#ifndef _CEGUIStaticText_h_
#define _CEGUIStaticText_h_

#include "elements/CEGUIStatic.h"
#include "elements/CEGUIStaticTextProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT StaticText : public Static
{
public:
	static const String EventNamespace;				


	
	
	enum HorzFormatting
	{
		LeftAligned,			
		RightAligned,			
		HorzCentred,			
		HorzJustified,			
		WordWrapLeftAligned,	
		WordWrapRightAligned,	
		WordWrapCentred,		
		WordWrapJustified		
	};


	
	enum VertFormatting
	{
		TopAligned,		
		BottomAligned,	
		VertCentred     
	};


	
	
	StaticText(const String& type, const String& name);


	
	virtual ~StaticText(void);


	
	
	ColourRect	getTextColours(void) const		{return d_textCols;}

	
	
	HorzFormatting	getHorizontalFormatting(void) const		{return	d_horzFormatting;}


	
	VertFormatting	getVerticalFormatting(void) const		{return	d_vertFormatting;}


	
	bool	isVerticalScrollbarEnabled(void) const;


	
	bool	isHorizontalScrollbarEnabled(void) const;


	
	virtual Rect	getUnclippedInnerRect(void) const;


	
	
	virtual void	initialise(void);


	
	void	setTextColours(const ColourRect& colours);


	
	void	setTextColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour);


	
	void	setTextColours(const colour& col)		{setTextColours(col, col, col, col);}


	
	void	setFormatting(HorzFormatting h_fmt, VertFormatting v_fmt);


	
	void	setVerticalFormatting(VertFormatting v_fmt);


	
	void	setHorizontalFormatting(HorzFormatting h_fmt);


	
	void	setVerticalScrollbarEnabled(bool setting);


	
	void	setHorizontalScrollbarEnabled(bool setting);


	
	void	setTextScale( Size  scale );
	Size	getTextScale() const { return Size( d_fScaleX, d_fScaleX ); }
protected:
	
	virtual void populateRenderCache();


	
	virtual void	onTextChanged(WindowEventArgs& e);
	virtual void	onSized(WindowEventArgs& e);
	virtual	void	onFontChanged(WindowEventArgs& e);
	virtual void	onMouseWheel(MouseEventArgs& e);


	
	
	virtual	Rect	getTextRenderArea(void) const;


	
	void	configureScrollbars(void);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"StaticText")	return true;
		return Static::testClassName_impl(class_name);
	}


	
	
	virtual Scrollbar*	createVertScrollbar(const String& name) const		= 0;
 

	
	virtual Scrollbar*	createHorzScrollbar(const String& name) const		= 0;


	
	bool	handleScrollbarChange(const EventArgs& e);


	
	HorzFormatting	d_horzFormatting;		
	VertFormatting	d_vertFormatting;		
	ColourRect		d_textCols;				
	Scrollbar*		d_vertScrollbar;		
	Scrollbar*		d_horzScrollbar;		
	bool			d_enableVertScrollbar;	
	bool			d_enableHorzScrollbar;	

	float			d_fScaleX;
	float			d_fScaleY;
private:
	
	static StaticTextProperties::TextColours	d_textColoursProperty;
	static StaticTextProperties::VertFormatting	d_vertFormattingProperty;
	static StaticTextProperties::HorzFormatting	d_horzFormattingProperty;
	static StaticTextProperties::VertScrollbar	d_vertScrollbarProperty;
	static StaticTextProperties::HorzScrollbar	d_horzScrollbarProperty;
	static StaticTextProperties::TextScale		d_textScaleProperty;


	
	void	addStaticTextProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
