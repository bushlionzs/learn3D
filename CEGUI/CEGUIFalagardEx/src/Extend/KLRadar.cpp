#include "KLradar.h"
#include "ceguiimagesetmanager.h"
#include "ceguiimageset.h"
#include "ceguiwindowmanager.h"
#include "elements\ceguistaticimage.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIKeyImageAnimation.h"
#include "math.h"
#include "elements\ceguitooltip.h"
#include "CEGUIExceptions.h"
#include "CEGUIPropertyHelper.h"
#include <algorithm>
#include "KLEventTimer.h"


namespace CEGUI
{
	const utf8 KLRadar::WidgetTypeName[] = "Falagard/Radar";
	size_t KLRadar::d_dirtyFlag = 0;
	KLRadarProperties::AlphaImage		KLRadar::d_AlphaImageProperty;	
	KLRadarProperties::IconImage			KLRadar::d_IconImageProperty;
	KLRadarProperties::AnimateImage		KLRadar::d_AnimateImageProperty;
	KLRadarProperties::AutoReset			KLRadar::d_AutoRestProperty;
	KLRadarProperties::ViewRaduis			KLRadar::d_ViewRaduisProperty;

	const float MAX_RESET_TIMER = 10;
	const int GROWP_SIZE = 5;
	const float ANGEL_1 = 3.1415926f / 180;
	const float MINIMAP_TEXTURE_SZIE = 256.0f;
	const int SCENE_MAP_ZOOMSCALE = 4;
	const int SCENE_MAP_PER_PIC = 64; 

	struct MINIMAP_FLAG_DATA
	{
		Point   pos;
		String  name;
		Size    size;
		Window* m_pWindow;
		size_t dirty;
		MINIMAP_FLAG_DATA()
		{
			pos = Point( 0,0 );
			name.clear();
			size = Size( 0,0 );
			dirty = true;
			m_pWindow = 0;
		}
		~MINIMAP_FLAG_DATA()
		{
			m_pWindow = 0;
		}
	};

	KLRadar::KLRadar(const String& type, const String& name):
		KLSceneMap( type, name )
	{
		CEGUI_START_ADD_STATICPROPERTY( KLRadar )
			CEGUI_ADD_STATICPROPERTY( &d_IconImageProperty );
			CEGUI_ADD_STATICPROPERTY( &d_AnimateImageProperty );
			CEGUI_ADD_STATICPROPERTY( &d_AutoRestProperty );
			CEGUI_ADD_STATICPROPERTY( &d_AlphaImageProperty );
			CEGUI_ADD_STATICPROPERTY( &d_ViewRaduisProperty );
		CEGUI_END_ADD_STATICPROPERTY

		m_nDisplayMode = SCENEMAP_DISPLAY_MODE_ABSOLTE; 
		m_bMouseInWindow = false;
		m_bIsAutoReset = true;

		d_AlphaName = String("");
		m_ViewRadius = 10000000;
		m_pFakeBackground = 0;
		setNeedRealTimeUpdate(true);
		
		
	}

	KLRadar::~KLRadar(void)
	{
		for( int i = 0; i < IMAGE_TYPE_NUM; i ++ )
		{
			RENDER_POS* pList = GetListByType( i );
			if( !pList )continue;
			RENDER_POS::iterator it = pList->begin();
			RENDER_POS::iterator itend = pList->end();
			while(it != itend)
			{
				MINIMAP_FLAG_DATA* data = it->second;
				m_pFakeBackground->removeChildWindow( data->m_pWindow );
				delete data;
				it++;
			}
			pList->clear();
		}
		d_AlphaName = String("");

		if(m_pFakeBackground)
		{
			WindowManager::getSingleton().destroyWindow( m_pFakeBackground );
			m_pFakeBackground = 0;
		}
		if(m_pCameraWindow)
		{
			m_pCameraWindow = 0;
		}


		clearPathNodeData(false);
	}

	void KLRadar::onMouseButtonDown( MouseEventArgs &e )
	{
		KLSceneMap::onMouseButtonDown( e );
	
		d_MouseScenePos = ScreenPosToScenePos( e.position );
		d_MouseScenePos.d_x /= m_fZoomValueX;
		d_MouseScenePos.d_y /= m_fZoomValueY;
	}

	void    KLRadar::onMouseEnters( MouseEventArgs& e )
	{
		m_bMouseInWindow = true;
		KLSceneMap::onMouseEnters( e );
	}

	void    KLRadar::onMouseLeaves( MouseEventArgs& e )
	{
		if( !isHit(e.position) )
		{
			setLeaveMap( false );
		}

		KLSceneMap::onMouseLeaves( e );
	}

	bool KLRadar::ChildMouseEnters( const EventArgs& e)
	{
		return true;
	}

	bool KLRadar::ChildMouseLeaves( const EventArgs& e)
	{
		MouseEventArgs arg( (const MouseEventArgs&)e );
		if( !isHit(arg.position) )
		{
			setLeaveMap( false );
		}

		return true;
	}


	void KLRadar::createBackground( const String& strFileName )
	{
		KLSceneMap::createBackground(strFileName);

		if(m_pFakeBackground)
		{
			
			
			clearPathNodeData();
			WindowManager::getSingleton().destroyWindow( m_pFakeBackground );
		}
		
		

		Rect rect( 0, 0, MINIMAP_TEXTURE_SZIE, MINIMAP_TEXTURE_SZIE);
		Point offset( 0, 0 );


		
		System::getSingleton().getRenderer()->initMinimapRender("none",d_AlphaName,(size_t)MINIMAP_TEXTURE_SZIE);

		m_pBackground->setVisible(false);
		uint child_count = m_pBackground->getChildCount();

		for (uint i = 0; i < child_count; ++i)
		{
			m_pBackground->getChildAtIdx(i)->setVisible(false);
		}

		char szFakeWindowName[ 128 ];
		sprintf( szFakeWindowName, "%sFakeWindow", getName().c_str() );

		if( WindowManager::getSingleton().isWindowPresent( szFakeWindowName ) ) 
		{
			WindowManager::getSingleton().destroyWindow( szFakeWindowName );
		}
		WindowManager::getSingleton().createWindow(  "DefaultWindow", szFakeWindowName );
		m_pFakeBackground = WindowManager::getSingleton().getWindow( szFakeWindowName );
		addChildWindow( m_pFakeBackground );
		m_pFakeBackground->setMaximumSize( Size( 100, 100 ) );
		m_pFakeBackground->setRiseOnClickEnabled( false );
		m_pFakeBackground->setMouseMoveHollow( true );

		
	}

