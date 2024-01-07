

#ifndef _CEGUIEditboxInterface_h_
#define _CEGUIEditboxInterface_h_

#include "CEGUIBase.h"


namespace CEGUI
{


class CEGUIEXPORT EditboxInterface
{
public:
	
	virtual void	setSelection(size_t start_pos, size_t end_pos) = 0;
	
	
	virtual size_t	getSelectionLength(void) const = 0;

	
	virtual size_t	getSelectionStartIndex(void) const = 0;


	
	virtual size_t	getSelectionEndIndex(void) const = 0;

	
	virtual bool	isTextMasked(void) const = 0;
	
	virtual size_t	getMaxTextLength(void) const = 0;

	
	virtual void	setCaratIndex(size_t carat_pos) = 0;
};


}

#endif
