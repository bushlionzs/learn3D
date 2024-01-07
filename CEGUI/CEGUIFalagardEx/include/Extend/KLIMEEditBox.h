#ifndef _FalIMEEditBox_h_
#define _FalIMEEditBox_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLIMEEditBoxProperties.h"
#include "FalEditbox.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLIMEEditBox : public FalagardEditbox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLIMEEditBox(const String& type, const String& name);

        
        ~KLIMEEditBox();

		
		
		
		virtual void	resetCaretBlink(void);

		
		virtual	void	onCaratMoved(WindowEventArgs& e);


		
		virtual bool	hasInputFocus(void) const;

		virtual void	setCaratIndex(size_t carat_pos);

    protected:
        
		virtual	void			onMouseButtonDown(MouseEventArgs& e);
        virtual void			populateRenderCache();
		virtual void			updateSelf(float elapsed);
		virtual void			onActivated(ActivationEventArgs& e);
		virtual void			onDeactivated(ActivationEventArgs& e);
		virtual void			onParentHidden(void);

        virtual size_t			getTextIndexFromPosition(const Point& pt) const;

        
        float	d_lastTextOffset;			
		

		double	d_blinkTime;				
		double	d_lastBlink;				
		bool	d_caretOn;					

		int		d_lastTextLen;				

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLIMEEditBox")	return true;
			return FalagardEditbox::testClassName_impl(class_name);
		}

	private:
        
		static KLIMEEditBoxProperties::DefaultEditBox	d_defaultEditBoxProperty;

       

        
        void addIMEEditBoxProperties(void);
	};

    
    class FALAGARDBASE_API KLIMEEditBoxFactory : public WindowFactory
    {
    public:
        KLIMEEditBoxFactory(void) : WindowFactory(KLIMEEditBox::WidgetTypeName) { }
        ~KLIMEEditBoxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}

#endif