#include "KLKeyImageAnimation.h"
#include "CEGUIKeyImageAnimation.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "ogreroot.h"
#include "ogretimer.h"
namespace CEGUI
{
	const utf8 KLKeyImageAnimation::WidgetTypeName[] = "Falagard/KeyImageAnimation";
	KLKeyImageAnimationProperties::FalKeyImageAnimation KLKeyImageAnimation::d_AnimateNameProperty;

	KLKeyImageAnimation::KLKeyImageAnimation(const String& type, const String& name) :
        FalagardButton(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLKeyImageAnimation )
		   CEGUI_ADD_STATICPROPERTY( &d_AnimateNameProperty  );
		CEGUI_END_ADD_STATICPROPERTY

		m_pAnimate = 0;
		m_bPlay = true;
		d_normalImage.setHorzFormatting( RenderableImage::HorzStretched );
		d_normalImage.setVertFormatting( RenderableImage::VertStretched );
	}

	KLKeyImageAnimation::~KLKeyImageAnimation(void)
	{
	}
	void KLKeyImageAnimation::SetAnimate( const String& strAnimate )
	{
		if(KeyImageAnimationManager::getSingleton().isAnimatePresent(strAnimate))
		{
			m_pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( strAnimate );
			m_nAnimateStart = int( System::getSingleton().getCurTimeElapsed() * 1000.0f );
		}
	}
	void KLKeyImageAnimation::drawNormal(float z)
	{
		if( m_bPlay )
		{
			ColourRect colours(d_normalImage.getColours());
			colours.setAlpha(getEffectiveAlpha() * m_fAlpha );
			d_normalImage.setColours(colours);
			d_normalImage.draw(d_renderCache);
		}
	}
	void	KLKeyImageAnimation::drawSelf(float z)
	{
		if( d_needsRedraw )
		{
			d_renderCache.clearCachedImagery();
			d_needsRedraw = false;
			
			drawNormal( z );
			if (isDisabled(true) )
			{
				drawDisabled(z);
			}
			else
			{
				
				if (isPushed() ) 
				{
					drawPushed(z);
				}
				
				if (isHovering() )
				{
					drawHover(z);
				}
			}
		}
		Window::drawSelf(z);
	}
	void	KLKeyImageAnimation::Play( bool bPlay )
	{
		m_bPlay = bPlay;
		m_nAnimateStart = int( System::getSingleton().getCurTimeElapsed() * 1000.0f );
	}

	size_t   KLKeyImageAnimation::getFrameNumber()
	{
		if( m_pAnimate  )
		{
			m_pAnimate->getFrameNumber();
		}
		return 0;
	}

	String KLKeyImageAnimation::getFrameName(const size_t& index)
	{
		if(m_pAnimate)
		{
			return m_pAnimate->getFrame( (int)index )->getName();
		}
		return "";
	}

	void	KLKeyImageAnimation::updateSelf(float elapsed)
	{
		
		if( m_pAnimate  )
		{
			if( m_bPlay )
			{
				int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);
				const Image* pFrame = m_pAnimate->getFrame( time_now - m_nAnimateStart, -1 );				
				m_fAlpha = m_pAnimate->getFrameAlpha( time_now - m_nAnimateStart, -1 );
				d_normalImage.setImage( pFrame ) ;
				if (!pFrame)
				{
					d_realTimeUpdate = false;
					hide();
				}
			}
			else
			{
				d_normalImage.setImage( NULL ) ;
				d_realTimeUpdate = false;
				hide();
			}
			
			requestRedraw();
		}
		
	}

	void KLKeyImageAnimation::onMouseMove(MouseEventArgs& e)
	{
		
		Window::onMouseMove(e);
	}

    
    
    
    Window* KLAnimateFactory::createWindow(const String& name)
    {
        return new KLKeyImageAnimation(d_type, name);
    }

    void KLAnimateFactory::destroyWindow(Window* window)
    {

            delete window;
    }
}