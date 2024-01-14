

#include "CEGUIScheme.h"
#include "CEGUIExceptions.h"
#include "CEGUISchemeManager.h"
#include "CEGUILogger.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIFontManager.h"
#include "CEGUIFont.h"
#include "CEGUIWindowFactoryManager.h"
#include "CEGUIFactoryModule.h"
#include "CEGUIScheme_xmlHandler.h"
#include "CEGUIDataContainer.h"
#include "CEGUISystem.h"
#include "CEGUIXMLParser.h"
#include "falagard/CEGUIFalWidgetLookManager.h"

extern "C" void registerFalagardFactory(const CEGUI::String& type_name);
extern "C" CEGUI::uint registerAllFalagardFactories(void);


namespace CEGUI
{



const char Scheme::GUISchemeSchemaName[]					= "GUIScheme.xsd";



Scheme::Scheme(const String& filename, const String& resourceGroup)
{
	if (filename.empty() || (filename == (utf8*)""))
	{
		throw InvalidRequestException((utf8*)"Scheme::Scheme - Filename supplied for Scheme loading must be valid");
	}

    
    Scheme_xmlHandler handler(this);

    
	try
	{
		auto parser = System::getSingleton().getXMLParser();
		parser->parseXMLFile(handler, filename, GUISchemeSchemaName, resourceGroup);
	}
	catch(...)
	{
        Logger::getSingleton().logEvent("Scheme::Scheme - loading of Scheme from file '" + filename +"' failed.", Errors);
        throw;
	}

	Logger::getSingleton().logEvent((utf8*)"Loaded GUI scheme '" + d_name + "' from data in file '" + filename + "'.", Informative);

	
	loadResources();
}



Scheme::~Scheme(void)
{
	unloadResources();

	Logger::getSingleton().logEvent((utf8*)"GUI scheme '" + d_name + "' has been unloaded.", Informative);
}



void Scheme::loadResources(void)
{
	Logger::getSingleton().logEvent((utf8*)"---- Begining resource loading for GUI scheme '" + d_name + "' ----", Informative);

	ImagesetManager& ismgr		= ImagesetManager::getSingleton();
	FontManager& fntmgr			= FontManager::getSingleton();
	WindowFactoryManager& wfmgr = WindowFactoryManager::getSingleton();
    WidgetLookManager& wlfMgr   = WidgetLookManager::getSingleton();

	std::vector<LoadableUIElement>::const_iterator	pos;

	
	for (pos = d_imagesets.begin(); pos != d_imagesets.end(); ++pos)
	{
		if (!ismgr.isImagesetPresent((*pos).name))
		{
			
			Imageset* iset = ismgr.createImageset((*pos).filename, (*pos).resourceGroup );

			
			String realname = iset->getName();

			if (realname != (*pos).name)
			{
				ismgr.destroyImageset(iset);
				throw InvalidRequestException((utf8*)"Scheme::loadResources - The Imageset created by file '" + 
					(*pos).filename + "' is named '" + realname + "', not '" + (*pos).name + "' as required by Scheme '" + d_name + "'.");
			}

		}

	}

    
    for (pos = d_imagesetsFromImages.begin(); pos != d_imagesetsFromImages.end(); ++pos)
    {
        if (!ismgr.isImagesetPresent((*pos).name))
            ismgr.createImagesetFromImageFile((*pos).name, (*pos).filename, (*pos).resourceGroup);
    }

	
	std::vector<FontElement>::iterator itFont;
	for (itFont = d_fonts.begin(); itFont != d_fonts.end(); ++itFont)
	{
		if (!fntmgr.isFontPresent((*itFont).name))
		{
			Font* font = fntmgr.createFont((*itFont).type, (*itFont).filename, (*itFont).resourceGroup);

			
			String realname = font->getName();

			if (realname != (*itFont).name)
			{
				fntmgr.destroyFont(font);
				throw InvalidRequestException((utf8*)"Scheme::loadResources - The Font created by file '" + 
					(*pos).filename + "' is named '" + realname + "', not '" + (*pos).name + "' as required by Scheme '" + d_name + "'.");
			}

		}

	}

    
    for (pos = d_looknfeels.begin(); pos != d_looknfeels.end(); ++pos)
    {
        wlfMgr.parseLookNFeelSpecification((*pos).filename, (*pos).resourceGroup);
    }

	
#ifdef CEGUIBASE_LIB
	std::vector<UIModule>::iterator	cmod = d_widgetModules.begin();
	for (;cmod != d_widgetModules.end(); ++cmod)
	{

		(*cmod).module = NULL;
		
		if ((*cmod).factories.size() == 0)
		{
			Logger::getSingleton().logEvent("No window factories specified for module '" + (*cmod).name + "' - adding all available factories...");
			registerAllFalagardFactories();
		}
		
		else
		{
			std::vector<UIElementFactory>::const_iterator	elem = (*cmod).factories.begin();
			for (; elem != (*cmod).factories.end(); ++elem)
			{
				if (!wfmgr.isFactoryPresent((*elem).name))
				{
					registerFalagardFactory((*elem).name);
				}
			}
		}
	}
#else
	std::vector<UIModule>::iterator	cmod = d_widgetModules.begin();
	for (;cmod != d_widgetModules.end(); ++cmod)
	{
		
		if ((*cmod).module == NULL)
		{
			(*cmod).module = new FactoryModule((*cmod).name);
		}

		
		if ((*cmod).factories.size() == 0)
		{
			Logger::getSingleton().logEvent("No window factories specified for module '" + (*cmod).name + "' - adding all available factories...");
			(*cmod).module->registerAllFactories();
		}
		
		else
		{
			std::vector<UIElementFactory>::const_iterator	elem = (*cmod).factories.begin();
			for (; elem != (*cmod).factories.end(); ++elem)
			{
				if (!wfmgr.isFactoryPresent((*elem).name))
				{
					(*cmod).module->registerFactory((*elem).name);
				}
			}
		}
	}
#endif
	

	
	std::vector<AliasMapping>::iterator alias = d_aliasMappings.begin();
	for (;alias != d_aliasMappings.end(); ++alias)
	{
		
		WindowFactoryManager::TypeAliasIterator iter = wfmgr.getAliasIterator();

		
		while (!iter.isAtEnd() && (iter.getCurrentKey() != (*alias).aliasName))
			++iter;

		
		if (!iter.isAtEnd())
		{
			
			if (iter.getCurrentValue().getActiveTarget() == (*alias).targetName)
			{
				
				continue;
			}

		}

		
		wfmgr.addWindowTypeAlias((*alias).aliasName, (*alias).targetName);
	}

    
    std::vector<FalagardMapping>::iterator falagard = d_falagardMappings.begin();
    for (;falagard != d_falagardMappings.end(); ++falagard)
    {
        
        WindowFactoryManager::FalagardMappingIterator iter = wfmgr.getFalagardMappingIterator();

        
        while (!iter.isAtEnd() && (iter.getCurrentKey() != (*falagard).windowName))
            ++iter;

        
        if (!iter.isAtEnd())
        {
            
            if ((iter.getCurrentValue().d_baseType == (*falagard).targetName) &&
                (iter.getCurrentValue().d_lookName == (*falagard).lookName))
            {
                
                continue;
            }
        }

        
        wfmgr.addFalagardWindowMapping((*falagard).windowName, (*falagard).targetName, (*falagard).lookName);
    }

	
	fntmgr.setFontBlinkTime(d_fontBlinkTime);

	Logger::getSingleton().logEvent((utf8*)"---- Resource loading for GUI scheme '" + d_name + "' completed ----", Informative);
}



void Scheme::unloadResources(void)
{
	Logger::getSingleton().logEvent((utf8*)"---- Begining resource cleanup for GUI scheme '" + d_name + "' ----", Informative);

	ImagesetManager& ismgr		= ImagesetManager::getSingleton();
	FontManager& fntmgr			= FontManager::getSingleton();
	WindowFactoryManager& wfmgr = WindowFactoryManager::getSingleton();

	std::vector<LoadableUIElement>::const_iterator	pos;

	
	std::vector<FontElement>::iterator itFont;
	for (itFont = d_fonts.begin(); itFont != d_fonts.end(); ++itFont)
	{
		fntmgr.destroyFont((*itFont).name);
	}

	
	for (pos = d_imagesets.begin(); pos != d_imagesets.end(); ++pos)
	{
		ismgr.destroyImageset((*pos).name);
	}

    
    for (pos = d_imagesetsFromImages.begin(); pos != d_imagesetsFromImages.end(); ++pos)
    {
        ismgr.destroyImageset((*pos).name);
    }

	
	std::vector<UIModule>::iterator	cmod = d_widgetModules.begin();
	for (;cmod != d_widgetModules.end(); ++cmod)
	{
		std::vector<UIElementFactory>::const_iterator	elem = (*cmod).factories.begin();
		for (; elem != (*cmod).factories.end(); ++elem)
		{
			wfmgr.removeFactory((*elem).name);
		}

		
		if ((*cmod).module != NULL)
		{
			delete (*cmod).module;
			(*cmod).module = NULL;
		}

	}

	
	std::vector<AliasMapping>::iterator alias = d_aliasMappings.begin();
	for (;alias != d_aliasMappings.end(); ++alias)
	{
		
		WindowFactoryManager::TypeAliasIterator iter = wfmgr.getAliasIterator();

		
		while (!iter.isAtEnd() && (iter.getCurrentKey() != (*alias).aliasName))
			++iter;

		
		if (!iter.isAtEnd())
		{
			
			wfmgr.removeWindowTypeAlias((*alias).aliasName, (*alias).targetName);
		}

	}

    
    std::vector<FalagardMapping>::iterator falagard = d_falagardMappings.begin();
    for (;falagard != d_falagardMappings.end(); ++falagard)
    {
        
        WindowFactoryManager::FalagardMappingIterator iter = wfmgr.getFalagardMappingIterator();

        
        while (!iter.isAtEnd() && (iter.getCurrentKey() != (*falagard).windowName))
            ++iter;

        
        if (!iter.isAtEnd())
        {
            
            if ((iter.getCurrentValue().d_baseType == (*falagard).targetName) &&
                (iter.getCurrentValue().d_lookName == (*falagard).lookName))
            {
                
                wfmgr.removeFalagardWindowMapping((*falagard).targetName);
            }
        }
    }

	Logger::getSingleton().logEvent((utf8*)"---- Resource cleanup for GUI scheme '" + d_name + "' completed ----", Informative);
}



bool Scheme::resourcesLoaded(void) const
{
	ImagesetManager& ismgr		= ImagesetManager::getSingleton();
	FontManager& fntmgr			= FontManager::getSingleton();
	WindowFactoryManager& wfmgr = WindowFactoryManager::getSingleton();

	std::vector<LoadableUIElement>::const_iterator	pos;

	
	for (pos = d_imagesets.begin(); pos != d_imagesets.end(); ++pos)
	{
		if (!ismgr.isImagesetPresent((*pos).name))
		{
			return false;
		}

	}

	
	std::vector<FontElement>::const_iterator itFont;
	for (itFont = d_fonts.begin(); itFont != d_fonts.end(); ++itFont)
	{
		if (!fntmgr.isFontPresent((*itFont).name))
		{
			return false;
		}

	}

	
	std::vector<UIModule>::const_iterator	cmod = d_widgetModules.begin();
	for (;cmod != d_widgetModules.end(); ++cmod)
	{
		std::vector<UIElementFactory>::const_iterator	elem = (*cmod).factories.begin();

		for (; elem != (*cmod).factories.end(); ++elem)
		{
			if (!wfmgr.isFactoryPresent((*elem).name))
			{
				return false;
			}

		}

	}

	
	std::vector<AliasMapping>::const_iterator alias = d_aliasMappings.begin();
	for (;alias != d_aliasMappings.end(); ++alias)
	{
		
		WindowFactoryManager::TypeAliasIterator iter = wfmgr.getAliasIterator();

		
		while (!iter.isAtEnd() && (iter.getCurrentKey() != (*alias).aliasName))
			++iter;

		
		if (!iter.isAtEnd())
		{
			
			if (iter.getCurrentValue().getActiveTarget() == (*alias).targetName)
			{
				
				continue;
			}

		}

		
		return false;
	}

	return true;
}


} 
