

#ifndef _CEGUIScrollbar_h_
#define _CEGUIScrollbar_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIScrollbarProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT Scrollbar : public Window
{
public:
	static const String EventNamespace;				

	
	static const String EventScrollPositionChanged;		
	static const String EventThumbTrackStarted;			
	static const String EventThumbTrackEnded;				
	static const String EventScrollConfigChanged;			



	
	virtual void onSized(WindowEventArgs& e);
	virtual void onParentSized(WindowEventArgs& e);

	void setUsedInCombobox(bool bUsedInCombobox);
	void setComboboxScrollbarMaxWidth(int maxWidth);

	
	float	getDocumentSize(void) const			{return d_documentSize;}


	
	float	getPageSize(void) const				{return d_pageSize;}


	
	float	getStepSize(void) const				{return d_stepSize;}


	
	float	getOverlapSize(void) const			{return d_overlapSize;}


	
	float	getScrollPosition(void) const		{return d_position;}


	
	
	virtual void	initialise(void);


	
	void	setDocumentSize(float document_size);


	
	void	setPageSize(float page_size);


	
	void	setStepSize(float step_size);


	
	void	setOverlapSize(float overlap_size);


	
	void	setScrollPosition(float position);


	
	
	Scrollbar(const String& type, const String& name);


	
	virtual ~Scrollbar(void);

	virtual	void	onMouseWheel(MouseEventArgs& e);

	virtual void	setSpecialModal(bool spModual);


protected:
	

	
	virtual PushButton*	createIncreaseButton(const String& name) const		= 0;


	
	virtual PushButton*	createDecreaseButton(const String& name) const		= 0;


	
	virtual Thumb*	createThumb(const String& name) const		= 0;


	
	virtual void	updateThumb(void)	= 0;


	
	virtual float	getValueFromThumb(void) const	= 0;


	
	virtual float	getAdjustDirectionFromPoint(const Point& pt) const	= 0;


	
	bool	handleThumbMoved(const EventArgs& e);


	
	bool	handleIncreaseClicked(const EventArgs& e);


	
	bool	handleDecreaseClicked(const EventArgs& e);

	bool handleUpButtonMouseMultiDown(const EventArgs& e);
	bool handleDownButtonMouseMultiDown(const EventArgs& e);
	
	bool	handleThumbTrackStarted(const EventArgs& e);


	
	bool	handleThumbTrackEnded(const EventArgs& e);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Scrollbar")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual void	onScrollPositionChanged(WindowEventArgs& e);


	
	virtual void	onThumbTrackStarted(WindowEventArgs& e);


	
	virtual void	onThumbTrackEnded(WindowEventArgs& e);


	
	virtual void	onScrollConfigChanged(WindowEventArgs& e);


	
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseMultiDown(MouseEventArgs& e);

	
	float	d_documentSize;		
	float	d_pageSize;			
	float	d_stepSize;			
	float	d_overlapSize;		
	float	d_position;			

	bool    d_usedInCombobox;
	int     d_comboboxScrollbarMaxWidth;

	
	Thumb*		d_thumb;		
	PushButton*	d_increase;		
	PushButton*	d_decrease;		


private:
	
	static ScrollbarProperties::DocumentSize	d_documentSizeProperty;
	static ScrollbarProperties::PageSize		d_pageSizeProperty;
	static ScrollbarProperties::StepSize		d_stepSizeProperty;
	static ScrollbarProperties::OverlapSize		d_overlapSizeProperty;
	static ScrollbarProperties::ScrollPosition	d_scrollPositionProperty;


	
	void	addScrollbarProperties(void);
};


} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
