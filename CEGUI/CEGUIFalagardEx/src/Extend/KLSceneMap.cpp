#include "KLscenemap.h"
#include "ceguiPropertyHelper.h"
#include "ceguiimagesetmanager.h"
#include "ceguiimageset.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "ceguiwindowmanager.h"
#include "ceguitexture.h"
#include "KLKeyImageAnimation.h"

namespace CEGUI
{
	KLSceneMapProperties::PlayerImage			KLSceneMap::d_PlayerImageProperty;		
	KLSceneMapProperties::MySelfImage			KLSceneMap::d_MyselfImageProperty;		

	KLSceneMapProperties::FlashImage		KLSceneMap::d_FlashImageProperty;		
	KLSceneMapProperties::ActiveImage		KLSceneMap::d_ActiveImageProperty;		
	KLSceneMapProperties::TeammateImage		KLSceneMap::d_TeammateImageProperty;		

	const String KLSceneMap::EventNamespace("Falagard/SceneMap");
	const String KLSceneMap::MouseRButtonDownCtrl("MouseRButtonDownCtrl");
	const utf8 KLSceneMap::WidgetTypeName[] = "Falagard/SceneMap";
	const int SCENE_MAP_PER_PIC = 64; 
	const int SCENE_MAP_ZOOMSCALE = 4;
	
	struct SCENEMAP_FLAG_LIST
	{
		Point   pos;
		String  name;
		Size    size;
		Window* m_pWindow;
		size_t dirty;
		SCENEMAP_FLAG_LIST()
		{
			pos = Point( 0,0 );
			name.clear();
			size = Size( 0,0 );
			dirty = true;
			m_pWindow = 0;
		}
		~SCENEMAP_FLAG_LIST()
		{
			m_pWindow = 0;
		}
	};

	KLSceneMap::KLSceneMap(const String& type, const String& name) :
		FalagardStaticImage(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLSceneMap )
		   CEGUI_ADD_STATICPROPERTY( &d_PlayerImageProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_MyselfImageProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_FlashImageProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_ActiveImageProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_TeammateImageProperty );
		CEGUI_END_ADD_STATICPROPERTY
		
		d_fresh = false;
		d_PlayerDirect = 0;
		d_CameraDirect = 0;
		d_MyselfAnimate.clear();
		m_pMySelfWindow = NULL;
		m_nXCount		= 0;
		m_nYCount		= 0;
		d_MouseScenePos = Point( 0, 0 );
		d_SceneSize		= Size( 128, 128 );
		d_PlayerImage	= NULL;
		for( int i = 0; i < 5; i ++ )
			m_pFriendWindow[ i ] = NULL;
		m_pBackground = NULL;
		m_WindowZero = Point( 0, 0 );
		m_aPlayerPos.clear();
		m_aNpcPos.clear();
		m_fZoomValueX = 1; 
		m_fZoomValueY = 1; 

		
		m_pBigSceneWindow = 0;

		m_bDraping = false;
		m_bMouseIn = false;
		m_bIsCreateSceneMap = false;

		m_nDisplayMode = SCENEMAP_DISPLAY_MODE_ABSOLTE;
		
