

#include "FalMultiLineEditboxProperties.h"
#include "FalMultiLineEditbox.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
namespace FalagardMultiLineEditboxProperties
{
    String SelectionBrushImage::get(const PropertyReceiver* receiver) const
    {
        const Image* img = static_cast<const FalagardMultiLineEditbox*>(receiver)->getSelectionBrushImage();
        return img ? PropertyHelper::imageToString(img) : String("");
    }

    void SelectionBrushImage::set(PropertyReceiver* receiver, const String &value)
    {
        static_cast<FalagardMultiLineEditbox*>(receiver)->setSelectionBrushImage(PropertyHelper::stringToImage(value));
    }

}
} 
