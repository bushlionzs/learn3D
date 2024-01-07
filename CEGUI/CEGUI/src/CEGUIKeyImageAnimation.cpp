

#include "CEGUIKeyImageAnimation.h"
#include "CEGUIImageset.h"
#include "CEGUIExceptions.h"
#include "math.h"

namespace CEGUI
{
	
	KeyImageAnimation::KeyImageAnimation(const String& name, int id, bool loop, int totaltime, bool alpha, int loopType) :
		d_name(name),
		d_id(id),
		d_loopMode(loop),
		d_totalTime( totaltime ),
		d_bModeAlpha( alpha ),
		d_loopType( loopType )

	{
	}

	
	KeyImageAnimation::~KeyImageAnimation(void)
	{
	}

	
	void KeyImageAnimation::defineAnimateKey(const Image* image)
	{
		if(!image)
		{
			throw NullObjectException((utf8*)"KeyImageAnimation::defineAnimateKey - Image pointer must not be null.");
		}

		AnimateKey newKey;
		newKey.d_image = image;

		d_animateList.push_back(newKey);
	}

	
	const Image* KeyImageAnimation::getFrame(int time_elapsed, int time_total) const
	{
		if( time_total == -1 )
			time_total = d_totalTime;
		if(time_elapsed < 0) return 0;

		
		if(!d_loopMode && time_elapsed >= time_total) return 0;

		float fFrameScale = (float)(time_elapsed % time_total)/(float)(time_total);
		int nFrameIndex = (int)(fFrameScale*(float)d_animateList.size());
		if( d_animateList.size() == 0 || nFrameIndex >= d_animateList.size() )
			return 0;

		return d_animateList[nFrameIndex].d_image;
	}
	float KeyImageAnimation::getFrameAlpha( int time_elapsed, int time_total )
	{
		if( time_total == -1 ) 
			time_total = d_totalTime;
		if( d_bModeAlpha == false )
			return 1;
		int nTime = time_elapsed;
		if( d_loopMode )
			nTime = time_elapsed % time_total;
		
		float alpha	= float( nTime ) / float( time_total );
		switch( d_loopType )
		{
		case 0: 
			break;
		case 1: 
			{
				if( alpha < 0.5 )
					alpha *= 2;
				else
					alpha = ( 1.0f - alpha ) * 2;
			}
			break;
		case 2: 
			alpha = 1 - alpha;
			break;
		}
		return alpha;

	}
	const Image* KeyImageAnimation::getFrame(int index) const
	{
		if(index < 0 || index >= (int)d_animateList.size()) return 0;

		return d_animateList[index].d_image;
	}

	
	Size KeyImageAnimation::getSize(void) const
	{
		if(d_animateList.empty()) return Size(0.0f, 0.0f);

		
		
		
		return d_animateList[0].d_image->getSourceTextureArea().getSize();
	}

}