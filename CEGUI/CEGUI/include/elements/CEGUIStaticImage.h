

#ifndef _CEGUIStaticImage_h_
#define _CEGUIStaticImage_h_

#include "elements/CEGUIStatic.h"
#include "CEGUIRenderableImage.h"
#include "elements/CEGUIStaticImageProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT StaticImage : public Static
{
public:
	static const String EventNamespace;				


	
	
	enum HorzFormatting
	{
		LeftAligned,	
		RightAligned,	
		HorzCentred,	
		HorzStretched,	
		HorzTiled		
	};


	
	enum VertFormatting
	{
		TopAligned,		
		BottomAligned,	
		VertCentred,	
		VertStretched,	
		VertTiled		
	};


	
	
	StaticImage(const String& type, const String& name);


	
	virtual ~StaticImage(void);


	
	
	const Image*	getImage(void) const		{return d_image.getImage();}

	virtual void	setSize(MetricsMode mode, const Size& size);

	
	ColourRect	getImageColours(void) const		{return d_imageCols;}

	
	
	HorzFormatting	getHorizontalFormatting(void) const		{return	(HorzFormatting)d_image.getHorzFormatting();}


	
	VertFormatting	getVerticalFormatting(void) const		{return	(VertFormatting)d_image.getVertFormatting();}


	
	
	void	setImage(const Image* image);


	
	void	setImage(const String& imageset, const String& image);


	
	void	setImageColours(const ColourRect& colours);


	
	void	setImageColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour);


	
	void	setImageColours(const colour& col)		{setImageColours(col, col, col, col);}


	
	void	setFormatting(HorzFormatting h_fmt, VertFormatting v_fmt);


	
	void	setVerticalFormatting(VertFormatting v_fmt);


	
	void	setHorizontalFormatting(HorzFormatting h_fmt);

	
	void	setRightAnchor(const String& windowName) { d_rightAnchor = windowName; }

	
	String	getRightAnchor(void) const { return d_rightAnchor; }

	
	void	setBottomAnchor(const String& windowName) { d_bottomAnchor = windowName; }

	
	String	getBottomAnchor(void) const { return d_bottomAnchor; }

	
	virtual void postSizeChanged(void);

protected:
	
	virtual	void populateRenderCache();

	
	
	virtual void	onParentSized(WindowEventArgs& e);
	virtual void	onSized(WindowEventArgs& e);
	virtual void	onAlphaChanged(WindowEventArgs& e);
	virtual void	onStaticFrameChanged(WindowEventArgs& e);


	
	
	void	updateRenderableImageColours(void);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"StaticImage")	return true;
		return Static::testClassName_impl(class_name);
	}


	
	RenderableImage	d_image;		
	ColourRect		d_imageCols;	
	String			d_rightAnchor;	
	String			d_bottomAnchor;	

private:
	
	static StaticImageProperties::Image				d_imageProperty;
	static StaticImageProperties::ImageColours		d_imageColoursProperty;
	static StaticImageProperties::VertFormatting	d_vertFormattingProperty;
	static StaticImageProperties::HorzFormatting	d_horzFormattingProperty;
	static StaticImageProperties::RightAnchor		d_rightAnchorProperty;
	static StaticImageProperties::BottomAnchor		d_bottomAnchorProperty;


	
	void	addStaticImageProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
