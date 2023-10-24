#include "StretchImage.h"
//#include <BaseManager.h>


namespace demo
{
	StretchImageBox::StretchImageBox(MyGUI::Widget* _parent) : BaseLayout("StretchImage.layout", _parent)
	{
		assignWidget(mSeparatorH, "SeparatorH");
		assignWidget(mSeparatorV, "SeparatorV");
        assignWidget(mSeparatorCorner, "SeparatorCorner");

		assignWidget(mImagebox, "Left");
		assignWidget(mBackgroudImageBox, "BackgroudImageBox");

		mSeparatorH->eventMouseButtonPressed += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
		mSeparatorH->eventMouseDrag += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

		mSeparatorV->eventMouseButtonPressed += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
		mSeparatorV->eventMouseDrag += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

        mSeparatorCorner->eventMouseButtonPressed += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
        mSeparatorCorner->eventMouseDrag += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

		mImagebox->eventMouseButtonPressed += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
		mImagebox->eventMouseDrag += MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

        mBackgroudImageBox->setCoord(_parent->getCoord());

        mDefaultImagebox = mImagebox->getCoord();
        mDefaultSeparatorH = mSeparatorH->getCoord();
        mDefaultSeparatorV = mSeparatorV->getCoord();
        mDefaultSeparatorCorner = mSeparatorCorner->getCoord();
	}

	StretchImageBox::~StretchImageBox()
	{
        mSeparatorH->eventMouseButtonPressed -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
        mSeparatorH->eventMouseDrag -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

        mSeparatorV->eventMouseButtonPressed -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
        mSeparatorV->eventMouseDrag -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

        mSeparatorCorner->eventMouseButtonPressed -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
        mSeparatorCorner->eventMouseDrag -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);

