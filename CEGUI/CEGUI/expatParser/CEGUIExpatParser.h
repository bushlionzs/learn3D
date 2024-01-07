

#ifndef _CEGUIExpatParser_h_
#define _CEGUIExpatParser_h_

#include "CEGUIXMLParser.h"


namespace CEGUI
{


class CEGUIEXPORT ExpatParser : public CEGUI::XMLParser
{
public:
    ExpatParser(void);
    ~ExpatParser(void);
    
    void parseXMLFile(CEGUI::XMLHandler& handler, const CEGUI::String& filename, const CEGUI::String& schemaName, const CEGUI::String& resourceGroup);

protected:
    
    bool initialiseImpl(void);
    
    void cleanupImpl(void);
    
    static void startElement(void* data, const char* element, const char**attr); 
    static void endElement(void* data, const char* element); 
};

} 

#endif 
