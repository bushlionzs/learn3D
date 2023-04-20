#include "OgreHeader.h"
#include "SelfEquipWindow.h"
#include "CEGUIResourceManager.h"
#include "application_util.h"

namespace demo
{

	SelfEquipWindow::SelfEquipWindow() :
		BaseLayout("selfequip.layout")
	{
		assignWidget(mImageEquip, "equip");
		assignWidget(mImageClothes, "clothes");
		assignWidget(mImageClose, "close");
		assignWidget(mImageHelp, "help");

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

} // namespace demo
