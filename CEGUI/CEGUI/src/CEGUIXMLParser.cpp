

#include "CEGUIXMLParser.h"


namespace CEGUI
{

    XMLParser::XMLParser(void) :
            d_identifierString("Unknown XML parser (vendor did not set the ID string!)"),
            d_initialised(false)
    {}

    XMLParser::~XMLParser(void)
    {}

    bool XMLParser::initialise(void)
    {
        
        if (!d_initialised)
        {
            d_initialised = initialiseImpl();
        }

        return d_initialised;
    }

    void XMLParser::cleanup(void)
    {
        if (d_initialised)
        {
            cleanupImpl();
            d_initialised = false;
        }
    }

    const String& XMLParser::getIdentifierString() const
    {
        return d_identifierString;
    }

} 
