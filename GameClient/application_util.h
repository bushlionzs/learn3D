#pragma once
#include <MyGUI.h>
void setImageInfo(
	MyGUI::ImageBox* image,
	const String& imagesetname,
	const String& imagename);

void setImageInfoFromIcon(MyGUI::ImageBox* image, uint32_t item_id);