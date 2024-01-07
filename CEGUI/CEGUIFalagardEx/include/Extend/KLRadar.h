#pragma once

#include "falmodule.h"
#include "KLscenemap.h"

namespace CEGUI
{
	namespace KLRadarProperties
	{
		class IconImage: public Property
		{
		public:
			IconImage() : Property(
				"IconImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class AnimateImage: public Property
		{
		public:
			AnimateImage() : Property(
				"AnimateImage",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class AutoReset: public Property
		{
		public:
			AutoReset() : Property(
				"AutoReset",
				"Property to get/set Minimap name status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		
		class AlphaImage: public Property
		{
		public:
			AlphaImage() : Property(
				"AlphaImage",
				"Property to get/set the background texture.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

		class ViewRaduis: public Property
		{
		public:
			ViewRaduis() : Property(
				"ViewRaduis",
				"Property to get/set the background texture.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}
	
	struct MINIMAP_FLAG_DATA;
	class KLRadar : public KLSceneMap
	{
		enum MINIMAP_IMAGE_TYPE
		{
			IMAGE_TYPE_Animy			= 0,	
			
			IMAGE_TYPE_MissionNpc		= 1,
			IMAGE_TYPE_MissNoCompleteNpc= 2,
			IMAGE_TYPE_MissCompleteNpc	= 3,
			IMAGE_TYPE_ExpNpc			= 4,	
			IMAGE_TYPE_Team				= 5,	
			
			IMAGE_TYPE_PKKillPlayer		= 6,	
			IMAGE_TYPE_FamilyPlayer		= 7,	
			IMAGE_TYPE_GuildPlayer		= 8,	

			IMAGE_TYPE_HomelandPlayer	= 9,	
			IMAGE_TYPE_NoHomelandPlayer	= 10,	

			IMAGE_TYPE_ExpObj			= 11,	
			IMAGE_TYPE_Active			= 12,	
			
			IMAGE_TYPE_Flash			= 13,	
			IMAGE_TYPE_Pet				= 14,	

			IMAGE_TYPE_CircleMisionNPC	= 17,	
			IMAGE_TYPE_TransMissionNPC	= 18,	

			IMAGE_TYPE_NUM,
			IMAGE_TYPE_MYSELF,
			IMAGE_TYPE_CAMERA,
			IMAGE_TYPE_PathNode			= 30,	
			IMAGE_TYPE_PathChangeNode	= 31,	
			IMAGE_TYPE_PathFinish		= 32,	
		};
		
		enum MINIMAP_POS_TYPE
		{
			POS_TYPE_INVALIDE = -1,
			POS_TYPE_IMAGE = 0,
			POS_TYPE_ANIMATE,
		};

		const Image*		d_AnimyImage;				
		
		const Image*		d_MissionNpcImage;			
		const Image*		d_MissNoCompleteNpcImage;	
		const Image*		d_MissCompleteNpcImage;		

		const Image*		d_CircleMissionNpcImage;	
		const Image*		d_TransMissionNpcImage;		

		const Image*		d_ExpNpcImage;				
		const Image*		d_TeammateImage;			
		
		const Image*		d_PkKillPlayerImage;		
		const Image*		d_FamilyPlayerImage;		
		const Image*		d_GuildPlayerImage;			

		const Image*		d_HomelandPlayerImage;		
		const Image*		d_NoHomelandPlayerImage;	

		const Image*		d_ExpObjImage;				
		const Image*		d_MyselfImage;				
		const Image*		d_PetImage;					
		
		const Image*		d_FlashImage;				
		const Image*		d_PathNodeImage;			
		const Image*		d_PathChangeNodeImage;		
		const Image*		d_PathFinishImage;			

		String				d_PlayerAnimateName;		
		String				d_ActiveAnimateName;		
		String				d_FlashAnimateName;			
		String				d_CameraAnimateName;		

		typedef std::map<size_t, MINIMAP_FLAG_DATA* >  RENDER_POS;


		int			m_aPointerTimer[ IMAGE_TYPE_NUM ];	

		RENDER_POS			m_aAnimyPos;				
		
		RENDER_POS			m_aMissionNpcPos;			
		RENDER_POS			m_aMissNoCompleteNpcPos;	
		RENDER_POS			m_aMissCompleteNpcPos;		

		RENDER_POS			m_aCircleMissionNpcPos;		
		RENDER_POS			m_aTransMissionNpcPos;		

		RENDER_POS			m_aExpNpcPos;				
		RENDER_POS			m_aTeammatePos;				
		
		RENDER_POS			m_aPkKillPlayerPos;			
		
		RENDER_POS			m_aFamilyPlayerPos;			
		RENDER_POS			m_aGuildPlayerPos;			

		RENDER_POS			m_aHomelandPlayerPos;		
		RENDER_POS			m_aNoHomelandPlayerPos;		
														
		RENDER_POS			m_aExpObjPos;				
		RENDER_POS  		m_aScenePos;				
		RENDER_POS  		m_aActivePos;				
		RENDER_POS  		m_aFlashPos;				
		RENDER_POS  		m_aPetPos;					

		RENDER_POS			m_aPathNode;				

		float				d_ReturnTimer;				
		String				m_objTooltip;

		bool				m_bMouseInWindow;

		bool				m_bIsAutoReset;

		
		
		Window*				m_pFakeBackground;
		String				d_AlphaName;
		Window*				m_pCameraWindow;
		int					m_ViewRadius;
		
		

		struct MinimapWindowParameter
		{
			Rect d_alpha;
			Rect d_texture;
			Rect d_vertex;
			const Texture  *d_tex;
		};
		
		
	public:
		static const utf8   WidgetTypeName[];       
		static size_t d_dirtyFlag;
	public:
		KLRadar(const String& type, const String& name);
		~KLRadar(void);

	public:
		void		 setTypeImage( int nType, const Image* pImage ); 
		const Image* getTypeImage( int nType );

		void		 setTypeName( int nType, const String& str ); 
		String		 getTypeName( int nType );

		void		 setAlphaImage( const String& name );

		virtual	void updateSelf(float elapsed); 
		
		void		 UpdateViewRect(); 

		int			 GetTypeByName( const String& str );
		String		 GetNameByType( int nType );

		void		 setAutoReset( bool bAutoReset ){ m_bIsAutoReset = bAutoReset; };

		RENDER_POS*  GetListByType( int nType );

		virtual void drawSelf(float z);
		virtual void setViewRadius(const int r) {m_ViewRadius = r*r;}
		virtual int  getViewRadius() {return m_ViewRadius;}
		virtual void modifyPosition(float x, float y) {}
	public:
		virtual void setMinimapData( int nType, float fX, float fY, String& szName, size_t id, void* pUserData = NULL  );
		virtual void hideSceneMapData() {}
		virtual void Clear();
		
		virtual void setMyselfPos( const Point& pos );
		virtual void setMyselfDir( const int nDirect );

		virtual void CreateSceneMap( const String& strFileName );
		virtual void UpdateAllWindow();
		virtual void UpdateBackgroundItem();

		virtual void onMouseMove( MouseEventArgs &e );
		virtual void onMouseEnters( MouseEventArgs& e );
		virtual void onMouseLeaves( MouseEventArgs& e );
		virtual void onMouseButtonDown( MouseEventArgs &e );

		bool	ChildMouseEnters( const EventArgs& e);
		bool	ChildMouseLeaves( const EventArgs& e);

		virtual void createBackground( const String& strFileName );
		virtual void updateMinimapImage();

		virtual void startUpdate();
		virtual void endUpdate();

		virtual void resetReturnTimer();
		virtual void setLeaveMap( bool bLeave );

		virtual void addPathNodeData( float fX, float fY, int nType = 19, void* pUserData = NULL );
		virtual void clearPathNodeData(bool destroyWindow = true);
		
	public:
		static KLRadarProperties::AlphaImage		d_AlphaImageProperty;		
		static KLRadarProperties::IconImage			d_IconImageProperty;
		static KLRadarProperties::AnimateImage		d_AnimateImageProperty;
		static KLRadarProperties::AutoReset			d_AutoRestProperty;
		static KLRadarProperties::ViewRaduis			d_ViewRaduisProperty;
	private:
		void updateFlash();
		void updateActive();
		void updateMyselfDir();
		void updateMyselfPos();
		MINIMAP_FLAG_DATA*  getMiniMapFlagData( int nType, int nIndex, size_t id );

		int GetType( int nType );

		Point GetActiveArrowImagePos( Rect& rcView, Point& posStart, Point& posEnd );
		const Image* GetActiveArrowImage( Rect& rcView, Point& posStart, Point& posEnd );
		const Image* GetTeamMemberArrowImage( Point& posStart, Point& posEnd );
	};

	class FALAGARDBASE_API KLRadarFactory : public WindowFactory
    {
    public:
        KLRadarFactory(void) : WindowFactory(KLRadar::WidgetTypeName) { }
        ~KLRadarFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}