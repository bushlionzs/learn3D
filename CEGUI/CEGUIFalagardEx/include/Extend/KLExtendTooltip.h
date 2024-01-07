#ifndef _FalagardExtendTooltip_h_
#define _FalagardExtendTooltip_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLExtendTooltipProperties.h"
#include "KLSimpleText.h"
#include "IKLExtendTooltip.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLExtendTooltip : public Window, public IKLExtendTooltip
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        KLExtendTooltip(const String& type, const String& name);

        
        ~KLExtendTooltip();


        
		
		virtual void			resizeSelf(void);
		virtual Size			getRealSize();
		virtual float			getRealAbsoluteWidth();
		virtual float			getRealAbsoluteHeight();
		virtual void			setCurCondition(int curStarNum);


		

		String					getPageElementsName(void) const;
		void					setPageElementsName(const String& strName);

		String					getPageBakName(void) const;
		void					setPageBakName(const String& strName);

		String					getPageCloseName(void) const;
		void					setPageCloseName(const String& strName, float close);

		void					setDefaultWidth(float width);
		void					setConditionWidth(int starNum, float starWidth);

		float computeExtendWidth(Window* pWindow);
	public:
        

		class ResizeText : public KLSimpleText
		{
		public:
	        static const utf8   WidgetTypeName[];       

			ResizeText(const String& type, const String& name);
			~ResizeText();

		public:
			
			Size		_resizeSelf(const Size size);

			
			const Image*	getTopFrame(void) const { return d_topFrame; }
			void			setTopFrame(const Image* topFrame) { d_topFrame = topFrame; }

			const Image*	getMiddleFrame(void) const { return d_middleFrame; }
			void			setMiddleFrame(const Image* middleFrame) { d_middleFrame = middleFrame; }

			const Image*	getBottomFrame(void) const { return d_bottomFrame; }
			void			setBottomFrame(const Image* bottomFrame) { d_bottomFrame = bottomFrame; }

			URect			getTextArea(void) const { return d_textArea; }
			void			setTextArea(const URect& textArea) { d_textArea = textArea; }

		protected:
			
			virtual void			populateRenderCache();
			virtual Rect			getTextRenderArea(void) const;

			
			virtual bool	testClassName_impl(const String& class_name) const
			{
				if (class_name==(const utf8*)"KLExtendTooltip/ResizeText")	return true;
				return Window::testClassName_impl(class_name);
			}

			

			
			void addResizeTextProperties(void);

			
			const Image*	d_topFrame;
			const Image*	d_middleFrame;
			const Image*	d_bottomFrame;
			URect			d_textArea;

			
			static KLResizeTextProperties::TopFrame		d_topFrameProperty;
			static KLResizeTextProperties::MiddleFrame	d_middleFrameProperty;
			static KLResizeTextProperties::BottomFrame	d_bottomFrameProperty;
			static KLResizeTextProperties::TextArea		d_textAreaProperty;
		};

		class ResizeTextFactory : public WindowFactory
		{
		public:
			ResizeTextFactory(void) : WindowFactory(ResizeText::WidgetTypeName) { }
			~ResizeTextFactory(void){}
			Window* createWindow(const String& name);
			void destroyWindow(Window* window);
		};

    protected:
        
		virtual void			populateRenderCache();
		virtual void			onSized(WindowEventArgs& e);

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLExtendTooltip")	return true;
			return Window::testClassName_impl(class_name);
		}

		
		struct Elements
		{
			Window*		pWindow;			
			bool		bDynamicSize;		
		};
		typedef std::vector< Elements > ElementsVector;

		ElementsVector	d_VectorElements;	

		Window*			d_pagebakWindow;	
		Window*			d_pageCloseWindow;	

		float			d_defaultWidth;		
		float			d_curDefaultWidth;	

		
		
		
		int				d_defaultCondition;	
		int				d_curCondition;		
		int				d_lastCondition;	
		float			d_conditionWidth;	

		float			d_closeWidth;		

	private:
        
		static FalagardExtendTooltipProperties::PageElements		d_pageElementsProperty;
		static FalagardExtendTooltipProperties::PageBak			d_pageBakProperty;
		static FalagardExtendTooltipProperties::PageClose		d_pageCloseProperty;
		static FalagardExtendTooltipProperties::ResizeMaxWidth	d_defaultWidthProperty;
		static FalagardExtendTooltipProperties::ConditionWidth	d_conditionWidthProperty;
	
        

        
        void addSuperTooltipProperties(void);
    };

    
    class FALAGARDBASE_API KLExtendTooltipFactory : public WindowFactory
    {
    public:
        KLExtendTooltipFactory(void) : WindowFactory(KLExtendTooltip::WidgetTypeName) { }
        ~KLExtendTooltipFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

}

#endif