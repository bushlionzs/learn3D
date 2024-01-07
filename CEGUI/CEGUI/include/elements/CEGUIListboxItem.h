

#ifndef _CEGUIListboxItem_h_
#define _CEGUIListboxItem_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIColourRect.h"
#include "CEGUIRenderCache.h"


namespace CEGUI
{

class CEGUIEXPORT ListboxItem
{
public:
	
	static const colour	DefaultSelectionColour;		


	
	
	ListboxItem(const String& text, uint item_id = 0, void* item_data = NULL, bool disabled = false, bool auto_delete = true);


	
	virtual ~ListboxItem(void) {}


	
	
	const String&	getText(void) const		{return d_itemText;}
	const String&	getTooltipText(void) const		{return d_tooltipText;}

	
	const String&	getTagText(void) const		{return d_tagText;}

	
	uint	getID(void) const			{return d_itemID;}


	
	void*	getUserData(void) const		{return d_itemData;}

	
	bool	isSelected(void) const		{return d_selected;}


	
	bool	isDisabled(void) const		{return d_disabled;}


	
	bool	isAutoDeleted(void) const	{return d_autoDelete;}


	
	const Window*	getOwnerWindow(void) const		{return d_owner;} 


	
	ColourRect	getSelectionColours(void) const		{return d_selectCols;}


	
	const Image*	getSelectionBrushImage(void) const		{return d_selectBrush;}


	
	
	void	setText(const String& text)		{d_itemText = text;}

	void	setTooltipText(const String& text)		{d_tooltipText = text;}

	
	void	setID(uint item_id)		{d_itemID = item_id;}


	
	void	setUserData(void* item_data)	{d_itemData = item_data;}


	
	void	setSelected(bool setting)		{d_selected = setting;}

	void	setShowNormalBrush(bool setting)		{d_showNormalBrush = setting;}

	
	void	setDisabled(bool setting)		{d_disabled = setting;}

	
	void	setAutoDeleted(bool setting)		{d_autoDelete = setting;}


	
	void	setOwnerWindow(const Window* owner)		{d_owner = owner;}


	
	void	setSelectionColours(const ColourRect& cols)		{d_selectCols = cols;}


	
	void	setSelectionColours(colour top_left_colour, colour top_right_colour, colour bottom_left_colour, colour bottom_right_colour);


	
	void	setSelectionColours(colour col)		{setSelectionColours(col, col, col, col);}


	
	void	setSelectionBrushImage(const Image* image)		{d_selectBrush = image;}


	
	void	setSelectionBrushImage(const String& imageset, const String& image);

	
	void	setNormalBrushImage(const Image* image)		{d_normalBrush = image;}


	
	void	setNormalBrushImage(const String& imageset, const String& image);



	
	void	setTagText(const String& tagText) { d_tagText = tagText; }

	
	
	virtual	Size	getPixelSize( const Window* pParent) = 0;


	
	virtual	void	draw(const Vector3& position, float alpha, const Rect& clipper) const	= 0;

    virtual void    draw(RenderCache& cache,const Rect& targetRect, float zBase,  float alpha, const Rect* clipper) const = 0;

	
	
	virtual	bool	operator<(const ListboxItem& rhs) const		{return d_itemText < rhs.getText();}


	
	virtual	bool	operator>(const ListboxItem& rhs) const		{return d_itemText > rhs.getText();}


protected:
	
	
	ColourRect getModulateAlphaColourRect(const ColourRect& cols, float alpha) const;


	
	colour calculateModulatedAlphaColour(colour col, float alpha) const;


	
	String	d_itemText;		
	String  d_tooltipText;  
	uint	d_itemID;		
	void*	d_itemData;		
	bool	d_selected;		
	bool	d_disabled;		
	bool	d_autoDelete;	
	const Window*	d_owner;	
	ColourRect		d_selectCols;		
	const Image*	d_selectBrush;		

	bool			d_showNormalBrush;		
	const Image*	d_normalBrush;		
	String			d_tagText;			
};

} 


#endif	
