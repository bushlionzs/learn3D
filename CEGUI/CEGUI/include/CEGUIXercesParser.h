

#ifndef _CEGUIXercesParser_h_
#define _CEGUIXercesParser_h_

#include "CEGUIXMLParser.h"


#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>


namespace CEGUI
{
    class XercesHandler : public XERCES_CPP_NAMESPACE::DefaultHandler
    {
    public:
        XercesHandler(XMLHandler& handler);
        ~XercesHandler(void);

        
        void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XERCES_CPP_NAMESPACE::Attributes& attrs);
        void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
        void warning (const XERCES_CPP_NAMESPACE::SAXParseException &exc);
        void error (const XERCES_CPP_NAMESPACE::SAXParseException &exc);
        void fatalError (const XERCES_CPP_NAMESPACE::SAXParseException &exc);

    protected:
        XMLHandler& d_handler;      
    };

    
    class XercesParser : public XMLParser
    {
    public:
        XercesParser(void);
        ~XercesParser(void);

        
        void parseXMLFile(XMLHandler& handler, const String& filename, const String& schemaName, const String& resourceGroup);

        
        
        static void populateAttributesBlock(const XERCES_CPP_NAMESPACE::Attributes& src, XMLAttributes& dest);

        
        static String transcodeXmlCharToString(const XMLCh* const xmlch_str);

    protected:
        static void initialiseSchema(XERCES_CPP_NAMESPACE::SAX2XMLReader* reader, const String& schemaName, const String& xmlFilename, const String& resourceGroup);
        static XERCES_CPP_NAMESPACE::SAX2XMLReader* createReader(XERCES_CPP_NAMESPACE::DefaultHandler& handler);
        static void doParse(XERCES_CPP_NAMESPACE::SAX2XMLReader* parser, const String& xmlFilename, const String& resourceGroup);

        
        bool initialiseImpl(void);
        void cleanupImpl(void);
    };

} 


#endif  
