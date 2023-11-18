#include "OgreHeader.h"
#include "SelfEquipWindow.h"
#include "CEGUIResourceManager.h"
#include "application_util.h"



SelfEquipWindow::SelfEquipWindow() :
	BaseLayout("selfequip.layout")
{
	assignWidget(mImageEquip, "equip");
	assignWidget(mImageClothes, "clothes");
	assignWidget(mImageClose, "close");
	assignWidget(mImageHelp, "help");
	assignWidget(mImageModel, "model");
	//mImageModel->setImageTexture("awesomeface.png");
	String imagesetname = "UI_MainBoard_2";
	String imagename = "UI_MainBoard_2_Selfequip_Board";
	setImageInfo(mImageEquip, imagesetname, imagename);

	mImageEquip->setItemSelect(0);

	imagesetname = "test";
	imagename = "aa";

	setImageInfo(mImageClothes, imagesetname, imagename);
	mImageClothes->setItemSelect(0);

	imagesetname = "UI_duihua_1";
	imagename = "UI_duihua_1_close_normal";

	setImageInfo(mImageClose, imagesetname, imagename);
	mImageClose->setItemSelect(0);

	imagesetname = "UI_duihua_1";
	imagename = "UI_duihua_1_help_normal";

	setImageInfo(mImageHelp, imagesetname, imagename);
	mImageHelp->setItemSelect(0);


	mImageClothes->setNeedToolTip(true);
	mImageClothes->eventToolTip += MyGUI::newDelegate(this, &SelfEquipWindow::notifyToolTip);


	mToolTip = new ToolTip();
	mToolTip->hide();

	mImageEquip->eventMouseButtonPressed += MyGUI::newDelegate(this, &SelfEquipWindow::onWindowMouseButtonPressed);
	mImageEquip->eventMouseDrag += MyGUI::newDelegate(this, &SelfEquipWindow::onWindowMouseDrag);
	mImageEquip->eventMouseButtonReleased += MyGUI::newDelegate(this, &SelfEquipWindow::onWindowMouseButtonReleased);
}

void SelfEquipWindow::onWindowMouseButtonPressed(
	MyGUI::Widget* _sender,
	int _left,
	int _top,
	MyGUI::MouseButton _id)
{
	auto& gui = MyGUI::Gui::getInstance();
	auto windowList = gui.getEnumerator();
	int maxZ = 0;
	do
	{
		auto current = windowList.current();

		int curZ = current->getAbsoluteTop();
		if (curZ > maxZ)
			maxZ = curZ;
	} while (windowList.next());
	
	//mMainWidget->setPosition(mMainWidget->getPosition().left, maxZ + 1);

	mDragging = true;
	mDragOffset = MyGUI::IntPoint(_left, _top) - mMainWidget->getPosition();
}

void SelfEquipWindow::onWindowMouseDrag(
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

void SelfEquipWindow::onWindowMouseButtonReleased(
	MyGUI::Widget* _sender,
	int _left,
	int _top,
	MyGUI::MouseButton _id)
{
	mDragging = false;
}

void SelfEquipWindow::notifyToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info)
{
	ItemData item;
	item._itemname = "none";
	if (_sender == mImageClothes)
	{
		item._itemname = "clothes";
	}

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

void SelfEquipWindow::clearView()
{
	MyGUI::WidgetManager::getInstance().destroyWidgets(mMainWidget->getEnumerator());
}

MyGUI::Widget* SelfEquipWindow::getView()
{
	return mMainWidget;
}


void SelfEquipWindow::setModelTexture(const String& name)
{
	mImageModel->setImageTexture(name);
}
