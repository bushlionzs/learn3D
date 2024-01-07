

#ifndef _CEGUIDragContainer_h_
#define _CEGUIDragContainer_h_

#include "CEGUIWindow.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIDragContainerProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT DragContainer : public Window
    {
    public:
        
        static const String WidgetTypeName;     
        static const String EventNamespace;     
        static const String EventDragStarted;   
        static const String EventDragEnded;     
        static const String EventDragPositionChanged;   
        static const String EventDragEnabledChanged;    
        static const String EventDragAlphaChanged;      
        static const String EventDragMouseCursorChanged;
        static const String EventDragThresholdChanged;  
        static const String EventDragDropTargetChanged; 

        
        
        DragContainer(const String& type, const String& name);

        
        virtual ~DragContainer(void);

        
        
        bool isDraggingEnabled(void) const;

        
        void setDraggingEnabled(bool setting);

        
        bool isBeingDragged(void) const;

        
        float getPixelDragThreshold(void) const;

        
        void setPixelDragThreshold(float pixels);

        
        float getDragAlpha(void) const;

        
        void setDragAlpha(float alpha);

        
        const Image* getDragCursorImage(void) const;

        
        void setDragCursorImage(const Image* image);

        
        void setDragCursorImage(MouseCursorImage image);

        
        void setDragCursorImage(const String& imageset, const String& image);

        
        Window* getCurrentDropTarget(void) const;

    protected:
        

        		
        bool isDraggingThresholdExceeded(const Point& local_mouse);

	    
        void initialiseDragging(void);

        
        void doDragging(const Point& local_mouse);

        
        void updateActiveMouseCursor(void) const;


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"DragContainer")	return true;
			return Window::testClassName_impl(class_name);
		}


        
        void drawSelf(float z);

        

        
        virtual void onMouseButtonDown(MouseEventArgs& e);
        virtual void onMouseButtonUp(MouseEventArgs& e);
        virtual void onMouseMove(MouseEventArgs& e);
        virtual void onCaptureLost(WindowEventArgs& e);
        virtual void onAlphaChanged(WindowEventArgs& e);
        virtual void onClippingChanged(WindowEventArgs& e);

        
        
        virtual void onDragStarted(WindowEventArgs& e);

        
        virtual void onDragEnded(WindowEventArgs& e);

        
        virtual void onDragPositionChanged(WindowEventArgs& e);

        
        virtual void onDragEnabledChanged(WindowEventArgs& e);

        
        virtual void onDragAlphaChanged(WindowEventArgs& e);

        
        virtual void onDragMouseCursorChanged(WindowEventArgs& e);

        
        virtual void onDragThresholdChanged(WindowEventArgs& e);

        
        virtual void onDragDropTargetChanged(DragDropEventArgs& e);

        
        bool    d_draggingEnabled;  
        bool    d_leftMouseDown;    
        bool    d_dragging;         
        Point   d_dragPoint;        
        Point   d_startPosition;    
        float   d_dragThreshold;    
        float   d_dragAlpha;        
        float   d_storedAlpha;      
        bool    d_storedClipState;  
        Window* d_dropTarget;       
        const Image* d_dragCursorImage; 

    private:
        
        static DragContainerProperties::DragAlpha       d_dragAlphaProperty;
        static DragContainerProperties::DragCursorImage d_dragCursorImageProperty;
        static DragContainerProperties::DraggingEnabled d_dragEnabledProperty;
        static DragContainerProperties::DragThreshold   d_dragThresholdProperty;

        
        
        void addDragContainerProperties(void);
    };

    
    class DragContainerFactory : public WindowFactory
    {
    public:
        DragContainerFactory(void) : WindowFactory(DragContainer::WidgetTypeName) { }
        ~DragContainerFactory(void){}

        Window* createWindow(const String& name)
        {
            DragContainer* wnd = new DragContainer(d_type, name);
            return wnd;
        }

        void destroyWindow(Window* window)
        {
            if (window->getType() == d_type)
                delete window;
        }

    };


} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
