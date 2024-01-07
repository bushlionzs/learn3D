
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUILogger.h"
#include "CEGUIXMLAttributes.h"
#include "CEGUIXmlParser.h"
#include "CEGUIKeyImageAnimation_xmlHandler.h"
#include "CEGUIImageset.h"
#include "CEGUIImage.h"
#include "CEGUITexture.h"
#include "CEGUIWindow.h"

namespace CEGUI
{
	template<> KeyImageAnimationManager* Singleton<KeyImageAnimationManager>::ms_Singleton	= NULL;
	KeyImageAnimationManager::KeyImageAnimationManager(const String& animateDefFilename)
	{
		if (animateDefFilename.empty() || (animateDefFilename == (utf8*)""))
		{
			throw InvalidRequestException((utf8*)"KeyImageAnimationManager::KeyImageAnimationManager - Filename supplied for KeyImageAnimation loading must be valid");
		}

		KeyImageAnimation_xmlHandler handler;
		System::getSingleton().getXMLParser()->parseXMLFile(handler, animateDefFilename, "", "");
	}

	KeyImageAnimationManager::~KeyImageAnimationManager(void)
	{
		destroyAllAnimates();
	}

	KeyImageAnimationManager& KeyImageAnimationManager::getSingleton(void)
	{
		return Singleton<KeyImageAnimationManager>::getSingleton();
	}

	KeyImageAnimationManager* KeyImageAnimationManager::getSingletonPtr(void)
	{
		return Singleton<KeyImageAnimationManager>::getSingletonPtr();
	}

	
	KeyImageAnimation* KeyImageAnimationManager::createAnimate(const String& name, int id, bool loop, int totaltime, bool alpha, int loopType )
	{
		
		if (isAnimatePresent(name))
		{
			throw AlreadyExistsException((utf8*)"KeyImageAnimationManager::createAnimate - A animate named '" + name + "' already exists.");
		}
		
		KeyImageAnimation* newAnimate = new KeyImageAnimation(name, id, loop, totaltime, alpha, loopType );

		d_animateNameMap[name] = newAnimate;

		
		if( d_animateIDMap.find(id) == d_animateIDMap.end())
		{
			d_animateIDMap[id] = newAnimate;
		}

		return newAnimate;
	}

	
	bool KeyImageAnimationManager::isAnimatePresent(const String& name) const
	{
		return (d_animateNameMap.find(name) != d_animateNameMap.end());
	}

	bool KeyImageAnimationManager::isAnimatePresent(int id) const
	{
		return (d_animateIDMap.find(id) != d_animateIDMap.end());
	}

	
	const KeyImageAnimation* KeyImageAnimationManager::getAnimate(const String& name) const
	{
		AnimateNameRegistry::const_iterator pos = d_animateNameMap.find(name);
		if (pos == d_animateNameMap.end())
		{
			char sz[128];
			sprintf(sz,name.c_str());
			throw UnknownObjectException("Aniamtemanager::getAniamte- No Animatenamed '" + name + "' is present in the system.");
		}

		return pos->second;
	}

	const KeyImageAnimation* KeyImageAnimationManager::getAnimate(int id) const
	{
		AnimateIDRegistry::const_iterator pos = d_animateIDMap.find(id);
		if (pos == d_animateIDMap.end())
		{
			char szTemp[256];
			_snprintf(szTemp, 255, 
				"Aniamtemanager::getAniamte- No KeyImageAnimation's id '%d' is present in the system.", id);
			throw UnknownObjectException(szTemp);
		}

		return pos->second;
	}

	
	void KeyImageAnimationManager::destroyAnimate(const String& name)
	{
		AnimateNameRegistry::iterator pos = d_animateNameMap.find(name);

		if (pos != d_animateNameMap.end())
		{
			
			if(pos->second->getID() > 0)
			{
				d_animateIDMap.erase(pos->second->getID());
			}

			delete pos->second;
			d_animateNameMap.erase(pos);
		}
	}

	
	void KeyImageAnimationManager::destroyAnimate(KeyImageAnimation* animate)
	{
		if (animate != NULL)
		{
			destroyAnimate(animate->getName());
		}
	}

	
	void KeyImageAnimationManager::destroyAllAnimates(void)
	{
		while (!d_animateNameMap.empty())
		{
			destroyAnimate(d_animateNameMap.begin()->first);
		}
	}

	
	void KeyImageAnimationManager::clearRuntimeAnimateList(void)
	{
		d_runtimeAnimate.clear();
	}

	
	void KeyImageAnimationManager::draw(const Window* OwnerWindow, const KeyImageAnimation* animate, int time_start, int time_now, int time_total, const Vector3& position, const Size& size, const Rect& clip_rect, const colour& colours)
	{
		if(!animate)
		{
			throw NullObjectException((utf8*)"KeyImageAnimationManager::draw - KeyImageAnimation pointer must not be null.");
		}

		const Image* image_current = animate->getFrame(time_now-time_start, time_total);

		
		if(!image_current) return;

		unsigned long idQuad = image_current->draw(position, size, clip_rect, ColourRect(colours, colours, colours, colours), TopLeftToBottomRight, 1.0, 1.0, (void*)OwnerWindow);

		AnimateRuntime animateRuntime;
		animateRuntime.d_animate = animate;
		animateRuntime.d_timeStart = time_start;
		animateRuntime.d_timeNow = time_now;
		animateRuntime.d_timeTotal = time_total;
		animateRuntime.d_quadID = idQuad;
		animateRuntime.d_destRect = Rect(position.d_x, position.d_y, position.d_x + size.d_width, position.d_y + size.d_height);
		animateRuntime.d_clipRect = clip_rect;
		animateRuntime.d_colours = colours;

		if( !((Window*)OwnerWindow)->setAnimateRuntime(&animateRuntime) )
			d_runtimeAnimate.push_back(animateRuntime);
	}

	
	void KeyImageAnimationManager::updateRuntimeAnimateList(void)
	{
		AnimateRuntimeRegistry::iterator it;
		for(it=d_runtimeAnimate.begin(); it!=d_runtimeAnimate.end(); it++)
		{
			AnimateRuntime& animate = *it;

			updateRuntimeAnimate(animate);
		}
	}

