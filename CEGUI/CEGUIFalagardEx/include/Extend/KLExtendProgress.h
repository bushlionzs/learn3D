#pragma once
#include "falprogressbar.h"
#include "ceguirenderableimage.h"
namespace CEGUI
{

	namespace KLExtendProgressProperties
	{
		
		class ProgressImage: public Property
		{
		public:
			ProgressImage() : Property(
				"ProgressImage",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class EffectColor: public Property
		{
		public:
			EffectColor() : Property(
				"EffectColor",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class EffectColorLevel: public Property
		{
		public:
			EffectColorLevel() : Property(
				"EffectColorLevel",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		class MoveSpeed: public Property
		{
		public:
			MoveSpeed() : Property(
				"MoveSpeed",
				"Property to get/set empty status.",
				"")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};


	};


	class KLExtendProgress : public ProgressBar
	{
	public:
		static const utf8   WidgetTypeName[];       
	public:
		KLExtendProgress( const String& type, const String& name );
		~KLExtendProgress(void);


		static KLExtendProgressProperties::ProgressImage			d_effectImageProperty;
		static KLExtendProgressProperties::EffectColor				d_effectAlphaProperty;
		static KLExtendProgressProperties::EffectColorLevel		d_EffectColorLevelProperty;

		static KLExtendProgressProperties::MoveSpeed				d_MoveSpeedProperty;


		void	setEffectImage( const Image* pImage );		
		void    setEffectColor( ColourRect& color );
		void	setEffectColorLevel( int nIndex, ColourRect& color);
		void	setMoveSpeed( float fMoveSpeed ) { d_MoveSpeed = fMoveSpeed; };
	protected:
		virtual void	populateRenderCache();
		virtual void	updateSelf(float elapsed);
	private:
		ColourRect			d_EffectColorLevel[ 11 ];
		ColourRect			d_EffectColor;	
		
		RenderableImage		d_BackImage;  

		float				d_MoveSpeed;
		float				d_curPos;


		Rect				d_rectProgress;
		Rect				d_rectEffect;

		ColourRect&			getCurColor();

	};

	class FALAGARDBASE_API KLExtendProgressFactory : public WindowFactory
    {
    public:
        KLExtendProgressFactory(void) : WindowFactory( KLExtendProgress::WidgetTypeName ) { }
        ~KLExtendProgressFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};