        mImagebox->eventMouseButtonPressed -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseButtonPressed);
        mImagebox->eventMouseDrag -= MyGUI::newDelegate(this, &StretchImageBox::notifyMouseDrag);
	}

    void StretchImageBox::init(MyGUI::IntCoord* origin_coord)
    {
        MyGUI::IntCoord mStartImagebox = mDefaultImagebox;
        MyGUI::IntCoord mStartSeparatorH = mDefaultSeparatorH;
        MyGUI::IntCoord mStartSeparatorV = mDefaultSeparatorV;
        MyGUI::IntCoord mStartSeparatorCorner = mDefaultSeparatorCorner;

        if (origin_coord)
        {
            int left_delta = origin_coord->left - mDefaultImagebox.left;
            int width_delta = origin_coord->width - mDefaultImagebox.width;
            int top_delta = origin_coord->top - mDefaultImagebox.top;
            int height_delta = origin_coord->height - mDefaultImagebox.height;

            mStartImagebox.left += left_delta;
            mStartImagebox.width += width_delta;
            mStartImagebox.top += top_delta;
            mStartImagebox.height += height_delta;

            mStartSeparatorH.left += (left_delta+width_delta);
            mStartSeparatorH.top = mStartImagebox.top;
            mStartSeparatorH.height += height_delta;

            mStartSeparatorV.left = mStartImagebox.left;
            mStartSeparatorV.top += (top_delta+height_delta);
            mStartSeparatorV.width += width_delta;

            mStartSeparatorCorner.left = mStartImagebox.width - mStartSeparatorCorner.width;
            mStartSeparatorCorner.top = mStartImagebox.height - mStartSeparatorCorner.height;
        }

        mImagebox->setCoord(mStartImagebox);
        mSeparatorH->setCoord(mStartSeparatorH);
        mSeparatorV->setCoord(mStartSeparatorV);
        mSeparatorCorner->setCoord(mStartSeparatorCorner);
    }

	void StretchImageBox::addImage(std::string& name)
	{
		mImagebox->setImageTexture(name);
	}

	void StretchImageBox::notifyMouseButtonPressed(MyGUI::Widget* _sender,
		int _left, int _top, MyGUI::MouseButton _id)
	{
		if (_id == MyGUI::MouseButton::Left)
		{
			mStartImagebox = mImagebox->getCoord();
			mStartSeparatorH = mSeparatorH->getCoord();
			mStartSeparatorV = mSeparatorV->getCoord();
            mStartSeparatorCorner = mSeparatorCorner->getCoord();
			mStartMousePosition = MyGUI::InputManager::getInstance().getMousePosition();
		}

        // eventOnChangeCoord(this, "", getImageCoord(), getParentCoord());
	}

	void StretchImageBox::notifyMouseDrag(MyGUI::Widget* _sender,
		int _left, int _top, MyGUI::MouseButton _id)
	{
		int minSize = 10;
		if (_id == MyGUI::MouseButton::Left)
		{
            MyGUI::IntCoord leftPanel = mStartImagebox;
            MyGUI::IntCoord separatorHPanel = mStartSeparatorH;
            MyGUI::IntCoord separatorVPanel = mStartSeparatorV;
            MyGUI::IntCoord separatorCornerPanel = mStartSeparatorCorner;

			if (_sender == mSeparatorH)
			{
				MyGUI::IntPoint mousePosition = MyGUI::InputManager::getInstance().getMousePosition();
				int delta = mousePosition.left - mStartMousePosition.left;

				leftPanel.width += delta;
				separatorHPanel.left += delta;
				separatorVPanel.width += delta;
                separatorCornerPanel.left += delta;

                MyGUI::IntCoord parentCoord = mMainWidget->getAbsoluteCoord();
                MyGUI::IntCoord coord = mImagebox->getAbsoluteCoord();

                int x = coord.left + leftPanel.width;

                int parent_x = parentCoord.left + parentCoord.width;

                if (x + minSize > parent_x)
                {
                    int diff = x + minSize - parent_x;

                    leftPanel.width -= diff;
                    separatorHPanel.left -= diff;
                    separatorVPanel.width -= diff;
                    separatorCornerPanel.left -= diff;
                }

				mImagebox->setCoord(leftPanel);
				mSeparatorH->setCoord(separatorHPanel);
				mSeparatorV->setCoord(separatorVPanel);
                mSeparatorCorner->setCoord(separatorCornerPanel);
			}
			else if(_sender == mSeparatorV)
			{
				MyGUI::IntPoint mousePosition = MyGUI::InputManager::getInstance().getMousePosition();
				int delta = mousePosition.top - mStartMousePosition.top;

				leftPanel.height += delta;
				separatorHPanel.height += delta;
				separatorVPanel.top += delta;
                separatorCornerPanel.top += delta;

                MyGUI::IntCoord parentCoord = mMainWidget->getAbsoluteCoord();
				MyGUI::IntCoord coord = mImagebox->getAbsoluteCoord();

                int y = coord.top + leftPanel.height;

                int parent_y = parentCoord.top + parentCoord.height;

                if (y + minSize > parent_y)
                {
                    int diff = y + minSize - parent_y;

                    leftPanel.height -= diff;
                    separatorHPanel.height -= diff;
                    separatorVPanel.top -= diff;
                    separatorCornerPanel.top -= diff;
                }
                
				mImagebox->setCoord(leftPanel);
				mSeparatorH->setCoord(separatorHPanel);
				mSeparatorV->setCoord(separatorVPanel);
                mSeparatorCorner->setCoord(separatorCornerPanel);
			}
            else if (_sender == mSeparatorCorner)
            {
                MyGUI::IntPoint mousePosition = MyGUI::InputManager::getInstance().getMousePosition();
                int top_delta = mousePosition.top - mStartMousePosition.top;
                int left_delta = mousePosition.left - mStartMousePosition.left;

                leftPanel.width += left_delta;
                leftPanel.height += top_delta;

                separatorHPanel.left += left_delta;
                separatorHPanel.height += top_delta;

                separatorVPanel.top += top_delta;
                separatorVPanel.width += left_delta;

                separatorCornerPanel.top += top_delta;
                separatorCornerPanel.left += left_delta;

                MyGUI::IntCoord parentCoord = mMainWidget->getAbsoluteCoord();
                MyGUI::IntCoord coord = mImagebox->getAbsoluteCoord();

                int x = coord.left + leftPanel.width;

                int parent_x = parentCoord.left + parentCoord.width;

                if (x + minSize > parent_x)
                {
                    int diff = x + minSize - parent_x;

                    leftPanel.width -= diff;
                    separatorHPanel.left -= diff;
                    separatorVPanel.width -= diff;
                    separatorCornerPanel.left -= diff;
                }


                int y = coord.top + leftPanel.height;

                int parent_y = parentCoord.top + parentCoord.height;

                if (y + minSize > parent_y)
                {
                    int diff = y + minSize - parent_y;

                    leftPanel.height -= diff;
                    separatorHPanel.height -= diff;
                    separatorVPanel.top -= diff;
                    separatorCornerPanel.top -= diff;
                }


                mImagebox->setCoord(leftPanel);
                mSeparatorH->setCoord(separatorHPanel);
                mSeparatorV->setCoord(separatorVPanel);
                mSeparatorCorner->setCoord(separatorCornerPanel);
            }
			else if (_sender == mImagebox)
			{
				MyGUI::IntPoint mousePosition = MyGUI::InputManager::getInstance().getMousePosition();
				int top_delta = mousePosition.top - mStartMousePosition.top;
				int left_delta = mousePosition.left - mStartMousePosition.left;

				leftPanel.left += left_delta;
				leftPanel.top += top_delta;

				separatorHPanel.left += left_delta;
				separatorHPanel.top += top_delta;
				separatorVPanel.left += left_delta;
				separatorVPanel.top += top_delta;

                // separatorCornerPanel.left += left_delta;
                // separatorCornerPanel.top += top_delta;

				mImagebox->setCoord(leftPanel);
				mSeparatorH->setCoord(separatorHPanel);
				mSeparatorV->setCoord(separatorVPanel);
                // mSeparatorCorner->setCoord(separatorCornerPanel);
			}
		}

        eventOnChangeCoord(this, "", getImageCoord(), getParentCoord());
	}

}//demo
