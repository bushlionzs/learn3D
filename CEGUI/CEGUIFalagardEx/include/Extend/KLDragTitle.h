#ifndef _FalDragTitle_h_
#define _FalDragTitle_h_

#include "CEGUIWindow.h"
#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLDragTitleProperties.h"


namespace CEGUI
{

	class KLBoundWindow;
	
	
	
	
	
	class FALAGARDBASE_API KLDragTitle : public Window
	{
	public:
        static const utf8   WidgetTypeName[];       

        
		KLDragTitle(const String& type, const String& name);

		
        ~KLDragTitle();

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLDragTitle")	return true;
			return Window::testClassName_impl(class_name);
		}


		
		String			getDragTarget(void) const;	
		void			setDragTarget(const String& strName);

	protected:
		
		virtual void	onMouseMove(MouseEventArgs& e);
		virtual void	onMouseButtonDown(MouseEventArgs& e);
		virtual void	onMouseButtonUp(MouseEventArgs& e);
		virtual void	onCaptureLost(WindowEventArgs& e);

        
		KLBoundWindow*	d_dragTarget;			
		bool					d_dragging;				
		Point					d_dragPoint;			

	private:
        
		static KLDragTitleProperties::DragTarget		d_dragTargetProperty;

        

        
        void addDragTitleProperties(void);


	};

    
    class FALAGARDBASE_API KLDragTitleFactory : public WindowFactory
    {
    public:
        KLDragTitleFactory(void) : WindowFactory(KLDragTitle::WidgetTypeName) { }
        ~KLDragTitleFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

}

#endif