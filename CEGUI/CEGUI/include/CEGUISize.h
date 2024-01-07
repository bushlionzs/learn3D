

#ifndef _CEGUISize_h_
#define _CEGUISize_h_

#include "CEGUIBase.h"


namespace CEGUI
{


class CEGUIEXPORT Size
{
public:
	Size(void) {}
	Size(float width, float height) : d_width(width), d_height(height) {}

	bool operator==(const Size& other) const;
	bool operator!=(const Size& other) const;

	float d_width, d_height;
};

} 


#endif	
