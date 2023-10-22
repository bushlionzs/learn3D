#include "ItemBox.h"


ItemBox::ItemBox(MyGUI::Widget* _parent) :
	wraps::BaseItemBox<CellView>(_parent)
{
}

ItemBox::~ItemBox()
{
	MyGUI::ItemBox* box = getItemBox();
	size_t count = box->getItemCount();
	for (size_t pos = 0; pos < count; ++pos)
	{
		delete *box->getItemDataAt<ItemData*>(pos);
	}
}
