#pragma once

#include "falmodule.h"
#include "ceguiwindowfactory.h"
#include "falstaticimage.h"
#include "IKLSceneMapWindow.h"

namespace CEGUI
{

	namespace KLSceneMapProperties
	{
		class PlayerImage: public Property
		{
		public:
			PlayerImage() : Property(
				"PlayerImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


		class MySelfImage: public Property
		{
		public:
			MySelfImage() : Property(
				"MySelfImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class FlashImage: public Property
		{
		public:
			FlashImage() : Property(
				"FlashImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class ActiveImage: public Property
		{
		public:
			ActiveImage() : Property(
				"ActiveImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class TeammateImage: public Property
		{
		public:
			TeammateImage() : Property(
				"TeammateImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}
	
	enum 
	{
		SCENEMAP_DISPLAY_MODE_FULLSCREEN = 0,	
		SCENEMAP_DISPLAY_MODE_ABSOLTE,		
	};
	
	struct SCENEMAP_FLAG_LIST;
	class  KLSceneMap :	public FalagardStaticImage, public IKLSceneMapWindow
	{
	public:

		static const utf8   WidgetTypeName[];       

		static KLSceneMapProperties::PlayerImage		d_PlayerImageProperty;		
		static KLSceneMapProperties::MySelfImage		d_MyselfImageProperty;		
		static KLSceneMapProperties::FlashImage		d_FlashImageProperty;		
		static KLSceneMapProperties::ActiveImage		d_ActiveImageProperty;		
		static KLSceneMapProperties::TeammateImage	d_TeammateImageProperty;	

		void   Close();

		virtual void onMouseMove( MouseEventArgs &e );
		virtual void onMouseButtonDown( MouseEventArgs &e );
		virtual void onMouseButtonUp( MouseEventArgs &e );
		virtual void onMouseLeaves( MouseEventArgs& e );
		virtual	void updateSelf(float elapsed); 
		virtual void onMouseEnters(MouseEventArgs& e);

		
		virtual const Point GetMouseScenePos() const { return d_MouseScenePos; };
		
		void setPlayerImage( const Image* pImage );

		void setMyselfImage( const String& name );

		void setTeammateImage(const String& name);
		void setFlashImage(const String& name);
		void setActiveImage(const String&name);
		
		virtual void startUpdate() {};
		virtual void endUpdate() {};
		
		virtual void setMyselfDir( const int nDirect );
		
		virtual void setMyselfPos( const Point& pos );
		
		virtual void setCameraDir( const int nDirect );
		
		virtual void addPlayerPos( const Point& pos, const String& name );
		
		virtual void Clear();
		
		virtual void SetSceneSize( Size size ) { d_SceneSize = size ; };
		
		virtual void SetSceneFileName( const String& str );

		virtual void SetZoomMode( int nMode );

		virtual void setMinimapData( int nType, float fX, float fY, String& szName, size_t id, void* pUserData = NULL  );
		virtual void updateMinimapImage() {};
		virtual void setViewRadius(const int r) {};
		virtual void createBackground( const String& strFileName );
		virtual void modifyPosition(float x, float y);

		virtual void hideSceneMapData();
		virtual void setSubmitNpcImage( const int nIndex, const CEGUI::String& imageName );
		virtual void resetReturnTimer() {};
		virtual void setLeaveMap( bool bLeave ) {}
		virtual void ClearNPCPos(bool destroyWindow = true);

		virtual void addPathNodeData( float fX, float fY, int nType = 19, void* pUserData = NULL );
		virtual void clearPathNodeData(bool destroyWindow = true);

		
		void reset_radarWindow();

	protected:
		virtual void	onParentSized(WindowEventArgs& e);
		const Image*	getImageByName( const String& str, Rect rect ); 

		void			SetViewByCenter( const Point& pos ); 
		Rect			GetCurrentViewRect(); 
		Point			GetCurrentCenter();
		virtual	void	setSceneMapCenter();

	protected:
		
		virtual void populateRenderCache();
	protected:

		struct SCENEMAP_FLAG_DATA
		{
			Point   pos;
			String  name;
		};
		typedef std::list< SCENEMAP_FLAG_DATA >  RENDER_POS;
		RENDER_POS	m_aPlayerPos;
		
		typedef std::map<size_t, SCENEMAP_FLAG_LIST* >  RENDER_POS_LIST;
		RENDER_POS_LIST	m_aNpcPos;			
		RENDER_POS_LIST	m_aPathNode;		

		int			d_PlayerDirect;			
		int         d_CameraDirect;
		Point		d_MyseflPos;
		bool		d_fresh;

		Image*		d_PlayerImage;
		String		d_MyselfAnimate;
		
		Window*		m_pFriendWindow[ 5 ];	
		Window*		m_pMySelfWindow;		
		Window*		m_pBackground;

		Window*		m_pBigSceneWindow;

		

		int			m_nXCount;
		int			m_nYCount;
		Point		d_MouseScenePos;
		Point		m_PlayerPos;			
		Point		m_WindowZero;			
		bool		m_bMouseIn;
		
		Size		d_SceneSize;
		
		virtual void	CreateSceneMap( const String& strFileName );
		virtual void	UpdateAllWindow();
		void			ResetPlayerWindow( int nIndex, SCENEMAP_FLAG_DATA& data );
		virtual Point	ScenePosToWindowPos( const Point& pos ) const;			
		Point			ScreenPosToScenePos( const Point& pos );				
		Point			ScreenPosToScenePosRelative( const Point& pos );		
		Point			ScreenPosToWindowPosRelative( const Point& pos );		
		Point			ScreenPosToPicPos( const Point& pos );					
		void			ResetMyself();
		virtual void	UpdateBackgroundItem();

		float m_fZoomValueX;		
		float m_fZoomValueY;		
		bool  m_bDraping;
		Point m_ptDrapOffset;
		int   m_nDisplayMode;		
		bool  m_bIsCreateSceneMap;

		
		Window* m_radarWindow[8][8]; 

	public:
		KLSceneMap( const String& type, const String& name );
		virtual ~KLSceneMap();

		static const String EventNamespace;
		static const String MouseRButtonDownCtrl;
	};

	class FALAGARDBASE_API KLScenemapFactory : public WindowFactory
    {
    public:
        KLScenemapFactory(void) : WindowFactory(KLSceneMap::WidgetTypeName) { }
        ~KLScenemapFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};