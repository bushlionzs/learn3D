

#ifndef _CEGUIMenuBase_h_
#define _CEGUIMenuBase_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIMenuBaseProperties.h"
#include "elements/CEGUIItemListBase.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT MenuBase : public ItemListBase
{
public:
	static const String EventNamespace;				

	
	static const colour DefaultBackgroundColour;			


	
	
	static const String EventPopupOpened;					
	static const String EventPopupClosed;					


	
	
	float	getItemSpacing(void) const					{return d_itemSpacing;}


	
	float	getHorzPadding(void) const					{return d_horzPadding;}


	
	float	getVertPadding(void) const					{return d_vertPadding;}


	
	float	getBorderWidth(void) const					{return d_borderWidth;}	


	
	const ColourRect&	getBackgroundColours(void) const	{return d_backgroundColours;}


	
	bool	isMultiplePopupsAllowed(void) const			{return d_allowMultiplePopups;}


	
	MenuItem*	getPopupMenuItem(void) const				{return d_popup;}


	
	
	void	setItemSpacing(float spacing)				{d_itemSpacing=spacing;handleUpdatedItemData();}


	
	void	setHorzPadding(float padding)				{d_horzPadding=padding;handleUpdatedItemData();}


	
	void	setVertPadding(float padding)				{d_vertPadding=padding;handleUpdatedItemData();}


	
	void	setBorderWidth(float border)				{d_borderWidth=border;handleUpdatedItemData();}


	
	void	setBackgroundColours(const ColourRect& cr)	{d_backgroundColours=cr;}


	
	void	changePopupMenuItem(MenuItem* item);


	
	void	setAllowMultiplePopups(bool setting)		{d_allowMultiplePopups=setting;}


	
	
	MenuBase(const String& type, const String& name);


	
	virtual ~MenuBase(void);


protected:
	
	
	virtual void	onPopupOpened(WindowEventArgs& e);


	
	virtual void	onPopupClosed(WindowEventArgs& e);


	

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"MenuBase")	return true;
		return ItemListBase::testClassName_impl(class_name);
	}


	
	float d_itemSpacing;		
	float d_horzPadding;		
	float d_vertPadding;		
	float d_borderWidth;		
	
	ColourRect d_backgroundColours;		
	
	MenuItem* d_popup;		
	bool d_allowMultiplePopups;		


private:
	
	static MenuBaseProperties::ItemSpacing			d_itemSpacingProperty;
	static MenuBaseProperties::HorzPadding			d_horzPaddingProperty;
	static MenuBaseProperties::VertPadding			d_vertPaddingProperty;
	static MenuBaseProperties::BorderWidth			d_borderWidthProperty;
	static MenuBaseProperties::BackgroundColours	d_backgroundColoursProperty;
	static MenuBaseProperties::AllowMultiplePopups	d_allowMultiplePopupsProperty;

	
	void	addMenuBaseProperties(void);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
