#pragma once
#include "falprogressbar.h"
#include "ceguirenderableimage.h"
namespace CEGUI
{

	namespace KLRingProgressProperties
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
		
		class ProgressColor: public Property
		{
		public:
			ProgressColor() : Property(
				"ProgressColor",
				"Property to get/set ProgressColor.",
				"")
			{}
			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

	};

#define RINGPROCESS_MAX_TRI_COUNT  5
#define RINGPROCESS_VERTEX_COUNT_PER_TRI  3

	class FALAGARDBASE_API KLRingProgress : public ProgressBar
	{
	public:
		static const utf8   WidgetTypeName[];       
	public:
		KLRingProgress( const String& type, const String& name );
		~KLRingProgress(void);

		static KLRingProgressProperties::ProgressImage			d_ImageProperty;
		static KLRingProgressProperties::ProgressColor			d_ColorProperty;

		void	setImage( const Image* pImage ){ d_pImage = pImage; }
		
		void    setColor( const colour& color ){ d_diffuseColor = color; }
		colour&	getColor() { return d_diffuseColor; }

		virtual void drawSelf(float z);

	protected:
		bool populateTriByIdx(int triIdx, float pos);
		int  populateTri();

		virtual void	populateRenderCache();
		virtual void	updateSelf(float elapsed);

	private:
		
		const Image*        d_pImage;
		colour              d_diffuseColor;
		float               d_prePos;
		int                 d_curUseTriCount;
		Point               d_vertex[RINGPROCESS_MAX_TRI_COUNT * RINGPROCESS_VERTEX_COUNT_PER_TRI];
		Point               d_uv[RINGPROCESS_MAX_TRI_COUNT * RINGPROCESS_VERTEX_COUNT_PER_TRI];
		float               d_elapsed;
	};

	class FALAGARDBASE_API KLRingProgressFactory : public WindowFactory
    {
    public:
        KLRingProgressFactory(void) : WindowFactory( KLRingProgress::WidgetTypeName ) { }
        ~KLRingProgressFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};