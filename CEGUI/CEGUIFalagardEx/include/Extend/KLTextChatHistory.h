#ifndef _FalagardTextChatHistory_h_
#define _FalagardTextChatHistory_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLTextChatHistoryProperties.h"
#include "IKLTextChatHistory.h"


namespace CEGUI
{
	
	
	enum SCB_POS_STATE 
	{
		SPS_NONE,
		SPS_TOP,
		SPS_MIDDLE,
		SPS_END,
	};
	

	class KLTextChatBoard;

    class FALAGARDBASE_API KLTextChatHistory : public Window, public IKLTextChatHistory
    {
    public:
        static const utf8   WidgetTypeName[];       


		static const String EventNamespace;				
		static const String EventParentMouseEnters;
		static const String EventParentMouseLeaves;

       
        KLTextChatHistory(const String& type, const String& name);

        
        ~KLTextChatHistory();

		
		
		int				getChatBoardNumber() const { return d_chatBoardNum; }
		void			setChatBoardNumber(const int BoardNum) { d_chatBoardNum = BoardNum;}

		void			setFadeEnabled(bool setting)	{ d_fadeEnabled = setting; }

		float			getFadeShowTime() const { return d_fadeShowTime; }
		void			setFadeShowTime(const float time) { d_fadeShowTime = time;}

		
		virtual bool	updatePositionChanged();

		
		
		virtual size_t insertChatString(const String& strChat);
		virtual Window *getChatBoard(const size_t index);
		
		virtual void removeAllChatStrings();

		
		virtual void extendClearRegion();

		
		virtual void scrollToEnd();

		
		void performWindowLayout(void);

		
		
		SCB_POS_STATE GetScbPosState();
		bool UpdateAddNewWindow();
		void Layout();
		void validateScbRange();
		

		void setNeedUpdate(void);

		virtual void	onMouseEnters(MouseEventArgs& e);

		virtual void	updateSelf(float);

		virtual void	setMouseHollow(bool mousehollow);

		virtual void	setMouseMoveHollow(bool mousehollow);

		virtual void	setMouseLButtonHollow(bool mousehollow);

		virtual void	setMouseRButtonHollow(bool mousehollow);

		virtual void	setSpecialModal(bool spModual);

	public:
		class ParentWindow : public Window
		{
		public:
	        static const utf8   WidgetTypeName[];       
			ParentWindow(const String& type, const String& name);
	        ~ParentWindow();
			
			void setChatHistoryWindow(KLTextChatHistory* chathistoryWindow)
			{
				d_chatHistoryWindow = chathistoryWindow;
			}

		protected:
			KLTextChatHistory* d_chatHistoryWindow;
		};

		class ParentWindowFactory : public WindowFactory
		{
		public:
			ParentWindowFactory(void) : WindowFactory(ParentWindow::WidgetTypeName) { }
			~ParentWindowFactory(void){}
			Window* createWindow(const String& name);
			void destroyWindow(Window* window);
		};

    protected:
        
		virtual void	initialise(void);
		virtual void	onSized(WindowEventArgs& e);

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLTextChatHistory")	return true;
			return Window::testClassName_impl(class_name);
		}

		
		Rect getTextRenderArea(void) const;

		
		void configureScrollbars(void);

		
		
		bool handleScrollbarChange(const EventArgs& e);

		
		
		bool handleToEndBtnClick(const EventArgs& e);
		void onMouseWheel(MouseEventArgs& e);

		bool	ParentMouseEnters( const EventArgs& e);
		bool	ParentMouseLeaves( const EventArgs& e);

		
		ParentWindow*						d_parentWindow;		
		std::list< KLTextChatBoard* >		m_listChatBoard;	
		Scrollbar*							d_vertScrollbar;	
		float								d_totalHeight;		
		int									d_chatBoardNum;		
		bool								d_first;			
		PushButton*							d_toEnd;			
		float								d_extendHeight;		
		float								d_fadeShowTime;
		bool								d_fadeEnabled;
		
		unsigned int                        d_startOffsetY;     
		unsigned int                        d_currentOffsetY;   

	private:
        
		static KLTextChatHistoryProperties::ChatBoardNumber		d_chatBoardNumProperty;
		static KLTextChatHistoryProperties::FadeEnabled			d_FadeEnabledProperty;

       

        
        void addChatHistoryProperties(void);
	};

    
    class FALAGARDBASE_API KLTextChatHistoryFactory : public WindowFactory
    {
    public:
        KLTextChatHistoryFactory(void) : WindowFactory(KLTextChatHistory::WidgetTypeName) { }
        ~KLTextChatHistoryFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}

#endif