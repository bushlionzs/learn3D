

#include "elements/CEGUIFrameWindow.h"
#include "elements/CEGUITitlebar.h"
#include "elements/CEGUIPushButton.h"
#include "CEGUIMouseCursor.h"
#include "CEGUIWindowManager.h"
#include "CEGUIExceptions.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"


namespace CEGUI
{
const String FrameWindow::EventNamespace("FrameWindow");


FrameWindowProperties::SizingEnabled			FrameWindow::d_sizingEnabledProperty;
FrameWindowProperties::FrameEnabled				FrameWindow::d_frameEnabledProperty;
FrameWindowProperties::TitlebarEnabled			FrameWindow::d_titlebarEnabledProperty;
FrameWindowProperties::CloseButtonEnabled		FrameWindow::d_closeButtonEnabledProperty;
FrameWindowProperties::RollUpState				FrameWindow::d_rollUpStateProperty;
FrameWindowProperties::RollUpEnabled			FrameWindow::d_rollUpEnabledProperty;
FrameWindowProperties::DragMovingEnabled		FrameWindow::d_dragMovingEnabledProperty;
FrameWindowProperties::SizingBorderThickness	FrameWindow::d_sizingBorderThicknessProperty;
FrameWindowProperties::TitlebarFont				FrameWindow::d_titlebarFontProperty;
FrameWindowProperties::CaptionColour			FrameWindow::d_captionColourProperty;
FrameWindowProperties::NSSizingCursorImage      FrameWindow::d_nsSizingCursorProperty;
FrameWindowProperties::EWSizingCursorImage      FrameWindow::d_ewSizingCursorProperty;
FrameWindowProperties::NWSESizingCursorImage    FrameWindow::d_nwseSizingCursorProperty;
FrameWindowProperties::NESWSizingCursorImage    FrameWindow::d_neswSizingCursorProperty;




const String FrameWindow::EventRollupToggled( (utf8*)"RollupToggled" );
const String FrameWindow::EventCloseClicked( (utf8*)"CloseClicked" );


const float FrameWindow::DefaultSizingBorderSize	= 8.0f;



FrameWindow::FrameWindow(const String& type, const String& name) :
	Window(type, name)
{
	d_frameEnabled		= true;
	d_rollupEnabled		= true;
	d_rolledup			= false;
	d_sizingEnabled		= true;
	d_beingSized		= false;
	d_dragMovable		= true;

	d_borderSize		= DefaultSizingBorderSize;

	d_nsSizingCursor = d_ewSizingCursor = d_neswSizingCursor = d_nwseSizingCursor = NULL;

	addFrameWindowProperties();
}



FrameWindow::~FrameWindow(void)
{
}



void FrameWindow::initialise(void)
{
	
	d_titlebar		= createTitlebar(getName() + "__auto_titlebar__");
	d_closeButton	= createCloseButton(getName() + "__auto_closebutton__");

	
	if (d_titlebar != NULL)
	{
		d_titlebar->setDraggingEnabled(d_dragMovable);
		addChildWindow(d_titlebar);
	}

	if (d_closeButton != NULL)
	{
		addChildWindow(d_closeButton);

		
		d_closeButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&CEGUI::FrameWindow::closeClickHandler, this));
	}

	performChildWindowLayout();
}



void FrameWindow::setSizingEnabled(bool setting)
{
	d_sizingEnabled = setting;
}



void FrameWindow::setFrameEnabled(bool setting)
{
	d_frameEnabled = setting;
	requestRedraw();
}



void FrameWindow::setTitleBarEnabled(bool setting)
{
    try
    {
        Window* titlebar = WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__");
        titlebar->setEnabled(setting);
        titlebar->setVisible(setting);
    }
    catch (UnknownObjectException)
    {}
}



