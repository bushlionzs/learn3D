

#include "elements/CEGUIStaticImage.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIWindowManager.h"


namespace CEGUI
{
const String StaticImage::EventNamespace("StaticImage");


StaticImageProperties::Image			StaticImage::d_imageProperty;
StaticImageProperties::ImageColours		StaticImage::d_imageColoursProperty;
StaticImageProperties::VertFormatting	StaticImage::d_vertFormattingProperty;
StaticImageProperties::HorzFormatting	StaticImage::d_horzFormattingProperty;
StaticImageProperties::RightAnchor		StaticImage::d_rightAnchorProperty;
StaticImageProperties::BottomAnchor		StaticImage::d_bottomAnchorProperty;



StaticImage::StaticImage(const String& type, const String& name) :
	Static(type, name),
	d_imageCols(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF)
{
	addStaticImageProperties();

	
	d_image.setHorzFormatting(RenderableImage::HorzStretched);
	d_image.setVertFormatting(RenderableImage::VertStretched);
}



StaticImage::~StaticImage(void)
{
}



void StaticImage::setImage(const Image* image)
{
	d_image.setImage(image);
	
	requestRedraw();
}
void StaticImage::setSize(MetricsMode mode, const Size& size)
{
	Window::setSize( mode, size );
	d_image.setSize(getUnclippedInnerRect().getSize());
}


void StaticImage::setImage(const String& imageset, const String& image)
{
	setImage(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image));
}



void StaticImage::setImageColours(const ColourRect& colours)
{
	d_imageCols = colours;
	updateRenderableImageColours();

	requestRedraw();
}



void StaticImage::setImageColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour)
{
	d_imageCols.d_top_left		= top_left_colour;
	d_imageCols.d_top_right		= top_right_colour;
	d_imageCols.d_bottom_left	= bottom_left_colour;
	d_imageCols.d_bottom_right	= bottom_right_colour;
	updateRenderableImageColours();

	requestRedraw();
}



void StaticImage::setFormatting(HorzFormatting h_fmt, VertFormatting v_fmt)
{
	d_image.setHorzFormatting((RenderableImage::HorzFormatting)h_fmt);
	d_image.setVertFormatting((RenderableImage::VertFormatting)v_fmt);

	requestRedraw();
}



void StaticImage::setVerticalFormatting(VertFormatting v_fmt)
{
	d_image.setVertFormatting((RenderableImage::VertFormatting)v_fmt);
	
	requestRedraw();
}



void StaticImage::setHorizontalFormatting(HorzFormatting h_fmt)
{
	d_image.setHorzFormatting((RenderableImage::HorzFormatting)h_fmt);

	requestRedraw();
}



void StaticImage::updateRenderableImageColours(void)
{
	float alpha = getEffectiveAlpha();

	d_image.setColours(
		calculateModulatedAlphaColour(d_imageCols.d_top_left, alpha),
		calculateModulatedAlphaColour(d_imageCols.d_top_right, alpha),
		calculateModulatedAlphaColour(d_imageCols.d_bottom_left, alpha),
		calculateModulatedAlphaColour(d_imageCols.d_bottom_right, alpha)
	);

}



void StaticImage::populateRenderCache()
{
	
	Static::populateRenderCache();
	
	
	
	
	updateRenderableImageColours();
	d_image.draw(d_renderCache);
}



void StaticImage::onParentSized(WindowEventArgs& e)
{
	
	Static::onParentSized( e );
	d_image.setSize(getUnclippedInnerRect().getSize());

	e.handled = true;
}

void StaticImage::onSized(WindowEventArgs& e)
{
	Static::onSized(e);
	d_image.setSize(getUnclippedInnerRect().getSize());
	e.handled = true;
}

void StaticImage::onAlphaChanged(WindowEventArgs& e)
{
	
	Static::onAlphaChanged(e);

	
	updateRenderableImageColours();

	e.handled = true;
}



void StaticImage::onStaticFrameChanged(WindowEventArgs& e)
{
	
	Static::onStaticFrameChanged(e);

	
	
	Rect absRect(getUnclippedPixelRect());
	Rect innerRect(getUnclippedInnerRect());
	d_image.setSize(innerRect.getSize());
	d_image.setPosition(Point(innerRect.d_left - absRect.d_left, innerRect.d_top - absRect.d_top));

	e.handled = true;
}


void StaticImage::postSizeChanged(void)
{
	bool bRightAnchor = false;
	bool bBottomAnchor = false;

	float fAnchorWidth = 0.0f;
	float fAnchorHeight = 0.0f;

	if(!d_rightAnchor.empty())
	{
		Window* rightAnchor = WindowManager::getSingleton().getWindow(d_rightAnchor);
		if(rightAnchor)
		{
			bRightAnchor = true;
			fAnchorWidth = rightAnchor->getPixelRect().d_left-getPixelRect().d_left;
		}
	}

	if(!d_bottomAnchor.empty())
	{
		Window* bottomAnchor = WindowManager::getSingleton().getWindow(d_bottomAnchor);
		if(bottomAnchor)
		{
			bBottomAnchor = true;
			fAnchorHeight = bottomAnchor->getPixelRect().d_top-getPixelRect().d_top;
		}
	}

	if(bRightAnchor || bBottomAnchor)
	{
		float f1 = fAnchorWidth/getParentWidth();
		float f2 = f1*getParentWidth();

		if(fAnchorWidth != f2)
		{
			float fDif = fAnchorWidth-f2;
		}

		UVector2 usz(
			(bRightAnchor  ? UDim(0.0, fAnchorWidth)  : UDim(getRelativeWidth(), 0.0)),
			(bBottomAnchor ? UDim(0.0, fAnchorHeight) : UDim(getRelativeHeight(), 0.0)));

		setWindowSize(usz);
		d_image.setSize(getUnclippedInnerRect().getSize());
		requestRedraw();
	}

	Window::postSizeChanged();
}


void StaticImage::addStaticImageProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( StaticImage );
	   CEGUI_ADD_STATICPROPERTY( &d_imageProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_imageColoursProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_vertFormattingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_horzFormattingProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_rightAnchorProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_bottomAnchorProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


} 
