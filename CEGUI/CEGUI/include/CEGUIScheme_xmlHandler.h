

#ifndef _CEGUIScheme_xmlHandler_h_
#define _CEGUIScheme_xmlHandler_h_

#include "CEGUIScheme.h"
#include "CEGUIXMLHandler.h"


namespace CEGUI
{

    
    class Scheme_xmlHandler : public XMLHandler
    {
    public:
        
        
        Scheme_xmlHandler(Scheme* scheme) : d_scheme(scheme)
        {}

        
        virtual ~Scheme_xmlHandler(void)
        {}

        
        
        virtual void elementStart(const String& element, const XMLAttributes& attributes);
        virtual void elementEnd(const String& element);

    private:
        
        
        static const String GUISchemeElement;               
        static const String ImagesetElement;                
		static const String ImagesetBinElement;				
        static const String ImagesetFromImageElement;       
        static const String FontElement;                    
        static const String WindowSetElement;               
        static const String WindowFactoryElement;           
        static const String WindowAliasElement;             
        static const String FalagardMappingElement;         
        static const String LookNFeelElement;               
		static const String TypeAttribute;					
        static const String NameAttribute;                  
        static const String FilenameAttribute;              
        static const String AliasAttribute;                 
        static const String TargetAttribute;                
        static const String ResourceGroupAttribute;         
        static const String WindowTypeAttribute;            
        static const String TargetTypeAttribute;            
        static const String LookNFeelAttribute;             

		static const char	FontType_FreeType[];			
		static const char	FontType_Bitmap[];				

		static const String FontBlinkTimeElement;			
		static const String	SecondsAttribute;				
        
        Scheme* d_scheme;           
    };

} 

#endif  
