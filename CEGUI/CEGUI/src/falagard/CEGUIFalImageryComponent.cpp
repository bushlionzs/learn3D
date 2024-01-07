

#include "falagard/CEGUIFalImageryComponent.h"
#include "falagard/CEGUIFalXMLEnumHelper.h"
#include "CEGUIImage.h"
#include "CEGUIExceptions.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIPropertyHelper.h"
#include <iostream>




namespace CEGUI
{
    ImageryComponent::ImageryComponent() :
        d_image(0),
        d_vertFormatting(VF_TOP_ALIGNED),
        d_horzFormatting(HF_LEFT_ALIGNED)
    {}

    const Image* ImageryComponent::getImage() const
    {
        return d_image;
    }

    void ImageryComponent::setImage(const Image* image)
    {
        d_image = image;
    }

    void ImageryComponent::setImage(const String& imageset, const String& image)
    {
        try
        {
            d_image = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
        }
        catch (UnknownObjectException)
        {
            d_image = 0;
        }
    }

    VerticalFormatting ImageryComponent::getVerticalFormatting() const
    {
        return d_vertFormatting;
    }

    void ImageryComponent::setVerticalFormatting(VerticalFormatting fmt)
    {
        d_vertFormatting = fmt;
    }

    HorizontalFormatting ImageryComponent::getHorizontalFormatting() const
    {
        return d_horzFormatting;
    }

    void ImageryComponent::setHorizontalFormatting(HorizontalFormatting fmt)
    {
        d_horzFormatting = fmt;
    }

    void ImageryComponent::render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        
        const Image* img = isImageFetchedFromProperty() ?
            PropertyHelper::stringToImage(srcWindow.getProperty(d_imagePropertyName)) :
            d_image;

        
        if (!img)
            return;

        HorizontalFormatting horzFormatting = d_horzFormatPropertyName.empty() ? d_horzFormatting :
            FalagardXMLHelper::stringToHorzFormat(srcWindow.getProperty(d_horzFormatPropertyName));

        VerticalFormatting vertFormatting = d_vertFormatPropertyName.empty() ? d_vertFormatting :
            FalagardXMLHelper::stringToVertFormat(srcWindow.getProperty(d_vertFormatPropertyName));

        uint horzTiles, vertTiles;
        float xpos, ypos;

        Size imgSz(img->getSize());

        
        ColourRect finalColours;
        initColoursRect(srcWindow, modColours, finalColours);

        
        switch (horzFormatting)
        {
            case HF_STRETCHED:
                imgSz.d_width = destRect.getWidth();
                xpos = destRect.d_left;
                horzTiles = 1;
                break;

            case HF_TILED:
                xpos = destRect.d_left;
                horzTiles = (uint)((destRect.getWidth() + (imgSz.d_width - 1)) / imgSz.d_width);
                break;

            case HF_LEFT_ALIGNED:
                xpos = destRect.d_left;
                horzTiles = 1;
                break;

            case HF_CENTRE_ALIGNED:
                xpos = destRect.d_left + PixelAligned((destRect.getWidth() - imgSz.d_width) * 0.5f);
                horzTiles = 1;
                break;

            case HF_RIGHT_ALIGNED:
                xpos = destRect.d_right - imgSz.d_width;
                horzTiles = 1;
                break;

            default:
                throw InvalidRequestException("ImageryComponent::render - An unknown HorizontalFormatting value was specified.");
        }

        
        switch (vertFormatting)
        {
            case VF_STRETCHED:
                imgSz.d_height = destRect.getHeight();
                ypos = destRect.d_top;
                vertTiles = 1;
                break;

            case VF_TILED:
                ypos = destRect.d_top;
                vertTiles = (uint)((destRect.getHeight() + (imgSz.d_height - 1)) / imgSz.d_height);
                break;

            case VF_TOP_ALIGNED:
                ypos = destRect.d_top;
                vertTiles = 1;
                break;

            case VF_CENTRE_ALIGNED:
                ypos = destRect.d_top + PixelAligned((destRect.getHeight() - imgSz.d_height) * 0.5f);
                vertTiles = 1;
                break;

            case VF_BOTTOM_ALIGNED:
                ypos = destRect.d_bottom - imgSz.d_height;
                vertTiles = 1;
                break;

            default:
                throw InvalidRequestException("ImageryComponent::render - An unknown VerticalFormatting value was specified.");
        }

        
        Rect finalRect;
        Rect finalClipper;
        const Rect* clippingRect;
        finalRect.d_top = ypos;
        finalRect.d_bottom = ypos + imgSz.d_height;

        for (uint row = 0; row < vertTiles; ++row)
        {
            finalRect.d_left = xpos;
            finalRect.d_right = xpos + imgSz.d_width;

            for (uint col = 0; col < horzTiles; ++col)
            {
                
                if (((vertFormatting == VF_TILED) && row == vertTiles - 1) ||
                    ((horzFormatting == HF_TILED) && col == horzTiles - 1))
                {
                    finalClipper = clipper ? clipper->getIntersection(destRect) : destRect;
                    clippingRect = &finalClipper;
                }
                
                else
                {
                    clippingRect = clipper;
                }

                
                srcWindow.getRenderCache().cacheImage(*img, finalRect, base_z, finalColours, clippingRect, clipToDisplay);

                finalRect.d_left += imgSz.d_width;
                finalRect.d_right += imgSz.d_width;
            }

            finalRect.d_top += imgSz.d_height;
            finalRect.d_bottom += imgSz.d_height;
        }
    }

    void ImageryComponent::writeXMLToStream(OutStream& out_stream) const
    {
        
        out_stream << "<ImageryComponent>" << std::endl;
        
        d_area.writeXMLToStream(out_stream);

        
        if (isImageFetchedFromProperty())
            out_stream << "<ImageProperty name=\"" << d_imagePropertyName << "\" />" << std::endl;
        else
            out_stream << "<Image imageset=\"" << d_image->getImagesetName() << "\" image=\"" << d_image->getName() << "\" />" << std::endl;

        
        writeColoursXML(out_stream);

        
        if (!writeVertFormatXML(out_stream))
        {
            
            out_stream << "<VertFormat type=\"" << FalagardXMLHelper::vertFormatToString(d_vertFormatting) << "\" />" << std::endl;
        }

        
        if (!writeHorzFormatXML(out_stream))
        {
            
            out_stream << "<HorzFormat type=\"" << FalagardXMLHelper::horzFormatToString(d_horzFormatting) << "\" />" << std::endl;
        }

        
        out_stream << "</ImageryComponent>" << std::endl;
    }

    bool ImageryComponent::isImageFetchedFromProperty() const
    {
        return !d_imagePropertyName.empty();
    }

    const String& ImageryComponent::getImagePropertySource() const
    {
        return d_imagePropertyName;
    }

    void ImageryComponent::setImagePropertySource(const String& property)
    {
        d_imagePropertyName = property;
    }

} 
