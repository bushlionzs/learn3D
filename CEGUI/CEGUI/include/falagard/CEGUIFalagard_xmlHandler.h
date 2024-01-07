

#ifndef _CEGUIFalagard_xmlHandler_h_
#define _CEGUIFalagard_xmlHandler_h_

#include "CEGUIXMLHandler.h"
#include "CEGUIcolour.h"
#include "falagard/CEGUIFalDimensions.h"
#include "CEGUIWindow.h"
#include <vector>


namespace CEGUI
{
    
    class WidgetLookManager;
    class WidgetLookFeel;
    class WidgetComponent;
    class ImagerySection;
    class StateImagery;
    class LayerSpecification;
    class SectionSpecification;
    class ImageryComponent;
    class ComponentArea;
    class Dimension;
    class TextComponent;
    class NamedArea;
    class FrameComponent;

    
    class Falagard_xmlHandler : public XMLHandler
    {
    public:
        
        Falagard_xmlHandler(WidgetLookManager* mgr);

        
        ~Falagard_xmlHandler();

        
        void elementStart(const String& element, const XMLAttributes& attributes);
        void elementEnd(const String& element);

    private:
        
        
        static const String FalagardElement;            
        static const String WidgetLookElement;          
        static const String ChildElement;               
        static const String ImagerySectionElement;      
        static const String StateImageryElement;        
        static const String LayerElement;               
        static const String SectionElement;             
        static const String ImageryComponentElement;    
        static const String TextComponentElement;       
        static const String FrameComponentElement;      
        static const String AreaElement;                
        static const String ImageElement;               
        static const String ColoursElement;             
        static const String VertFormatElement;          
        static const String HorzFormatElement;          
        static const String VertAlignmentElement;       
        static const String HorzAlignmentElement;       
        static const String PropertyElement;            
		static const String DimElement;                 
		static const String UnifiedDimElement;          
        static const String AbsoluteDimElement;         
        static const String ImageDimElement;            
        static const String WidgetDimElement;           
        static const String FontDimElement;             
        static const String PropertyDimElement;         
        static const String TextElement;                
        static const String ColourPropertyElement;      
        static const String ColourRectPropertyElement;  
        static const String NamedAreaElement;           
        static const String PropertyDefinitionElement;  
        static const String DimOperatorElement;         
        static const String VertFormatPropertyElement;  
        static const String HorzFormatPropertyElement;  
        static const String AreaPropertyElement;        
        static const String ImagePropertyElement;       
        
        static const String TopLeftAttribute;           
        static const String TopRightAttribute;          
        static const String BottomLeftAttribute;        
        static const String BottomRightAttribute;       
        static const String ImagesetAttribute;          
        static const String ImageAttribute;             
        static const String TypeAttribute;              
        static const String NameAttribute;              
        static const String PriorityAttribute;          
        static const String SectionNameAttribute;       
        static const String NameSuffixAttribute;        
        static const String LookAttribute;              
        static const String ScaleAttribute;             
        static const String OffsetAttribute;            
        static const String ValueAttribute;             
        static const String DimensionAttribute;         
        static const String WidgetAttribute;            
        static const String StringAttribute;            
        static const String FontAttribute;              
        static const String InitialValueAttribute;      
        static const String ClippedAttribute;           
        static const String OperatorAttribute;          
        static const String PaddingAttribute;           
        static const String LayoutOnWriteAttribute;     
        static const String RedrawOnWriteAttribute;     

        
        static argb_t hexStringToARGB(const String& str);

        
        void assignAreaDimension(Dimension& dim);

        void doBaseDimStart(const BaseDim* dim);
        void doBaseDimEnd();

        
        WidgetLookManager* d_manager;

        
        WidgetLookFeel*     d_widgetlook;
        WidgetComponent*    d_childcomponent;
        ImagerySection*     d_imagerysection;
        StateImagery*       d_stateimagery;
        LayerSpecification* d_layer;
        SectionSpecification* d_section;
        ImageryComponent*   d_imagerycomponent;
        ComponentArea*   d_area;
        Dimension       d_dimension;
        TextComponent*  d_textcomponent;
        NamedArea*      d_namedArea;
        FrameComponent*  d_framecomponent;

        std::vector<BaseDim*>    d_dimStack;
    };

} 


#endif  
