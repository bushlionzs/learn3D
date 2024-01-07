#include "KLRingProgress.h"
#include "CEGUIPropertyHelper.h"

#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616


#define RINGPROGRESS_RENDER_IMM   1

namespace CEGUI
{
	const float fConstKeyAngle[5] = {0.f, 45.f, 135.f, 225.f, 315.f};
	const float fConstAngle[5] = {45.f, 90.f, 90.f, 90.f, 45.f};
	const Point ConstCenterUv(0.5f, 0.5f);
	const Point ConstUv[RINGPROCESS_MAX_TRI_COUNT * RINGPROCESS_VERTEX_COUNT_PER_TRI] = 
		{
			ConstCenterUv, Point(1.f, 1.f), Point(ConstCenterUv.d_x, 1.f),
			ConstCenterUv, Point(1.f, 0.f), Point(1.f, 1.f),
			ConstCenterUv, Point(0.f, 0.f), Point(1.f, 0.f),
			ConstCenterUv, Point(0.f, 1.f), Point(0.f, 0.f),
			ConstCenterUv, Point(ConstCenterUv.d_x, 1.f), Point(0.f, 1.f)
		};

	const utf8  KLRingProgress::WidgetTypeName[] = "Falagard/RingProgress";

	KLRingProgressProperties::ProgressImage			KLRingProgress::d_ImageProperty;
	KLRingProgressProperties::ProgressColor			KLRingProgress::d_ColorProperty;
		
	KLRingProgress::KLRingProgress( const String& type, const String& name ) : 
		ProgressBar( type, name ),
	    d_prePos(0.f)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLExtendProgress )
		   CEGUI_ADD_STATICPROPERTY( &d_ImageProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_ColorProperty  );
		CEGUI_END_ADD_STATICPROPERTY
		
		d_diffuseColor = colour(1,1,1);
#if RINGPROGRESS_RENDER_IMM
#else
		d_needsRedraw = false;
#endif
		d_realTimeUpdate = false;
		d_elapsed = 0.f;

	}

	KLRingProgress::~KLRingProgress(void)
	{

	}

	bool KLRingProgress::populateTriByIdx(int triIdx, float pos)
	{
		if(triIdx < 0 || triIdx > RINGPROCESS_MAX_TRI_COUNT - 1)
			return false;

		int uvIdx = triIdx * RINGPROCESS_VERTEX_COUNT_PER_TRI;
		for(int i=0;i<RINGPROCESS_VERTEX_COUNT_PER_TRI;i++)
			d_uv[uvIdx+i] = ConstUv[uvIdx+i];

		float radian = pos * (M_PI / 180.f);

		float diff = fConstAngle[triIdx] - pos;
		if(diff > 0)
		{
			float u, v;
			int sliderIdx = uvIdx + 1;

			if(triIdx == 0)
			{
				u = (tan(radian) + 1) * 0.5f;
				d_uv[sliderIdx].d_x = u;
			}
			else if(triIdx == 1)
			{
				if(radian < M_PI_4)
				{
					v = (tan(M_PI_4 - radian) + 1) * 0.5f;
				}
				else
				{
					v = (1 - tan(radian - M_PI_4)) * 0.5f;
				}
				d_uv[sliderIdx].d_y = v;
			}
			else if(triIdx == 2)
			{
				if(radian < M_PI_4)
				{
					u = (tan(M_PI_4 - radian) + 1) * 0.5f;
				}
				else
				{
					u = (1 - tan(radian - M_PI_4)) * 0.5f;
				}
				d_uv[sliderIdx].d_x = u;
			}
			else if(triIdx == 3)
			{
				if(radian < M_PI_4)
				{
					v = (1 - tan(M_PI_4 - radian)) * 0.5f;
				}
				else
				{
					v = (tan(radian - M_PI_4) + 1) * 0.5f;
				}
				d_uv[sliderIdx].d_y = v;
			}
			else if(triIdx == 4)
			{
				u = (1 - tan(M_PI_4 - radian)) * 0.5f;

				d_uv[sliderIdx].d_x = u;
			}
		}

		return true;		
	}

	int KLRingProgress::populateTri()
	{
		int count = 0;
		float curPos = (float)(d_progress * 360.f);

		if(curPos <= fConstKeyAngle[0])
		{
			count = 0;
		}
		else if(curPos <= fConstKeyAngle[1])
		{
			if(populateTriByIdx(0, curPos))
				count = 1;
		}
		else if(curPos <= fConstKeyAngle[2])
		{
			if( populateTriByIdx(0, fConstAngle[0]) &&
				populateTriByIdx(1, curPos - fConstKeyAngle[1]))
				count = 2;
		}
		else if(curPos <= fConstKeyAngle[3])
		{
			if( populateTriByIdx(0, fConstAngle[0]) &&
			    populateTriByIdx(1, fConstAngle[1]) &&
			    populateTriByIdx(2, curPos - fConstKeyAngle[2]) )
				count = 3;
		}
		else if(curPos <= fConstKeyAngle[4])
		{
			if(	populateTriByIdx(0, fConstAngle[0]) &&
			    populateTriByIdx(1, fConstAngle[1]) &&
			    populateTriByIdx(2, fConstAngle[2]) &&
			    populateTriByIdx(3, curPos - fConstKeyAngle[3]) )
				count = 4;
		}
		else
		{
			if(	populateTriByIdx(0, fConstAngle[0]) &&
			    populateTriByIdx(1, fConstAngle[1]) &&
			    populateTriByIdx(2, fConstAngle[2]) &&
			    populateTriByIdx(3, fConstAngle[3]) &&
			    populateTriByIdx(4, curPos - fConstKeyAngle[4]) )
				count = 5;
		}

		return count;
	}

	void KLRingProgress::populateRenderCache()
	{
		if(d_pImage)
		{			
			d_curUseTriCount = populateTri();
			if(d_curUseTriCount)
			{
				Rect dest(0,0,getAbsoluteWidth(),getAbsoluteHeight());
#if RINGPROGRESS_RENDER_IMM
				
				Point& position = getUnclippedPixelRect().getPosition();
				dest.offset(position);
				for(int i=0;i<d_curUseTriCount;i++)
					d_pImage->drawTri(dest, 1.f, d_diffuseColor, &d_uv[i*RINGPROCESS_VERTEX_COUNT_PER_TRI]);
#else
				
				for(int i=0;i<d_curUseTriCount;i++)
					d_renderCache.cacheImageTri(*d_pImage, dest, &d_uv[i*RINGPROCESS_VERTEX_COUNT_PER_TRI], 
					    0.f, 
						d_diffuseColor);
#endif				
			}
		}
	}

	void KLRingProgress::drawSelf(float z)
	{
#if RINGPROGRESS_RENDER_IMM
		d_needsRedraw = true;
#endif
		Window::drawSelf(z);
	}

	void KLRingProgress::updateSelf(float elapsed)
	{
		
	}
	
	namespace KLRingProgressProperties
	{
		
		String ProgressImage::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void ProgressImage::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLRingProgress*>(receiver)->setImage(PropertyHelper::stringToImage(value));
		}

		
		String ProgressColor::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void ProgressColor::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLRingProgress*>(receiver)->setColor( PropertyHelper::stringToColour(value) );
		}
	};


    
    Window* KLRingProgressFactory::createWindow(const String& name)
    {
        return new KLRingProgress(d_type, name);
    }

    void KLRingProgressFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}