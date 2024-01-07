

#ifndef _CEGUIFalWidgetLookManager_h_
#define _CEGUIFalWidgetLookManager_h_

#include "CEGUISingleton.h"
#include "CEGUIString.h"
#include "CEGUIExceptions.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include <map>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#	pragma warning(disable : 4275)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT WidgetLookManager : public Singleton<WidgetLookManager>
    {
    public:
        
        WidgetLookManager();

        
        ~WidgetLookManager();

       	
	      static	WidgetLookManager&	getSingleton(void);


	      
	      static	WidgetLookManager*	getSingletonPtr(void);


        
        void parseLookNFeelSpecification(const String& filename, const String& resourceGroup = "");


        
        bool isWidgetLookAvailable(const String& widget) const;


        
        const WidgetLookFeel& getWidgetLook(const String& widget) const;


        
        void eraseWidgetLook(const String& widget);


        
        void addWidgetLook(WidgetLookFeel& look);

        
        void writeFalagardXMLHeadToStream(OutStream& out_stream) const;

        
        void writeFalagardXMLTailToStream(OutStream& out_stream) const;

        
        void writeWidgetLookToStream(const String& name, OutStream& out_stream) const;

        
        void writeWidgetLookSeriesToStream(const String& prefix, OutStream& out_stream) const;


    private:
        static const String FalagardSchemaName;     

        typedef std::map<String, WidgetLookFeel*> WidgetLookList;
        WidgetLookList  d_widgetLooks;
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
