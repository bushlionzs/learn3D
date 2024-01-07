

#include "falagard/CEGUIFalNamedArea.h"
#include <iostream>


namespace CEGUI
{
    NamedArea::NamedArea(const String& name) :
        d_name(name)
    {
    }

    const String& NamedArea::getName() const
    {
        return d_name;
    }

    const ComponentArea& NamedArea::getArea() const
    {
        return d_area;
    }

    void NamedArea::setArea(const ComponentArea& area)
    {
        d_area = area;
    }

    void NamedArea::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<NamedArea name=\"" << d_name << "\">" << std::endl;
        d_area.writeXMLToStream(out_stream);
        out_stream << "</NamedArea>" << std::endl;
    }

} 
