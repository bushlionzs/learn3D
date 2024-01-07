

#include "FalListHeaderSegmentProperties.h"
#include "FalListHeaderSegment.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
namespace FalagardListHeaderSegmentProperties
{
String SizingCursorImage::get(const PropertyReceiver* receiver) const
{
    const Image* img = static_cast<const FalagardListHeaderSegment*>(receiver)->getSizingCursorImage();
    return img ? PropertyHelper::imageToString(img) : String("");
}

void SizingCursorImage::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FalagardListHeaderSegment*>(receiver)->setSizingCursorImage(PropertyHelper::stringToImage(value));
}

String MovingCursorImage::get(const PropertyReceiver* receiver) const
{
    const Image* img = static_cast<const FalagardListHeaderSegment*>(receiver)->getMovingCursorImage();
    return img ? PropertyHelper::imageToString(img) : String("");
}

void MovingCursorImage::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FalagardListHeaderSegment*>(receiver)->setMovingCursorImage(PropertyHelper::stringToImage(value));
}

}
} 
