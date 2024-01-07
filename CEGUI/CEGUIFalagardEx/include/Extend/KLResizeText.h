#pragma once
#include "FalStaticText.h"

namespace CEGUI
{

	namespace KLResizeTextProperties 
	{
		
		
		class AimWindow : public Property
		{
		public:
			AimWindow() : Property(
				"AimWindow",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		
		class AimPosition : public Property
		{
		public:
			AimPosition() : Property(
				"AimPosition",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
	}


	class KLResizeText :	public FalagardStaticText
	{
	public:

		static const utf8   WidgetTypeName[];       

		KLResizeText(const String& type, const String& name);
		~KLResizeText(void);


		void SetAimWindow( const String& strWindowName );
		void SetAimPosition( const String& strPositionName );

		Window* GetAimWindow(){ return m_pAimWindow; };
	protected:
		Window*			m_pAimWindow;
		enum POSITIONTYPE
		{
			InvalidPosition = -1,
			LeftTop = 0,
			RightTop = 1,
			RightBottom = 2,
			LeftBottom = 3,
		};
		enum LOCKTYPE
		{
			LockWidth  = 0,
			LockHeight = 1,
		};
		int				m_nAimPositionType;
		int				m_nSelfPositionType;
		int				m_nLockType;
	public:
		static KLResizeTextProperties::AimWindow     d_AimWindowPropety;
		static KLResizeTextProperties::AimPosition   d_AimPositionPropety;

		void	ResizeWindow();
	protected:
		virtual void populateRenderCache();
		virtual void onTextChanged( WindowEventArgs& e );
		virtual void onSized(WindowEventArgs& e);
		void		positionSelf();

		Size getTextSize() const; 
		float getTextHeight() const;
	};

	class FALAGARDBASE_API KLResizeTextWindowFactory : public WindowFactory
	{
	public:
		KLResizeTextWindowFactory(void) : WindowFactory(KLResizeText::WidgetTypeName) { }
		~KLResizeTextWindowFactory(void){}
		Window* createWindow(const String& name);
		void destroyWindow(Window* window);
	};
};