

#include "CEGUIHyperLink.h"
#include "CEGUIWindow.h"


namespace CEGUI
{
	HyperLink::HyperLink()
	{
		d_name = "";
		d_length = 0;
		d_curLength = 0;

		d_rectBuf.clear();
		d_guidRuntime.clear();
		d_pOwnerWindow.clear();
	}

	HyperLink::~HyperLink()
	{
		CleanUp();
	}

	void HyperLink::addNewRect(const Window* pOwnerWindow,const Rect newRect, unsigned long guid)
	{
		if( d_length >= d_curLength )
		{
			d_rectBuf.push_back( newRect );
			d_pOwnerWindow.push_back( pOwnerWindow );
			d_guidRuntime.push_back( guid );
			++d_curLength;
			if( guid != 0 )
				++d_length;
			return;
		}

		d_rectBuf[d_length] = newRect;
		d_pOwnerWindow[d_length] = pOwnerWindow;
		d_guidRuntime[d_length] = guid;

		if( guid != 0 )
			++d_length;
	}

	void HyperLink::CleanUp()
	{
		d_name = "";
		d_length = 0;
		d_curLength = 0;

		d_rectBuf.clear();
		d_guidRuntime.clear();
		d_pOwnerWindow.clear();
	}

	bool HyperLink::isInRange(unsigned long guid)
	{
		for( int i = 0; i < d_curLength; ++i )
		{
			if(	d_guidRuntime[i] == guid )
				return true;
		}
		return false;
	}

	bool HyperLink::isInRange(const Window* pOwnerWindow,const Point& position)
	{
		for( int i = 0; i < d_curLength; ++i )
		{
			bool a = d_rectBuf[i].isPointInRect(position);
			bool c = d_pOwnerWindow[i]->isCapturedByThis();

			if(	d_rectBuf[i].isPointInRect(position) && d_pOwnerWindow[i] == pOwnerWindow )
				return true;
		}
		return false;
	}

}
