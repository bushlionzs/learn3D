#pragma once
#pragma once

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
#include <limits>

namespace demo
{
	class StretchImageBox :
		public wraps::BaseLayout
	{
	public:
		StretchImageBox(MyGUI::Widget* _parent = nullptr);
		~StretchImageBox();

	public:
		void init(MyGUI::IntCoord* origin_coord);

		void addImage(std::string& name);
		// void setCoord(MyGUI::IntCoord& coord);
		MyGUI::IntCoord getImageCoord() { return mImagebox->getCoord(); }
		MyGUI::IntCoord getParentCoord() { return mMainWidget->getCoord(); }
		// MyGUI::IntCoord getOutputCoord();
		MyGUI::ImageBox* get_backgroud_image_box()
		{
			return mBackgroudImageBox;
		}

		void notifyMouseButtonPressed(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
		void notifyMouseDrag(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	public:
		MyGUI::delegates::CDelegate4<BaseLayout*, const MyGUI::UString&, const MyGUI::IntCoord&, const MyGUI::IntCoord&> eventOnChangeCoord;

	private:
		MyGUI::ImageBox* mImagebox;
		MyGUI::ImageBox* mBackgroudImageBox;
		MyGUI::Widget* mSeparatorH;
		MyGUI::Widget* mSeparatorV;
        MyGUI::Widget* mSeparatorCorner;

		MyGUI::IntCoord mDefaultImagebox;
		MyGUI::IntCoord mDefaultSeparatorH;
		MyGUI::IntCoord mDefaultSeparatorV;
        MyGUI::IntCoord mDefaultSeparatorCorner;

		MyGUI::IntCoord mStartImagebox;
		MyGUI::IntCoord mStartSeparatorH;
		MyGUI::IntCoord mStartSeparatorV;
        MyGUI::IntCoord mStartSeparatorCorner;

		MyGUI::IntPoint mStartMousePosition;

	};

} // namespace demo

