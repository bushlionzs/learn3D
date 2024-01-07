

#ifndef _CEGUIRenderableElement_h_
#define _CEGUIRenderableElement_h_

#include "CEGUIBase.h"
#include "CEGUISystem.h"
#include "CEGUIColourRect.h"
#include "CEGUIVector.h"
#include "CEGUIRenderCache.h"


namespace CEGUI
{

class CEGUIEXPORT RenderableElement
{
public:
	
	
	void	draw(const Vector3& position, const Rect& clip_rect);

    
    void draw(RenderCache& renderCache) const;

	
	
	RenderableElement*	getNextElement(void) const			{return d_next;}


	
	const ColourRect&	getColours(void) const						{return d_colours;}


	
	Point	getPosition(void) const							{return Point(d_area.d_left, d_area.d_top);}


	
	Size	getSize(void) const				{return Size(d_area.getWidth(), d_area.getHeight());}


	
	const Rect&	getRect(void) const				{return d_area;}


	
	bool	isColourRectPerImage(bool setting) const		{return d_useColoursPerImage;}


	
	
	void	setNextElement(RenderableElement* element)		{d_next = element;}


	
	void	setColours(const ColourRect& colours)			{d_colours = colours;}


	
	void	setColours(const colour& top_left_colour, const colour& top_right_colour, const colour& bottom_left_colour, const colour& bottom_right_colour);


	
	void	setPosition(const Point& position)				{d_area.setPosition(position);}


	
	void	setSize(const Size& size)		{d_area.setSize(size);}


	
	void	setRect(const Rect& area)		{d_area = area;}


	
	void	setColourRectPerImage(bool setting)		{d_useColoursPerImage = setting;}


	
	
	RenderableElement(void);



	
	virtual ~RenderableElement(void);


protected:
	
	
	virtual void	draw_impl(const Vector3& position, const Rect& clip_rect) const = 0;

    
    virtual void draw_impl(RenderCache& renderCache) const = 0;


	
	RenderableElement*	d_next;		
	ColourRect	d_colours;			
	Rect		d_area;				
	bool		d_useColoursPerImage;	
};

} 


#endif	
