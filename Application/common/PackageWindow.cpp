#include "OgreHeader.h"
#include "PackageWindow.h"
#include "CEGUIResourceManager.h"
#include "application_util.h"
namespace demo
{

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

		mItemList.emplace_back();

		auto& back = mItemList.back();
		back._item_pos = 0;
		back._item_id = 10010070;
		
		MyGUI::FactoryManager& factory = MyGUI::FactoryManager::getInstance();

		MyGUI::IntCoord coord;
		coord.left = 16;
		coord.width = 32;
		coord.top = 6;
		coord.height = 32;
		back._item_image = mImageBackgroudCover->createWidget<MyGUI::ImageBox>("ImageBox", coord, MyGUI::Align::Stretch, "aabb");
		back._item_image->setVisible(true);
		setImageInfoFromIcon(back._item_image, 10010070);
		back._item_image->setItemSelect(0);
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

} // namespace demo
