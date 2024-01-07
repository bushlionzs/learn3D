

#include "CEGUIRenderCache.h"
#include "CEGUISystem.h"
#include "CEGUIRenderer.h"
#include "CEGUIWindow.h"



namespace CEGUI
{
	class Window;
    RenderCache::RenderCache()
    {}

    RenderCache::~RenderCache()
    {}

    bool RenderCache::hasCachedImagery() const
    {
        return !(d_cachedImages.empty() && d_cachedTexts.empty());
    }

    void RenderCache::render(const Point& basePos, float baseZ, const Rect& clipper, float xtex, float ytex) const
    {
        Rect displayArea(System::getSingleton().getRenderer()->getRect());
        Rect custClipper;
        const Rect* finalClipper;
        Rect finalRect;

        
        for(ImageryList::const_iterator image = d_cachedImages.begin(); image != d_cachedImages.end(); ++image)
        {
            if (image->usingCustomClipper)
            {
                custClipper = image->customClipper;
                custClipper.offset(basePos);
                custClipper = image->clipToDisplay ? displayArea.getIntersection(custClipper) : clipper.getIntersection(custClipper);
                finalClipper = &custClipper;
            }
            else
            {
                finalClipper = image->clipToDisplay ? &displayArea : &clipper;
            }

            finalRect = image->target_area;
            finalRect.offset(basePos);

			
			if(image->pTriangleClipper)
			{
				image->source_image->drawTri( finalRect, baseZ + image->z_offset, 
					image->colours.d_top_left, image->pTriangleClipper->uv, xtex, ytex );
			}
			else
			{
				image->source_image->draw(finalRect, baseZ + image->z_offset, 
					*finalClipper, image->colours, TopLeftToBottomRight, xtex, ytex);
			}
        }

        
        for(TextList::const_iterator text = d_cachedTexts.begin(); text != d_cachedTexts.end(); ++text)
        {
			if ((*text).dirty )
			{
				
				if( (*text).OwnerWindow->getCacheRenderInfo() )
					break;
			}

            if ((*text).usingCustomClipper)
            {
                custClipper = (*text).customClipper;
                custClipper.offset(basePos);
                custClipper = (*text).clipToDisplay ? displayArea.getIntersection(custClipper) : clipper.getIntersection(custClipper);
                finalClipper = &custClipper;
            }
            else
            {
                finalClipper = (*text).clipToDisplay ? &displayArea : &clipper;
            }

            finalRect = (*text).target_area;
            finalRect.offset(basePos);
			(*text).source_font->drawText((const Window*)(*text).OwnerWindow, (const String&)(*text).text, 
				(const Rect&)finalRect, (float) baseZ + (*text).z_offset, (const Rect&)*finalClipper, 
				(TextFormatting)(*text).formatting, (const ColourRect&)(*text).colours, (float)(*text).fScaleX, (float)(*text).fScaleY );

			bool& dirty = (bool&)(*text).dirty;
			dirty = true;
        }
    }

    void RenderCache::clearCachedImagery()
    {
		
		for(ImageryList::const_iterator image = d_cachedImages.begin(); image != d_cachedImages.end(); ++image)
        {
			if(image->pTriangleClipper)
				delete image->pTriangleClipper;
		}
        d_cachedImages.clear();
        d_cachedTexts.clear();
    }

    void RenderCache::cacheImage(const Image& image, const Rect& destArea, float zOffset, 
		const ColourRect& cols, const Rect* clipper, bool clipToDisplay)
    {
        ImageInfo imginf;
        imginf.source_image = &image;
        imginf.target_area  = destArea;
        imginf.z_offset     = zOffset;
        imginf.colours      = cols;
        imginf.clipToDisplay= clipToDisplay;

        if (clipper)
        {
            imginf.customClipper = *clipper;
            imginf.usingCustomClipper = true;
        }
        else
        {
            imginf.usingCustomClipper = false;
        }

		imginf.pTriangleClipper = NULL;

        d_cachedImages.push_back(imginf);
    }

	
	void RenderCache::cacheImageTri(const Image& image, const Rect& destArea, const Point* uv,
		float zOffset, const colour& col)
	{
	    ImageInfo imginf;
        imginf.source_image = &image;
        imginf.target_area  = destArea;
        imginf.z_offset     = zOffset;
        imginf.colours.setColours(col);
        imginf.clipToDisplay = false;
        imginf.usingCustomClipper = false;

		imginf.pTriangleClipper = new TriangleClipper;
		memcpy(&imginf.pTriangleClipper->uv[0], uv, sizeof(Point)*3);

        d_cachedImages.push_back(imginf);
	}


    void RenderCache::cacheText( const Window* OwnerWindow, const String& text, const Font* font, TextFormatting format, const Rect& destArea, float zOffset, const ColourRect& cols, const Rect* clipper, bool clipToDisplay, float fScaleX, float fScaleY )
    {
        TextInfo txtinf;
		utf32 color = utf32( cols.d_top_left.getARGB() );
		utf32 bkColor = 0xFC000000;
		
		
		color = ( color & 0x00ffffff ) | 0xfB000000;  
		txtinf.text         = color;
		txtinf.text			+= bkColor +  text;
        txtinf.source_font  = font;
        txtinf.formatting   = format;
        txtinf.target_area  = destArea;

        txtinf.z_offset     = zOffset;
        txtinf.colours      = cols;
        txtinf.clipToDisplay= clipToDisplay;
		txtinf.fScaleX		= fScaleX;
		txtinf.fScaleY		= fScaleY;
		txtinf.OwnerWindow  = OwnerWindow;
		txtinf.dirty	    = false;

        if (clipper)
        {
			txtinf.usingCustomClipper = true;
            txtinf.customClipper = *clipper;
			
			
			txtinf.customClipper.d_top -= 1.f;
			txtinf.customClipper.d_bottom += 1.f;
			txtinf.customClipper.d_left -= 1.f;
			txtinf.customClipper.d_right += 1.f;            
        }
        else
        {
            txtinf.usingCustomClipper = false;
        }

		

		

        d_cachedTexts.push_back(txtinf);
    }


} 
