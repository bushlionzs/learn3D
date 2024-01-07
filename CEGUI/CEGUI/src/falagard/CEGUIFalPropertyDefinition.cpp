

#include "falagard/CEGUIFalPropertyDefinition.h"
#include "CEGUIWindow.h"
#include <iostream>


namespace CEGUI
{
    PropertyDefinition::PropertyDefinition(const String& name, const String& initialValue, bool redrawOnWrite, bool layoutOnWrite) :
        Property(name, "Falagard custom property definition - gets/sets a named user string.", initialValue),
        d_userStringName(name + "_fal_auto_prop__"),
        d_writeCausesRedraw(redrawOnWrite),
        d_writeCausesLayout(layoutOnWrite)
    {
    }

    
    String PropertyDefinition::get(const PropertyReceiver* receiver) const
    {
        return static_cast<const Window*>(receiver)->getUserString(d_userStringName);
    }

    void PropertyDefinition::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Window*>(receiver)->setUserString(d_userStringName, value);

        if (d_writeCausesLayout)
            static_cast<Window*>(receiver)->performChildWindowLayout();

        if (d_writeCausesRedraw)
            static_cast<Window*>(receiver)->requestRedraw();
    }

    void PropertyDefinition::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<PropertyDefinition name=\"" << d_name << "\" ";

        if (!d_default.empty())
            out_stream << "initialValue=\"" << d_default << "\" ";

        if (d_writeCausesRedraw)
            out_stream << "redrawOnWrite=\"true\" ";

        if (d_writeCausesLayout)
            out_stream << "layoutOnWrite=\"true\" ";

        out_stream << "/>" << std::endl;
    }

} 
