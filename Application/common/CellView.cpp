#include "OgreHeader.h"
#include "CellView.h"
#include "application_util.h"

void CellView::getCellDimension(MyGUI::Widget* _sender, MyGUI::IntCoord& _coord, bool _drop)
{
	_coord.set(0, 0, 32, 32);
}

CellView::CellView(MyGUI::Widget* _parent) :
	wraps::BaseCellView<ItemData*>("CellView.layout", _parent)
{
	assignWidget(mImageBack, "image_Back");
	assignWidget(mImageBorder, "image_Border");
}

void CellView::update(const MyGUI::IBDrawItemInfo& _info, ItemData* _data)
{
	if (_info.update)
	{
	
		
	}

	if (_info.drag)
	{
		mImageBack->setItemName("None");
		mImageBorder->setItemName("None");
	}
	else
	{
		if (_info.active)
		{
			mImageBorder->setVisible(true);
			mImageBack->setVisible(true);
			setImageInfo(mImageBack, "CJSH_icons_1", "CJSH_icons_1_action_1");
			setImageInfo(mImageBorder, "CJSH_icons_1", "CJSH_icons_1_action_1");
		}
		
	}
}

