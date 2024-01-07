#include "KLselfAdaptationwindow.h"
#include "ceguipropertyhelper.h"
#include "CEGUIFont.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace CEGUI
{
	const utf8 KLSelfAdaptationWindow::WidgetTypeName[] = "Falagard/SelfAdaptation";
	KLSelfAdaptationProperties::FitType			KLSelfAdaptationWindow::d_FitTypeProperty;
	KLSelfAdaptationProperties::FitPosition		KLSelfAdaptationWindow::d_FitPosProperty;
	KLSelfAdaptationProperties::MaxWidth			KLSelfAdaptationWindow::d_MaxWidthProperty;
	KLSelfAdaptationProperties::Life				KLSelfAdaptationWindow::d_LifeProperty;
	KLSelfAdaptationProperties::FadeOutTime		KLSelfAdaptationWindow::d_FadeOutProperty;
	KLSelfAdaptationProperties::FadeInTime		KLSelfAdaptationWindow::d_FadeInProperty;
	KLSelfAdaptationProperties::TextFormted		KLSelfAdaptationWindow::d_TextFormatedProperty;

	KLSelfAdaptationWindow::KLSelfAdaptationWindow(const String& type, const String& name):
		KLSimpleText(type, name)
	{
		
		d_maxWidth = 2000;
		m_bFadeMode = false;
		m_nFitType = SELF_FIT_CENTER;
		m_fFadeInTime = 1;
		m_fFadeOutTime = 2;
		m_fLife = 1;
		m_changeSize = false;
#if OPTIMIZE_DAMAGE		
		m_bSingleLine = true;
#endif 
		mTextFormting = CEGUI::WordWrapLeftAligned;
		CEGUI_START_ADD_STATICPROPERTY( KLSelfAdaptationWindow )
		   CEGUI_ADD_STATICPROPERTY( &d_FitTypeProperty );
           CEGUI_ADD_STATICPROPERTY( &d_FitPosProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_MaxWidthProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_LifeProperty );
           CEGUI_ADD_STATICPROPERTY( &d_FadeOutProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_FadeInProperty );
			CEGUI_ADD_STATICPROPERTY( &d_TextFormatedProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	KLSelfAdaptationWindow::~KLSelfAdaptationWindow(void)
	{
	}

	void KLSelfAdaptationWindow::updateSelf(float elapsed)
	{
		if( m_bFadeMode && m_fCurLife < m_fMaxLife && isVisible() )
		{
			m_fCurLife += elapsed;
			if( m_fCurLife > m_fMaxLife )
			{
				hide();
				return;
			}
			if( m_fCurLife < m_fFadeInTime )  
				setAlpha( m_fCurLife / m_fFadeInTime );
			else if( m_fCurLife < m_fFadeInTime + m_fLife )
				setAlpha( 1 );
			else
				setAlpha( ( m_fMaxLife - m_fCurLife ) / m_fFadeOutTime );
			requestRedraw();
		}
	}

	//因为在窗口大小改变时,KLSelfAdaptationWindow::updateSelfSize设置
	//完正确的大小之后,WidgetComponent::layout => WindowManager::getSingleton().getWindow(owner.getName() + d_nameSuffix)->setRect(Absolute, d_area.getPixelRect(owner));
	//中d_area又再次设置了一个错误的大小!导致大小为不正确的1024x256
	//因postSizeChanged在最后执行，再次更新为正确大小
	void KLSelfAdaptationWindow::postSizeChanged(void)
	{
		Window::postSizeChanged();

		m_changeSize = true;
		updateSelfSize();
	}

	void KLSelfAdaptationWindow::updateSelfSize(void)
	{
		if(m_changeSize)
		{
			const Font* fnt = getFont();

			if (fnt && !d_text.empty())
			{
				Rect area(System::getSingleton().getRenderer()->getRect());
				if(area.getWidth() > (float)d_maxWidth) area.d_right = area.d_left + d_maxWidth;

	            
				Size sz = fnt->getFormattedSize(d_text, area, mTextFormting, d_fScaleX, d_fScaleY, m_bSingleLine); 
				sz.d_height += 2; 
				sz.d_width += 2;

				setSize(Absolute, sz);
			}
			else
			{
				setSize(Absolute, Size(0,0));
			}
			requestRedraw();

			m_changeSize = false;
		}
	}

	
	void KLSelfAdaptationWindow::updateSelfPosition()
	{
		//updateSelfSize(); //此处频繁调用耗时严重，去除!

		CEGUI::Point pos = m_ptCenter;
		switch( m_nFitType )
		{
		case SELF_FIT_LEFT:
			pos.d_y -= getAbsoluteHeight()/2.f;
			break;
		case SELF_FIT_RIGHT:
			pos.d_x -= getAbsoluteWidth();
			pos.d_y -= getAbsoluteHeight()/2;
			break;
		case SELF_FIT_TOP:
			pos.d_x -= getAbsoluteWidth() / 2;
			break;
		case SELF_FIT_BOTTOM:
			pos.d_x -= getAbsoluteWidth() / 2;
			pos.d_y -= getAbsoluteHeight();
			break;
		case SELF_FIT_LEFTTOP:
			break;
		case SELF_FIT_LEFTBOTTOM:
			pos.d_y -= getAbsoluteHeight();
			break;
		case SELF_FIT_RIGHTTOP:
			pos.d_x -= getAbsoluteWidth();
			break;
		case SELF_FIT_RIGHTBOTOM:
			pos.d_x -= getAbsoluteWidth();
			pos.d_y -= getAbsoluteHeight();
			break;
		case SELF_FIT_CENTER:
			pos.d_x -= getAbsoluteWidth() / 2;
			pos.d_y -= getAbsoluteHeight() / 2;
			break;
		default:
			break;
		}

		static UVector2 position;
		position.d_x = cegui_absdim(PixelAligned(pos.d_x));
		position.d_y = cegui_absdim(PixelAligned(pos.d_y));
		d_area.setPosition(position);

/*
		char buffer[MAX_PATH];
		sprintf(buffer, "SelfAdaptationWindow[0x%X]: updateSelfPosition, Position: %.2f, %.2f, Size: %.2f, %.2f\n", 
			(unsigned int)this, 
			pos.d_x, pos.d_y, 
			getAbsoluteWidth(),	getAbsoluteHeight()
			);
		::OutputDebugString(buffer);
	*/
	}

	void KLSelfAdaptationWindow::setCenter( const Point& pos )
	{
		//center相同,不代表ui位置没有改变,ui以左上角位置为准.
		//if( m_ptCenter == pos )
		//	return;

		m_ptCenter = pos;
		updateSelfPosition();

/*
		char buffer[MAX_PATH];
		sprintf(buffer, "SelfAdaptationWindow[0x%X]: setCenter, Size:%.2f, %.2f\n", 
			(unsigned int)this,
			getAbsoluteWidth(),
			getAbsoluteHeight()
			);
		::OutputDebugString(buffer);*/
	}

	void KLSelfAdaptationWindow::onParentSized(WindowEventArgs& e)
	{
		KLSimpleText::onParentSized(e);

		m_changeSize = true;
		updateSelfSize();
/*
		char buffer[MAX_PATH];
		sprintf(buffer, "SelfAdaptationWindow[0x%X]: onParentSized, Size:%.2f, %.2f\n", 
			(unsigned int)this,
			getAbsoluteWidth(),
			getAbsoluteHeight()
			);
		::OutputDebugString(buffer);*/
	}
	
	void KLSelfAdaptationWindow::setText( const String& text )
	{
		m_changeSize = true;
		Window::setText(text);
		
#if OPTIMIZE_DAMAGE
		if(String::npos == d_text.find_first_of('\n', 0))
			m_bSingleLine = true;
		else
			m_bSingleLine = false;
#endif

		//m_ptCenter = Point(0, 0);
		updateSelfSize();
		m_fCurLife = 0;
		m_fMaxLife = m_fLife + m_fFadeInTime + m_fFadeOutTime;
		if( text.empty() )
			hide();
	}

	namespace KLSelfAdaptationProperties
	{
		
		String	MaxWidth::get(const PropertyReceiver* receiver) const
		{
			return PropertyHelper::intToString(static_cast<const KLSelfAdaptationWindow*>(receiver)->getMaxWidth());
		}
		void MaxWidth::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSelfAdaptationWindow*>(receiver)->setMaxWidth( PropertyHelper::stringToInt( value ) );
		}

		
		String	FitType::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	FitType::set(PropertyReceiver* receiver, const String& value)
		{
			int nType = 0;
			if( value == (utf8*)"Center" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_CENTER;
			}
			else if( value == (utf8*)"Left" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_LEFT;
			}
			else if( value == (utf8*)"Right" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_RIGHT;
			}
			else if( value == (utf8*)"Top" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_TOP;
			}
			else if( value == (utf8*)"Bottom" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_BOTTOM;
			}
			else if( value == (utf8*)"LeftTop" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_LEFTTOP;
			}
			else if( value == (utf8*)"RightBottm" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_RIGHTBOTOM;
			}
			else if( value == (utf8*)"LeftBottom" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_LEFTBOTTOM;
			}
			else if( value == (utf8*)"RightTop" )
			{
				nType = KLSelfAdaptationWindow::SELF_FIT_RIGHTBOTOM;
			}

			static_cast<KLSelfAdaptationWindow*>(receiver)->setFitType( nType );
		}

		
			
		String	FitPosition::get(const PropertyReceiver* receiver) const
		{
			Point nPos = static_cast<const KLSelfAdaptationWindow*>(receiver)->getCenter();
			return PropertyHelper::pointToString( nPos );
		}
		void	FitPosition::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSelfAdaptationWindow*>(receiver)->setCenter( PropertyHelper::stringToPoint( value ) );
		}



		String	Life::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	Life::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSelfAdaptationWindow*>(receiver)->setLife( PropertyHelper::stringToFloat( value ) );
		}



		String	FadeInTime::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	FadeInTime::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSelfAdaptationWindow*>(receiver)->setFadeInTime( PropertyHelper::stringToFloat( value ) );
		}



		String	FadeOutTime::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	FadeOutTime::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSelfAdaptationWindow*>(receiver)->setFadeOutTime( PropertyHelper::stringToFloat( value ) );
		}

		String	TextFormted::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	TextFormted::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSelfAdaptationWindow*>(receiver)->setTextFormated( CEGUI::LeftAligned );
		}
	}

	 
    
    Window* KLSelfAdaptationWindowFactory::createWindow(const String& name)
    {
        return new KLSelfAdaptationWindow(d_type, name);
    }

    void KLSelfAdaptationWindowFactory::destroyWindow(Window* window)
    {
		delete window;
    }
};