

#include "FalStaticImage.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardStaticImage::WidgetTypeName[] = "Falagard/StaticImage";

    FalagardStaticImage::FalagardStaticImage(const String& type, const String& name) :
        StaticImage(type, name)
    {
    }

    FalagardStaticImage::~FalagardStaticImage()
    {
    }

    void FalagardStaticImage::populateRenderCache()
    {
		d_renderCache.clearCachedImagery();
		StaticImage::populateRenderCache();

        const StateImagery* imagery;
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);

		bool is_enabled = !isDisabled();

        
        if (d_frameEnabled)
        {
            imagery = &wlf.getStateImagery(is_enabled ? "EnabledFrame" : "DisabledFrame");
            
            imagery->render(*this);
        }

        
        if (d_backgroundEnabled)
        {
            imagery = &wlf.getStateImagery(is_enabled ? "EnabledBackground" : "DisabledBackground");
            
            imagery->render(*this);
        }

        
        imagery = &wlf.getStateImagery(is_enabled ? "Enabled" : "Disabled");
        
        imagery->render(*this);

        
    }

    Rect FalagardStaticImage::getUnclippedInnerRect(void) const
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);

        String area_name(isFrameEnabled() ? "WithFrame" : "NoFrame");
        area_name += "ImageRenderArea";

        if (wlf.isNamedAreaDefined(area_name))
            return wlf.getNamedArea(area_name).getArea().getPixelRect(*this).offset(getUnclippedPixelRect().getPosition());
        else
            return StaticImage::getUnclippedInnerRect();
    }

    
    
    
    Window* FalagardStaticImageFactory::createWindow(const String& name)
    {
#ifdef _DEBUG
		static int num = 0;
		++num;
#endif

        return new FalagardStaticImage(d_type, name);
    }

    void FalagardStaticImageFactory::destroyWindow(Window* window)
    {
#ifdef _DEBUG
		static int num = 0;
		++num;
#endif

        delete window;
    }

} 
