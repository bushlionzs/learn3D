

#ifndef _CEGUIImage_h_
#define _CEGUIImage_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIRect.h"
#include "CEGUIColourRect.h"
#include "CEGUIVector.h"
#include "CEGUISize.h"
#include "CEGUIRenderer.h"
#include <map>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT Image
{
public:
	
	Size	getSize(void) const			{return Size(d_scaledWidth, d_scaledHeight);}
	

	
	float	getWidth(void) const		{return d_scaledWidth;}


	
	float	getHeight(void) const		{return d_scaledHeight;}


	
	Point	getOffsets(void) const		{return d_scaledOffset;}


	
	float	getOffsetX(void) const		{return	d_scaledOffset.d_x;}


	
	float	getOffsetY(void) const		{return d_scaledOffset.d_y;}


	
	const String&	getName(void) const;


	
	const Imageset*	getImageset(void) const { return d_owner; }

	
	const String&	getImagesetName(void) const;

    
    const Rect& getSourceTextureArea(void) const;

	
	
	void        setSourceTextureArea( Rect rect );
	
	

	
	unsigned long	draw(const Vector3& position, const Size& size, const Rect& clip_rect, const colour& top_left_colour = 0xFFFFFFFF, 
		const colour& top_right_colour = 0xFFFFFFFF, const colour& bottom_left_colour = 0xFFFFFFFF, const colour& bottom_right_colour = 0xFFFFFFFF, 
		QuadSplitMode quad_split_mode = TopLeftToBottomRight, float xtex = 1.0f, float ytex = 1.0f, void* pUserData = 0, bool isActiveHyperLink = false) const
	{
		return draw( position, size, clip_rect, 
			ColourRect(top_left_colour, top_right_colour, bottom_left_colour, bottom_right_colour), quad_split_mode, xtex, ytex, pUserData, isActiveHyperLink);
	}


	
	unsigned long	draw(const Rect& dest_rect, float z, const Rect& clip_rect, const colour& top_left_colour = 0xFFFFFFFF, 
		const colour& top_right_colour = 0xFFFFFFFF, const colour& bottom_left_colour = 0xFFFFFFFF, const colour& bottom_right_colour = 0xFFFFFFFF, 
		QuadSplitMode quad_split_mode = TopLeftToBottomRight, float xtex = 1.0f, float ytex = 1.0f) const
	{
		return draw(dest_rect, z, clip_rect, ColourRect(top_left_colour, top_right_colour, bottom_left_colour, bottom_right_colour), 
			quad_split_mode, xtex, ytex);
	}


	
	unsigned long	draw(const Vector3& position, const Size& size, const Rect& clip_rect, const ColourRect& colours, 
		QuadSplitMode quad_split_mode = TopLeftToBottomRight, float xtex = 1.0f, float ytex = 1.0f, void* pUserData = 0, bool isActiveHyperLink = false) const;

	
	unsigned long	draw(const Vector3& position, const Rect& clip_rect, const ColourRect& colours, 
		QuadSplitMode quad_split_mode = TopLeftToBottomRight, float xtex = 1.0f, float ytex = 1.0f) const
	{
		return draw(Rect(position.d_x, position.d_y, position.d_x + getWidth(), position.d_y + getHeight()), 
			position.d_z, clip_rect, colours, quad_split_mode, xtex, ytex);
	}


	
	unsigned long	draw(const Vector3& position, const Rect& clip_rect, const colour& top_left_colour = 0xFFFFFFFF, const colour& top_right_colour = 0xFFFFFFFF, const colour& bottom_left_colour = 0xFFFFFFFF, const colour& bottom_right_colour = 0xFFFFFFFF, 
		QuadSplitMode quad_split_mode = TopLeftToBottomRight, float xtex = 1.0f, float ytex = 1.0f) const
	{
		return draw(Rect(position.d_x, position.d_y, position.d_x + getWidth(), position.d_y + getHeight()), position.d_z, 
			clip_rect, ColourRect(top_left_colour, top_right_colour, bottom_left_colour, bottom_right_colour), 
			quad_split_mode, xtex, ytex);
	}


	
	unsigned long	draw(const Rect& dest_rect, float z, const Rect& clip_rect,const ColourRect& colours, 
		                    QuadSplitMode quad_split_mode = TopLeftToBottomRight, float xtex = 1.0f, float ytex = 1.0f) const;

	
	unsigned long   drawTri(const Rect& dest_rect, float z, const colour& diffuse, const Point* uv, 
							float xtex = 1.0f, float ytex = 1.0f ) const;
    
    void writeXMLToStream(OutStream& out_stream) const;


	friend class std::map<String, Image>;
	friend struct std::pair<const String, Image>;


	
	
	Image(void) {}


	
	Image(const Imageset* owner, const String& name, const Rect& area, const Point& render_offset, float horzScaling = 1.0f, float vertScaling = 1.0f);



	
	Image(const Image& image);


	
	~Image(void);


private:
	
	friend class Imageset;

		
	
	
	void	setHorzScaling(float factor);


	
	void	setVertScaling(float factor);


	
	const Imageset*	d_owner;		
	Rect			d_area;			
	Point			d_offset;		

	
	float	d_scaledWidth;		
	float	d_scaledHeight;		
	Point	d_scaledOffset;		
	String	d_name;				
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
