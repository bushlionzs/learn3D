

#include "falagard/CEGUIFalFrameComponent.h"
#include "falagard/CEGUIFalXMLEnumHelper.h"
#include "CEGUIImage.h"
#include "CEGUIExceptions.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include <iostream>


namespace CEGUI
{
    FrameComponent::FrameComponent() :
        d_vertFormatting(VF_STRETCHED),
        d_horzFormatting(HF_STRETCHED)
    {
        for (int i = 0; i < FIC_FRAME_IMAGE_COUNT; ++i)
            d_frameImages[i] = 0;
    }

    VerticalFormatting FrameComponent::getBackgroundVerticalFormatting() const
    {
        return d_vertFormatting;
    }

    void FrameComponent::setBackgroundVerticalFormatting(VerticalFormatting fmt)
    {
        d_vertFormatting = fmt;
    }

    HorizontalFormatting FrameComponent::getBackgroundHorizontalFormatting() const
    {
        return d_horzFormatting;
    }

    void FrameComponent::setBackgroundHorizontalFormatting(HorizontalFormatting fmt)
    {
        d_horzFormatting = fmt;
    }

    const Image* FrameComponent::getImage(FrameImageComponent part) const
    {
        assert(part < FIC_FRAME_IMAGE_COUNT);

        return d_frameImages[part];
    }

    void FrameComponent::setImage(FrameImageComponent part, const Image* image)
    {
        assert(part < FIC_FRAME_IMAGE_COUNT);

        d_frameImages[part] = image;
    }

    void FrameComponent::setImage(FrameImageComponent part, const String& imageset, const String& image)
    {
        assert(part < FIC_FRAME_IMAGE_COUNT);

        try
        {
            d_frameImages[part] = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
        }
        catch (UnknownObjectException)
        {
            d_frameImages[part] = 0;
        }
    }

