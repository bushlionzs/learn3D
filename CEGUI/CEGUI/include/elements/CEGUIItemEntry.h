

#ifndef _CEGUIItemEntry_h_
#define _CEGUIItemEntry_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT ItemEntry : public Window
{
public:
	
	
	virtual Size getItemPixelSize(void) = 0;

	
	
	ItemEntry(const String& type, const String& name);


	
	virtual ~ItemEntry(void);


protected:
	

	
    virtual void    populateRenderCahce() {};


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ItemEntry")	return true;
		return Window::testClassName_impl(class_name);
	}
   
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif


#endif	