	void KLRadar::onMouseMove( MouseEventArgs &e )
	{
		KLSceneMap::onMouseMove( e );

		ChildList::const_reverse_iterator	child, end;

		end = m_pFakeBackground->getDrawList()->rend();
		m_objTooltip.clear();
		for (child = m_pFakeBackground->getDrawList()->rbegin(); child != end; ++child)
		{
			if ((*child)->isVisible())
			{
				
				if( (*child)->isHit(e.position) && !(*child)->getMouseHollow() )
				{
					if( !m_objTooltip.empty() )
					{
						m_objTooltip += "\n";
					}
					m_objTooltip += (*child)->getText();
				}
			}
		}
		if( getTooltip() )
		{
			getTooltip()->setTargetWindow( this );
			setTooltipText( m_objTooltip ); 
			getTooltip()->positionSelf();
		}

	}
	
	void KLRadar::setTypeImage( int nType, const Image* pImage ) 
	{
		switch( nType )
		{
		case IMAGE_TYPE_Animy:
			d_AnimyImage = pImage;
			break;
		
		case IMAGE_TYPE_MissionNpc:
			d_MissionNpcImage = pImage;
			break;
		case IMAGE_TYPE_MissNoCompleteNpc:
			d_MissNoCompleteNpcImage = pImage;
			break;
		case IMAGE_TYPE_MissCompleteNpc:
			d_MissCompleteNpcImage = pImage;
			break;

		case IMAGE_TYPE_ExpNpc:
			d_ExpNpcImage = pImage;
			break;
		case IMAGE_TYPE_Team:
			d_TeammateImage = pImage;
			break;
		
		case IMAGE_TYPE_PKKillPlayer:
			d_PkKillPlayerImage = pImage;
			break;

		
		case IMAGE_TYPE_FamilyPlayer:
			d_FamilyPlayerImage = pImage;
			break;
		case IMAGE_TYPE_GuildPlayer:
			d_GuildPlayerImage = pImage;
			break;



		case IMAGE_TYPE_HomelandPlayer:		
			d_HomelandPlayerImage = pImage;
			break;
		case IMAGE_TYPE_NoHomelandPlayer:
			d_NoHomelandPlayerImage = pImage;
			break;

		case IMAGE_TYPE_ExpObj:
			d_ExpObjImage = pImage;
			break;
		
		
		
		case IMAGE_TYPE_Pet:
			d_PetImage = pImage;
			break;

		case IMAGE_TYPE_CircleMisionNPC:
			d_CircleMissionNpcImage = pImage;
			break;

		case IMAGE_TYPE_TransMissionNPC:
			d_TransMissionNpcImage = pImage;
			break;

		case IMAGE_TYPE_Flash:
			d_FlashImage = pImage;
			break;
		case IMAGE_TYPE_PathNode:
			d_PathNodeImage = pImage;
			break;
		case IMAGE_TYPE_PathChangeNode:
			d_PathChangeNodeImage = pImage;
			break;
		case IMAGE_TYPE_PathFinish:
			d_PathFinishImage = pImage;
			break;
		}
	}
	const Image* KLRadar::getTypeImage( int nType )
	{
		switch( nType )
		{
		case IMAGE_TYPE_Animy:
			return d_AnimyImage;
		
		case IMAGE_TYPE_MissionNpc:
			return d_MissionNpcImage;
		case IMAGE_TYPE_MissNoCompleteNpc:
			return d_MissNoCompleteNpcImage;
		case IMAGE_TYPE_MissCompleteNpc:
			return d_MissCompleteNpcImage;
		case IMAGE_TYPE_ExpNpc:
			return d_ExpNpcImage;
		case IMAGE_TYPE_Team:
			return d_TeammateImage;
		
		case IMAGE_TYPE_PKKillPlayer:
			return d_PkKillPlayerImage;
		
		case IMAGE_TYPE_FamilyPlayer:
			return d_FamilyPlayerImage;
		case IMAGE_TYPE_GuildPlayer:
			return d_GuildPlayerImage;


		case IMAGE_TYPE_HomelandPlayer:		
			return d_HomelandPlayerImage;
		case IMAGE_TYPE_NoHomelandPlayer:
			return d_NoHomelandPlayerImage;
		case IMAGE_TYPE_ExpObj:
			return d_ExpObjImage;
		
		
		case IMAGE_TYPE_Pet:
			return d_PetImage;
		case IMAGE_TYPE_CircleMisionNPC:
			return d_CircleMissionNpcImage;
		case IMAGE_TYPE_TransMissionNPC:
			return d_TransMissionNpcImage;
		case IMAGE_TYPE_MYSELF:		
			break;
		case IMAGE_TYPE_Flash:		
			return d_FlashImage;
		case IMAGE_TYPE_Active:		
			break;
		case IMAGE_TYPE_PathNode:
			return d_PathNodeImage;
		case IMAGE_TYPE_PathChangeNode:
			return d_PathChangeNodeImage;
		case IMAGE_TYPE_PathFinish:
			return d_PathFinishImage;
		}
		return NULL;
	}
	void KLRadar::setTypeName( int nType, const String& str ) 
	{
		switch( nType )
		{
		case IMAGE_TYPE_MYSELF:
			{
				d_PlayerAnimateName = str;
				break;
			}
		case IMAGE_TYPE_CAMERA:
			{
				d_CameraAnimateName = str;
				break;			
			}
		case IMAGE_TYPE_Flash:
			d_FlashAnimateName = str;
			break;
		case IMAGE_TYPE_Active:
			d_ActiveAnimateName = str;
			break;
		default:
			break;
		}
	}
	String KLRadar::getTypeName( int nType )
	{
		switch( nType )
		{
		case IMAGE_TYPE_MYSELF:
			return d_PlayerAnimateName;
		case IMAGE_TYPE_Flash:
			return d_FlashAnimateName;
		case IMAGE_TYPE_Active:
			return d_ActiveAnimateName;
		default:
			break;
		}
		return "";
	}

