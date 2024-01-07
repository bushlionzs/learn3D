#include "KLTextChatChannel.h"
#include "CEGUIPropertyHelper.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIPushButton.h"
#include "FalStaticImage.h"



namespace CEGUI
{
    const utf8  KLTextChatChannel::WidgetTypeName[] = "Falagard/TextChatChannel";

	KLTextChatChannelProperties::ButtonSize		KLTextChatChannel::d_btnSizeProperty;
	KLTextChatChannelProperties::ButtonPosition	KLTextChatChannel::d_btnPositionProperty;
	KLTextChatChannelProperties::TextSize			KLTextChatChannel::d_textSizeProperty;
	KLTextChatChannelProperties::HoverChannel		KLTextChatChannel::d_hoverChannelProperty;
	KLTextChatChannelProperties::HoverChannelName	KLTextChatChannel::d_hoverChannelNameProperty;
	KLTextChatChannelProperties::ChannelBkg		KLTextChatChannel::d_channelBkgProperty;
	KLTextChatChannelProperties::BkgSize			KLTextChatChannel::d_bkgSizeProperty;
	KLTextChatChannelProperties::BkgPosition		KLTextChatChannel::d_bkgPositionProperty;

	KLTextChatChannel::KLTextChatChannel(const String& type, const String& name) :
        Window(type, name),
		d_btnSize(0.0, 0.0),
		d_btnPosition(0.0, 0.0),
		d_hoverChannel(-1),
		d_lastHoverChannel(-1),
		d_bkgSize(0,0),
		d_bkgPosition(0,0),	
		d_channelBkg(0)
    {
        addChatChannelProperties();
    }

    KLTextChatChannel::~KLTextChatChannel()
    {
    }

