#pragma once


struct ItemData
{
	std::string icon;
	std::string title;
	std::string type;
	std::string desc;
	std::string birth_desc;
};

bool getItemInfo(uint32_t id, ItemData& data);