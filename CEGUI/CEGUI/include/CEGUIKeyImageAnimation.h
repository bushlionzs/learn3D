
#ifndef _CEGUIKeyImageAnimation_h_
#define _CEGUIKeyImageAnimation_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIRect.h"
#include <vector>
#include "ceguicolour.h"
#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
	class CEGUIEXPORT KeyImageAnimation
	{
		friend class KeyImageAnimation_xmlHandler;
		friend class KeyImageAnimationManager;

	public:
		
		const String& getName(void) const {return	d_name;}

		
		int getID(void) const {return	d_id;}

		
		void defineAnimateKey(const Image* image);

		
		const Image* getFrame(int time_elapsed, int time_total) const;

		
		const Image* getFrame(int index) const;

		
		int getFrameNumber(void) const { return (int)d_animateList.size(); }

		
		Size	getSize(void) const;

		float getFrameAlpha( int time_elapsed, int time_total );

	protected:
		
		struct AnimateKey
		{
			const Image* d_image;
		};
		typedef std::vector< AnimateKey >  AnimateKeyRegistry;

		String				d_name;			
		int					d_id;			
		bool				d_loopMode;		
		int					d_loopType;		
		int					d_totalTime;
		AnimateKeyRegistry	d_animateList;	

		bool				d_bModeAlpha;  
	private:
		
		
		KeyImageAnimation(const String& name, int id, bool loop, int totaltime, bool alpha, int alphaType );

		
		~KeyImageAnimation(void);

	private:
		

	};

	
	struct CEGUIEXPORT AnimateRuntime
	{
		const KeyImageAnimation*	d_animate;			
		int				d_timeStart;		
		int				d_timeNow;			
		int				d_timeTotal;		
		Rect			d_destRect;			
		Rect			d_clipRect;			
		unsigned long	d_quadID;			
		colour			d_colours;
	};
}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif