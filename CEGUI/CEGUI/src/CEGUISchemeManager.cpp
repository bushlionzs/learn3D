

#include "CEGUISchemeManager.h"
#include "CEGUIExceptions.h"
#include "CEGUILogger.h"
#include "CEGUIScheme.h"


namespace CEGUI
{


template<> SchemeManager* Singleton<SchemeManager>::ms_Singleton	= NULL;




SchemeManager::SchemeManager(void)
{
	
}



SchemeManager::~SchemeManager(void)
{
	Logger::getSingleton().logEvent((utf8*)"---- Begining cleanup of GUI Scheme system ----");

	unloadAllSchemes();

	
}



Scheme* SchemeManager::loadScheme(const String& scheme_filename, const String& resourceGroup)
{
	

	Scheme* tmp = new Scheme(scheme_filename, resourceGroup);
	String name = tmp->getName();
	d_schemes[name] = tmp;
	return tmp;
}



void SchemeManager::unloadScheme(const String& scheme_name)
{
	SchemeRegistry::iterator pos = d_schemes.find(scheme_name);

	if (pos != d_schemes.end())
	{
		String tmpName(scheme_name);

		delete pos->second;
		d_schemes.erase(pos);

		Logger::getSingleton().logEvent((utf8*)"Scheme '" + tmpName + "' has been unloaded.");
	}
	else
	{
		Logger::getSingleton().logEvent((utf8*)"Unable to unload non-existant scheme '" + scheme_name + "'.", Errors);
	}

}



Scheme* SchemeManager::getScheme(const String& name) const
{
	SchemeRegistry::const_iterator pos = d_schemes.find(name);

	if (pos == d_schemes.end())
	{
		throw UnknownObjectException("SchemeManager::getScheme - A Scheme object with the specified name '" + name +"' does not exist within the system");
	}

	return pos->second;
}


SchemeManager& SchemeManager::getSingleton(void)
{
	return Singleton<SchemeManager>::getSingleton();
}


SchemeManager* SchemeManager::getSingletonPtr(void)
{
	return Singleton<SchemeManager>::getSingletonPtr();
}



SchemeManager::SchemeIterator SchemeManager::getIterator(void) const
{
	return SchemeIterator(d_schemes.begin(), d_schemes.end());
}



void SchemeManager::unloadAllSchemes(void)
{
	
	while (!d_schemes.empty())
	{
		unloadScheme(d_schemes.begin()->first);
	}

}


} 
