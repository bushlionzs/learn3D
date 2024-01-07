
#ifndef _CEGUIHyperLink_h_
#define _CEGUIHyperLink_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIRect.h"
#include <vector>
#include <map>



namespace CEGUI
{
class Window;
const int MAX_CELL_NUM = 256;

struct CEGUIEXPORT HyperLink
{
	
	std::vector<unsigned long>	d_guidRuntime;

	String						d_name;

	
	std::vector<Rect>			d_rectBuf;

	std::vector<const Window*>	d_pOwnerWindow;

	int							d_length;
	int							d_curLength;

	HyperLink();
	~HyperLink();

	void addNewRect(const Window* pOwnerWindow,const Rect newRect, unsigned long guid);

	void CleanUp();

	bool isInRange(unsigned long guid);

	bool isInRange(const Window* pOwnerWindow,const Point& position);
};

}

#endif	