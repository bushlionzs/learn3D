#include "KLTextScrollBar.h"
#include "ceguiPropertyHelper.h"
#include "ceguiimagesetmanager.h"
#include "ceguiimageset.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "ceguiwindowmanager.h"
#include "ceguitexture.h"
#include "CEGUIExceptions.h"
#include "KLSimpleText.h"

namespace CEGUI
{
	const utf8 KLTextScrollBar::WidgetTypeName[] = "Falagard/TextScrollBar";
	KLTextScrollBarProperties::FalagardTextScrollBarBackgroud		KLTextScrollBar::mScrollBarBackgroudProperty;		
	KLTextScrollBarProperties::FalagardTextScrollBarSpeed		KLTextScrollBar::mScrollBarSpeedProperty;		
	KLTextScrollBarProperties::FalagardTextScrollBarDirection		KLTextScrollBar::mScrollBarDirectionProperty;	
	KLTextScrollBarProperties::FalagardTextScrollBarText		KLTextScrollBar::mScrollBarTextProperty;		
	KLTextScrollBarProperties::FalagardTextScrollLoop		KLTextScrollBar::mScrollBarLoopProperty;		
	KLTextScrollBarProperties::FalagardTextScrollTextColor		KLTextScrollBar::mScrollBarTextColorProperty;		
	KLTextScrollBarProperties::FalagardTextScrollLoopTimes		KLTextScrollBar::mScrollBarLoopTimesProperty;	

	
	KLTextScrollBarProperties::FalagardTextScrollBarQueueMode		KLTextScrollBar::mScrollBarQueueModeProperty;		
	
	KLTextScrollBarProperties::FalagardTextScrollBarStringSpace   KLTextScrollBar::mScrollBarStringSpaceProperty;

	const String KLTextScrollBar::EventNamespace("Falagard/TextScrollBar");
	const String KLTextScrollBar::EventTextHide((utf8*)"TextHide");

	namespace KLTextScrollBarProperties
	{
		String   FalagardTextScrollBarBackgroud::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollBarBackgroud::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setBackgroudWindowName(value);
		}


