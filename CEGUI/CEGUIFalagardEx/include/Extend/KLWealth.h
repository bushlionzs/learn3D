#ifndef _FalMoney_h_
#define _FalMoney_h_

#include "CEGUIWindow.h"
#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "KLWealthProperties.h"


namespace CEGUI
{
	
	
	
	
	
	
    class FALAGARDBASE_API KLWealth : public Window
    {
    public:
        static const utf8   WidgetTypeName[];       

		
		
		enum HorzFormatting
		{
			LeftAligned,			
			RightAligned,			
		};

        
		KLWealth(const String& type, const String& name);

		
        ~KLWealth();

		
		virtual void	initialise(void);

		

		
		HorzFormatting	getHorizontalFormatting(void) const		{return	d_horzFormatting;}
		
		void	setHorizontalFormatting(HorzFormatting h_fmt);


		
		int				getMoneyNumber() const { return d_MoneyNum; }
		void			setMoneyNumber(int moneyNumber);

		
		const Image*	getGoldIcon(void) const	{ return d_imageGoldIcon; }
		void			setGoldIcon(const Image* pImage)	{ d_imageGoldIcon = pImage; }

		const Image*	getSilverIcon(void) const	{ return d_imageSilverIcon; }
		void			setSilverIcon(const Image* pImage)	{ d_imageSilverIcon = pImage; }
		
		const Image*	getCopperIcon(void) const	{ return d_imageCopperIcon; }
		void			setCopperIcon(const Image* pImage)	{ d_imageCopperIcon = pImage; }

	protected:
        

		void			populateRenderCache();

		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLWealth")	return true;
			return Window::testClassName_impl(class_name);
		}

	protected:
        
		int				d_MoneyNum;				
		HorzFormatting	d_horzFormatting;		

		const Image*	d_imageGoldIcon;		
		const Image*	d_imageSilverIcon;		
		const Image*	d_imageCopperIcon;		

	private:
        
		static KLWealthProperties::HorzFormatting	d_horzFormattingProperty;
        static KLWealthProperties::MoneyNumber		d_moneyNumProperty;
        static KLWealthProperties::GoldIcon		d_goldIconProperty;
        static KLWealthProperties::SilverIcon		d_silverIconProperty;
        static KLWealthProperties::CopperIcon		d_copperIconProperty;

        

        
        void addMoneyProperties(void);

	};

    
    class FALAGARDBASE_API KLWealthFactory : public WindowFactory
    {
    public:
        KLWealthFactory(void) : WindowFactory(KLWealth::WidgetTypeName) { }
        ~KLWealthFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}
#endif