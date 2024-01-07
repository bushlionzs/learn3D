

#include "CEGUIPropertySet.h"
#include "CEGUIProperty.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"


namespace CEGUI
{


void PropertySet::addProperty(Property* property)
{
	if (property == NULL)
	{
		throw NullObjectException((utf8*)"The given Property object pointer is NULL.");
	}

	if (d_properties.find(property->getName()) != d_properties.end())
	{
		throw AlreadyExistsException((utf8*)"A Property named '" + property->getName() + (utf8*)"' already exists in the PropertySet.");
	}

	d_properties[property->getName()] = property;
}


void PropertySet::removeProperty(const String& name)
{
	PropertyRegistry::iterator pos = d_properties.find(name);

	if (pos != d_properties.end())
	{
		d_properties.erase(pos);
	}
}


void PropertySet::clearProperties(void)
{
	d_properties.clear();
}


bool PropertySet::isPropertyPresent(const String& name) const
{
	return (d_properties.find(name) != d_properties.end());
}


const String& PropertySet::getPropertyHelp(const String& name) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);

	if (pos == d_properties.end())
	{
		throw UnknownObjectException((utf8*)"There is no Property named '" + name + (utf8*)"' available in the set.");
	}

	return pos->second->getHelp();
}


String PropertySet::getProperty(const String& name, const PropertyReceiver& receiver) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);

	if (pos == d_properties.end())
	{
		throw UnknownObjectException((utf8*)"There is no Property named '" + name + (utf8*)"' available in the set.");
	}

	return pos->second->get(&receiver);
}


void PropertySet::setProperty(const String& name, const String& value, PropertyReceiver& receiver) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);

	if (pos == d_properties.end())
	{
		throw UnknownObjectException((utf8*)"There is no Property named '" + name + (utf8*)"' available in the set.");
	}

	if (NULL != WindowManager::getSingleton().getPropertyCallback())
	{
		String propname = name;
		String proVal  = value;

		if(
			
			propname == (CEGUI::utf8*)"Image" ||
			propname == (CEGUI::utf8*)"NormalImage" ||
			propname == (CEGUI::utf8*)"HoverImage" ||
			propname == (CEGUI::utf8*)"PushedImage" ||
			propname == (CEGUI::utf8*)"DisabledImage" ||
			propname == (CEGUI::utf8*)"TopLeftFrameImage" ||
			propname == (CEGUI::utf8*)"TopFrameImage" ||
			propname == (CEGUI::utf8*)"TopRightFrameImage" ||
			propname == (CEGUI::utf8*)"LeftFrameImage" ||
			propname == (CEGUI::utf8*)"BackgroundImage" ||
			propname == (CEGUI::utf8*)"RightFrameImage" ||
			propname == (CEGUI::utf8*)"BottomLeftFrameImage" ||
			propname == (CEGUI::utf8*)"BottomFrameImage" ||
			propname == (CEGUI::utf8*)"BottomRightFrameImage" ||

			
			propname == (CEGUI::utf8*)"ChannelBkg"
		)
		(*WindowManager::getSingleton().getPropertyCallback())( NULL, propname, proVal, NULL );
	}

	pos->second->set(&receiver, value);
}



PropertySet::PropertyIterator PropertySet::getIterator(void) const
{
	return PropertyIterator(d_properties.begin(), d_properties.end());
}



bool PropertySet::isPropertyDefault(const String& name, const PropertyReceiver& receiver) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);

	if (pos == d_properties.end())
	{
		throw UnknownObjectException((utf8*)"There is no Property named '" + name + (utf8*)"' available in the set.");
	}

	return pos->second->isDefault(&receiver);
}



String PropertySet::getPropertyDefault(const String& name, const PropertyReceiver& receiver) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);

	if (pos == d_properties.end())
	{
		throw UnknownObjectException((utf8*)"There is no Property named '" + name + (utf8*)"' available in the set.");
	}

	return pos->second->getDefault(&receiver);
}

} 
