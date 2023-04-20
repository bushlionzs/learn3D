#pragma once
#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
#include "ToolTip.h"

namespace demo
{
	struct PackageItemInfo
	{
		int32_t _item_pos;
		uint32_t _item_id;
		MyGUI::ImageBox* _item_image;
	};
	class PackageWindow :
		public wraps::BaseLayout
	{
	public:
		PackageWindow();

		void clearView();

		MyGUI::Widget* getView();

		void notifyToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info);
	private:
		MyGUI::ImageBox* mImageBackgroud;
		MyGUI::ImageBox* mImageBackgroudCover;
		std::vector<PackageItemInfo> mItemList;
		ToolTip* mToolTip;
	};

} // namespace demo

