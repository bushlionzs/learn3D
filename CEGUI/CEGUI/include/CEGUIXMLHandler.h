

#ifndef _CEGUIXMLHandler_h_
#define _CEGUIXMLHandler_h_

#include "CEGUIBase.h"



namespace CEGUI
{
    class CEGUIEXPORT XMLHandler
    {
    public:
        
        XMLHandler(void);

        
        virtual ~XMLHandler(void);
        
        
        virtual void elementStart(const String& element, const XMLAttributes& attributes);
        
        
        virtual void elementEnd(const String& element);

	
	virtual void text(const String& text);
    };

} 


#endif  
