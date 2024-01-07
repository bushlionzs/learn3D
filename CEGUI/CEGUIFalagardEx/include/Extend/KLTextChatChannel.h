#ifndef _FalagardTextChatChannel_h_
#define _FalagardTextChatChannel_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLTextChatChannelProperties.h"
#include "KLSimpleText.h"
#include "IKLTextChatChannel.h"



namespace CEGUI
{

    class FALAGARDBASE_API KLTextChatChannel : public IKLTextChatChannel, public Window
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLTextChatChannel(const String& type, const String& name);

        
        ~KLTextChatChannel();

		
		Size			getButtonSize(void) const { return d_btnSize;}
		void			setButttonSize(const Size& itemSize) { d_btnSize = itemSize; }
	
		Point			getButtonPosition(void) const { return d_btnPosition; }
		void			setButtonPosition(const Point& position) { d_btnPosition = position; }

		Size			getTextSize(void) const { return d_textSize;}
		void			setTextSize(const Size& itemSize) { d_textSize = itemSize; }

		String			getHoverChannel(void) const;
		String			getHoverChannelName(void) const;

		void			setItemBkg(const String& strItemImg);

		Size			getBkgSize(void) const { return d_bkgSize;}
		void			setBkgSize(const Size& itemSize);

		Point			getBkgPosition(void) const { return d_bkgPosition; }
		void			setBkgPosition(const Point& position);


        
		
		virtual void	clearAllChannel(void);

		
		virtual void	addChannel(const String& strType, const String& strNormal, const String& strHover, const String& strPushed, const String& strName);

		virtual void	setSpecialModal(bool spModual);

    protected:
        
		virtual void	onMouseLeaves(MouseEventArgs& e);


		
		void resizeSelf(void);
		

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLTextChatChannel")	return true;
			return Window::testClassName_impl(class_name);
		}

		bool	ButtonEventMouseDown( const EventArgs& e);
		bool	ButtonEventMouseUp( const EventArgs& e);
		
		bool	TextEventMouseDown( const EventArgs& e);
		bool	TextEventMouseUp( const EventArgs& e);

		bool	TextMouseEnters( const EventArgs& e);
		bool	TextMouseLeaves( const EventArgs& e);

		
		struct ChannelItem
		{
			String			d_strType;
			String			d_strName;
			Window*			d_channelBtn;
			Window*			d_channelText;
		};

		std::vector< ChannelItem >		d_allChannel;	
		Size							d_btnSize;
		Point							d_btnPosition;
		Size							d_textSize;
		
		Size							d_bkgSize;
		Point							d_bkgPosition;

		int								d_hoverChannel;
		int								d_lastHoverChannel;
		Window*							d_channelBkg;

	private:
        
		static KLTextChatChannelProperties::ButtonSize		d_btnSizeProperty;
		static KLTextChatChannelProperties::ButtonPosition	d_btnPositionProperty;
		static KLTextChatChannelProperties::TextSize			d_textSizeProperty;
		static KLTextChatChannelProperties::HoverChannel		d_hoverChannelProperty;
		static KLTextChatChannelProperties::HoverChannelName	d_hoverChannelNameProperty;
		static KLTextChatChannelProperties::ChannelBkg		d_channelBkgProperty;
		static KLTextChatChannelProperties::BkgSize			d_bkgSizeProperty;
		static KLTextChatChannelProperties::BkgPosition		d_bkgPositionProperty;

        
        
        void addChatChannelProperties(void);
    };

    
    class FALAGARDBASE_API KLTextChatChannelFactory : public WindowFactory
    {
    public:
        KLTextChatChannelFactory(void) : WindowFactory(KLTextChatChannel::WidgetTypeName) { }
        ~KLTextChatChannelFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}



#endif
