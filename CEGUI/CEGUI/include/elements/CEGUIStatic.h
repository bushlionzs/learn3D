

#ifndef _CEGUIStatic_h_
#define _CEGUIStatic_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "CEGUIRenderableFrame.h"
#include "elements/CEGUIStaticProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT Static : public Window
{
public:
	static const String EventNamespace;				


	
	
	bool	isFrameEnabled(void) const		{return d_frameEnabled;}
	bool	isRecalcFrameEnabled(void) const		{return d_recalcFrameEnabled;}


	
	bool	isBackgroundEnabled(void) const		{return d_backgroundEnabled;}


	
	ColourRect	getFrameColours(void) const		{return d_frameCols;}


	
	ColourRect	getBackgroundColours(void) const		{return d_backgroundCols;}


	
	virtual Rect	getUnclippedInnerRect(void) const;


	
	const Image*	getImageForFrameLocation(FrameLocation location) const;


	
	const Image* getBackgroundImage(void) const;


	
	
	void	setFrameEnabled(bool setting);
	void	setRecalcFrameEnabled(bool setting);


	
	void	setFrameImages(const Image* topleft, const Image* topright, const Image* bottomleft, const Image* bottomright, const Image* left, const Image* top, const Image* right, const Image* bottom);


	
	void	setFrameColours(const ColourRect& colours);


	
	void	setFrameColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour);


	
	void	setFrameColours(const colour& col)		{setFrameColours(col, col, col, col);}


	
	void	setBackgroundEnabled(bool setting);


	
	void	setBackgroundImage(const Image* image);


	
	void	setBackgroundImage(const String& imageset, const String& image);


	
	void	setBackgroundColours(const ColourRect& colours);


	
	void	setBackgroundColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour);


	
	void	setBackgroundColours(const colour& col)		{setBackgroundColours(col, col, col, col);}


	
	void	setImageForFrameLocation(FrameLocation location, const Image* image);


	
	
	Static(const String& type, const String& name);


	
	virtual ~Static(void);


protected:
	
	virtual	void populateRenderCache();


	
	virtual void	onSized(WindowEventArgs& e);
	virtual void	onParentSized(WindowEventArgs& e);
	virtual void	onAlphaChanged(WindowEventArgs& e);


	
	
	void	updateRenderableFrameColours(void);


	
	colour	calculateModulatedAlphaColour(const colour& col, float alpha) const;


	
	virtual void	onStaticFrameChanged(WindowEventArgs& e)	{}


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Static")	return true;
		return Window::testClassName_impl(class_name);
	}

	
	bool				d_frameEnabled;		
	bool				d_recalcFrameEnabled;		
	ColourRect			d_frameCols;		
	RenderableFrame		d_frame;			
	bool				d_backgroundEnabled;
	ColourRect			d_backgroundCols;	
	const Image*		d_background;		

	
	float	d_left_width;			
	float	d_right_width;			
	float	d_top_height;			
	float	d_bottom_height;		


private:
	
	static StaticProperties::FrameEnabled				d_frameEnabledProperty;
	static StaticProperties::BackgroundEnabled			d_backgroundEnabledProperty;
	static StaticProperties::FrameColours				d_frameColoursProperty;
	static StaticProperties::BackgroundColours			d_backgroundColoursProperty;
	static StaticProperties::BackgroundImage			d_backgroundImageProperty;
	static StaticProperties::TopLeftFrameImage			d_topLeftFrameProperty;
	static StaticProperties::TopRightFrameImage			d_topRightFrameProperty;
	static StaticProperties::BottomLeftFrameImage		d_bottomLeftFrameProperty;
	static StaticProperties::BottomRightFrameImage		d_bottomRightFrameProperty;
	static StaticProperties::LeftFrameImage				d_leftFrameProperty;
	static StaticProperties::RightFrameImage			d_rightFrameProperty;
	static StaticProperties::TopFrameImage				d_topFrameProperty;
	static StaticProperties::BottomFrameImage			d_bottomFrameProperty;
	static StaticProperties::RecalcFrame				d_recalcFrameEnabledProperty;


	
	void	addStaticProperties(void);
};


} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
