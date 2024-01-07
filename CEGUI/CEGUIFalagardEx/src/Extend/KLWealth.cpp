
#include "KLWealth.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
    const utf8  KLWealth::WidgetTypeName[] = "Falagard/Wealth";

	KLWealthProperties::HorzFormatting		KLWealth::d_horzFormattingProperty;
    KLWealthProperties::MoneyNumber		KLWealth::d_moneyNumProperty;
    KLWealthProperties::GoldIcon			KLWealth::d_goldIconProperty;
    KLWealthProperties::SilverIcon			KLWealth::d_silverIconProperty;
    KLWealthProperties::CopperIcon			KLWealth::d_copperIconProperty;

    KLWealth::KLWealth(const String& type, const String& name) :
        Window(type, name),
		d_horzFormatting(LeftAligned),
		d_MoneyNum(0),
		d_imageGoldIcon(0),
		d_imageSilverIcon(0),
		d_imageCopperIcon(0)
    {
        addMoneyProperties();
    }

    KLWealth::~KLWealth()
    {
    }

	void KLWealth::initialise(void)
	{

	}

	void KLWealth::addMoneyProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLWealth )
		   CEGUI_ADD_STATICPROPERTY( &d_horzFormattingProperty );
           CEGUI_ADD_STATICPROPERTY( &d_moneyNumProperty );
           CEGUI_ADD_STATICPROPERTY( &d_goldIconProperty );
           CEGUI_ADD_STATICPROPERTY( &d_silverIconProperty );
           CEGUI_ADD_STATICPROPERTY( &d_copperIconProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	
	void KLWealth::setMoneyNumber(int moneyNumber)
    {
		d_MoneyNum = moneyNumber;
		requestRedraw();
    }

	
	void KLWealth::setHorizontalFormatting(HorzFormatting h_fmt)
	{
		d_horzFormatting = h_fmt;
		requestRedraw();
	}

	
	void KLWealth::populateRenderCache()
	{
		const int GAP_TEXT_ICON = 2;

		
		int nCopperNum	= d_MoneyNum%100;
		int nSilverNum	= (d_MoneyNum%10000)/100;
		int nGoldNum	= d_MoneyNum/10000;

		
		Rect areaTotal(0, 0, getPixelRect().getWidth(), getPixelRect().getHeight());
		Rect areaDisplay( 0,0,0,0 );
		char szMoney[32];
		const Font* pFont = getFont();
	    ColourRect final_cols(colour(1.0f, 1.0f, 1.0f));
		Size moneySize[ 3 ];

		if( nGoldNum > 0 ) 
		{
			_snprintf(szMoney, 32, "%d", nGoldNum);
			moneySize[ 0 ] = pFont->getFormattedSize((utf8*)szMoney, areaTotal, (TextFormatting)d_horzFormatting, 1 );
			areaDisplay.d_right += moneySize[ 0 ].d_width;
			areaDisplay.d_right += d_imageGoldIcon->getWidth();
			if( moneySize[ 0 ].d_height > areaDisplay.getHeight() )
				areaDisplay.d_bottom = moneySize[ 0 ].d_height;
			if( d_imageGoldIcon->getHeight() > areaDisplay.getHeight() )
				areaDisplay.d_bottom = d_imageGoldIcon->getHeight();

			areaDisplay.d_right += GAP_TEXT_ICON;
		}
		if( nGoldNum > 0 || nSilverNum > 0 ) 
		{
			_snprintf(szMoney, 32, "%d", nSilverNum);
			moneySize[ 1 ] = pFont->getFormattedSize((utf8*)szMoney, areaTotal, (TextFormatting)d_horzFormatting, 1 );
			areaDisplay.d_right += moneySize[ 1 ].d_width;
			areaDisplay.d_right += d_imageSilverIcon->getWidth();
			if( moneySize[ 1 ].d_height > areaDisplay.getHeight() )
				areaDisplay.d_bottom = moneySize[ 1 ].d_height;
			if( d_imageSilverIcon->getHeight() > areaDisplay.getHeight() )
				areaDisplay.d_bottom = d_imageSilverIcon->getHeight();

			areaDisplay.d_right += GAP_TEXT_ICON;
		}
		{
			_snprintf(szMoney, 32, "%d", nCopperNum);
			moneySize[ 2 ] = pFont->getFormattedSize((utf8*)szMoney, areaTotal, (TextFormatting)d_horzFormatting, 1 );
			areaDisplay.d_right += moneySize[ 2 ].d_width;
			areaDisplay.d_right += d_imageCopperIcon->getWidth();
			if( moneySize[ 2 ].d_height > areaDisplay.getHeight() )
				areaDisplay.d_bottom = moneySize[ 2 ].d_height;
			if( d_imageCopperIcon->getHeight() > areaDisplay.getHeight() )
				areaDisplay.d_bottom = d_imageCopperIcon->getHeight();
		}

		
		Rect rectRender(areaDisplay);
		switch( d_horzFormatting )
		{
		case KLWealth::LeftAligned:
			break;
		case KLWealth::RightAligned:
			rectRender.d_left += areaTotal.getWidth() - areaDisplay.getWidth();
			rectRender.d_right = rectRender.d_left + areaDisplay.getWidth(); 
			break;
		default:
			break;
		}
		float fLeft = rectRender.d_left;
		if(nGoldNum > 0)
		{
			_snprintf(szMoney, 32, "%d", nGoldNum);
	
			Rect areaText(fLeft, areaTotal.getHeight() - moneySize[ 0 ].d_height, fLeft + moneySize[ 0 ].d_width, areaTotal.getHeight());
			fLeft += moneySize[ 0 ].d_width;
			Rect aretIcon(fLeft, areaTotal.getHeight() - d_imageGoldIcon->getHeight(), areaText.d_right + d_imageGoldIcon->getWidth(),areaTotal.getHeight() );
			fLeft += d_imageGoldIcon->getWidth();
			d_renderCache.cacheText(this, 
				(utf8*)szMoney, pFont, (TextFormatting)RightAligned, areaText, 0.0f, final_cols);
			d_renderCache.cacheImage(*d_imageGoldIcon, aretIcon, 0.0f, final_cols);
		
			areaDisplay.d_right += GAP_TEXT_ICON;
		}
		if( nSilverNum > 0 || nGoldNum > 0 )
		{
			_snprintf(szMoney, 32, "%d", nSilverNum);
			Rect areaText(fLeft, areaTotal.getHeight() - moneySize[ 1 ].d_height, fLeft + moneySize[ 1 ].d_width, areaTotal.getHeight());
			fLeft += moneySize[ 1 ].d_width;
			Rect aretIcon(fLeft, areaTotal.getHeight() - d_imageGoldIcon->getHeight(), areaText.d_right + d_imageSilverIcon->getWidth(),areaTotal.getHeight() );
			fLeft += d_imageSilverIcon->getWidth();
			
			d_renderCache.cacheText(this, 
				(utf8*)szMoney, pFont, (TextFormatting)RightAligned, areaText, 0.0f, final_cols);
			d_renderCache.cacheImage(*d_imageSilverIcon, aretIcon, 0.0f, final_cols);
			fLeft = aretIcon.d_right;

			areaDisplay.d_right += GAP_TEXT_ICON;
		}
		{
			_snprintf(szMoney, 32, "%d", nCopperNum);
	
			Rect areaText(fLeft, areaTotal.getHeight() - moneySize[ 2 ].d_height, fLeft + moneySize[ 2 ].d_width, areaTotal.getHeight());
			fLeft += moneySize[ 2 ].d_width;
			Rect aretIcon(fLeft, areaTotal.getHeight() - d_imageGoldIcon->getHeight(), areaText.d_right + d_imageCopperIcon->getWidth(),areaTotal.getHeight() );
			fLeft += d_imageCopperIcon->getWidth();
			
			d_renderCache.cacheText(this, 
				(utf8*)szMoney, pFont, (TextFormatting)RightAligned, areaText, 0.0f, final_cols);
			d_renderCache.cacheImage(*d_imageCopperIcon, aretIcon, 0.0f, final_cols);
		}
	}
    
    Window* KLWealthFactory::createWindow(const String& name)
    {
        return new KLWealth(d_type, name);
    }

    void KLWealthFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}