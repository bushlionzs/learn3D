#pragma once

namespace CEGUI
{
	class IKLSceneMapWindow
	{
	public:
		virtual const Point GetMouseScenePos() const = 0;
		virtual Point ScenePosToWindowPos( const Point& pos ) const = 0;

		virtual void setMyselfDir( const int nDirect ) = 0;
		virtual void setCameraDir( const int nDirect ) = 0;
		virtual void setMyselfPos( const Point& pos ) = 0;

		virtual void addPlayerPos( const Point& pos, const String& name ) = 0;
		virtual void Clear() = 0;

		virtual void SetSceneSize( Size size ) = 0;
		virtual void SetSceneFileName( const String& str ) = 0;
		virtual void SetZoomMode( int nMode ) = 0;

		virtual void setMinimapData( int nType, float fX, float fY, String& szName,  size_t id, void* pUserData = NULL) = 0;

		virtual void setSceneMapCenter() = 0;
		virtual void updateMinimapImage() = 0;
		virtual void setViewRadius(const int r) = 0;
		virtual void startUpdate() = 0;
		virtual void endUpdate() = 0;
		virtual void modifyPosition(float x, float y) = 0;
		
		virtual void resetReturnTimer() = 0;
		virtual void hideSceneMapData() = 0;
		virtual void setSubmitNpcImage( const int nIndex, const CEGUI::String& imageName ) = 0;
		virtual void setLeaveMap( bool bLeave ) = 0;

		virtual void ClearNPCPos(bool destroyWindow = true)	= 0;
		virtual void addPathNodeData( float fX, float fY, int nType = 19, void* pUserData = NULL ) = 0;
		virtual void clearPathNodeData(bool destroyWindow = true) = 0;
	};
};