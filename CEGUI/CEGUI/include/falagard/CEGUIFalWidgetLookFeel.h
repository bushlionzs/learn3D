

#ifndef _CEGUIFalWidgetLookFeel_h_
#define _CEGUIFalWidgetLookFeel_h_

#include "CEGUIPropertySet.h"
#include "falagard/CEGUIFalStateImagery.h"
#include "falagard/CEGUIFalWidgetComponent.h"
#include "falagard/CEGUIFalImagerySection.h"
#include "falagard/CEGUIFalPropertyInitialiser.h"
#include "falagard/CEGUIFalPropertyDefinition.h"
#include "falagard/CEGUIFalNamedArea.h"
#include <map>
#include <list>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{
    
    class CEGUIEXPORT WidgetLookFeel : public PropertySet
    {
    public:
        WidgetLookFeel(const String& name);
        WidgetLookFeel() {}

        
        const StateImagery& getStateImagery(const CEGUI::String& state) const;

        
        const ImagerySection& getImagerySection(const CEGUI::String& section) const;

        
        const String& getName() const;

        
        void addImagerySection(const ImagerySection& section);

        
        void addWidgetComponent(const WidgetComponent& widget);

        
        void addStateSpecification(const StateImagery& state);

        
        void addPropertyInitialiser(const PropertyInitialiser& initialiser);

        
        void clearImagerySections();

        
        void clearWidgetComponents();

        
        void clearStateSpecifications();

        
        void clearPropertyInitialisers();

        
        void initialiseWidget(Window& widget) const;

        
        bool isStateImageryPresent(const String& state) const;

        
        void addNamedArea(const NamedArea& area);

        
        void clearNamedAreas();

        
        const NamedArea& getNamedArea(const String& name) const;

        
        bool isNamedAreaDefined(const String& name) const;

        
        void layoutChildWidgets(const Window& owner) const;

        
        void addPropertyDefinition(const PropertyDefinition& propdef);

        
        void clearPropertyDefinitions();

        
        void writeXMLToStream(OutStream& out_stream) const;

        
        void renameChildren(const Window& widget, const String& newBaseName) const;

    private:
        typedef std::map<String, StateImagery>    StateList;
        typedef std::map<String, ImagerySection>  ImageryList;
        typedef std::map<String, NamedArea>       NamedAreaList;
        typedef std::vector<WidgetComponent>      WidgetList;
        typedef std::vector<PropertyInitialiser>  PropertyList;
        typedef std::list<PropertyDefinition>   PropertyDefinitionList;

        CEGUI::String   d_lookName;         
        ImageryList     d_imagerySections;  
        WidgetList      d_childWidgets;     
        StateList       d_stateImagery;     
        PropertyList    d_properties;       
        NamedAreaList   d_namedAreas;       
        mutable PropertyDefinitionList  d_propertyDefinitions;  
    };


} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
