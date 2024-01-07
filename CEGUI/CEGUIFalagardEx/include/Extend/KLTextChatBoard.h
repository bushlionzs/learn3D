#ifndef _FalagardTextChatBoard_h_
#define _FalagardTextChatBoard_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLTextChatBoardProperties.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLTextChatBoard : public Window
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLTextChatBoard(const String& type, const String& name);

        
        ~KLTextChatBoard();

		
		virtual float		resizeSelf(float maxWidth);

		virtual void		updateSelf(float);

		virtual bool		isMouseHollow(const Point* pPosition) const;
		virtual bool		isMouseLButtonHollow(const Point* pPosition) const;
		virtual bool		isMouseRButtonHollow(const Point* pPosition) const;
		virtual void		onMouseLeaves( MouseEventArgs& e );

		
		virtual bool		getCacheRenderInfo() const;

		
		virtual bool		setAnimateRuntime(const AnimateRuntime* aniRuntime);

		
		virtual bool		setFontBlinkRuntime(const FontBlinkRuntime* fontRuntime);

		
		virtual bool		setHyperLinkRuntime(int guid, const String name, const Rect hyper_rect);

		virtual String		getHyperLinkContex(const Point* position)const;

		void				setFadeEnabled(bool setting)	{ d_fadeEnabled = setting; }

    protected:
        
		virtual void			populateRenderCache();

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLTextChatBoard")	return true;
			return Window::testClassName_impl(class_name);
		}

		

	private:
        

        

        
		void addChatBoardProperties(void);

		bool						d_fadeEnabled;
    };

    
    class FALAGARDBASE_API KLTextChatBoardFactory : public WindowFactory
    {
    public:
        KLTextChatBoardFactory(void) : WindowFactory(KLTextChatBoard::WidgetTypeName) { }
        ~KLTextChatBoardFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

}

#endif