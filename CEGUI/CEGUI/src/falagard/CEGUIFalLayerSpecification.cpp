

#include "falagard/CEGUIFalLayerSpecification.h"
#include <iostream>


namespace CEGUI
{
    LayerSpecification::LayerSpecification(uint priority) :
        d_layerPriority(priority)
    {}

    void LayerSpecification::render(Window& srcWindow, float base_z, const ColourRect* modcols, const Rect* clipper, bool clipToDisplay) const
    {
        
        for(SectionList::const_iterator curr = d_sections.begin(); curr != d_sections.end(); ++curr)
        {
            (*curr).render(srcWindow, base_z, modcols, clipper, clipToDisplay);
        }
    }

    void LayerSpecification::render(Window& srcWindow, const Rect& baseRect, float base_z, const ColourRect* modcols, const Rect* clipper, bool clipToDisplay) const
    {
        
        for(SectionList::const_iterator curr = d_sections.begin(); curr != d_sections.end(); ++curr)
        {
            (*curr).render(srcWindow, baseRect, base_z, modcols, clipper, clipToDisplay);
        }
    }

    void LayerSpecification::addSectionSpecification(const SectionSpecification& section)
    {
        d_sections.push_back(section);
    }

    void LayerSpecification::clearSectionSpecifications()
    {
        d_sections.clear();
    }

    uint LayerSpecification::getLayerPriority() const
    {
        return d_layerPriority;
    }

    bool LayerSpecification::operator<(const LayerSpecification& other) const
    {
        return d_layerPriority < other.d_layerPriority;
    }

    void LayerSpecification::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<Layer";

        if (d_layerPriority != 0)
            out_stream << " priority=\"" << d_layerPriority << "\"";

        out_stream << ">" << std::endl;

        
        for(SectionList::const_iterator curr = d_sections.begin(); curr != d_sections.end(); ++curr)
        {
            (*curr).writeXMLToStream(out_stream);
        }

        out_stream << "</Layer>" << std::endl;
    }

} 
