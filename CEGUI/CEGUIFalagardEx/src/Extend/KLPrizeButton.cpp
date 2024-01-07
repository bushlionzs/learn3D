#include "KLPrizeButton.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"



namespace CEGUI
{
	const utf8 KLPrizeButton::WidgetTypeName[] = "Falagard/PrizeButton";

    KLPrizeButton::KLPrizeButton(const String& type, const String& name) :
        FalagardButton(type, name)
		, d_Checked(false)
		, d_Masked(false),
		d_CornerChar("")
    {
    }

    KLPrizeButton::~KLPrizeButton()
    {
    }

	void KLPrizeButton::initialise(void)
	{
		performWindowLayout();
	}

	void KLPrizeButton::drawSelf( float z )
	{
		if (d_needsRedraw  )
		{
			d_renderCache.clearCachedImagery();
			d_needsRedraw = false;

			drawNormal(z);

			if( isMasked() )
				drawDisabled(z);

			drawCorner(z);
		}

		if (isChecked()) 
		{
			drawPushed(z);
			drawCorner(z);
		}

		Window::drawSelf(z);
	}

	void KLPrizeButton::drawCorner(float z)
	{
		
		if( !d_CornerChar.empty() )
		{
			ColourRect final_cols(colour(1.0f, 1.0f, 1.0f));

			
			float fFontHeight = getFont()->getFontHeight();
			d_renderCache.cacheText(this, d_CornerChar, getFont(), (TextFormatting)RightAligned, 
				Rect(0, getAbsoluteSize().d_height-fFontHeight-2, getAbsoluteSize().d_width-2, getAbsoluteSize().d_height), 0.0f, final_cols);
		}
	}

	
	void KLPrizeButton::onSized(WindowEventArgs& e)
	{
		FalagardButton::onSized(e);

		performWindowLayout();
		requestRedraw();
	}

	void KLPrizeButton::performWindowLayout(void)
	{
	}
   
    
    Window* KLPrizeButtonWindowFactory::createWindow(const String& name)
    {
        return new KLPrizeButton(d_type, name);
    }

    void KLPrizeButtonWindowFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}