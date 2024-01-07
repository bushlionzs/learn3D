

#include "FalButton.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardButton::WidgetTypeName[] = "Falagard/Button";

    FalagardButton::FalagardButton(const String& type, const String& name) :
        PushButton(type, name)
    {
		d_recalculation = false;
    }

    FalagardButton::~FalagardButton()
    {
    }

    void FalagardButton::drawSelf(float z)
    {
        
        
        

        
        if (d_needsRedraw)
        {
            
            d_renderCache.clearCachedImagery();
            
            d_needsRedraw = false;
            
            PushButton::drawSelf(z);
        }

        
        Window::drawSelf(z);
    }

    void FalagardButton::drawNormal(float z)
    {
        doButtonRender("Normal");

        
        if (d_useNormalImage)
        {
            ColourRect colours(d_normalImage.getColours());
            colours.setAlpha(getEffectiveAlpha());
            d_normalImage.setColours(colours);
            d_normalImage.draw(d_renderCache);
        }
    }

    void FalagardButton::drawHover(float z)
    {
        doButtonRender("Hover");

        
        if (d_useHoverImage)
        {
            ColourRect colours(d_hoverImage.getColours());
            colours.setAlpha(getEffectiveAlpha());
            d_hoverImage.setColours(colours);
            d_hoverImage.draw(d_renderCache);
        }
    }

    void FalagardButton::drawPushed(float z)
    {
        doButtonRender("Pushed");

        
        if (d_usePushedImage)
        {
            ColourRect colours(d_pushedImage.getColours());
            colours.setAlpha(getEffectiveAlpha());
            d_pushedImage.setColours(colours);
            d_pushedImage.draw(d_renderCache);
        }
    }

    void FalagardButton::drawDisabled(float z)
    {
        doButtonRender("Disabled");

        
        if (d_useDisabledImage)
        {
            ColourRect colours(d_disabledImage.getColours());
            colours.setAlpha(getEffectiveAlpha());
            d_disabledImage.setColours(colours);
            d_disabledImage.draw(d_renderCache);
        }
    }

    void FalagardButton::doButtonRender(const String& state)
    {
        
        
        

        
        if (d_useStandardImagery)
        {
			d_validSize = 0;

            const StateImagery* imagery;

            try
            {
                
                const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
                
                
                imagery = wlf.isStateImageryPresent(state) ? &wlf.getStateImagery(state) : &wlf.getStateImagery("Normal");
            }
            
            catch (UnknownObjectException)
            {
                
                return;
            }

            
            
            
            imagery->render(*this);
        }
    }

	Size FalagardButton::getRenderSize()
	{
		const Font* font = getFont();
		if( font == 0 )
		{
			Logger::getSingleton().logEvent((utf8*)"FalagardButton::getRenderSize() out side. (getFont() == NULL)");
			return Window::getRenderSize();
		}
		if( d_text.empty() )
		{
			Logger::getSingleton().logEvent((utf8*)"FalagardButton::getRenderSize() out side. (d_text == NULL)");
		}

		Rect absarea( 0, 0, 1024,768 );
		Size size = font->getFormattedSize( d_text, absarea, (TextFormatting)LeftAligned );
		size.d_width += 30;
		size.d_height += 10;
		return size;
	}

    
    
    
    Window* FalagardButtonFactory::createWindow(const String& name)
    {
        return new FalagardButton(d_type, name);
    }

    void FalagardButtonFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
