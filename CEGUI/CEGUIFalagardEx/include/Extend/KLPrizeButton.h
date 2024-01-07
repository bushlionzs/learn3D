#ifndef _FalRewardItemWindow_h_
#define _FalRewardItemWindow_h_

#include "FalModule.h"
#include "FalButton.h"


namespace CEGUI
{
	
	
	
	
	
	class FALAGARDBASE_API KLPrizeButton : public FalagardButton
	{
	public:
        static const utf8   WidgetTypeName[];       

        
		KLPrizeButton(const String& type, const String& name);

		
        ~KLPrizeButton();

		
		virtual void	initialise(void);

		
		bool isChecked() const { return d_Checked; }
		void setChecked(bool checked) { d_Checked = checked; }

		bool isMasked() const { return d_Masked; }
		void setMasked(bool checked) { d_Masked = checked; }

		
		void* getHelper(void) const { return d_OwnerItem; }
		void  setHelper(void* pHelper) { d_OwnerItem = pHelper; }
		void  setCornerChar(String cornerChar) { d_CornerChar = cornerChar; }

	protected:
		
		void performWindowLayout(void);

		
		virtual void	onSized(WindowEventArgs& e);

		virtual void	drawSelf(float z);

		virtual void	drawCorner(float z);
	
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLPrizeButton")	return true;
			return FalagardButton::testClassName_impl(class_name);
		}


		
		Rect	d_rectImage;			
		bool	d_Checked;				
		bool	d_Masked;				
		void*	d_OwnerItem;			
		String	d_CornerChar;
	};


    
	class FALAGARDBASE_API KLPrizeButtonWindowFactory : public WindowFactory
	{
	public:
		KLPrizeButtonWindowFactory(void) : WindowFactory(KLPrizeButton::WidgetTypeName) { }
		~KLPrizeButtonWindowFactory(void){}
		Window* createWindow(const String& name);
		void destroyWindow(Window* window);
	};

}

#endif
