

#include "CEGUIRenderableElement.h"


namespace CEGUI
{


RenderableElement::RenderableElement(void) :
	d_next(NULL),
	d_colours(colour(1, 1, 1, 1)),
	d_area(0, 0, 0, 0),
	d_useColoursPerImage(false)
{
}



RenderableElement::~RenderableElement(void)
{
}



void RenderableElement::setColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour)
{
	d_colours.d_top_left		= top_left_colour;
	d_colours.d_top_right		= top_right_colour;
	d_colours.d_bottom_left		= bottom_left_colour;
	d_colours.d_bottom_right	= bottom_right_colour;
}



void RenderableElement::draw(const Vector3& position, const Rect& clip_rect)
{
	Vector3	final_pos(position);
	final_pos.d_x += d_area.d_left;
	final_pos.d_y += d_area.d_top;

	
	draw_impl(final_pos, clip_rect);

	
	if (d_next != NULL)
	{
		d_next->draw(position, clip_rect);
	}

}

void RenderableElement::draw(RenderCache& renderCache) const
{
    draw_impl(renderCache);

    
    if (d_next)
    {
        d_next->draw(renderCache);
    }
}

} 
