

#include "CEGUIFontManager.h"
#include "CEGUIExceptions.h"
#include "CEGUILogger.h"
#include "CEGUIFont.h"
#include "CEGUIFreeTypeFont.h"
#include "CEGUIBitmapFont.h"
#include "CEGUIFontManager_implData.h"
#include "CEGUIFont_implData.h"
#include "CEGUISystem.h"

#include "CEGUIImageset.h"
#include "CEGUIImage.h"
#include "CEGUITexture.h"
#include "CEGUIWindow.h"

#include <ft2build.h>
#include FT_FREETYPE_H



namespace CEGUI
{


template<> FontManager* Singleton<FontManager>::ms_Singleton	= NULL;




FontManager::FontManager(void)
{
	d_implData = new FontManagerImplData;

	if (FT_Init_FreeType(&d_implData->d_ftlib))
	{
		throw GenericException((utf8*)"FontManager::FontManager - Failed to initialise the FreeType library.");
	}

	

	d_timeOld = 0.0f;
	d_totalLife = 0.8f;	
	d_minAlpha = 0.35f;	

	d_curBlinkAlpha = 1.0f;
}



FontManager::~FontManager(void)
{
	Logger::getSingleton().logEvent((utf8*)"---- Begining cleanup of Font system ----");
	destroyAllFonts();

	FT_Done_FreeType(d_implData->d_ftlib);
	delete d_implData;

	
	for(FontRawDataContainerMapIterator itRawDataContainer =d_fontRawContainers.begin();itRawDataContainer!=d_fontRawContainers.end();++itRawDataContainer)
	{
		if(itRawDataContainer->second)
		{
			destroyFontRawData(itRawDataContainer->second);
			itRawDataContainer->second=NULL;
		}
	}

	
}



Font* FontManager::createFont(FontType type, const String& filename, const String& resourceGroup)
{
	
	
	Font* temp = 0;
	if(FreeType == type)
	{
		temp = new FreeTypeFont(filename, resourceGroup, new FreeTypeFont::FontImplData(d_implData->d_ftlib));
	}
	else
	{
		temp = new BitmapFont(filename, resourceGroup);
	}

	temp->load(filename, resourceGroup);

	String name = temp->getName();

	if (isFontPresent(name))
	{
		delete temp;

		throw AlreadyExistsException((utf8*)"FontManager::createFont - A font named '" + name + "' already exists.");
	}

	d_fonts[name] = temp;

    
    if (d_fonts.size() == 1)
    {
        System::getSingleton().setDefaultFont(temp);
    }

	return temp; 
}


void FontManager::destroyFont(const String& name)
{
	 FontRegistry::iterator	pos = d_fonts.find(name);

	if (pos != d_fonts.end())
	{
		String tmpName(name);

		delete pos->second;
		d_fonts.erase(pos);

		Logger::getSingleton().logEvent((utf8*)"Font '" + tmpName +"' has been destroyed.");
	}

}



void FontManager::destroyFont(Font* font)
{
	if (font != NULL)
	{
		destroyFont(font->getName());
	}

}



void FontManager::destroyAllFonts(void)
{
	while (!d_fonts.empty())
	{
		destroyFont(d_fonts.begin()->first);
	}

}



bool FontManager::isFontPresent(const String& name) const
{
	return (d_fonts.find(name) != d_fonts.end());
}



Font* FontManager::getFont(const String& name) const
{
	FontRegistry::const_iterator pos = d_fonts.find(name);

	if (pos == d_fonts.end())
	{
		throw UnknownObjectException("FontManager::getFont - A Font object with the specified name '" + name +"' does not exist within the system");
	}

	return pos->second;
}



void FontManager::notifyScreenResolution(const Size& size)
{
	
	FontRegistry::iterator pos = d_fonts.begin(), end = d_fonts.end();

	for (; pos != end; ++pos)
	{
		pos->second->notifyScreenResolution(size);
	}

}

void FontManager::prepareFontTexture(void)
{
	
	FontRegistry::iterator pos = d_fonts.begin(), end = d_fonts.end();

	for (; pos != end; ++pos)
	{
		pos->second->prepareFontTexture();
	}
}


void FontManager::addRuntimeBlink(const Window* OwnerWindow, const Image* img, unsigned long& quadID, const Vector3& position, const Size& size, const Rect& clip_rect, const ColourRect& col_rect)
{
	FontBlinkRuntime runtime;

	runtime.d_texture = (Imageset*)img->getImageset();
	runtime.d_quadID = quadID;
	runtime.d_colorRect = col_rect;
	runtime.d_originalAlpha = col_rect.d_top_left.getAlpha(); 

	Rect source_rect = img->getSourceTextureArea();
	Rect dest_rect = Rect(position.d_x, position.d_y, position.d_x + size.d_width, position.d_y + size.d_height);
	
	Size sz = img->getSize();
	Point pt = img->getOffsets();

	
	Rect final_rect(dest_rect.getIntersection(clip_rect));

	Texture* pTex = img->getImageset()->getTexture();

	float x_scale = 1.0f / (float)pTex->getWidth();
	float y_scale = 1.0f / (float)pTex->getHeight();

	float tex_per_pix_x = source_rect.getWidth() / dest_rect.getWidth();
	float tex_per_pix_y = source_rect.getHeight() / dest_rect.getHeight();

	
	Rect  tex_rect((source_rect.d_left + ((final_rect.d_left - dest_rect.d_left) * tex_per_pix_x)) * x_scale,
		(source_rect.d_top + ((final_rect.d_top - dest_rect.d_top) * tex_per_pix_y)) * y_scale,
		(source_rect.d_right + ((final_rect.d_right - dest_rect.d_right) * tex_per_pix_x)) * x_scale,
		(source_rect.d_bottom + ((final_rect.d_bottom - dest_rect.d_bottom) * tex_per_pix_y)) * y_scale);

	runtime.d_textureRect = tex_rect;

	if( !((Window*)OwnerWindow)->setFontBlinkRuntime(&runtime) )
		d_runtimeBlink.push_back(runtime);
}

void FontManager::clearRuntimeBlinkList(void)
{
	d_runtimeBlink.clear();
}

void FontManager::updateRuntimeBlinkList(void)
{
	FontBlinkRegistry::iterator it;
	for(it = d_runtimeBlink.begin(); it != d_runtimeBlink.end(); ++it)
	{
		FontBlinkRuntime& runtime = *it;
		updateRuntimeBlink(runtime);
	}
}

void FontManager::updateRuntimeBlink( FontBlinkRuntime &runtime )
{
	runtime.d_colorRect.setAlpha(getBlinkAlphaValue());

	System::getSingleton().getRenderer()->adjustQuad(
		runtime.d_quadID, runtime.d_texture, runtime.d_textureRect, runtime.d_colorRect);
}

void FontManager::updateRuntimeBlink( const ColourRect &runtimeColor, void* pInfo )
{
	ColourRect rect = runtimeColor;
	rect.setAlpha(getBlinkAlphaValue());

	Window::QuadInfo* info = (Window::QuadInfo*)pInfo;
	info->topLeftCol	= System::getSingleton().getRenderer()->colourToOgre(rect.d_bottom_left);
	info->topRightCol	= System::getSingleton().getRenderer()->colourToOgre(rect.d_bottom_right);
	info->bottomLeftCol = System::getSingleton().getRenderer()->colourToOgre(rect.d_top_left);
	info->bottomRightCol= System::getSingleton().getRenderer()->colourToOgre(rect.d_top_right);
}

void FontManager::updateRuntimeBlink( float alpha, void* pInfo )
{
	Window::QuadInfo* info = (Window::QuadInfo*)pInfo;
	ColourRect rect(info->topLeftCol, info->topRightCol, info->bottomLeftCol, info->bottomRightCol);
	rect.setAlpha(alpha);

	info->topLeftCol	= System::getSingleton().getRenderer()->colourToOgre(rect.d_bottom_left);
	info->topRightCol	= System::getSingleton().getRenderer()->colourToOgre(rect.d_bottom_right);
	info->bottomLeftCol = System::getSingleton().getRenderer()->colourToOgre(rect.d_top_left);
	info->bottomRightCol= System::getSingleton().getRenderer()->colourToOgre(rect.d_top_right);
}

void FontManager::calculateBlinkAlphaValue(void)
{
	float nowTime = System::getSingleton().getCurTimeElapsed();
	float step = 0.0f;

	static bool dir = true;

	

	step = (nowTime - d_timeOld)/d_totalLife;
	d_timeOld = nowTime;

	d_curBlinkAlpha += (dir)?step:-step;
	if(d_curBlinkAlpha > 1.0f)
	{
		d_curBlinkAlpha = 1.0f;
		dir = false;
	}

	if(d_curBlinkAlpha < d_minAlpha)
	{
		d_curBlinkAlpha = d_minAlpha;
		dir = true;
	}

	
	
}

FontManager& FontManager::getSingleton(void)
{
	return Singleton<FontManager>::getSingleton();
}


FontManager* FontManager::getSingletonPtr(void)
{
	return Singleton<FontManager>::getSingletonPtr();
}



FontManager::FontIterator FontManager::getIterator(void) const
{
	return FontIterator(d_fonts.begin(), d_fonts.end());
}

bool FontManager::isFontRawDataPresent(const String& name) const
{
	return (d_fontRawContainers.find(name) != d_fontRawContainers.end());
}

RawDataContainer* FontManager::getFontRawData(const String& name)
{
	if(isFontRawDataPresent(name))
		return d_fontRawContainers[name];
	else
		return NULL;
}
RawDataContainer* FontManager::createFontRawData( const String& filename, const String& resourceGroup)
{
	if(isFontRawDataPresent(filename))
		return d_fontRawContainers[filename];
	else
	{
		RawDataContainer* pNewRawDataContainer = new RawDataContainer();
		assert(pNewRawDataContainer);
		if(pNewRawDataContainer)
		{
			System::getSingleton().getResourceProvider()->loadRawDataContainer(filename, *pNewRawDataContainer, resourceGroup);
			d_fontRawContainers[filename]=pNewRawDataContainer;
			return pNewRawDataContainer;
		}
		else
			return NULL;
	}
}
bool FontManager::destroyFontRawData(RawDataContainer* pRawDataContainer)
{
	if(pRawDataContainer)
	{
		System::getSingleton().getResourceProvider()->unloadRawDataContainer(*pRawDataContainer);
			delete pRawDataContainer;
			pRawDataContainer=NULL;
			return true;
	}
	else
		return false;
}


} 

