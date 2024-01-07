#include "KLBoundWindow.h"
#include <CEGUIWindowManager.h>


namespace CEGUI
{
	
	
	
	
	
	const utf8  KLBoundWindow::WidgetTypeName[] = "Falagard/BoundWindow";
	
	KLBoundWindow::KLBoundWindow(const String& type, const String& name) :
        Window(type, name)
    {
		addBoundWindowProperties();
    }

	KLBoundWindow::~KLBoundWindow()
	{
	}

	void KLBoundWindow::addBoundWindowProperties(void)
    {
    }

	
	void KLBoundWindow::offsetPixelPosition(const Vector2& offset)
	{
		UVector2 uOffset;

		if (getMetricsMode() == Relative)
		{
			Size sz = getParentSize();

			uOffset.d_x = cegui_reldim((sz.d_width != 0) ? offset.d_x / sz.d_width : 0);
			uOffset.d_y = cegui_reldim((sz.d_height != 0) ? offset.d_y / sz.d_height : 0);
		}
		else
		{
			uOffset.d_x = cegui_absdim(PixelAligned(offset.d_x));
			uOffset.d_y = cegui_absdim(PixelAligned(offset.d_y));
		}

		setWindowPosition(d_area.getPosition() + uOffset);
	}

    
    
    
    Window* KLBoundWindowFactory::createWindow(const String& name)
    {
        return new KLBoundWindow(d_type, name);
    }

    void KLBoundWindowFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}