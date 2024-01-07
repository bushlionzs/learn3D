#pragma once
#include "KLsimpletext.h"
#include "IKLSelfAdaptationWindow.h"

namespace CEGUI
{
	namespace KLSelfAdaptationProperties
	{
		class MaxWidth : public Property
		{
		public:
			MaxWidth() : Property(
				"MaxWidth",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		class FitType: public Property
		{
		public:
			FitType() : Property(
				"FitType",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		class FitPosition: public Property
		{
		public:
			FitPosition() : Property(
				"FitPosition",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		
		class Life : public Property
		{
		public:
			Life() : Property(
				"Life",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		
		class FadeOutTime : public Property
		{
		public:
			FadeOutTime() : Property(
				"FadeOutTime",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		
		class FadeInTime : public Property
		{
		public:
			FadeInTime() : Property(
				"FadeInTime",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		
		class TextFormted : public Property
		{
		public:
			TextFormted() : Property(
				"TextFormted",
				"",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

	};
	class FALAGARDBASE_API KLSelfAdaptationWindow : public KLSimpleText, public IKLSelfAdaptationWindow
	{
	public:
		enum SELF_FIT_TYPE
		{
			SELF_FIT_CENTER = 0,
			SELF_FIT_LEFT,
			SELF_FIT_RIGHT,
			SELF_FIT_TOP,
			SELF_FIT_BOTTOM,
			SELF_FIT_LEFTTOP,
			SELF_FIT_LEFTBOTTOM,
			SELF_FIT_RIGHTTOP,
			SELF_FIT_RIGHTBOTOM,
		};
	public:
		static const utf8   WidgetTypeName[];       
		virtual void setText( const String& text );
		virtual void postSizeChanged(void);
		virtual void	updateSelf(float elapsed);
		
		virtual void	onParentSized(WindowEventArgs& e);

		void setMaxWidth( int fWidth ) { d_maxWidth = fWidth; updateSelfSize(); };
		int getMaxWidth(void) const { return d_maxWidth; }

		void setFitType( int nType ) { m_nFitType = nType; updateSelfPosition(); };
		virtual void setCenter(const Point& pos );
		Point getCenter( void ) const { return m_ptCenter; }

		void setLife( float fLife ) { m_fLife = fLife; m_bFadeMode = true; };
		void setFadeInTime( float fTime ) { m_fFadeInTime = fTime; m_bFadeMode = true; };
		void setFadeOutTime( float fTime ) { m_fFadeOutTime = fTime; m_bFadeMode = true; };
		void setTextFormated(CEGUI::TextFormatting f){ mTextFormting = f;};

		void setChangedSize(bool change) { m_changeSize = change; }


	public:
		KLSelfAdaptationWindow(const String& type, const String& name);
		~KLSelfAdaptationWindow(void);

		static KLSelfAdaptationProperties::FitType			d_FitTypeProperty;
		static KLSelfAdaptationProperties::FitPosition		d_FitPosProperty;
		static KLSelfAdaptationProperties::MaxWidth			d_MaxWidthProperty;
		static KLSelfAdaptationProperties::Life				d_LifeProperty;
		static KLSelfAdaptationProperties::FadeOutTime		d_FadeOutProperty;
		static KLSelfAdaptationProperties::FadeInTime		d_FadeInProperty;
		static KLSelfAdaptationProperties::TextFormted		d_TextFormatedProperty;
	
	protected:
		int	  d_maxWidth;		
		Point m_ptCenter;		
		int   m_nFitType;		

		bool  m_bFadeMode;
		float m_fCurLife;
		float m_fMaxLife;
		float m_fLife;
		float m_fFadeInTime;
		float m_fFadeOutTime;
		CEGUI::TextFormatting  mTextFormting;
		Size m_mySize;

		
		bool m_bSingleLine;
		
	protected:
		
		bool  m_changeSize; 



		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLSelfAdaptationWindow")	return true;
			return Window::testClassName_impl(class_name);
		}

		virtual void updateSelfSize(void);
		virtual void updateSelfPosition(void);
	};

	class FALAGARDBASE_API KLSelfAdaptationWindowFactory : public WindowFactory
    {
    public:
        KLSelfAdaptationWindowFactory(void) : WindowFactory(KLSelfAdaptationWindow::WidgetTypeName) { }
        ~KLSelfAdaptationWindowFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}; 