

#include "CEGUIGUILayout_xmlHandler.h"
#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUIScriptModule.h"
#include "CEGUIXMLAttributes.h"



namespace CEGUI
{

const String GUILayout_xmlHandler::GUILayoutElement( (utf8*)"GUILayout" );
const String GUILayout_xmlHandler::WindowElement( (utf8*)"Window" );
const String GUILayout_xmlHandler::PropertyElement( (utf8*)"Property" );
const String GUILayout_xmlHandler::LayoutImportElement( (utf8*)"LayoutImport" );
const String GUILayout_xmlHandler::EventElement( (utf8*)"Event" );
const char	GUILayout_xmlHandler::WindowTypeAttribute[]		= "Type";
const char	GUILayout_xmlHandler::WindowNameAttribute[]		= "Name";
const char	GUILayout_xmlHandler::PropertyNameAttribute[]	= "Name";
const char	GUILayout_xmlHandler::PropertyValueAttribute[]	= "Value";
const char	GUILayout_xmlHandler::LayoutParentAttribute[]	= "Parent";
const char	GUILayout_xmlHandler::LayoutImportFilenameAttribute[]	= "Filename";
const char	GUILayout_xmlHandler::LayoutImportPrefixAttribute[]		= "Prefix";
const char	GUILayout_xmlHandler::LayoutImportResourceGroupAttribute[] = "ResourceGroup";
const char	GUILayout_xmlHandler::EventNameAttribute[]		= "Name";
const char	GUILayout_xmlHandler::EventFunctionAttribute[]	= "Function";

void GUILayout_xmlHandler::elementStart(const String& element, const XMLAttributes& attributes)
{
	
	if (element == GUILayoutElement)
	{
		d_layoutParent = attributes.getValueAsString(LayoutParentAttribute);

		
		if (!d_layoutParent.empty())
		{
			if (!WindowManager::getSingleton().isWindowPresent(d_layoutParent))
			{
				
				throw InvalidRequestException((utf8*)"GUILayout_xmlHandler::startElement - layout loading has been aborted since the specified parent Window ('" + d_layoutParent + "') does not exist.");
			}

		}

	}
	
	else if (element == WindowElement)
	{
		
        String windowType(attributes.getValueAsString(WindowTypeAttribute));

		
        String windowName(attributes.getValueAsString(WindowNameAttribute));

		
		try
		{
			Window* wnd = WindowManager::getSingleton().createWindow(windowType, d_namingPrefix + windowName);

			
			if (!d_stack.empty())
			{
				d_stack.back()->addChildWindow(wnd);
			}
			else
			{
				d_root = wnd;
			}

			
			d_stack.push_back(wnd);
		}
		catch (AlreadyExistsException exc)
		{
			
			cleanupLoadedWindows();

			
			throw InvalidRequestException((utf8*)"GUILayout_xmlHandler::startElement - layout loading has been aborted since Window named '" + windowName + "' already exists.");
		}
		catch (UnknownObjectException exc)
		{
			
			cleanupLoadedWindows();

			
			throw InvalidRequestException((utf8*)"GUILayout_xmlHandler::startElement - layout loading has been aborted since no WindowFactory is available for '" + windowType + "' objects.");
		}

	}
	
	else if (element == PropertyElement)
	{
		
        String propertyName(attributes.getValueAsString(PropertyNameAttribute));

		
        String propertyValue(attributes.getValueAsString(PropertyValueAttribute));

		
		try
		{
			if (!d_stack.empty())
			{
				Window* curwindow = d_stack.back();
				bool useit = true;
				if (NULL != d_propertyCallback)
				{
					useit = (*d_propertyCallback)(curwindow, propertyName, propertyValue, d_userData);
				}
				if (useit)
				{
					curwindow->setProperty(propertyName, propertyValue);
				}
			}
		}
		catch (Exception exc)
		{
			
		}

	}
	
	else if (element == LayoutImportElement)
	{
        
        String prefixName(d_namingPrefix);
        prefixName += attributes.getValueAsString(LayoutImportPrefixAttribute);

        try
        {
            
            Window* subLayout = WindowManager::getSingleton().loadWindowLayout(
                    attributes.getValueAsString( LayoutImportFilenameAttribute),
                    prefixName,
                    attributes.getValueAsString(LayoutImportResourceGroupAttribute),
                    d_propertyCallback,
                    d_userData);

            
            if ((subLayout != NULL) && (!d_stack.empty()))
                d_stack.back()->addChildWindow(subLayout);
        }
        
        catch (Exception& )
        {
            
            cleanupLoadedWindows();

            
            throw GenericException("GUILayout_xmlHandler::startElement - layout loading aborted due to imported layout load failure (see error(s) above).");
        }
	}
	
	else if (element == EventElement)
	{
        String eventName(attributes.getValueAsString(EventNameAttribute));
        String functionName(attributes.getValueAsString(EventFunctionAttribute));

		
		try
		{
			if (!d_stack.empty())
			{
                d_stack.back()->subscribeEvent(eventName, ScriptFunctor(functionName));
			}
		}
		catch (Exception exc)
		{
			
		}

	}
	
	else
	{
		throw FileIOException("GUILayout_xmlHandler::startElement - Unexpected data was found while parsing the gui-layout file: '" + element + "' is unknown.");
	}

}

void GUILayout_xmlHandler::elementEnd(const String& element)
{
	
	if (element == GUILayoutElement)
	{
		
		if (!d_layoutParent.empty() && (d_root != NULL))
		{
			WindowManager::getSingleton().getWindow(d_layoutParent)->addChildWindow(d_root);
		}

	}
	
	else if (element == WindowElement)
	{
		
		if (!d_stack.empty())
		{
			d_stack.pop_back();
		}

	}

}



void GUILayout_xmlHandler::cleanupLoadedWindows(void)
{
	
	
	
	while (!d_stack.empty())
	{
		Window* wnd = d_stack.back();

		
		if (wnd->getParent() != NULL)
		{
			wnd->getParent()->removeChildWindow(wnd);
		}

		
		WindowManager::getSingleton().destroyWindow(wnd);

		
		d_stack.pop_back();
	}

	d_root = NULL;
}



Window* GUILayout_xmlHandler::getLayoutRootWindow(void) const
{
	return d_root;
}

} 
