

#include "CEGUIMouseCursor.h"
#include "CEGUIExceptions.h"
#include "CEGUILogger.h"
#include "CEGUISystem.h"
#include "CEGUIRenderer.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIImage.h"


namespace CEGUI
{
const String MouseCursor::EventNamespace("MouseCursor");



template<> MouseCursor* Singleton<MouseCursor>::ms_Singleton	= NULL;



const String MouseCursor::EventImageChanged( (utf8*)"ImageChanged" );



MouseCursor::MouseCursor(void)
{
    Rect screenArea(System::getSingleton().getRenderer()->getRect());

	
	d_position.d_x = screenArea.getWidth() / 2;
	d_position.d_y = screenArea.getHeight() / 2;
	d_position.d_z = 1.0f;

	
	setConstraintArea(&screenArea);

	
	d_visible = true;

	
	d_cursorImage = NULL;

	
	addMouseCursorEvents();

	d_cursorCallback = 0;

	
}



MouseCursor::~MouseCursor(void)
{
	
}



void MouseCursor::setImage(const Image* image)
{
	d_cursorImage = image;
	MouseCursorEventArgs args(this);
	args.image = image;
	onImageChanged(args);
}



void MouseCursor::setImage(const String& imageset, const String& image_name)
{
	setImage(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image_name));
}



void MouseCursor::draw(void) const
{
	if (d_visible && (d_cursorImage != NULL))
	{
		d_cursorImage->draw( d_position, System::getSingleton().getRenderer()->getRect() );
	}
}



void MouseCursor::setPosition(const Point& position)
{
	d_position.d_x = position.d_x;
	d_position.d_y = position.d_y;
	constrainPosition();
}



void MouseCursor::offsetPosition(const Point& offset)
{
	d_position.d_x += offset.d_x;
	d_position.d_y += offset.d_y;
	constrainPosition();
}



void MouseCursor::constrainPosition(void)
{
    Rect absarea(getConstraintArea());

	if (d_position.d_x >= absarea.d_right)
		d_position.d_x = absarea.d_right -1;

	if (d_position.d_y >= absarea.d_bottom)
		d_position.d_y = absarea.d_bottom -1;

	if (d_position.d_y < absarea.d_top)
		d_position.d_y = absarea.d_top;

	if (d_position.d_x < absarea.d_left)
		d_position.d_x = absarea.d_left;
}



void MouseCursor::setConstraintArea(const Rect* area)
{
	Rect renderer_area = System::getSingleton().getRenderer()->getRect();

	if (area == NULL)
	{
		d_constraints.d_min.d_x = cegui_reldim(renderer_area.d_left / renderer_area.getWidth());
		d_constraints.d_min.d_y = cegui_reldim(renderer_area.d_top / renderer_area.getHeight());
		d_constraints.d_max.d_x = cegui_reldim(renderer_area.d_right / renderer_area.getWidth());
		d_constraints.d_max.d_y = cegui_reldim(renderer_area.d_bottom / renderer_area.getHeight());
	}
	else
	{
        Rect finalArea(area->getIntersection(renderer_area));
		d_constraints.d_min.d_x = cegui_reldim(finalArea.d_left / renderer_area.getWidth());
		d_constraints.d_min.d_y = cegui_reldim(finalArea.d_top / renderer_area.getHeight());
		d_constraints.d_max.d_x = cegui_reldim(finalArea.d_right / renderer_area.getWidth());
		d_constraints.d_max.d_y = cegui_reldim(finalArea.d_bottom / renderer_area.getHeight());
		
		
		if( d_constraints.d_max.d_x.d_scale < 1.0f )
		{
			d_constraints.d_max.d_x.d_scale = 1.0f;
		}
		if( d_constraints.d_max.d_y.d_scale < 1.0f )
		{
			d_constraints.d_max.d_y.d_scale = 1.0f;
		}
	}

	constrainPosition();
}



void MouseCursor::setUnifiedConstraintArea(const URect* area)
{
	Rect renderer_area = System::getSingleton().getRenderer()->getRect();

	if (area)
	{
        d_constraints = *area;
	}
	else
	{
		d_constraints.d_min.d_x = cegui_reldim(renderer_area.d_left / renderer_area.getWidth());
		d_constraints.d_min.d_y = cegui_reldim(renderer_area.d_top / renderer_area.getHeight());
		d_constraints.d_max.d_x = cegui_reldim(renderer_area.d_right / renderer_area.getWidth());
		d_constraints.d_max.d_y = cegui_reldim(renderer_area.d_bottom / renderer_area.getHeight());
	}

	constrainPosition();
}


Rect MouseCursor::getConstraintArea(void) const
{
    return Rect(d_constraints.asAbsolute(System::getSingleton().getRenderer()->getSize()));
}


const URect& MouseCursor::getUnifiedConstraintArea(void) const
{
    return d_constraints;
}


Point MouseCursor::getDisplayIndependantPosition(void) const
{
	Size dsz(System::getSingleton().getRenderer()->getSize());

	return Point(d_position.d_x / (dsz.d_width - 1.0f), d_position.d_y / (dsz.d_height - 1.0f));
}



void MouseCursor::addMouseCursorEvents(void)
{
	
	addEvent(EventImageChanged);
}






void MouseCursor::onImageChanged(MouseCursorEventArgs& e)
{
	fireEvent(EventImageChanged, e, EventNamespace);
}


MouseCursor& MouseCursor::getSingleton(void)
{
	return Singleton<MouseCursor>::getSingleton();
}


MouseCursor* MouseCursor::getSingletonPtr(void)
{
	return Singleton<MouseCursor>::getSingletonPtr();
}

void MouseCursor::setGameCursor( int nCursor )
{
	if( d_cursorCallback )
	{
		d_cursorCallback(nCursor);
	}
}
} 
