
#include "KLsoftkeyboard.h"
#include "ceguipropertyhelper.h"
#include "ceguiinputevent.h"
#include "elements\ceguieditbox.h"
#include "ceguiwindowmanager.h"
#include "ceguiimagesetmanager.h"
#include "ceguiimageset.h"
namespace CEGUI
{
	const String KLSoftKeyBoard::EventNamespace("KLSoftKeyBoard");
	const utf8 KLSoftKeyBoard::WidgetTypeName[] = "Falagard/SoftKeyWindow";

	KLSoftKeyProperties::HoverImage   KLSoftKeyBoard::d_hoverImage;
	KLSoftKeyProperties::PushedImage   KLSoftKeyBoard::d_pushedImage;
	KLSoftKeyProperties::KeySize      KLSoftKeyBoard::d_keySize;

	const String KLSoftKeyBoard::EventReturn( (utf8*)"ReturnPush" );

	KLSoftKeyBoard::KLSoftKeyBoard(const String& type, const String& name):
			FalagardStaticImage( type, name )
	{
		m_pAimEditBox = NULL;
		m_bShiftDown = false;
		m_pLastKey = NULL;
		m_pCurrentKey = NULL;
		GridWidth = 30;
		GridHeight = 30;
		d_gridWidth = 30;
		d_gridHeight = 30;
		d_SoftkeyCallback = NULL;

		for( int i = 0; i < BUTTON_TYPE_NUMBER; i ++ )
		{
			m_pHoverImage[ i ] = NULL;
			m_pPushedImage[ i ] = NULL;
		}
		m_bKeyDown = false;
		CEGUI_START_ADD_STATICPROPERTY( KLSoftKeyBoard )
			CEGUI_ADD_STATICPROPERTY( &d_hoverImage );
			CEGUI_ADD_STATICPROPERTY( &d_pushedImage );
			CEGUI_ADD_STATICPROPERTY( &d_keySize );
		CEGUI_END_ADD_STATICPROPERTY
	}

