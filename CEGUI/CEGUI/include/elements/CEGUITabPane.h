

#ifndef _CEGUITabPane_h_
#define _CEGUITabPane_h_

#include "elements/CEGUIStatic.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT TabPane : public Static
{
public:
	
	
    TabPane(const String& type, const String& name) : Static(type, name) {}


	
    virtual ~TabPane(void) {}


	

	

protected:
	

    
	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Tabpane")	return true;
		return Static::testClassName_impl(class_name);
	}

	

private:
	


	
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
