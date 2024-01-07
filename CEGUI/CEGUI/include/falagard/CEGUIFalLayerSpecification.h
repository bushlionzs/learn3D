

#ifndef _CEGUIFalLayerSpecification_h_
#define _CEGUIFalLayerSpecification_h_

#include "falagard/CEGUIFalSectionSpecification.h"
#include "CEGUIWindow.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class CEGUIEXPORT LayerSpecification
    {
    public:
        
        LayerSpecification(uint priority);

        
        void render(Window& srcWindow, float base_z, const ColourRect* modcols = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        void render(Window& srcWindow, const Rect& baseRect, float base_z, const ColourRect* modcols = 0, const Rect* clipper = 0, bool clipToDisplay = false) const;

        
        void addSectionSpecification(const SectionSpecification& section);

        
        void clearSectionSpecifications();

        
        uint getLayerPriority() const;

        
        bool operator<(const LayerSpecification& other) const;

        
        void writeXMLToStream(OutStream& out_stream) const;

    private:
        typedef std::vector<SectionSpecification> SectionList;

        SectionList d_sections;         
        uint        d_layerPriority;    
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
