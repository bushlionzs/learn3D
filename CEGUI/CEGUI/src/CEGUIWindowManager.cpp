

#include "CEGUIWindowManager.h"
#include "CEGUIWindowFactoryManager.h"
#include "CEGUIWindowFactory.h"
#include "CEGUIWindow.h"
#include "CEGUIExceptions.h"
#include "CEGUIGUILayout_xmlHandler.h"
#include "CEGUIXMLParser.h"
#include <iostream>
#include <sstream>


namespace CEGUI
{


template<> WindowManager* Singleton<WindowManager>::ms_Singleton	= NULL;




const char	WindowManager::GUILayoutSchemaName[]	= "GUILayout.xsd";
const String WindowManager::GeneratedWindowNameBase("__cewin_uid_");



WindowManager::WindowManager(void) :
    d_uid_counter(0),
	d_propertyCallback(0)
{
    
}



WindowManager::~WindowManager(void)
{
	destroyAllWindows();
    cleanDeadPool();

	
}



Window* WindowManager::createWindow(const String& type, const String& name)
{
    String finalName(name.empty() ? generateUniqueWindowName() : name);

	if (isWindowPresent(finalName))
	{
		throw AlreadyExistsException("WindowManager::createWindow - A Window object with the name '" + finalName +"' already exists within the system.");
	}

    WindowFactoryManager& wfMgr = WindowFactoryManager::getSingleton();
    WindowFactory* factory = wfMgr.getFactory(type);

    Window* newWindow = factory->createWindow(finalName);
    Logger::getSingleton().logEvent("Window '" + finalName +"' of type '" + type + "' has been created.", Informative);

    
    if (wfMgr.isFalagardMappedType(type))
    {
        
        
        newWindow->setLookNFeel(type, wfMgr.getMappedLookForType(type));
    }

    
    newWindow->initialise();

	d_windowRegistry[finalName] = newWindow;

	return newWindow;
}



void WindowManager::destroyWindow(Window* window)
{
	if (window != NULL)
	{
		
		
		
		
		String name = window->getName();

		destroyWindow(name);
	}

}



void WindowManager::destroyWindow(const String& window)
{
	WindowRegistry::iterator wndpos = d_windowRegistry.find(window);

	if (wndpos != d_windowRegistry.end())
	{
        Window* wnd = wndpos->second;

        
        d_windowRegistry.erase(wndpos);

        
        wnd->destroy();

        
        d_deathrow.push_back(wnd);

        
        System::getSingleton().notifyWindowDestroyed(wnd);

		Logger::getSingleton().logEvent((utf8*)"Window '" + window + "' has been added to dead pool.", Informative);
	}

}



Window* WindowManager::getWindow(const String& name) const
{
	WindowRegistry::const_iterator pos = d_windowRegistry.find(name);

	if (pos == d_windowRegistry.end())
	{
		throw UnknownObjectException("WindowManager::getWindow - A Window object with the name '" + name +"' does not exist within the system");
	}

	return pos->second;
}



bool WindowManager::isWindowPresent(const String& name) const
{
	return (d_windowRegistry.find(name) != d_windowRegistry.end());
}



void WindowManager::destroyAllWindows(void)
{
	String window_name;
	while (!d_windowRegistry.empty())
	{
		window_name = d_windowRegistry.begin()->first;
		destroyWindow(window_name);
	}

}



Window* WindowManager::loadWindowLayout(const String& filename, const String& name_prefix, const String& resourceGroup, PropertyCallback* callback, void* userdata)
{
	if (filename.empty() || (filename == (utf8*)""))
	{
		throw InvalidRequestException((utf8*)"WindowManager::loadWindowLayout - Filename supplied for gui-layout loading must be valid.");
	}

	
	Logger::getSingleton().logEvent((utf8*)"---- Beginning loading of GUI layout from '" + filename + "' ----", Informative);

    
    GUILayout_xmlHandler handler(name_prefix, callback, userdata);

	if( callback )
		d_propertyCallback = callback;

	
	try
	{
        System::getSingleton().getXMLParser()->parseXMLFile(handler, filename, GUILayoutSchemaName, resourceGroup);
	}
	catch(...)
	{
        Logger::getSingleton().logEvent("WindowManager::loadWindowLayout - loading of layout from file '" + filename +"' failed.", Errors);
        throw;
	}

    
    

	
	if(handler.getLayoutRootWindow())
	{
		handler.getLayoutRootWindow()->postSizeChanged();
	}

	return handler.getLayoutRootWindow();
}


WindowManager& WindowManager::getSingleton(void)
{
	return Singleton<WindowManager>::getSingleton();
}


WindowManager* WindowManager::getSingletonPtr(void)
{
	return Singleton<WindowManager>::getSingletonPtr();
}

bool WindowManager::isDeadPoolEmpty(void) const
{
    return d_deathrow.empty();
}

void WindowManager::cleanDeadPool(void)
{
    WindowVector::reverse_iterator curr = d_deathrow.rbegin();
    for (; curr != d_deathrow.rend(); ++curr)
    {

#if defined(DEBUG) || defined (_DEBUG)
        CEGUI_LOGINSANE("Window '" + (*curr)->getName() + "' about to be finally destroyed from dead pool.");
#endif

        WindowFactory* factory = WindowFactoryManager::getSingleton().getFactory((*curr)->getType());
        factory->destroyWindow(*curr);
    }
    
    
    d_deathrow.clear();
}

void WindowManager::writeWindowLayoutToStream(const Window& window, OutStream& out_stream, bool writeParent) const
{
    
    out_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    
    out_stream << "<GUILayout";
    
    if ((window.getParent() != 0) && writeParent)
    {
        out_stream << " Parent=\"" << window.getParent()->getName() << "\" ";
    }
    
    out_stream << ">" << std::endl;
    
    window.writeXMLToStream(out_stream);
    
    out_stream << "</GUILayout>" << std::endl;
}

void WindowManager::writeWindowLayoutToStream(const String& window, OutStream& out_stream, bool writeParent) const
{
    writeWindowLayoutToStream(*getWindow(window), out_stream, writeParent);
}

String WindowManager::generateUniqueWindowName()
{
    
    std::ostringstream uidname;
    uidname << GeneratedWindowNameBase.c_str() << d_uid_counter;

    
    unsigned long old_uid = d_uid_counter;
    ++d_uid_counter;

    
    if (d_uid_counter < old_uid)
        Logger::getSingleton().logEvent("UID counter for generated window names has wrapped around - the fun shall now commence!");

    
    return String(uidname.str());
}

void WindowManager::renameWindow(const String& window, const String& new_name)
{
    renameWindow(getWindow(window), new_name);
}

void WindowManager::renameWindow(Window* window, const String& new_name)
{
    if (window)
    {
        WindowRegistry::iterator pos = d_windowRegistry.find(window->getName());

        if (pos != d_windowRegistry.end())
        {
            
            d_windowRegistry.erase(pos);
            
            window->rename(new_name);
            
            d_windowRegistry[new_name] = window;
        }
    }
}


WindowManager::WindowIterator WindowManager::getIterator(void) const
{
	return WindowIterator(d_windowRegistry.begin(), d_windowRegistry.end());
}
} 
