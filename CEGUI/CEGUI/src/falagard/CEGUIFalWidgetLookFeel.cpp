

#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIExceptions.h"
#include "CEGUILogger.h"
#include "CEGUIWindowManager.h"
#include <iostream>


namespace CEGUI
{
    WidgetLookFeel::WidgetLookFeel(const String& name) :
        d_lookName(name)
    {}

    const StateImagery& WidgetLookFeel::getStateImagery(const CEGUI::String& state) const
    {
        StateList::const_iterator imagery = d_stateImagery.find(state);

        if (imagery == d_stateImagery.end())
        {
            throw UnknownObjectException("WidgetLookFeel::getStateImagery - unknown state '" + state + "' in look '" + d_lookName + "'.");
        }

        return (*imagery).second;
    }


    const ImagerySection& WidgetLookFeel::getImagerySection(const CEGUI::String& section) const
    {
        ImageryList::const_iterator imgSect = d_imagerySections.find(section);

        if (imgSect == d_imagerySections.end())
        {
            throw UnknownObjectException("WidgetLookFeel::getImagerySection - unknown imagery section '" + section +  "' in look '" + d_lookName + "'.");
        }

        return (*imgSect).second;
    }


    const String& WidgetLookFeel::getName() const
    {
        return d_lookName;
    }

    void WidgetLookFeel::addImagerySection(const ImagerySection& section)
    {
        if (d_imagerySections.find(section.getName()) != d_imagerySections.end())
        {
            Logger::getSingleton().logEvent(
                "WidgetLookFeel::addImagerySection - Defintion for imagery section '" + section.getName() + "' already exists.  Replacing previous definition.");
        }

        d_imagerySections[section.getName()] = section;
    }

    void WidgetLookFeel::addWidgetComponent(const WidgetComponent& widget)
    {
        d_childWidgets.push_back(widget);
    }

    void WidgetLookFeel::addStateSpecification(const StateImagery& state)
    {
        if (d_stateImagery.find(state.getName()) != d_stateImagery.end())
        {
            Logger::getSingleton().logEvent(
                "WidgetLookFeel::addStateSpecification - Defintion for state '" + state.getName() + "' already exists.  Replacing previous definition.");
        }
        const char* str = state.getName().c_str();
        d_stateImagery[state.getName()] = state;
    }

    void WidgetLookFeel::addPropertyInitialiser(const PropertyInitialiser& initialiser)
    {
        d_properties.push_back(initialiser);
    }

    void WidgetLookFeel::clearImagerySections()
    {
        d_imagerySections.clear();
    }

    void WidgetLookFeel::clearWidgetComponents()
    {
        d_childWidgets.clear();
    }

    void WidgetLookFeel::clearStateSpecifications()
    {
        d_stateImagery.clear();
    }

    void WidgetLookFeel::clearPropertyInitialisers()
    {
        d_properties.clear();
    }

    void WidgetLookFeel::initialiseWidget(Window& widget) const
    {
        
        for(PropertyDefinitionList::iterator propdef = d_propertyDefinitions.begin(); propdef != d_propertyDefinitions.end(); ++propdef)
        {
            
            widget.setProperty((*propdef).getName(), (*propdef).getDefault(&widget));
        }

        
        for(PropertyList::const_iterator prop = d_properties.begin(); prop != d_properties.end(); ++prop)
        {
            (*prop).apply(widget);
        }

        
        for(WidgetList::const_iterator curr = d_childWidgets.begin(); curr != d_childWidgets.end(); ++curr)
        {
            (*curr).create(widget);
        }
    }

    bool WidgetLookFeel::isStateImageryPresent(const String& state) const
    {
        return d_stateImagery.find(state) != d_stateImagery.end();
    }

    void WidgetLookFeel::addNamedArea(const NamedArea& area)
    {
        if (d_namedAreas.find(area.getName()) != d_namedAreas.end())
        {
            Logger::getSingleton().logEvent(
                "WidgetLookFeel::addNamedArea - Defintion for area '" + area.getName() + "' already exists.  Replacing previous definition.");
        }

        d_namedAreas[area.getName()] = area;
    }

    void WidgetLookFeel::clearNamedAreas()
    {
        d_namedAreas.clear();
    }

    const NamedArea& WidgetLookFeel::getNamedArea(const String& name) const
    {
        NamedAreaList::const_iterator area = d_namedAreas.find(name);

        if (area == d_namedAreas.end())
        {
            throw UnknownObjectException("WidgetLookFeel::getNamedArea - unknown named area: '" + name +  "' in look '" + d_lookName + "'.");
        }

        return (*area).second;
    }

    bool WidgetLookFeel::isNamedAreaDefined(const String& name) const
    {
        return d_namedAreas.find(name) != d_namedAreas.end();
    }

    void WidgetLookFeel::layoutChildWidgets(const Window& owner) const
    {
        
        for(WidgetList::const_iterator wdgt = d_childWidgets.begin(); wdgt != d_childWidgets.end(); ++wdgt)
        {
            (*wdgt).layout(owner);
        }
    }

    void WidgetLookFeel::addPropertyDefinition(const PropertyDefinition& propdef)
    {
		if(propdef.getName() == "VertLabelFormatting")
		{
			int a=0;
		}
        d_propertyDefinitions.push_back(propdef);
		
		addProperty(&(*(d_propertyDefinitions.rbegin())));
    }

    void WidgetLookFeel::clearPropertyDefinitions()
    {
        d_propertyDefinitions.clear();
    }

    void WidgetLookFeel::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<WidgetLook name=\"" << d_lookName << "\">" << std::endl;

        
        {
          
          for (PropertyDefinitionList::const_iterator curr = d_propertyDefinitions.begin(); curr != d_propertyDefinitions.end(); ++curr)
              (*curr).writeXMLToStream(out_stream);
        }

        {
          
          for (PropertyList::const_iterator curr = d_properties.begin(); curr != d_properties.end(); ++curr)
              (*curr).writeXMLToStream(out_stream);
        }

        {
          
          for (NamedAreaList::const_iterator curr = d_namedAreas.begin(); curr != d_namedAreas.end(); ++curr)
              (*curr).second.writeXMLToStream(out_stream);
        }

        {
          
          for (WidgetList::const_iterator curr = d_childWidgets.begin(); curr != d_childWidgets.end(); ++curr)
              (*curr).writeXMLToStream(out_stream);
        }

        {
          
          for (ImageryList::const_iterator curr = d_imagerySections.begin(); curr != d_imagerySections.end(); ++curr)
              (*curr).second.writeXMLToStream(out_stream);
        }

        {
          
          for (StateList::const_iterator curr = d_stateImagery.begin(); curr != d_stateImagery.end(); ++curr)
              (*curr).second.writeXMLToStream(out_stream);
        }

        out_stream << "</WidgetLook>" << std::endl;
    }

    void WidgetLookFeel::renameChildren(const Window& widget, const String& newBaseName) const
    {
        WindowManager& winMgr = WindowManager::getSingleton();

        for(WidgetList::const_iterator curr = d_childWidgets.begin(); curr != d_childWidgets.end(); ++curr)
            winMgr.renameWindow(widget.getName() + (*curr).getWidgetNameSuffix(),
                                newBaseName + (*curr).getWidgetNameSuffix());
    }

} 
