

#ifndef _CEGUIFalDimensions_h_
#define _CEGUIFalDimensions_h_

#include "falagard/CEGUIFalEnums.h"
#include "CEGUIString.h"
#include "CEGUIUDim.h"


namespace CEGUI
{
     
    class CEGUIEXPORT BaseDim
    {
    public:
        BaseDim();

        virtual ~BaseDim();

        
        float getValue(const Window& wnd) const;

        
        float getValue(const Window& wnd, const Rect& container) const;

        
        BaseDim* clone() const;

        
        DimensionOperator getDimensionOperator() const;

        
        void setDimensionOperator(DimensionOperator op);

        
        const BaseDim* getOperand() const;

        
        void setOperand(const BaseDim& operand);

        
        void writeXMLToStream(OutStream& out_stream) const;

    protected:
        
        virtual float getValue_impl(const Window& wnd) const = 0;

        
        virtual float getValue_impl(const Window& wnd, const Rect& container) const = 0;

        
        virtual BaseDim* clone_impl() const = 0;

        
        virtual void writeXMLElementName_impl(OutStream& out_stream) const = 0;

        
        virtual void writeXMLElementAttributes_impl(OutStream& out_stream) const = 0;

    private:
        DimensionOperator   d_operator;
        BaseDim*            d_operand;
    };


    
    class CEGUIEXPORT AbsoluteDim : public BaseDim
    {
    public:
        
        AbsoluteDim(float val);

        
        void setValue(float val);

    protected:
        
        float getValue_impl(const Window& wnd) const;
        float getValue_impl(const Window& wnd, const Rect& container) const;
        void writeXMLElementName_impl(OutStream& out_stream) const;
        void writeXMLElementAttributes_impl(OutStream& out_stream) const;

        BaseDim* clone_impl() const;

    private:
        float d_val;    
    };


    
    class CEGUIEXPORT ImageDim : public BaseDim
    {
    public:
        
        ImageDim(const String& imageset, const String& image, DimensionType dim);

        
        void setSourceImage(const String& imageset, const String& image);

        
        void setSourceDimension(DimensionType dim);

    protected:
        
        float getValue_impl(const Window& wnd) const;
        float getValue_impl(const Window& wnd, const Rect& container) const;
        void writeXMLElementName_impl(OutStream& out_stream) const;
        void writeXMLElementAttributes_impl(OutStream& out_stream) const;
        BaseDim* clone_impl() const;

    private:
        String d_imageset;      
        String d_image;         
        DimensionType d_what;   
    };


    
    class CEGUIEXPORT WidgetDim : public BaseDim
    {
    public:
        
        WidgetDim(const String& name, DimensionType dim);

        
        void setWidgetName(const String& name);

        
        void setSourceDimension(DimensionType dim);

    protected:
        
        float getValue_impl(const Window& wnd) const;
        float getValue_impl(const Window& wnd, const Rect& container) const;
        void writeXMLElementName_impl(OutStream& out_stream) const;
        void writeXMLElementAttributes_impl(OutStream& out_stream) const;
        BaseDim* clone_impl() const;

    private:
        String d_widgetName;    
        DimensionType d_what;   
    };


    
    class CEGUIEXPORT UnifiedDim : public BaseDim
    {
    public:
        
        UnifiedDim(const UDim& value, DimensionType dim);

    protected:
        
        float getValue_impl(const Window& wnd) const;
        float getValue_impl(const Window& wnd, const Rect& container) const;
        void writeXMLElementName_impl(OutStream& out_stream) const;
        void writeXMLElementAttributes_impl(OutStream& out_stream) const;
        BaseDim* clone_impl() const;

    private:
        UDim d_value;           
        DimensionType d_what;   
    };

    
    class CEGUIEXPORT FontDim : public BaseDim
    {
    public:
        
        FontDim(const String& name, const String& font, const String& text, FontMetricType metric, float padding = 0);

    protected:
        
        float getValue_impl(const Window& wnd) const;
        float getValue_impl(const Window& wnd, const Rect& container) const;
        void writeXMLElementName_impl(OutStream& out_stream) const;
        void writeXMLElementAttributes_impl(OutStream& out_stream) const;
        BaseDim* clone_impl() const;

    private:
        String  d_font;          
        String  d_text;          
        String  d_childSuffix;   
        FontMetricType d_metric; 
        float   d_padding;       
    };

    
    class CEGUIEXPORT PropertyDim : public BaseDim
    {
    public:
        
        PropertyDim(const String& name, const String& property);

    protected:
        
        float getValue_impl(const Window& wnd) const;
        float getValue_impl(const Window& wnd, const Rect& container) const;
        void writeXMLElementName_impl(OutStream& out_stream) const;
        void writeXMLElementAttributes_impl(OutStream& out_stream) const;
        BaseDim* clone_impl() const;

    private:
        String d_property;      
        String  d_childSuffix;  
    };

    
    class CEGUIEXPORT Dimension
    {
    public:
        
        Dimension();

        
        ~Dimension();

        
        Dimension(const BaseDim& dim, DimensionType type);

        
        Dimension(const Dimension& other);

        
        Dimension& operator=(const Dimension& other);

        
        const BaseDim& getBaseDimension() const;

        
        void setBaseDimension(const BaseDim& dim);

        
        DimensionType getDimensionType() const;

        
        void setDimensionType(DimensionType type);

        
        void writeXMLToStream(OutStream& out_stream) const;

    private:
        BaseDim*        d_value;    
        DimensionType   d_type;     
    };


    
    class CEGUIEXPORT ComponentArea
    {
    public:
        
        Rect getPixelRect(const Window& wnd) const;

        
        Rect getPixelRect(const Window& wnd, const Rect& container) const;

        
        void writeXMLToStream(OutStream& out_stream) const;

        
        bool isAreaFetchedFromProperty() const;

        
        const String& getAreaPropertySource() const;

        
        void setAreaPropertySource(const String& property);


        Dimension d_left;   
        Dimension d_top;    
        Dimension d_right_or_width;     
        Dimension d_bottom_or_height;   

    private:
        String  d_areaProperty;         
    };

} 


#endif  
