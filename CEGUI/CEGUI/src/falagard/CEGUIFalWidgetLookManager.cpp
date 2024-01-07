

#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalagard_xmlHandler.h"
#include "CEGUIResourceProvider.h"
#include "CEGUIXMLParser.h"
#include "CEGUIExceptions.h"
#include "CEGUILogger.h"


namespace CEGUI
{
    
    
    template<> WidgetLookManager* Singleton<WidgetLookManager>::ms_Singleton = 0;
    const String WidgetLookManager::FalagardSchemaName("Falagard.xsd");
    

    WidgetLookManager::WidgetLookManager()
    {
        
    }

    WidgetLookManager::~ WidgetLookManager()
    {
        
		
		for (WidgetLookList::iterator curr = d_widgetLooks.begin(); curr != d_widgetLooks.end(); ++curr)
        {
            if ((*curr).second)
			{
				WidgetLookFeel* p = (WidgetLookFeel*)((*curr).second);
				delete p;
				(*curr).second = 0;
			}
        }
    }

    
	  WidgetLookManager&	WidgetLookManager::getSingleton(void)
	  {
		  return Singleton<WidgetLookManager>::getSingleton();
	  }

	  
	  WidgetLookManager*	WidgetLookManager::getSingletonPtr(void)
	  {
		  return Singleton<WidgetLookManager>::getSingletonPtr();
  	}

    void WidgetLookManager::parseLookNFeelSpecification(const String& filename, const String& resourceGroup)
    {
        
        if (filename.empty())
        {
            throw InvalidRequestException("WidgetLookManager::parseLookNFeelSpecification - Filename supplied for look & feel file must be valid");
        }

        
        Falagard_xmlHandler handler(this);

        
        try
        {
            System::getSingleton().getXMLParser()->parseXMLFile(handler, filename, FalagardSchemaName, resourceGroup);
        }
        catch(...)
        {
            Logger::getSingleton().logEvent("WidgetLookManager::parseLookNFeelSpecification - loading of look and feel data from file '" + filename +"' has failed.", Errors);
            throw;
        }
    }

    bool WidgetLookManager::isWidgetLookAvailable(const String& widget) const
    {
        return d_widgetLooks.find(widget) != d_widgetLooks.end();
    }

    const WidgetLookFeel& WidgetLookManager::getWidgetLook(const String& widget) const
    {
        WidgetLookList::const_iterator wlf = d_widgetLooks.find(widget);

        if (wlf != d_widgetLooks.end())
        {
            return *((*wlf).second);
        }

        throw UnknownObjectException("WidgetLookManager::getWidgetLook - Widget look and feel '" + widget + "' does not exist.");
    }

    void WidgetLookManager::eraseWidgetLook(const String& widget)
    {
        WidgetLookList::iterator wlf = d_widgetLooks.find(widget);
        if (wlf != d_widgetLooks.end())
        {
            d_widgetLooks.erase(wlf);
        }
        else
        {
            Logger::getSingleton().logEvent(
                "WidgetLookManager::eraseWidgetLook - Widget look and feel '" + widget + "' did not exist.");
        }
    }

    void WidgetLookManager::addWidgetLook(WidgetLookFeel& look)
    {
        if (isWidgetLookAvailable(look.getName()))
        {
            Logger::getSingleton().logEvent(
                "WidgetLookManager::addWidgetLook - Widget look and feel '" + look.getName() + "' already exists.  Replacing previous definition.");
        }

        d_widgetLooks[look.getName()] = &look;
    }

    void WidgetLookManager::writeFalagardXMLHeadToStream(OutStream& out_stream) const
    {
        
        out_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
        
        out_stream << "<Falagard>" << std::endl;
    }

    void WidgetLookManager::writeFalagardXMLTailToStream(OutStream& out_stream) const
    {
        
        out_stream << "</Falagard>" << std::endl;
    }

    void WidgetLookManager::writeWidgetLookToStream(const String& name, OutStream& out_stream) const
    {
        
        writeFalagardXMLHeadToStream(out_stream);

        try
        {
            
            getWidgetLook(name).writeXMLToStream(out_stream);
        }
        catch (UnknownObjectException)
        {
            Logger::getSingleton().logEvent("WidgetLookManager::writeWidgetLookToStream - Failed to write widget look XML data to stream.", Errors);
        }

        
        writeFalagardXMLTailToStream(out_stream);
    }

    void WidgetLookManager::writeWidgetLookSeriesToStream(const String& prefix, OutStream& out_stream) const
    {
        
        writeFalagardXMLHeadToStream(out_stream);

        for (WidgetLookList::const_iterator curr = d_widgetLooks.begin(); curr != d_widgetLooks.end(); ++curr)
        {
            if ((*curr).first.compare(0, prefix.length(), prefix) == 0)
                (*curr).second->writeXMLToStream(out_stream);
        }

        
        writeFalagardXMLTailToStream(out_stream);
    }

} 
