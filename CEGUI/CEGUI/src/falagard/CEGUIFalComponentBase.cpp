

#include "falagard/CEGUIFalComponentBase.h"
#include "CEGUIExceptions.h"
#include "CEGUIPropertyHelper.h"
#include <iostream>


namespace CEGUI
{
    FalagardComponentBase::FalagardComponentBase() :
        d_colours(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF),
        d_colourProperyIsRect(false)
    {}

    FalagardComponentBase::~ FalagardComponentBase()
    {}

    void FalagardComponentBase::render(Window& srcWindow, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        Rect destRect(d_area.getPixelRect(srcWindow));
        render_impl(srcWindow, destRect, base_z, modColours, clipper, clipToDisplay);
    }

    void FalagardComponentBase::render(Window& srcWindow, const Rect& baseRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        Rect destRect(d_area.getPixelRect(srcWindow, baseRect));
        render_impl(srcWindow, destRect, base_z, modColours, clipper, clipToDisplay);
    }

    const ComponentArea& FalagardComponentBase::getComponentArea() const
    {
        return d_area;
    }

    void FalagardComponentBase::setComponentArea(const ComponentArea& area)
    {
        d_area = area;
    }

    const ColourRect& FalagardComponentBase::getColours() const
    {
        return d_colours;
    }

    void FalagardComponentBase::setColours(const ColourRect& cols)
    {
        d_colours = cols;
    }

    void FalagardComponentBase::setColoursPropertySource(const String& property)
    {
        d_colourPropertyName = property;
    }

    void FalagardComponentBase::setColoursPropertyIsColourRect(bool setting)
    {
        d_colourProperyIsRect = setting;
    }

    void FalagardComponentBase::initColoursRect(const Window& wnd, const ColourRect* modCols, ColourRect& cr) const
    {
        
        if (!d_colourPropertyName.empty())
        {
            
            if (d_colourProperyIsRect)
            {
                cr = PropertyHelper::stringToColourRect(wnd.getProperty(d_colourPropertyName));
            }
            
            else
            {
                colour val(PropertyHelper::stringToColour(wnd.getProperty(d_colourPropertyName)));
                cr.d_top_left     = val;
                cr.d_top_right    = val;
                cr.d_bottom_left  = val;
                cr.d_bottom_right = val;
            }
        }
        
        else
        {
            cr = d_colours;
        }

        if (modCols)
        {
            cr *= *modCols;
        }
    }


    void FalagardComponentBase::setVertFormattingPropertySource(const String& property)
    {
        d_vertFormatPropertyName = property;
    }

    void FalagardComponentBase::setHorzFormattingPropertySource(const String& property)
    {
        d_horzFormatPropertyName = property;
    }

    bool FalagardComponentBase::writeColoursXML(OutStream& out_stream) const
    {
        if (!d_colourPropertyName.empty())
        {
            if (d_colourProperyIsRect)
                out_stream << "<ColourRectProperty ";
            else
                out_stream << "<ColourProperty ";

            out_stream << "name=\"" << d_colourPropertyName << "\" />" << std::endl;
        }
        else if (!d_colours.isMonochromatic() || d_colours.d_top_left != colour(1,1,1,1))
        {
            out_stream << "<Colours ";
            out_stream << "topLeft=\"" << PropertyHelper::colourToString(d_colours.d_top_left) << "\" ";
            out_stream << "topRight=\"" << PropertyHelper::colourToString(d_colours.d_top_right) << "\" ";
            out_stream << "bottomLeft=\"" << PropertyHelper::colourToString(d_colours.d_bottom_left) << "\" ";
            out_stream << "bottomRight=\"" << PropertyHelper::colourToString(d_colours.d_bottom_right) << "\" />" << std::endl;
        }
        else
        {
            return false;
        }

        return true;
    }

    bool FalagardComponentBase::writeVertFormatXML(OutStream& out_stream) const
    {
        if (!d_vertFormatPropertyName.empty())
        {
            out_stream << "<VertFormatProperty name=\"" << d_vertFormatPropertyName << "\" />" << std::endl;
            return true;
        }

        return false;
    }

    bool FalagardComponentBase::writeHorzFormatXML(OutStream& out_stream) const
    {
        if (!d_horzFormatPropertyName.empty())
        {
            out_stream << "<HorzFormatProperty name=\"" << d_horzFormatPropertyName << "\" />" << std::endl;
            return true;
        }

        return false;
    }

} 