	void KLTextChatChannel::addChatChannelProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLTextChatChannel )
		   CEGUI_ADD_STATICPROPERTY( &d_btnSizeProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_btnPositionProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_textSizeProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_hoverChannelProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_hoverChannelNameProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_channelBkgProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_bkgSizeProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_bkgPositionProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	void KLTextChatChannel::onMouseLeaves(MouseEventArgs& e)
	{
		
		Window::onMouseLeaves(e);

		d_hoverChannel = -1;
		d_lastHoverChannel = -1;
		requestRedraw();
	}

	bool KLTextChatChannel::ButtonEventMouseDown( const EventArgs& e)
	{
		const MouseEventArgs& mouseArgs = (const MouseEventArgs&)e;
		if (mouseArgs.button != LeftButton)
		{
			return true;
		}

		Window* pWindow =  mouseArgs.window;
		if( !pWindow )
			return true;

		for(size_t i = 0; i < d_allChannel.size(); i++ )
		{
			if( d_allChannel[i].d_channelBtn == pWindow )
			{
				d_hoverChannel = (int)i;
				d_lastHoverChannel = d_hoverChannel;
			}
		}

		return true;
	}

	bool KLTextChatChannel::ButtonEventMouseUp( const EventArgs& e)
	{
		return true;
	}

	bool KLTextChatChannel::TextEventMouseDown( const EventArgs& e)
	{
		const MouseEventArgs& mouseArgs = (const MouseEventArgs&)e;
		if (mouseArgs.button != LeftButton)
		{
			return true;
		}

		Window* pWindow =  mouseArgs.window;
		if( !pWindow )
			return true;

		for(size_t i = 0; i < d_allChannel.size(); i++ )
		{
			if( d_allChannel[i].d_channelText == pWindow )
			{
				d_hoverChannel = (int)i;
				d_lastHoverChannel = d_hoverChannel;
			}
		}

		return true;
	}

	bool KLTextChatChannel::TextEventMouseUp( const EventArgs& e)
	{
		return true;
	}

	bool KLTextChatChannel::TextMouseEnters( const EventArgs& e)
	{
		Window* pWindow =  static_cast<Window*>( ((const MouseEventArgs&) e).window );
		if( !pWindow )
			return true;

		for(size_t i = 0; i < d_allChannel.size(); i++ )
		{
			if( d_allChannel[i].d_channelText == pWindow )
			{
				((PushButton*)d_allChannel[i].d_channelBtn)->setHovering(true);
				((PushButton*)d_allChannel[i].d_channelBtn)->requestRedraw();
			}
		}

		return true;
	}

	bool KLTextChatChannel::TextMouseLeaves( const EventArgs& e)
	{
		Window* pWindow =  static_cast<Window*>( ((const MouseEventArgs&) e).window );
		if( !pWindow )
			return true;

		for(size_t i = 0; i < d_allChannel.size(); i++ )
		{
			if( d_allChannel[i].d_channelText == pWindow )
			{
				((PushButton*)d_allChannel[i].d_channelBtn)->setHovering(false);
				((PushButton*)d_allChannel[i].d_channelBtn)->requestRedraw();
			}
		}

		return true;
	}

	void KLTextChatChannel::resizeSelf(void)
	{
		int size = (int)d_allChannel.size();

		for(int i = 0; i < size; i++ )
		{
			Point curChannel = d_btnPosition;
			curChannel.d_y -= i * d_btnSize.d_height;
			d_allChannel[i].d_channelBtn->setPosition( curChannel );
			d_allChannel[i].d_channelText->setPosition( Point(curChannel.d_x + d_btnSize.d_width, curChannel.d_y) );
		}

		Size curSize = d_bkgSize;
		Point curPosition = d_bkgPosition;

		curSize.d_height += (size - 1) * d_btnSize.d_height;
		curPosition.d_y -= (size - 1) * d_btnSize.d_height;

		if( d_channelBkg )
		{
			d_channelBkg->setSize( curSize );
			d_channelBkg->setPosition( curPosition );
		}
	}

	void KLTextChatChannel::clearAllChannel(void)
	{
		for(size_t i = 0; i < d_allChannel.size(); i++ )
		{
			if( d_allChannel[i].d_channelBtn )
				WindowManager::getSingleton().destroyWindow( d_allChannel[i].d_channelBtn );
			if( d_allChannel[i].d_channelText )
				WindowManager::getSingleton().destroyWindow( d_allChannel[i].d_channelText );
		}

		d_allChannel.clear();
		resizeSelf();
	}

	void KLTextChatChannel::addChannel(const String& strType, const String& strNormal, const String& strHover, const String& strPushed, const String& strName)
	{
		ChannelItem newChannel;

		newChannel.d_channelBtn  = static_cast<Window*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/Button_2", strName+"1"));
		newChannel.d_channelText = static_cast<Window*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/SimpleText", strName+"2"));
		newChannel.d_strName = strName;
		newChannel.d_strType = strType;

		if( !newChannel.d_channelBtn || !newChannel.d_channelText )
			return;

		newChannel.d_channelBtn->setSize( d_btnSize );
		newChannel.d_channelBtn->setProperty( "NormalImage", strNormal );
		newChannel.d_channelBtn->setProperty( "HoverImage", strHover );
		newChannel.d_channelBtn->setProperty( "PushedImage", strPushed );
		newChannel.d_channelBtn->subscribeEvent( Window::EventMouseButtonDown,	Event::Subscriber(&CEGUI::KLTextChatChannel::ButtonEventMouseDown, this));
		newChannel.d_channelBtn->subscribeEvent( Window::EventMouseButtonUp,	Event::Subscriber(&CEGUI::KLTextChatChannel::ButtonEventMouseUp, this) );
		newChannel.d_channelBtn->setSpecialModal(d_specialModal);
		addChildWindow(newChannel.d_channelBtn);

		newChannel.d_channelText->setSize( d_textSize );
		newChannel.d_channelText->setProperty( "Text", strName );
		newChannel.d_channelText->subscribeEvent( Window::EventMouseEnters,		Event::Subscriber(&CEGUI::KLTextChatChannel::TextMouseEnters, this));
		newChannel.d_channelText->subscribeEvent( Window::EventMouseLeaves,		Event::Subscriber(&CEGUI::KLTextChatChannel::TextMouseLeaves, this) );
		newChannel.d_channelText->subscribeEvent( Window::EventMouseButtonDown, Event::Subscriber(&CEGUI::KLTextChatChannel::TextEventMouseDown, this));
		newChannel.d_channelText->subscribeEvent( Window::EventMouseButtonUp,	Event::Subscriber(&CEGUI::KLTextChatChannel::ButtonEventMouseUp, this) );
		newChannel.d_channelText->setSpecialModal(d_specialModal);
		addChildWindow(newChannel.d_channelText);

		d_allChannel.push_back(newChannel);

		resizeSelf();
	}

	String KLTextChatChannel::getHoverChannel(void) const
	{
		if(d_hoverChannel >= 0 && d_hoverChannel < (int)d_allChannel.size())
		{
			return d_allChannel[d_hoverChannel].d_strType;
		}
		return String("");
	}

	String KLTextChatChannel::getHoverChannelName(void) const
	{
		if(d_hoverChannel >= 0 && d_hoverChannel < (int)d_allChannel.size())
		{
			return d_allChannel[d_hoverChannel].d_strName;
		}
		return String("");
	}

	void KLTextChatChannel::setItemBkg(const String& strItemImg)
	{
		d_channelBkg = static_cast<Window*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/StaticImage", getName() + "__auto_bkg") );

		if( !d_channelBkg )
			return;
		
		d_channelBkg->setProperty( "Image", strItemImg );
		d_channelBkg->setSpecialModal(d_specialModal);
		addChildWindow(d_channelBkg);
	}

	void KLTextChatChannel::setBkgSize( const Size& itemSize )
	{
		d_bkgSize = itemSize;
		if( d_channelBkg )
			d_channelBkg->setSize( itemSize );
	}

	void KLTextChatChannel::setBkgPosition( const Point& position )
	{
		d_bkgPosition = position;
		if( d_channelBkg )
			d_channelBkg->setPosition( position );
	}

	void KLTextChatChannel::setSpecialModal(bool spModual)
	{
		d_specialModal = spModual;

		if( d_channelBkg )
			d_channelBkg->setSpecialModal(spModual);
	}

    
    
    
    Window* KLTextChatChannelFactory::createWindow(const String& name)
    {
        return new KLTextChatChannel(d_type, name);
    }

    void KLTextChatChannelFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}
