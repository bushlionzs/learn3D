#ifndef _FalComplexWindow_h_
#define _FalComplexWindow_h_

#include "CEGUIWindow.h"
#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "IKLComplexWindow.h"
#include "KLComplexWindowProperties.h"
#include "KLKeyImageAnimation.h"


namespace CEGUI
{
	class FalagardButton;
	class KLPrizeButton;
	class KLActionButton;
	class KLWealth;

	
	
	
	
	
	class FALAGARDBASE_API KLComplexWindow : public Window, public IKLComplexWindow
	{
    public:
        static const utf8   WidgetTypeName[];       

		
		static const String EventNamespace;				
		static const String EventOptionClicked;
		static const String EventLinkClicked;
		static const String EventRewardItemClicked;
		static const String EventRewardItemMouseEnter;
		static const String EventRewardItemMouseLeave;
		static const String EventParentMouseEnters;
		static const String EventParentMouseLeaves;

		static KLComplexWindowProperties::ActionButtonSize		d_ActionButtonSizeProperty;

		
		static KLComplexWindowProperties::TextColour               d_textColorProperty;
		static KLComplexWindowProperties::NormalTextColour               d_optionNormalTextColour;
		static KLComplexWindowProperties::HoverTextColour              d_optionHoverTextColour;
		static KLComplexWindowProperties::PushedTextColour              d_optionPushedTextColour;


		static KLComplexWindowProperties::ActionButtonDistance	d_ActionButtonDistanceProperty;
		static KLComplexWindowProperties::TextAniName				d_textAniProperty;
		static KLComplexWindowProperties::OptionButtonSize		d_OptionButtonSizeProperty;
		static KLComplexWindowProperties::TextFixedValue			d_TextFixedValueProperty;
	   
		KLComplexWindow(const String& type, const String& name);

		
        ~KLComplexWindow();

		
		virtual void	initialise(void);

		virtual void	updateSelf(float elapsed);

		
		void		setActionButtonSize( const Size& rect );
		
		const Size	getActionButtonSize() const;

		
		void		setActionButtonDistance( const Size& rect );
		
		const Size	getActionButtonDistance() const;

		
		void		setOptionButtonSize( const Size& rect );
		
		const Size	getOptionButtonSize() const;

		virtual void	setMouseHollow(bool mousehollow);

		virtual void	setMouseMoveHollow(bool mousehollow);

		virtual void	setMouseLButtonHollow(bool mousehollow);

		virtual void	setMouseRButtonHollow(bool mousehollow);

		virtual void	onMouseWheel(MouseEventArgs& e);

		virtual bool		isMouseHollow(const Point* pPosition) const;
		virtual bool		isMouseLButtonHollow(const Point* pPosition) const;
		virtual bool		isMouseRButtonHollow(const Point* pPosition) const;

		
		void setTextColor(colour col){ d_textColor = col; }
		const colour& getTextColor() const { return d_textColor; }
		
		void setOptionNormalTextColour(colour col){ d_NormalTextColour = col; }
		const colour& getOptionNormalTextColour() const { return d_NormalTextColour; }

		void setOptionHoverTextColour(colour col){ d_HoverTextColour = col; }
		const colour& getOptionHoverTextColour() const { return d_HoverTextColour; }

		void setOptionPushedTextColour(colour col){ d_PushedTextColour = col; }
		const colour& getOptionPushedTextColour() const { return d_PushedTextColour; }

	public:
		
		virtual int				AddChildElement_Text(String strText, Font* font, TextFormatting typeset=WordWrapLeftAligned, bool showImage=false, bool showButton=false);
		
		virtual void			AddChildElement_Option(String strText,String strExtra1,String strExtra2, String strText3, Font* font=NULL);

		
		virtual void			AddChildElement_HyperLink( String strText, int nLinkID, bool bReArrange, Font* font=NULL);

		
		virtual Window*			AddChildElement_Item(String strIconImage, String strText,  bool bRadio, bool bReArrange, Font* font=NULL, int ActionID = -1, int nCount = 0, bool isMask = false);

		
		virtual Window*			AddChildElement_Action(String strIconImage, int ActionID, bool bRadio, bool bReArrange, Font* font=NULL);

		
		virtual void			AddChildElement_Money(int money, Font* font=NULL);

		
		virtual void			ClearAllElement(void);
		
		void					performWindowLayout(void);

		virtual void			PageEnd();

		virtual int				GetCurActionId() { return d_curActionId; }

		void					setTextItemAni(const String aniName);

		void					setTextFixedValue(float fix);
		float					getTextFixedValue()const { return d_textFixedValue; }

