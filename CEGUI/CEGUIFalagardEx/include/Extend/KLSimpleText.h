#ifndef _FalSimpleText_h_
#define _FalSimpleText_h_


#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLSimpleTextProperties.h"


namespace CEGUI
{

    class FALAGARDBASE_API KLSimpleText : public Window
    {
    public:
        static const utf8   WidgetTypeName[];       

		
		
		enum HorzFormatting
		{
			LeftAligned,			
			RightAligned,			
			HorzCentred,			
			HorzJustified,			
			WordWrapLeftAligned,	
			WordWrapRightAligned,	
			WordWrapCentred,		
			WordWrapJustified		
		};


		
		enum VertFormatting
		{
			TopAligned,		
			BottomAligned,	
			VertCentred     
		};

        
        KLSimpleText(const String& type, const String& name);

        
        ~KLSimpleText();

		

		
		HorzFormatting	getHorizontalFormatting(void) const		{return	d_horzFormatting;}


		
		VertFormatting	getVerticalFormatting(void) const		{return	d_vertFormatting;}

		
		void	setVerticalFormatting(VertFormatting v_fmt);


		
		void	setHorizontalFormatting(HorzFormatting h_fmt);


    protected:
        
		virtual void			populateRenderCache();
		virtual Rect			getTextRenderArea(void) const { return Rect(Point(0, 0), getAbsoluteSize()); }

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLSimpleText")	return true;
			return Window::testClassName_impl(class_name);
		}

		
		HorzFormatting	d_horzFormatting;		
		VertFormatting	d_vertFormatting;		


		float			d_fScaleX;
		float			d_fScaleY;
		colour			d_TextColour;
	public:
		void	setTextScale( Size  scale );
		Size    getTextScale() { return Size( d_fScaleX, d_fScaleY ); };
		void    setTextColor( const colour& col ) { d_TextColour = col; };

	private:
        
		static KLSimpleTextProperties::VertFormatting	d_vertFormattingProperty;
		static KLSimpleTextProperties::HorzFormatting	d_horzFormattingProperty;
		static KLSimpleTextProperties::TextScale		d_textScaleProperty;
		static KLSimpleTextProperties::TextColor		d_textColorProperty;

        

        
        void addSimpleTextProperties(void);

    };

    
    class FALAGARDBASE_API KLSimpleTextFactory : public WindowFactory
    {
    public:
        KLSimpleTextFactory(void) : WindowFactory(KLSimpleText::WidgetTypeName) { }
        ~KLSimpleTextFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}



#endif