

#include "CEGUIWindowFactoryManager.h"
#include "CEGUIWindowFactory.h"
#include "CEGUIExceptions.h"
#include <algorithm>


namespace CEGUI
{


template<> WindowFactoryManager* Singleton<WindowFactoryManager>::ms_Singleton	= NULL;



void WindowFactoryManager::addFactory(WindowFactory* factory)
{
	
	if (factory == NULL)
	{
		throw NullObjectException((utf8*)"WindowFactoryManager::addFactory - The provided WindowFactory pointer was NULL");
	}

	
	if (d_factoryRegistry.find(factory->getTypeName()) != d_factoryRegistry.end())
	{
		throw AlreadyExistsException((utf8*)"WindowFactoryManager::addFactory - A WindowFactory for type '" + factory->getTypeName() + (utf8*)"' is already registered.");
	}

	
	d_factoryRegistry[factory->getTypeName()] = factory;

	
}



void WindowFactoryManager::removeFactory(const String& name)
{
	d_factoryRegistry.erase(name);

	
}



void WindowFactoryManager::removeFactory(WindowFactory* factory)
{
	if (factory != NULL)
	{
		removeFactory(factory->getTypeName());
	}

}



WindowFactory* WindowFactoryManager::getFactory(const String& type) const
{
    
    String targetType(getDereferencedAliasType(type));

	
	WindowFactoryRegistry::const_iterator pos = d_factoryRegistry.find(targetType);

	
	if (pos != d_factoryRegistry.end())
	{
		return pos->second;
	}
    
    else
    {
        FalagardMapRegistry::const_iterator falagard = d_falagardRegistry.find(targetType);

        
        if (falagard != d_falagardRegistry.end())
        {
            
            return getFactory(falagard->second.d_baseType);
        }
        
        else
        {
            throw UnknownObjectException("WindowFactoryManager::getFactory - A WindowFactory object, an alias, or mapping for '" + type + "' Window objects is not registered with the system.");
        }
    }
}



bool WindowFactoryManager::isFactoryPresent(const String& name) const
{
    
    String targetType(getDereferencedAliasType(name));

    
    if (d_factoryRegistry.find(targetType) != d_factoryRegistry.end())
    {
        return true;
    }
    
    else
    {
        return (d_falagardRegistry.find(targetType) != d_falagardRegistry.end());
    }
}


WindowFactoryManager& WindowFactoryManager::getSingleton(void)
{
	return Singleton<WindowFactoryManager>::getSingleton();
}


WindowFactoryManager* WindowFactoryManager::getSingletonPtr(void)
{
	return Singleton<WindowFactoryManager>::getSingletonPtr();
}



WindowFactoryManager::WindowFactoryIterator	WindowFactoryManager::getIterator(void) const
{
	return WindowFactoryIterator(d_factoryRegistry.begin(), d_factoryRegistry.end());
}



WindowFactoryManager::TypeAliasIterator WindowFactoryManager::getAliasIterator(void) const
{
	return TypeAliasIterator(d_aliasRegistry.begin(), d_aliasRegistry.end());
}



void WindowFactoryManager::addWindowTypeAlias(const String& aliasName, const String& targetType)
{
	
	if (!isFactoryPresent(targetType))
	{
		throw UnknownObjectException((utf8*)"WindowFactoryManager::addWindowTypeAlias - alias '" + aliasName + "' could not be created because the target type '" + targetType + "' is unknown within the system.");
	}

	TypeAliasRegistry::iterator pos = d_aliasRegistry.find(aliasName);

	if (pos == d_aliasRegistry.end())
	{
		d_aliasRegistry[aliasName].d_targetStack.push_back(targetType);
	}
	
	else
	{
		pos->second.d_targetStack.push_back(targetType);
	}

	
}



void WindowFactoryManager::removeWindowTypeAlias(const String& aliasName, const String& targetType)
{
	
	TypeAliasRegistry::iterator pos = d_aliasRegistry.find(aliasName);

	
	if (pos != d_aliasRegistry.end())
	{
		
		std::vector<String>::iterator aliasPos = std::find(pos->second.d_targetStack.begin(), pos->second.d_targetStack.end(), targetType);
		
		
		if (aliasPos != pos->second.d_targetStack.end())
		{
			
			pos->second.d_targetStack.erase(aliasPos);

			

			
			if (pos->second.d_targetStack.empty())
			{
				
				d_aliasRegistry.erase(aliasName);

				
			}

		}

	}

}

void WindowFactoryManager::addFalagardWindowMapping(const String& newType, const String& targetType, const String& lookName)
{
    WindowFactoryManager::FalagardWindowMapping mapping;
    mapping.d_windowType = newType;
    mapping.d_baseType   = targetType;
    mapping.d_lookName   = lookName;

    
    if (d_falagardRegistry.find(newType) != d_falagardRegistry.end())
    {
        
        Logger::getSingleton().logEvent("Falagard mapping for type '" + newType + "' already exists - current mapping will be replaced.");
    }

    

    d_falagardRegistry[newType] = mapping;
}

void WindowFactoryManager::removeFalagardWindowMapping(const String& type)
{
    FalagardMapRegistry::iterator iter = d_falagardRegistry.find(type);

    if (iter != d_falagardRegistry.end())
    {
        Logger::getSingleton().logEvent("Removing falagard mapping for type '" + type + "'.");
        d_falagardRegistry.erase(iter);
    }
}

WindowFactoryManager::FalagardMappingIterator WindowFactoryManager::getFalagardMappingIterator() const
{
    return FalagardMappingIterator(d_falagardRegistry.begin(), d_falagardRegistry.end());
}

bool WindowFactoryManager::isFalagardMappedType(const String& type) const
{
    return d_falagardRegistry.find(getDereferencedAliasType(type)) != d_falagardRegistry.end();
}

const String& WindowFactoryManager::getMappedLookForType(const String& type) const
{
    FalagardMapRegistry::const_iterator iter =
        d_falagardRegistry.find(getDereferencedAliasType(type));

    if (iter != d_falagardRegistry.end())
    {
        return (*iter).second.d_lookName;
    }
    
    else
    {
        throw InvalidRequestException("WindowFactoryManager::getMappedLookForType - Window factory type '" + type + "' is not a falagard mapped type (or an alias for one).");
    }
}

String WindowFactoryManager::getDereferencedAliasType(const String& type) const
{
    TypeAliasRegistry::const_iterator alias = d_aliasRegistry.find(type);

    
    
    if (alias != d_aliasRegistry.end())
        return getDereferencedAliasType(alias->second.getActiveTarget());

    
    return type;
}





const String& WindowFactoryManager::AliasTargetStack::getActiveTarget(void) const
{
	return d_targetStack.back();
}


uint WindowFactoryManager::AliasTargetStack::getStackedTargetCount(void) const
{
	return (uint)d_targetStack.size();
}


} 
