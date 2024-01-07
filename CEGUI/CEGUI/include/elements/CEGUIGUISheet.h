

#ifndef _CEGUIGUISheet_h_
#define _CEGUIGUISheet_h_

#include "CEGUIWindow.h"
#include "CEGUIWindowFactory.h"



namespace CEGUI
{

class CEGUIEXPORT GUISheet : public Window
{
public:
    
    
    static const String WidgetTypeName;             


    
    
    GUISheet(const String& type, const String& name) : Window(type, name) {}


    
    virtual ~GUISheet(void) {}


protected:
    
    virtual void    drawSelf(float z) {}


    
    void initialise(void)
    {
        Window::initialise();

        setMaximumSize(Size(1.0f, 1.0f));
        setSize(Size(1.0f, 1.0f));
    }


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"GUISheet")	return true;
		return Window::testClassName_impl(class_name);
	}
};



class GUISheetFactory : public WindowFactory
{
public:
    
    GUISheetFactory(void) : WindowFactory(GUISheet::WidgetTypeName) { }
    ~GUISheetFactory(void){}


    
    Window* createWindow(const String& name)
    {
        return new GUISheet(d_type, name);
    }


    
    virtual void    destroyWindow(Window* window)    { if (window->getType() == d_type) delete window; }
};


typedef GUISheet DefaultWindow;


} 


#endif  
