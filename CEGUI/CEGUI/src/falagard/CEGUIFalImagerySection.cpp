

#include "falagard/CEGUIFalImagerySection.h"
#include "CEGUIPropertyHelper.h"
#include <iostream>


namespace CEGUI
{
    ImagerySection::ImagerySection() :
        d_masterColours(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF),
        d_colourProperyIsRect(false)
    {}

    ImagerySection::ImagerySection(const String& name) :
        d_name(name),
        d_masterColours(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF),
        d_colourProperyIsRect(false)
    {}

    void ImagerySection::render(Window& srcWindow, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        
        ColourRect finalCols;
        initMasterColourRect(srcWindow, finalCols);

        if (modColours)
            finalCols *= *modColours;

        ColourRect* finalColsPtr = (finalCols.isMonochromatic() && finalCols.d_top_left.getARGB() == 0xFFFFFFFF) ? 0 : &finalCols;

        
        for(FrameList::const_iterator frame = d_frames.begin(); frame != d_frames.end(); ++frame)
        {
            (*frame).render(srcWindow, base_z, finalColsPtr, clipper, clipToDisplay);
        }
        
        for(ImageryList::const_iterator image = d_images.begin(); image != d_images.end(); ++image)
        {
            (*image).render(srcWindow, base_z, finalColsPtr, clipper, clipToDisplay);
        }
        
        for(TextList::const_iterator text = d_texts.begin(); text != d_texts.end(); ++text)
        {
            (*text).render(srcWindow, base_z, finalColsPtr, clipper, clipToDisplay);
        }
    }

    void ImagerySection::render(Window& srcWindow, const Rect& baseRect, float base_z, const CEGUI::ColourRect* modColours, const Rect* clipper, bool clipToDisplay) const
    {
        
        ColourRect finalCols;
        initMasterColourRect(srcWindow, finalCols);

        if (modColours)
            finalCols *= *modColours;

        ColourRect* finalColsPtr = (finalCols.isMonochromatic() && finalCols.d_top_left.getARGB() == 0xFFFFFFFF) ? 0 : &finalCols;

        
        for(FrameList::const_iterator frame = d_frames.begin(); frame != d_frames.end(); ++frame)
        {
            (*frame).render(srcWindow, baseRect, base_z, finalColsPtr, clipper, clipToDisplay);
        }
        
        for(ImageryList::const_iterator image = d_images.begin(); image != d_images.end(); ++image)
        {
            (*image).render(srcWindow, baseRect, base_z, finalColsPtr, clipper, clipToDisplay);
        }
        
        for(TextList::const_iterator text = d_texts.begin(); text != d_texts.end(); ++text)
        {
            (*text).render(srcWindow, baseRect, base_z, finalColsPtr, clipper, clipToDisplay);
        }
    }

    void ImagerySection::addImageryComponent(const ImageryComponent& img)
    {
        d_images.push_back(img);
    }

    void ImagerySection::clearImageryComponents()
    {
        d_images.clear();
    }

    void ImagerySection::addTextComponent(const TextComponent& text)
    {
        d_texts.push_back(text);
    }

    void ImagerySection::clearTextComponents()
    {
        d_texts.clear();
    }

    void ImagerySection::clearFrameComponents()
    {
        d_frames.clear();
    }

    void ImagerySection::addFrameComponent(const FrameComponent& frame)
    {
        d_frames.push_back(frame);
    }

    const ColourRect& ImagerySection::getMasterColours() const
    {
        return d_masterColours;
    }

    void ImagerySection::setMasterColours(const ColourRect& cols)
    {
        d_masterColours = cols;
    }

    const String& ImagerySection::getName() const
    {
        return d_name;
    }

    void ImagerySection::setMasterColoursPropertySource(const String& property)
    {
        d_colourPropertyName = property;
    }

    void ImagerySection::setMasterColoursPropertyIsColourRect(bool setting)
    {
        d_colourProperyIsRect = setting;
    }

    void ImagerySection::initMasterColourRect(const Window& wnd, ColourRect& cr) const
    {
        
        if (!d_colourPropertyName.empty())
        {
            
            if (d_colourProperyIsRect)
            {
                cr = PropertyHelper::stringToColourRect(wnd.getProperty(d_colourPropertyName));
            }
            
            else
            {
                colour val(PropertyHelper::stringToColour(wnd.getProperty(d_colourPropertyName)));
                cr.d_top_left     = val;
                cr.d_top_right    = val;
                cr.d_bottom_left  = val;
                cr.d_bottom_right = val;
            }
        }
        
        else
        {
            cr = d_masterColours;
        }
    }

