

#include "CEGUIScheme_xmlHandler.h"

#include "CEGUIExceptions.h"
#include "CEGUIImageset.h"
#include "CEGUILogger.h"
#include "CEGUIXMLAttributes.h"
#include "falagard/CEGUIFalWidgetLookManager.h"


namespace CEGUI
{




const String Scheme_xmlHandler::GUISchemeElement( "GUIScheme" );
const String Scheme_xmlHandler::ImagesetElement( "Imageset" );
const String Scheme_xmlHandler::ImagesetBinElement( "Imageset_bin" );
const String Scheme_xmlHandler::ImagesetFromImageElement( "ImagesetFromImage" );
const String Scheme_xmlHandler::FontElement( "Font" );
const String Scheme_xmlHandler::WindowSetElement( "WindowSet" );
const String Scheme_xmlHandler::WindowFactoryElement( "WindowFactory" );
const String Scheme_xmlHandler::WindowAliasElement( "WindowAlias" );
const String Scheme_xmlHandler::FalagardMappingElement( "FalagardMapping" );
const String Scheme_xmlHandler::LookNFeelElement( "LookNFeel" );
const String Scheme_xmlHandler::TypeAttribute( "Type" );
const String Scheme_xmlHandler::NameAttribute( "Name" );
const String Scheme_xmlHandler::FilenameAttribute( "Filename" );
const String Scheme_xmlHandler::AliasAttribute( "Alias" );
const String Scheme_xmlHandler::TargetAttribute( "Target" );
const String Scheme_xmlHandler::ResourceGroupAttribute( "ResourceGroup" );
const String Scheme_xmlHandler::WindowTypeAttribute( "WindowType" );
const String Scheme_xmlHandler::TargetTypeAttribute( "TargetType" );
const String Scheme_xmlHandler::LookNFeelAttribute( "LookNFeel" );

const char	Scheme_xmlHandler::FontType_FreeType[]	= "FreeType";
const char	Scheme_xmlHandler::FontType_Bitmap[]		= "Bitmap";

const String Scheme_xmlHandler::FontBlinkTimeElement( "FontBlinkTime" );
const String Scheme_xmlHandler::SecondsAttribute( "Seconds" );


void Scheme_xmlHandler::elementStart(const String& element, const XMLAttributes& attributes)
{
	
	if (element == WindowAliasElement)
	{
		Scheme::AliasMapping	alias;

		alias.aliasName	 = attributes.getValueAsString(AliasAttribute);
        alias.targetName = attributes.getValueAsString(TargetAttribute);
		d_scheme->d_aliasMappings.push_back(alias);
	}
	
	else if (element == ImagesetElement)
	{
		Scheme::LoadableUIElement	imageset;

        imageset.name = attributes.getValueAsString(NameAttribute);
        imageset.filename = attributes.getValueAsString(FilenameAttribute);
        imageset.resourceGroup = attributes.getValueAsString(ResourceGroupAttribute);

		d_scheme->d_imagesets.push_back(imageset);
	}
	
	else if (element == ImagesetBinElement)
	{
		Scheme::UIElementFactory	imageset_bin;

        imageset_bin.name = attributes.getValueAsString(FilenameAttribute);

		d_scheme->d_imagesets_bin = imageset_bin;
	}
    
    else if (element == ImagesetFromImageElement)
    {
        Scheme::LoadableUIElement	imageset;

        imageset.name = attributes.getValueAsString(NameAttribute);
        imageset.filename = attributes.getValueAsString(FilenameAttribute);
        imageset.resourceGroup = attributes.getValueAsString(ResourceGroupAttribute);

        d_scheme->d_imagesetsFromImages.push_back(imageset);
    }
	
	else if (element == FontElement)
	{
		Scheme::FontElement	font;

        font.name = attributes.getValueAsString(NameAttribute);
        font.filename = attributes.getValueAsString(FilenameAttribute);
        font.resourceGroup = attributes.getValueAsString(ResourceGroupAttribute);

		String strTemp = attributes.getValueAsString(TypeAttribute);
		if(strTemp == FontType_FreeType)
		{
			font.type = FreeType;
		}
		else if(strTemp == FontType_Bitmap)
		{
			font.type = Bitmap;
		}
		else
		{
			throw FileIOException("Scheme::xmlHandler::startElement - font '" + font.name + "' must define type.");
		}

		d_scheme->d_fonts.push_back(font);
	}
	
	else if (element == WindowSetElement)
	{
		Scheme::UIModule	module;
        module.name		= attributes.getValueAsString(FilenameAttribute);
		module.module	= NULL;

		module.factories.clear();
		d_scheme->d_widgetModules.push_back(module);
	}
	
	else if (element == WindowFactoryElement)
	{
		Scheme::UIElementFactory factory;

        factory.name = attributes.getValueAsString(NameAttribute);

		d_scheme->d_widgetModules[d_scheme->d_widgetModules.size() - 1].factories.push_back(factory);
	}
	
	else if (element == GUISchemeElement)
	{
		
        d_scheme->d_name = attributes.getValueAsString(NameAttribute);

		Logger::getSingleton().logEvent("Started creation of Scheme '" + d_scheme->d_name + "' via XML file.", Informative);

		if (SchemeManager::getSingleton().isSchemePresent(d_scheme->d_name))
		{
			throw	AlreadyExistsException((utf8*)"A GUI Scheme named '" + d_scheme->d_name + "' is already present in the system.");
		}

	}
    else if (element == FalagardMappingElement)
    {
        Scheme::FalagardMapping fmap;
        fmap.windowName = attributes.getValueAsString(WindowTypeAttribute);
        fmap.targetName = attributes.getValueAsString(TargetTypeAttribute);
        fmap.lookName   = attributes.getValueAsString(LookNFeelAttribute);

        d_scheme->d_falagardMappings.push_back(fmap);
    }
    else if (element == LookNFeelElement)
    {
        Scheme::LoadableUIElement lnf;
        lnf.filename      = attributes.getValueAsString(FilenameAttribute);
        lnf.resourceGroup = attributes.getValueAsString(ResourceGroupAttribute);

        d_scheme->d_looknfeels.push_back(lnf);
    }
	else if (element == FontBlinkTimeElement)
	{
		d_scheme->d_fontBlinkTime = attributes.getValueAsFloat(SecondsAttribute, 0.8f);
	}
	
	else
	{
		throw FileIOException("Scheme::xmlHandler::startElement - Unexpected data was found while parsing the Scheme file: '" + element + "' is unknown.");
	}

}

void Scheme_xmlHandler::elementEnd(const String& element)
{
	if (element == GUISchemeElement)
	{
		Logger::getSingleton().logEvent("Finished creation of Scheme '" + d_scheme->d_name + "' via XML file.", Informative);
	}

}

} 
