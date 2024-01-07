

#include "FalPopupMenu.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardPopupMenu::WidgetTypeName[] = "Falagard/PopupMenu";

    FalagardPopupMenu::FalagardPopupMenu(const String& type, const String& name) :
        PopupMenu(type, name)
    {
    }

    FalagardPopupMenu::~FalagardPopupMenu()
    {
    }

    void FalagardPopupMenu::populateRenderCache()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

	void FalagardPopupMenu::onSized(WindowEventArgs& e)
	{
		Window::onSized(e);

		sizeToContent_impl();
	}

    void FalagardPopupMenu::sizeToContent_impl(void)
    {
        Rect renderArea(getItemRenderArea());
        Rect wndArea(getAbsoluteRect());

        
        Size sz(getContentSize());

        
        sz.d_width  += wndArea.getWidth() - renderArea.getWidth();
        sz.d_height += wndArea.getHeight() - renderArea.getHeight();

		sz.d_width /= System::getSingleton().getRenderer()->getSize().d_width;
		sz.d_height /= System::getSingleton().getRenderer()->getSize().d_height;

		setSize(Relative,sz);
    }

    Rect FalagardPopupMenu::getItemRenderArea(void) const
    {
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        return wlf.getNamedArea("ItemRenderArea").getArea().getPixelRect(*this);
    }


    
    
    
    Window* FalagardPopupMenuFactory::createWindow(const String& name)
    {
        return new FalagardPopupMenu(d_type, name);
    }

    void FalagardPopupMenuFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
