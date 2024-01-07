

#include "CEGUIImage.h"
#include "CEGUIImageset.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIExceptions.h"

#include "elements/CEGUIPushButton.h"
#include "elements/CEGUIPushButtonProperties.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{


namespace PushButtonProperties
{
    String NormalImage::get(const PropertyReceiver* receiver) const
    {
        const RenderableImage* img = static_cast<const PushButton*>(receiver)->getNormalImage();
        return img ? PropertyHelper::imageToString(img->getImage()) : String("");
    }

    void NormalImage::set(PropertyReceiver* receiver, const String &value)
    {
        RenderableImage image;
        image.setImage(PropertyHelper::stringToImage(value));
        image.setHorzFormatting(RenderableImage::HorzStretched);
        image.setVertFormatting(RenderableImage::VertStretched);
        static_cast<PushButton*>(receiver)->setNormalImage(&image);
    }

    String PushedImage::get(const PropertyReceiver* receiver) const
    {
        const RenderableImage* img = static_cast<const PushButton*>(receiver)->getPushedImage();
        return img ? PropertyHelper::imageToString(img->getImage()) : String("");
    }

    void PushedImage::set(PropertyReceiver* receiver, const String &value)
    {
        RenderableImage image;
        image.setImage(PropertyHelper::stringToImage(value));
        image.setHorzFormatting(RenderableImage::HorzStretched);
        image.setVertFormatting(RenderableImage::VertStretched);
        static_cast<PushButton*>(receiver)->setPushedImage(&image);
    }

    String HoverImage::get(const PropertyReceiver* receiver) const
    {
        const RenderableImage* img = static_cast<const PushButton*>(receiver)->getHoverImage();
        return img ? PropertyHelper::imageToString(img->getImage()) : String("");
    }

    void HoverImage::set(PropertyReceiver* receiver, const String &value)
    {
        RenderableImage image;
        image.setImage(PropertyHelper::stringToImage(value));
        image.setHorzFormatting(RenderableImage::HorzStretched);
        image.setVertFormatting(RenderableImage::VertStretched);
        static_cast<PushButton*>(receiver)->setHoverImage(&image);
    }

    String DisabledImage::get(const PropertyReceiver* receiver) const
    {
        const RenderableImage* img = static_cast<const PushButton*>(receiver)->getDisabledImage();
        return img ? PropertyHelper::imageToString(img->getImage()) : String("");
    }

    void DisabledImage::set(PropertyReceiver* receiver, const String &value)
    {
        RenderableImage image;
        image.setImage(PropertyHelper::stringToImage(value));
        image.setHorzFormatting(RenderableImage::HorzStretched);
        image.setVertFormatting(RenderableImage::VertStretched);
        static_cast<PushButton*>(receiver)->setDisabledImage(&image);
    }

    String UseStandardImagery::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const PushButton*>(receiver)->isStandardImageryEnabled());
    }

    void UseStandardImagery::set(PropertyReceiver* receiver, const String &value)
    {
        static_cast<PushButton*>(receiver)->setStandardImageryEnabled(PropertyHelper::stringToBool(value));
    }

    String TextXOffset::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const PushButton*>(receiver)->getTextXOffset());
    }

    void TextXOffset::set(PropertyReceiver* receiver, const String &value)
    {
        static_cast<PushButton*>(receiver)->setTextXOffset(PropertyHelper::stringToFloat(value));
    }

}

}
