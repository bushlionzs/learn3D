#include "OgreHeader.h"
#include "SelfEquipWindow.h"
#include "CEGUIResourceManager.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"

SelfEquipWindow::SelfEquipWindow() :
	BaseLayout("selfequip.layout")
{
	assignWidget(mImageEquip, "equip");
	assignWidget(mImageClose, "close");
	assignWidget(mImageHelp, "help");
	assignWidget(mImageModel, "model");
	String imagesetname = "UI_MainBoard_2";
	String imagename = "UI_MainBoard_2_Selfequip_Board";
	setImageInfo(mImageEquip, imagesetname, imagename);

	mImageEquip->setItemSelect(0);


	imagesetname = "UI_duihua_1";
	imagename = "UI_duihua_1_close_normal";

	setImageInfo(mImageClose, imagesetname, imagename);
	mImageClose->setItemSelect(0);

	imagesetname = "UI_duihua_1";
	imagename = "UI_duihua_1_help_normal";

	setImageInfo(mImageHelp, imagesetname, imagename);
	mImageHelp->setItemSelect(0);

	mEquips.resize(HEQUIP_NUMBER);
	mEquipCoords.resize(HEQUIP_NUMBER);

	auto right = 300;

	mEquipCoords[HEQUIP_MAINHAND] = { 39, 106, 32, 32 };
	mEquipCoords[HEQUIP_ASSIHAND] = { right, 106, 32, 32 };
	mEquipCoords[HEQUIP_HEAD] = {39, 148, 32, 32};
	mEquipCoords[HEQUIP_NECK] = { right, 148, 32, 32};
	mEquipCoords[HEQUIP_SHOULDER] = {39, 356, 32, 32};
	mEquipCoords[HEQUIP_BACK] = { 39, 189, 32, 32 };
	mEquipCoords[HEQUIP_WRIST] = { right, 148, 32, 32 };
	mEquipCoords[HEQUIP_FEET] = { right, 315, 32, 32};

	mEquipCoords[HEQUIP_RING1] = { right, 231, 32, 32 };
	mEquipCoords[HEQUIP_RING1] = { right, 273, 32, 32 };

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
	if (_info.type == MyGUI::ToolTipInfo::Show)
	{
		uint32_t* value = _sender->getUserData<uint32_t>();
		ItemData itemdata;

		auto& equips = GameDataManager::GetSingleton().getUserEquip();

		KItem* item = equips[*value];
		auto id = item->GetIdTable();
		mToolTip->show(id);
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

void SelfEquipWindow::update()
{
	auto& equips = GameDataManager::GetSingleton().getUserEquip();


	for (int32_t i = 0; i < HEQUIP_NUMBER; i++)
	{
		KItem* item = equips[i];

		if (item)
		{
			createImageBox(i);
			auto id = item->GetIdTable();
			setImageInfoFromIcon(mEquips[i], id);
		}
		else
		{
			setImageInfoFromIcon(mEquips[i], -1);
		}
	}
	
}

void SelfEquipWindow::createImageBox(uint32_t pos)
{
	if (mEquips[pos])
		return;

	auto imagebox = mImageEquip->createWidget<MyGUI::ImageBox>("ImageBox", mEquipCoords[pos], MyGUI::Align::Stretch, "");

	imagebox->setNeedToolTip(true);
	imagebox->eventToolTip += MyGUI::newDelegate(this, &SelfEquipWindow::notifyToolTip);
	imagebox->setVisible(true);
	imagebox->setUserData(pos);
	
	mEquips[pos] = imagebox;
}