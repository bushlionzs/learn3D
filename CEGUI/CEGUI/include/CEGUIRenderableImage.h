

#ifndef _CEGUIRenderableImage_h_
#define _CEGUIRenderableImage_h_

#include "CEGUIBase.h"
#include "CEGUIRenderableElement.h"



namespace CEGUI
{

class CEGUIEXPORT RenderableImage : public RenderableElement
{
public:
	
	
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


	
	
	RenderableImage(void);


	
	virtual ~RenderableImage(void);


	
	
	void	setImage(const Image* image)		{d_image = image;}


	
	void	setHorzFormatting(HorzFormatting formatting)			{d_horzFormat = formatting;}
		

	
	void	setVertFormatting(VertFormatting formatting)			{d_vertFormat = formatting;}
	
	
	
	void	setQuadSplitMode(QuadSplitMode split_mode)				{d_quadSplitMode = split_mode;}


	
	const Image*	getImage(void) const		{return d_image;}


	
	HorzFormatting	getHorzFormatting(void) const				{return d_horzFormat;}


	
	VertFormatting	getVertFormatting(void) const				{return d_vertFormat;}
	
	
	
	QuadSplitMode	getQuadSplitMode(void) const				{return d_quadSplitMode;}


protected:
	
	
	void draw_impl(const Vector3& position, const Rect& clip_rect) const;

    
    void draw_impl(RenderCache& renderCache) const;

    
    uint getHorzTileCount() const;

    
    uint getVertTileCount() const;

    
    float getBaseXCoord(const Size& sz) const;

    
    float getBaseYCoord(const Size& sz) const;

    
    Size getDestinationSize() const;

	
	HorzFormatting	d_horzFormat;		
	VertFormatting	d_vertFormat;		
	QuadSplitMode	d_quadSplitMode;	
	const Image*	d_image;			
};

} 


#endif	
