

#include "CEGUIProperty.h"
#include <iostream>


namespace CEGUI
{
	
	bool Property::isDefault(const PropertyReceiver* receiver) const
	{
		return (get(receiver) == d_default);
	}

	
	String Property::getDefault(const PropertyReceiver* receiver) const
	{
		return d_default;
	}

    void Property::writeXMLToStream(const PropertyReceiver* receiver, OutStream& out_stream) const
    {
        if (d_writeXML)
        {
            out_stream << "<Property Name=\"" << d_name <<"\" Value=\"" << get(receiver).c_str() << "\" />"  << std::endl;
        }
    }

} 
