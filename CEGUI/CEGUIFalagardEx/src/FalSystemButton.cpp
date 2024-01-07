

#include "FalSystemButton.h"


namespace CEGUI
{
    const utf8 FalagardSystemButton::WidgetTypeName[] = "Falagard/SystemButton";

    FalagardSystemButton::FalagardSystemButton(const String& type, const String& name) :
        FalagardButton(type, name)
    {
    }

    FalagardSystemButton::~FalagardSystemButton()
    {
    }

    Rect FalagardSystemButton::getPixelRect(void) const
    {
        
        if (d_parent && d_parent->getParent() && isClippedByParent())
        {
            return d_parent->getParent()->getInnerRect().getIntersection(getUnclippedPixelRect());
        }
        
        else
        {
            return System::getSingleton().getRenderer()->getRect().getIntersection(getUnclippedPixelRect());
        }
    }

    
    
    
    Window* FalagardSystemButtonFactory::createWindow(const String& name)
    {
        return new FalagardSystemButton(d_type, name);
    }

    void FalagardSystemButtonFactory::destroyWindow(Window* window)
    {
        delete window;
    }


} 