	void KLRadar::setAlphaImage( const String& name )
	{
		d_AlphaName = name;
	}

	
	void KLRadar::UpdateViewRect() 
	{
		SetViewByCenter( d_MyseflPos );
		
	} 

	void  KLRadar::UpdateBackgroundItem()
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
						pWindow->setPosition( Absolute, pos );
						pWindow->setSize( Absolute, size );
					}
				}
				pos.d_y += size.d_height;

			}
			pos.d_x += size.d_width; 
			pos.d_y = 0;
		}
		
		
		
		
		
		
		
		
		
		
		
	}
	void  KLRadar::UpdateAllWindow()
	{
		if( m_pBackground == NULL )
			return;

		
		
		float fMax = ( d_SceneSize.d_width > d_SceneSize.d_height ) ? d_SceneSize.d_width : d_SceneSize.d_height;
		if( m_nDisplayMode == SCENEMAP_DISPLAY_MODE_FULLSCREEN ) 
		{
			float fScale = getAbsoluteHeight() / getAbsoluteWidth();
			m_fZoomValueX = fScale * d_SceneSize.d_width / fMax ;
			m_fZoomValueY = d_SceneSize.d_height / fMax;
		}
		else 
		{
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

		m_pFakeBackground->setRect( Relative, winRect );
		m_pFakeBackground->setSize( Relative, winRect.getSize());
		m_pFakeBackground->setPosition( Relative, m_WindowZero );
		UpdateBackgroundItem();
		requestRedraw();
		d_fresh = true;
		
	}

	
	void KLRadar::CreateSceneMap( const String& strFileName )
	{
		createBackground( strFileName );

		for( int i = 0; i < IMAGE_TYPE_NUM; i ++ )
		{
			m_aPointerTimer[ i ] = 0;
			RENDER_POS* pList = GetListByType( i );
			if( !pList )continue;
			RENDER_POS::iterator it = pList->begin();
			RENDER_POS::iterator itend = pList->end();
			while(it != itend)
			{
				MINIMAP_FLAG_DATA* data =  it->second;
				if( data && data->m_pWindow )
					WindowManager::getSingleton().destroyWindow( data->m_pWindow );
				it++;
			}
			pList->clear();
		}

		char szWindowName[ 128 ];
		sprintf( szWindowName, "%s_MySelf",getName().c_str() );
		if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) )
		{
			m_pMySelfWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );		
			m_pMySelfWindow->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLRadar::ChildMouseEnters, this));
			m_pMySelfWindow->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLRadar::ChildMouseLeaves, this) );
		}

		if( m_pMySelfWindow )
		{
			
			m_pFakeBackground->addChildWindow( m_pMySelfWindow );	

			m_pMySelfWindow->setHookMode( Hook_Center );
			m_pMySelfWindow->setZoomMode( Relative );
			m_pMySelfWindow->setMaximumSize( Size( 100, 100 ) );
			m_pMySelfWindow->setMouseHollow( true );
		}


		sprintf( szWindowName, "%s_Camera",getName().c_str() );
		if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) )
		{
			m_pCameraWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );	
			m_pCameraWindow->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLRadar::ChildMouseEnters, this));
			m_pCameraWindow->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLRadar::ChildMouseLeaves, this) );
		}

		if( m_pCameraWindow )
		{
			m_pCameraWindow = WindowManager::getSingleton().getWindow( szWindowName );
			m_pFakeBackground->addChildWindow( m_pCameraWindow );	

			m_pCameraWindow->setHookMode( Hook_Center );
			m_pCameraWindow->setZoomMode( Relative );
			m_pCameraWindow->setMaximumSize( Size( 100, 100 ) );
			m_pCameraWindow->setMouseHollow( true );

		}

		m_pBackground->setMouseHollow( true );
		m_pBackground->setMouseLButtonHollow( false );
		m_pBackground->setMouseRButtonHollow( true );

		m_pMySelfWindow->setAlwaysOnTop( true );
		UpdateAllWindow();

	}
	int KLRadar::GetType( int nType )
	{
		switch( nType )
		{
		case IMAGE_TYPE_Animy:
		
		case IMAGE_TYPE_MissionNpc:
		case IMAGE_TYPE_MissNoCompleteNpc:
		case IMAGE_TYPE_MissCompleteNpc:

		case IMAGE_TYPE_ExpNpc:
		case IMAGE_TYPE_Team:
		
		case IMAGE_TYPE_PKKillPlayer:
		
		case IMAGE_TYPE_FamilyPlayer:
		case IMAGE_TYPE_GuildPlayer:

		case IMAGE_TYPE_HomelandPlayer:		
		case IMAGE_TYPE_NoHomelandPlayer:
		case IMAGE_TYPE_ExpObj:
		
		case IMAGE_TYPE_Pet:
			return POS_TYPE_IMAGE;

		case IMAGE_TYPE_Flash:
		case IMAGE_TYPE_Active:
			return POS_TYPE_ANIMATE;
		}
		return POS_TYPE_INVALIDE;
	}

	void KLRadar::startUpdate()
	{
		d_dirtyFlag++;
	}
	void KLRadar::endUpdate()
	{
		for( int i = 0; i < IMAGE_TYPE_NUM; i ++ )
		{
			RENDER_POS* pList = GetListByType( i );
			if( !pList )continue;
			RENDER_POS::iterator it = pList->begin();
			RENDER_POS::iterator itend = pList->end();
			while(it != itend)
			{
				RENDER_POS::iterator temp = it++;
				MINIMAP_FLAG_DATA* data = temp->second;

				if( data->dirty != d_dirtyFlag)
				{
					m_pFakeBackground->removeChildWindow( data->m_pWindow );
					WindowManager::getSingleton().destroyWindow( data->m_pWindow );
					delete data;
					pList->erase(temp);
				}			
			}
		}

		

		
	}

	void KLRadar::resetReturnTimer() 
	{ 
		d_ReturnTimer = 0;
	}

	void KLRadar::addPathNodeData(float fX, float fY, int nType, void* pUserData)
	{
		Point screenpos = Point( fX, fY );
		Point selfpos = screenpos - m_PlayerPos;
		
		
		if( nType != IMAGE_TYPE_PathNode && nType != IMAGE_TYPE_PathChangeNode && nType != IMAGE_TYPE_PathFinish )
			return ;

		char szWindowName[ 128 ];
		static size_t nodeIndex = 0;
		++nodeIndex;
		sprintf( szWindowName, "%s_%s_%d",getName().c_str(),"pathnode", nodeIndex );
		MINIMAP_FLAG_DATA* pNewItem = new MINIMAP_FLAG_DATA;
		if( pNewItem )
		{
			if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) )
			{
				pNewItem->m_pWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );
				pNewItem->m_pWindow->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLRadar::ChildMouseEnters, this));
				pNewItem->m_pWindow->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLRadar::ChildMouseLeaves, this) );
			}
			else
				pNewItem->m_pWindow = WindowManager::getSingleton().getWindow( szWindowName );
			if( pNewItem->m_pWindow )
			{
				pNewItem->m_pWindow->setMaximumSize( Size( 100, 100 ) );
				pNewItem->m_pWindow->setHookMode( Hook_Center );
				pNewItem->m_pWindow->setZoomMode( Relative );
				pNewItem->m_pWindow->setMouseLButtonHollow(true);

				m_pFakeBackground->addChildWindow( pNewItem->m_pWindow );					

				if( getTypeImage( nType ) )
				{
					( ( StaticImage*)( pNewItem->m_pWindow ))->setImage( getTypeImage( nType ) );
					pNewItem->size = ( getTypeImage( nType )->getSourceTextureArea() ).getSize();
				}

				screenpos = ScenePosToWindowPos(screenpos);
				pNewItem->pos= screenpos;
				pNewItem->name = "";
				pNewItem->m_pWindow->setText( "" );
				pNewItem->m_pWindow->setHookPosition( pNewItem->pos );
				pNewItem->m_pWindow->setSize( Absolute,pNewItem->size );

				pNewItem->m_pWindow->show();	
				m_aPathNode.insert(std::make_pair(nodeIndex,pNewItem));
			}
		}
	}

	void KLRadar::clearPathNodeData(bool destroyWindow)
	{
		RENDER_POS::iterator it;
		while( !m_aPathNode.empty() )
		{
			it = m_aPathNode.begin();

			if( destroyWindow && it->second->m_pWindow )
			{
				if( m_pFakeBackground )
					m_pFakeBackground->removeChildWindow( it->second->m_pWindow );
				WindowManager::getSingleton().destroyWindow( it->second->m_pWindow  );
				it->second->m_pWindow =NULL;
			}
			delete it->second;
			m_aPathNode.erase(it);
		}
		m_aPathNode.clear();
	}

	void KLRadar::setMinimapData( int nType, float fX, float fY, String& szName, size_t id, void* pUserData  )
	{
		
		Point screenpos = Point( fX, fY );
		Point selfpos = screenpos - m_PlayerPos;
		bool  bShowOutRangeTeamMember = false;
		float fNewX = 0.0f;
		float fNewY = 0.0f;
		Size ScreenRect = System::getSingleton().getRenderer()->getSize();
		int ViewRadius = (int)(ScreenRect.d_height / 768 * m_ViewRadius);
		if((selfpos.d_x*selfpos.d_x + selfpos.d_y*selfpos.d_y) >= ViewRadius * 0.5)
		{
			if( IMAGE_TYPE_Team == nType )
			{
				fNewY = (sqrtf(ViewRadius)-3.5)*selfpos.d_y/sqrtf( selfpos.d_x * selfpos.d_x + selfpos.d_y * selfpos.d_y );
				fNewX = (sqrtf(ViewRadius)-3.5)*selfpos.d_x/sqrtf( selfpos.d_x * selfpos.d_x + selfpos.d_y * selfpos.d_y );
				screenpos = Point( fNewX, fNewY ) + m_PlayerPos;
				bShowOutRangeTeamMember = true;
			}
			else
				return;
		}

		MINIMAP_FLAG_DATA *data = NULL;
		data = getMiniMapFlagData( nType, m_aPointerTimer[ nType ],id );
		
		screenpos = ScenePosToWindowPos(screenpos);
		

		if( data )
		{
			data->pos= screenpos;
			data->name = szName;
			data->m_pWindow->setText( szName );
			data->m_pWindow->setHookPosition( data->pos );
			data->m_pWindow->setWindowLayOutNum( 50 );
			if( IMAGE_TYPE_Team == nType && bShowOutRangeTeamMember == true )
			{
				const Image* pImage = GetTeamMemberArrowImage( Point(0.0f, 0.0f), Point(fNewX,fNewY) );
				if( pImage )
				{
					( ( StaticImage*)( data->m_pWindow ))->setImage( pImage );
					data->size = ( pImage->getSourceTextureArea() ).getSize();
					data->m_pWindow->setWindowLayOutNum( 1 );
				}
			}
			else
			{
				const Image* pImage = getTypeImage( nType );
				if( pImage )
				{
					( ( StaticImage*)( data->m_pWindow ))->setImage( pImage );
					data->size = ( pImage->getSourceTextureArea() ).getSize();
				}
			}
			data->m_pWindow->setSize( Absolute,data->size );
			data->m_pWindow->show();
			data->dirty = d_dirtyFlag;
			
			m_aPointerTimer[ nType ] ++;
		}
	}
	MINIMAP_FLAG_DATA*  KLRadar::getMiniMapFlagData( int nType, int nIndex,size_t id )
	{
		RENDER_POS* pList = GetListByType( nType );
		if( pList )
		{
			RENDER_POS::iterator iter = pList->find(id);
			if( iter == pList->end() )
			{			
				char szWindowName[ 128 ];
				sprintf( szWindowName, "%s_%s_%d",getName().c_str(),GetNameByType( nType ).c_str(), nIndex );
				MINIMAP_FLAG_DATA* pNewItem = new MINIMAP_FLAG_DATA;
				if( pNewItem )
				{
					if( !WindowManager::getSingleton().isWindowPresent( szWindowName ) )
					{
						pNewItem->m_pWindow = WindowManager::getSingleton().createWindow( "KylinUI/StaticImage", szWindowName );
						pNewItem->m_pWindow->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLRadar::ChildMouseEnters, this));
						pNewItem->m_pWindow->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLRadar::ChildMouseLeaves, this) );
					}
					else
						pNewItem->m_pWindow = WindowManager::getSingleton().getWindow( szWindowName );
					if( pNewItem->m_pWindow )
					{
						pNewItem->m_pWindow->setMaximumSize( Size( 100, 100 ) );
						pNewItem->m_pWindow->setHookMode( Hook_Center );
						pNewItem->m_pWindow->setZoomMode( Relative );
						pNewItem->m_pWindow->setMouseLButtonHollow(true);

						m_pFakeBackground->addChildWindow( pNewItem->m_pWindow );					
					
						if( getTypeImage( nType ) )
						{
							( ( StaticImage*)( pNewItem->m_pWindow ))->setImage( getTypeImage( nType ) );
							pNewItem->size = ( getTypeImage( nType )->getSourceTextureArea() ).getSize();
						}	
						pNewItem->m_pWindow->show();	
						pList->insert(std::make_pair(id,pNewItem));
						pNewItem->dirty = d_dirtyFlag;
						return pNewItem;
					}
				}
			}
			else
			{
				iter->second->dirty = d_dirtyFlag;
				return iter->second;
			}
		}
		return NULL;
	}
	void KLRadar::Clear()
	{
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	void KLRadar::setMyselfDir( const int nDirect )
	{
		KLSceneMap::setMyselfDir( nDirect );
		updateMyselfPos();
		updateMyselfDir();
		
		

	}

	
	void KLRadar::setMyselfPos( const Point& pos )
	{
		if( m_PlayerPos != pos )
			d_ReturnTimer = 0;
		m_PlayerPos = pos;
		d_MyseflPos = ScenePosToWindowPos( pos );
		d_fresh = true;
		updateMyselfPos(); 
		updateMyselfDir();

		
	}
	
	Point KLRadar::GetActiveArrowImagePos( Rect& rcView, Point& posStart, Point& posEnd )
	{
		Point pos;
		float fx,fy,fc,fangle;
		fx = ( posEnd.d_x - posStart.d_x );
		fy = ( posEnd.d_y - posStart.d_y );
		if( fx == 0 ) 
		{
			pos.d_x = posStart.d_x;
			if( fy > 0 )
				pos.d_y = rcView.d_bottom;
			else
				pos.d_y = rcView.d_top;
			return pos;
		}
		if( fy == 0 )
		{
			pos.d_y = posStart.d_y;
			if( fx > 0 )
				pos.d_x = rcView.d_left;
			else
				pos.d_x = rcView.d_right;
			return pos;
		}
		fangle = float( abs( fy ) ) / float( abs( fx ) );
		if( fangle < 1 ) 
		{
			if( fx < 0 )
				pos.d_x = rcView.d_left;
			else
				pos.d_x = rcView.d_right;
			fc = rcView.d_right - posStart.d_x;
			fc = abs( fc * fy / fx );
			if( fy < 0 )
				pos.d_y = posStart.d_y - fc;
			else
				pos.d_y = posStart.d_y + fc;
		}
		else if( fangle > 1 )
		{
			if( fy < 0 )
				pos.d_y = rcView.d_top;
			else
				pos.d_y = rcView.d_bottom;
			fc = rcView.d_bottom - posStart.d_y;
			fc = abs( fc * fx / fy );
			if( fx > 0 )
				pos.d_x = posStart.d_x + fc;
			else
				pos.d_x = posStart.d_x - fc;
		}
		else 
		{
			if( fx < 0 )
				pos.d_x = rcView.d_left;
			else 
				pos.d_x = rcView.d_right;
			if( fy < 0 )
				pos.d_y = rcView.d_top;
			else
				pos.d_y = rcView.d_bottom;
		}
		return pos;
	}
	
	const Image* KLRadar::GetActiveArrowImage( Rect& rcView,Point& posStart, Point& posEnd )
	{
		Point pos;
		float fx,fy,fangle;
		fx = ( posEnd.d_x - posStart.d_x );
		fy = ( posEnd.d_y - posStart.d_y );
		
		if( fx == 0 ) 
		{
			if( fy > 0 )
				fangle = 90;
			else
				fangle = 270;
		}
		else if( fy == 0 )
		{
			if( fx > 0 )
				fangle = 0;
			else
				fangle = 180;
		}
		else
		{
			fangle = atan( abs( fy / fx ) ) / ANGEL_1;
		}
		if( fx > 0 ) 
		{
			if( fy > 0 )
				fangle = 360 - fangle;
		}
		else
		{
			if( fy < 0 )
				fangle = 180 - fangle;
			else
				fangle = 180 + fangle;
		}
		KeyImageAnimation* pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_ActiveAnimateName );
		int nCurFrame = int( ( fangle * pAnimate->getFrameNumber() ) / 360 );
		return pAnimate->getFrame( nCurFrame );
	}

	const Image* KLRadar::GetTeamMemberArrowImage( Point& posStart, Point& posEnd )
	{
		Point pos;
		float fx,fy,fangle;
		fx = ( posEnd.d_x - posStart.d_x );
		fy = ( posEnd.d_y - posStart.d_y );

		if( fx == 0 ) 
		{
			if( fy > 0 )
				fangle = 90;
			else
				fangle = 270;
		}
		else if( fy == 0 )
		{
			if( fx > 0 )
				fangle = 0;
			else
				fangle = 180;
		}
		else
		{
			fangle = atan( abs( fy / fx ) ) / ANGEL_1;
		}
		if( fx > 0 ) 
		{
			if( fy > 0 )
				fangle = 360 - fangle;
		}
		else
		{
			if( fy < 0 )
				fangle = 180 - fangle;
			else
				fangle = 180 + fangle;
		}
		fangle = fangle < 270 ? fangle + 90 : fangle + 90 - 360 ;
		KeyImageAnimation* pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_PlayerAnimateName );
		int nCurFrame = int( ( fangle * pAnimate->getFrameNumber() ) / 360 );
		return pAnimate->getFrame( nCurFrame );
	}

	void KLRadar::updateMinimapImage()
	{
		
	}
		
	
	void KLRadar::updateActive()
	{
		
		static int time_now = 0;
		time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);
		Point ptCenter = GetCurrentCenter();
		Rect  rcViewRect = GetCurrentViewRect();
		
		KeyImageAnimation* pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_ActiveAnimateName );
		KeyImageAnimation* pFlashAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_FlashAnimateName );
		if( pAnimate == NULL )
			return;
		if( pFlashAnimate == NULL ) 
			return;
		Image* pImage = (Image*)( pAnimate->getFrame( 0 ) ); 
		
		Rect rcDirViewRect = rcViewRect;

		if( pImage )
		{				
			float width;
			float height;

			width = ( pImage->getSourceTextureArea().getWidth() / 2 ) / m_pBackground->getAbsoluteWidth();
			height = ( pImage->getSourceTextureArea().getHeight() / 2 ) / m_pBackground->getAbsoluteHeight();

			rcDirViewRect.d_left += width;
			rcDirViewRect.d_right -= width;
			rcDirViewRect.d_top += height;
			rcDirViewRect.d_bottom -= height;
		}

		
		RENDER_POS* pList = GetListByType( IMAGE_TYPE_Active );
		if( pList)
		{
		RENDER_POS::iterator it = pList->begin();
		RENDER_POS::iterator itend = pList->end();
		while(it != itend)
		{
			MINIMAP_FLAG_DATA* data = it->second;
			if( data )
			{
				
				if( !rcViewRect.isPointInRect( data->pos ) )
				{
					data->m_pWindow->setHookPosition( GetActiveArrowImagePos( rcDirViewRect, ptCenter, data->pos ) );
					Image* pImage = (Image*)( GetActiveArrowImage( rcViewRect, ptCenter, data->pos ) );
					if( pImage )
					{
						( ( StaticImage*)( data->m_pWindow ))->setImage( pImage );
						Size size = pImage->getSourceTextureArea().getSize();
						data->m_pWindow->setSize( Absolute, size );
						data->m_pWindow->show();
						data->m_pWindow->setMouseHollow( false );
					}
				}
				else
				{
					Image* pImage = (Image*)( pFlashAnimate->getFrame( time_now, -1 ) );
					if( pImage )
					{
						if( data )
						{
							data->m_pWindow->setHookPosition( data->pos );
							Size size = pImage->getSourceTextureArea().getSize();
							( ( StaticImage*)data->m_pWindow)->setImage( pImage );
							data->m_pWindow->setSize( Absolute, size );
							data->m_pWindow->setMouseHollow( true );
						}
					}
				}
			}
			it++;
		}
		}



	}

	void KLRadar::updateMyselfPos()
	{
		m_pMySelfWindow->setHookPosition( d_MyseflPos );
		m_pCameraWindow->setHookPosition( d_MyseflPos );
	}
	void KLRadar::updateMyselfDir()
	{
		KeyImageAnimation* pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_PlayerAnimateName );
		if( pAnimate )
		{
			int nCurFrame = ( ( d_PlayerDirect ) * pAnimate->getFrameNumber() ) / 360;
			Image* pImage = (Image*)( pAnimate->getFrame( nCurFrame ) );
			Size size;
			
			if( pImage )
			{
				size.d_width = pImage->getSourceTextureArea().getWidth();
				size.d_height = pImage->getSourceTextureArea().getHeight();
				( ( StaticImage*)( m_pMySelfWindow ))->setImage( pImage );
				m_pMySelfWindow->setSize( Absolute, size );
			}
		}

		pAnimate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate( d_CameraAnimateName );
		if( pAnimate )
		{
			int nCurFrame = ( ( d_CameraDirect ) * pAnimate->getFrameNumber() ) / 360;
			Image* pImage = (Image*)( pAnimate->getFrame( nCurFrame ) );
			Size size;

			if( pImage )
			{
				size.d_width = pImage->getSourceTextureArea().getWidth();
				size.d_height = pImage->getSourceTextureArea().getHeight();
				( ( StaticImage*)( m_pCameraWindow ))->setImage( pImage );
				m_pCameraWindow->setSize( Absolute, size );
			}
		}

	}
	void KLRadar::updateFlash()
	{
	}
	void KLRadar::updateSelf(float elapsed)
	{
		
		
		if( !m_bMouseInWindow )
			d_MouseScenePos = m_PlayerPos;

		if( m_bDraping )
		{
			d_ReturnTimer = MAX_RESET_TIMER;
			d_fresh = true;
		}
		else if( d_ReturnTimer > 0 )
		{
			if( m_bIsAutoReset )
			{
				d_ReturnTimer -= elapsed;
				if( d_ReturnTimer <= 0 )
				{
					d_ReturnTimer = 0;
					UpdateViewRect();
					d_fresh = true;
				}
			}
		}
		else
		{
			if( m_bIsAutoReset )
				UpdateViewRect();
		}

		if( m_aPointerTimer[ IMAGE_TYPE_Active ] )
			d_fresh = true;

		if( d_fresh && isVisible() )
		{
			updateFlash();
			updateActive();	
			d_fresh = false;
			requestRedraw();
		}
	}
	KLRadar::RENDER_POS* KLRadar::GetListByType( int nType )
	{
		RENDER_POS* pList = NULL;
		switch( nType )
		{
		case IMAGE_TYPE_Animy:
			pList = &m_aAnimyPos;
			break;
		
		case IMAGE_TYPE_MissionNpc:
			pList = &m_aMissionNpcPos;
			break;
		case IMAGE_TYPE_MissNoCompleteNpc:
			pList = &m_aMissNoCompleteNpcPos;
			break;
		case IMAGE_TYPE_MissCompleteNpc:
			pList = &m_aMissCompleteNpcPos;
			break;

		case IMAGE_TYPE_ExpNpc:	
			pList = &m_aExpNpcPos;
			break;
		case IMAGE_TYPE_Team:
			pList = &m_aTeammatePos;
			break;
		
		case IMAGE_TYPE_PKKillPlayer:
			pList = &m_aPkKillPlayerPos;
			break;
		
		case IMAGE_TYPE_FamilyPlayer:
			pList = &m_aFamilyPlayerPos;
			break;
		case IMAGE_TYPE_GuildPlayer:
			pList = &m_aGuildPlayerPos;
			break;



		case IMAGE_TYPE_HomelandPlayer:		
			pList = &m_aHomelandPlayerPos;
			break;
		case IMAGE_TYPE_NoHomelandPlayer:
			pList = &m_aNoHomelandPlayerPos;
			break;

		case IMAGE_TYPE_ExpObj:	
			pList = &m_aExpObjPos;
			break;
		case IMAGE_TYPE_Active:
			pList = &m_aActivePos;
			break;
		
		
		
		case IMAGE_TYPE_Flash:
			pList = &m_aFlashPos;
			break;
		case IMAGE_TYPE_Pet:
			pList = &m_aPetPos;
			break;
		case IMAGE_TYPE_CircleMisionNPC:
			pList = &m_aCircleMissionNpcPos;
			break;
		case IMAGE_TYPE_TransMissionNPC:
			pList = &m_aTransMissionNpcPos;
			break;
		default:
			break;
		}
		return pList;
	}
	int KLRadar::GetTypeByName( const String& val )
	{
		int nType = -1;
		
		if( val == (utf8*)"AnimyImage" )
		{
			nType = KLRadar::IMAGE_TYPE_Animy;
		}
		
		else if( val == ( utf8*)"MissionNpcImage" )
		{
			nType = KLRadar::IMAGE_TYPE_MissionNpc;
		}
		else if( val == ( utf8*)"MissNoCompleteNpcImage" )
		{
			nType = KLRadar::IMAGE_TYPE_MissNoCompleteNpc;
		}
		else if( val == ( utf8*)"MissCompleteNpcImage" )
		{
			nType = KLRadar::IMAGE_TYPE_MissCompleteNpc;
		}

		else if( val == ( utf8*)"ExpNpcImage" )
		{
			nType = KLRadar::IMAGE_TYPE_ExpNpc;
		}
		else if( val == ( utf8*)"TeammateImage" )
		{
			nType = KLRadar::IMAGE_TYPE_Team;
		}
		
		else if( val == ( utf8* )"PKKillPlayerImage" )
		{
			nType = KLRadar::IMAGE_TYPE_PKKillPlayer;
		}
		
		else if( val == (utf8*)"FamilyPlayerImage" )
		{
			nType = KLRadar::IMAGE_TYPE_FamilyPlayer;
		}
		else if( val == (utf8*)"GuildPlayerImage" )
		{
			nType = KLRadar::IMAGE_TYPE_GuildPlayer;
		}




		else if( val == (utf8*)"HomelandPlayerImage" )
		{
			nType = KLRadar::IMAGE_TYPE_HomelandPlayer;
		}
		else if( val == (utf8*)"NoHomelandPlayerImage" )
		{
			nType = KLRadar::IMAGE_TYPE_NoHomelandPlayer;
		}
		else if( val == ( utf8*)"ObjImage" )	
		{
			nType = KLRadar::IMAGE_TYPE_ExpObj;
		}
		else if( val == ( utf8*)"ActiveImage" )
		{
			nType = KLRadar::IMAGE_TYPE_Active;
		}
		
		
		
		
		else if( val == ( utf8*)"FlashImage" )
		{
			nType = KLRadar::IMAGE_TYPE_Flash;
		}
		else if( val == ( utf8*)"PetImage" )
		{
			nType = KLRadar::IMAGE_TYPE_Pet;
		}
		
		else if( val == ( utf8*)"CircleMissionNpcImage")
		{
			nType = KLRadar::IMAGE_TYPE_CircleMisionNPC;
		}
		
		else if( val == ( utf8*)"TransMissionNpcImage")
		{
			nType = KLRadar::IMAGE_TYPE_TransMissionNPC;
		}
		else if( val == ( utf8*)"MySelfImage" )
		{
			nType = KLRadar::IMAGE_TYPE_MYSELF;
		}
		else if( val == ( utf8*)"CameraImage" )
		{
			nType = KLRadar::IMAGE_TYPE_CAMERA;
		}
		else if( val == ( utf8*)"PathNodeImage" )
		{
			nType = KLRadar::IMAGE_TYPE_PathNode;
		}
		else if( val == ( utf8*)"PathChangeNodeImage" )
		{
			nType = KLRadar::IMAGE_TYPE_PathChangeNode;
		}
		else if( val == ( utf8*)"PathFinishImage" )
		{
			nType = KLRadar::IMAGE_TYPE_PathFinish;
		}
		return nType;
	}

	void  KLRadar::drawSelf(float z)
	{
		

		
		
		{
			
			uint child_count = m_pBackground->getChildCount();
			for (uint i = 0; i < child_count; ++i)
			{
				Window *childWindow = m_pBackground->getChildAtIdx(i);
				if(childWindow->getPixelRect().getWidth() > 0.0f && childWindow->getPixelRect().getHeight() > 0.0f)
				{
					Rect mother_rect = m_pBackground->getPixelRect();

					Rect backgroundRect = Rect(Point(0,0), childWindow->getAbsoluteSize());
					const Texture* tex = static_cast<StaticImage *>(childWindow)->getImage()->getImageset()->getTexture();

					Rect final_rect = childWindow->getPixelRect();
					Rect vertex_rect = final_rect;

					final_rect.offset(Point(-childWindow->getUnclippedPixelRect().d_left,-childWindow->getUnclippedPixelRect().d_top));
					Rect  tex_rect(final_rect.d_left/backgroundRect.getWidth(),
						final_rect.d_top/backgroundRect.getHeight(),
						final_rect.d_right/backgroundRect.getWidth(),
						final_rect.d_bottom/backgroundRect.getHeight());

					final_rect.d_left = vertex_rect.d_left - mother_rect.d_left;
					final_rect.d_right = vertex_rect.d_right - mother_rect.d_left;
					final_rect.d_top = vertex_rect.d_top - mother_rect.d_top;
					final_rect.d_bottom = vertex_rect.d_bottom - mother_rect.d_top;

					Rect alpha_rect;	
					alpha_rect.d_left	= final_rect.d_left/mother_rect.getWidth();
					alpha_rect.d_right	= final_rect.d_right/mother_rect.getWidth();
					alpha_rect.d_top		= final_rect.d_top/mother_rect.getHeight();
					alpha_rect.d_bottom	= final_rect.d_bottom/mother_rect.getHeight();

					System::getSingleton().getRenderer()->addMinimapQuad(alpha_rect,tex_rect,vertex_rect,tex,z);
					
					
					
					
					

				}

			}

			
			child_count = m_pFakeBackground->getChildCount();
			for (uint i = 0; i < child_count; ++i)
			{
				Window *childWindow = m_pFakeBackground->getChildAtIdx(i);
				if(childWindow->getPixelRect().getWidth() > 0.0f && childWindow->getPixelRect().getHeight() > 0.0f)
				{
					Rect mother_rect = m_pFakeBackground->getPixelRect();
					Rect final_rect = childWindow->getPixelRect();
					int	 x0	= ( mother_rect.d_left + mother_rect.d_right ) / 2;
					int	 y0 = ( mother_rect.d_top + mother_rect.d_bottom ) / 2;

					if(final_rect.d_left > x0 && final_rect.d_top > y0)
					{
						if( (final_rect.d_right - x0)*(final_rect.d_right - x0) + (final_rect.d_bottom - y0)*(final_rect.d_bottom - y0) > ((mother_rect.d_right - mother_rect.d_left)/2 - 5)*((mother_rect.d_right - mother_rect.d_left)/2 - 5) )
							childWindow->setVisible(false);
						else
							childWindow->setVisible(true);
					}
					else
					{
						if( (final_rect.d_left - x0)*(final_rect.d_left - x0) + (final_rect.d_top - y0)*(final_rect.d_top - y0) > ((mother_rect.d_right - mother_rect.d_left)/2 - 5)*((mother_rect.d_right - mother_rect.d_left)/2 - 5) )
							childWindow->setVisible(false);
						else
							childWindow->setVisible(true);
					}

					if( childWindow->getWindowLayOutNum() == 1 )
						childWindow->setVisible(true);
				}
			}

			
		}
		
		
		
		
		
		
		
		
		
	}

	String	KLRadar::GetNameByType( int nType )
	{
		switch( nType )
		{
		case IMAGE_TYPE_Animy:
			return (utf8*)"AnimyImage";
		
		case IMAGE_TYPE_MissionNpc:
			return  (utf8*)"MissionNpcImage";
		case IMAGE_TYPE_MissNoCompleteNpc:
			return  (utf8*)"MissNoCompleteNpcImage";
		case IMAGE_TYPE_MissCompleteNpc:
			return  (utf8*)"MissCompleteNpcImage";
		case IMAGE_TYPE_ExpNpc:
			return  (utf8*)"ExpNpcImage";
		case IMAGE_TYPE_Team:
			return ( utf8*)"TeammateImage";
		
		case IMAGE_TYPE_PKKillPlayer:
			return (utf8*)"PKKillPlayerImage";
		
		case IMAGE_TYPE_FamilyPlayer:
			return (utf8*)"FamilyPlayerImage";
		case IMAGE_TYPE_GuildPlayer:
			return (utf8*)"GuildPlayerImage";


		case IMAGE_TYPE_HomelandPlayer:		
			return (utf8*)"HomelandPlayerImage";
		case IMAGE_TYPE_NoHomelandPlayer:
			return (utf8*)"NoHomelandPlayerImage";
		case IMAGE_TYPE_ExpObj:
			return ( utf8*)"PlayerImage";
		case IMAGE_TYPE_Active:
			return ( utf8*)"ActiveImage";
		
		
		case IMAGE_TYPE_Flash:
			return (utf8*)"FlashImage";
		case IMAGE_TYPE_Pet:
			return (utf8*)"PetImage";
		case IMAGE_TYPE_CircleMisionNPC:
			return (utf8*)"CircleMissionNpcImage";
		case IMAGE_TYPE_TransMissionNPC:
			return (utf8*)"TransMissionNpcImage";
		case IMAGE_TYPE_MYSELF:
			return ( utf8*)"MySelfImage";
		}
		return "";
	}

	void KLRadar::setLeaveMap( bool bLeave )
	{
		 m_bDraping = bLeave;
		m_bMouseInWindow = bLeave;
		if( !bLeave )
			d_MouseScenePos = m_PlayerPos;
	}

	namespace KLRadarProperties
	{
		
		String AlphaImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void AlphaImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLRadar*>(receiver)->setAlphaImage( value ) ;
		}
		String IconImage::get( const PropertyReceiver* receiver) const
		{
			return "";
		}

		void IconImage::set( PropertyReceiver* receiver, const String& value) 
		{
			char szType[ 128 ];
			char szSet[ 128 ];
			char szImage[ 128 ];
			sprintf( szSet, "" );
			sprintf( szType, "" );
			sprintf( szImage, "" );
			sscanf( value.c_str(), "type:%127s set:%127s image:%127s", szType, szSet, szImage );
			const Image* pImage = ImagesetManager::getSingleton().getImageset( szSet )->getImage( szImage );
			int nType = ( static_cast<KLRadar*>(receiver) )->GetTypeByName( (utf8*)szType );
			static_cast< KLRadar*>(receiver)->setTypeImage( nType, pImage );
		}

		String AnimateImage::get( const PropertyReceiver* receiver) const
		{
			return "";
		}

		void AnimateImage::set( PropertyReceiver* receiver, const String& value) 
		{
			char szType[ 128 ];
			char szAnimate[ 128 ];
			sprintf( szType, "" );
			sprintf( szAnimate, "" );
			sscanf( value.c_str(), "type:%127s animate:%127s", szType, szAnimate);
			int nType = static_cast<KLRadar*>(receiver)->GetTypeByName( (utf8*)szType );
			static_cast< KLRadar*>(receiver)->setTypeName( nType, szAnimate );
		}

		String AutoReset::get( const PropertyReceiver* receiver) const
		{
			return "";
		}

		void AutoReset::set( PropertyReceiver* receiver, const String& value) 
		{
			static_cast< KLRadar*>(receiver)->setAutoReset( PropertyHelper::stringToBool( value ) );
		}

		String ViewRaduis::get( const PropertyReceiver* receiver) const
		{
			return "";
		}

		void ViewRaduis::set( PropertyReceiver* receiver, const String& value) 
		{
			static_cast< KLRadar*>(receiver)->setViewRadius( PropertyHelper::stringToInt( value ) );
		}
	}

    
    Window* KLRadarFactory::createWindow(const String& name)
    {
        return new KLRadar(d_type, name);
    }

    void KLRadarFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}