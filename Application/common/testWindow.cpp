#include "OgreHeader.h"
#include "testWindow.h"
#include "application_util.h"

TestWindow::TestWindow() :
	BaseLayout("test.layout")
{
	assignWidget(mTextBox, "edit");
	assignWidget(mImageTest, "test");
	assignWidget(mItemBox, "itembox");
	MyGUI::ImageBox* aa = mItemBox->createWidget<MyGUI::ImageBox>(std::string("ImageBox"),
		MyGUI::IntCoord(0, 0, 100, 100),
		MyGUI::Align::Left, std::string("aabb"));
	setImageInfo(aa, "CJSH_icons_1", "CJSH_icons_1_action_1");
	setImageInfo(mImageTest, "CJSH_icons_1", "CJSH_icons_1_action_1");
	//setImageInfo(mImageTest, "UI_MainBoard_3", "UI_MainBoard_3_Packet_Cover");
	mTextBox->setCaptionWithReplacing("#ff0000我是中国人\n#00ff00bbbbbbb");
}

TestWindow::~TestWindow()
{

}

MyGUI::Widget* TestWindow::getView()
{
	return mMainWidget;
}