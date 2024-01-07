#include "KLcheckbutton.h"
#include "ceguicolourrect.h"
#include "CEGUIPropertyHelper.h"
namespace CEGUI
{
	const utf8  KLCheckButton::WidgetTypeName[] = "Falagard/CheckBox";

    KLCheckButtonProperties::SelectImage KLCheckButton::d_selectImageProperty;
	KLCheckButtonProperties::Selected KLCheckButton::d_selectedProperty;
	KLCheckButtonProperties::CheckMode KLCheckButton::d_checkModeProperty;
	KLCheckButton::KLCheckButton( const String& type, const String& name ):
		FalagardButton(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLCheckButton )
		   CEGUI_ADD_STATICPROPERTY( &d_selectImageProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_selectedProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_checkModeProperty  );
		CEGUI_END_ADD_STATICPROPERTY

		d_nCheckMode = 0;
	}

	KLCheckButton::~KLCheckButton(void)
	{
	}
	void	KLCheckButton::drawSelf(float z)
	{
		if( d_needsRedraw )
		{
			if( isCheck() && !isPushed())
			{
				d_renderCache.clearCachedImagery();
            
				d_needsRedraw = false;
				drawPushed( z );
			}
			else
				return FalagardButton::drawSelf( z );
		}
		Window::drawSelf(z);
	}
	void KLCheckButton::drawCheck()
	{
        ColourRect colours(d_selectImage.getColours());
        colours.setAlpha(getEffectiveAlpha());
        d_selectImage.setColours(colours);
        d_selectImage.draw(d_renderCache);
	}
	void	KLCheckButton::setSelectImage(const RenderableImage* image)
	{
		if (image)
		{
			d_selectImage = *image;
			d_selectImage.setRect(Rect(0, 0, getAbsoluteWidth(), getAbsoluteHeight()));
		}
		requestRedraw();
	}
	void KLCheckButton::setCustomImageryAutoSized(bool setting)
	{
		
		if (setting && setting != d_autoscaleImages)
		{
			Rect area(0, 0, getAbsoluteWidth(), getAbsoluteHeight());
			d_selectImage.setRect(area);
			requestRedraw();
		}

		PushButton::setCustomImageryAutoSized( setting );
	}
	void	KLCheckButton::onMouseButtonDown(MouseEventArgs& e)
	{
		PushButton::onMouseButtonDown(e);

		if (e.button == LeftButton)
		{
			e.handled = true;
		}
	}
	void	KLCheckButton::setCheck( bool bCheck )
	{
		d_bIsSelected = bCheck;
		if( d_nCheckMode == 1 && bCheck ) 
		{
			if( d_bIsSelected )
			{
				Window* pParent = getParent();
				uint child_count = pParent->getChildCount();
				for (uint i = 0; i < child_count; ++i)
				{
					Window* pChildWindow = pParent->getChildAtIdx( i );
					if(!(pChildWindow->testClassName("KLCheckButton"))) continue;

					KLCheckButton* pButton = (KLCheckButton*)pChildWindow;

					if(pButton != this )
						pButton->setCheck( false );
				}
			}
		}
		requestRedraw();
	}
	void KLCheckButton::setCheckMode( int nMode )
	{
		d_nCheckMode = nMode;
	}
	const int KLCheckButton::getCheckMode() const
	{
		return d_nCheckMode;
	}
	void	KLCheckButton::onMouseButtonUp(MouseEventArgs& e)
	{
		if( d_pushed && (!d_bIsSelected || d_nCheckMode == 0 ) && this == System::getSingleton().getGUISheet()->getChildAtPosition(e.position) )
			d_bIsSelected = !d_bIsSelected;

		FalagardButton::onMouseButtonUp(e);

		if( !d_pushed )
			return;

		if( d_nCheckMode == 1 ) 
		{
			if( d_bIsSelected )
			{
				Window* pParent = getParent();
				uint child_count = pParent->getChildCount();
				for (uint i = 0; i < child_count; ++i)
				{
					Window* pChildWindow = pParent->getChildAtIdx( i );
					if(!(pChildWindow->testClassName("KLCheckButton"))) continue;

					KLCheckButton* pButton = (KLCheckButton*)pChildWindow;

					if(pButton != this)
						pButton->setCheck( false );
				}
			}
		}

	}

	
    
    
    Window* KLCheckButtonFactory::createWindow(const String& name)
    {
        return new KLCheckButton(d_type, name);
    }

    void KLCheckButtonFactory::destroyWindow(Window* window)
    {
		delete window;
    }

	
    
    
	namespace KLCheckButtonProperties
	{
		String SelectImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void SelectImage::set(PropertyReceiver* receiver, const String& value)
		{
			RenderableImage image;
			image.setImage(PropertyHelper::stringToImage(value));
			image.setHorzFormatting(RenderableImage::HorzStretched);
			image.setVertFormatting(RenderableImage::VertStretched);
			static_cast<KLCheckButton*>(receiver)->setSelectImage(&image);
		}
		String Selected::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::boolToString(static_cast<const KLCheckButton*>(receiver)->isCheck());
		}

		void Selected::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLCheckButton*>(receiver)->setCheck(PropertyHelper::stringToBool(value));
		}

		
		
		
		String CheckMode::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::intToString(static_cast<const KLCheckButton*>(receiver)->getCheckMode());
		}

		void CheckMode::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLCheckButton*>(receiver)->setCheckMode(PropertyHelper::stringToInt(value));
		}
	}
};