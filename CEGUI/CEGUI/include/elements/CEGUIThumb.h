

#ifndef _CEGUIThumb_h_
#define _CEGUIThumb_h_

#include "CEGUIPushButton.h"
#include "elements/CEGUIThumbProperties.h"
#include <utility>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Thumb : public PushButton
{
public:
	static const String EventNamespace;				


	
	
	static const String EventThumbPositionChanged;		
	static const String EventThumbTrackStarted;			
	static const String EventThumbTrackEnded;				


	 
	
	bool	isHotTracked(void) const			{return d_hotTrack;}

	
	bool	isVertFree(void) const				{return d_vertFree;}

	
	bool	isHorzFree(void) const				{return d_horzFree;}


	
	std::pair<float, float>	getVertRange(void) const;


	
	std::pair<float, float>	getHorzRange(void) const;


	
	
	void	setHotTracked(bool setting)				{d_hotTrack = setting;}


	
	void	setVertFree(bool setting)						{d_vertFree = setting;}


	
	void	setHorzFree(bool setting)						{d_horzFree = setting;}
	

	
	void	setVertRange(float min, float max);


	
	void	setHorzRange(float min, float max);


	
	
	Thumb(const String& type, const String& name);


	
	virtual ~Thumb(void);


protected:
	

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Thumb")	return true;
		return PushButton::testClassName_impl(class_name);
	}


	
	
	virtual void	onThumbPositionChanged(WindowEventArgs& e);


	
	virtual void	onThumbTrackStarted(WindowEventArgs& e);


	
	virtual void	onThumbTrackEnded(WindowEventArgs& e);



	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);


	
	
	bool	d_hotTrack;					
	bool	d_vertFree;					
	bool	d_horzFree;					

	
	float	d_vertMin, d_vertMax;		
	float	d_horzMin, d_horzMax;		

	
	bool	d_beingDragged;				
	Point	d_dragPoint;				


private:
	
	static ThumbProperties::HotTracked	d_hotTrackedProperty;
	static ThumbProperties::VertFree	d_vertFreeProperty;
	static ThumbProperties::HorzFree	d_horzFreeProperty;
	static ThumbProperties::VertRange	d_vertRangeProperty;
	static ThumbProperties::HorzRange	d_horzRangeProperty;


	
	void	addThumbProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
