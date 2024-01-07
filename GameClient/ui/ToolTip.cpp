#include "OgreHeader.h"
#include "ToolTip.h"
#include "application_util.h"


ToolTip::ToolTip() :
	BaseLayout("equiptip.layout")
{
	assignWidget(mTextName, "itemname");
	assignWidget(mTextDesc, "desc");
	assignWidget(mImageInfo, "show");

	const MyGUI::IntCoord& coord = MyGUI::IntCoord();
	mOffsetHeight = mMainWidget->getHeight() - coord.height;

	
}

void ToolTip::show(uint32_t id)
{

	if (!getItemInfo(id, mItemData))
	{
		return;
	}
	mTextName->setCaption(mItemData.title);
	mTextDesc->setCaption(mItemData.desc);
	
	setImageInfoFromIcon(mImageInfo, id);

	/*const MyGUI::IntSize& text_size = MyGUI::IntSize();
	mMainWidget->setSize(mMainWidget->getWidth(), mOffsetHeight + text_size.height);*/
	mTextName->setVisible(true);
	mMainWidget->setVisible(true);

}

void ToolTip::hide()
{
	mMainWidget->setVisible(false);
}

void ToolTip::move(const MyGUI::IntPoint& _point)
{
	const MyGUI::IntPoint offset(10, 10);

	MyGUI::IntPoint point = MyGUI::InputManager::getInstance().getMousePosition() + offset;

	const MyGUI::IntSize& size = mMainWidget->getSize();
	const MyGUI::IntSize& view_size = mMainWidget->getParentSize();

	if ((point.left + size.width) > view_size.width)
	{
		point.left -= offset.left + offset.left + size.width;
	}
	if ((point.top + size.height) > view_size.height)
	{
		point.top -= offset.top + offset.top + size.height;
	}

	mMainWidget->setPosition(point);
}

