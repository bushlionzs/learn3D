#include "OgreHeader.h"
#include "PackageWindow.h"
#include "CEGUIResourceManager.h"
#include "application_util.h"
#include "PackageBox.h"
#include "GameDataManager.h"
#include "KItem.h"

#define ITEM_WIDTH 32
#define ITEM_HEIGHT 32
#define CELL_WIDTH  46
#define CELL_HEIGHT 45

PackageWindow::PackageWindow() :
	BaseLayout("package.layout")
{
	assignWidget(mImageBackgroud, "background");
	assignWidget(mImageBackgroudCover, "background_cover");
	String imagesetname = "UI_MainBoard_2";
	String imagename = "UI_MainBoard_2_Other_Board";
	setImageInfo(mImageBackgroud, imagesetname, imagename);
	mImageBackgroud->setItemSelect(0);

	imagesetname = "UI_MainBoard_3";
	imagename = "UI_MainBoard_3_Packet_Cover";

	setImageInfo(mImageBackgroudCover, imagesetname, imagename);
	mImageBackgroudCover->setItemSelect(0);


	mToolTip = new ToolTip();
	mToolTip->hide();

		
	MyGUI::FactoryManager& factory = MyGUI::FactoryManager::getInstance();

	_row = 6;
	_column = 6;

	_imageboxs.resize(_row * _column);



	

	MyGUI::IntCoord aa;
	aa.left = 16 + 0 * CELL_WIDTH;
	aa.top = 5 + 0 * CELL_HEIGHT;
	aa.width = ITEM_WIDTH;
	aa.height = ITEM_HEIGHT;
	_focus_box = mImageBackgroudCover->createWidget<MyGUI::ImageBox>("ImageBox", aa, MyGUI::Align::Stretch, "focus");
	setImageInfo(_focus_box, "CJSH_icons_1", "CJSH_icons_1_action_1");
	_focus_box->setItemSelect(0);
	_focus_box->setVisible(false);

	/*updateItem(0, 0, 10010070);
	updateItem(0, 1, 10010070);
	updateItem(0, 5, 10010070);

	updateItem(1, 0, 10010070);
	updateItem(1, 1, 10010070);
	updateItem(1, 5, 10010070);

	updateItem(3, 4, 10010070);
	updateItem(4, 4, 10010070);
	updateItem(5, 4, 10010070);
	updateItem(5, 5, 10010070);
	setItemFocus(5, 4);*/

	mImageBackgroud->eventMouseButtonPressed += MyGUI::newDelegate(this, &PackageWindow::onWindowMouseButtonPressed);
	mImageBackgroud->eventMouseDrag += MyGUI::newDelegate(this, &PackageWindow::onWindowMouseDrag);
	mImageBackgroud->eventMouseButtonReleased += MyGUI::newDelegate(this, &PackageWindow::onWindowMouseButtonReleased);
}

void PackageWindow::notifyToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info)
{
	ItemData item;
	item._itemname = "none";


	if (_info.type == MyGUI::ToolTipInfo::Show)
	{
		mToolTip->show(&item);
		mToolTip->move(_info.point);
	}
	else if (_info.type == MyGUI::ToolTipInfo::Hide)
	{
		mToolTip->hide();
	}
	
}

void PackageWindow::clearView()
{
	MyGUI::WidgetManager::getInstance().destroyWidgets(mMainWidget->getEnumerator());
}

MyGUI::Widget* PackageWindow::getView()
{
	return mMainWidget;
}

void PackageWindow::onWindowMouseButtonPressed(
	MyGUI::Widget* _sender,
	int _left,
	int _top,
	MyGUI::MouseButton _id)
{
	
	mDragging = true;
	mDragOffset = MyGUI::IntPoint(_left, _top) - mMainWidget->getPosition();
}

void PackageWindow::onWindowMouseDrag(
	MyGUI::Widget* _sender,
	int _left,
	int _top,
	MyGUI::MouseButton _id)
{
	if (mDragging)
	{
		MyGUI::IntPoint new_pos =
			MyGUI::IntPoint(_left, _top) - mDragOffset;
		mMainWidget->setPosition(new_pos.left, new_pos.top);
	}
}

void PackageWindow::onWindowMouseButtonReleased(
	MyGUI::Widget* _sender,
	int _left,
	int _top,
	MyGUI::MouseButton _id)
{
	mDragging = false;
}

void PackageWindow::notifyMouseMove(MyGUI::Widget* _sender, int _left, int _top)
{

}

void PackageWindow::notifySetFocus(MyGUI::Widget* current, MyGUI::Widget* last)
{
	if (last)
	{
		_focus_box->setVisible(false);
	}

	if (current)
	{
		MyGUI::ImageBox* imagebox = (MyGUI::ImageBox*)current;
		uint32_t index = imagebox->getDepth() - 1;

		uint32_t row = index / _column;
		uint32_t column = index % _column;

		setItemFocus(row, column);
	}

}

bool PackageWindow::updateItem(
	uint32_t row,
	uint32_t column,
	uint32_t itemId)
{
	uint32_t index = row * _column + column;

	auto imagebox = _imageboxs[index];
	if (imagebox == nullptr)
	{
		MyGUI::IntCoord coord;
		coord.left = 16 + column * CELL_WIDTH;
		coord.top = 5 + row * CELL_HEIGHT;
		coord.width = ITEM_WIDTH;
		coord.height = ITEM_HEIGHT;
		imagebox = mImageBackgroudCover->createWidget<MyGUI::ImageBox>("ImageBox", coord, MyGUI::Align::Stretch, "aabb");
		_imageboxs[index] = imagebox;
		

		imagebox->setItemSelect(0);
		imagebox->setDepth(index + 1);
		imagebox->eventMouseSetFocus += MyGUI::newDelegate(this, &PackageWindow::notifySetFocus);
		imagebox->eventMouseLostFocus += MyGUI::newDelegate(this, &PackageWindow::notifySetFocus);
	}

	setImageInfoFromIcon(imagebox, itemId);
	return true;
}

void PackageWindow::setItemFocus(
	uint32_t row,
	uint32_t column)
{
	MyGUI::IntCoord aa;
	aa.left = 16 + column * CELL_WIDTH;
	aa.top = 5 + row * CELL_HEIGHT;
	aa.width = ITEM_WIDTH;
	aa.height = ITEM_HEIGHT;

	_focus_box->setCoord(aa);
	_focus_box->setVisible(true);
}

void PackageWindow::update()
{
	const std::vector<KItem*>&  itemlist = GameDataManager::GetSingleton().getUserBag();

	for (int32_t i = 0; i < itemlist.size(); i++)
	{
		KItem* item = itemlist[i];
		if (item == nullptr)
		{
			continue;
		}
		int row = i / 6;
		int col = i % 6;

		updateItem(row, col, item->GetIdTable());
	}
}

