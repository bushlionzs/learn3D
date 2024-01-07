#ifndef _FalMultiIMEEditBox_h_
#define _FalMultiIMEEditBox_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "FalMultiLineEditbox.h"
#include "KLMultiIMEEditBoxProperties.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLMultiIMEEditBox : public FalagardMultiLineEditbox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLMultiIMEEditBox(const String& type, const String& name);

        
        ~KLMultiIMEEditBox();

		
		
		virtual void	resetCaretBlink(void);

		
		virtual	void	onCaratMoved(WindowEventArgs& e);

		
		virtual bool	hasInputFocus(void) const;

    protected:
        
		virtual void			onMouseButtonDown(MouseEventArgs& e);
		virtual void			onActivated(ActivationEventArgs& e);
		virtual void			onDeactivated(ActivationEventArgs& e);
		virtual void			cacheCaratImagery(const Rect& textArea);
		virtual void			updateSelf(float elapsed);
		virtual void			onParentHidden(void);
		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLMultiIMEEditBox")	return true;
			return FalagardMultiLineEditbox::testClassName_impl(class_name);
		}

	private:
        
		static KLMultiIMEEditBoxProperties::DefaultEditBox	d_defaultEditBoxProperty;


        
        float	d_lastTextOffset;			
		

		double	d_blinkTime;				
		double	d_lastBlink;				
		bool	d_caretOn;					

		int		d_lastTextLen;				

       

        
        void addMultiIMEEditBoxProperties(void);
	};

    
    class FALAGARDBASE_API KLMultiIMEEditBoxFactory : public WindowFactory
    {
    public:
        KLMultiIMEEditBoxFactory(void) : WindowFactory(KLMultiIMEEditBox::WidgetTypeName) { }
        ~KLMultiIMEEditBoxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

}

#endif