	KLSoftKeyBoard::~KLSoftKeyBoard(void)
	{
	}
	void KLSoftKeyBoard::SetActiveEditBox( String& windowName )
	{
		m_pAimEditBox = WindowManager::getSingleton().getWindow( windowName );
	}
	void KLSoftKeyBoard::onMouseButtonUp( MouseEventArgs& e )
	{
		if( m_bKeyDown && e.button == LeftButton && m_pCurrentKey && m_pAimEditBox )
		{
			m_pAimEditBox->activate();
			switch( m_pCurrentKey->m_pKeyDefine->nType )
			{
			case SoftKey_Back:
				{
					if( d_SoftkeyCallback )
					{
						d_SoftkeyCallback( 0, m_pCurrentKey->m_pKeyDefine->uChar );
//						d_SoftkeyCallback( 9, 0 );
						((Editbox*)m_pAimEditBox)->clearText();
					}
					else
					{
						((Editbox*)m_pAimEditBox)->handleBackspace();
					}
				}
				break;
			case SoftKey_Return:
				fireEvent(EventReturn, e, EventNamespace);
				break;
			case SoftKey_Shift:
				m_bShiftDown = !m_bShiftDown;
				break;
			default:
				{
					if( d_SoftkeyCallback )
					{
						d_SoftkeyCallback( 0, m_pCurrentKey->m_pKeyDefine->uChar );
//						((Editbox*)m_pAimEditBox)->addCharater( 48 );
					}
					else
					{
						((Editbox*)m_pAimEditBox)->addCharater( m_pCurrentKey->m_pKeyDefine->uChar );	// 
					}
				}
				break;
			}
			ResetAllKey();
			m_bKeyDown = false;
		}
		releaseInput();
		requestRedraw();
	}
	void KLSoftKeyBoard::onMouseLeaves( MouseEventArgs& e )
	{
		m_bKeyDown = false;
		m_pLastKey = NULL;
		m_pCurrentKey = NULL;
		releaseInput();
		requestRedraw();
	}
	void KLSoftKeyBoard::onMouseButtonDown( MouseEventArgs& e )
	{
		
		if( e.button == LeftButton && m_pCurrentKey )
		{
			m_bKeyDown = true;
			requestRedraw();
			activate();
			captureInput();
		}

	}
	void KLSoftKeyBoard::onMouseMove( MouseEventArgs& e )
	{
		updateKeyPosition( e.position );
		Window::onMouseMove( e );
	}
	void KLSoftKeyBoard::updateKeyPosition( const Point& screenPos )
	{
		m_pCurrentKey = getKeyByPosition( screenPos );
		if( m_pCurrentKey )
		{
			switch( m_pCurrentKey->m_pKeyDefine->nType )
			{
			case SoftKey_Back:
				m_pCurrentKey = &m_aKeyPosList[ SoftKey_Back ].at( 0 );
				break;
			case SoftKey_Shift:
				m_pCurrentKey = &m_aKeyPosList[ SoftKey_Shift ].at( 0 );
				break;
			case SoftKey_Return:
				m_pCurrentKey = &m_aKeyPosList[ SoftKey_Return ].at( 0 );
				break;
			default:
				break;
			}
		}
		if( m_pCurrentKey != m_pLastKey ) 
		{	
			setKeyHover( m_pLastKey, false );
			setKeyHover( m_pCurrentKey, true );
			m_pLastKey = m_pCurrentKey;
			m_bKeyDown = false;
			requestRedraw();
		}
	}
	SKey_Position* KLSoftKeyBoard::getKeyByPosition( const Point& screenPos )
	{
		Point pos = screenPos;
		pos.d_x -= getPixelRect().d_left;
		pos.d_y -= getPixelRect().d_top;
		for( int j = 0; j < SoftKey_TypeNumber; j ++ )
		{
			for( int i = 0; i < int( m_aKeyPosList[ j ].size() ); i ++ )
			{
				SKey_Position *pItem = &m_aKeyPosList[ j ].at( i );
				CEGUI::Rect rect;
				rect.d_left   = pItem->m_Pos.d_x;
				rect.d_top    = pItem->m_Pos.d_y;
				rect.d_right  = rect.d_left + d_gridWidth;
				rect.d_bottom = rect.d_top + d_gridHeight;
				if( rect.isPointInRect( pos ) )
				{
					return pItem;
				}
			}
		}
		return NULL;
	}
	void KLSoftKeyBoard::setKeyHover( SKey_Position* pKey, bool bHover )
	{
		if( pKey )
			pKey->setHover( bHover );
	}
	void KLSoftKeyBoard::setKeyPosition( int x, int y, int nType )
	{
		SKey_Position item;
		item.m_Pos.d_x = x * d_gridWidth; 
		item.m_Pos.d_y = y * d_gridHeight;
		m_aKeyPosList[ nType ].push_back( item );
	}
	void KLSoftKeyBoard::setKeyDefine( utf32 nchar, int nType )
	{
		SKey_Define  define;
		define.uChar = nchar;
		define.nType = nType;
		m_aKeyDefineList[ nType ].push_back( define );
	}
	void KLSoftKeyBoard::onShown(WindowEventArgs& e)
	{
		ResetAllKey();
		FalagardStaticImage::onShown( e );
	}
	
