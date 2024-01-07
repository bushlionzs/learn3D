

#ifndef _CEGUIFalPropertyInitialiser_h_
#define _CEGUIFalPropertyInitialiser_h_

#include "CEGUIPropertySet.h"



namespace CEGUI
{
    
    class CEGUIEXPORT PropertyInitialiser
    {
    public:
        
        PropertyInitialiser(const String& property, const String& value);

        
        void apply(Window& target) const;

        
        const String& getTargetPropertyName() const;

        
        const String& getInitialiserValue() const;

        
        void writeXMLToStream(OutStream& out_stream) const;

    private:
        CEGUI::String   d_propertyName;     
        CEGUI::String   d_propertyValue;    
    };

} 


#endif  
