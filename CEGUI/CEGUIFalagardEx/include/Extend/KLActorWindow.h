#ifndef _FalActorWindow_h_
#define _FalActorWindow_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLActorWindowProperties.h"
#include "IKLActorWindow.h"
#include "CEGUIRenderableImage.h"
#include "elements\CEGUIStaticImage.h"


namespace CEGUI
{
	
	
	
	
	
	class FALAGARDBASE_API KLActorWindow : public StaticImage, public IKLActorWindow
	{
	public:
		static const utf8   WidgetTypeName[];	


        static const String EventNamespace;		

        static const String EventMeshHook;		
        static const String EventMeshShown;		
        static const String EventMeshHidden;	

		
		KLActorWindow(const String& type, const String& name);

		
		~KLActorWindow(void);


		

		
		String			getFakeObject(void) const { return d_fakeObjectName; }
		
		void			setFakeObject(const String& fakeObject);

		
		String			getShowControl(void) const { return d_showControlWindowName; }
		
		void			setShowControl(const String& windowName);

        
		
		virtual void	subscribeShownEvent(Event::Subscriber subscriber);
		
		virtual void	subscribeHidenEvent(Event::Subscriber subscriber);
		
		virtual void	subscribeHookEvent(Event::Subscriber subscriber);

	protected:
        
		virtual void			populateRenderCache();
		virtual void			onParentHidden(void);

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLActorWindow")	return true;
			return StaticImage::testClassName_impl(class_name);
		}

		
		String				d_fakeObjectName;			
		String				d_showControlWindowName;	

		
		bool			handleControlShown(const CEGUI::EventArgs& e);
		bool			handleControlHidden(const CEGUI::EventArgs& e);

	private:
        
		static KLActorWindowProperties::FakeObject		d_fakeObjectProperty;
		static KLActorWindowProperties::ShowControl	d_showControlProperty;

        

        
        void addMeshWindowProperties(void);
	};

    
	class FALAGARDBASE_API KLActorWindowFactory : public WindowFactory
    {
    public:
        KLActorWindowFactory(void) : WindowFactory(KLActorWindow::WidgetTypeName) { }
        ~KLActorWindowFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};

#endif