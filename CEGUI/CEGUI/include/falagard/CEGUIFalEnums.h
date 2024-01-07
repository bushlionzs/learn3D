

#ifndef _CEGUIFalEnums_h_
#define _CEGUIFalEnums_h_


namespace CEGUI
{
    
    enum DimensionType
    {
        DT_LEFT_EDGE,       
        DT_X_POSITION,      
        DT_TOP_EDGE,        
        DT_Y_POSITION,      
        DT_RIGHT_EDGE,      
        DT_BOTTOM_EDGE,     
        DT_WIDTH,           
        DT_HEIGHT,          
        DT_X_OFFSET,        
        DT_Y_OFFSET,        
        DT_INVALID          
    };

    
    enum VerticalFormatting
    {
        VF_TOP_ALIGNED,         
        VF_CENTRE_ALIGNED,      
        VF_BOTTOM_ALIGNED,      
        VF_STRETCHED,           
        VF_TILED                
    };

    
    enum HorizontalFormatting
    {
        HF_LEFT_ALIGNED,        
        HF_CENTRE_ALIGNED,      
        HF_RIGHT_ALIGNED,       
        HF_STRETCHED,           
        HF_TILED                
    };

    
    enum VerticalTextFormatting
    {
        VTF_TOP_ALIGNED,         
        VTF_CENTRE_ALIGNED,      
        VTF_BOTTOM_ALIGNED       
    };

    
    enum HorizontalTextFormatting
    {
        HTF_LEFT_ALIGNED,        
        HTF_RIGHT_ALIGNED,       
        HTF_CENTRE_ALIGNED,      
        HTF_JUSTIFIED,           
        HTF_WORDWRAP_LEFT_ALIGNED,    
        HTF_WORDWRAP_RIGHT_ALIGNED,   
        HTF_WORDWRAP_CENTRE_ALIGNED,  
        HTF_WORDWRAP_JUSTIFIED        
    };

    
    enum FontMetricType
    {
        FMT_LINE_SPACING,       
        FMT_BASELINE,           
        FMT_HORZ_EXTENT         
    };

    
    enum DimensionOperator
    {
        DOP_NOOP,       
        DOP_ADD,        
        DOP_SUBTRACT,   
        DOP_MULTIPLY,   
        DOP_DIVIDE      
    };

    
    enum FrameImageComponent
    {
        FIC_BACKGROUND,             
        FIC_TOP_LEFT_CORNER,        
        FIC_TOP_RIGHT_CORNER,       
        FIC_BOTTOM_LEFT_CORNER,     
        FIC_BOTTOM_RIGHT_CORNER,    
        FIC_LEFT_EDGE,              
        FIC_RIGHT_EDGE,             
        FIC_TOP_EDGE,               
        FIC_BOTTOM_EDGE,            
        FIC_FRAME_IMAGE_COUNT       
    };

} 


#endif  
