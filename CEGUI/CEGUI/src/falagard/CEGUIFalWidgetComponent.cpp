

#include "falagard/CEGUIFalWidgetComponent.h"
#include "falagard/CEGUIFalXMLEnumHelper.h"
#include "CEGUIWindowManager.h"
#include "CEGUIExceptions.h"
#include <iostream>


namespace CEGUI
{
    WidgetComponent::WidgetComponent(const String& type, const String& look, const String& suffix) :
        d_baseType(type),
        d_imageryName(look),
        d_nameSuffix(suffix),
        d_vertAlign(VA_TOP),
        d_horzAlign(HA_LEFT)
    {}

    void WidgetComponent::create(Window& parent) const
    {
        
        String widgetName = parent.getName() + d_nameSuffix;
        Window* widget = WindowManager::getSingleton().createWindow(d_baseType, widgetName);

        
        if (!d_imageryName.empty())
            widget->setLookNFeel("", d_imageryName);

        
        parent.addChildWindow(widget);

        
        widget->setVerticalAlignment(d_vertAlign);
        widget->setHorizontalAlignment(d_horzAlign);

        
        
        

        
        
        for(PropertiesList::const_iterator curr = d_properties.begin(); curr != d_properties.end(); ++curr)
        {
            (*curr).apply(*widget);
        }
    }

    const ComponentArea& WidgetComponent::getComponentArea() const
    {
        return d_area;
    }

    void WidgetComponent::setComponentArea(const ComponentArea& area)
    {
        d_area = area;
    }

    const String& WidgetComponent::getBaseWidgetType() const
    {
        return d_baseType;
    }

    void WidgetComponent::setBaseWidgetType(const String& type)
    {
        d_baseType = type;
    }

    const String& WidgetComponent::getWidgetLookName() const
    {
        return d_imageryName;
    }

    void WidgetComponent::setWidgetLookName(const String& look)
    {
        d_imageryName = look;
    }

    const String& WidgetComponent::getWidgetNameSuffix() const
    {
        return d_nameSuffix;
    }

    void WidgetComponent::setWidgetNameSuffix(const String& suffix)
    {
        d_nameSuffix = suffix;
    }

    VerticalAlignment WidgetComponent::getVerticalWidgetAlignemnt() const
    {
        return d_vertAlign;
    }

    void WidgetComponent::setVerticalWidgetAlignment(VerticalAlignment alignment)
    {
        d_vertAlign = alignment;
    }

    HorizontalAlignment WidgetComponent::getHorizontalWidgetAlignemnt() const
    {
        return d_horzAlign;
    }

    void WidgetComponent::setHorizontalWidgetAlignemnt(HorizontalAlignment alignment)
    {
        d_horzAlign = alignment;
    }

    void WidgetComponent::addPropertyInitialiser(const PropertyInitialiser& initialiser)
    {
        d_properties.push_back(initialiser);
    }

    void WidgetComponent::clearPropertyInitialisers()
    {
        d_properties.clear();
    }

    void WidgetComponent::layout(const Window& owner) const
    {
        try
        {
            WindowManager::getSingleton().getWindow(owner.getName() + d_nameSuffix)->setRect(Absolute, d_area.getPixelRect(owner));
        }
        catch (UnknownObjectException)
        {}
    }

    void WidgetComponent::writeXMLToStream(OutStream& out_stream) const
    {
        
        out_stream << "<Child type=\"" << d_baseType << "\" nameSuffix=\"" << d_nameSuffix << "\"";

        if (!d_imageryName.empty())
            out_stream << " look=\"" << d_imageryName << "\"";

        out_stream << ">" << std::endl;

        
        d_area.writeXMLToStream(out_stream);

        
        out_stream << "<VertAlignment type=\"" << FalagardXMLHelper::vertAlignmentToString(d_vertAlign) << "\" />" << std::endl;

        
        out_stream << "<HorzAlignment type=\"" << FalagardXMLHelper::horzAlignmentToString(d_horzAlign) << "\" />" << std::endl;

        
        for (PropertiesList::const_iterator prop = d_properties.begin(); prop != d_properties.end(); ++prop)
        {
            (*prop).writeXMLToStream(out_stream);
        }

        
        out_stream << "</Child>" << std::endl;
    }

} 
