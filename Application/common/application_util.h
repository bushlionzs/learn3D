#pragma once
#include <MyGUI.h>
void setImageInfo(
	MyGUI::ImageBox* image,
	const String& imagesetname,
	const String& imagename);

void setImageInfoFromIcon(MyGUI::ImageBox* image, uint32_t item_id);

struct GameItemData
{
	std::string icon;
	std::string title;
	std::string desc;
	std::string type;
	std::string birth_desc;
};

bool getItemInfo(uint32_t id, GameItemData& data);