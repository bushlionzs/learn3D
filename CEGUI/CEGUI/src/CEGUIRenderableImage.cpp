

#include "CEGUIRenderableImage.h"
#include "CEGUIImage.h"
#include "CEGUIExceptions.h"


namespace CEGUI
{


RenderableImage::RenderableImage(void) :
	d_horzFormat(LeftAligned),
	d_vertFormat(TopAligned),
	d_quadSplitMode(TopLeftToBottomRight),
	d_image(NULL)
{
}



RenderableImage::~RenderableImage(void)
{
}



void RenderableImage::draw_impl(const Vector3& position, const Rect& clip_rect) const
{
	
	if (d_image == NULL)
		return;

	
	Rect final_clipper(position.d_x, position.d_y, 0, 0);
	final_clipper.setSize(d_area.getSize());
	final_clipper = clip_rect.getIntersection(final_clipper);

	Size imgSize(getDestinationSize());
	
	uint horzTiles = getHorzTileCount();
	uint vertTiles = getVertTileCount();
	
	float baseX = getBaseXCoord(imgSize) + position.d_x;
	
	float baseY = getBaseYCoord(imgSize) + position.d_y;

	Vector3 drawpos(0,baseY, position.d_z);
	ColourRect final_colours(d_colours);
	bool calcColoursPerImage = !(d_useColoursPerImage || d_colours.isMonochromatic());

	
	for (uint row = 0; row < vertTiles; ++row)
	{
		drawpos.d_x = baseX;

		for (uint col = 0; col < horzTiles; ++col)
		{
			if (calcColoursPerImage)
			{
				float leftfactor = (drawpos.d_x - baseX + d_image->getOffsetX()) / d_area.getWidth();
				float rightfactor = leftfactor + imgSize.d_width / d_area.getWidth();
				float topfactor = (drawpos.d_y - baseY + d_image->getOffsetY()) / d_area.getHeight();
				float bottomfactor = topfactor + imgSize.d_height / d_area.getHeight();

				final_colours = d_colours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
			}

			d_image->draw(drawpos, imgSize, final_clipper, final_colours, d_quadSplitMode);
			drawpos.d_x += imgSize.d_width;
		}

		drawpos.d_y += imgSize.d_height;
	}

}

void RenderableImage::draw_impl(RenderCache& renderCache) const
{
    
    if (!d_image)
        return;

    
    Size imgSize(getDestinationSize());
    
    float baseX = getBaseXCoord(imgSize) + d_area.d_left;
    float baseY = getBaseYCoord(imgSize) + d_area.d_top;
    
    uint horzTiles = getHorzTileCount();
    uint vertTiles = getVertTileCount();

    
    ColourRect final_colours(d_colours);
    bool calcColoursPerImage = !(d_useColoursPerImage || d_colours.isMonochromatic());

    
    Rect targetRect;
    targetRect.d_top    = baseY;
    targetRect.d_bottom = baseY + imgSize.d_height;

    
    for (uint row = 0; row < vertTiles; ++row)
    {
        
        targetRect.d_left  = baseX;
        targetRect.d_right = baseX + imgSize.d_width;

        for (uint col = 0; col < horzTiles; ++col)
        {
            
            if (calcColoursPerImage)
            {
                float leftfactor = (targetRect.d_left - baseX + d_image->getOffsetX()) / d_area.getWidth();
                float rightfactor = leftfactor + imgSize.d_width / d_area.getWidth();
                float topfactor = (targetRect.d_top - baseY + d_image->getOffsetY()) / d_area.getHeight();
                float bottomfactor = topfactor + imgSize.d_height / d_area.getHeight();
                final_colours = d_colours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            renderCache.cacheImage(*d_image, targetRect, 0, final_colours);
            
            targetRect.d_left  += imgSize.d_width;
            targetRect.d_right += imgSize.d_width;
        }

        
        targetRect.d_top    += imgSize.d_height;
        targetRect.d_bottom += imgSize.d_height;
    }
}

uint RenderableImage::getHorzTileCount() const
{
    return (d_horzFormat == HorzTiled) ? (uint)((d_area.getWidth() + (d_image->getWidth() - 1)) / d_image->getWidth()) : 1;
}

uint RenderableImage::getVertTileCount() const
{
    return (d_vertFormat == VertTiled) ? (uint)((d_area.getHeight() + (d_image->getHeight() - 1)) / d_image->getHeight()) : 1;
}

float RenderableImage::getBaseXCoord(const Size& sz) const
{
    switch (d_horzFormat)
    {
        case HorzStretched:
        case HorzTiled:
        case LeftAligned:
            return 0;
            break;

        case HorzCentred:
            return PixelAligned((d_area.getWidth() - sz.d_width) * 0.5f);
            break;

        case RightAligned:
            return d_area.getWidth() - sz.d_width;
            break;

        default:
            throw InvalidRequestException("An unknown horizontal formatting value was specified in a RenderableImage object.");
    }
}

float RenderableImage::getBaseYCoord(const Size& sz) const
{
    switch (d_vertFormat)
    {
        case VertStretched:
        case VertTiled:
        case TopAligned:
            return 0;
            break;

        case VertCentred:
            return PixelAligned((d_area.getHeight() - sz.d_height) * 0.5f);
            break;

        case BottomAligned:
            return d_area.getHeight() - sz.d_height;
            break;

        default:
            throw InvalidRequestException("An unknown vertical formatting value was specified in a RenderableImage object.");
    }
}

Size RenderableImage::getDestinationSize() const
{
    return Size (
        (d_horzFormat == HorzStretched) ? d_area.getWidth() : d_image->getWidth(),
        (d_vertFormat == VertStretched) ? d_area.getHeight() : d_image->getHeight()
    );
}

} 
