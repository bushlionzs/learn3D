

#ifndef _CEGUIFalStateImagery_h_
#define _CEGUIFalStateImagery_h_

#include "falagard/CEGUIFalLayerSpecification.h"
#include "CEGUIWindow.h"
#include <set>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT StateImagery
    {
    public:
        
        StateImagery() {}

        
        StateImagery(const String& name);

        
        void render(Window& srcWindow, const ColourRect* modcols = 0, const Rect* clipper = 0) const;

        
        void render(Window& srcWindow, const Rect& baseRect, const ColourRect* modcols = 0, const Rect* clipper = 0) const;

        
        void addLayer(const LayerSpecification& layer);

        
        void clearLayers();

        
        const String& getName() const;

        
        bool isClippedToDisplay() const;

        
        void setClippedToDisplay(bool setting);

        
        void writeXMLToStream(OutStream& out_stream) const;

    private:
        typedef std::multiset<LayerSpecification> LayersList;

        CEGUI::String   d_stateName;    
        LayersList      d_layers;       
        bool            d_clipToDisplay; 
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
