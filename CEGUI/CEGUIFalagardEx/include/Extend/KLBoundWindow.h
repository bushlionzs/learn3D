#ifndef _FalBoundWindow_h_
#define _FalBoundWindow_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLBoundWindowProperties.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLBoundWindow : public Window
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLBoundWindow(const String& type, const String& name);

        
        ~KLBoundWindow();


		
		void		offsetPixelPosition(const Vector2& offset);

    protected:
        


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLBoundWindow")	return true;
			return Window::testClassName_impl(class_name);
		}

	private:
        

        
        
        void addBoundWindowProperties(void);
    };

    
    class FALAGARDBASE_API KLBoundWindowFactory : public WindowFactory
    {
    public:
        KLBoundWindowFactory(void) : WindowFactory(KLBoundWindow::WidgetTypeName) { }
        ~KLBoundWindowFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

}

#endif
