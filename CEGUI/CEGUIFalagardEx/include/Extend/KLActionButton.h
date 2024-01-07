#ifndef _FalActionButton_h_
#define _FalActionButton_h_

#include "FalButton.h"
#include "KLActionButtonProperties.h"
#include "IKLActionButton.h"


namespace CEGUI
{
	struct AnimateRuntime;
	class KeyImageAnimation;

    class FALAGARDBASE_API KLActionButton : public FalagardButton, public IKLActionButton
    {
	public:
		
		class ActionButtonDragDropEventArgs : public WindowEventArgs
		{
		public:
			ActionButtonDragDropEventArgs(Window* wnd) : WindowEventArgs(wnd) {}
			KLActionButton*	dragDropItem; 
		};

    public:
        static const utf8  WidgetTypeName[];		
        static const String EventNamespace;			

        static const String EventDragStarted;			
        static const String EventDragEnded;				
        static const String EventDragPositionChanged;   
        static const String EventDragEnabledChanged;    
        static const String EventDragThresholdChanged;  
        static const String EventDragDropTargetChanged; 
		static const String EventDropItemEnters;		
		static const String EventDropItemLeaves;		
		static const String EventDropItemDropped;		
		static const String EventRBClicked;				

		
		KLActionButton(const String& type, const String& name);

		
        ~KLActionButton();

        
		bool			isEmpty() const { return d_empty; }
		void			setEmpty(bool setting) { d_empty = setting; }

		bool			isChecked() const { return d_checked; }
		void			setChecked(bool checked) { d_checked = checked; }

		bool			isGloom() const { return d_gloom; }
		void			setGloom(bool isgloom) { d_gloom = isgloom; }

		bool			isDefault(void) const { return d_default; }
		void			setDefault(bool bDefault) { d_default = bDefault; }

		
		
		String			getCornerChar(int nPos) const;
		void			setCornerChar(int nPos, const String& strChar, bool isColor = false );

		virtual void	setAnimate(const String& name, int totalTime, float percent);
		virtual void	cleanAnimate(void);

        
		bool			isDraggingEnabled(void) const { return d_draggingEnabled; }

        
		void			setDraggingEnabled(bool setting) { d_draggingEnabled = setting; }

        
		float			getPixelDragThreshold(void) const { return d_dragThreshold; }

        
		void			setPixelDragThreshold(float pixels) { d_dragThreshold = pixels; }

		
		virtual void	subscribeDragDropStartedEvent(Event::Subscriber subscriber);
		
		virtual void	subscribeMouseEnterEvent(Event::Subscriber subscriber);
		
		virtual void	subscribeMouseLeaveEvent(Event::Subscriber subscriber);

		
		virtual void	notifyDragingEnd(void);

		
		virtual void	notifyDragDrop_Droped(KLActionButton* pBtn);
		
		virtual void			setLogicItemData(void* pData);
		virtual void* getLogicItemData(void) const;

		
		virtual const char*		getDragAcceptName(void) const { return d_dragAcceptName.c_str(); }
		virtual void			setDragAcceptName(const String& value) { d_dragAcceptName = value; }

		
		virtual void			setCoverImage(const String& imageset, const String& image, float alpha = 0.5f);

		
		virtual void			setCoverImageShow(bool bshow);

	protected:
        
		virtual void	drawSelf(float z);

        
		virtual void	initialise(void);
		virtual void	onMouseButtonDown(MouseEventArgs& e);
		virtual void	onMouseButtonUp(MouseEventArgs& e);
        virtual void	onMouseMove(MouseEventArgs& e);
		virtual void	onMouseLeaves(MouseEventArgs& e);
		virtual void	onRBClicked(WindowEventArgs& e);
		virtual void	onClicked(WindowEventArgs& e);
		virtual void	updateSelf(float elapsed);
		virtual void	prepareBigchar(void);

        

    protected:
        
		void	drawCorner(float z);
		void	drawAnimate(float z);
		void	drawDefault(float z);
		void	drawCover(float z);

		struct ANIMATE
		{
			KeyImageAnimation*		d_animate;
			int				d_time_start;
			int				d_time_total;
			const Image*	d_currentFrame;
			float			d_alpha;
		};

		void	updateAnimate(ANIMATE& animate);

        		
        bool isDraggingThresholdExceeded(const Point& local_mouse);


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLActionButton")	return true;
			return FalagardButton::testClassName_impl(class_name);
		}

	protected:
        
		void*	m_pLogicData;		
        bool	d_empty;			
		bool	d_checked;			
		bool	d_gloom;			
		bool	d_default;			

        bool    d_draggingEnabled;  
        bool    d_leftMouseDown;    
        bool    d_dragging;         
        Point   d_dragPoint;        
        float   d_dragThreshold;    

		String	d_dragAcceptName;	

		const Image*	d_pCoverImage;		
		bool			d_showCoverImage;	
		float			d_fCoverImageAlpha;

		struct CORNER_CHAR
		{
			String			d_Char; 				
		};

		CORNER_CHAR			d_CornerChar_TopLeft;	
		CORNER_CHAR			d_CornerChar_TopRight;	
		CORNER_CHAR			d_CornerChar_BotLeft;	
		CORNER_CHAR			d_CornerChar_BotRight;	

		MouseButton			d_ActiveButton;			
		MouseButton			d_DragButton;			

		ANIMATE				d_animate1;				
		bool				m_bCoolDown;			
	private:
        
        static KLActionButtonProperties::Empty			d_emptyProperty;
        static KLActionButtonProperties::Checked			d_checkedProperty;
		static KLActionButtonProperties::Gloom			d_gloomProperty;
		static KLActionButtonProperties::Default			d_defaultProperty;
		static KLActionButtonProperties::CornerChar		d_cornerCharProperty;
        static KLActionButtonProperties::DraggingEnabled	d_dragEnabledProperty;
        static KLActionButtonProperties::DragThreshold	d_dragThresholdProperty;
		static KLActionButtonProperties::DragAcceptName	d_dragAcceptNameProperty;

        

        
        void addActionButtonProperties(void);

	}; 

    
    class FALAGARDBASE_API KLActionButtonFactory : public WindowFactory
    {
    public:
        KLActionButtonFactory(void) : WindowFactory(KLActionButton::WidgetTypeName) { }
        ~KLActionButtonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}

#endif

