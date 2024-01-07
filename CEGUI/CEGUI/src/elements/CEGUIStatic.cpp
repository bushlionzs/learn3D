

#include "elements/CEGUIStatic.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"



namespace CEGUI
{
const String Static::EventNamespace("Static");


StaticProperties::FrameEnabled				Static::d_frameEnabledProperty;
StaticProperties::BackgroundEnabled			Static::d_backgroundEnabledProperty;
StaticProperties::FrameColours				Static::d_frameColoursProperty;
StaticProperties::BackgroundColours			Static::d_backgroundColoursProperty;
StaticProperties::BackgroundImage			Static::d_backgroundImageProperty;
StaticProperties::TopLeftFrameImage			Static::d_topLeftFrameProperty;
StaticProperties::TopRightFrameImage		Static::d_topRightFrameProperty;
StaticProperties::BottomLeftFrameImage		Static::d_bottomLeftFrameProperty;
StaticProperties::BottomRightFrameImage		Static::d_bottomRightFrameProperty;
StaticProperties::LeftFrameImage			Static::d_leftFrameProperty;
StaticProperties::RightFrameImage			Static::d_rightFrameProperty;
StaticProperties::TopFrameImage				Static::d_topFrameProperty;
StaticProperties::BottomFrameImage			Static::d_bottomFrameProperty;
StaticProperties::RecalcFrame				Static::d_recalcFrameEnabledProperty;



Static::Static(const String& type, const String& name) :
	Window(type, name),
	d_frameEnabled(false),
	d_recalcFrameEnabled(true),
	d_frameCols(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF),
	d_backgroundEnabled(false),
	d_backgroundCols(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF),
	d_background(NULL),
	d_left_width(0),
	d_right_width(0),
	d_top_height(0),
	d_bottom_height(0)
{
	addStaticProperties();
}



Static::~Static(void)
{
}



Rect Static::getUnclippedInnerRect(void) const
{
	
	if (d_frameEnabled)
	{
		CEGUI::Size curSize = CEGUI::System::getSingleton().getRenderer()->getSize();

		Rect tmp(Window::getUnclippedInnerRect());
		tmp.d_left		+= d_left_width;
		tmp.d_right		-= d_right_width;
		tmp.d_top		+= d_top_height;
		tmp.d_bottom	-= d_bottom_height;
		return tmp;
	}
	
	else
	{
		return Window::getUnclippedInnerRect();
	}

}



void Static::setFrameEnabled(bool setting)
{
	if (d_frameEnabled != setting)
	{
		d_frameEnabled = setting;
		WindowEventArgs args(this);
		onStaticFrameChanged(args);
		requestRedraw();
	}
}

void Static::setRecalcFrameEnabled(bool setting)
{
	if (d_recalcFrameEnabled != setting)
	{
		d_recalcFrameEnabled = setting;
	}
}



void Static::setFrameImages(const Image* topleft, const Image* topright, const Image* bottomleft, const Image* bottomright, const Image* left, const Image* top, const Image* right, const Image* bottom)
{
	
	d_frame.setImages(topleft, topright, bottomleft, bottomright, left, top, right, bottom);

	
	d_left_width	= (left != NULL) ? left->getWidth() : 0.0f;
	d_right_width	= (right != NULL) ? right->getWidth() : 0.0f;
	d_top_height	= (top != NULL) ? top->getHeight() : 0.0f;
	d_bottom_height	= (bottom != NULL) ? bottom->getHeight() : 0.0f;

	
	if (d_frameEnabled)
	{
		WindowEventArgs args(this);
		onStaticFrameChanged(args);
		requestRedraw();
	}

}



void Static::setFrameColours(const ColourRect& colours)
{
	d_frameCols = colours;
	updateRenderableFrameColours();

	
	if (d_frameEnabled)
	{
		WindowEventArgs args(this);
		onStaticFrameChanged(args);
		requestRedraw();
	}

}



void Static::setFrameColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour)
{
	d_frameCols.d_top_left		= top_left_colour;
	d_frameCols.d_top_right		= top_right_colour;
	d_frameCols.d_bottom_left	= bottom_left_colour;
	d_frameCols.d_bottom_right	= bottom_right_colour;
	updateRenderableFrameColours();

	
	if (d_frameEnabled)
	{
		WindowEventArgs args(this);
		onStaticFrameChanged(args);
		requestRedraw();
	}

}



void Static::setBackgroundEnabled(bool setting)
{
	if (d_backgroundEnabled != setting)
	{
		d_backgroundEnabled = setting;
		requestRedraw();
	}

}



