#include "OgreHeader.h"
#include "ToolTip.h"

namespace demo
{

	ToolTip::ToolTip() :
		BaseLayout("equiptip.layout")
	{
		assignWidget(mTextName, "itemname");
		assignWidget(mTextLevel, "level");
		assignWidget(mImageInfo, "show");

		const MyGUI::IntCoord& coord = MyGUI::IntCoord();
		mOffsetHeight = mMainWidget->getHeight() - coord.height;
	}

	void ToolTip::show(ItemData* _data)
	{
		if (_data == nullptr)
			return;

		mTextLevel->setCaption("level");
		mTextName->setCaption(_data->_itemname.c_str());

		const MyGUI::IntSize& text_size = MyGUI::IntSize();
		mMainWidget->setSize(mMainWidget->getWidth(), mOffsetHeight + text_size.height);

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

} // namespace demo
