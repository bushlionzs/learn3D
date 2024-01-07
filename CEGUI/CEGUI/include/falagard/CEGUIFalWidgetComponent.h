

#ifndef _CEGUIFalWidgetComponent_h_
#define _CEGUIFalWidgetComponent_h_

#include "falagard/CEGUIFalDimensions.h"
#include "falagard/CEGUIFalPropertyInitialiser.h"
#include "CEGUIWindow.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT WidgetComponent
    {
    public:
        WidgetComponent() {}
        WidgetComponent(const String& type, const String& look, const String& suffix);

        
        void create(Window& parent) const;

        const ComponentArea& getComponentArea() const;
        void setComponentArea(const ComponentArea& area);

        const String& getBaseWidgetType() const;
        void setBaseWidgetType(const String& type);

        const String& getWidgetLookName() const;
        void setWidgetLookName(const String& look);

        const String& getWidgetNameSuffix() const;
        void setWidgetNameSuffix(const String& suffix);

        VerticalAlignment getVerticalWidgetAlignemnt() const;
        void setVerticalWidgetAlignment(VerticalAlignment alignment);

        HorizontalAlignment getHorizontalWidgetAlignemnt() const;
        void setHorizontalWidgetAlignemnt(HorizontalAlignment alignment);

        void addPropertyInitialiser(const PropertyInitialiser& initialiser);
        void clearPropertyInitialisers();

        void layout(const Window& owner) const;

        
        void writeXMLToStream(OutStream& out_stream) const;

    private:
        typedef std::vector<PropertyInitialiser> PropertiesList;

        ComponentArea   d_area;              
        String   d_baseType;                 
        String   d_imageryName;              
        String   d_nameSuffix;               
        VerticalAlignment    d_vertAlign;    
        HorizontalAlignment  d_horzAlign;    
        PropertiesList  d_properties;        
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
