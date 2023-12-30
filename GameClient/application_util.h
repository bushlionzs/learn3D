#pragma once
#include <MyGUI.h>
void setImageInfo(
	MyGUI::ImageBox* image,
	const String& imagesetname,
	const String& imagename);

void setImageInfoFromIcon(MyGUI::ImageBox* image, uint32_t item_id);

struct ItemData
{
	std::string icon;
	std::string title;
	std::string type;
	std::string desc;
	std::string birth_desc;
};

bool getItemInfo(uint32_t id, ItemData& data);