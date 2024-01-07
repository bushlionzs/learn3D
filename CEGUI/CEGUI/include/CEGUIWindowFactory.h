

#ifndef _CEGUIWindowFactory_h_
#define _CEGUIWindowFactory_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIWindow.h"
#include "CEGUIPropertySet.h"
#include <set>

#if defined (_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT WindowFactory : public PropertySet
{
public:
	
	virtual	Window*	createWindow(const String& name) = 0;

	
	virtual void	destroyWindow(Window* window) = 0;

	
	const String& getTypeName(void) const		{return d_type;}

	bool addStaticProperty(const String& dictoryName);
protected:
	
	WindowFactory(const String& type) : d_type(type) {}

public:		
	virtual ~WindowFactory(void) {}

protected:
	
	String		d_type;		

	typedef std::set< String >	StaticPropertyDictory;
	StaticPropertyDictory d_propertyDictory;
};

#define CEGUI_START_ADD_STATICPROPERTY( className ) \
	if(d_windowFactory && d_windowFactory->addStaticProperty(#className)) \
	{ \

#define CEGUI_ADD_STATICPROPERTY( property ) \
	d_windowFactory->addProperty(property);

#define CEGUI_END_ADD_STATICPROPERTY \
	}

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
