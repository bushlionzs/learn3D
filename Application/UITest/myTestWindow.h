#pragma once

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
class MyTestWindow :
	public wraps::BaseLayout
{
public:
	MyTestWindow();
	~MyTestWindow();

	MyGUI::Widget* getView();
private:
};