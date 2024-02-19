#pragma once
#include <CEGUI/CEGUI.h>
#include "ToolTip.h"
#include "UIDefine.h"

struct PackageItemInfo
{
	int32_t _item_pos;
	uint32_t _item_id;
	CEGUI::Window* _item_image;
};
class PackageWindow :public UIBase
{
public:
	PackageWindow(CEGUI::Window* parent);
	virtual void update() override;

	bool handle_ButtonClick(const CEGUI::EventArgs& args);
	bool handle_PackageClick(const CEGUI::EventArgs& args);
private:
	bool updateItem(
		uint32_t index,
		uint32_t itemId);
private:
	std::vector<PackageItemInfo> _package_item_list;
};


