/*!
	@file
	@author		Albert Semenov
	@date		10/2008
*/
#ifndef EDITOR_WINDOW_H_
#define EDITOR_WINDOW_H_

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
#include "ToolTip.h"

namespace demo
{

	class SelfEquipWindow :
		public wraps::BaseLayout
	{
	public:
		SelfEquipWindow();

		void clearView();

		MyGUI::Widget* getView();

		void notifyToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info);
	private:
		MyGUI::ImageBox* mImageEquip;
		MyGUI::ImageBox* mImageClothes;
		MyGUI::ImageBox* mImageClose;
		MyGUI::ImageBox* mImageHelp;
		ToolTip* mToolTip;
	};

} // namespace demo

#endif // EDITOR_WINDOW_H_
