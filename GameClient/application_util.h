#pragma once

#include <server_message.pb.h>

struct ItemData
{
	std::string icon;
	std::string title;
	std::string type;
	std::string desc;
	std::string birth_desc;
};

bool getItemInfo(uint32_t id, ItemData& data);

std::string transformImageName(const char* name);

struct EventData
{
	uint32_t type;
	std::string desc;
};
bool getEventItemInfo(const servermessage::EventItem* item, EventData& result);

bool FormatQuestString(String& strConvert);

struct UIDesc
{
	std::string caption;
	std::string attachment;
};
bool replaceUIDesc(String& desc, std::vector<UIDesc>& buttonlist);