		setNeedRealTimeUpdate(true);


	}

	KLSceneMap::~KLSceneMap()
	{
		if( m_pBackground )
		{
			WindowManager::getSingleton().destroyWindow( m_pBackground );
			m_pBackground = NULL;
		}

		ClearNPCPos(false);
		clearPathNodeData(false);
	}
	void KLSceneMap::Close()
	{
		Clear();

		uint child_count = getChildCount();
		for (uint i = 0; i < child_count; ++i)
		{
			d_children[i]->hide();

		}

		if( m_pMySelfWindow )
		{
			m_pMySelfWindow = NULL;
		}
		for( int i = 0; i < 5; i ++ )
		{
			m_pFriendWindow[ i ] = NULL;
		}
	}
	void KLSceneMap::addPlayerPos( const Point& pos, const String& name )
	{
		SCENEMAP_FLAG_DATA  data;
		data.pos = pos;
		data.name = name;
		m_aPlayerPos.push_back( data );
		d_fresh = true;
	}
	void KLSceneMap::onMouseButtonDown( MouseEventArgs &e )
	{
		
		
		m_ptDrapOffset = ScreenPosToScenePosRelative( e.position );
		if( e.button == RightButton )
		{
			if( e.sysKeys & Control )
				return;
			
			e.handled = true;
			captureInput();
		}

		
		d_MouseScenePos = ScreenPosToScenePos( e.position );
		d_MouseScenePos.d_x /= m_fZoomValueX;
		d_MouseScenePos.d_y /= m_fZoomValueY;
		if( d_MouseScenePos.d_x < 0 || d_MouseScenePos.d_x > d_SceneSize.d_width ||
			d_MouseScenePos.d_y < 0 || d_MouseScenePos.d_y > d_SceneSize.d_height )
		{
			d_MouseScenePos.d_x = 0;
			d_MouseScenePos.d_y = 0;
		}

		Window::onMouseButtonDown( e );
	}
	void KLSceneMap::onMouseEnters(MouseEventArgs& e)
	{
		m_bMouseIn = true;
		d_MouseScenePos = ScreenPosToScenePos( e.position );
		d_MouseScenePos.d_x /= m_fZoomValueX;
		d_MouseScenePos.d_y /= m_fZoomValueY;
		if( d_MouseScenePos.d_x < 0 || d_MouseScenePos.d_x > d_SceneSize.d_width ||
			d_MouseScenePos.d_y < 0 || d_MouseScenePos.d_y > d_SceneSize.d_height )
		{
			d_MouseScenePos.d_x = 0;
			d_MouseScenePos.d_y = 0;
		}
		Window::onMouseEnters( e );
	}
	void KLSceneMap::onMouseButtonUp( MouseEventArgs &e )
	{
		if( e.button == RightButton && ( e.sysKeys & Control ) )
		{
			WindowEventArgs args(this);
			fireEvent(MouseRButtonDownCtrl, args, EventNamespace);
			return;
		}
		m_bDraping = false;
		releaseInput();
		Window::onMouseButtonUp( e );
	}
	void    KLSceneMap::onMouseLeaves( MouseEventArgs& e )
	{
		m_bDraping = false;

		if( !isHit(e.position) )
		{
			d_MouseScenePos = m_PlayerPos;
			m_bMouseIn = false;
		}
		Window::onMouseLeaves( e );
	}

	void KLSceneMap::modifyPosition(float x, float y)
	{
		m_WindowZero.d_x += x;
		m_WindowZero.d_y += y;

		UpdateAllWindow();		
	}

	void KLSceneMap::onMouseMove( MouseEventArgs &e )
	{
		if( m_bDraping ) 
		{
			Point tmp = ScreenPosToWindowPosRelative( e.position );
			m_WindowZero.d_x = tmp.d_x - m_ptDrapOffset.d_x;
			m_WindowZero.d_y = tmp.d_y - m_ptDrapOffset.d_y;
			
			UpdateAllWindow();
		}
		else
		{
			d_MouseScenePos = ScreenPosToScenePos( e.position );
			d_MouseScenePos.d_x /= m_fZoomValueX;
			d_MouseScenePos.d_y /= m_fZoomValueY;
			if( d_MouseScenePos.d_x < 0 || d_MouseScenePos.d_x > d_SceneSize.d_width ||
				d_MouseScenePos.d_y < 0 || d_MouseScenePos.d_y > d_SceneSize.d_height )
				return;
		}
		FalagardStaticImage::onMouseMove( e );
	}
	void KLSceneMap::updateSelf(float elapsed)
	{
		if( !m_bMouseIn&& isVisible() )
			d_MouseScenePos = m_PlayerPos;

		if( d_fresh && isVisible() )
		{
			int i = 0;
			
			ResetMyself();

			
			for( i = 0; i < 5; i ++ )
			{
				m_pFriendWindow[ i ]->hide();
				m_pFriendWindow[ i ]->setNeedRealTimeUpdate(false);
			}
			RENDER_POS::iterator   it;
			String strTooltip[ 5 ]; 
			for( i = 0, it = m_aPlayerPos.begin(); it != m_aPlayerPos.end(); it ++, i ++ )
			{
				ResetPlayerWindow( i, ( *it ) );
			}
			
			
			for( int i = 0; i < 5; i ++ )
			{
				
				if( !m_pFriendWindow[ i ]->isVisible() ) 
					break;
				strTooltip[ i ] = m_pFriendWindow[ i ]->getTooltipText();
				for( int j = 0; j < 5; j ++ )
				{
					if( j == i )
						continue;
					if( !m_pFriendWindow[ j ]->isVisible() )
						break;
					if( Rect( 0, 0, 0, 0 ) != m_pFriendWindow[ i ]->getRect().getIntersection( m_pFriendWindow[ j ]->getRect() ) )
					{
						if( strTooltip[ i ].size() )
							strTooltip[ i ] += "\r\n";
						strTooltip[ i ] += m_pFriendWindow[ j ]->getTooltipText();
					}
				}
			}
			for( int i = 0; i < 5; i ++ )
			{
				if( !m_pFriendWindow[ i ]->isVisible() ) 
					break;
				m_pFriendWindow[ i ]->setTooltipText( strTooltip[ i ] );
			}

			d_fresh = false;
			requestRedraw();
		}
	}
	void KLSceneMap::setPlayerImage( const Image* pImage )
	{
		
		d_PlayerImage = ( Image* )pImage;
	}

	void KLSceneMap::setMyselfImage( const String& name )
	{
		d_MyselfAnimate = name;
	}

	void KLSceneMap::setTeammateImage(const String& name)
	{
		
	}
	void KLSceneMap::setFlashImage(const String& name)
	{
		
	}
	void KLSceneMap::setActiveImage(const String&name)
	{
		
	}

	void KLSceneMap::Clear()
	{
		m_aPlayerPos.clear();
	}
	void  KLSceneMap::SetViewByCenter( const Point& pos )
	{
		if( m_pBackground )
		{
			float fWidthWindowPerBackground = getAbsoluteWidth() / m_pBackground->getAbsoluteWidth();
			float fHeightWindowPerBackground = getAbsoluteHeight() / m_pBackground->getAbsoluteHeight();
			m_WindowZero.d_x = -( pos.d_x/fWidthWindowPerBackground - 0.5f);
			m_WindowZero.d_y = -( pos.d_y/fHeightWindowPerBackground - 0.5f);
			UpdateAllWindow();
		}
	}
	void KLSceneMap::setMyselfDir( const int nDirect )
	{
		d_PlayerDirect = ( nDirect ) % 360; 
		if( d_PlayerDirect < 0 )
			d_PlayerDirect += 360;
		d_fresh = true;
	}
	void KLSceneMap::setMyselfPos( const Point& pos ) 
	{
		m_PlayerPos = pos;
		d_MyseflPos = ScenePosToWindowPos( pos );	
		d_fresh = true;
	}

	void KLSceneMap::setCameraDir( const int nDirect )
	{
		d_CameraDirect = ( nDirect ) % 360; 
		if( d_CameraDirect < 0 )
			d_CameraDirect += 360;
		d_fresh = true;
	}
	void KLSceneMap::SetSceneFileName( const String& str )
	{
		CreateSceneMap( str.c_str() );
	}
	void KLSceneMap::onParentSized( WindowEventArgs &e )
	{
		FalagardStaticImage::onParentSized( e );
		UpdateAllWindow();
	}
	
	Point	KLSceneMap::GetCurrentCenter()
	{
		Point pos;
		float fWidthWindowPerBackground = getAbsoluteWidth() / m_pBackground->getAbsoluteWidth();
		float fHeightWindowPerBackground = getAbsoluteHeight() / m_pBackground->getAbsoluteHeight();
		pos.d_x = -m_WindowZero.d_x * fWidthWindowPerBackground + fWidthWindowPerBackground / 2;
		pos.d_y = -m_WindowZero.d_y * fHeightWindowPerBackground + fHeightWindowPerBackground / 2 ;
		return pos;
	}
	
	Rect KLSceneMap::GetCurrentViewRect() 
	{
		Rect rect;
		float fWidthWindowPerBackground = getAbsoluteWidth() / m_pBackground->getAbsoluteWidth();
		float fHeightWindowPerBackground = getAbsoluteHeight() / m_pBackground->getAbsoluteHeight();
		rect.d_left		= -m_WindowZero.d_x * fWidthWindowPerBackground;
		rect.d_top		= -m_WindowZero.d_y * fHeightWindowPerBackground;
		rect.d_right	= rect.d_left + fWidthWindowPerBackground;
		rect.d_bottom	= rect.d_top + fHeightWindowPerBackground;
		return rect;
	}

	void KLSceneMap::populateRenderCache()
	{
		
		
		FalagardStaticImage::populateRenderCache();
	}
	void  KLSceneMap::UpdateAllWindow()
	{
		if( !m_bIsCreateSceneMap )
			return;

		if( m_pBackground == NULL )
			return;
		
		
		
		float fMax = ( d_SceneSize.d_width > d_SceneSize.d_height ) ? d_SceneSize.d_width : d_SceneSize.d_height;
		if( m_nDisplayMode == SCENEMAP_DISPLAY_MODE_FULLSCREEN ) 
		{
			if( m_pBigSceneWindow )
			{
				
				
				m_pBigSceneWindow->setVisible(true);
			}
			
			float fScale = getAbsoluteHeight() / getAbsoluteWidth();
			m_fZoomValueX = fScale * d_SceneSize.d_width / fMax ;
			m_fZoomValueY = d_SceneSize.d_height / fMax;
		}
		else 
		{
			if( m_pBigSceneWindow )
				m_pBigSceneWindow->setVisible(false);

			m_fZoomValueX = d_SceneSize.d_width * SCENE_MAP_ZOOMSCALE / getAbsoluteWidth(); 
			m_fZoomValueY = d_SceneSize.d_height * SCENE_MAP_ZOOMSCALE / getAbsoluteHeight(); 
		}

		Rect winRect;
		winRect = Rect( 0, 0, m_fZoomValueX, m_fZoomValueY );
		if( m_fZoomValueX < 1 ) 
		{
			winRect.d_left = ( 1 - m_fZoomValueX ) / 2;
			winRect.d_right = winRect.d_left + m_fZoomValueX;
			m_WindowZero.d_x = winRect.d_left;
		}
		else
		{
			if( m_WindowZero.d_x < 1 - m_fZoomValueX  )
				m_WindowZero.d_x = 1 - m_fZoomValueX;
			if( m_WindowZero.d_x > 0 )
				m_WindowZero.d_x = 0;
		}
		if( m_fZoomValueY < 1 )
		{
			winRect.d_top = ( 1 - m_fZoomValueY ) / 2;
			winRect.d_bottom = winRect.d_top + m_fZoomValueY;
			m_WindowZero.d_y = winRect.d_top;
		}
		else
		{
			if( m_WindowZero.d_y < 1 - m_fZoomValueY )
				m_WindowZero.d_y = 1 - m_fZoomValueY;
			if( m_WindowZero.d_y > 0 )
				m_WindowZero.d_y = 0;
		}
		m_pBackground->setRect( Relative, winRect );
		m_pBackground->setSize( Relative, winRect.getSize());
		m_pBackground->setPosition( Relative, m_WindowZero );

		UpdateBackgroundItem();
		requestRedraw();
		d_fresh = true;
	}

	void KLSceneMap::UpdateBackgroundItem()
	{
		int i = 0;
		
		
		float fOffsetX, fOffsetY; 
	
		fOffsetX = float( ( int( d_SceneSize.d_width ) % SCENE_MAP_PER_PIC ) / float( SCENE_MAP_PER_PIC ) );  
		fOffsetY = float( ( int( d_SceneSize.d_height ) % SCENE_MAP_PER_PIC ) / float( SCENE_MAP_PER_PIC ) );
		m_nXCount =  int( d_SceneSize.d_width ) / SCENE_MAP_PER_PIC;
		m_nYCount =  int( d_SceneSize.d_height ) / SCENE_MAP_PER_PIC;
		if( fOffsetX ) 
			m_nXCount += 1;
		else 
			fOffsetX = 1;
		if( fOffsetY )
			m_nYCount += 1;
		else 
			fOffsetY = 1;
		Size size;
		float fPicSizeX = 256, fPicSizeY = 256;
		if( m_nDisplayMode == SCENEMAP_DISPLAY_MODE_FULLSCREEN )
		{
			float fMax = ( d_SceneSize.d_width > d_SceneSize.d_height ) ? d_SceneSize.d_width : d_SceneSize.d_height;
			float fScale = getAbsoluteHeight() / getAbsoluteWidth();
			fPicSizeX *= fScale * getAbsoluteWidth() / ( fMax * SCENE_MAP_ZOOMSCALE ); 
			fPicSizeY *= getAbsoluteHeight() / ( fMax * SCENE_MAP_ZOOMSCALE );
		}
		Point pos( 0, 0);

		
		assert(m_nXCount <= 8);
		assert(m_nYCount <= 8);

		for( i = 0; i < m_nXCount; i ++ )
		{
			if( i == m_nXCount - 1 && fOffsetX != 1 ) 
				size.d_width = float( fOffsetX * fPicSizeX );
			else
				size.d_width = fPicSizeX;
			
			for( int j = 0; j < m_nYCount; j ++ ) 
			{
				
				if( j == m_nYCount - 1 && fOffsetY != 1 )
					size.d_height = float( fOffsetY * fPicSizeY);
				else
					size.d_height = fPicSizeY;

				
				
				
				Window* pWindow = m_radarWindow[i][j];
				if( pWindow )
				{
					if( m_nDisplayMode == SCENEMAP_DISPLAY_MODE_FULLSCREEN )
					{
						pWindow->hide();
					}
					else
					{
						pWindow->show();
					}
					pWindow->setPosition( Absolute, pos );
					pWindow->setSize( Absolute, size );
				}
				pos.d_y += size.d_height;

			}
			pos.d_x += size.d_width; 
			pos.d_y = 0;
		}
	}
	void KLSceneMap::SetZoomMode( int nMode )
	{ 
		m_nDisplayMode = nMode; 
		UpdateAllWindow();
		setSceneMapCenter();
	};
	const Image* KLSceneMap::getImageByName( const String& str, Rect rect ) 
	{
		const String imagename = "Scenemap_view"; 
		Imageset* pSet;
		char szFullFileName[ 128 ];

		if( CEGUI::Logger::getSingleton().isDebugEnvironment() )
			sprintf( szFullFileName, "%s.jpg", str.c_str() );
		else
			sprintf( szFullFileName, "%s.dds", str.c_str() );

		Point offset( 0, 0 );
		if( !ImagesetManager::getSingleton().isImagesetPresent( str ) )
		{
			pSet = ImagesetManager::getSingleton().createImagesetFromImageFile( str.c_str(), szFullFileName, "Scene" );
		}
		pSet = ImagesetManager::getSingleton().getImageset( str );
		if( pSet ) 
		{
			if( !pSet->isImageDefined( imagename ) )
				pSet->defineImage( imagename, rect, offset );
			return pSet->getImage( imagename );
		}
		return NULL;
		
	}

	
	void KLSceneMap::reset_radarWindow()
	{
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				m_radarWindow[i][j] = 0;
	}

	void KLSceneMap::createBackground( const String& strFileName )
	{
		
		reset_radarWindow();

		
		int i = 0;
		char szImagesetName[ 128 ];
		char szWindowName[ 128 ];

		
		if(m_pBackground)
		{
			WindowManager::getSingleton().destroyWindow( m_pBackground );
		}
		sprintf( szWindowName, "%s_auto_background", getName().c_str() ); 
		if( WindowManager::getSingleton().isWindowPresent( szWindowName ) ) 
		{		
			WindowManager::getSingleton().destroyWindow( szWindowName );		
		}
		
		m_pBackground = WindowManager::getSingleton().createWindow( "DefaultWindow", szWindowName );
		
		addChildWindow( m_pBackground );
		m_pBackground->setMaximumSize( Size( 100, 100 ) );
		m_pBackground->setRiseOnClickEnabled( false );
		m_pBackground->setMouseMoveHollow( true );
		
		float fOffsetX, fOffsetY; 
		float fPicSizeX = 256, fPicSizeY = 256;
		fOffsetX = float( ( int( d_SceneSize.d_width ) % SCENE_MAP_PER_PIC ) / float( SCENE_MAP_PER_PIC ) );  
		fOffsetY = float( ( int( d_SceneSize.d_height ) % SCENE_MAP_PER_PIC ) / float( SCENE_MAP_PER_PIC ) );
		m_nXCount =  int( d_SceneSize.d_width ) / SCENE_MAP_PER_PIC;
		m_nYCount =  int( d_SceneSize.d_height ) / SCENE_MAP_PER_PIC;
		if( fOffsetX ) 
			m_nXCount += 1;
		else 
			fOffsetX = 1;
		if( fOffsetY )
			m_nYCount += 1;
		else 
			fOffsetY = 1;

		float fWidthPerItem = 1 / d_SceneSize.d_width;
		float fHeightPerItem = 1 / d_SceneSize.d_height;
		
		
		assert(m_nXCount <= 8);
		assert(m_nYCount <= 8);

		for( i = 0; i < m_nXCount; i ++ )
		{
			for( int j = 0; j < m_nYCount; j ++ ) 
			{
				sprintf( szImagesetName, "%s_%d_%d", strFileName.c_str(),i, j );
				
				Rect rect( 0, 0, float( fPicSizeX ), float( fPicSizeY ) );
				Point offset( 0, 0 );
				if( i == m_nXCount - 1 && fOffsetX != 1 ) 
					rect.d_right = float( fOffsetX * fPicSizeX );
				if( j == m_nYCount - 1 && fOffsetY != 1 )
					rect.d_bottom = float( fOffsetY * fPicSizeY);
				
				sprintf( szWindowName, "%s_map_%d_%d", getName().c_str(),i, j ); 
				Window* pWindow = NULL;
				if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) ) 
				{
					pWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );
					m_pBackground->addChildWindow( pWindow );
				}
				
				
				if( pWindow ) 
				{
					
					m_radarWindow[i][j] = pWindow;
					try
					{
						const Image* pStaticImage = ((StaticImage*)pWindow)->getImage();
						if(pStaticImage)
						{
							Imageset* imageset = (Imageset*)(pStaticImage->getImageset());
							if( imageset && imageset->getOriginTexture() )
							{
								imageset->destroyImagesetTexture();
							}
						}
					}
					catch (...)
					{
						Logger::getSingleton().logEvent("KLRadar::createBackground - failed destroyImagesetTexture.", Errors);
					}

					((StaticImage*)pWindow)->setImage( getImageByName( szImagesetName, rect ) );
					pWindow->setRiseOnClickEnabled( false );
					pWindow->setMouseHollow( true );
				}

				
				CEGUI::Rect winRect;
				winRect.d_left= i * SCENE_MAP_PER_PIC / d_SceneSize.d_width;
				winRect.d_top = j * SCENE_MAP_PER_PIC / d_SceneSize.d_height;
				winRect.d_right = winRect.d_left + ( fOffsetX * SCENE_MAP_PER_PIC) / d_SceneSize.d_width;
				winRect.d_bottom = winRect.d_top + ( fOffsetY * SCENE_MAP_PER_PIC) / d_SceneSize.d_height;
				pWindow->setRect( Relative, winRect );
				pWindow->setSize( Relative, winRect.getSize() );
				pWindow->show();
				pWindow->setMouseHollow( true ); 
				pWindow->setMouseMoveHollow( true ); 
				pWindow->setMaximumSize( Size( 100, 100 ) );
				pWindow->setRiseOnClickEnabled( false );			
			}
		}
	}
	void KLSceneMap::CreateSceneMap( const String& strFileName )
	{
		m_bIsCreateSceneMap = true;

		char szWindowName[ 128 ];

		if( CEGUI::Logger::getSingleton().isDebugEnvironment() )
			sprintf(szWindowName,"%s_bigscenemap.jpg",strFileName.c_str());
		else
			sprintf(szWindowName,"%s_bigscenemap.dds",strFileName.c_str());

		if( !WindowManager::getSingleton().isWindowPresent( "bigscenemap_Window" ) ) 
			WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", "bigscenemap_Window" );
		m_pBigSceneWindow = (StaticImage*)WindowManager::getSingleton().getWindow( "bigscenemap_Window" );

		Imageset *pSet = 0;
		if( !ImagesetManager::getSingleton().isImagesetPresent( szWindowName ) )
		{
			ImagesetManager::getSingleton().createImagesetFromImageFile( szWindowName, szWindowName, "Scene" );
		}
		pSet = ImagesetManager::getSingleton().getImageset(szWindowName);
		assert(pSet);
		Texture* pTex = pSet->getTexture();
		assert(pTex);
		m_pBigSceneWindow->setProperty( "Image", PropertyHelper::stringToImageString( szWindowName, "full_image") );

		addChildWindow(m_pBigSceneWindow);
		m_pBigSceneWindow->setVisible(false);		
		m_pBigSceneWindow->setPosition( Relative, Point(0.0f,0.0f));
		m_pBigSceneWindow->setSize( Relative,Size(1.0f,1.0f));

		m_pBigSceneWindow->setMouseHollow( true );
		m_pBigSceneWindow->setMouseMoveHollow( true );
		m_pBigSceneWindow->setRiseOnClickEnabled(false);

		
		createBackground( strFileName );

		
		for(int  i = 0; i < 5; i ++ )
		{
			sprintf( szWindowName, "Scenemap_Player_%d", i );
			if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) ) 
				WindowManager::getSingleton().createWindow( "KylinUI/NoHoverAnimate", szWindowName );
			m_pFriendWindow[ i ] = (StaticImage*)WindowManager::getSingleton().getWindow( szWindowName );
			m_pBackground->addChildWindow( m_pFriendWindow[ i ] );
			m_pFriendWindow[ i ]->hide();
			((KLKeyImageAnimation*)m_pFriendWindow[i])->SetAnimate( "circle" );
			m_pFriendWindow[i]->setMouseHollow(true);
			m_pFriendWindow[i]->setMouseMoveHollow(false);
			m_pFriendWindow[i]->setMouseLButtonHollow(true);
		}
		sprintf( szWindowName, "%s_Auto_MyselfWindow", getName().c_str() );  
		if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) ) 
			WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );
		m_pMySelfWindow = (StaticImage*)WindowManager::getSingleton().getWindow( szWindowName );		
		m_pMySelfWindow->setAlwaysOnTop( true );
		m_pMySelfWindow->setMouseHollow( true );
		m_pMySelfWindow->setMouseMoveHollow( true );
		m_pMySelfWindow->show();
		addChildWindow( m_pMySelfWindow );

		m_pBackground->setMouseHollow( true );
		m_pBackground->setMouseMoveHollow( true );

		UpdateAllWindow();
	}

	void	KLSceneMap::setSceneMapCenter()
	{
		SetViewByCenter( d_MyseflPos );
	}
	void KLSceneMap::ResetMyself()
	{
		KeyImageAnimation* pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_MyselfAnimate );
		if( pAnimate && m_pBackground && m_pMySelfWindow )
		{
			int nCurFrame = ( d_PlayerDirect * pAnimate->getFrameNumber() ) / 360;
			Image* pPlayerImage = (Image*)( pAnimate->getFrame( nCurFrame ) );
			
			Point curPos = d_MyseflPos;
			Rect rect;
			float fWidth = ( pPlayerImage->getWidth() / m_pBackground->getAbsoluteWidth() ) / 2;
			float fHeight = ( pPlayerImage->getHeight() / m_pBackground->getAbsoluteHeight() ) / 2;
			rect.d_left   = curPos.d_x -  fWidth;
			rect.d_right  = curPos.d_x + fWidth;
			rect.d_top    = curPos.d_y - fHeight;
			rect.d_bottom = curPos.d_y + fHeight; 
			(( StaticImage* )m_pMySelfWindow)->setImage( pPlayerImage ) ;
			m_pMySelfWindow->setRect( Relative, rect );
			m_pMySelfWindow->setSize( Relative, rect.getSize() );
			m_pMySelfWindow->moveToFront();
		}
	}
	
	void KLSceneMap::ResetPlayerWindow( int nIndex, SCENEMAP_FLAG_DATA& data )
	{
		Point curPos = ScenePosToWindowPos( data.pos );
		Rect rect;
		float fWidth = ( d_PlayerImage->getSourceTextureArea().getWidth() / m_pBackground->getAbsoluteWidth() ) ;
		float fHeight = ( d_PlayerImage->getSourceTextureArea().getHeight() / m_pBackground->getAbsoluteHeight() ) ;
		rect.d_left   = curPos.d_x - fWidth;
		rect.d_right  = curPos.d_x + fWidth;
		rect.d_top    = curPos.d_y - fHeight;
		rect.d_bottom = curPos.d_y + fHeight;
	
		m_pFriendWindow[ nIndex ]->show();
		m_pFriendWindow[ nIndex ]->setRect( Relative, rect );
		m_pFriendWindow[ nIndex ]->setSize( Relative,  rect.getSize() );
		m_pFriendWindow[ nIndex ]->setTooltipText( data.name );
		m_pFriendWindow[ nIndex ]->setMouseLButtonHollow(true);
		m_pFriendWindow[ nIndex ]->setNeedRealTimeUpdate(true);

		
		
		
		
		
	}

	Point KLSceneMap::ScreenPosToScenePos( const Point& pos ) 
	{

		Point tmp;
		float fMapScreenWidth = getPixelRect().getWidth();
		float fMapScreenHeight = getPixelRect().getHeight();
		
		tmp.d_x = ( pos.d_x - getPixelRect().d_left ) / fMapScreenWidth - m_WindowZero.d_x;
		tmp.d_y = ( pos.d_y - getPixelRect().d_top ) / fMapScreenHeight - m_WindowZero.d_y;

		tmp.d_x *= d_SceneSize.d_width;
		tmp.d_y *= d_SceneSize.d_height;
		return tmp;
	}

	Point KLSceneMap::ScreenPosToWindowPosRelative( const Point& pos ) 
	{
		Point tmp;
		float fMapScreenWidth = getPixelRect().getWidth();
		float fMapScreenHeight = getPixelRect().getHeight();
		
		tmp.d_x = ( pos.d_x - getPixelRect().d_left ) / fMapScreenWidth;
		tmp.d_y = ( pos.d_y - getPixelRect().d_top ) / fMapScreenHeight;
		return tmp;
	}
	Point KLSceneMap::ScreenPosToScenePosRelative( const Point& pos ) 
	{
		Point tmp;
		float fMapScreenWidth = getPixelRect().getWidth();
		float fMapScreenHeight = getPixelRect().getHeight();
		
		tmp.d_x = ( pos.d_x - getPixelRect().d_left ) / fMapScreenWidth - m_WindowZero.d_x;
		tmp.d_y = ( pos.d_y - getPixelRect().d_top ) / fMapScreenHeight - m_WindowZero.d_y;
		return tmp;
	}
	Point KLSceneMap::ScenePosToWindowPos( const Point& pos )const
	{
		Point tmp;
		tmp.d_x = pos.d_x / d_SceneSize.d_width;
		tmp.d_y = pos.d_y / d_SceneSize.d_height;
		return tmp;
	}

	void KLSceneMap::addPathNodeData( float fX, float fY, int nType, void* pUserData )
	{
		Point screenpos = Point( fX, fY );
		screenpos = ScenePosToWindowPos(screenpos);
		String imageName = (char*)pUserData;
		char szWindowName[ 128 ];
		static size_t nodeIndex = 0;
		++nodeIndex;
		sprintf( szWindowName, "%s_%s_%d",getName().c_str(), "pathnode", nodeIndex );

		SCENEMAP_FLAG_LIST* pNewItem = new SCENEMAP_FLAG_LIST;
		if( pNewItem )
		{
			if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) )
				pNewItem->m_pWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );
			else
				pNewItem->m_pWindow = WindowManager::getSingleton().getWindow( szWindowName );

			if( pNewItem->m_pWindow )
			{
				pNewItem->pos= screenpos;
				pNewItem->name = "";
				pNewItem->dirty = 0;

				pNewItem->m_pWindow->setMaximumSize( Size( 100, 100 ) );
				pNewItem->m_pWindow->setHookMode( Hook_Center );
				pNewItem->m_pWindow->setZoomMode( Relative );
				pNewItem->m_pWindow->setMouseLButtonHollow(true);
				pNewItem->m_pWindow->setAlwaysOnTop( true );

				const Image* pImage = PropertyHelper::stringToImage(imageName);
				if( pImage == NULL )
				{
					if( pNewItem->m_pWindow )
					{
						WindowManager::getSingleton().destroyWindow( pNewItem->m_pWindow );
					}
					delete pNewItem;
					return;
				}

				pNewItem->m_pWindow->setProperty( "Image", imageName );
				pNewItem->m_pWindow->setHookPosition( screenpos );
				pNewItem->size = pImage->getSourceTextureArea().getSize();
				
				pNewItem->m_pWindow->setSize( Absolute, pNewItem->size );
				m_pBigSceneWindow->addChildWindow( pNewItem->m_pWindow );
				pNewItem->m_pWindow->show();	
				m_aPathNode.insert(std::make_pair(nodeIndex, pNewItem));
			}
		}
	}

	void KLSceneMap::clearPathNodeData(bool destroyWindow)
	{
		RENDER_POS_LIST::iterator Iter;
		while( !m_aPathNode.empty() )
		{
			Iter = m_aPathNode.begin();
			if( destroyWindow && Iter->second->m_pWindow )
			{
				removeChildWindow( Iter->second->m_pWindow );
				WindowManager::getSingleton().destroyWindow( Iter->second->m_pWindow );
			}
			delete Iter->second;
			m_aPathNode.erase(Iter);
		}
		m_aPathNode.clear();
	}

	void KLSceneMap::setMinimapData( int nType, float fX, float fY, String& szName, size_t id, void* pUserData  )
	{
		if( pUserData == NULL )
			return;

		String imageName = (char*)pUserData;
		Point screenpos = Point( fX, fY );
		screenpos = ScenePosToWindowPos(screenpos);

		RENDER_POS_LIST::iterator Iter = m_aNpcPos.find(nType);
		if( Iter == m_aNpcPos.end() )
		{
			char szWindowName[ 128 ];
			sprintf( szWindowName, "%s_%d",getName().c_str(), nType );

			SCENEMAP_FLAG_LIST* pNewItem = new SCENEMAP_FLAG_LIST;
			if( pNewItem )
			{
				if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) )
					pNewItem->m_pWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );
				else
					pNewItem->m_pWindow = WindowManager::getSingleton().getWindow( szWindowName );

				if( pNewItem->m_pWindow )
				{
					pNewItem->pos= screenpos;
					pNewItem->name = szName;
					pNewItem->dirty = 0;

					pNewItem->m_pWindow->setMaximumSize( Size( 100, 100 ) );
					pNewItem->m_pWindow->setHookMode( Hook_Center );
					pNewItem->m_pWindow->setZoomMode( Relative );
					pNewItem->m_pWindow->setMouseLButtonHollow(false);
					pNewItem->m_pWindow->setAlwaysOnTop( true );

					const Image* pImage = PropertyHelper::stringToImage(imageName);
					if( pImage == NULL )
					{
						if( pNewItem->m_pWindow )
						{
							WindowManager::getSingleton().destroyWindow( pNewItem->m_pWindow );
						}
						delete pNewItem;
						return;
					}

					pNewItem->m_pWindow->setProperty( "Image", imageName );
					pNewItem->m_pWindow->setHookPosition( screenpos );
					pNewItem->size = pImage->getSourceTextureArea().getSize();
					pNewItem->m_pWindow->setTooltipText( szName );
					pNewItem->m_pWindow->setSize( Absolute, pNewItem->size );
					pNewItem->m_pWindow->show();	
					m_aNpcPos.insert(std::make_pair(nType, pNewItem));
				}
			}
		}
		else
		{
			SCENEMAP_FLAG_LIST *data = Iter->second;

			if( data )
			{
				data->pos= screenpos;
				data->name = szName;
				data->m_pWindow->setProperty( "Image", imageName );
				data->m_pWindow->setHookPosition( screenpos );
				data->m_pWindow->setAlwaysOnTop( true );
				const Image* pImage = PropertyHelper::stringToImage(imageName);
				if( pImage != NULL )
				{
					data->size = pImage->getSourceTextureArea().getSize();
					data->m_pWindow->setSize( Absolute, data->size );
				}
				data->m_pWindow->setTooltipText( szName );
				data->m_pWindow->show();

				if( data->dirty == 0 )
				{
					data->dirty = 1;
					if(id == 1)
						m_pBigSceneWindow->addChildWindow(data->m_pWindow);
					else
						addChildWindow( data->m_pWindow );
				}
			}
		}
	}

	void KLSceneMap::hideSceneMapData()
	{
		RENDER_POS_LIST::iterator Iter = m_aNpcPos.begin();
		for( ; Iter != m_aNpcPos.end(); ++Iter )
		{
			if( Iter->second->m_pWindow )
			{
				Iter->second->m_pWindow->hide();
			}
		}
	}

	void KLSceneMap::ClearNPCPos(bool destroyWindow)
	{
		RENDER_POS_LIST::iterator Iter;
		while( !m_aNpcPos.empty() )
		{
			Iter = m_aNpcPos.begin();
			if( destroyWindow && Iter->second->m_pWindow )
			{
				removeChildWindow( Iter->second->m_pWindow );
				WindowManager::getSingleton().destroyWindow( Iter->second->m_pWindow );
				Iter->second->m_pWindow=NULL;
			}
			delete Iter->second;
			m_aNpcPos.erase(Iter);
		}
		m_aNpcPos.clear();
	}

	void KLSceneMap::setSubmitNpcImage( const int nIndex, const CEGUI::String& imageName )
	{
		RENDER_POS_LIST::iterator Iter = m_aNpcPos.find(nIndex);
		if( Iter != m_aNpcPos.end() )
		{
			if( Iter->second )
			{
				const Image* pImage = PropertyHelper::stringToImage(imageName);
				if( pImage == NULL )
					return;

				Iter->second->size = pImage->getSourceTextureArea().getSize();
				Iter->second->m_pWindow->setProperty( "Image", imageName );
				Iter->second->m_pWindow->setHookPosition( Iter->second->pos );
				Iter->second->m_pWindow->setSize( Absolute, Iter->second->size );
				Iter->second->m_pWindow->moveToFront();
			}
		}
	}

	namespace KLSceneMapProperties
	{
		
		String PlayerImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void PlayerImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSceneMap*>(receiver)->setPlayerImage(PropertyHelper::stringToImage(value));
		}
		
		String MySelfImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void MySelfImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSceneMap*>(receiver)->setMyselfImage( value ) ;
		}

		String FlashImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void FlashImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSceneMap*>(receiver)->setFlashImage( value ) ;
		}

		String ActiveImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void ActiveImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSceneMap*>(receiver)->setActiveImage( value ) ;
		}

		String TeammateImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void TeammateImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLSceneMap*>(receiver)->setTeammateImage( value ) ;
		}
	};
 
    Window* KLScenemapFactory::createWindow(const String& name)
    {
        return new KLSceneMap(d_type, name);
    }

    void KLScenemapFactory::destroyWindow(Window* window)
    {
		delete window;
    }
};