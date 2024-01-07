

#ifndef _CEGUIEventArgs_h_
#define _CEGUIEventArgs_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"


namespace CEGUI
{

class CEGUIEXPORT EventArgs
{
public:
	
	EventArgs(void) : handled(false) {}
	virtual ~EventArgs(void) {}

	
	virtual bool isKindOf(const String& strClassName) const { return strClassName==(utf8*)"Event"; }

	
	bool	handled;		
};

} 

#endif	
