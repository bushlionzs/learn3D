

#include "CEGUIImageset_xmlHandler.h"

#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUILogger.h"
#include "CEGUIXMLAttributes.h"


namespace CEGUI
{



const String Imageset_xmlHandler::ImagesetElement( (utf8*)"Imageset" );
const String Imageset_xmlHandler::ImageElement( (utf8*)"Image" );
const char	Imageset_xmlHandler::ImagesetImageFileAttribute[]		= "Imagefile";
const char	Imageset_xmlHandler::ImagesetResourceGroupAttribute[]   = "ResourceGroup";
const char	Imageset_xmlHandler::ImagesetNameAttribute[]			= "Name";
const char	Imageset_xmlHandler::ImagesetNativeHorzResAttribute[]	= "NativeHorzRes";
const char	Imageset_xmlHandler::ImagesetNativeVertResAttribute[]	= "NativeVertRes";
const char	Imageset_xmlHandler::ImagesetAutoScaledAttribute[]		= "AutoScaled";
const char	Imageset_xmlHandler::ImageNameAttribute[]				= "Name";
const char	Imageset_xmlHandler::ImageXPosAttribute[]				= "XPos";
const char	Imageset_xmlHandler::ImageYPosAttribute[]				= "YPos";
const char	Imageset_xmlHandler::ImageWidthAttribute[]				= "Width";
const char	Imageset_xmlHandler::ImageHeightAttribute[]				= "Height";
const char	Imageset_xmlHandler::ImageXOffsetAttribute[]			= "XOffset";
const char	Imageset_xmlHandler::ImageYOffsetAttribute[]			= "YOffset";


void Imageset_xmlHandler::elementStart(const String& element, const XMLAttributes& attributes)
{
	
	if (element == ImageElement)
	{
		String	name(attributes.getValueAsString(ImageNameAttribute));

		Rect	rect;
        rect.d_left	= (float)attributes.getValueAsInteger(ImageXPosAttribute);
        rect.d_top	= (float)attributes.getValueAsInteger(ImageYPosAttribute);
        rect.setWidth((float)attributes.getValueAsInteger(ImageWidthAttribute));
        rect.setHeight((float)attributes.getValueAsInteger(ImageHeightAttribute));

		Point	offset;
        offset.d_x	= (float)attributes.getValueAsInteger(ImageXOffsetAttribute, 0);
        offset.d_y	= (float)attributes.getValueAsInteger(ImageYOffsetAttribute, 0);

		d_imageset->defineImage(name, rect, offset);
	}
	
	else if (element == ImagesetElement)
	{
        d_imageset->d_name = attributes.getValueAsString(ImagesetNameAttribute);

		Logger::getSingleton().logEvent("Started creation of Imageset '" + d_imageset->d_name + "' via XML file.", Informative);

		
		
		
		float hres, vres;

		
        hres = (float)attributes.getValueAsInteger(ImagesetNativeHorzResAttribute, 1024);

		
        vres = (float)attributes.getValueAsInteger(ImagesetNativeVertResAttribute, 768);

		d_imageset->setNativeResolution(Size(hres, vres));

		
        d_imageset->setAutoScalingEnabled(attributes.getValueAsBool(ImagesetAutoScaledAttribute, true));

		
		
		
		String filename(attributes.getValueAsString(ImagesetImageFileAttribute));
		String resourceGroup(attributes.getValueAsString(ImagesetResourceGroupAttribute));

		
		if(filename.empty())
		{
			throw GenericException((utf8*)"Imageset::xmlHandler::startElement - Must define 'Imagefile' for a imageset file: '" + filename + "'");
		}

		
		if(!ImagesetManager::getSingleton().d_textureLoadDelay )
		{
			try
			{
				d_imageset->d_texture = System::getSingleton().getRenderer()->createTexture(filename, resourceGroup);
			}
			catch(...)
			{
				throw RendererException((utf8*)"Imageset::xmlHandler::startElement - An unexpected error occurred while creating a Texture object from file '" + filename + "'");
			}
		}

        d_imageset->d_textureFilename = filename;
	}
	
	else
	{
		throw FileIOException("Imageset::xmlHandler::startElement - Unexpected data was found while parsing the Imageset file: '" + element + "' is unknown.");
	}

}

void Imageset_xmlHandler::elementEnd(const String& element)
{
	if (element == ImagesetElement)
	{
		Logger::getSingleton().logEvent("Finished creation of Imageset '" + d_imageset->d_name + "' via XML file.", Informative);
	}
}

} 
