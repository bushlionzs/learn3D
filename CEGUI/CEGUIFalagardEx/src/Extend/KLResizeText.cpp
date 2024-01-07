#include "KLresizetext.h"
#include "ceguiwindowmanager.h"
#include "CEGUIFont.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
namespace CEGUI
{

	const utf8  KLResizeText::WidgetTypeName[] = "Falagard/ResizeText";


	KLResizeTextProperties::AimWindow     KLResizeText::d_AimWindowPropety;
	KLResizeTextProperties::AimPosition   KLResizeText::d_AimPositionPropety;


	KLResizeText::KLResizeText( const String& type, const String& name ):
		FalagardStaticText(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLResizeText )
		   CEGUI_ADD_STATICPROPERTY( &d_AimWindowPropety  );
		   CEGUI_ADD_STATICPROPERTY( &d_AimPositionPropety  );
		CEGUI_END_ADD_STATICPROPERTY
	}

	KLResizeText::~KLResizeText(void)
	{
	}

	void KLResizeText::SetAimWindow( const String& strWindowName )
	{
		m_pAimWindow = WindowManager::getSingleton().getWindow( strWindowName );
	}
	void KLResizeText::SetAimPosition( const String& strPositionName )
	{
		char szAim[ 128 ];
		char szSelf[ 128 ];
		char szLock[ 128 ];
		sscanf( strPositionName.c_str(),  "Aim:%s Self:%s Lock:%s", szAim, szSelf, szLock  ); 
		if( strcmp( szAim, "LeftTop" ) == 0 )
		{
			m_nAimPositionType = LeftTop;
		}
		else if( strcmp( szAim,"RightTop" )== 0 )
		{
			m_nAimPositionType = RightTop;
		}
		else if( strcmp( szAim, "RightBottom" ) == 0 )
		{
			m_nAimPositionType = RightBottom;
		}
		else if( strcmp( szAim,"LeftBottom" ) == 0)
		{
			m_nAimPositionType = LeftBottom;
		}
		else
			m_nAimPositionType = InvalidPosition;


		if( strcmp( szSelf, "LeftTop" ) == 0 )
		{
			m_nSelfPositionType = LeftTop;
		}
		else if( strcmp( szSelf, "RightTop" ) == 0 )
		{
			m_nSelfPositionType = RightTop;
		}
		else if( strcmp( szSelf, "RightBottom" ) == 0 )
		{
			m_nSelfPositionType = RightBottom;
		}
		else if( strcmp( szSelf, "LeftBottom" ) == 0)
		{
			m_nSelfPositionType = LeftBottom;
		}
		else 
			m_nSelfPositionType = InvalidPosition;


		if( strcmp( szLock, "Width" ) )
			m_nLockType = LockWidth;
		else if( strcmp( szLock, "Height" ) )
			m_nLockType = LockHeight;
	}
	void KLResizeText::positionSelf()
	{
		Point pos;
		if( m_pAimWindow ) 
		{
			Size sz = getAbsoluteSize();
			Size szAim = m_pAimWindow->getAbsoluteSize();
			pos = m_pAimWindow->getAbsolutePosition();
			switch( m_nAimPositionType )
			{
			case LeftTop:
				{
					
					switch( m_nSelfPositionType )
					{
					case LeftTop: 
						break;
					case RightTop: 
						pos.d_x -= sz.d_width;
						break;
					case RightBottom: 
						pos.d_x -= sz.d_width;
						pos.d_y -= sz.d_height;
						break;
					case LeftBottom: 
						pos.d_y -= sz.d_height;
						break;
					default:
						break;
					}
				}
				break;
			case RightTop:
				{
					switch( m_nSelfPositionType )
					{
					case LeftTop: 
						pos.d_x += sz.d_width;
						break;
					case RightTop: 
						break;
					case RightBottom:
						pos.d_y -= sz.d_height;
						pos.d_x += szAim.d_width - sz.d_width;
						break;
					case LeftBottom: 
						pos.d_x += szAim.d_width;
						pos.d_y -= sz.d_height;
						break;
					default:
						break;
					}
				}
				break;
			case RightBottom:
				{
					Size sz = m_pAimWindow->getAbsoluteSize();
					switch( m_nSelfPositionType )
					{
					case LeftTop: 
						pos.d_x += sz.d_width;
						pos.d_y += sz.d_height;
						break;
					case RightTop:
						pos.d_x += szAim.d_width - sz.d_width;
						pos.d_y += szAim.d_height;
						break;
					case RightBottom: 
						break;
					case LeftBottom: 
						pos.d_x += szAim.d_width;
						pos.d_y += szAim.d_height - sz.d_height;
						break;
					default:
						break;
					}
				}
				break;
			case LeftBottom:
				{
					switch( m_nSelfPositionType )
					{
					case LeftTop: 
						pos.d_y += szAim.d_height; 
						break;
					case RightTop: 
						pos.d_x -= sz.d_width;
						pos.d_y += szAim.d_height;
						break;
					case RightBottom: 
						pos.d_x -= sz.d_width;
						pos.d_y += szAim.d_height - sz.d_height;
						break;
					case LeftBottom: 
						break;
					default:
						break;
					}
				}
				break;
			}
			
		} 
		else 
		{
			Size sz = getAbsoluteSize();
			Size szParent = getParentSize();
			pos = getParent()->getAbsolutePosition();
			switch( m_nSelfPositionType )
			{
				case LeftTop: 
					break;
				case RightTop: 
					pos.d_x += szParent.d_width - sz.d_width;
					break;
				case RightBottom: 
					pos.d_x += szParent.d_width - sz.d_width;
					pos.d_y += szParent.d_height - sz.d_height; 
					break;
				case LeftBottom: 
					pos.d_y += szParent.d_height - sz.d_height; 
					break;
				default:
					break;
			}
		}
		setPosition( Absolute, pos );
	}
	void KLResizeText::onTextChanged( WindowEventArgs& e )
	{
		
		
	}
	
	void KLResizeText::onSized( WindowEventArgs& e )
	{
		
		
	}
	void	KLResizeText::ResizeWindow()
	{
		setHeight( Absolute, getTextHeight() );
		d_frame.setSize(getAbsoluteSize());
		requestRedraw();
		
	}
	float KLResizeText::getTextHeight() const
	{
		const Font* fnt = getFont();
		Size sz;
        if (fnt)
        {
            Rect area = getAbsoluteRect();
			float height = fnt->getFormattedSize(d_text, area, CEGUI::WordWrapCentred).d_height;
			return height;
		}
		return 0;

	}
	Size KLResizeText::getTextSize() const 
	{
		const Font* fnt = getFont();
		Size sz;
		

  
  
        if (fnt)
        {
            Rect area = getAbsoluteRect();
			 
            
			float height = fnt->getFormattedSize(d_text, area, CEGUI::WordWrapCentred).d_height;
			

			sz =  Size(area.getWidth(), height);
        }
        else
        {
            sz = Size(0,0);
        }
		return sz;
	}

	void KLResizeText::populateRenderCache()
	{
		StaticText::populateRenderCache();
	}

	Window* KLResizeTextWindowFactory::createWindow(const String& name)
    {
        return new KLResizeText(d_type, name);
    }

    void KLResizeTextWindowFactory::destroyWindow(Window* window)
    {
        delete window;
    }

	namespace KLResizeTextProperties 
	{
		String AimWindow::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void AimWindow::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLResizeText*>(receiver)->SetAimWindow( value );
		}
		
		
		String AimPosition::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void AimPosition::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLResizeText*>(receiver)->SetAimPosition( value );
		}
	}

};