    void FrameComponent::render_impl(Window& srcWindow, Rect& destRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        Rect backgroundRect(destRect);
        Rect finalRect;
        Size imageSize;
        ColourRect imageColours;
        float leftfactor, rightfactor, topfactor, bottomfactor;
        bool calcColoursPerImage;

        
        float topOffset = 0, bottomOffset = 0, leftOffset = 0, rightOffset = 0;
        float topWidth, bottomWidth, leftHeight, rightHeight;
        topWidth = bottomWidth = destRect.getWidth();
        leftHeight = rightHeight = destRect.getHeight();

        
        ColourRect finalColours;
        initColoursRect(srcWindow, modColours, finalColours);

        if (finalColours.isMonochromatic())
        {
            calcColoursPerImage = false;
            imageColours = finalColours;
        }
        else
        {
            calcColoursPerImage = true;
        }

        
        if (d_frameImages[FIC_TOP_LEFT_CORNER])
        {
            
            imageSize = d_frameImages[FIC_TOP_LEFT_CORNER]->getSize();
            finalRect.d_left = destRect.d_left;
            finalRect.d_top  = destRect.d_top;
            finalRect.setSize(imageSize);

            
            topOffset  += imageSize.d_width;
            leftOffset += imageSize.d_height;
            topWidth   -= topOffset;
            leftHeight -= leftOffset;

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_TOP_LEFT_CORNER]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_TOP_LEFT_CORNER]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_TOP_LEFT_CORNER], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_TOP_RIGHT_CORNER])
        {
            
            imageSize = d_frameImages[FIC_TOP_RIGHT_CORNER]->getSize();
            finalRect.d_left = destRect.d_right - imageSize.d_width;
            finalRect.d_top  = destRect.d_top;
            finalRect.setSize(imageSize);

            
            rightOffset += imageSize.d_height;
            topWidth    -= imageSize.d_width;
            rightHeight -= rightOffset;

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_TOP_RIGHT_CORNER]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_TOP_RIGHT_CORNER]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_TOP_RIGHT_CORNER], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_BOTTOM_LEFT_CORNER])
        {
            
            imageSize = d_frameImages[FIC_BOTTOM_LEFT_CORNER]->getSize();
            finalRect.d_left = destRect.d_left;
            finalRect.d_top  = destRect.d_bottom - imageSize.d_height;
            finalRect.setSize(imageSize);

            
            bottomOffset += imageSize.d_width;
            bottomWidth  -= bottomOffset;
            leftHeight   -= imageSize.d_height;

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_BOTTOM_LEFT_CORNER]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_BOTTOM_LEFT_CORNER]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_BOTTOM_LEFT_CORNER], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_BOTTOM_RIGHT_CORNER])
        {
            
            imageSize = d_frameImages[FIC_BOTTOM_RIGHT_CORNER]->getSize();
            finalRect.d_left = destRect.d_right - imageSize.d_width;
            finalRect.d_top  = destRect.d_bottom - imageSize.d_height;
            finalRect.setSize(imageSize);

            
            bottomWidth -= imageSize.d_width;
            rightHeight -= imageSize.d_height;

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_BOTTOM_RIGHT_CORNER]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_BOTTOM_RIGHT_CORNER]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_BOTTOM_RIGHT_CORNER], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_TOP_EDGE])
        {
            
            imageSize = d_frameImages[FIC_TOP_EDGE]->getSize();
            finalRect.d_left   = destRect.d_left + topOffset;
            finalRect.d_right  = finalRect.d_left + topWidth;
            finalRect.d_top    = destRect.d_top;
            finalRect.d_bottom = finalRect.d_top + imageSize.d_height;

            
            backgroundRect.d_top += imageSize.d_height + d_frameImages[FIC_TOP_EDGE]->getOffsetY();;

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_TOP_EDGE]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_TOP_EDGE]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_TOP_EDGE], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_BOTTOM_EDGE])
        {
            
            imageSize = d_frameImages[FIC_BOTTOM_EDGE]->getSize();
            finalRect.d_left   = destRect.d_left + bottomOffset;
            finalRect.d_right  = finalRect.d_left + bottomWidth;
            finalRect.d_bottom = destRect.d_bottom;
            finalRect.d_top    = finalRect.d_bottom - imageSize.d_height;

            
            backgroundRect.d_bottom -= imageSize.d_height - d_frameImages[FIC_BOTTOM_EDGE]->getOffsetY();;

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_BOTTOM_EDGE]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_BOTTOM_EDGE]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_BOTTOM_EDGE], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_LEFT_EDGE])
        {
            
            imageSize = d_frameImages[FIC_LEFT_EDGE]->getSize();
            finalRect.d_left   = destRect.d_left;
            finalRect.d_right  = finalRect.d_left + imageSize.d_width;
            finalRect.d_top    = destRect.d_top + leftOffset;
            finalRect.d_bottom = finalRect.d_top + leftHeight;

            
            backgroundRect.d_left += imageSize.d_width + d_frameImages[FIC_LEFT_EDGE]->getOffsetX();

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_LEFT_EDGE]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_LEFT_EDGE]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_LEFT_EDGE], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        
        if (d_frameImages[FIC_RIGHT_EDGE])
        {
            
            imageSize = d_frameImages[FIC_RIGHT_EDGE]->getSize();
            finalRect.d_top    = destRect.d_top + rightOffset;
            finalRect.d_bottom = finalRect.d_top + rightHeight;
            finalRect.d_right  = destRect.d_right;
            finalRect.d_left   = finalRect.d_right - imageSize.d_width;

            
            backgroundRect.d_right -= imageSize.d_width - d_frameImages[FIC_RIGHT_EDGE]->getOffsetX();

            
            if (calcColoursPerImage)
            {
                leftfactor   = (finalRect.d_left + d_frameImages[FIC_RIGHT_EDGE]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + finalRect.getWidth() / destRect.getWidth();
                topfactor    = (finalRect.d_top + d_frameImages[FIC_RIGHT_EDGE]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + finalRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_RIGHT_EDGE], finalRect, base_z, imageColours, 0, clipToDisplay);
        }

        if (d_frameImages[FIC_BACKGROUND])
        {
            
            if (calcColoursPerImage)
            {
                leftfactor   = (backgroundRect.d_left + d_frameImages[FIC_BACKGROUND]->getOffsetX()) / destRect.getWidth();
                rightfactor  = leftfactor + backgroundRect.getWidth() / destRect.getWidth();
                topfactor    = (backgroundRect.d_top + d_frameImages[FIC_BACKGROUND]->getOffsetY()) / destRect.getHeight();
                bottomfactor = topfactor + backgroundRect.getHeight() / destRect.getHeight();

                imageColours = finalColours.getSubRectangle( leftfactor, rightfactor, topfactor, bottomfactor);
            }

            
            doBackgroundRender(srcWindow, backgroundRect, base_z, imageColours, clipper, clipToDisplay);
        }
    }

    void FrameComponent::doBackgroundRender(Window& srcWindow, Rect& destRect, float base_z, const ColourRect& colours, const Rect* clipper, bool clipToDisplay) const
    {
        HorizontalFormatting horzFormatting = d_horzFormatPropertyName.empty() ? d_horzFormatting :
            FalagardXMLHelper::stringToHorzFormat(srcWindow.getProperty(d_horzFormatPropertyName));

        VerticalFormatting vertFormatting = d_vertFormatPropertyName.empty() ? d_vertFormatting :
            FalagardXMLHelper::stringToVertFormat(srcWindow.getProperty(d_vertFormatPropertyName));

		
        int horzTiles = 0, vertTiles = 0;
        float xpos, ypos;

        Size imgSz(d_frameImages[FIC_BACKGROUND]->getSize());

        
        switch (horzFormatting)
        {
            case HF_STRETCHED:
                imgSz.d_width = destRect.getWidth();
                xpos = destRect.d_left;
                horzTiles = 1;
                break;

            case HF_TILED:
                xpos = destRect.d_left;
                horzTiles = (int)((destRect.getWidth() + (imgSz.d_width - 1)) / imgSz.d_width);
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
                throw InvalidRequestException("FrameComponent::doBackgroundRender - An unknown HorizontalFormatting value was specified.");
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
                vertTiles = (int)((destRect.getHeight() + (imgSz.d_height - 1)) / imgSz.d_height);
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
                throw InvalidRequestException("FrameComponent::doBackgroundRender - An unknown VerticalFormatting value was specified.");
        }

        
        Rect finalRect;
        Rect finalClipper;
        const Rect* clippingRect;
        finalRect.d_top = ypos;
        finalRect.d_bottom = ypos + imgSz.d_height;

        for (int row = 0; row < vertTiles; ++row)
        {
            finalRect.d_left = xpos;
            finalRect.d_right = xpos + imgSz.d_width;

            for (int col = 0; col < horzTiles; ++col)
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

                
                srcWindow.getRenderCache().cacheImage(*d_frameImages[FIC_BACKGROUND], finalRect, base_z, colours, clippingRect, clipToDisplay);

                finalRect.d_left += imgSz.d_width;
                finalRect.d_right += imgSz.d_width;
            }

            finalRect.d_top += imgSz.d_height;
            finalRect.d_bottom += imgSz.d_height;
        }
    }

    void FrameComponent::writeXMLToStream(OutStream& out_stream) const
    {
        
        out_stream << "<FrameComponent>" << std::endl;
        
        d_area.writeXMLToStream(out_stream);

        
        for (int i = 0; i < FIC_FRAME_IMAGE_COUNT; ++i)
        {
            if (d_frameImages[i])
            {
                out_stream << "<Image imageset=\"" << d_frameImages[i]->getImagesetName();
                out_stream << "\" image=\"" << d_frameImages[i]->getName();
                out_stream << "\" type=\"" << FalagardXMLHelper::frameImageComponentToString(static_cast<FrameImageComponent>(i));
                out_stream << "\" />" << std::endl;
            }
        }

        
        writeColoursXML(out_stream);

        
        if (!writeVertFormatXML(out_stream))
        {
            
            out_stream << "<VertFormat type=\"" << FalagardXMLHelper::vertFormatToString(d_vertFormatting) << "\" />" << std::endl;
        }

        
        if (!writeHorzFormatXML(out_stream))
        {
            
            out_stream << "<HorzFormat type=\"" << FalagardXMLHelper::horzFormatToString(d_horzFormatting) << "\" />" << std::endl;
        }

        
        out_stream << "</FrameComponent>" << std::endl;
    }

} 