	void KLSoftKeyBoard::ResetAllKey()
	{
		assert(m_aKeyPosList[ SoftKey_Punctuation ].size() == m_aKeyDefineList[ SoftKeyDef_Punctuation ].size() );

		
		int nStart = rand() % int( m_aKeyPosList[ SoftKey_Punctuation ].size() );
		int nIndex;
		for( int i = 0; i < int( m_aKeyPosList[ SoftKey_Punctuation ].size() ); i ++ )
		{
			nIndex = i + nStart;
			if( nIndex >= int( m_aKeyPosList[ SoftKey_Punctuation ].size() ) )
				nIndex = nIndex - int( m_aKeyPosList[ SoftKey_Punctuation ].size() );
			SKey_Position* pItem = &m_aKeyPosList[ SoftKey_Punctuation ].at( i );
			pItem->m_pKeyDefine  = &m_aKeyDefineList[ SoftKeyDef_Punctuation ].at( nIndex );
		}
		nStart = rand() % int( m_aKeyPosList[ SoftKey_Number ].size() );
		for( int i = 0; i < int( m_aKeyPosList[ SoftKey_Number ].size() ); i ++ )
		{
			nIndex = i + nStart;
			if( nIndex >= int( m_aKeyPosList[ SoftKey_Number ].size() ) )
				nIndex = nIndex - int( m_aKeyPosList[ SoftKey_Number ].size() );
			SKey_Position* pItem = &m_aKeyPosList[ SoftKey_Number ].at( i );
			pItem->m_pKeyDefine  = &m_aKeyDefineList[ SoftKeyDef_Number ].at( nIndex );
		}
		nStart = rand() % int( m_aKeyPosList[ SoftKey_Word ].size() );
		for( int i = 0; i < int( m_aKeyPosList[ SoftKey_Word ].size() ); i ++ )
		{
			nIndex = i + nStart;
			if( nIndex >= int( m_aKeyPosList[ SoftKey_Word ].size() ) )
				nIndex = nIndex - int( m_aKeyPosList[ SoftKey_Word ].size() );

			SKey_Position* pItem = &m_aKeyPosList[ SoftKey_Word ].at( i );
			if( m_bShiftDown )
				pItem->m_pKeyDefine  = &m_aKeyDefineList[ SoftKeyDef_Capital_Word ].at( nIndex );
			else
				pItem->m_pKeyDefine  = &m_aKeyDefineList[ SoftKeyDef_Lower_Word ].at( nIndex );
		}

		
		for( int i = 0; i < int ( m_aKeyPosList[ SoftKey_Back ].size() ); i ++ )
		{
			SKey_Position* pItem = &m_aKeyPosList[ SoftKey_Back ].at( i );
			pItem->m_pKeyDefine = &m_KeyDefBack;
		}
		for( int i = 0; i < int ( m_aKeyPosList[ SoftKey_Return].size() ); i ++ )
		{
			SKey_Position* pItem = &m_aKeyPosList[ SoftKey_Return ].at( i );
			pItem->m_pKeyDefine = &m_KeyDefReturn;
		}
		for( int i = 0; i < int ( m_aKeyPosList[ SoftKey_Shift].size() ); i ++ )
		{
			SKey_Position* pItem = &m_aKeyPosList[ SoftKey_Shift ].at( i );
			pItem->m_pKeyDefine = &m_KeyDefShift;
		}
		requestRedraw();
	}
	void KLSoftKeyBoard::initialise()
	{
		
		for( int i = 33; i < 48; i ++ )
			setKeyDefine( i, SoftKeyDef_Punctuation );
		for( int i = 58; i < 65; i ++ )
			setKeyDefine( i, SoftKeyDef_Punctuation );
		for( int i = 91; i < 97; i ++ )
			setKeyDefine( i, SoftKeyDef_Punctuation );
		for( int i = 123; i < 127; i ++ )
			setKeyDefine( i, SoftKeyDef_Punctuation );
		
		for( int i = 48; i < 58; i ++ )
			setKeyDefine( i, SoftKeyDef_Number );
		
		for( int i = 97; i < 123; i ++ )
			setKeyDefine( i, SoftKeyDef_Lower_Word );
		
		for( int i = 65; i < 91; i ++ )
			setKeyDefine( i, SoftKeyDef_Capital_Word );

		m_KeyDefReturn.nType = SoftKey_Return;
		m_KeyDefShift.nType = SoftKey_Shift;
		m_KeyDefBack.nType = SoftKey_Back;

		resetAllPosition();
		FalagardStaticImage::initialise();
		
	}
	void KLSoftKeyBoard::setKeySize( const Size& size )
	{
		GridWidth = size.d_width;
		GridHeight = size.d_height;

		Size curSize;
		if(getParent())
			curSize = getParent()->getAbsoluteSize();
		else
			curSize = System::getSingleton().getRenderer()->getSize();

		if( curSize.d_width == 1024 && curSize.d_height == 768 )
		{
			d_gridWidth = GridWidth;
			d_gridHeight = GridHeight;
		}
		else
		{
			d_gridWidth = GridWidth / 1024 * curSize.d_width;
			d_gridHeight = GridHeight / 768 * curSize.d_height;
		}
		if(d_groupWindow)
		{
			float xscale = curSize.d_width/1024;
			float yscale = curSize.d_height/768;			

			d_gridWidth = d_gridWidth /xscale * yscale;
		}

		resetAllPosition();
	}
	void KLSoftKeyBoard::resetAllPosition()
	{
		for( int i = 0; i < SoftKey_TypeNumber; i ++ )
			m_aKeyPosList[ i ].clear();
		SKey_Position item;
		for( int i = 0; i < 10; i ++ ) 
		{
			setKeyPosition( i + 1, 1, SoftKey_Number );
		}
		
		for( int i = 0; i < 13; i ++ )
		{
			setKeyPosition( i , 0, SoftKey_Punctuation );
		}
		
		setKeyPosition( 0, 1, SoftKey_Punctuation);
		setKeyPosition( 11,1, SoftKey_Punctuation);
		setKeyPosition( 12,1, SoftKey_Punctuation);
		setKeyPosition( 10,2, SoftKey_Punctuation);
		setKeyPosition( 11,2, SoftKey_Punctuation);
		setKeyPosition( 12,2, SoftKey_Punctuation);
		setKeyPosition( 13,2, SoftKey_Punctuation);
		setKeyPosition( 9,3, SoftKey_Punctuation);
		setKeyPosition( 10,3, SoftKey_Punctuation);
		setKeyPosition( 11,3, SoftKey_Punctuation);
		setKeyPosition( 12,3, SoftKey_Punctuation);
		setKeyPosition( 7,4, SoftKey_Punctuation);
		setKeyPosition( 8,4, SoftKey_Punctuation);
		setKeyPosition( 9,4, SoftKey_Punctuation);
		setKeyPosition( 10,4, SoftKey_Punctuation);
		setKeyPosition( 11,4, SoftKey_Punctuation);
		setKeyPosition( 12,4, SoftKey_Punctuation);
		setKeyPosition( 13,4, SoftKey_Punctuation);
		setKeyPosition( 14,4, SoftKey_Punctuation);

		
		for( int i = 0; i < 10; i ++ )
			setKeyPosition( i , 2, SoftKey_Word );
		for( int i = 0; i < 9; i ++ )
			setKeyPosition( i , 3, SoftKey_Word );
		for( int i = 0; i < 7; i ++ )
			setKeyPosition( i , 4, SoftKey_Word );

		
		setKeyPosition( 13,0,SoftKey_Back );
		setKeyPosition( 14,0,SoftKey_Back );

		setKeyPosition( 13,1,SoftKey_Shift );
		setKeyPosition( 14,1,SoftKey_Shift );

		
		setKeyPosition( 13,3,SoftKey_Return );
		setKeyPosition( 14,2,SoftKey_Return );
		setKeyPosition( 14,3,SoftKey_Return );
		
		
		ResetAllKey();
	}
	void KLSoftKeyBoard::populateRenderCache()
	{
		FalagardStaticImage::populateRenderCache();

		
		Rect rect;
		const Font* font = getFont();
		
		if (font == 0)
			return;
		ColourRect final_TextColor( colour( 0.0f, 0.0f, 0.0f ) );
		final_TextColor.setAlpha( d_alpha );
		String text;
		for( int j = 0; j < SoftKey_Type_Number; j ++ )
		{
			for( int i = 0; i < int( m_aKeyPosList[ j ].size() ); i ++ )
			{
				SKey_Position* pItem = &m_aKeyPosList[ j ].at( i );
				rect.d_left   = pItem->m_Pos.d_x ;
				rect.d_right  = pItem->m_Pos.d_x + d_gridWidth ;
				rect.d_top    = pItem->m_Pos.d_y;
				rect.d_bottom = pItem->m_Pos.d_y + d_gridHeight;
	

				if( pItem && pItem->m_pKeyDefine&& ( pItem->m_pKeyDefine->nType <= SoftKey_Type_Number ) ) 
				{
					text = pItem->m_pKeyDefine->uChar;
					float textHeight = font->getFormattedSize( text, rect, CEGUI::LeftAligned ).d_height;
					rect.d_top += ( rect.getHeight() - textHeight ) / 2;
					d_renderCache.cacheText( this, text, font, Centred , rect, 0, final_TextColor, &rect, true );
				}
			}
		}

		ColourRect final_ImageColor( colour( 1.0f, 1.0f, 1.0f ) );
		final_ImageColor.setAlpha( d_alpha );
		if( m_pCurrentKey && m_pCurrentKey->m_pKeyDefine )
		{
			switch( m_pCurrentKey->m_pKeyDefine->nType )
			{
			case SoftKey_Back:
				rect.d_left   = m_pCurrentKey->m_Pos.d_x;
				rect.d_right  = m_pCurrentKey->m_Pos.d_x + d_gridWidth * 2 ;
				rect.d_top    = m_pCurrentKey->m_Pos.d_y;
				rect.d_bottom = m_pCurrentKey->m_Pos.d_y + d_gridHeight;
				if( m_bKeyDown )
				{
					if( m_pPushedImage[ BUTTON_TYPE_BACK ] )
					d_renderCache.cacheImage( *m_pPushedImage[ BUTTON_TYPE_BACK ], rect, 0, final_ImageColor);
				}
				else
				{
					if( m_pHoverImage[ BUTTON_TYPE_BACK ] )
					d_renderCache.cacheImage( *m_pHoverImage[ BUTTON_TYPE_BACK ], rect, 0, final_ImageColor);
				}
				break;

			case SoftKey_Shift:
				rect.d_left   = m_pCurrentKey->m_Pos.d_x;
				rect.d_right  = m_pCurrentKey->m_Pos.d_x + d_gridWidth * 2 ;
				rect.d_top    = m_pCurrentKey->m_Pos.d_y;
				rect.d_bottom = m_pCurrentKey->m_Pos.d_y + d_gridHeight;
				if( m_bKeyDown )
				{
					if( m_pPushedImage[ BUTTON_TYPE_SHIFT ] )
					d_renderCache.cacheImage( *m_pPushedImage[ BUTTON_TYPE_SHIFT ], rect, 0, final_ImageColor);
				}
				else
				{
					if( m_pHoverImage[ BUTTON_TYPE_SHIFT ] )
					d_renderCache.cacheImage( *m_pHoverImage[ BUTTON_TYPE_SHIFT ], rect, 0, final_ImageColor);
				}
				break;

			case SoftKey_Return:
				rect.d_left   = m_pCurrentKey->m_Pos.d_x;
				rect.d_right  = m_pCurrentKey->m_Pos.d_x + d_gridWidth * 2;
				rect.d_top    = m_pCurrentKey->m_Pos.d_y - d_gridHeight;
				rect.d_bottom = m_pCurrentKey->m_Pos.d_y + d_gridHeight;
				if( m_bKeyDown )
				{
					if( m_pPushedImage[ BUTTON_TYPE_RETURN ] )
					d_renderCache.cacheImage( *m_pPushedImage[ BUTTON_TYPE_RETURN ], rect, 0, final_ImageColor);
				}
				else
				{
					if( m_pHoverImage[ BUTTON_TYPE_RETURN ] )
					d_renderCache.cacheImage( *m_pHoverImage[ BUTTON_TYPE_RETURN ], rect, 0, final_ImageColor);
				}
				break;

			default:
				rect.d_left   = m_pCurrentKey->m_Pos.d_x ;
				rect.d_right  = m_pCurrentKey->m_Pos.d_x + d_gridWidth ;
				rect.d_top    = m_pCurrentKey->m_Pos.d_y;
				rect.d_bottom = m_pCurrentKey->m_Pos.d_y + d_gridHeight;
				if( m_bKeyDown )
				{
					if( m_pPushedImage[ BUTTON_TYPE_NORMAL ] )
					d_renderCache.cacheImage( *m_pPushedImage[ BUTTON_TYPE_NORMAL ], rect, 0, final_ImageColor);
				}
				else
				{
					if( m_pHoverImage[ BUTTON_TYPE_NORMAL ] )
					d_renderCache.cacheImage( *m_pHoverImage[ BUTTON_TYPE_NORMAL ], rect, 0, final_ImageColor);
				}
				break;
			}
		}
	}

