#include "OgreHeader.h"
#include "ToolTip.h"
#include "application_util.h"
#include "platform_file.h"


ToolTip::ToolTip() :
	BaseLayout("equiptip.layout")
{
	assignWidget(mTextName, "itemname");
	assignWidget(mTextDesc, "desc");
	assignWidget(mImageInfo, "show");

	const MyGUI::IntCoord& coord = MyGUI::IntCoord();
	mOffsetHeight = mMainWidget->getHeight() - coord.height;


}

void ToolTip::show(uint32_t id, MyGUI::Widget* parent)
{

	if (!getItemInfo(id, mItemData))
	{
		return;
	}

	MyGUI::Colour color;
	color.red = 1.0f;
	color.green = 0.0f;
	color.blue = 0.0f;
	color.alpha = 1.0f;
	mTextName->setColour(color);

	std::string aa = "#ff0000aaaaaaaaa\n#00ff00bbbbbbb";
	mTextName->setCaptionWithReplacing(aa);

	
	
	mTextDesc->setColour(color);
	mTextDesc->setCaptionWithReplacing(aa);

	setImageInfoFromIcon(mImageInfo, id);

	mMainWidget->setVisible(true);

	mMainWidget->setDepth(0);

	mMainWidget->attachToWidget(parent);
}

void ToolTip::hide()
{
	mMainWidget->setVisible(false);
}

void ToolTip::move(const MyGUI::IntPoint& _point)
{
	const MyGUI::IntPoint offset(10, 10);

	MyGUI::IntPoint point = MyGUI::InputManager::getInstance().getMousePosition() + offset;


	auto* parent = mMainWidget->getParent();

	if (parent)
	{
		auto pos = parent->getPosition();
		point -= pos;
		mMainWidget->setPosition(point);
	}
	
}

