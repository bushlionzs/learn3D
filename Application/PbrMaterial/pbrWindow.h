#pragma once

#include <CEGUI/WindowManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/System.h>
//#include <CEGUI/ImagesetManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/ImageManager.h>
#include <DefaultWindow.h>
#include <FrameWindow.h>
#include <CEGUIManager.h>
class PbrMaterial;
class PBRWindow
{
public:
	PBRWindow(PbrMaterial* self);
	~PBRWindow();
	bool handleItemSelected(const CEGUI::EventArgs& args);

	bool handleMaterialTypeSelected(const CEGUI::EventArgs& args);

	bool handleLightDirectionChanged(const CEGUI::EventArgs& args);
private:
	CEGUI::Window* mRoot = nullptr;
	PbrMaterial* mPbrMaterial = nullptr;
	Ogre::Vector3 mLightDirection;
};