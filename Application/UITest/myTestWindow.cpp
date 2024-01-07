#include "OgreHeader.h"
#include "myTestWindow.h"
#include "application_util.h"
#include "StretchImage.h"
#include "PackageBox.h"
#include <platform_file.h>
#include "VideoManager.h"

MyTestWindow::MyTestWindow() :
	BaseLayout("test.layout")
{
	assignWidget(mTextName, "text");
	assignWidget(mEditBox, "edit");
	std::string aa = "#ff0000aaaaaaaaa\n#00ff00bbbbbbb";
	mTextName->setCaption(L"#ff0000我是中国人bbbbbbb");

	assignWidget(mLeftButton, "pig");
	assignWidget(mRightButton, "btn");
	mRightButton->eventMouseButtonPressed += MyGUI::newDelegate(this, &MyTestWindow::onWindowMouseButtonPressed);
	mLeftButton->eventMouseButtonPressed += MyGUI::newDelegate(this, &MyTestWindow::onWindowMouseButtonPressed);


	mEditBox->setFontHeight(40);

	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
	mEditBox->addText(L"#ff0000我是中国人\n#00ff00bbbbbbb");
}

MyTestWindow::~MyTestWindow()
{

}

void MyTestWindow::show(uint32_t id)
{
	GameItemData mItemData;
	if (!getItemInfo(id, mItemData))
	{
		return;
	}
	std::wstring aa = acsi_to_widebyte(mItemData.title.c_str());
	mTextName->setCaption(aa);
	aa = acsi_to_widebyte(mItemData.desc.c_str());
	mTextDesc->setCaption(aa);

	setImageInfoFromIcon(mImageInfo, id);

	/*const MyGUI::IntSize& text_size = MyGUI::IntSize();
	mMainWidget->setSize(mMainWidget->getWidth(), mOffsetHeight + text_size.height);*/
	mTextName->setVisible(true);
	mMainWidget->setVisible(true);

}

void MyTestWindow::onWindowMouseButtonPressed(
	MyGUI::Widget* _sender,
	int _left,
	int _top,
	MyGUI::MouseButton _id)
{
	if (_sender == mRightButton)
	{
		VideoManager::getSingleton().playSound("一见钟情.mp3");
	}
	else
	{
		VideoManager::getSingleton().playSound("猪叫.ogg");
	}
}

MyGUI::Widget* MyTestWindow::getView()
{
	return mMainWidget;
}