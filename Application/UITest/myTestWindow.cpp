#include "OgreHeader.h"
#include "myTestWindow.h"
#include "application_util.h"
#include "StretchImage.h"
#include "PackageBox.h"

MyTestWindow::MyTestWindow() :
	BaseLayout("test.layout")
{
	auto obj = new PackageBox(mMainWidget);

	MyGUI::IntCoord pos;
	pos.left = 0;
	pos.top = 0;
	pos.width = 296;
	pos.height = 407;
	obj->init(6, 6, pos);

	obj->updateItem(0, 0, 10010070);
	obj->updateItem(0, 1, 10010070);
	obj->updateItem(0, 5, 10010070);

	obj->updateItem(1, 0, 10010070);
	obj->updateItem(1, 1, 10010070);
	obj->updateItem(1, 5, 10010070);

	obj->updateItem(3, 4, 10010070);
	obj->updateItem(4, 4, 10010070);
	obj->updateItem(5, 4, 10010070);
	obj->updateItem(5, 5, 10010070);
	obj->setItemFocus(5, 4);
}

MyTestWindow::~MyTestWindow()
{

}

MyGUI::Widget* MyTestWindow::getView()
{
	return mMainWidget;
}