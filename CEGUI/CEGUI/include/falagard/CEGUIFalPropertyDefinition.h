

#ifndef _CEGUIFalPropertyDefinition_h_
#define _CEGUIFalPropertyDefinition_h_

#include "CEGUIProperty.h"


namespace CEGUI
{
    
    class CEGUIEXPORT PropertyDefinition : public Property
    {
    public:
        PropertyDefinition(const String& name, const String& initialValue, bool redrawOnWrite, bool layoutOnWrite);

        
        String get(const PropertyReceiver* receiver) const;
        void set(PropertyReceiver* receiver, const String& value);

        
        void writeXMLToStream(OutStream& out_stream) const;

    protected:
        String d_userStringName;
        bool d_writeCausesRedraw;
        bool d_writeCausesLayout;
    };

} 


#endif  
