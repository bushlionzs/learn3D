#ifndef _FalagardRoleInformationBoard_h
#define _FalagardRoleInformationBoard_h

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLRoleInformationBoardProperties.h"


namespace CEGUI
{
    class FALAGARDBASE_API KLRoleInformationBoard : public Window
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLRoleInformationBoard(const String& type, const String& name);

        
        ~KLRoleInformationBoard();

    protected:
        

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLRoleInformationBoard")	return true;
			return Window::testClassName_impl(class_name);
		}

		

	private:
        

        

        
        void addCreatureBoardProperties(void);
    };

    
    class FALAGARDBASE_API KLRoleInformationBoardFactory : public WindowFactory
    {
    public:
        KLRoleInformationBoardFactory(void) : WindowFactory(KLRoleInformationBoard::WidgetTypeName) { }
        ~KLRoleInformationBoardFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };


}


#endif