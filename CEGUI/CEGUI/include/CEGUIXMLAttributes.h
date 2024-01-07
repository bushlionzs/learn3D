

#ifndef _CEGUIXMLAttributes_h_
#define _CEGUIXMLAttributes_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include <map>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT XMLAttributes
    {
    public:
        
        XMLAttributes(void);

        
        virtual ~XMLAttributes(void);

        
        void add(const String& attrName, const String& attrValue);
        
        
        void remove(const String& attrName);

        
        bool exists(const String& attrName) const;

        
        size_t getCount(void) const;

        
        const String& getName(size_t index) const;
        
        
        const String& getValue(size_t index) const;

        
        const String& getValue(const String& attrName) const;

        
        const String& getValueAsString(const String& attrName, const String& def = "") const;

        
        bool getValueAsBool(const String& attrName, bool def = false) const;
        
        
        int getValueAsInteger(const String& attrName, int def = 0) const;
        
        
        float getValueAsFloat(const String& attrName, float def = 0.0f) const;

    protected:
        typedef std::map<String, String, String::FastLessCompare> AttributeMap;
        AttributeMap    d_attrs;
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
