

#ifndef _CEGUIFalXMLEnumHelper_h_
#define _CEGUIFalXMLEnumHelper_h_

#include "CEGUIString.h"
#include "CEGUIWindow.h"
#include "falagard/CEGUIFalEnums.h"


namespace CEGUI
{
    
    class CEGUIEXPORT FalagardXMLHelper
    {
    public:
        static VerticalFormatting stringToVertFormat(const String& str);
        static HorizontalFormatting stringToHorzFormat(const String& str);
        static VerticalAlignment stringToVertAlignment(const String& str);
        static HorizontalAlignment stringToHorzAlignment(const String& str);
        static DimensionType stringToDimensionType(const String& str);
        static VerticalTextFormatting stringToVertTextFormat(const String& str);
        static HorizontalTextFormatting stringToHorzTextFormat(const String& str);
        static FontMetricType stringToFontMetricType(const String& str);
        static DimensionOperator stringToDimensionOperator(const String& str);
        static FrameImageComponent stringToFrameImageComponent(const String& str);

        static String vertFormatToString(VerticalFormatting format);
        static String horzFormatToString(HorizontalFormatting format);
        static String vertAlignmentToString(VerticalAlignment alignment);
        static String horzAlignmentToString(HorizontalAlignment alignment);
        static String dimensionTypeToString(DimensionType dim);
        static String vertTextFormatToString(VerticalTextFormatting format);
        static String horzTextFormatToString(HorizontalTextFormatting format);
        static String fontMetricTypeToString(FontMetricType metric);
        static String dimensionOperatorToString(DimensionOperator op);
        static String frameImageComponentToString(FrameImageComponent imageComp);
    };
} 


#endif  
