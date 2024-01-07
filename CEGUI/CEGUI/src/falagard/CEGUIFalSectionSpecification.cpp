

#include "falagard/CEGUIFalSectionSpecification.h"
#include "falagard/CEGUIFalImagerySection.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "CEGUIExceptions.h"
#include "CEGUIPropertyHelper.h"
#include <iostream>


namespace CEGUI
{
    SectionSpecification::SectionSpecification(const String& owner, const String& sectionName) :
        d_owner(owner),
        d_sectionName(sectionName),
        d_usingColourOverride(false),
        d_colourProperyIsRect(false)
    {}

    SectionSpecification::SectionSpecification(const String& owner, const String& sectionName, const ColourRect& cols) :
        d_owner(owner),
        d_sectionName(sectionName),
        d_coloursOverride(cols),
        d_usingColourOverride(true),
        d_colourProperyIsRect(false)
    {}

    void SectionSpecification::render(Window& srcWindow, float base_z, const ColourRect* modcols, const Rect* clipper, bool clipToDisplay) const
    {
        try
        {
            
			const ImagerySection* sect =
				&WidgetLookManager::getSingleton().getWidgetLook(d_owner).getImagerySection(d_sectionName);

            
            ColourRect finalColours;
            initColourRectForOverride(srcWindow, finalColours);
            finalColours.modulateAlpha(srcWindow.getEffectiveAlpha());

            if (modcols)
                finalColours *= *modcols;

            
            sect->render(srcWindow, base_z, &finalColours, clipper, clipToDisplay);
        }
        
        catch (Exception)
        {}
    }

    void SectionSpecification::render(Window& srcWindow, const Rect& baseRect, float base_z, const ColourRect* modcols, const Rect* clipper, bool clipToDisplay) const
    {
        try
        {
            
            const ImagerySection* sect =
                &WidgetLookManager::getSingleton().getWidgetLook(d_owner).getImagerySection(d_sectionName);

            
            ColourRect finalColours;
            initColourRectForOverride(srcWindow, finalColours);
            finalColours.modulateAlpha(srcWindow.getEffectiveAlpha());

            if (modcols)
                finalColours *= *modcols;

            
            sect->render(srcWindow, baseRect, base_z, &finalColours, clipper, clipToDisplay);
        }
        
        catch (Exception)
        {}
    }

    const String& SectionSpecification::getOwnerWidgetLookFeel() const
    {
        return d_owner;
    }

    const String& SectionSpecification::getSectionName() const
    {
        return d_sectionName;
    }

    const ColourRect& SectionSpecification::getOverrideColours() const
    {
        return d_coloursOverride;
    }

    void SectionSpecification::setOverrideColours(const ColourRect& cols)
    {
        d_coloursOverride = cols;
    }

    bool SectionSpecification::isUsingOverrideColours() const
    {
        return d_usingColourOverride;
    }

    void SectionSpecification::setUsingOverrideColours(bool setting)
    {
        d_usingColourOverride = setting;
    }

    void SectionSpecification::setOverrideColoursPropertySource(const String& property)
    {
        d_colourPropertyName = property;
    }

    void SectionSpecification::initColourRectForOverride(const Window& wnd, ColourRect& cr) const
    {
        
        if (!d_usingColourOverride)
        {
            colour val(1,1,1,1);
            cr.d_top_left     = val;
            cr.d_top_right    = val;
            cr.d_bottom_left  = val;
            cr.d_bottom_right = val;
        }
        
        else if (!d_colourPropertyName.empty())
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
            cr = d_coloursOverride;
        }
    }

    void SectionSpecification::setOverrideColoursPropertyIsColourRect(bool setting)
    {
        d_colourProperyIsRect = setting;
    }

    void SectionSpecification::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<Section ";

        if (!d_owner.empty())
            out_stream << "look=\"" << d_owner << "\" ";

        out_stream << "section=\"" << d_sectionName << "\"";

        if (d_usingColourOverride)
        {
            
            out_stream << ">" << std::endl;

            
            if (!d_colourPropertyName.empty())
            {
                if (d_colourProperyIsRect)
                    out_stream << "<ColourRectProperty ";
                else
                    out_stream << "<ColourProperty ";

                out_stream << "name=\"" << d_colourPropertyName << "\" />" << std::endl;
            }
            else if (!d_coloursOverride.isMonochromatic() || d_coloursOverride.d_top_left != colour(1,1,1,1))
            {
                out_stream << "<Colours ";
                out_stream << "topLeft=\"" << PropertyHelper::colourToString(d_coloursOverride.d_top_left) << "\" ";
                out_stream << "topRight=\"" << PropertyHelper::colourToString(d_coloursOverride.d_top_right) << "\" ";
                out_stream << "bottomLeft=\"" << PropertyHelper::colourToString(d_coloursOverride.d_bottom_left) << "\" ";
                out_stream << "bottomRight=\"" << PropertyHelper::colourToString(d_coloursOverride.d_bottom_right) << "\" />" << std::endl;
            }

            
            out_stream << "</Section>" << std::endl;
        }
        else
        {
            
            out_stream << " />" << std::endl;
        }
    }

} 
