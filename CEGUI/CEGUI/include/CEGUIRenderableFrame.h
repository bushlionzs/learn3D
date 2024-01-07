

#ifndef _CEGUIRenderableFrame_h_
#define _CEGUIRenderableFrame_h_

#include "CEGUIBase.h"
#include "CEGUIRenderableElement.h"



namespace CEGUI
{

enum FrameLocation
{
	Invalid,			
	TopLeftCorner,		
	TopRightCorner,		
	BottomLeftCorner,	
	BottomRightCorner,	
	LeftEdge,			
	TopEdge,			
	RightEdge,			
	BottomEdge			
};



class CEGUIEXPORT RenderableFrame : public RenderableElement
{
public:
	
	
	RenderableFrame(void);


	
	virtual ~RenderableFrame(void);


	
	void	setImages(const Image* topleft, const Image* topright, const Image* bottomleft, const Image* bottomright, const Image* left, const Image* top, const Image* right, const Image* bottom);


	
	void	setImageForLocation(FrameLocation location, const Image* image);



	
	const Image*	getImageForLocation(FrameLocation location) const;


protected:
	
	
	void draw_impl(const Vector3& position, const Rect& clip_rect) const;

    
    void draw_impl(RenderCache& renderCache) const;

	
	
	const Image*	d_topleft;			
	const Image*	d_topright;			
	const Image*	d_bottomleft;		
	const Image*	d_bottomright;		
	const Image*	d_left;				
	const Image*	d_right;			
	const Image*	d_top;				
	const Image*	d_bottom;			
};

} 


#endif	