void FrameWindow::setCloseButtonEnabled(bool setting)
{
    try
    {
        Window* closebtn = WindowManager::getSingleton().getWindow(getName() + "__auto_closebutton__");
        closebtn->setEnabled(setting);
        closebtn->setVisible(setting);
    }
    catch (UnknownObjectException)
    {}
}



void FrameWindow::setRollupEnabled(bool setting)
{
	if ((setting == false) && isRolledup())
	{
		toggleRollup();
	}

	d_rollupEnabled = setting;
}



void FrameWindow::toggleRollup(void)
{
    if (isRollupEnabled())
    {
        d_rolledup ^= true;
        
        
        WindowEventArgs args(this);
        onRollupToggled(args);
    }

}



void FrameWindow::setTitlebarFont(const String& name)
{
    try
    {
        WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__")->setFont(name);
    }
    catch (UnknownObjectException)
    {}
}



void FrameWindow::setTitlebarFont(Font* font)
{
    try
    {
        WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__")->setFont(font);
    }
    catch (UnknownObjectException)
    {}
}



void FrameWindow::offsetPixelPosition(const Vector2& offset)
{
    UVector2 uOffset;

    if (getMetricsMode() == Relative)
    {
        Size sz = getParentSize();

        uOffset.d_x = cegui_reldim((sz.d_width != 0) ? offset.d_x / sz.d_width : 0);
        uOffset.d_y = cegui_reldim((sz.d_height != 0) ? offset.d_y / sz.d_height : 0);
    }
    else
    {
        uOffset.d_x = cegui_absdim(PixelAligned(offset.d_x));
        uOffset.d_y = cegui_absdim(PixelAligned(offset.d_y));
    }

    setWindowPosition(d_area.getPosition() + uOffset);
}



FrameWindow::SizingLocation FrameWindow::getSizingBorderAtPoint(const Point& pt) const
{
	Rect	frame(getSizingRect());

	
	if (isSizingEnabled() && isFrameEnabled())
	{
		
		if (frame.isPointInRect(pt))
		{
			
			frame.d_left	+= d_borderSize;
			frame.d_top		+= d_borderSize;
			frame.d_right	-= d_borderSize;
			frame.d_bottom	-= d_borderSize;

			
			bool top	= (pt.d_y < frame.d_top);
			bool bottom = (pt.d_y >= frame.d_bottom);
			bool left	= (pt.d_x < frame.d_left);
			bool right	= (pt.d_x >= frame.d_right);

			
			if (top && left)
			{
				return SizingTopLeft;
			}
			else if (top && right)
			{
				return SizingTopRight;
			}
			else if (bottom && left)
			{
				return SizingBottomLeft;
			}
			else if (bottom && right)
			{
				return SizingBottomRight;
			}
			else if (top)
			{
				return SizingTop;
			}
			else if (bottom)
			{
				return SizingBottom;
			}
			else if (left)
			{
				return SizingLeft;
			}
			else if (right)
			{
				return SizingRight;
			}

		}

	}

	
	return SizingNone;
}



