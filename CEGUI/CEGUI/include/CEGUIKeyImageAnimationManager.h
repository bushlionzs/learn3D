#ifndef _CEGUIKeyImageAnimationManager_h_
#define _CEGUIKeyImageAnimationManager_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUIKeyImageAnimation.h"

#include <vector>
#include <map>
#include <set>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
	class CEGUIEXPORT KeyImageAnimationManager :	public Singleton< KeyImageAnimationManager >
	{
	public:
		
		KeyImageAnimationManager(const String& name);

		
		~KeyImageAnimationManager(void);

		
		static	KeyImageAnimationManager&	getSingleton(void);

		
		static	KeyImageAnimationManager*	getSingletonPtr(void);

		
		KeyImageAnimation* createAnimate(const String& name, int id, bool loop, int totaltime, bool bAlphaMode , int loopType );

		
		void destroyAnimate(const String& name);

		
		void destroyAnimate(KeyImageAnimation* animate);

		
		void destroyAllAnimates(void);

		
		void addAnimateImageset(const String& name);

		
		bool isImagesetInAnimate(const String& name) const;

		
		bool isAnimatePresent(const String& name) const;

		
		bool isAnimatePresent(int id) const;

		
		const KeyImageAnimation* getAnimate(const String& name) const;

		
		const KeyImageAnimation* getAnimate(int id) const;

		
		void draw(const Window* OwnerWindow, const String& name, int time_start, int time_now, int time_total, const Vector3& position, const Size& size, const Rect& clip_rect, const colour& colours)
		{
			if(isAnimatePresent(name))
			{
				draw(OwnerWindow, getAnimate(name), time_start, time_now, time_total, position, size, clip_rect, colours);
			}
		}

		
		void draw(const Window* OwnerWindow, int id, int time_start, int time_now, int time_total, const Vector3& position, const Size& size, const Rect& clip_rect, const colour& colours)
		{
			if(isAnimatePresent(id))
			{
				draw(OwnerWindow, getAnimate(id), time_start, time_now, time_total, position, size, clip_rect, colours);
			}
		}

		
		void draw(const Window* OwnerWindow, const KeyImageAnimation* animate, int time_start, int time_now, int time_total, const Vector3& position, const Size& size, const Rect& clip_rect, const colour& colours);

		
		void clearRuntimeAnimateList(void);

		
		void updateRuntimeAnimateList(void);

		void updateRuntimeAnimate( AnimateRuntime &animate );
		void updateRuntimeAnimate(AnimateRuntime &animate, void* pInfo );

	private:
		
		typedef std::map< String, KeyImageAnimation* > AnimateNameRegistry;
		
		AnimateNameRegistry d_animateNameMap;

		typedef std::map< int, KeyImageAnimation* > AnimateIDRegistry;
		
		AnimateIDRegistry d_animateIDMap;

		
		typedef std::vector< AnimateRuntime > AnimateRuntimeRegistry;
		AnimateRuntimeRegistry d_runtimeAnimate;

		
		typedef std::set< String > AnimateImagesetRegistry;
		AnimateImagesetRegistry d_animateImageset;
	};
};

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif