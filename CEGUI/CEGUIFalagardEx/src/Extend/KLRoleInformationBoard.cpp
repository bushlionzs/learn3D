#include "KLRoleInformationBoard.h"



namespace CEGUI
{
	
	
	
	
	
    const utf8  KLRoleInformationBoard::WidgetTypeName[] = "Falagard/RoleInformationBoard";

    KLRoleInformationBoard::KLRoleInformationBoard(const String& type, const String& name) :
        Window(type, name)
    {
        addCreatureBoardProperties();
    }

    KLRoleInformationBoard::~KLRoleInformationBoard()
    {
    }

	void KLRoleInformationBoard::addCreatureBoardProperties(void)
    {
    }
   
    
    Window* KLRoleInformationBoardFactory::createWindow(const String& name)
    {
        return new KLRoleInformationBoard(d_type, name);
    }

    void KLRoleInformationBoardFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}