

#include "falagard/CEGUIFalPropertyInitialiser.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindow.h"
#include <iostream>


namespace CEGUI
{
    PropertyInitialiser::PropertyInitialiser(const String& property, const String& value) :
        d_propertyName(property),
        d_propertyValue(value)
    {}

    void PropertyInitialiser::apply(Window& target) const
    {
        try
        {
            target.setProperty(d_propertyName, d_propertyValue);
        }
        
        catch (UnknownObjectException)
        {}
    }

    const String& PropertyInitialiser::getTargetPropertyName() const
    {
        return d_propertyName;
    }

    const String& PropertyInitialiser::getInitialiserValue() const
    {
        return d_propertyValue;
    }

    void PropertyInitialiser::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<Property name=\"" << d_propertyName << "\" value=\"" << d_propertyValue << "\" />" << std::endl;
    }

} 
