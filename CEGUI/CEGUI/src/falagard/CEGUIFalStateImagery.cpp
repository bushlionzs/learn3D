

#include "falagard/CEGUIFalStateImagery.h"
#include "CEGUISystem.h"
#include "CEGUIRenderer.h"
#include <iostream>


namespace CEGUI
{
    StateImagery::StateImagery(const String& name) :
        d_stateName(name),
        d_clipToDisplay(false)
    {}

    void StateImagery::render(Window& srcWindow, const ColourRect* modcols, const Rect* clipper) const
    {
        float base_z;

        
        for(LayersList::const_iterator curr = d_layers.begin(); curr != d_layers.end(); ++curr)
        {
            
            base_z = -0.0000001f * static_cast<float>((*curr).getLayerPriority());
            (*curr).render(srcWindow, base_z, modcols, clipper, d_clipToDisplay);
        }
    }

    void StateImagery::render(Window& srcWindow, const Rect& baseRect, const ColourRect* modcols, const Rect* clipper) const
    {
        float base_z;

        
        for(LayersList::const_iterator curr = d_layers.begin(); curr != d_layers.end(); ++curr)
        {
            
            base_z = -0.0000001f * static_cast<float>((*curr).getLayerPriority());
            (*curr).render(srcWindow, baseRect, base_z, modcols, clipper, d_clipToDisplay);
        }
    }

    void StateImagery::addLayer(const LayerSpecification& layer)
    {
        d_layers.insert(layer);
    }

    void StateImagery::clearLayers()
    {
        d_layers.clear();
    }

    const String& StateImagery::getName() const
    {
        return d_stateName;
    }

    bool StateImagery::isClippedToDisplay() const
    {
        return d_clipToDisplay;
    }

    void StateImagery::setClippedToDisplay(bool setting)
    {
        d_clipToDisplay = setting;
    }

    void StateImagery::writeXMLToStream(OutStream& out_stream) const
    {
        out_stream << "<StateImagery name=\"" << d_stateName << "\"";

        if (d_clipToDisplay)
            out_stream << " clipped=\"false\"";

        if (d_layers.empty())
        {
            out_stream << " />" << std::endl;
        }
        else
        {
            out_stream << ">" << std::endl;

            
            for(LayersList::const_iterator curr = d_layers.begin(); curr != d_layers.end(); ++curr)
                (*curr).writeXMLToStream(out_stream);

            
            out_stream << "</StateImagery>" << std::endl;
        }
    }

} 
