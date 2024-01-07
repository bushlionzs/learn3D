

#include "CEGUIImageset.h"
#include "CEGUIExceptions.h"
#include "CEGUITexture.h"
#include "CEGUIRenderer.h"
#include "CEGUISystem.h"
#include "CEGUIImageset_xmlHandler.h"
#include "CEGUILogger.h"
#include "CEGUIDataContainer.h"
#include "CEGUIXMLParser.h"
#include "CEGUIKeyImageAnimationManager.h"
#include <iostream>
#include <cmath>


namespace CEGUI
{



const char	Imageset::ImagesetSchemaName[]			= "Imageset.xsd";



Imageset::Imageset(const String& name, Texture* texture ) :
	d_name(name),
	d_texture(texture)
{
	d_layoutRefCount = 0;

	d_textureLoadDelay = ImagesetManager::getSingleton().d_textureLoadDelay;
	if (d_texture == NULL)
	{
		throw NullObjectException((utf8*)"Imageset::Imageset - Texture object supplied for Imageset creation must not be NULL");
	}

	
	d_textureLoadDelay = false;

	
	d_autoScale = true;
	setNativeResolution(Size(DefaultNativeHorzRes, DefaultNativeVertRes));
	d_needFree = true;
	d_useAutoFree = true;
	d_textureFilename.clear();
	d_resourceGroup = (utf8*)"General";
	d_isFromFile = false;
}



Imageset::Imageset(const String& filename, const String& resourceGroup )
{
	d_layoutRefCount = 0;

	
	d_autoScale = true;
	d_textureLoadDelay = ImagesetManager::getSingleton().d_textureLoadDelay;
	setNativeResolution(Size(DefaultNativeHorzRes, DefaultNativeVertRes));

	
	d_textureLoadDelay = ImagesetManager::getSingleton().d_textureLoadDelay;

	d_texture = 0;
	d_textureFilename = filename;
	d_resourceGroup = resourceGroup;
	load(filename, resourceGroup);
	d_needFree = true;
	d_useAutoFree = true;
	d_isFromFile = false;
}


Imageset::Imageset(const String& name, const String& filename, const String& resourceGroup ) :
    d_name(name)
{
	d_layoutRefCount = 0;

    
	d_textureLoadDelay = ImagesetManager::getSingleton().d_textureLoadDelay;
	d_texture = 0;
	d_textureFilename = filename;
	d_resourceGroup = resourceGroup;

	
	
	
	
	
	

	
	

    
    d_autoScale = true;
	d_isFromFile = true;
	setNativeResolution(Size(DefaultNativeHorzRes, DefaultNativeVertRes));
    

    
    defineImage("full_image", Rect(0, 0, DefaultNativeHorzRes, DefaultNativeVertRes), Point(0, 0) );
	d_needFree = true;
	d_useAutoFree = true;
}


Imageset::~Imageset(void)
{
	unload();
}



void Imageset::setTexture(Texture* texture)
{
	if (d_texture == NULL)
	{
		throw NullObjectException((utf8*)"Imageset::setTexture - Texture object supplied for Imageset creation must not be NULL");
	}

	d_texture = texture;
}



void Imageset::load(const String& filename, const String& resourceGroup)
{
	
	unload();

	if (filename.empty() || (filename == (utf8*)""))
	{
		throw InvalidRequestException((utf8*)"Imageset::load - Filename supplied for Imageset loading must be valid");
	}

    
    Imageset_xmlHandler handler(this);

	
	try
	{
        System::getSingleton().getXMLParser()->parseXMLFile(handler, filename, ImagesetSchemaName, resourceGroup);
	}
	catch(...)
	{
		unload();

        Logger::getSingleton().logEvent("Imageset::load - loading of Imageset from file '" + filename +"' failed.", Errors);
        throw;
	}

}

 

const Image* Imageset::getImage(const String& name) const
{
	ImageRegistry::const_iterator	pos = d_images.find(name);

	if (pos == d_images.end())
	{
		return NULL;
		
	}

	return &pos->second;
}



void Imageset::defineImage(const String& name, const Rect& image_rect, const Point& render_offset)
{
	if (isImageDefined(name))
	{
		throw AlreadyExistsException("Imageset::defineImage - An image with the name '" + name + "' already exists in Imageset '" + d_name + "'.");
	}

	
	float hscale = d_autoScale ? d_horzScaling : 1.0f;
	float vscale = d_autoScale ? d_vertScaling : 1.0f;

	
	
	d_images[name] = Image(this, name, image_rect, render_offset, hscale, vscale);

	CEGUI_LOGINSANE("Image '" + name + "' has been defined for Imageset '" + d_name + "'.")
}



unsigned long Imageset::draw(const Rect& source_rect, const Rect& dest_rect, float z, const Rect& clip_rect,const ColourRect& colours, 
							 QuadSplitMode quad_split_mode, float xtex, float ytex, void* pUserData, bool isActiveHyperLink) const
{
	
	((Imageset*)this)->checkLoad();

	
	Rect final_rect(dest_rect.getIntersection(clip_rect));

	
	if (final_rect.getWidth() != 0 && d_texture )
	{
		float x_scale = 1.0f / (float)d_texture->getWidth();
		float y_scale = 1.0f / (float)d_texture->getHeight();

		float tex_per_pix_x = source_rect.getWidth() / dest_rect.getWidth();
		float tex_per_pix_y = source_rect.getHeight() / dest_rect.getHeight();

		
		Rect  tex_rect(
			PixelAligned(source_rect.d_left + ((final_rect.d_left - dest_rect.d_left) * tex_per_pix_x)) * x_scale,
			PixelAligned(source_rect.d_top + ((final_rect.d_top - dest_rect.d_top) * tex_per_pix_y)) * y_scale,
			PixelAligned(source_rect.d_right + ((final_rect.d_right - dest_rect.d_right) * tex_per_pix_x)) * x_scale,
			PixelAligned(source_rect.d_bottom + ((final_rect.d_bottom - dest_rect.d_bottom) * tex_per_pix_y)) * y_scale);


		float tex_width = tex_rect.getWidth() * abs( xtex );
		float tex_height = tex_rect.getHeight() * abs( ytex );
		float Ivt_width = tex_rect.getWidth() - tex_width;
		float Ivt_height = tex_rect.getHeight() - tex_height;

		if( xtex != 1.0f )
		{
			if( xtex < 0 )
			{
				tex_rect.d_right = tex_rect.d_left + tex_width;
			}
			else
			{
				tex_rect.d_left += Ivt_width;
			}
		}

		if( ytex != 1.0f )
		{
			if( ytex < 0 )
			{
				tex_rect.d_bottom = tex_rect.d_top + tex_height;
			}
			else
			{
				tex_rect.d_top += Ivt_height;
			}
		}
		

		final_rect.d_left	= PixelAligned(final_rect.d_left);
		final_rect.d_right	= PixelAligned(final_rect.d_right);
		final_rect.d_top	= PixelAligned(final_rect.d_top);
		final_rect.d_bottom	= PixelAligned(final_rect.d_bottom);
		
		return d_texture->getRenderer()->addQuad(final_rect, z, this, tex_rect, colours, quad_split_mode, pUserData, isActiveHyperLink);

	}

	return 0;
}


unsigned long Imageset::drawTri(const Rect& source_rect, const Rect& dest_rect, float z, const colour& diffuse, 
							    const Point* image_uv, float xtex, float ytex) const
{
	
	((Imageset*)this)->checkLoad();

	if(d_texture && image_uv)
	{
		Point pt[3], uv[3];
		
		float texWidth  = d_texture->getWidth();
		float texHeight = d_texture->getHeight();

		for(int i=0; i<3; i++)
		{
			
			pt[i].d_x = dest_rect.d_left + (dest_rect.getWidth() * image_uv[i].d_x);
			pt[i].d_y = dest_rect.d_top + (dest_rect.getHeight() * (1 - image_uv[i].d_y));

			
			uv[i].d_x = (source_rect.d_left + (image_uv[i].d_x * source_rect.getWidth())) / texWidth;
			uv[i].d_y = (source_rect.d_top + ((1 - image_uv[i].d_y) * source_rect.getHeight())) / texHeight;
		}

		return d_texture->getRenderer()->addTriangle(pt, uv, this, diffuse, z);
	}

	return 0;
}


Texture*	Imageset::getTexture(void) const						
{
	if( !d_texture )
	{
		((Imageset*)this)->checkLoad();
	}
	return d_texture;
}


Texture* Imageset::getOriginTexture( void ) const
{
	return d_texture;
}

void Imageset::checkLoad(void)
{
	
	d_needFree = false;
	if( d_texture )
		return;
	if( d_textureFilename.empty() )
		return;
    
    d_texture = System::getSingleton().getRenderer()->createTexture(d_textureFilename, d_resourceGroup);

	if( d_isFromFile )
	{
		undefineImage("full_image");
		setNativeResolution(Size(d_texture->getWidth(), d_texture->getHeight()));

		
		defineImage("full_image", Rect(0, 0, d_texture->getWidth(), d_texture->getHeight()), Point(0, 0) );
	}

	if( d_texture )
	{
		size_t size = ImagesetManager::getSingleton().getVideoMemorySize();
		ImagesetManager::getSingleton().setVideoMemorySize( size + d_texture->calculateSize() );
	}

	
	d_textureLoadDelay = false;

    
    d_autoScale = true;

    setNativeResolution(Size(d_nativeHorzRes, d_nativeVertRes));
}


void Imageset::unload(void)
{
	undefineAllImages();

	if( d_texture )
	{
		size_t size = ImagesetManager::getSingleton().getVideoMemorySize();
		ImagesetManager::getSingleton().setVideoMemorySize( size - d_texture->calculateSize() );
	}

	
	System::getSingleton().getRenderer()->destroyTexture(d_texture);
	d_texture = NULL;
}



void Imageset::updateImageScalingFactors(void)
{
	float hscale, vscale;

	if (d_autoScale)
	{
		hscale = d_horzScaling;
		vscale = d_vertScaling;
	}
	else
	{
		hscale = vscale = 1.0f;
	}

	ImageRegistry::iterator pos = d_images.begin(), end = d_images.end();
	for(; pos != end; ++pos)
	{
		pos->second.setHorzScaling(hscale);
		pos->second.setVertScaling(vscale);
	}

}



void Imageset::setAutoScalingEnabled(bool setting)
{
	if (setting != d_autoScale)
	{
		d_autoScale = setting;
		updateImageScalingFactors();
	}

}



void Imageset::setNativeResolution(const Size& size)
{
	d_nativeHorzRes = size.d_width;
	d_nativeVertRes = size.d_height;

	
	notifyScreenResolution(System::getSingleton().getRenderer()->getSize());
}



void Imageset::notifyScreenResolution(const Size& size)
{
	if(KeyImageAnimationManager::getSingletonPtr() && KeyImageAnimationManager::getSingleton().isImagesetInAnimate(this->getName()))
	{
		d_horzScaling = d_vertScaling = 1.0;
	}
	else
	{
		d_horzScaling = size.d_width / d_nativeHorzRes;
		d_vertScaling = size.d_height / d_nativeVertRes;
	}

	if (d_autoScale)
	{
		updateImageScalingFactors();
	}

}

void Imageset::writeXMLToStream(OutStream& out_stream) const
{
    
    out_stream << "<Imageset Name=\"" << d_name << "\" ";
    out_stream << "Filename=\"" << d_textureFilename << "\" ";

    if (d_nativeHorzRes != DefaultNativeHorzRes)
        out_stream << "NativeHorzRes=\"" << static_cast<uint>(d_nativeHorzRes) << "\" ";

    if (d_nativeVertRes != DefaultNativeVertRes)
        out_stream << "NativeVertRes=\"" << static_cast<uint>(d_nativeVertRes) << "\" ";

    if (d_autoScale)
        out_stream << "AutoScaled=\"True\" ";

    out_stream << ">" << std::endl;

    
    ImageIterator image = getIterator();

    while (!image.isAtEnd())
    {
        image.getCurrentValue().writeXMLToStream(out_stream);
        ++image;
    }

    
    out_stream << "</Imageset>" << std::endl;
}



Imageset::ImageIterator Imageset::getIterator(void) const
{
	return ImageIterator(d_images.begin(), d_images.end());
}


void Imageset::undefineImage(const String& name)
{
	d_images.erase(name);

	CEGUI_LOGINSANE("Image '" + name + "' has been removed from Imageset '" + d_name + "'.")
}


void Imageset::undefineAllImages(void)
{
	d_images.clear();

	CEGUI_LOGINSANE("All images have been removed from Imageset '" + d_name + "'.")
}





void Imageset::setImageArea( const String& name, Rect rect )
{
	ImageRegistry::iterator	pos = d_images.find(name);

	if (pos == d_images.end())
	{
		throw	UnknownObjectException("Imageset::getImage - The Image named '" + name + "' could not be found in Imageset '" + d_name + "'.");
	}
	pos->second.setSourceTextureArea( rect );
}

void Imageset::AutoFree()
{
	if( !d_useAutoFree ) 
		return;
	if( !d_texture )
		return;
	
	if( d_textureFilename.empty() )
		return;
	if( d_needFree == false ) 
	{
		d_needFree = true;
		return;
	}

	destroyImagesetTexture();

	System::getSingleton().signalRedraw();
}

void Imageset::destroyImagesetTexture()
{
	if( d_texture == NULL )
		return;

	if( d_texture )
	{
		size_t size = ImagesetManager::getSingleton().getVideoMemorySize();
		size -= d_texture->calculateSize();
		if( size < 0 )
			size = 0;
		ImagesetManager::getSingleton().setVideoMemorySize( size );
	}

	System::getSingleton().getRenderer()->destroyTexture(d_texture);
	d_texture = NULL;
	d_layoutRefCount = 0;
}

int Imageset::setLayoutRefCount( bool addOrDec )
{
	if( addOrDec )
	{
		++d_layoutRefCount;
	}
	else
	{
		--d_layoutRefCount;

		if( d_layoutRefCount < 0 )
			d_layoutRefCount = 0;
	}

	return d_layoutRefCount;
}

size_t Imageset::getTextureSize( void ) const
{
	if( d_texture )
	{
		return d_texture->calculateSize();
	}

	return 0;
}

Size Imageset::getImageSize(const String& name) const
{
	const Image* p = getImage(name);
	if( p == NULL )
		return Size(0.0f,0.0f);

	return p->getSize();
}

float Imageset::getImageWidth(const String& name) const
{
	const Image* p = getImage(name);
	if( p == NULL )
		return 0.0f;

	return p->getWidth();
}

float Imageset::getImageHeight(const String& name) const
{
	const Image* p = getImage(name);
	if( p == NULL )
		return 0.0f;

	return p->getHeight();
}

Point Imageset::getImageOffset(const String& name) const
{
	const Image* p = getImage(name);
	if( p == NULL )
		return Point(0.0f,0.0f);

	return p->getOffsets();
}

float Imageset::getImageOffsetX(const String& name) const
{
	const Image* p = getImage(name);
	if( p == NULL )
		return 0.0f;

	return p->getOffsetX();
}

float Imageset::getImageOffsetY(const String& name) const
{
	const Image* p = getImage(name);
	if( p == NULL )
		return 0.0f;

	return p->getOffsetY();
}



} 
