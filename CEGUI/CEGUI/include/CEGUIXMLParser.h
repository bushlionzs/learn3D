

#ifndef _CEGUIXMLParser_h_
#define _CEGUIXMLParser_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"


namespace CEGUI
{
    
    class CEGUIEXPORT XMLParser
    {
    public:
        
        XMLParser(void);

        
        virtual ~XMLParser(void);

        
        bool initialise(void);

        
        void cleanup(void);

        
        virtual void parseXMLFile(XMLHandler& handler, const String& filename, const String& schemaName, const String& resourceGroup) = 0;

        
        const String& getIdentifierString() const;

    protected:
        
        virtual bool initialiseImpl(void) = 0;

        

        virtual void cleanupImpl(void) = 0;

        
        String d_identifierString;                 

    private:
        bool d_initialised;     
    };

} 


#endif  