		void					setInlineButtionEvent(int nChildWindowIndex, const String& strEventName, const String& strFunction);

		virtual Window*			GetInlineButtion(int nChildWindowIndex);
	
	public:
		class ParentWindow : public Window
		{
		public:
	        static const utf8   WidgetTypeName[];       
			ParentWindow(const String& type, const String& name);
	        ~ParentWindow();
			
			void	SetComplexWindow(KLComplexWindow* pComplex)
			{
				d_ComplexWindow = pComplex;
			}

			virtual bool		isMouseHollow(const Point* pPosition) const;
			virtual bool		isMouseLButtonHollow(const Point* pPosition) const;
			virtual bool		isMouseRButtonHollow(const Point* pPosition) const;
			virtual void		onMouseLeaves( MouseEventArgs& e );

			
			virtual bool		getCacheRenderInfo() const;

			
			virtual bool		setHyperLinkRuntime(int guid, const String name, const Rect hyper_rect);

			virtual String		getHyperLinkContex(const Point* position)const;

		protected:
			virtual void	populateRenderCache();

			KLComplexWindow* d_ComplexWindow;
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
		
		
		struct ChildElement
		{
			String			d_Name;
			ChildType		d_Type;
			Rect			d_rectClient;
			const Font*	d_Font;
			String          d_exInfo1;
			String          d_exInfo2;
			TextFormatting	d_Typeset;
			int				d_Index;

			ChildElement()
			{
				static int nIndex = 0;
				d_Index = nIndex++;
			}
		};

		
		struct ChildElement_Text : public ChildElement
		{
			String						d_Text;
			bool						d_showImage;
			KLKeyImageAnimation*	d_finishAni;
			bool						d_showButton;
			PushButton*					d_Button;

			ChildElement_Text()
			{
				d_finishAni = 0;
				d_showImage = false;
				d_showButton = false;
				d_Button = 0;
			}
		};

		
		struct ChildElement_Option : public ChildElement
		{
			FalagardButton*				d_Button;
			String						d_Text;
			int							d_State;
		};

		
		struct ChildElement_Item : public ChildElement
		{
			KLPrizeButton*			d_Button;

			String						d_Text;
			bool						d_ReArrange;
			bool						d_Radio;
			int							d_ActionId;
		};

		
		struct ChildElement_Action : public ChildElement
		{

			KLActionButton*		d_ActionButton;
			String						d_Text;
			bool						d_ReArrange;
			bool						d_Radio;
		};

		
		struct ChildElement_HyperLink : public ChildElement
		{
			FalagardButton*				d_Button;
			int							d_State;
			String						d_Text;
			bool						d_ReArrange;
		};

		
		struct ChildElement_Money : public ChildElement
		{
			KLWealth*				d_Money;
		};

		Size							d_ActionButtonSize;			
		Size							d_ActionButtonDistance;		
		Size							d_OptionButtonSize;			

		typedef std::vector< ChildElement* >	ChildVector;
		typedef std::vector< ChildElement_Item* >	RadioItemChild;

	protected:
		
		colour d_textColor;
		colour d_NormalTextColour;
		colour d_HoverTextColour;
		colour d_PushedTextColour;


		

		
		virtual void	onSized(WindowEventArgs& e);
		virtual void	prepareBigchar(void);

		
		Rect		getTextRenderArea(void) const;

		
		void		configureScrollbars(void);
		
		void		_destroyAllElements(void);


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLComplexWindow")	return true;
			return Window::testClassName_impl(class_name);
		}

		
		
		bool	handleScrollbarChange(const EventArgs& e);
		
		bool	handleOptionClicked(const EventArgs& e);
		
		bool	handleLinkClicked(const EventArgs& e);
		
		bool	handleRewardItemClicked(const EventArgs& e);

		bool	MouseEnters( const EventArgs& e);
		bool	MouseLeaves( const EventArgs& e);

		void	NeedUpdate() { d_NeedUpdate = true; }


		
		ParentWindow*	d_ParentWindow;			
		Scrollbar*		d_vertScrollbar;		
		bool			d_enableVertScrollbar;	
		ChildVector		d_ChildVector;			
		RadioItemChild	d_RadioChild;			
		float			d_totalHeight;			
		int				d_curActionId;

		String			d_textAniString;
		float			d_textFixedValue;

		bool			d_NeedUpdate;
	};


    
    class FALAGARDBASE_API KLComplexWindowFactory : public WindowFactory
    {
    public:
        KLComplexWindowFactory(void) : WindowFactory(KLComplexWindow::WidgetTypeName) { }
        ~KLComplexWindowFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}

#endif