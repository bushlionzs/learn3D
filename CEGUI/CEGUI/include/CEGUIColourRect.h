

#ifndef _CEGUIColourRect_h_
#define _CEGUIColourRect_h_

#include "CEGUIBase.h"
#include "CEGUIcolour.h"


namespace CEGUI
{

class CEGUIEXPORT ColourRect
{
public:
	
	ColourRect(void);


	
	ColourRect(const colour& col);


	
	ColourRect(const colour& top_left, const colour& top_right, const colour& bottom_left, const colour& bottom_right);


	
	void	setAlpha(float alpha);


	
	void	setTopAlpha(float alpha);


	
	void	setBottomAlpha(float alpha);


	
	void	setLeftAlpha(float alpha);


	
	void	setRightAlpha(float alpha);


	
	bool	isMonochromatic() const;


	
	ColourRect getSubRectangle( float left, float right, float top, float bottom ) const;

	
	colour getColourAtPoint( float x, float y ) const;


	
	void	setColours(const colour& col);


	
	void	modulateAlpha(float alpha);

    
    ColourRect& operator*=(const ColourRect& other);


	colour	d_top_left, d_top_right, d_bottom_left, d_bottom_right;		
};

} 


#endif	