	void KLSoftKeyBoard::onSized(WindowEventArgs& e)
	{
		Size curSize;
		if(getParent())
			curSize = getParent()->getAbsoluteSize();
		else
			curSize = System::getSingleton().getRenderer()->getSize();

		if(curSize.d_width > 1024)
			curSize.d_width = 1024;
		if(curSize.d_height > 768)
			curSize.d_height = 769;

		if( curSize.d_width == 1024 && curSize.d_height == 768 )
		{
			d_gridWidth = GridWidth;
			d_gridHeight = GridHeight;
		}
		else
		{
			d_gridWidth = GridWidth / 1024 * curSize.d_width;
			d_gridHeight = GridHeight / 768 * curSize.d_height;
		}

		if(d_groupWindow)
		{
			float xscale = curSize.d_width/1024;
			float yscale = curSize.d_height/768;			

			d_gridWidth = d_gridWidth /xscale * yscale;
		}

		resetAllPosition();

		Window::onSized(e);
	}

	void KLSoftKeyBoard::setHoverImage( int nType, const Image* pImage )
	{
		m_pHoverImage[ nType ] = pImage;
	}
	void KLSoftKeyBoard::setPushedImage( int nType, const Image* pImage )
	{
		m_pPushedImage[ nType ] = pImage;
	}

