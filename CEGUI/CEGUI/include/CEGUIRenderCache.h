

#ifndef _CEGUIRenderCache_h_
#define _CEGUIRenderCache_h_

#include "CEGUIVector.h"
#include "CEGUIRect.h"
#include "CEGUIImage.h"
#include "CEGUIFont.h"

#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{
    
	class Window;
    class CEGUIEXPORT RenderCache
    {
    public:
        
        RenderCache();

        
        ~RenderCache();

        
        bool hasCachedImagery() const;

        
        void render(const Point& basePos, float baseZ, const Rect& clipper, float xtex = 1.0f, float ytex = 1.0f) const;

        
        void clearCachedImagery();

        
        void cacheImage(const Image& image, const Rect& destArea, float zOffset, const ColourRect& cols, const Rect* clipper = 0, bool clipToDisplay = false);
		
		
		void cacheImageTri(const Image& image, const Rect& destArea, const Point* uv,
			float zOffset, const colour& col);

        
        void cacheText(const Window* OwnerWindow, const String& text, const Font* font, TextFormatting format, const Rect& destArea, float zOffset, const ColourRect& cols, const Rect* clipper = 0, bool clipToDisplay = false, float fScaleX = 1.0, float fScaleY = 1.0 );

    private:
        
		
		struct TriangleClipper
		{
			Point uv[3];
		};

        struct ImageInfo
        {
            const Image* source_image;
            Rect target_area;
            float z_offset;
            ColourRect colours;
            Rect customClipper;
            bool usingCustomClipper;
            bool clipToDisplay;
			
			TriangleClipper* pTriangleClipper;
        };

        
        struct TextInfo
        {
            String text;
            const Font* source_font;
            TextFormatting formatting;
            Rect target_area;
            float z_offset;
            ColourRect colours;
            Rect customClipper;
            bool usingCustomClipper;
            bool clipToDisplay;
			float fScaleX;
			float fScaleY;
			const Window* OwnerWindow;
			bool dirty;
        };

        typedef std::vector<ImageInfo>  ImageryList;
        typedef std::vector<TextInfo>   TextList;

        ImageryList d_cachedImages;     
        TextList d_cachedTexts;         
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif


#endif  
