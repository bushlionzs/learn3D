

#include "FalThumb.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardThumb::WidgetTypeName[] = "Falagard/Thumb";


    FalagardThumb::FalagardThumb(const String& type, const String& name) :
        Thumb(type, name)
    {
    }

    FalagardThumb::~FalagardThumb()
    {
    }

    void FalagardThumb::drawSelf(float z)
    {
        
        
        

        
        Thumb::drawSelf(z);

        
        Window::drawSelf(z);
    }

    void FalagardThumb::drawNormal(float z)
    {
        doThumbRender("Normal");
    }

    void FalagardThumb::drawHover(float z)
    {
        doThumbRender("Hover");
    }

    void FalagardThumb::drawPushed(float z)
    {
        doThumbRender("Pushed");
    }

    void FalagardThumb::drawDisabled(float z)
    {
        doThumbRender("Disabled");
    }

    void FalagardThumb::doThumbRender(const String& state)
    {
        
        
        

        
        if (d_needsRedraw)
        {
            
            d_renderCache.clearCachedImagery();
            
            d_needsRedraw = false;

            
            if (d_useStandardImagery)
            {
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
    }


    
    
    
    Window* FalagardThumbFactory::createWindow(const String& name)
    {
        return new FalagardThumb(d_type, name);
    }

    void FalagardThumbFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