    Rect ImagerySection::getBoundingRect(const Window& wnd) const
    {
        Rect compRect;
        Rect bounds(0, 0, 0, 0);

        
        for(FrameList::const_iterator frame = d_frames.begin(); frame != d_frames.end(); ++frame)
        {
            compRect = (*frame).getComponentArea().getPixelRect(wnd);

            bounds.d_left   = std::min(bounds.d_left, compRect.d_left);
            bounds.d_top    = std::min(bounds.d_top, compRect.d_top);
            bounds.d_right  = std::max(bounds.d_right, compRect.d_right);
            bounds.d_bottom = std::max(bounds.d_bottom, compRect.d_bottom);
        }
        
        for(ImageryList::const_iterator image = d_images.begin(); image != d_images.end(); ++image)
        {
            compRect = (*image).getComponentArea().getPixelRect(wnd);

            bounds.d_left   = std::min(bounds.d_left, compRect.d_left);
            bounds.d_top    = std::min(bounds.d_top, compRect.d_top);
            bounds.d_right  = std::max(bounds.d_right, compRect.d_right);
            bounds.d_bottom = std::max(bounds.d_bottom, compRect.d_bottom);
        }
        
        for(TextList::const_iterator text = d_texts.begin(); text != d_texts.end(); ++text)
        {
            compRect = (*text).getComponentArea().getPixelRect(wnd);

            bounds.d_left   = std::min(bounds.d_left, compRect.d_left);
            bounds.d_top    = std::min(bounds.d_top, compRect.d_top);
            bounds.d_right  = std::max(bounds.d_right, compRect.d_right);
            bounds.d_bottom = std::max(bounds.d_bottom, compRect.d_bottom);
        }

        return bounds;
    }

    Rect ImagerySection::getBoundingRect(const Window& wnd, const Rect& rect) const
    {
        Rect compRect;
        Rect bounds(0, 0, 0, 0);

        
        for(FrameList::const_iterator frame = d_frames.begin(); frame != d_frames.end(); ++frame)
        {
            compRect = (*frame).getComponentArea().getPixelRect(wnd, rect);

            bounds.d_left   = std::min(bounds.d_left, compRect.d_left);
            bounds.d_top    = std::min(bounds.d_top, compRect.d_top);
            bounds.d_right  = std::max(bounds.d_right, compRect.d_right);
            bounds.d_bottom = std::max(bounds.d_bottom, compRect.d_bottom);
        }
        
        for(ImageryList::const_iterator image = d_images.begin(); image != d_images.end(); ++image)
        {
            compRect = (*image).getComponentArea().getPixelRect(wnd, rect);

            bounds.d_left   = std::min(bounds.d_left, compRect.d_left);
            bounds.d_top    = std::min(bounds.d_top, compRect.d_top);
            bounds.d_right  = std::max(bounds.d_right, compRect.d_right);
            bounds.d_bottom = std::max(bounds.d_bottom, compRect.d_bottom);
        }
        
        for(TextList::const_iterator text = d_texts.begin(); text != d_texts.end(); ++text)
        {
            compRect = (*text).getComponentArea().getPixelRect(wnd, rect);

            bounds.d_left   = std::min(bounds.d_left, compRect.d_left);
            bounds.d_top    = std::min(bounds.d_top, compRect.d_top);
            bounds.d_right  = std::max(bounds.d_right, compRect.d_right);
            bounds.d_bottom = std::max(bounds.d_bottom, compRect.d_bottom);
        }

        return bounds;
    }

    void ImagerySection::writeXMLToStream(OutStream& out_stream) const
    {
        
        out_stream << "<ImagerySection name=\"" << d_name << "\">" << std::endl;

        
        if (!d_colourPropertyName.empty())
        {
            if (d_colourProperyIsRect)
                out_stream << "<ColourRectProperty ";
            else
                out_stream << "<ColourProperty ";

            out_stream << "name=\"" << d_colourPropertyName << "\" />" << std::endl;
        }
        else if (!d_masterColours.isMonochromatic() || d_masterColours.d_top_left != colour(1,1,1,1))
        {
            out_stream << "<Colours ";
            out_stream << "topLeft=\"" << PropertyHelper::colourToString(d_masterColours.d_top_left) << "\" ";
            out_stream << "topRight=\"" << PropertyHelper::colourToString(d_masterColours.d_top_right) << "\" ";
            out_stream << "bottomLeft=\"" << PropertyHelper::colourToString(d_masterColours.d_bottom_left) << "\" ";
            out_stream << "bottomRight=\"" << PropertyHelper::colourToString(d_masterColours.d_bottom_right) << "\" />" << std::endl;
        }

        
        for(FrameList::const_iterator frame = d_frames.begin(); frame != d_frames.end(); ++frame)
        {
            (*frame).writeXMLToStream(out_stream);
        }

        
        for(ImageryList::const_iterator image = d_images.begin(); image != d_images.end(); ++image)
        {
            (*image).writeXMLToStream(out_stream);
        }

        
        for(TextList::const_iterator text = d_texts.begin(); text != d_texts.end(); ++text)
        {
            (*text).writeXMLToStream(out_stream);
        }

        
        out_stream << "</ImagerySection>" << std::endl;
    }

} 
