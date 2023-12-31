#include "OgreHeader.h"
#include "myTestWindow.h"
#include "application_util.h"
#include "StretchImage.h"
#include "PackageBox.h"

MyTestWindow::MyTestWindow() :
	BaseLayout("equiptip.layout")
{
	//MyGUI::TextBox* bb;
	//assignWidget(bb, "text");
	MyGUI::IntCoord aa;
	aa.left = 50;
	aa.top = 50;
	aa.width = 100;
	aa.height = 50;
	/*auto texbox = mMainWidget->createWidget<MyGUI::TextBox>("TextBox", aa, MyGUI::Align::Default, "aabb");

	texbox->setCaption("BBBBBBBBBBBBBBBBBBBBBBB");
	texbox->setVisible(true);*/
}

MyTestWindow::~MyTestWindow()
{

}

MyGUI::Widget* MyTestWindow::getView()
{
	return mMainWidget;
}