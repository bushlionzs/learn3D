#include "KLExtendProgress.h"
#include "CEGUIPropertyHelper.h"
namespace CEGUI
{

	const utf8  KLExtendProgress::WidgetTypeName[] = "Falagard/ExtendProgress";

	KLExtendProgressProperties::ProgressImage			KLExtendProgress::d_effectImageProperty;
	KLExtendProgressProperties::EffectColor			KLExtendProgress::d_effectAlphaProperty;
	KLExtendProgressProperties::EffectColorLevel		KLExtendProgress::d_EffectColorLevelProperty;
	
	KLExtendProgressProperties::MoveSpeed				KLExtendProgress::d_MoveSpeedProperty;
		
	KLExtendProgress::KLExtendProgress( const String& type, const String& name ) : 
		ProgressBar( type, name )
	{
		CEGUI_START_ADD_STATICPROPERTY( KLExtendProgress )
		   CEGUI_ADD_STATICPROPERTY( &d_effectImageProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_MoveSpeedProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_effectAlphaProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_EffectColorLevelProperty  );
		CEGUI_END_ADD_STATICPROPERTY

		d_BackImage.setHorzFormatting(RenderableImage::HorzStretched);
		d_BackImage.setVertFormatting(RenderableImage::VertStretched);

		d_MoveSpeed		= 1; 
		d_curPos		= 1;
		d_progress		= 1;
	}

	KLExtendProgress::~KLExtendProgress(void)
	{

	}

	ColourRect& KLExtendProgress::getCurColor()
	{
		int nColor = int( d_curPos * 10 );
		if( nColor < 0 ) nColor = 0;
		if( nColor > 10 ) nColor = 10;
		return d_EffectColorLevel[ int( d_curPos * 10 ) ];
	}
	void	KLExtendProgress::populateRenderCache()
	{
	

		if( d_curPos == d_progress )
			d_rectProgress = Rect( 0, 0, getAbsoluteWidth() * d_progress, getAbsoluteHeight() );
		
		d_BackImage.setColours( getCurColor() );
		d_BackImage.setRect( d_rectProgress );
		d_BackImage.draw( d_renderCache );
		if( d_curPos != d_progress )
		{
			d_BackImage.setColours( d_EffectColor );
			d_BackImage.setRect( d_rectEffect );
			d_BackImage.draw( d_renderCache );
		}
	}

	void   KLExtendProgress::setEffectImage( const Image* pImage )
	{
		d_BackImage.setImage( pImage );
	}

	void    KLExtendProgress::setEffectColor( ColourRect& color )  
	{
		d_EffectColor = color;
	}
	void   KLExtendProgress::setEffectColorLevel( int nIndex, ColourRect&	color )
	{
		for( int i = nIndex; i < 11; i ++ ) 
			d_EffectColorLevel[ i ] = color;
	}

	void	KLExtendProgress::updateSelf(float elapsed)
	{

		if( d_curPos != d_progress )  
		{
			
			float fMoveLength = elapsed * d_MoveSpeed;
			if( d_curPos > d_progress ) 
			{
				d_curPos -= fMoveLength;
				if( d_curPos < d_progress )
					d_curPos = d_progress;
			}
			else
			{
				d_curPos += fMoveLength;
				if( d_curPos > d_progress )
					d_curPos = d_progress;
			}
			if( d_curPos < d_progress )
			{	
				d_rectEffect = Rect( getAbsoluteWidth() * d_curPos, 0, getAbsoluteWidth() * d_progress, getAbsoluteHeight() );
				d_rectProgress = Rect( 0, 0, getAbsoluteWidth() * d_progress, getAbsoluteHeight() );
			}
			else
			{
				d_rectEffect = Rect( getAbsoluteWidth() * d_progress, 0, getAbsoluteWidth() * d_curPos, getAbsoluteHeight() );
				d_rectProgress = Rect( 0, 0, getAbsoluteWidth() * d_curPos, getAbsoluteHeight() );
			}
			if( d_curPos < 0 )
				d_curPos = 0;
			if( d_curPos > 1 )
				d_curPos = 1;
			requestRedraw();
			d_needsRedraw = true;
		}
	
	}
	
	namespace KLExtendProgressProperties
	{

		
		String ProgressImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void ProgressImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendProgress*>(receiver)->setEffectImage(PropertyHelper::stringToImage(value));
		}

		
		String EffectColor::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void EffectColor::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendProgress*>(receiver)->setEffectColor( PropertyHelper::stringToColourRect(value) );
		}
		
		String EffectColorLevel::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void EffectColorLevel::set(PropertyReceiver* receiver, const String& value)
		{
			int nIndex = 0;
			argb_t topLeft = 0xFF000000, topRight = 0xFF000000, bottomLeft = 0xFF000000, bottomRight = 0xFF000000;
			sscanf(value.c_str(), "index:%d tl:%8X tr:%8X bl:%8X br:%8X", &nIndex, &topLeft, &topRight, &bottomLeft, &bottomRight );
			static_cast<KLExtendProgress*>(receiver)->setEffectColorLevel( nIndex, ColourRect( topLeft, topRight, bottomLeft, bottomRight ) );
		}
		String MoveSpeed::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void MoveSpeed::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLExtendProgress*>(receiver)->setMoveSpeed( PropertyHelper::stringToFloat(value));
		}
	};


	
    
    
    Window* KLExtendProgressFactory::createWindow(const String& name)
    {
        return new KLExtendProgress(d_type, name);
    }

    void KLExtendProgressFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}