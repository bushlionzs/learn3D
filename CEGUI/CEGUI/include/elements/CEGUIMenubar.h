

#ifndef _CEGUIMenubar_h_
#define _CEGUIMenubar_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIMenuBase.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Menubar : public MenuBase
{
public:
	static const String EventNamespace;				

	
	
	Menubar(const String& type, const String& name);


	
	virtual ~Menubar(void);


protected:
	
	
	virtual void	layoutItemWidgets();


	
	virtual Size getContentSize();


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Menubar")	return true;
		return MenuBase::testClassName_impl(class_name);
	}

};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