	void KeyImageAnimationManager::updateRuntimeAnimate( AnimateRuntime &animate )
	{
		
		animate.d_timeNow = (int)(System::getSingleton().getCurTimeElapsed()*1000);

		const Image* image_current = animate.d_animate->getFrame(animate.d_timeNow-animate.d_timeStart, animate.d_timeTotal);
		if(image_current)
		{
			Size sz = image_current->getSize();
			Point pt = image_current->getOffsets();

			Rect	source_rect = image_current->getSourceTextureArea();
			Rect&	dest_rect = animate.d_destRect;
			Rect&	clip_rect = animate.d_clipRect;

			
			Rect final_rect(dest_rect.getIntersection(clip_rect));

			Texture* pTex = image_current->getImageset()->getTexture();

			float x_scale = 1.0f / (float)pTex->getWidth();
			float y_scale = 1.0f / (float)pTex->getHeight();

			float tex_per_pix_x = source_rect.getWidth() / dest_rect.getWidth();
			float tex_per_pix_y = source_rect.getHeight() / dest_rect.getHeight();

			
			Rect  tex_rect((source_rect.d_left + ((final_rect.d_left - dest_rect.d_left) * tex_per_pix_x)) * x_scale,
				(source_rect.d_top + ((final_rect.d_top - dest_rect.d_top) * tex_per_pix_y)) * y_scale,
				(source_rect.d_right + ((final_rect.d_right - dest_rect.d_right) * tex_per_pix_x)) * x_scale,
				(source_rect.d_bottom + ((final_rect.d_bottom - dest_rect.d_bottom) * tex_per_pix_y)) * y_scale);

			System::getSingleton().getRenderer()->adjustQuad(
				animate.d_quadID, image_current->getImageset(), tex_rect, animate.d_colours );
		}
	}

	void KeyImageAnimationManager::updateRuntimeAnimate(AnimateRuntime &animate, void* pInfo )
	{
		
		animate.d_timeNow = (int)(System::getSingleton().getCurTimeElapsed()*1000);

		const Image* image_current = animate.d_animate->getFrame(animate.d_timeNow-animate.d_timeStart, animate.d_timeTotal);
		if(image_current)
		{
			Size sz = image_current->getSize();
			Point pt = image_current->getOffsets();

			Rect	source_rect = image_current->getSourceTextureArea();
			Rect&	dest_rect = (Rect&)animate.d_destRect;
			Rect&	clip_rect = (Rect&)animate.d_clipRect;

			
			Rect final_rect(dest_rect.getIntersection(clip_rect));

			Texture* pTex = image_current->getImageset()->getTexture();

			float x_scale = 1.0f / (float)pTex->getWidth();
			float y_scale = 1.0f / (float)pTex->getHeight();

			float tex_per_pix_x = source_rect.getWidth() / dest_rect.getWidth();
			float tex_per_pix_y = source_rect.getHeight() / dest_rect.getHeight();

			
			Rect  tex_rect((source_rect.d_left + ((final_rect.d_left - dest_rect.d_left) * tex_per_pix_x)) * x_scale,
				(source_rect.d_top + ((final_rect.d_top - dest_rect.d_top) * tex_per_pix_y)) * y_scale,
				(source_rect.d_right + ((final_rect.d_right - dest_rect.d_right) * tex_per_pix_x)) * x_scale,
				(source_rect.d_bottom + ((final_rect.d_bottom - dest_rect.d_bottom) * tex_per_pix_y)) * y_scale);

			Window::QuadInfo* info = (Window::QuadInfo*)pInfo;
			info->texture = image_current->getImageset();
			info->texPosition = tex_rect;
			ColourRect col = animate.d_colours;
			info->topLeftCol		= System::getSingleton().getRenderer()->colourToOgre(col.d_bottom_left);
			info->topRightCol		= System::getSingleton().getRenderer()->colourToOgre(col.d_bottom_right);
			info->bottomLeftCol		= System::getSingleton().getRenderer()->colourToOgre(col.d_top_left);
			info->bottomRightCol	= System::getSingleton().getRenderer()->colourToOgre(col.d_top_right);
			
			
		}
	}

	
	void KeyImageAnimationManager::addAnimateImageset(const String& name)
	{
		d_animateImageset.insert(name);
	}

	
	bool KeyImageAnimationManager::isImagesetInAnimate(const String& name) const
	{
		AnimateImagesetRegistry::const_iterator it;
		it = d_animateImageset.find(name);
		return (it != d_animateImageset.end());
	}

}