void FrameWindow::moveLeftEdge(float delta)
{
    float orgWidth = getAbsoluteWidth();
    float adjustment;
    float* minDim;
    float* maxDim;
    URect area(d_area);

    
    
    
    
    
    float maxWidth(d_maxSize.d_x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
    float minWidth(d_minSize.d_x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
    float newWidth = orgWidth - delta;

    if (newWidth > maxWidth)
        delta = orgWidth - maxWidth;
    else if (newWidth < minWidth)
        delta = orgWidth - minWidth;

    
    if (getMetricsMode() == Relative)
    {
        float base = getParentWidth();
        adjustment = (base != 0) ? delta / base : 0;
        minDim = &area.d_min.d_x.d_scale;
        maxDim = &area.d_max.d_x.d_scale;
    }
    else
    {
        adjustment = PixelAligned(delta);
        minDim = &area.d_min.d_x.d_offset;
        maxDim = &area.d_max.d_x.d_offset;
    }

    if (d_horzAlign == HA_RIGHT)
    {
        *maxDim -= adjustment;
    }
    else if (d_horzAlign == HA_CENTRE)
    {
        *maxDim -= adjustment * 0.5f;
        *minDim += adjustment * 0.5f;
    }
    else
    {
        *minDim += adjustment;
    }

    setWindowArea_impl(area.d_min, area.getSize(), d_horzAlign == HA_LEFT);
}

void FrameWindow::moveRightEdge(float delta)
{
    
    float orgWidth = getAbsoluteWidth();
    float adjustment;
    float* minDim;
    float* maxDim;
    URect area(d_area);

    
    
    
    
    
    float maxWidth(d_maxSize.d_x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
    float minWidth(d_minSize.d_x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
    float newWidth = orgWidth + delta;

    if (newWidth > maxWidth)
        delta = maxWidth - orgWidth;
    else if (newWidth < minWidth)
        delta = minWidth - orgWidth;
    
    
    if (getMetricsMode() == Relative)
    {
        float base = getParentWidth();
        adjustment = (base != 0) ? delta / base : 0;
        minDim = &area.d_min.d_x.d_scale;
        maxDim = &area.d_max.d_x.d_scale;
    }
    else
    {
        adjustment = PixelAligned(delta);
        minDim = &area.d_min.d_x.d_offset;
        maxDim = &area.d_max.d_x.d_offset;
    }

    *maxDim += adjustment;

    if (d_horzAlign == HA_RIGHT)
    {
        *maxDim += adjustment;
        *minDim += adjustment;
    }
    else if (d_horzAlign == HA_CENTRE)
    {
        *maxDim += adjustment * 0.5f;
        *minDim += adjustment * 0.5f;
    }

    setWindowArea_impl(area.d_min, area.getSize(), d_horzAlign == HA_RIGHT);

    
    d_dragPoint.d_x += getAbsoluteWidth() - orgWidth;
}


void FrameWindow::moveTopEdge(float delta)
{
    float orgHeight = getAbsoluteHeight();
    float adjustment;
    float* minDim;
    float* maxDim;
    URect area(d_area);

    
    
    
    
    
    float maxHeight(d_maxSize.d_y.asAbsolute(System::getSingleton().getRenderer()->getHeight()));
    float minHeight(d_minSize.d_y.asAbsolute(System::getSingleton().getRenderer()->getHeight()));
    float newHeight = orgHeight - delta;

    if (newHeight > maxHeight)
        delta = orgHeight - maxHeight;
    else if (newHeight < minHeight)
        delta = orgHeight - minHeight;

    
    if (getMetricsMode() == Relative)
    {
        float base = getParentHeight();
        adjustment = (base != 0) ? delta / base : 0;
        minDim = &area.d_min.d_y.d_scale;
        maxDim = &area.d_max.d_y.d_scale;
    }
    else
    {
        adjustment = PixelAligned(delta);
        minDim = &area.d_min.d_y.d_offset;
        maxDim = &area.d_max.d_y.d_offset;
    }

    if (d_vertAlign == VA_BOTTOM)
    {
        *maxDim -= adjustment;
    }
    else if (d_vertAlign == VA_CENTRE)
    {
        *maxDim -= adjustment * 0.5f;
        *minDim += adjustment * 0.5f;
    }
    else
    {
        *minDim += adjustment;
    }

    setWindowArea_impl(area.d_min, area.getSize(), d_vertAlign == VA_TOP);
}



void FrameWindow::moveBottomEdge(float delta)
{
    
    float orgHeight = getAbsoluteHeight();
    float adjustment;
    float* minDim;
    float* maxDim;
    URect area(d_area);

    
    
    
    
    
    float maxHeight(d_maxSize.d_y.asAbsolute(System::getSingleton().getRenderer()->getHeight()));
    float minHeight(d_minSize.d_y.asAbsolute(System::getSingleton().getRenderer()->getHeight()));
    float newHeight = orgHeight + delta;

    if (newHeight > maxHeight)
        delta = maxHeight - orgHeight;
    else if (newHeight < minHeight)
        delta = minHeight - orgHeight;
    
    
    if (getMetricsMode() == Relative)
    {
        float base = getParentHeight();
        adjustment = (base != 0) ? delta / base : 0;
        minDim = &area.d_min.d_y.d_scale;
        maxDim = &area.d_max.d_y.d_scale;
    }
    else
    {
        adjustment = PixelAligned(delta);
        minDim = &area.d_min.d_y.d_offset;
        maxDim = &area.d_max.d_y.d_offset;
    }

    *maxDim += adjustment;

    if (d_vertAlign == VA_BOTTOM)
    {
        *maxDim += adjustment;
        *minDim += adjustment;
    }
    else if (d_vertAlign == VA_CENTRE)
    {
        *maxDim += adjustment * 0.5f;
        *minDim += adjustment * 0.5f;
    }

    setWindowArea_impl(area.d_min, area.getSize(), d_vertAlign == VA_BOTTOM);

    
    d_dragPoint.d_y += getAbsoluteHeight() - orgHeight;
}


bool FrameWindow::closeClickHandler(const EventArgs& e)
{
    WindowEventArgs args(this);
	onCloseClicked(args);

	return true;
}



void FrameWindow::setCursorForPoint(const Point& pt) const
{
	switch(getSizingBorderAtPoint(pt))
	{
	case SizingTop:
	case SizingBottom:
		MouseCursor::getSingleton().setImage(d_nsSizingCursor);
		break;

	case SizingLeft:
	case SizingRight:
		MouseCursor::getSingleton().setImage(d_ewSizingCursor);
		break;

	case SizingTopLeft:
	case SizingBottomRight:
		MouseCursor::getSingleton().setImage(d_nwseSizingCursor);
		break;

	case SizingTopRight:
	case SizingBottomLeft:
		MouseCursor::getSingleton().setImage(d_neswSizingCursor);
		break;

	default:
		MouseCursor::getSingleton().setImage(getMouseCursor());
		break;
	}

}



void FrameWindow::onRollupToggled(WindowEventArgs& e)
{
    requestRedraw();

	fireEvent(EventRollupToggled, e, EventNamespace);
}



void FrameWindow::onCloseClicked(WindowEventArgs& e)
{
	fireEvent(EventCloseClicked, e, EventNamespace);
}



void FrameWindow::onMouseMove(MouseEventArgs& e)
{
	
	Window::onMouseMove(e);

	
	if (System::getSingleton().getWindowContainingMouse() != this)
	{
		return;
	}

	if (isSizingEnabled())
	{
		Point localMousePos(screenToWindow(e.position));

		if (getMetricsMode() == Relative)
		{
			localMousePos = relativeToAbsolute(localMousePos);
		}

		if (d_beingSized)
		{
			SizingLocation dragEdge = getSizingBorderAtPoint(d_dragPoint);

			
			float	deltaX = localMousePos.d_x - d_dragPoint.d_x;
			float	deltaY = localMousePos.d_y - d_dragPoint.d_y;

			
			if (isLeftSizingLocation(dragEdge))
			{
				moveLeftEdge(deltaX);
			}
			else if (isRightSizingLocation(dragEdge))
			{
				moveRightEdge(deltaX);
			}

			
			if (isTopSizingLocation(dragEdge))
			{
				moveTopEdge(deltaY);
			}
			else if (isBottomSizingLocation(dragEdge))
			{
				moveBottomEdge(deltaY);
			}

		}
		else
		{
			setCursorForPoint(localMousePos);
		}

	}

	
	e.handled = true;
}



void FrameWindow::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		if (isSizingEnabled())
		{
			
			Point localPos(screenToWindow(e.position));

			if (getMetricsMode() == Relative)
			{
				localPos = relativeToAbsolute(localPos);
			}

			
			if (getSizingBorderAtPoint(localPos) != SizingNone)
			{
				
				if (captureInput())
				{
					
					d_beingSized = true;
					d_dragPoint = localPos;
				}

			}

		}

		e.handled = true;
	}

}



void FrameWindow::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		
		releaseInput();
		e.handled = true;
	}

}



