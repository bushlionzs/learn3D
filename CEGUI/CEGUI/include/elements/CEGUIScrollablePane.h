

#ifndef _CEGUIScrollablePane_h_
#define _CEGUIScrollablePane_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIScrollablePaneProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT ScrollablePane : public Window
    {
    public:
        
        static const String EventNamespace;                 
        static const String EventContentPaneChanged;        
        static const String EventVertScrollbarModeChanged;	
        static const String EventHorzScrollbarModeChanged;	
        static const String EventAutoSizeSettingChanged;    
        static const String EventContentPaneScrolled;       

        
        
        ScrollablePane(const String& type, const String& name);

        
        ~ScrollablePane(void);

        
        
        const ScrolledContainer* getContentPane(void) const;

        
        bool	isVertScrollbarAlwaysShown(void) const;
        
        void	setShowVertScrollbar(bool setting);

        
        bool	isHorzScrollbarAlwaysShown(void) const;

        
        void	setShowHorzScrollbar(bool setting);

        
        bool isContentPaneAutoSized(void) const;

        
        void setContentPaneAutoSized(bool setting);

        
        const Rect& getContentPaneArea(void) const;

        
        void setContentPaneArea(const Rect& area);

        
        float getHorizontalStepSize(void) const;

        
        void setHorizontalStepSize(float step);

        
        float getHorizontalOverlapSize(void) const;

        
        void setHorizontalOverlapSize(float overlap);

        
        float getHorizontalScrollPosition(void) const;

        
        void setHorizontalScrollPosition(float position);

        
        float getVerticalStepSize(void) const;

        
        void setVerticalStepSize(float step);

        
        float getVerticalOverlapSize(void) const;

        
        void setVerticalOverlapSize(float overlap);

        
        float getVerticalScrollPosition(void) const;

        
        void setVerticalScrollPosition(float position);

        
        void initialise(void);

    protected:
        
        
        virtual Scrollbar* createHorizontalScrollbar(const String& name) const = 0;

        
        virtual Scrollbar* createVerticalScrollbar(const String& name) const = 0;

        
        virtual Rect getViewableArea(void) const = 0;

        

		
	    void configureScrollbars(void);

        
        bool isVertScrollbarNeeded(void) const;

        
        bool isHorzScrollbarNeeded(void) const;

        
        void updateContainerPosition(void);


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"ScrollablePane")	return true;
			return Window::testClassName_impl(class_name);
		}


        
        
        virtual void onContentPaneChanged(WindowEventArgs& e);

        
        virtual void onVertScrollbarModeChanged(WindowEventArgs& e);

        
        virtual void onHorzScrollbarModeChanged(WindowEventArgs& e);

        
        virtual void onAutoSizeSettingChanged(WindowEventArgs& e);

        
        virtual void onContentPaneScrolled(WindowEventArgs& e);

        
        
        bool handleScrollChange(const EventArgs&  e);

        
        bool handleContentAreaChange(const EventArgs& e);

        
        bool handleAutoSizePaneChanged(const EventArgs& e);

        
        void addChild_impl(Window* wnd);
        void removeChild_impl(Window* wnd);
        void onSized(WindowEventArgs& e);
        void onMouseWheel(MouseEventArgs& e);

        
        bool    d_forceVertScroll;		
        bool    d_forceHorzScroll;		
        Rect    d_contentRect;          
        float   d_vertStep;             
        float   d_vertOverlap;          
        float   d_horzStep;             
        float   d_horzOverlap;          

        
        Scrollbar*  d_vertScrollbar;        
        Scrollbar*  d_horzScrollbar;        
        ScrolledContainer*  d_container;    

    private:
	    
        static ScrollablePaneProperties::ForceHorzScrollbar     d_horzScrollbarProperty;
        static ScrollablePaneProperties::ForceVertScrollbar     d_vertScrollbarProperty;
	    static ScrollablePaneProperties::ContentPaneAutoSized	d_autoSizedProperty;
	    static ScrollablePaneProperties::ContentArea            d_contentAreaProperty;
        static ScrollablePaneProperties::HorzStepSize           d_horzStepProperty;
        static ScrollablePaneProperties::HorzOverlapSize        d_horzOverlapProperty;
        static ScrollablePaneProperties::HorzScrollPosition     d_horzScrollPositionProperty;
        static ScrollablePaneProperties::VertStepSize           d_vertStepProperty;
        static ScrollablePaneProperties::VertOverlapSize        d_vertOverlapProperty;
        static ScrollablePaneProperties::VertScrollPosition     d_vertScrollPositionProperty;

	    
	    void addScrollablePaneProperties(void);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
