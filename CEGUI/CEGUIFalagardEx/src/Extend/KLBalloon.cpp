
#include "KLBalloon.h"
#include "ceguipropertyhelper.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
namespace CEGUI
{
	const utf8 KLBalloon::WidgetTypeName[] = "Falagard/Balloon";

	KLBalloonProperties::ArrowImage  KLBalloon::d_ArrowProperty;
	KLBalloon::KLBalloon(const String& type, const String& name):
		KLSelfAdaptationWindow(type, name),
		d_needUpdateSize(true) 
	{
		CEGUI_START_ADD_STATICPROPERTY( KLBalloon )
		   CEGUI_ADD_STATICPROPERTY( &d_ArrowProperty );

		CEGUI_END_ADD_STATICPROPERTY
		setAlpha( 0 );
	}

	KLBalloon::~KLBalloon(void)
	{
	}

	void KLBalloon::populateRenderCache()
	{
		const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        const StateImagery* imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
		if( d_ArrowImage.getImage() )
		{
			colour col( 1,1,1, getAlpha() );
			d_ArrowImage.setColours( col );
			d_ArrowImage.draw(d_renderCache);
		}
	}

	void KLBalloon::updateSelfSize()
	{
		if(d_needUpdateSize || m_changeSize) 
		{
			KLSelfAdaptationWindow::updateSelfSize();

			const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
			if( wlf.isNamedAreaDefined( "TextArea" ) )
			{
				const Rect rectBorder(wlf.getNamedArea("TextArea").getArea().getPixelRect(*this));
				Rect wndArea(getAbsoluteRect());
				Size size(getAbsoluteSize());

				size.d_width  += wndArea.getWidth() - rectBorder.getWidth();
				size.d_height += wndArea.getHeight() - rectBorder.getHeight();

				setSize(Absolute, size);
			}

			if( d_ArrowImage.getImage() )
			{
				Size size = d_ArrowImage.getImage()->getSize();
				Rect area( getAbsoluteWidth() / 2 - size.d_width / 2, getAbsoluteHeight() - size.d_height - 2, getAbsoluteWidth() / 2 + size.d_width / 2, getAbsoluteHeight() -1 );
				d_ArrowImage.setRect( area );
			}

			d_needUpdateSize = false;
		}
	}
	void KLBalloon::setArrowImage( const Image* image )
	{
		d_ArrowImage.setImage( image );
		d_ArrowImage.setHorzFormatting( RenderableImage::HorzStretched );
		d_ArrowImage.setVertFormatting( RenderableImage::VertStretched );
	}

	
	void KLBalloon::setText( const String& text )
	{
		d_needUpdateSize = true;
		KLSelfAdaptationWindow::setText( text );
	}

	namespace KLBalloonProperties
	{
		String	ArrowImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}


		void	ArrowImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLBalloon*>( receiver )->setArrowImage( PropertyHelper::stringToImage( value ) );
		}
	}
	 
    
    Window* KLBalloonFactory::createWindow(const String& name)
    {
        return new KLBalloon(d_type, name);
    }

    void KLBalloonFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}