void FrameWindow::onCaptureLost(WindowEventArgs& e)
{
	
	Window::onCaptureLost(e);

	
	d_beingSized = false;

	e.handled = true;
}



void FrameWindow::onTextChanged(WindowEventArgs& e)
{
    
    WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__")->setText(d_text);
    
    performChildWindowLayout();
}



void FrameWindow::onActivated(ActivationEventArgs& e)
{
	Window::onActivated(e);
	d_titlebar->requestRedraw();
}



void FrameWindow::onDeactivated(ActivationEventArgs& e)
{
	Window::onDeactivated(e);
	d_titlebar->requestRedraw();
}



void FrameWindow::setDragMovingEnabled(bool setting)
{
	if (d_dragMovable != setting)
	{
		d_dragMovable = setting;

        try
        {
            static_cast<Titlebar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__"))->setDraggingEnabled(setting);
        }
        catch (UnknownObjectException)
        {}
    }

}



const Font* FrameWindow::getTitlebarFont(void) const
{
    try
    {
        return WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__")->getFont();
    }
    catch (UnknownObjectException)
    {
        return 0;
    }
}



void FrameWindow::addFrameWindowProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( FrameWindow );
	   CEGUI_ADD_STATICPROPERTY( &d_sizingEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_frameEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_titlebarEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_closeButtonEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_rollUpEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_rollUpStateProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_dragMovingEnabledProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_sizingBorderThicknessProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_titlebarFontProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_captionColourProperty );
       CEGUI_ADD_STATICPROPERTY( &d_nsSizingCursorProperty );
       CEGUI_ADD_STATICPROPERTY( &d_ewSizingCursorProperty );
       CEGUI_ADD_STATICPROPERTY( &d_nwseSizingCursorProperty );
       CEGUI_ADD_STATICPROPERTY( &d_neswSizingCursorProperty );
	CEGUI_END_ADD_STATICPROPERTY
}