		String   FalagardTextScrollBarSpeed::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollBarSpeed::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setScrollSpeed(PropertyHelper::stringToFloat(value));
		}


		String   FalagardTextScrollBarDirection::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollBarDirection::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setScrollDirection(PropertyHelper::stringToInt(value));
		}


		String   FalagardTextScrollBarText::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollBarText::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setScrollText(value);
		}


		String   FalagardTextScrollLoop::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollLoop::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setLoop(PropertyHelper::stringToBool(value));
		}

		String   FalagardTextScrollTextColor::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollTextColor::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setTextColor(PropertyHelper::stringToColour(value));
		}

		String   FalagardTextScrollLoopTimes::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollLoopTimes::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setLoopTimes(PropertyHelper::stringToUint(value));
		}

		
		String FalagardTextScrollBarQueueMode::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollBarQueueMode::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setQueueMode(PropertyHelper::stringToBool(value));
		}
		
		
		
		
		
		
		
		
		String FalagardTextScrollBarStringSpace::get(const PropertyReceiver* receiver) const
		{
			return "";
		}
		void   FalagardTextScrollBarStringSpace::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLTextScrollBar*>(receiver)->setStringSpace(PropertyHelper::stringToUint(value));
		}
		
	}

	KLTextScrollBar::KLTextScrollBar(const String& type, const String& name) :
		Window(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLTextScrollBar )
			CEGUI_ADD_STATICPROPERTY( &mScrollBarBackgroudProperty );
			CEGUI_ADD_STATICPROPERTY( &mScrollBarSpeedProperty );
			CEGUI_ADD_STATICPROPERTY( &mScrollBarDirectionProperty );
			CEGUI_ADD_STATICPROPERTY( &mScrollBarTextProperty );
			CEGUI_ADD_STATICPROPERTY( &mScrollBarLoopProperty );
			CEGUI_ADD_STATICPROPERTY( &mScrollBarTextColorProperty );
			CEGUI_ADD_STATICPROPERTY( &mScrollBarLoopTimesProperty );
		CEGUI_END_ADD_STATICPROPERTY
		mBackgroudWindow = 0;
		mTextWindow = 0;
		mBackgroudWindowName = "";
		mScrollSpeed = 0.1f;
		mLoop = false;
		mScrollDirection = 1;
		mStartTime = 0;
		mTextRealLength = 0;
		mFirstTime = true;
		mTextColour = colour(1.0f, 0.0f, 0.0f, 1.0f);
		mLoopTimes = 0;
		mCurrentLoopTimes = 0; 
		setNeedRealTimeUpdate(true);

		
		mQueueMode = false;
		mTextWindowSpace = 10;
		mCurrentTextWindowTotalLength = 0;
	}

	KLTextScrollBar::~KLTextScrollBar()
	{
		
		
		
		
	}
	

	String KLTextScrollBar::getBackgroudWindowName()
	{
		return mBackgroudWindowName;
	}

	void KLTextScrollBar::setBackgroudWindowName(const String &name)
	{
		mBackgroudWindowName = name;
	}

	void KLTextScrollBar::setScrollText(  const String& str)
	{
		mShownText = str;

		const Font* font = getFont();

		
		if (font == 0)
			throw GenericException((utf8*)"KLTextScrollBar::setScrollText + Please Set up the font");

		Size sz = font->getLineSize(mShownText);
		mTextRealLength = sz.d_width+5.0f;
	}
	void KLTextScrollBar::setScrollSpeed( float speed )
	{
		mScrollSpeed = speed;
	}
	void KLTextScrollBar::setScrollDirection( int direction )
	{
		
		
		mScrollDirection = 1;
	}
	void KLTextScrollBar::resetState(const String& str)
	{
		if(mQueueMode)
		{
		}
		else
		{
			if(str.size())
			{
				mShownText = str;
				setScrollText(mShownText);
			}
			if(mBackgroudWindowName.empty())
			{
				throw GenericException((utf8*)"KLTextScrollBar::resetState + Please make sure backgroundname");
			}
			if(mTextWindow)
			{
				WindowManager::getSingleton().destroyWindow( mTextWindow );
			}
			char WindowName[ 128 ];
			sprintf( WindowName, "%sTextWindow", getName().c_str() );
			mTextWindow = WindowManager::getSingleton().createWindow("KylinUI/SimpleText", WindowName );
			mTextWindow->setClippedByParent(true);
			mTextWindow->setFont(getFont());

			if( d_mouseHollow )
			{
				mTextWindow->setMouseHollow(d_mouseHollow);
			}
			if( d_mouseMoveHollow )
			{
				mTextWindow->setMouseMoveHollow(d_mouseMoveHollow);
			}
			if( d_mouseLButtonHollow )
			{
				mTextWindow->setMouseLButtonHollow(d_mouseLButtonHollow);
			}
			if( d_mouseRButtonHollow )
			{
				mTextWindow->setMouseRButtonHollow(d_mouseRButtonHollow);
			}

			if(!mBackgroudWindow)
			{
				mBackgroudWindow = WindowManager::getSingleton().getWindow( mBackgroudWindowName );
			}
			mBackgroudWindow->addChildWindow(mTextWindow);
			if( d_mouseHollow )
			{
				mBackgroudWindow->setMouseHollow(d_mouseHollow);
			}
			if( d_mouseMoveHollow )
			{
				mBackgroudWindow->setMouseMoveHollow(d_mouseMoveHollow);
			}
			if( d_mouseLButtonHollow )
			{
				mBackgroudWindow->setMouseLButtonHollow(d_mouseLButtonHollow);
			}
			if( d_mouseRButtonHollow )
			{
				mBackgroudWindow->setMouseRButtonHollow(d_mouseRButtonHollow);
			}

			KLSimpleText *window = static_cast<KLSimpleText *>(mTextWindow);		
			if(mScrollDirection)
				window->setPosition(Relative,Point(1.0f,0.2f));
			else
				window->setPosition(Relative,Point(0.0f,0.2f));
			window->setIgnoreMaxSizeFlag(true);
			window->setHeight(Relative,1.0f);
			window->setWidth(Absolute,mTextRealLength);
			window->setVerticalFormatting(KLSimpleText::TopAligned);
			window->setHorizontalFormatting(KLSimpleText::LeftAligned);
			window->setTextColor(mTextColour);
			window->setText(mShownText);
			mCurrentLoopTimes = 0;
			mFirstTime = true;
		}
	}

	void KLTextScrollBar::onSized(WindowEventArgs& e)
	{
		Window::onSized(e);

		if( !mTextWindow )
			return;

		Size curSize = System::getSingleton().getRenderer()->getSize();
		Size oldSize = System::getSingleton().getRenderer()->getOldSize();
		float scale = curSize.d_width / oldSize.d_width;
		
		
		
		
		
		
		const Font* font = getFont();
		if (font == 0)
			throw GenericException((utf8*)"KLTextScrollBar::setScrollText + Please Set up the font");
		Size sz = font->getLineSize(mShownText);
		mTextRealLength = sz.d_width+5.0f;
		mTextWindow->setWidth(Absolute, mTextRealLength);
	}

	void KLTextScrollBar::setLoop(bool flag)
	{
		mLoop = flag;
	}
	void KLTextScrollBar::setTextColor(colour c)
	{
		mTextColour = c;
	}
	void KLTextScrollBar::setLoopTimes(size_t num)
	{
		mLoopTimes = num;
	}
	KLSimpleText* KLTextScrollBar::createTextWindow(const String& str)
	{
		static int idx = 0;
		Window*	 pWindow = NULL;
		char WindowName[128];
		sprintf( WindowName, "%s_QueueText_%d", getName().c_str(), idx++ );
		pWindow = WindowManager::getSingleton().createWindow("KylinUI/SimpleText", WindowName );
		pWindow->setClippedByParent(true);
		pWindow->setFont(getFont());

		if( d_mouseHollow )
		{
			pWindow->setMouseHollow(d_mouseHollow);
		}
		if( d_mouseMoveHollow )
		{
			pWindow->setMouseMoveHollow(d_mouseMoveHollow);
		}
		if( d_mouseLButtonHollow )
		{
			pWindow->setMouseLButtonHollow(d_mouseLButtonHollow);
		}
		if( d_mouseRButtonHollow )
		{
			pWindow->setMouseRButtonHollow(d_mouseRButtonHollow);
		}

		if(!mBackgroudWindow)
		{
			mBackgroudWindow = WindowManager::getSingleton().getWindow( mBackgroudWindowName );
		}
		mBackgroudWindow->addChildWindow(pWindow);
		if( d_mouseHollow )
		{
			mBackgroudWindow->setMouseHollow(d_mouseHollow);
		}
		if( d_mouseMoveHollow )
		{
			mBackgroudWindow->setMouseMoveHollow(d_mouseMoveHollow);
		}
		if( d_mouseLButtonHollow )
		{
			mBackgroudWindow->setMouseLButtonHollow(d_mouseLButtonHollow);
		}
		if( d_mouseRButtonHollow )
		{
			mBackgroudWindow->setMouseRButtonHollow(d_mouseRButtonHollow);
		}

		KLSimpleText *window = static_cast<KLSimpleText *>(pWindow);

		const Font* font = getFont();
		Size sz = font->getLineSize(str);
		int width = sz.d_width + mTextWindowSpace;
		window->setWidth(Absolute, width);
		
		
		if(mScrollDirection)
		{
			window->setPosition(Relative,Point(1.0f,0.2f));
		}
		else
		{
			window->setPosition(Relative,Point(0.0f,0.2f));
		}

		window->setIgnoreMaxSizeFlag(true);
		window->setHeight(Relative,1.0f);
		window->setVerticalFormatting(KLSimpleText::TopAligned);
		window->setHorizontalFormatting(KLSimpleText::LeftAligned);
		window->setTextColor(mTextColour);
		window->setText(str);

		return window;
	}
	void KLTextScrollBar::updateSelf(float elapsed)
	{
		float positionx = mScrollSpeed*elapsed;
		if(mQueueMode)
		{
			std::list<Window*>::iterator it = mTextWindowQueue.begin();
			while(it != mTextWindowQueue.end())
			{
				Window* pWindow = *it;

				Rect& rect = pWindow->getRelativeRect();
				Point position = pWindow->getPosition(Relative);
				position.d_x -= positionx; 
				
				
				if(rect.d_right <= 0)
				{
					float width = pWindow->getWidth(Absolute);
					

					mTextWindowQueue.erase(it++);
					WindowManager::getSingleton().destroyWindow( pWindow );
				}
				else
				{
					pWindow->setPosition(Relative, position);
					++it;
				}
			}
			
			bool bAddNewWindow = false;
			if(mTextWindowQueue.size() == 0)
				bAddNewWindow = true;
			else
			{
				
				it = mTextWindowQueue.end();
				--it;
				Window* pWindow = *it;
				Rect& rect = pWindow->getRelativeRect();
				if(rect.d_right < 1.0f)
				{
					bAddNewWindow = true;
				}
			}

			if(bAddNewWindow && mShownTextQueue.size() > 0)
			{
				String& str = mShownTextQueue.front();
				mTextWindowQueue.push_back( createTextWindow(str) );
				mShownTextQueue.pop_front();
			}
		}
		else
		{
			if(!mTextWindow)
				return;
			if(mFirstTime)
			{
				
				Point position = mTextWindow->getPosition(Relative);
				position.d_x = position.d_x*(1-positionx); 
				mTextWindow->setPosition(Relative,position);
				mFirstTime = false;
				return;
			}
			Rect renderRect = mTextWindow->getPixelRect();
			if(!renderRect.getWidth())
			{
				if(mLoopTimes > mCurrentLoopTimes)
				{
					mCurrentLoopTimes++;
				}
				else
				{
					WindowEventArgs args(this);				
					d_realTimeUpdate = false;
					hide();
					onTextHide(args);
					return;
				}
				mTextWindow->setPosition(Relative,Point(1.0f,0.2f));
				mFirstTime = true;
				return;
			}
			float positionx = mScrollSpeed*elapsed;
			Point position = mTextWindow->getPosition(Relative);
			position.d_x -= positionx; 
			mTextWindow->setPosition(Relative,position);
		}
	}

	bool KLTextScrollBar::testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Falagard/TextScrollBar")	return true;
		return Window::testClassName_impl(class_name);
	}

	void KLTextScrollBar::onTextHide( WindowEventArgs& e )
	{
		fireEvent(EventTextHide, e, EventNamespace);
	}

	void KLTextScrollBar::setQueueMode(bool bQueueMode)
	{
		mQueueMode = bQueueMode;
	}
	void KLTextScrollBar::clearAllText()
	{
		if(mQueueMode)
		{
			std::list<Window*>::iterator it = mTextWindowQueue.begin();
			while(it != mTextWindowQueue.end())
			{
				Window* pWindow = *it;
				WindowManager::getSingleton().destroyWindow( pWindow );
				++it;
			}

			mTextWindowQueue.clear();
			mShownTextQueue.clear();
		}
	}
	void KLTextScrollBar::pushText(const String& str)
	{
		mShownTextQueue.push_back(str);
	}
	void KLTextScrollBar::setStringSpace(size_t space)
	{
		mTextWindowSpace = space;
	}
	
    Window* KLTextScrollBarFactory::createWindow(const String& name)
    {
        return new KLTextScrollBar(d_type, name);
    }

    void KLTextScrollBarFactory::destroyWindow(Window* window)
    {
        delete window;
    }
};