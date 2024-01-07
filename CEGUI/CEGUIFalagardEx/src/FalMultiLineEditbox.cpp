

#include "FalMultiLineEditbox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"


namespace CEGUI
{
    const utf8 FalagardMultiLineEditbox::WidgetTypeName[] = "Falagard/MultiLineEditbox";
    FalagardMultiLineEditboxProperties::SelectionBrushImage FalagardMultiLineEditbox::d_selectionBrushProperty;


    FalagardMultiLineEditbox::FalagardMultiLineEditbox(const String& type, const String& name) :
        MultiLineEditbox(type, name)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardMultiLineEditbox )
		   CEGUI_ADD_STATICPROPERTY( &d_selectionBrushProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardMultiLineEditbox::~FalagardMultiLineEditbox()
    {
    }

    Rect FalagardMultiLineEditbox::getTextRenderArea(void) const
    {
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
		bool v_visible = false;
		if( d_vertScrollbar )
			v_visible = d_vertScrollbar->isVisible(true);
        bool h_visible = false;
		if( d_horzScrollbar )
			h_visible = d_horzScrollbar->isVisible(true);
        
        if (v_visible || h_visible)
        {
            String area_name("TextArea");

            if (h_visible)
            {
                area_name += "H";
            }
            if (v_visible)
            {
                area_name += "V";
            }
            area_name += "Scroll";

            if (wlf.isNamedAreaDefined(area_name))
            {
                return wlf.getNamedArea(area_name).getArea().getPixelRect(*this);
            }
        }

        
        return wlf.getNamedArea("TextArea").getArea().getPixelRect(*this);
    }

    Scrollbar* FalagardMultiLineEditbox::createVertScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardMultiLineEditbox::createHorzScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardMultiLineEditbox::cacheEditboxBaseImagery()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : (isReadOnly() ? "ReadOnly" : "Enabled"));
        
        imagery->render(*this);
    }

    void FalagardMultiLineEditbox::cacheCaratImagery(const Rect& textArea)
    {
        const Font* fnt = getFont();

        
		if ( fnt  )
        {
            
            size_t caratLine = getLineNumberFromIndex(d_caratPos);

            
            if (caratLine < d_lines.size())
            {
                
                size_t caratLineIdx = d_caratPos - d_lines[caratLine].d_startIdx;
                float ypos = caratLine * fnt->getLineSpacing();
                float xpos = fnt->getTextExtent(d_text.substr(d_lines[caratLine].d_startIdx, caratLineIdx));

                
                Renderer* renderer = System::getSingleton().getRenderer();
                float baseZ = renderer->getZLayer(7) - renderer->getCurrentZ();

                
                const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
                
                const ImagerySection& caratImagery = wlf.getImagerySection("Carat");

                
                Rect caratArea;
                caratArea.d_left    = textArea.d_left + xpos;
                caratArea.d_top     = textArea.d_top + ypos;
                caratArea.setWidth(caratImagery.getBoundingRect(*this).getSize().d_width);
                caratArea.setHeight(fnt->getLineSpacing());
				float fHPosition = 0;
				if( d_horzScrollbar )
					fHPosition = d_horzScrollbar->getScrollPosition();
				float fVPosition = 0;
				if( d_vertScrollbar )
					fVPosition = d_vertScrollbar->getScrollPosition();
                caratArea.offset( Point(-fHPosition, -fVPosition ));

                
				
				
				Rect newTextArea(textArea);
				newTextArea.d_right += caratImagery.getBoundingRect(*this).getSize().d_width;
                caratImagery.render(*this, caratArea, baseZ, 0, &newTextArea);
            }
        }
    }

    const Image* FalagardMultiLineEditbox::getSelectionBrushImage() const
    {
        return d_selectionBrush;
    }

    void FalagardMultiLineEditbox::setSelectionBrushImage(const Image* image)
    {
        d_selectionBrush = image;
        requestRedraw();
    }

    
    
    
    Window* FalagardMultiLineEditboxFactory::createWindow(const String& name)
    {
        return new FalagardMultiLineEditbox(d_type, name);
    }

    void FalagardMultiLineEditboxFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