colour FrameWindow::getCaptionColour(void) const
{
    return static_cast<Titlebar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__"))->getCaptionColour();
}



void FrameWindow::setCaptionColour(colour col)
{
    static_cast<Titlebar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__"))->setCaptionColour(col);
}


const Image* FrameWindow::getNSSizingCursorImage() const
{
    return d_nsSizingCursor;
}

const Image* FrameWindow::getEWSizingCursorImage() const
{
    return d_ewSizingCursor;
}

const Image* FrameWindow::getNWSESizingCursorImage() const
{
    return d_nwseSizingCursor;
}

const Image* FrameWindow::getNESWSizingCursorImage() const
{
    return d_neswSizingCursor;
}

void FrameWindow::setNSSizingCursorImage(const Image* image)
{
    d_nsSizingCursor = image;
}

void FrameWindow::setEWSizingCursorImage(const Image* image)
{
    d_ewSizingCursor = image;
}

void FrameWindow::setNWSESizingCursorImage(const Image* image)
{
    d_nwseSizingCursor = image;
}

void FrameWindow::setNESWSizingCursorImage(const Image* image)
{
    d_neswSizingCursor = image;
}

void FrameWindow::setNSSizingCursorImage(const String& imageset, const String& image)
{
    d_nsSizingCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
}

void FrameWindow::setEWSizingCursorImage(const String& imageset, const String& image)
{
    d_ewSizingCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
}

void FrameWindow::setNWSESizingCursorImage(const String& imageset, const String& image)
{
    d_nwseSizingCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
}

void FrameWindow::setNESWSizingCursorImage(const String& imageset, const String& image)
{
    d_neswSizingCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
}

} 
