#pragma once
#include "falbutton.h"
namespace CEGUI
{
	namespace KLCheckButtonProperties
	{
		class SelectImage : public Property
		{
		public:
			SelectImage() : Property(
				"SelectImage",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class Selected: public Property
		{
		public:
			Selected() : Property(
				"Selected",
				"Property to get/set empty status.",
				"False")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		class CheckMode : public Property
		{
		public:
			CheckMode() : Property(
				"CheckMode",
				"Property to get/set empty status.",
				"0")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
	};
	class FALAGARDBASE_API KLCheckButton :	public FalagardButton
	{
	public:
		  static const utf8  WidgetTypeName[];       
	public:
		KLCheckButton( const String& type, const String& name );
		~KLCheckButton(void);

		void	setSelectImage(const RenderableImage* image);


		static KLCheckButtonProperties::SelectImage	d_selectImageProperty;
		static KLCheckButtonProperties::Selected		d_selectedProperty;
		static KLCheckButtonProperties::CheckMode		d_checkModeProperty;

		virtual void	setCustomImageryAutoSized(bool setting);
		void	setCheck( bool bCheck );
		const bool	isCheck() const { return d_bIsSelected; } ;


		void			setCheckMode( int nMode );
		const int		getCheckMode() const;
	protected:
		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"KLCheckButton")	return true;
			return Window::testClassName_impl(class_name);
		}

		bool				d_bIsSelected; 
		
		int					d_nCheckMode;  
		
		RenderableImage		d_selectImage;

		virtual void	onMouseButtonDown(MouseEventArgs& e);
		virtual void	onMouseButtonUp(MouseEventArgs& e);
		virtual	void	drawSelf(float z);
		void			drawCheck();

	};
	
	class FALAGARDBASE_API KLCheckButtonFactory : public WindowFactory
    {
    public:
        KLCheckButtonFactory(void) : WindowFactory(KLCheckButton::WidgetTypeName) { }
        ~KLCheckButtonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

}