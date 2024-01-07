

#ifndef _CEGUIFalNamedArea_h_
#define _CEGUIFalNamedArea_h_

#include "falagard/CEGUIFalDimensions.h"


namespace CEGUI
{
    
    class CEGUIEXPORT NamedArea
    {
    public:
        NamedArea() {}
        NamedArea(const String& name);

        
        const String& getName() const;

        
        const ComponentArea& getArea() const;

        
        void setArea(const ComponentArea& area);

        
        void writeXMLToStream(OutStream& out_stream) const;

    private:
        String d_name;
        ComponentArea d_area;
    };

} 


#endif  
