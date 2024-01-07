#pragma once
#include "KLselfAdaptationwindow.h"
#include "ceguirenderableimage.h"
namespace CEGUI
{
	namespace KLBalloonProperties
	{	
		class ArrowImage : public Property
		{
			
		public:
			ArrowImage() : Property(
				"ArrowImage",
				"Property to get/set the state of the frame enabled setting for the Static widget.  Value is either \"True\" or \"False\".",
				"set: image:")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);

			
		};
		

	};
	class FALAGARDBASE_API KLBalloon :	public KLSelfAdaptationWindow
	{
	public:
		static const utf8   WidgetTypeName[];       
		KLBalloon( const String& type, const String& name );
		~KLBalloon(void);
	
		void setArrowImage( const Image* image );

		static KLBalloonProperties::ArrowImage  d_ArrowProperty;

		virtual void	populateRenderCache();
		
		
		void   setText( const String& text );

	protected:
		virtual void updateSelfSize(void);
	private:
		RenderableImage		d_ArrowImage;
		
		bool                d_needUpdateSize;
	};

	class FALAGARDBASE_API KLBalloonFactory : public WindowFactory
    {
    public:
        KLBalloonFactory(void) : WindowFactory(KLBalloon::WidgetTypeName) { }
        ~KLBalloonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

};