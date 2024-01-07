

#ifndef _CEGUIPropertySet_h_
#define _CEGUIPropertySet_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIIteratorBase.h"
#include "CEGUIProperty.h"
#include <map>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{

class CEGUIEXPORT PropertySet
{
public:
	
	PropertySet(void) {}


	
	virtual ~PropertySet(void) {}


	
	void	addProperty(Property* property);


	
	void	removeProperty(const String& name);


	
	void	clearProperties(void);


	
	bool	isPropertyPresent(const String& name) const;


	
	const String&	getPropertyHelp(const String& name) const;


	
	String	getProperty(const String& name, const PropertyReceiver& receiver) const;


	
	void	setProperty(const String& name, const String& value, PropertyReceiver& receiver) const;


	
	bool	isPropertyDefault(const String& name, const PropertyReceiver& receiver) const;


	
	String	getPropertyDefault(const String& name, const PropertyReceiver& receiver) const;

private:
	typedef std::map<String, Property*>	PropertyRegistry;
	PropertyRegistry	d_properties;


public:
	
	typedef	ConstBaseIterator<PropertyRegistry>	PropertyIterator;

	
	PropertyIterator	getIterator(void) const;
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
