

#include "CEGUIXMLAttributes.h"
#include "CEGUIExceptions.h"
#include <sstream>
#include <iterator>


namespace CEGUI
{
    XMLAttributes::XMLAttributes(void)
    {}

    XMLAttributes::~XMLAttributes(void)
    {}

    void XMLAttributes::add(const String& attrName, const String& attrValue)
    {
        d_attrs[attrName] = attrValue;
    }

    void XMLAttributes::remove(const String& attrName)
    {
        AttributeMap::iterator pos = d_attrs.find(attrName);

        if (pos != d_attrs.end())
            d_attrs.erase(pos);
    }

    bool XMLAttributes::exists(const String& attrName) const
    {
        return d_attrs.find(attrName) != d_attrs.end();
    }

    size_t XMLAttributes::getCount(void) const
    {
        return d_attrs.size();
    }

    const String& XMLAttributes::getName(size_t index) const
    {
        if (index >= d_attrs.size())
        {
            throw InvalidRequestException("XMLAttributes::getName - The specified index is out of range for this XMLAttributes block.");
        }

        AttributeMap::const_iterator iter = d_attrs.begin();
        std::advance(iter, index);

        return (*iter).first;
    }

    const String& XMLAttributes::getValue(size_t index) const
    {
        if (index >= d_attrs.size())
        {
            throw InvalidRequestException("XMLAttributes::getValue - The specified index is out of range for this XMLAttributes block.");
        }

        AttributeMap::const_iterator iter = d_attrs.begin();
        std::advance(iter, index);

        return (*iter).second;
    }

    const String& XMLAttributes::getValue(const String& attrName) const
    {
        AttributeMap::const_iterator pos = d_attrs.find(attrName);

        if (pos != d_attrs.end())
        {
            return (*pos).second;
        }
        else
        {
            throw UnknownObjectException("XMLAttributes::getValue - no value exists for an attribute named '" + attrName + "'.");
        }
    }

    const String& XMLAttributes::getValueAsString(const String& attrName, const String& def) const
    {
        return (exists(attrName)) ? getValue(attrName) : def;
    }


    bool XMLAttributes::getValueAsBool(const String& attrName, bool def) const
    {
        if (!exists(attrName))
        {
            return def;
        }

        const String& val = getValue(attrName);

        if (val == "false" || val == "0")
        {
            return false;
        }
        else if (val == "true" || val == "1")
        {
            return true;
        }
        else
        {
            throw InvalidRequestException("XMLAttributes::getValueAsInteger - failed to convert attribute '" + attrName + "' with value '" + getValue(attrName) + "' to bool.");
        }
    }

    int XMLAttributes::getValueAsInteger(const String& attrName, int def) const
    {
        if (!exists(attrName))
        {
            return def;
        }

        int val;
        std::istringstream strm(getValue(attrName).c_str());

        strm >> val;

        
        if (strm.fail())
        {
            throw InvalidRequestException("XMLAttributes::getValueAsInteger - failed to convert attribute '" + attrName + "' with value '" + getValue(attrName) + "' to integer.");
        }

        return val;
    }

    float XMLAttributes::getValueAsFloat(const String& attrName, float def) const
    {
        if (!exists(attrName))
        {
            return def;
        }

        float val;
        std::istringstream strm(getValue(attrName).c_str());

        strm >> val;

        
        if (strm.fail())
        {
            throw InvalidRequestException("XMLAttributes::getValueAsInteger - failed to convert attribute '" + attrName + "' with value '" + getValue(attrName) + "' to float.");
        }

        return val;
    }



} 
