

#include "CEGUIExpatParser.h"
#include "CEGUIResourceProvider.h"
#include "CEGUISystem.h"
#include "CEGUIXMLHandler.h"
#include "CEGUIXMLAttributes.h"
#include "CEGUIExceptions.h"
#include <expat.h>


namespace CEGUI
{
ExpatParser::ExpatParser(void)
{
    
    d_identifierString = "CEGUI::ExpatParser - Official expat based parser module for CEGUI";
}

ExpatParser::~ExpatParser(void)
{
}

void ExpatParser::parseXMLFile(CEGUI::XMLHandler& handler, const CEGUI::String& filename, const CEGUI::String& schemaName, const CEGUI::String& resourceGroup)
{
    
    XML_Parser parser = XML_ParserCreate(0); 

    if (! parser)
    {
        throw CEGUI::GenericException("ExpatParser::parseXMLFile - Unable to create a new Expat Parser");
    }

    XML_SetUserData(parser, (void*)&handler); 
    XML_SetElementHandler(parser, startElement, endElement); 

    
    CEGUI::RawDataContainer rawXMLData;
    CEGUI::System::getSingleton().getResourceProvider()->loadRawDataContainer(filename, rawXMLData, resourceGroup);

    
    if ( ! XML_Parse(parser, reinterpret_cast<const char*>(rawXMLData.getDataPtr()), rawXMLData.getSize(), true))
    {
		XML_Size line = XML_GetCurrentLineNumber(parser);
		char szTemp[128] = {0};
		sprintf(szTemp, "%d", line);
		CEGUI::String strLine = szTemp;

        CEGUI::System::getSingleton().getResourceProvider()->unloadRawDataContainer(rawXMLData);
        throw CEGUI::GenericException(CEGUI::String((CEGUI::utf8*)"ExpatParser::parseXMLFile( ") + 
									CEGUI::String(filename)+
									CEGUI::String((CEGUI::utf8*)" )  - XML Parsing error '\r\n") +
                                    CEGUI::String((CEGUI::utf8*)XML_ErrorString(XML_GetErrorCode(parser))) +
                                    CEGUI::String((CEGUI::utf8*)"' at line ")  + strLine);
    }

    
    CEGUI::System::getSingleton().getResourceProvider()->unloadRawDataContainer(rawXMLData);

	
	XML_ParserFree(parser);
}

bool ExpatParser::initialiseImpl(void)
{
    return true;
}

void ExpatParser::cleanupImpl(void)
{

}

void ExpatParser::startElement(void* data, const char* element, const char** attr)
{
    CEGUI::XMLHandler* handler = static_cast<XMLHandler*>(data);
    CEGUI::XMLAttributes attrs;

    for(size_t i = 0 ; attr[i] ; i += 2)
        attrs.add((CEGUI::utf8*)attr[i], (CEGUI::utf8*)attr[i+1]);

    handler->elementStart((CEGUI::utf8*)element, attrs);
}

void ExpatParser::endElement(void* data, const char* element)
{
    CEGUI::XMLHandler* handler = static_cast<CEGUI::XMLHandler*>(data);
    handler->elementEnd((CEGUI::utf8*)element);
}

} 