	namespace KLSoftKeyProperties
	{
		String	KeySize::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	KeySize::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSoftKeyBoard*>(receiver)->setKeySize( PropertyHelper::stringToSize( value ) );
		}

		String	HoverImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	HoverImage::set(PropertyReceiver* receiver, const String& value)
		{
			int  nType;
			char szSet[ 128 ];
			char szImage[ 128 ];
			sprintf( szSet, "" );
			sprintf( szImage, "" );
			sscanf( value.c_str(), "type:%d set:%127s image:%127s", &nType, szSet, szImage );

			const Image* pImage = ImagesetManager::getSingleton().getImageset( szSet )->getImage( szImage );
			static_cast<KLSoftKeyBoard*>(receiver)->setHoverImage( nType, pImage );
		}
		String	PushedImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void	PushedImage::set(PropertyReceiver* receiver, const String& value)
		{
			int  nType;
			char szSet[ 128 ];
			char szImage[ 128 ];
			sprintf( szSet, "" );
			sprintf( szImage, "" );
			sscanf( value.c_str(), "type:%d set:%127s image:%127s", &nType, szSet, szImage );
			const Image* pImage = ImagesetManager::getSingleton().getImageset( szSet )->getImage( szImage );
			static_cast<KLSoftKeyBoard*>(receiver)->setPushedImage( nType, pImage );
		}
	};

		 
    
    Window* KLSoftKeyFactory::createWindow(const String& name)
    {
        return new KLSoftKeyBoard(d_type, name);
    }

    void KLSoftKeyFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}