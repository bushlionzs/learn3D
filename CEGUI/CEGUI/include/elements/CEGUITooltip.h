

#ifndef _CEGUITooltip_h_
#define _CEGUITooltip_h_

#include "CEGUIWindow.h"
#include "elements/CEGUITooltipProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT Tooltip : public Window
    {
    public:
        
        static const String EventNamespace;                 
        static const String EventHoverTimeChanged;          
        static const String EventDisplayTimeChanged;        
        static const String EventFadeTimeChanged;           
        static const String EventTooltipActive;             
        static const String EventTooltipInactive;           

        
        
        Tooltip(const String& type, const String& name);

        
        ~Tooltip(void);

        
        
        void setTargetWindow(Window* wnd);

        
        const Window* getTargetWindow();

        
        void resetTimer(void);

        
        float getHoverTime(void) const;

        
        void setDisplayTime(float seconds);

        
        float getFadeTime(void) const;

        
		int getMaxWidth(void) const { return d_maxWidth; }

        
        void setHoverTime(float seconds);

        
        float getDisplayTime(void) const;

        
        void setFadeTime(float seconds);


        
		void setMaxWidth(int nWidth) { d_maxWidth = nWidth; }

        
        
        void positionSelf(void);

    protected:
        
        
        void doActiveState(float elapsed);
        void doInactiveState(float elapsed);
        void doFadeInState(float elapsed);
        void doFadeOutState(float elapsed);

        
        void switchToInactiveState(void);
        void switchToActiveState(void);
        void switchToFadeInState(void);
        void switchToFadeOutState(void);


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"Tooltip")	return true;
			return Window::testClassName_impl(class_name);
		}

        
        virtual Size getTextSize() const;

        
        
        virtual void onHoverTimeChanged(WindowEventArgs& e);

        
        virtual void onDisplayTimeChanged(WindowEventArgs& e);

        
        virtual void onFadeTimeChanged(WindowEventArgs& e);

        
        virtual void onTooltipActive(WindowEventArgs& e);

        
        virtual void onTooltipInactive(WindowEventArgs& e);


        
        void updateSelf(float elapsed);
        void onMouseEnters(MouseEventArgs& e);
        void onTextChanged(WindowEventArgs& e);

        
        
        enum TipState
        {
            Inactive,   
            Active,     
            FadeIn,     
            FadeOut     
        };

        
        TipState    d_state;        
        float       d_elapsed;      
        const Window* d_target;     
        float       d_hoverTime;    
        float       d_displayTime;  
        float       d_fadeTime;     
		int			d_maxWidth;		
		CEGUI::String d_targetName;
    private:
        
        static TooltipProperties::HoverTime      d_hoverTimeProperty;
        static TooltipProperties::DisplayTime    d_displayTimeProperty;
        static TooltipProperties::FadeTime       d_fadeTimeProperty;
        static TooltipProperties::MaxWidth       d_maxWidthProperty;

        
        void addTooltipProperties(void);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
