

#include "CEGUIWindowFactory.h"



namespace CEGUI
{

	bool WindowFactory::addStaticProperty(const String& dictoryName)
{
	
	if(d_propertyDictory.find(dictoryName) != d_propertyDictory.end()) return false;

	
	d_propertyDictory.insert(dictoryName);
	return true;
}

} 
