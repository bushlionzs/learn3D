

#include "CEGUIImage.h"
#include "CEGUIExceptions.h"
#include "CEGUITexture.h"
#include "CEGUIImageset.h"
#include "CEGUIRenderer.h"
#include "CEGUIPropertyHelper.h"
#include <cmath>
#include <iostream>


namespace CEGUI
{


Image::Image(const Imageset* owner, const String& name, const Rect& area, const Point& render_offset, float horzScaling, float vertScaling) :
	d_owner(owner),
	d_area(area),
	d_offset(render_offset),
	d_name(name)
{
	if (d_owner == NULL)
	{
		throw NullObjectException((utf8*)"Image::Image - Imageset pointer passed to Image constructor must not be null.");
	}

	
	setHorzScaling(horzScaling);
	setVertScaling(vertScaling);

	
}


Image::Image(const Image& image) :
	d_owner(image.d_owner),
	d_area(image.d_area),
	d_offset(image.d_offset),
	d_scaledWidth(image.d_scaledWidth),
	d_scaledHeight(image.d_scaledHeight),
	d_scaledOffset(image.d_scaledOffset),
	d_name(image.d_name)
{
}


Image::~Image(void)
{
}



void Image::setHorzScaling(float factor)
{
	d_scaledWidth		= PixelAligned(d_area.getWidth() * factor);
	d_scaledOffset.d_x	= PixelAligned(d_offset.d_x * factor);
}



void Image::setVertScaling(float factor)
{
	d_scaledHeight		= PixelAligned(d_area.getHeight() * factor);
	d_scaledOffset.d_y	= PixelAligned(d_offset.d_y * factor);
}



unsigned long Image::draw(const Rect& dest_rect, float z, const Rect& clip_rect, const ColourRect& colours, 
						  QuadSplitMode quad_split_mode, float xtex, float ytex) const
{
	Rect dest(dest_rect);

	
	dest.offset(d_scaledOffset);

	
	return d_owner->draw(d_area, dest, z, clip_rect, colours, quad_split_mode, xtex, ytex);
}


unsigned long Image::drawTri(const Rect& dest_rect, float z, const colour& diffuse, const Point* uv, 
							float xtex, float ytex) const
{
	Rect dest(dest_rect);

	
	dest.offset(d_scaledOffset);

	
	return d_owner->drawTri(d_area, dest, z, diffuse, uv, xtex, ytex);
}


unsigned long Image::draw(const Vector3& position, const Size& size, const Rect& clip_rect, const ColourRect& colours, 
					 QuadSplitMode quad_split_mode, float xtex, float ytex, void* pUserData, bool isActiveHyperLink) const
{
	Rect dest_rect(position.d_x, position.d_y, position.d_x + size.d_width, position.d_y + size.d_height);

	Rect dest(dest_rect);

	
	dest.offset(d_scaledOffset);

	
	return d_owner->draw(d_area, dest, position.d_z, clip_rect, colours, quad_split_mode, xtex, ytex, pUserData, isActiveHyperLink);
}


const String& Image::getName(void) const
{
	return d_name;
}



const String& Image::getImagesetName(void) const
{
	return d_owner->getName();
}


const Rect& Image::getSourceTextureArea(void) const
{
    return d_area;
}
void Image::setSourceTextureArea( Rect rect )
{
	d_area = rect;
}


void Image::writeXMLToStream(OutStream& out_stream) const
{
    out_stream << "<Image Name=\"" << d_name.c_str() << "\" ";
    out_stream << "XPos=\"" << PropertyHelper::uintToString(static_cast<uint>(d_area.d_left)) << "\" ";
    out_stream << "YPos=\"" << PropertyHelper::uintToString(static_cast<uint>(d_area.d_top)) << "\" ";
    out_stream << "Width=\"" << PropertyHelper::uintToString(static_cast<uint>(d_area.getWidth())) << "\" ";
    out_stream << "Height=\"" << PropertyHelper::uintToString(static_cast<uint>(d_area.getHeight())) << "\" ";

    if (d_offset.d_x != 0.0f)
        out_stream << "XOffset=\"" << PropertyHelper::intToString(static_cast<int>(d_offset.d_x)) << "\" ";

    if (d_offset.d_y != 0.0f)
        out_stream << "YOffset=\"" << PropertyHelper::intToString(static_cast<int>(d_offset.d_x)) << "\" ";

    out_stream << "/>" << std::endl;
}


} 
