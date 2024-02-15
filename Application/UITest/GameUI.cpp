#include "stdafx.h"
#include "GameUI.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "OgreViewport.h"
#include "MyGUIManager.h"
#include "OgreTextureManager.h"
#include "OgreMaterialManager.h"
#include "OgreRenderTexture.h"
#include "OgreCamera.h"
#include "role.h"
#include "PackageWindow.h"
#include "mytestWindow.h"
#include <CEGUI/InputEvent.h>
#include <CEGUI/widgets/DragContainer.h>
#include <CEGUI/CEGUI.h>
#include <platform_file.h>

using namespace CEGUI;

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

bool GameUI::appInit()
{
	ApplicationBase::appInit();
    InputManager::getSingletonPtr()->addListener(this);
    //HelloDemo1();
    ToolTipDemo();
    //PackageDemo();
	return true;
}

void GameUI::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);

	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
    auto& defautContext = CEGUI::System::getSingleton().getDefaultGUIContext();
    //defautContext.injectTimePulse(delta);
    mGUIContext->injectTimePulse(delta);
}

EngineType GameUI::getEngineType()
{
	//return EngineType_Vulkan;
	return EngineType_Dx11;
}

void GameUI::helloDemo()
{
    WindowManager& winMgr = WindowManager::getSingleton();
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();
    auto* root = (DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");

    mGUIContext->setRootWindow(root);

    FrameWindow* wnd = (FrameWindow*)winMgr.createWindow("TaharezLook/FrameWindow", "Demo Window");

    // Here we attach the newly created FrameWindow to the previously created
    // DefaultWindow which we will be using as the root of the displayed gui.
    root->addChild(wnd);

    // Windows are in Relative metrics mode by default.  This means that we can
    // specify sizes and positions without having to know the exact pixel size
    // of the elements in advance.  The relative metrics mode co-ordinates are
    // relative to the parent of the window where the co-ordinates are being set.
    // This means that if 0.5f is specified as the width for a window, that window
    // will be half as its parent window.
    //
    // Here we set the FrameWindow so that it is half the size of the display,
    // and centered within the display.
    wnd->setPosition(UVector2(cegui_reldim(0.25f), cegui_reldim(0.25f)));
    wnd->setSize(USize(cegui_reldim(0.5f), cegui_reldim(0.5f)));

    // now we set the maximum and minum sizes for the new window.  These are
    // specified using relative co-ordinates, but the important thing to note
    // is that these settings are aways relative to the display rather than the
    // parent window.
    //
    // here we set a maximum size for the FrameWindow which is equal to the size
    // of the display, and a minimum size of one tenth of the display.
    wnd->setMaxSize(USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
    wnd->setMinSize(USize(cegui_reldim(0.1f), cegui_reldim(0.1f)));

    // As a final step in the initialisation of our sample window, we set the window's
    // text to "Hello World!", so that this text will appear as the caption in the
    // FrameWindow's titlebar.
    wnd->setText("Hello World!");

}

void GameUI::HelloDemo1()
{
    SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
    SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
    SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");

    FontManager& fontManager(FontManager::getSingleton());

    // Set it as the default


    WindowManager& winMgr = WindowManager::getSingleton();
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();
    CEGUI::Font& font(fontManager.createFromFile("simhei24.font"));
    mGUIContext->setDefaultFont(&font);
    auto* root = WindowManager::getSingleton().loadLayoutFromFile("hello.xml");

    mGUIContext->setRootWindow(root);



}

void GameUI::TooltipDemo()
{
    WindowManager& winMgr = WindowManager::getSingleton();
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();
    auto* root = (DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");

    mGUIContext->setRootWindow(root);

    mToolTip = WindowManager::getSingleton().loadLayoutFromFile("ToolTip.xml");
    root->addChild(mToolTip);
}

void GameUI::DragDropDemo()
{
    // load windows look
    SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
    

    // load font and setup default if not loaded via scheme
    Font& defaultFont = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");

    mGUIContext = CEGUIManager::getSingleton().getGUIContext();
    // Set default font for the gui context
    mGUIContext->setDefaultFont(&defaultFont);

    // set up defaults
    mGUIContext->getMouseCursor().setDefaultImage("WindowsLook/MouseArrow");

    // load the drive icons imageset
    ImageManager::getSingleton().loadImageset("DriveIcons.imageset");

    // load the initial layout
    mGUIContext->setRootWindow(
        WindowManager::getSingleton().loadLayoutFromFile("DragDropDemo.layout"));

    // setup events
    subscribeEvents();
}

void GameUI::subscribeEvents()
{
    using namespace CEGUI;

    Window* root = mGUIContext->getRootWindow();

  

    /*
     * Subscribe the same handler to each of the twelve slots
     */
    CEGUI::String base_name = "MainWindow/Slot";

    for (int i = 1; i <= 12; ++i)
    {
        CEGUI_TRY
        {
            // get the window pointer for this slot
            Window * wnd =
                root->getChild(base_name + PropertyHelper<int>::toString(i));

        // subscribe the handler.
        wnd->subscribeEvent(
            Window::EventDragDropItemDropped,
            Event::Subscriber(&GameUI::handle_ItemDropped, this));
        }
            // if something goes wrong, log the issue but do not bomb!
            CEGUI_CATCH(CEGUI::Exception&)
        {}
    }
}

bool GameUI::handle_ItemDropped(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

    if (!dd_args.window->getChildCount())
    {
        // add dragdrop item as child of target if target has no item already
        dd_args.window->addChild(dd_args.dragDropItem);
        // Now we must reset the item position from it's 'dropped' location,
        // since we're now a child of an entirely different window
        dd_args.dragDropItem->setPosition(
            UVector2(UDim(0.05f, 0), UDim(0.05f, 0)));
    }

    return true;
}

void GameUI::SelfEquipDemo()
{
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();

    mSelfEquip = WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.xml");
    FontManager& fontManager(FontManager::getSingleton());
    CEGUI::Font& font(fontManager.createFromFile("simhei12.font"));
    
    mGUIContext->setDefaultFont(&font);

    //font.setProperty("TextColor", "FF0000");
    DefaultWindow* aa = (DefaultWindow*)mSelfEquip;

    mGUIContext->setRootWindow(mSelfEquip);

    auto* button = mSelfEquip->getChildRecursive("Packet_Close");

    mToolTip = WindowManager::getSingleton().loadLayoutFromFile("ToolTip.xml");


    auto* wnd = mSelfEquip->getChildRecursive("SelfEquip_0");
    
    wnd->subscribeEvent(
        Window::EventMouseEntersSurface,
        Event::Subscriber(&GameUI::handle_MouseEnter, this));

    wnd->subscribeEvent(
        Window::EventMouseLeavesSurface,
        Event::Subscriber(&GameUI::handle_MouseLeave, this));

    auto* close = mSelfEquip->getChildRecursive("Packet_Close");
    close->subscribeEvent(
        Window::EventMouseClick,
        Event::Subscriber(&GameUI::handle_ButtonClick, this));
}

bool GameUI::handle_ButtonClick(const CEGUI::EventArgs& args)
{
    mSelfEquip->hide();
    return true;
}

void GameUI::injectKeyRelease(KeyCode _key)
{
    if (_key == KeyCode::B)
    {
        mRoot->addChild(mToolTip);
        mToolTip->show();
    }
    
    if (_key == KeyCode::N)
    {
        mToolTip->hide();
    }
}

void GameUI::PackageDemo()
{
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();

    ImageManager::getSingleton().loadImageset("cjsh.imageset");
    auto* root = WindowManager::getSingleton().loadLayoutFromFile("Package.xml");
    FontManager& fontManager(FontManager::getSingleton());
    CEGUI::Font& font(fontManager.createFromFile("simhei24.font"));
    mGUIContext->setDefaultFont(&font);


    mGUIContext->setRootWindow(root);

    CEGUI::String base_name = "DragContainer";

    Window* package = root->getChild("Packet_Background_Cover");

    for (int i = 0; i < 36; ++i)
    {

        // get the window pointer for this slot
        Window* wnd =
            package->getChild(base_name + PropertyHelper<int>::toString(i));


        wnd->subscribeEvent(
            Window::EventDragDropItemDropped,
            Event::Subscriber(&GameUI::handle_PackageItemDropped, this));
    }
}

bool GameUI::handle_MouseEnter(const CEGUI::EventArgs& args)
{
    UVector2 pos(UDim(0.5f, 0), UDim(0.05f, 0));
    mToolTip->setPosition(pos);
    mToolTip->setProperty("AlwaysOnTop", "true");
    mSelfEquip->addChild(mToolTip);
    mToolTip->show();
    return true;
}

bool GameUI::handle_MouseLeave(const CEGUI::EventArgs& args)
{
   
    mToolTip->hide();

    return true;
}

bool GameUI::handle_PackageItemDropped(const CEGUI::EventArgs& args)
{
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);
    Window* current = dd_args.window;
    Window* source = dd_args.dragDropItem;

    CEGUI::Window* source_image = source->getChild("Image");
    CEGUI::Window* current_image = current->getChild("Image");
    CEGUI::String source_name = source_image->getProperty("Image");
    CEGUI::String current_name = current_image->getProperty("Image");
    current_image->setProperty("Image", source_name);
    source_image->setProperty("Image", current_name);
    return true;
}

void GameUI::MultiDemo()
{
    WindowManager& winMgr = WindowManager::getSingleton();
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();

    auto* root = (DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");

    mGUIContext->setRootWindow(root);

    FontManager& fontManager(FontManager::getSingleton());
    CEGUI::Font& font(fontManager.createFromFile("simhei12.font"));
    mGUIContext->setDefaultFont(&font);


    auto* package = WindowManager::getSingleton().loadLayoutFromFile("Package.xml");
    root->addChild(package);

    auto* selfEquip = WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.Kylin.xml");
    root->addChild(selfEquip);
}

void GameUI::ToolTipDemo()
{
    WindowManager& winMgr = WindowManager::getSingleton();
    mGUIContext = CEGUIManager::getSingleton().getGUIContext();

    mRoot = (DefaultWindow*)winMgr.createWindow("DefaultWindow", "Root");

    mGUIContext->setRootWindow(mRoot);

    FontManager& fontManager(FontManager::getSingleton());
    CEGUI::Font& font(fontManager.createFromFile("simhei12.font"));
    mGUIContext->setDefaultFont(&font);

    mToolTip = WindowManager::getSingleton().loadLayoutFromFile("ToolTip.xml");
}