#pragma once

#include "falmodule.h"
#include "ceguiwindowfactory.h"
#include "IKLTextScrollBar.h"

#include "KLSimpleText.h"
#include <queue>

namespace CEGUI
{

	namespace KLTextScrollBarProperties
	{

		
		
		class FalagardTextScrollBarBackgroud : public Property
		{
		public:
			FalagardTextScrollBarBackgroud() : Property("BackgroudWindow","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		class FalagardTextScrollBarSpeed : public Property
		{
		public:
			FalagardTextScrollBarSpeed() : Property("ScrollSpeed","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		class FalagardTextScrollBarDirection : public Property
		{
		public:
			FalagardTextScrollBarDirection() : Property("ScrollDirection","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		
		
		class FalagardTextScrollBarText : public Property
		{
		public:
			FalagardTextScrollBarText() : Property("ScrollText","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		
		class FalagardTextScrollLoop : public Property
		{
		public:
			FalagardTextScrollLoop() : Property("ScrollLoop","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		
		class FalagardTextScrollTextColor : public Property
		{
		public:
			FalagardTextScrollTextColor() : Property("ScrollColour","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		
		class FalagardTextScrollLoopTimes : public Property
		{
		public:
			FalagardTextScrollLoopTimes() : Property("ScrollLoopTimes","Property to get/set BackgroudWindow.","")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};	
		
		
		class FalagardTextScrollBarQueueMode : public Property
		{
		public:
			FalagardTextScrollBarQueueMode() : Property("QueueMode","Property to get/set QueueMode.","")
			{}

			String get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		
		
		
		
		
		

		
		
		
		class FalagardTextScrollBarStringSpace : public Property
		{
		public:
			FalagardTextScrollBarStringSpace() : Property("StringSpace", "Property to get/set StringSpace.","")
			{}
			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	}

	class  KLTextScrollBar :	public Window, public IKLTextScrollBar
	{
	public:
		static const String EventNamespace;				
		static const String EventTextHide;

		
		static KLTextScrollBarProperties::FalagardTextScrollBarBackgroud		mScrollBarBackgroudProperty;		
		static KLTextScrollBarProperties::FalagardTextScrollBarSpeed			mScrollBarSpeedProperty;		
		static KLTextScrollBarProperties::FalagardTextScrollBarDirection		mScrollBarDirectionProperty;	
		static KLTextScrollBarProperties::FalagardTextScrollBarText			mScrollBarTextProperty;		
		static KLTextScrollBarProperties::FalagardTextScrollLoop				mScrollBarLoopProperty;
		static KLTextScrollBarProperties::FalagardTextScrollTextColor			mScrollBarTextColorProperty;		
		static KLTextScrollBarProperties::FalagardTextScrollLoopTimes			mScrollBarLoopTimesProperty;		

		
		static KLTextScrollBarProperties::FalagardTextScrollBarQueueMode		mScrollBarQueueModeProperty;		
		
		static KLTextScrollBarProperties::FalagardTextScrollBarStringSpace	mScrollBarStringSpaceProperty;


		static const utf8   WidgetTypeName[]; 
		KLTextScrollBar( const String& type, const String& name );
		virtual ~KLTextScrollBar();

		
		String getBackgroudWindowName();
		void setBackgroudWindowName(const String &name);

		void setQueueMode(bool bQueueMode);
		void pushText(const String& str);
		void setStringSpace(size_t space);
		void clearAllText();


		KLSimpleText* createTextWindow(const String& str);

		
		virtual void setScrollText(  const String& str);
		virtual void setScrollSpeed( float speed );
		virtual void setScrollDirection( int direction );
		virtual void resetState(const String &str = "");
		virtual void setLoop(bool ); 
		virtual void setTextColor(colour);
		virtual void updateSelf(float elapsed);
		virtual void setLoopTimes(size_t num);

		virtual bool testClassName_impl(const String& class_name) const;

		virtual void onTextHide(WindowEventArgs& e);

	protected:
		virtual void	onSized(WindowEventArgs& e);

	private:
		
		bool mQueueMode;
		std::list<Window*> mTextWindowQueue;
		std::list<String>  mShownTextQueue;
		size_t mTextWindowSpace;
		size_t mCurrentTextWindowTotalLength;

		Window*		mBackgroudWindow;
		Window*		mTextWindow;
		String		mBackgroudWindowName;
		float		mScrollSpeed;
		bool		mLoop;
		int			mScrollDirection;
		String		mShownText;
		float		mStartTime;
		colour		mTextColour;
		size_t		mLoopTimes;
		size_t		mCurrentLoopTimes;
		float		mTextRealLength;
		bool		mFirstTime;
		
	};

	class FALAGARDBASE_API KLTextScrollBarFactory : public WindowFactory
    {
    public:
        KLTextScrollBarFactory(void) : WindowFactory(KLTextScrollBar::WidgetTypeName) { }
        ~KLTextScrollBarFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};