void Static::setBackgroundImage(const Image* image)
{
	d_background = image;

	if (d_backgroundEnabled)
	{
		requestRedraw();
	}

}



void Static::setBackgroundImage(const String& imageset, const String& image)
{
	setBackgroundImage(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image));
}



void Static::setBackgroundColours(const ColourRect& colours)
{
	d_backgroundCols = colours;

	if (d_backgroundEnabled)
	{
		requestRedraw();
	}

}



void Static::setBackgroundColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour)
{
	d_backgroundCols.d_top_left		= top_left_colour;
	d_backgroundCols.d_top_right	= top_right_colour;
	d_backgroundCols.d_bottom_left	= bottom_left_colour;
	d_backgroundCols.d_bottom_right	= bottom_right_colour;

	if (d_backgroundEnabled)
	{
		requestRedraw();
	}

}



void Static::updateRenderableFrameColours(void)
{
	float alpha = getEffectiveAlpha();

	d_frame.setColours(
		calculateModulatedAlphaColour(d_frameCols.d_top_left, alpha),
		calculateModulatedAlphaColour(d_frameCols.d_top_right, alpha),
		calculateModulatedAlphaColour(d_frameCols.d_bottom_left, alpha),
		calculateModulatedAlphaColour(d_frameCols.d_bottom_right, alpha)
	);

}



colour Static::calculateModulatedAlphaColour(const colour& col, float alpha) const
{
	colour temp(col);
	temp.setAlpha(temp.getAlpha() * alpha);
	return temp;
}



void Static::populateRenderCache()
{
	Rect backgroundRect(Point(0,0), getAbsoluteSize());

	
	if (d_frameEnabled)
	{
        d_frame.draw(d_renderCache);

		CEGUI::Size curSize = CEGUI::System::getSingleton().getRenderer()->getSize();

		float tmp_left_width = d_left_width;
		float tmp_right_width = d_right_width;
		float tmp_top_height = d_top_height;
		float tmp_bottom_height = d_bottom_height;

		if( d_recalcFrameEnabled )
		{
			tmp_left_width = d_left_width / 2048 * curSize.d_width;
			tmp_right_width = d_right_width / 2048 * curSize.d_width;
			tmp_top_height = d_top_height / 2048 * curSize.d_width;
			tmp_bottom_height = d_bottom_height / 2048 * curSize.d_width;
		}

		
		backgroundRect.d_left		+= tmp_left_width;
		backgroundRect.d_right		-= tmp_right_width;
		backgroundRect.d_top		+= tmp_top_height;
		backgroundRect.d_bottom		-= tmp_bottom_height;
	}

	
	if (d_backgroundEnabled && (d_background != NULL))
	{
        
        ColourRect colours(d_backgroundCols);
        colours.modulateAlpha(getEffectiveAlpha());
        
        d_renderCache.cacheImage(*d_background, backgroundRect, 0, colours);
	}

}



void Static::onParentSized(WindowEventArgs& e)
{
	
	Window::onParentSized(e);

	
	d_frame.setSize(getAbsoluteSize());

	e.handled = true;
}

void Static::onSized(WindowEventArgs& e)
{
	Window::onSized(e);
	d_frame.setSize(getAbsoluteSize());
	e.handled = true;
}


void Static::onAlphaChanged(WindowEventArgs& e)
{
	
	Window::onAlphaChanged(e);

	
	updateRenderableFrameColours();

	e.handled = true;
}



const Image* Static::getImageForFrameLocation(FrameLocation location) const
{
	return d_frame.getImageForLocation(location);
}



const Image* Static::getBackgroundImage(void) const
{
	return d_background;
}



void Static::setImageForFrameLocation(FrameLocation location, const Image* image)
{
	d_frame.setImageForLocation(location, image);

	
	switch (location)
	{
	case LeftEdge:
		d_left_width = (image != NULL) ? image->getWidth() : 0;
		break;

	case RightEdge:
		d_right_width = (image != NULL) ? image->getWidth() : 0;
		break;

	case TopEdge:
		d_top_height = (image != NULL) ? image->getHeight() : 0;
		break;

	case BottomEdge:
		d_bottom_height = (image != NULL) ? image->getHeight() : 0;
		break;

	default:
		break;
	}

}


void Static::addStaticProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Static );
	   CEGUI_ADD_STATICPROPERTY( &d_frameEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_backgroundEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_frameColoursProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_backgroundColoursProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_backgroundImageProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_topLeftFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_topRightFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_bottomLeftFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_bottomRightFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_leftFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_topFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_rightFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_bottomFrameProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_recalcFrameEnabledProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

} 
