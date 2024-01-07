

#ifndef _CEGUIItemListBase_h_
#define _CEGUIItemListBase_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIItemListBaseProperties.h"
#include "elements/CEGUIItemEntry.h"

#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT ItemListBase : public Window
{
public:
	static const String EventNamespace;				


	
	
	static const String EventListContentsChanged;			


	
	
	size_t	getItemCount(void) const		{return d_listItems.size();}


	
	ItemEntry*	getItemFromIndex(size_t index) const;


	
	size_t	getItemIndex(const ItemEntry* item) const;


	
	ItemEntry*	findItemWithText(const String& text, const ItemEntry* start_item);


	
	bool	isItemInList(const ItemEntry* item) const;


	
	bool isAutoResizeEnabled() const		{return d_autoResize;}


	
	
	virtual void	initialise(void);


	
	void	resetList(void);


	
	void	addItem(ItemEntry* item);


	
	void	insertItem(ItemEntry* item, const ItemEntry* position);


	
	void	removeItem(ItemEntry* item);


	
	void	handleUpdatedItemData(void);


	
	void setAutoResizeEnabled(bool setting);


	
	virtual	void	sizeToContent(void)		{sizeToContent_impl();}


	
	
	ItemListBase(const String& type, const String& name);


	
	virtual ~ItemListBase(void);


protected:
	
	
	virtual	void	sizeToContent_impl(void)		= 0;


	
	virtual Size getContentSize()		= 0;


	
	virtual	Rect	getItemRenderArea(void) const		= 0;


	
	virtual void	layoutItemWidgets()	= 0;


	
	virtual	void	populateRenderCache() = 0;


	

	
	bool	resetList_impl(void);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ItemListBase")	return true;
		return Window::testClassName_impl(class_name);
	}

	
	
	virtual	void	onListContentsChanged(WindowEventArgs& e);


	
	virtual void	onSized(WindowEventArgs& e);


	
	typedef	std::vector<ItemEntry*>	ItemEntryList;
	ItemEntryList	d_listItems;		

	
	bool d_autoResize;

private:
	
	static ItemListBaseProperties::AutoResizeEnabled	d_autoResizeEnabledProperty;


	
	void	addItemListBaseProperties(void);


	
	virtual void	addChild_impl(Window* wnd);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
