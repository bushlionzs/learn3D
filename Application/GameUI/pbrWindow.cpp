#include "stdafx.h"
#include <pbrWindow.h>

PBRWindow::PBRWindow()
{
    CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
    
    mRoot = (CEGUI::DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");
    auto* guiContext = CEGUIManager::getSingleton().getGUIContext();
    guiContext->setRootWindow(mRoot);

    auto* main = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("forge.xml");

    mRoot->addChild(main);

    CEGUI::Combobox* RenderMode = (CEGUI::Combobox*)main->getChildRecursive("RenderMode");

    CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem("Shaded", (CEGUI::uint)0);
    RenderMode->addItem(item);
    RenderMode->setItemSelectState(item, true);

    item = new CEGUI::ListboxTextItem("Albedo", (CEGUI::uint)1);
    RenderMode->addItem(item);

    item = new CEGUI::ListboxTextItem("Normals", (CEGUI::uint)2);
    RenderMode->addItem(item);

    item = new CEGUI::ListboxTextItem("Roughness", (CEGUI::uint)3);
    RenderMode->addItem(item);

    item = new CEGUI::ListboxTextItem("Metallic", (CEGUI::uint)4);
    RenderMode->addItem(item);

    item = new CEGUI::ListboxTextItem("AO", (CEGUI::uint)5);
    RenderMode->addItem(item);

    RenderMode->subscribeEvent(
        CEGUI::Combobox::EventListSelectionAccepted,
        CEGUI::Event::Subscriber(&PBRWindow::handleItemSelected, this));
    
}

PBRWindow::~PBRWindow()
{

}

bool PBRWindow::handleItemSelected(const CEGUI::EventArgs& args)
{
    CEGUI::Combobox* RenderMode = (CEGUI::Combobox*)(((CEGUI::WindowEventArgs&)args).window);
    CEGUI::ListboxItem* item = RenderMode->getSelectedItem();
    
    auto id = item->getID();

    return true;
}